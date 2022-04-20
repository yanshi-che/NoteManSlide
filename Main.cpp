#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#include <fstream>

#include "boost/json.hpp"
#include "MainSceneManager.h"
#include "Global.h"
#include "Config_Config.h"

using namespace boost;

class Fps {
	LONGLONG nowTime;
	LONGLONG time;
	LONGLONG waitTime;
	const LONGLONG sixtyWaitTime;
	const LONGLONG oneHundredTwentyWaitTime;
	int configFps;
	int fps;
	int fpsCount;
	LONGLONG fpsCountTime;
public:
	Fps(bool isConfigFpsSixty) : sixtyWaitTime(16666),oneHundredTwentyWaitTime(8333) {
		time = GetNowHiPerformanceCount();
		if (isConfigFpsSixty) {
			waitTime = sixtyWaitTime;
			Global::g_fpsDiff = 1.0;
			configFps = 60;
		}
		else {
			waitTime = oneHundredTwentyWaitTime;
			Global::g_fpsDiff = 0.5;
			configFps = 120;
		}
		nowTime = 0;
		fpsCountTime = time;
		fpsCount = 0;
		fps = 0;
	}

	void update() {
		nowTime = GetNowHiPerformanceCount();
		Global::g_time = nowTime;
		if (configFps != Config::g_fps) {
			if (configFps != 60) {
				configFps = 60;
				waitTime = sixtyWaitTime;
			}
			else {
				configFps = 120;
				waitTime = oneHundredTwentyWaitTime;
			}
		}
	}

	void drawFps() {
		++fpsCount;
		if (1000000 <= nowTime - fpsCountTime) {
			fps = fpsCount;
			fpsCount = 0;
			fpsCountTime = nowTime;
		}
		DrawFormatString(10, 10, GetColor(255, 255, 255), "%d", fps);
	}

	bool wait() {
		if (waitTime <= nowTime - time) {
			time = nowTime;
			return true;
		}
		return false;
	}
};

bool configInit() {
	//ファイルの読み込み用
	std::string s = "";
	std::string line = "";
	//json作成用の変数
	json::object obj;
	json::value val;
	json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();
	bool isFail = false;
	std::ifstream readfile(".\\config\\config.json");
	if (!readfile) {
		isFail = true;
		return true;
	}
	while (std::getline(readfile, line)) {
		s.append(line);
	}

	val = json::parse(s, sp);
	obj = val.at("Config").as_object();
	double hiSpeed = obj.at("hiSpeed").as_double();
	double judgeCorrection = obj.at("judge").as_double();
	std::uint16_t fps = static_cast<std::uint16_t>(obj.at("fps").as_int64());
	Config::g_hiSpeed += hiSpeed - Config::g_hiSpeed;
	Config::g_judgeCorrection += judgeCorrection - Config::g_judgeCorrection;
	Config::g_fps = fps;
	if (fps == 60) {
		return true;
	}
	return false;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(true);
	SetGraphMode(Global::WINDOW_WIDTH,Global::WINDOW_HEIGHT,Global::WINDOW_COLORBIT); //スクリーンの大きさの設定
	SetMainWindowText("NoteManSlide");
	SetWaitVSyncFlag(false);
	SetAlwaysRunFlag(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);//裏画面で画面生成
	//登録されている譜面が入ったディレクトリの読み込み
	std::string path = ".\\bgm";
	std::string bgmPath;

	try {
		for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)) {
			bgmPath = entry.path().string();
		}
	}
	catch (...) {
		DrawBox(30, 200, 710, 500, GetColor(0, 0, 0), true);
		DrawString(80, 300, "bgmの読み込みに失敗しました。\nディレクトリ構成、またはファイルに問題がある可能性があります。",GetColor(255,255,255));
		DrawString(80, 420, "5秒後にプログラムを終了します", GetColor(255, 255, 255));
		ScreenFlip();
		Sleep(5000);
		DxLib_End();				// ＤＸライブラリ使用の終了処理
		return 0;				// ソフトの終了
	}

	const int bgmHandle = LoadSoundMem(bgmPath.c_str());
	ChangeVolumeSoundMem(127, bgmHandle);

	const int backImgHandle = LoadGraph(".\\image\\background\\backImg.jpg");
	MainSceneManager mng = MainSceneManager(backImgHandle,bgmHandle);
	Fps* fps = nullptr;

	if (configInit()) {
		fps = new Fps(true);
	}
	else {
		fps = new Fps(false);
	}

	mng.initialize();
	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ProcessMessage() == 0) {
		fps->update();
		if (fps->wait()) {
			ClearDrawScreen();
			mng.update();
			mng.draw();
			fps->drawFps();
			ScreenFlip();
		}
	}

	mng.finalize();

	delete fps;
	DeleteGraph(backImgHandle);
	DeleteSoundMem(bgmHandle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理


	return 0;				// ソフトの終了
}
