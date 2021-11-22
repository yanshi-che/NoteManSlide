#include <iostream>
#include "Game_SceneManager.h"
#include "Game_Config.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);
	SetGraphMode(Game::WINDOW_WIDTH,Game::WINDOW_HEIGHT,Game::WINDOW_COLORBIT); //スクリーンの大きさの設定

	SetDrawScreen(DX_SCREEN_BACK);//裏画面で画面生成
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	Game::Game_SceneManager sm;

	sm.initialize();
	// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		sm.update();
		sm.draw();
	}

	sm.finalize();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}
