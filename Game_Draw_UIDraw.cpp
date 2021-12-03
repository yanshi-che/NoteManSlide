#include "Game_Draw_UIDraw.h"

Game::Draw::Game_Draw_UIDraw::Game_Draw_UIDraw(){
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "�t�@�C��(&F)", File);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "�V�K�쐬(&N)", NewFile);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "�J��(&O)", Open);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, TRUE, NULL, 0);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "�I��(&X)", Exit);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "�e�X�g(&T)", Test);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, Test, FALSE, "�Đ�(&P)", Play);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, Test, FALSE, "��~(&S)", Stop);
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

