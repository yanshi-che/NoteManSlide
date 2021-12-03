#include "Game_Draw_UIDraw.h"

Game::Draw::Game_Draw_UIDraw::Game_Draw_UIDraw(){
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "ファイル(&F)", File);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "新規作成(&N)", NewFile);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "開く(&O)", Open);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, TRUE, NULL, 0);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "終了(&X)", Exit);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "テスト(&T)", Test);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, Test, FALSE, "再生(&P)", Play);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, Test, FALSE, "停止(&S)", Stop);
	SetMenuItemSelectCallBackFunction(MenuItemSelectCallBack);
}

void Game::Draw::Game_Draw_UIDraw::setMusicData(std::unique_ptr<File::Game_File_MusicData> md) {
	musicData= std::move(md);
}

void Game::Draw::Game_Draw_UIDraw::MenuItemSelectCallBack(const TCHAR* itemName, int itemID){
	switch(itemID) {
	case NewFile:
		File::Game_File_MusicFileIO mfIO;
		Game_Draw_UIDraw ui;
		ui.setMusicData(mfIO.getMusicFile());
	}
}

