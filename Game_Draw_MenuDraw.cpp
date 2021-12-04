#include "Game_Draw_MenuDraw.h"

std::unique_ptr<Game::File::Game_File_MusicData> Game::Draw::Game_Draw_MenuDraw::musicData = nullptr;

Game::Draw::Game_Draw_DrawFactory* Game::Draw::Game_Draw_MenuDraw::drawFactory = nullptr;

Game::Draw::Game_Draw_MenuDraw::Game_Draw_MenuDraw(){
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "ファイル(&F)", File);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "新規作成(&N)", NewFile);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "開く(&O)", Open);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, TRUE, NULL, 0);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "終了(&X)", Exit);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "テスト(&T)", Test);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, Test, FALSE, "再生(&P)", Play);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, Test, FALSE, "停止(&S)", Stop);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "クオンタイズ(&Q)", QUONTIZE);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, QUONTIZE, FALSE, "4分音符", QUARTER);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, QUONTIZE, FALSE, "8分音符", EIGHTH);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, QUONTIZE, FALSE, "16分音符", SIXTEENTH);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, QUONTIZE, FALSE, "32分音符", THIRTYSECOND);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, QUONTIZE, FALSE, "3連符", TRIPLET);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, QUONTIZE, FALSE, "6連符", SEXTOLET);
	SetMenuItemSelectCallBackFunction(MenuItemSelectCallBack);
}

void Game::Draw::Game_Draw_MenuDraw::setMusicData(std::unique_ptr<File::Game_File_MusicData> md) {
	musicData= std::move(md);
	if (musicData!=nullptr) {
		drawFactory->getRaneDrawInstance()->setNumberOfRane(musicData.get()->getNumberOfRane());
		drawFactory->getBeatLineDrawInstance()->setMusicData(musicData.get());
	}
}

void Game::Draw::Game_Draw_MenuDraw::setDrawFactory(Game_Draw_DrawFactory* df) {
	drawFactory = df;
}

void Game::Draw::Game_Draw_MenuDraw::MenuItemSelectCallBack(const TCHAR* itemName, int itemID){
	switch(itemID) {
	case NewFile:
		File::Game_File_MusicFileIO mfIO;
		setMusicData(mfIO.getMusicFile());
		break;
	case QUARTER:
		if (musicData != nullptr) {
			drawFactory->getBeatLineDrawInstance()->setQuontize(quarterNote);
		}
		break;
	case EIGHTH:
		if (musicData != nullptr) {
			drawFactory->getBeatLineDrawInstance()->setQuontize(eighthNote);
		}
		break;
	case SIXTEENTH:
		if (musicData != nullptr) {
			drawFactory->getBeatLineDrawInstance()->setQuontize(sixteenthNote);
		}
		break;
	case THIRTYSECOND:
		if (musicData != nullptr) {
			drawFactory->getBeatLineDrawInstance()->setQuontize(thirtySecondNote);
		}
		break;
	case TRIPLET:
		if (musicData != nullptr) {
			drawFactory->getBeatLineDrawInstance()->setQuontize(tripletNote);
		}
		break;
	case SEXTOLET:
		if (musicData != nullptr) {
			drawFactory->getBeatLineDrawInstance()->setQuontize(sextoletNote);
		}
		break;
	}
}

