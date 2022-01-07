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
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "クオンタイズ(全体)", WholeQUONTIZE);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, WholeQUONTIZE, FALSE, "4分音符", WholeQUARTER);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, WholeQUONTIZE, FALSE, "8分音符", WholeEIGHTH);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, WholeQUONTIZE, FALSE, "16分音符", WholeSIXTEENTH);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, WholeQUONTIZE, FALSE, "32分音符", WholeTHIRTYSECOND);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, WholeQUONTIZE, FALSE, "3連符", WholeTRIPLET);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, WholeQUONTIZE, FALSE, "6連符", WholeSEXTOLET);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "クオンタイズ(小節)", PartQUONTIZE);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "4分音符", PartQUARTER);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "8分音符", PartEIGHTH);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "16分音符", PartSIXTEENTH);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "32分音符", PartTHIRTYSECOND);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "3連符", PartTRIPLET);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "6連符", PartSEXTOLET);
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
	case WholeQUARTER:
		if (musicData != nullptr) {

		}
		break;
	case WholeEIGHTH:
		if (musicData != nullptr) {

		}
		break;
	case WholeSIXTEENTH:
		if (musicData != nullptr) {

		}
		break;
	case WholeTHIRTYSECOND:
		if (musicData != nullptr) {

		}
		break;
	case WholeTRIPLET:
		if (musicData != nullptr) {

		}
		break;
	case WholeSEXTOLET:
		if (musicData != nullptr) {

		}
		break;
	case PartQUARTER:
		if (musicData != nullptr) {

		}
		break;
	case PartEIGHTH:
		if (musicData != nullptr) {

		}
		break;
	case PartSIXTEENTH:
		if (musicData != nullptr) {

		}
		break;
	case PartTHIRTYSECOND:
		if (musicData != nullptr) {

		}
		break;
	case PartTRIPLET:
		if (musicData != nullptr) {

		}
		break;
	case PartSEXTOLET:
		if (musicData != nullptr) {

		}
		break;
	}

}

