#include "Game_Draw_MenuDraw.h"

std::unique_ptr<Game::File::Game_File_MusicData> Game::Draw::Game_Draw_MenuDraw::musicData = nullptr;

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
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "�N�I���^�C�Y(����)", PartQUONTIZE);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "4������", PartQUARTER);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "8������", PartEIGHTH);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "16������", PartSIXTEENTH);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "32������", PartTHIRTYSECOND);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "3�A��", PartTRIPLET);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "�m�[�c�̎��", NoteType);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, NoteType, FALSE, "�ʏ�", Normal);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, NoteType, FALSE, "�����O", Long);
	SetMenuItemSelectCallBackFunction(MenuItemSelectCallBack);
}

void Game::Draw::Game_Draw_MenuDraw::setMusicData(std::unique_ptr<File::Game_File_MusicData> md) {
	musicData= std::move(md);
	if (musicData!=nullptr) {
		Singleton::Game_Singleton_RaneDraw::getInstance()->setNumberOfRane(musicData.get()->getNumberOfRane());
		Singleton::Game_Singleton_BeatLineManager::getInstance()->setMusicData(musicData.get());
	}
}

void Game::Draw::Game_Draw_MenuDraw::MenuItemSelectCallBack(const TCHAR* itemName, int itemID){
	switch(itemID) {
	case NewFile:
		if (musicData == nullptr) {
			File::Game_File_MusicFileIO mfIO;
			setMusicData(mfIO.getMusicFile());
		}
		else {

		}
		break;
	case WholeQUARTER:
		if (musicData != nullptr) {
			Singleton::Game_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::QUARTER,true);
		}
		break;
	case WholeEIGHTH:
		if (musicData != nullptr) {
			Singleton::Game_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::EIGHTH,true);
		}
		break;
	case WholeSIXTEENTH:
		if (musicData != nullptr) {
			Singleton::Game_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::SIXTEENTH,true);
		}
		break;
	case WholeTHIRTYSECOND:
		if (musicData != nullptr) {
			Singleton::Game_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::THIRTYSECOND,true);
		}
		break;
	case WholeTRIPLET:
		if (musicData != nullptr) {
			Singleton::Game_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::TRIPLET,true);
		}
		break;
	case PartQUARTER:
		if (musicData != nullptr) {
			Singleton::Game_Singleton_NoteManager::getInstance()->setBarIDForInitOneVector(Draw::Game_Draw_LineContainer::getbarIDForChangeQuontize());
			Singleton::Game_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::QUARTER, false);
		}
		break;
	case PartEIGHTH:
		if (musicData != nullptr) {
			Singleton::Game_Singleton_NoteManager::getInstance()->setBarIDForInitOneVector(Draw::Game_Draw_LineContainer::getbarIDForChangeQuontize());
			Singleton::Game_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::EIGHTH, false);
		}
		break;
	case PartSIXTEENTH:
		if (musicData != nullptr) {
			Singleton::Game_Singleton_NoteManager::getInstance()->setBarIDForInitOneVector(Draw::Game_Draw_LineContainer::getbarIDForChangeQuontize());
			Singleton::Game_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::SIXTEENTH, false);
		}
		break;
	case PartTHIRTYSECOND:
		if (musicData != nullptr) {
			Singleton::Game_Singleton_NoteManager::getInstance()->setBarIDForInitOneVector(Draw::Game_Draw_LineContainer::getbarIDForChangeQuontize());
			Singleton::Game_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::THIRTYSECOND, false);
		}
		break;
	case PartTRIPLET:
		if (musicData != nullptr) {
			Singleton::Game_Singleton_NoteManager::getInstance()->setBarIDForInitOneVector(Draw::Game_Draw_LineContainer::getbarIDForChangeQuontize());
			Singleton::Game_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::TRIPLET, false);
		}
		break;
	case Normal:
		Game_Draw_LineContainer::setNoteType(Global::NOTETYPENORMAL);
		break;
	case Long:
		Game_Draw_LineContainer::setNoteType(Global::NOTETYPELONG);
		break;
	}

}

