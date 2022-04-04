#include "Game_Config_Config.h"

Game::Config::Game_Config_Config::Game_Config_Config(std::shared_ptr<SceneChanger>& p_sceneChanger) : Task(p_sceneChanger){
	p_keyCheck = Singleton::Singleton_KeyHitCheck::getInstance();
	hiSpeed = ::Config::g_hiSpeed;
	judgeCorrection = ::Config::g_judgeCorrection;
	fontColor = GetColor(255, 255, 255);
	edgeColor = GetColor(0, 128, 128);
	font = 0;
	isFail = false;
}

void Game::Config::Game_Config_Config::initialize() {
	font = CreateFontToHandle("Pristina", 60, 4, DX_FONTTYPE_ANTIALIASING_EDGE);
	//ファイルの読み込み用
	std::string s = "";
	std::string line = "";
	//json作成用の変数
	json::object obj;
	json::value val;
	json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();

	std::ifstream readfile(".\\config\\config.json");
	if (!readfile) {
		isFail = true;
		return;
	}
	while (std::getline(readfile, line)) {
		s.append(line);
	}

	val = json::parse(s, sp);
	obj = val.at("Config").as_object();
	hiSpeed = obj.at("hiSpeed").as_double();
	judgeCorrection = obj.at("judge").as_double();
}

void Game::Config::Game_Config_Config::finalize() {
	DeleteFontToHandle(font);
	::Config::g_hiSpeed += hiSpeed - ::Config::g_hiSpeed;
	::Config::g_judgeCorrection += judgeCorrection - ::Config::g_judgeCorrection;
	if (!isFail) {
		//json作成用の変数
		json::object obj;
		json::value val;
		json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();

		obj["Config"] = { { "hiSpeed",hiSpeed},{"judge",judgeCorrection} };
		val = obj;

		std::ofstream writeFile;
		writeFile.open(".\\config\\config.json", std::ios::out);
		writeFile << val << std::endl;
		writeFile.close();
	}
}

void Game::Config::Game_Config_Config::update() {
	if (p_keyCheck->getHitKeyLong(KEY_INPUT_UP) == 1 || 60 < p_keyCheck->getHitKeyLong(KEY_INPUT_UP)) {
		if (hiSpeed < 1.5) {
			hiSpeed += 0.01;
		}
	}
	else if (p_keyCheck->getHitKeyLong(KEY_INPUT_DOWN) == 1 || 60 < p_keyCheck->getHitKeyLong(KEY_INPUT_DOWN)) {
		if (0.02 < hiSpeed) {
			hiSpeed -= 0.01;
		}
	}
	if (p_keyCheck->getHitKeyLong(KEY_INPUT_RIGHT) == 1 || 60 < p_keyCheck->getHitKeyLong(KEY_INPUT_RIGHT)) {
		if (judgeCorrection < 0.05) {
			judgeCorrection += 0.001;
		}
	}
	else if (p_keyCheck->getHitKeyLong(KEY_INPUT_LEFT) == 1 || 60 < p_keyCheck->getHitKeyLong(KEY_INPUT_LEFT)) {
		if (-0.05 < judgeCorrection) {
			judgeCorrection -= 0.001;
		}
	}
	if (p_keyCheck->getHitKeyUsual(KEY_INPUT_ESCAPE)) {
		p_sceneChanger->changeScene(Scene::Home);
	}
}

void Game::Config::Game_Config_Config::draw() {
	drawKeyConf();
	DrawStringToHandle(50, 200, "HiSpeed :", fontColor, font, edgeColor);
	DrawFormatStringToHandle(350, 200, fontColor, font, "%.1f", hiSpeed * 10.0, edgeColor);
	DrawStringToHandle(50, 430, "  judge :", fontColor, font, edgeColor);
	DrawFormatStringToHandle(350, 430, fontColor, font, "%.1f", judgeCorrection * 1000.0, edgeColor);
	if (isFail) {
		DrawString(50, 600, "コンフィグファイルが読み込めませんでした。\n保存されません。", fontColor,edgeColor);
	}
}

void Game::Config::Game_Config_Config::drawKeyConf() {
	DrawString(10, 720, "戻る:escape", fontColor, edgeColor);
	DrawString(200, 720, "hiSpeed:↑↓", fontColor, edgeColor);
	DrawString(400, 720, "judge:←→", fontColor, edgeColor);
}