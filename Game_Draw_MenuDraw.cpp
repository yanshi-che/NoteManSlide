#include "Game_Draw_MenuDraw.h"

std::unique_ptr<Game::File::Game_File_MusicData> Game::Draw::Game_Draw_MenuDraw::musicData = nullptr;

Game::Draw::Game_Draw_DrawFactory* Game::Draw::Game_Draw_MenuDraw::drawFactory = nullptr;

Game::Draw::Game_Draw_MenuDraw::Game_Draw_MenuDraw(){
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "�t�@�C��(&F)", File);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "�V�K�쐬(&N)", NewFile);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "�J��(&O)", Open);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, TRUE, NULL, 0);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "�I��(&X)", Exit);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "�e�X�g(&T)", Test);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, Test, FALSE, "�Đ�(&P)", Play);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, Test, FALSE, "��~(&S)", Stop);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "�N�I���^�C�Y(�S��)", WholeQUONTIZE);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, WholeQUONTIZE, FALSE, "4������", WholeQUARTER);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, WholeQUONTIZE, FALSE, "8������", WholeEIGHTH);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, WholeQUONTIZE, FALSE, "16������", WholeSIXTEENTH);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, WholeQUONTIZE, FALSE, "32������", WholeTHIRTYSECOND);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, WholeQUONTIZE, FALSE, "3�A��", WholeTRIPLET);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, WholeQUONTIZE, FALSE, "6�A��", WholeSEXTOLET);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "�N�I���^�C�Y(����)", PartQUONTIZE);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "4������", PartQUARTER);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "8������", PartEIGHTH);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "16������", PartSIXTEENTH);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "32������", PartTHIRTYSECOND);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "3�A��", PartTRIPLET);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "6�A��", PartSEXTOLET);
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

