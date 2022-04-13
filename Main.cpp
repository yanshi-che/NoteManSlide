#include <fstream>

#include "boost/json.hpp"
#include "MainSceneManager.h"
#include "Global.h"
#include "Config_Config.h"

using namespace boost;

class Fps {
	int mStartTime;         //測定開始時刻
	int mCount;             //カウンタ
	double mFps;             //fps
	static const int N = 60;//平均を取るサンプル数
	static const int FPS = 60;	//設定したFPS

public:
	Fps() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool Update() {
		if (mCount == 0) { //1フレーム目なら時刻を記憶
			mStartTime = GetNowCount();
		}
		if (mCount == N) { //60フレーム目なら平均を計算する
			int t = GetNowCount();
			mFps = 1000.0 / ((t - mStartTime) / (double)N);
			mCount = 0;
			mStartTime = t;
		}
		mCount++;
		return true;
	}


	void Draw() {
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mFps);
	}

	void Wait() {
		int tookTime = GetNowCount() - mStartTime;	//かかった時間
		int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
		if (waitTime > 0) {
			Sleep(waitTime);	//待機
		}
	}
};

void configInit() {
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
		return;
	}
	while (std::getline(readfile, line)) {
		s.append(line);
	}

	val = json::parse(s, sp);
	obj = val.at("Config").as_object();
	double hiSpeed = obj.at("hiSpeed").as_double();
	double judgeCorrection = obj.at("judge").as_double();
	Config::g_hiSpeed += hiSpeed - Config::g_hiSpeed;
	Config::g_judgeCorrection += judgeCorrection - Config::g_judgeCorrection;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(true);
	SetGraphMode(Global::WINDOW_WIDTH,Global::WINDOW_HEIGHT,Global::WINDOW_COLORBIT); //スクリーンの大きさの設定
	SetMainWindowText("NoteManSlide");

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
		DrawString(80, 420, "5秒後に終了します", GetColor(255, 255, 255));
		ScreenFlip();
		Sleep(5000);
		DxLib_End();				// ＤＸライブラリ使用の終了処理
		return 0;				// ソフトの終了
	}

	const int bgmHandle = LoadSoundMem(bgmPath.c_str());
	ChangeVolumeSoundMem(127, bgmHandle);

	const int backImgHandle = LoadGraph(".\\image\\background\\backImg.jpg");
	SetBackgroundColor(30,30,30);
	MainSceneManager mng = MainSceneManager(backImgHandle,bgmHandle);
	Fps fps;

	configInit();

	mng.initialize();
	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		fps.Update();
		mng.update();
		mng.draw();
		fps.Draw();
		ScreenFlip();
		fps.Wait();
	}

	mng.finalize();

	DeleteGraph(backImgHandle);
	DeleteSoundMem(bgmHandle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}
