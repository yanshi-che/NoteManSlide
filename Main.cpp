#include <iostream>
#include "MainSceneManager.h"
#include "Global.h"

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
	const int backImgHandle = LoadGraph(".\\image\\background\\backImg.jpg");

	SetBackgroundColor(30,30,30);
	MainSceneManager mng = MainSceneManager(backImgHandle);
	Fps fps;

	mng.initialize();
	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		fps.Update();
		fps.Draw();
		mng.update();
		mng.draw();
		ScreenFlip();
		fps.Wait();
	}

	mng.finalize();

	DeleteGraph(backImgHandle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}
