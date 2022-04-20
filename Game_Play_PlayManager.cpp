#include "Game_Play_PlayManager.h"


Game::Play::Game_Play_PlayManager::Game_Play_PlayManager(std::shared_ptr<SceneChanger>& p_sceneChanger, std::shared_ptr<Game_MusicDataShareBetweenOtherSection>& p_musicDataShare, std::shared_ptr<Game::Game_PlayResultShare>& p_playResultShare): Task(p_sceneChanger),p_musicDataShare(p_musicDataShare),p_playResultShare(p_playResultShare) {
	p_lane = nullptr;
	p_score = nullptr;
	drawNoteFunc = [&] {return drawBeforeStart(); };
	startTime = 0;
	isGameStart = false;
	isMusicStart = false;
	isLoadFail = false;
	isPlayToEnd = true;
	nowTime = 0;
	startDelay = 5.0;
	configFont = 0;
	musicHandle = 0;
	downColor = GetColor(0, 0, 0);
	fontColor = GetColor(255, 255, 255);
	edgeColor = GetColor(0, 128, 128);
	p_keyHitCheck = ::Singleton::Singleton_KeyHitCheck::getInstance();
}

void Game::Play::Game_Play_PlayManager::initialize() {
	configFont = CreateFontToHandle("Pristina", 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	const std::uint16_t laneAmount = Global::LANE_AMOUNT;

	normalNoteVec.resize(laneAmount);
	longNoteVec.resize(laneAmount);
	slideNoteVec.resize(2);
	normalNote.resize(laneAmount);
	longNote.resize(laneAmount);
	slideNote.resize(2);
	normalCount.resize(laneAmount);
	longCount.resize(laneAmount);
	slideCount.resize(2);

	std::vector<bool> isFirst;//ロングノーツの初期化でつかうフラグ
	std::vector<double> startTime;//ロングノーツの初期化で始点の時間を保管
	isFirst.resize(laneAmount);
	startTime.resize(laneAmount);
	for (int i = 0; i < laneAmount; ++i) {
		normalCount.at(i) = 0;
		longCount.at(i) = 0;
		isFirst.at(i) = true;
		startTime.at(i) = 0;
	}
	slideCount.at(0) = 0;
	slideCount.at(1) = 0;

	//小節線の初期化
	barLineVec.resize(p_musicDataShare->getMusicData()->getBarLength());
	const double timePerBeat = (Global::MINUTE / p_musicDataShare->getMusicData()->getBpm()) * Global::QUARTER;
	double timeSum = p_musicDataShare->getMusicData()->getBeginDelay() + startDelay;
	for (int i = 0, iSize = static_cast<int>(barLineVec.size()); i < iSize; ++i) {
		barLineVec.at(i) = std::make_unique<Game_Play_BarLine>(timeSum);
		timeSum += timePerBeat;
	}


	std::uint16_t maxChain = 0;
	//ノーツの初期化
	if (!initializeNote(laneAmount, timePerBeat,maxChain)){
		DrawBox(30, 200, 710, 500, GetColor(0, 0, 0), true);
		DrawString(80, 300, "譜面データまたは音楽ファイルの読み込みに失敗しました。\nディレクトリ構成、またはファイルに問題がある可能性があります。", fontColor, edgeColor);
		DrawString(80, 420, "5秒後にメニューに戻ります", fontColor, edgeColor);
		ScreenFlip();
		Sleep(5000);
		isLoadFail = true;
		p_sceneChanger->changeScene(Scene::GameMenu);
		return;
	}

	//音楽ファイルの読み込み
	try {
		musicHandle = LoadSoundMem(p_musicDataShare->getMusicData()->getMusicPath().c_str());
	}
	catch (...) {
		DrawBox(30, 200, 710, 500, GetColor(0, 0, 0), true);
		DrawString(80, 300, "音楽ファイルの読み込みに失敗しました。\nディレクトリ構成、またはファイルに問題がある可能性があります。", fontColor, edgeColor);
		DrawString(80, 420, "5秒後にメニューに戻ります", fontColor, edgeColor);
		ScreenFlip();
		Sleep(5000);
		isLoadFail = true;
		p_sceneChanger->changeScene(Scene::GameMenu);
		return;
	}
	ChangeVolumeSoundMem(127, musicHandle);

	//エフェクト
	p_effect = std::make_shared<Game_Play_Effect>();
	if (!p_effect->loadEffect()) {
		DrawBox(30, 200, 710, 500, GetColor(0, 0, 0), true);
		DrawString(80, 300, "エフェクトデータの読み込みに失敗しました。\nディレクトリ構成、またはファイルに問題がある可能性があります。", fontColor, edgeColor);
		DrawString(80, 420, "5秒後にメニューに戻ります", fontColor, edgeColor);
		ScreenFlip();
		Sleep(5000);
		isLoadFail = true;
		p_sceneChanger->changeScene(Scene::GameMenu);
		return;
	}
	//レーン周りの描画
	p_lane = std::make_unique<Game_Play_Lane>();
	//スコアの描画
	p_score = std::make_shared<Game_Play_Score>(configFont,maxChain);

	//初期判定配置
	for (int i = 0; i < laneAmount; ++i) {
		if (normalNoteVec.at(i).size() != NULL) {
			normalNote.at(i) = normalNoteVec.at(i).at(0).get();
			normalNote.at(i)->setTurn(true);
		}
		if (longNoteVec.at(i).size() != NULL) {
			longNote.at(i) = longNoteVec.at(i).at(0).get();
			longNote.at(i)->setTurn(true);
		}
	}
	if (slideNoteVec.at(0).size() != NULL) {
		slideNote.at(0) = slideNoteVec.at(0).at(0).get();
		slideNote.at(0)->setTurn(true);
	}
	if (slideNoteVec.at(1).size() != NULL) {
		slideNote.at(1) = slideNoteVec.at(1).at(0).get();
		slideNote.at(1)->setTurn(true);
	}

	setYUpdateBorder();
}

void Game::Play::Game_Play_PlayManager::finalize() {
	DeleteFontToHandle(configFont);
	DeleteSoundMem(musicHandle);
	p_lane.reset();
	p_score.reset();
	p_effect->finalize();
	p_effect.reset();
}

void Game::Play::Game_Play_PlayManager::draw() {
	if (!isLoadFail) {
		p_lane->draw();
		p_score->draw();
		drawNoteFunc();
		drawDown();
		p_effect->draw();
		drawHiSpeed();
		drawJudgeCorrection();
		DrawString(10, 720, "中断 : escape", fontColor, edgeColor);
	}
}

void Game::Play::Game_Play_PlayManager::drawBeforeStart() {
	DrawString(280, 330, "Press Space to Start", fontColor);
}

void Game::Play::Game_Play_PlayManager::drawDown() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxAA(static_cast<float>(Global::PLAY_LANE_X_MIN + 1.0), static_cast<float>(Global::JUDGELINE_Y + Global::NOTE_HEIGHT), static_cast<float>(Global::PLAY_LANE_X_MAX - 1.0), static_cast<float>(Global::WINDOW_HEIGHT), downColor, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Game::Play::Game_Play_PlayManager::drawHiSpeed() {
	DrawStringToHandle(10, 50, "HiSpeed :", fontColor,configFont ,edgeColor);
	DrawFormatStringToHandle(100, 50, fontColor,configFont, "%.1f", Config::g_hiSpeed * 10.0,edgeColor);
}

void Game::Play::Game_Play_PlayManager::drawJudgeCorrection() {
	DrawStringToHandle(10, 80, "  judge :", fontColor,configFont,edgeColor);
	DrawFormatStringToHandle(100, 80, fontColor,configFont, "%.1f", Config::g_judgeCorrection * 1000.0,edgeColor);
}

void Game::Play::Game_Play_PlayManager::drawNote() {
	for (int i = 0, iSize = static_cast<int>(barLineVec.size()); i < iSize; ++i) {
		barLineVec.at(i)->draw(nowTime);
	}
	//座標更新
	for (int i = 0, iSize = Global::LANE_AMOUNT; i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(normalNoteVec.at(i).size()); k < kSize; ++k) {
			normalNoteVec.at(i).at(k)->draw(nowTime);
		}
		for (int k = 0, kSize = static_cast<int>(longNoteVec.at(i).size()); k < kSize; ++k) {
			longNoteVec.at(i).at(k)->draw(nowTime);
		}
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(0).size()); i < iSize; ++i) {
		slideNoteVec.at(0).at(i)->draw(nowTime);
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(1).size()); i < iSize; ++i) {
		slideNoteVec.at(1).at(i)->draw(nowTime);
	}
}

void Game::Play::Game_Play_PlayManager::nextNote(const std::uint16_t noteType, const std::uint16_t laneIndex) {
	if (noteType == Global::NOTETYPE_NORMAL) {
		++normalCount.at(laneIndex);
		if (normalCount.at(laneIndex) < normalNoteVec.at(laneIndex).size()) {
			normalNote.at(laneIndex) = normalNoteVec.at(laneIndex).at(normalCount.at(laneIndex)).get();
			normalNote.at(laneIndex)->setTurn(true);
		}
		else {
			normalNote.at(laneIndex) = nullptr;
		}
	}
	else if (noteType == Global::NOTETYPE_LONG) {
		++longCount.at(laneIndex);
		if (longCount.at(laneIndex) < longNoteVec.at(laneIndex).size()) {
			longNote.at(laneIndex) = longNoteVec.at(laneIndex).at(longCount.at(laneIndex)).get();
			longNote.at(laneIndex)->setTurn(true);
		}
		else {
			longNote.at(laneIndex) = nullptr;
		}
	}
	else if (noteType == Global::NOTETYPE_SLIDER || noteType == Global::NOTETYPE_SLIDEL) {
		++slideCount.at(laneIndex);
		if (slideCount.at(laneIndex) < slideNoteVec.at(laneIndex).size()) {
			slideNote.at(laneIndex) = slideNoteVec.at(laneIndex).at(slideCount.at(laneIndex)).get();
			slideNote.at(laneIndex)->setTurn(true);
		}
		else {
			slideNote.at(laneIndex) = nullptr;
		}
	}
}

void Game::Play::Game_Play_PlayManager::setYUpdateBorder() {
	//小節線
	for (int i = 0, iSize = static_cast<int>(barLineVec.size()); i < iSize; ++i) {
		barLineVec.at(i)->setYUpdateBorder();
	}
	//ノーツ
	for (int i = 0, iSize = Global::LANE_AMOUNT; i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(normalNoteVec.at(i).size()); k < kSize; ++k) {
			normalNoteVec.at(i).at(k)->setYUpdateBorder();
		}
		for (int k = 0, kSize = static_cast<int>(longNoteVec.at(i).size()); k < kSize; ++k) {
			longNoteVec.at(i).at(k)->setYUpdateBorder();
		}
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(0).size()); i < iSize; ++i) {
		slideNoteVec.at(0).at(i)->setYUpdateBorder();
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(1).size()); i < iSize; ++i) {
		slideNoteVec.at(1).at(i)->setYUpdateBorder();
	}
}

void Game::Play::Game_Play_PlayManager::playUpdate() {
	nowTime = (double)(Global::g_time - startTime) / 1000000.0;

	if (!isMusicStart && isGameStart && startDelay <= nowTime) {
		PlaySoundMem(musicHandle, DX_PLAYTYPE_BACK, true);
		isMusicStart = true;
	}
	for (int i = 0, iSize = static_cast<int>(barLineVec.size()); i < iSize; ++i) {
		barLineVec.at(i)->update(nowTime);
	}
	//座標更新
	for (int i = 0, iSize = Global::LANE_AMOUNT; i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(normalNoteVec.at(i).size()); k < kSize; ++k) {
			normalNoteVec.at(i).at(k)->update(nowTime);
		}
		for (int k = 0, kSize = static_cast<int>(longNoteVec.at(i).size()); k < kSize; ++k) {
			longNoteVec.at(i).at(k)->update(nowTime);
		}
		if (normalNote.at(i) != nullptr) {
			normalNote.at(i)->check(nowTime);
		}
		if (longNote.at(i) != nullptr) {
			longNote.at(i)->check(nowTime);
		}
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(0).size()); i < iSize; ++i) {
		slideNoteVec.at(0).at(i)->update(nowTime);
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(1).size()); i < iSize; ++i) {
		slideNoteVec.at(1).at(i)->update(nowTime);
	}
	if (slideNote.at(0) != nullptr) {
		slideNote.at(0)->check(nowTime);
	}
	if (slideNote.at(1) != nullptr) {
		slideNote.at(1)->check(nowTime);
	}
}

void Game::Play::Game_Play_PlayManager::update() {
	if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_UP) == 1) {
		if (Config::g_hiSpeed < 1.5) {
			Config::g_hiSpeed += 0.01;
			setYUpdateBorder();
		}
	}
	else if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_DOWN) == 1) {
		if (0.02 < Config::g_hiSpeed) {
			Config::g_hiSpeed -= 0.01;
			setYUpdateBorder();
		}
	}
	if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_RIGHT) == 1) {
		if (Config::g_judgeCorrection < 0.05) {
			Config::g_judgeCorrection += 0.001;
		}
	}
	else if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_LEFT) == 1) {
		if (-0.05 < Config::g_judgeCorrection) {
			Config::g_judgeCorrection -= 0.001;
		}
	}
	if (isMusicStart && CheckSoundMem(musicHandle) != 1 || p_keyHitCheck->getHitKeyUsual(KEY_INPUT_ESCAPE)) {
		if (p_keyHitCheck->getHitKeyUsual(KEY_INPUT_ESCAPE)) {
			isPlayToEnd = false;
		}
		p_playResultShare->setPerfect(p_score->getPerfect());
		p_playResultShare->setGreat(p_score->getGreat());
		p_playResultShare->setMiss(p_score->getMiss());
		p_playResultShare->setIsPlayToEnd(isPlayToEnd);
		p_playResultShare->setScore(p_score->getScore());
		p_playResultShare->setIsClear(p_score->isClear());
		p_sceneChanger->changeScene(Scene::GameResult);
	}
	if (p_keyHitCheck->getHitKeyUsual(KEY_INPUT_SPACE)) {
		isGameStart = true;
		this->startTime = Global::g_time;
		drawNoteFunc = [&] {return drawNote(); };
	}
	playUpdate();
	p_effect->update();
}

void Game::Play::Game_Play_PlayManager::updateKey() {
	for (int i = 0, iSize = Global::LANE_AMOUNT; i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(normalNoteVec.at(i).size()); k < kSize; ++k) {
			normalNoteVec.at(i).at(k)->updateKey();
		}
		for (int k = 0, kSize = static_cast<int>(longNoteVec.at(i).size()); k < kSize; ++k) {
			longNoteVec.at(i).at(k)->updateKey();
		}
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(0).size()); i < iSize; ++i) {
		slideNoteVec.at(0).at(i)->updateKey();
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(1).size()); i < iSize; ++i) {
		slideNoteVec.at(1).at(i)->updateKey();
	}

}

bool Game::Play::Game_Play_PlayManager::initializeNote(const std::uint16_t laneAmount, const double timePerBeat,std::uint16_t& maxChain) {

	std::vector<bool> isFirst;//ロングノーツの初期化でつかうフラグ
	std::vector<double> startTime;//ロングノーツの初期化で始点の時間を保管
	isFirst.resize(laneAmount);
	startTime.resize(laneAmount);
	for (int i = 0; i < laneAmount; ++i) {
		isFirst.at(i) = true;
		startTime.at(i) = 0;
	}

	//レーンのｘ座標
	double laneX[Global::LANE_AMOUNT + 1];
	const double laneWidth = (Global::PLAY_LANE_X_MAX - Global::PLAY_LANE_X_MIN) / laneAmount;
	for (int i = 0; i <= laneAmount; ++i) {
		laneX[i] = laneWidth * i + Global::PLAY_LANE_X_MIN;
	}

	//スコアの読み込み
	std::string line = "";
	std::string s = "";
	std::ifstream readfile(p_musicDataShare->getMusicData()->getScorePath());
	if (!readfile) {
		return false;
	}
	while (std::getline(readfile, line)) {
		s.append(line);
	}

	try {
		json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();
		json::value val = json::parse(s, sp);

		//ノーツの初期化
		const json::array noteDataArray = val.as_object().at("NoteData").as_array();
		const double sixteenthTime = timePerBeat / Global::SIXTEENTH;
		const double arrowWidthBetween = laneWidth / Global::ARROW_NUM_LANE;
		std::uint16_t noteType;
		std::uint16_t laneIndex;
		std::uint16_t directionRightOrLeft;
		std::uint16_t slideNoteIndexStart;
		std::uint16_t slideNoteIndexEnd;
		std::function<void(std::uint16_t, std::uint16_t)> nextNoteFunc = [&](std::uint16_t n, std::uint16_t l) {return nextNote(n, l); };
		for (int i = 0, iSize = static_cast<int>(noteDataArray.size()); i < iSize; ++i) {
			noteType = static_cast<std::uint16_t>(noteDataArray.at(i).at("noteType").as_int64());
			laneIndex = static_cast<std::uint16_t>(noteDataArray.at(i).at("laneIndex").as_int64());
			if (noteType == Global::NOTETYPE_NORMAL) {
				normalNoteVec.at(laneIndex)
					.push_back(std::make_unique<Game_Play_NormalNote>(
						noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
						laneIndex, laneX[laneIndex], laneX[laneIndex + 1], nextNoteFunc, p_score,p_effect));
				++maxChain;
			}
			else if (noteType == Global::NOTETYPE_LONG) {
				if (isFirst.at(laneIndex)) {
					startTime.at(laneIndex) = noteDataArray.at(i).at("time").as_double() + startDelay;
					isFirst.at(laneIndex) = false;
					++maxChain;
				}
				else {
					longNoteVec.at(laneIndex)
						.push_back(std::make_unique<Game_Play_LongNote>(
							startTime.at(laneIndex), noteDataArray.at(i).at("time").as_double() + startDelay, sixteenthTime, noteType,
							laneIndex, laneX[laneIndex], laneX[laneIndex + 1], nextNoteFunc, p_score, p_effect,maxChain));
					isFirst.at(laneIndex) = true;
				}
			}
			else if (noteType == Global::NOTETYPE_SLIDER || noteType == Global::NOTETYPE_SLIDEL) {
				if (noteDataArray.at(i).at("rightOrLeft").as_int64() == 1) {
					laneIndex = 0;
				}
				else {
					laneIndex = 1;
				}
				if (noteDataArray.at(i).at("directionRightOrLeft").as_int64() == 1) {
					directionRightOrLeft = 0;
				}
				else {
					directionRightOrLeft = 1;
				}
				slideNoteIndexStart = static_cast<std::uint16_t>(noteDataArray.at(i).at("slideLaneIndexStart").as_int64());
				slideNoteIndexEnd = static_cast<std::uint16_t>(noteDataArray.at(i).at("slideLaneIndexEnd").as_int64());
				if (laneIndex == 0) {
					if (directionRightOrLeft == 0) {//右の右向き
						slideNoteVec.at(laneIndex)
							.push_back(std::make_unique<Game_Play_SlideNote>(
								noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
								laneX[slideNoteIndexStart], laneX[slideNoteIndexEnd + 1], laneWidth, arrowWidthBetween, laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc, p_score, p_effect));
					}
					else {//右の左向き
						slideNoteVec.at(laneIndex)
							.push_back(std::make_unique<Game_Play_SlideNote>(
								noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
								laneX[slideNoteIndexStart + 1], laneX[slideNoteIndexEnd], laneWidth, arrowWidthBetween, laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc, p_score, p_effect));
					}
				}
				else {//左の右向き
					if (directionRightOrLeft == 0) {
						slideNoteVec.at(laneIndex)
							.push_back(std::make_unique<Game_Play_SlideNote>(
								noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
								laneX[slideNoteIndexStart], laneX[slideNoteIndexEnd + 1], laneWidth, arrowWidthBetween, laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc, p_score, p_effect));
					}
					else {//左の左向き
						slideNoteVec.at(laneIndex)
							.push_back(std::make_unique<Game_Play_SlideNote>(
								noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
								laneX[slideNoteIndexStart + 1], laneX[slideNoteIndexEnd], laneWidth, arrowWidthBetween, laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc, p_score, p_effect));
					}
				}
				++maxChain;
			}
		}
	}
	catch (...) {
		return false;
	}

	return true;
}