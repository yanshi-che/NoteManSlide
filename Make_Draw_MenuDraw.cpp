#include "Make_Draw_MenuDraw.h"

std::shared_ptr<Make::File::Make_File_MusicData> Make::Draw::Make_Draw_MenuDraw::p_musicData = nullptr;

Make::Draw::Make_Draw_MenuDraw::Make_Draw_MenuDraw(){
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "�t�@�C��(&F)", File);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "�V�K�쐬(&N)", NewFile);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "�J��(&O)", Open);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "�ۑ�(&S)", Save);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "�G�N�X�|�[�g(&E)", Export);
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
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, NoteType, FALSE, "�X���C�h", Slide);
	SetMenuItemSelectCallBackFunction(MenuItemSelectCallBack);
}

void Make::Draw::Make_Draw_MenuDraw::setMusicData(std::shared_ptr<File::Make_File_MusicData> md) {
	p_musicData	= md;
	if (p_musicData!=nullptr) {
		Singleton::Make_Singleton_BeatLineManager::getInstance()->initialize(p_musicData);
	}
}

void Make::Draw::Make_Draw_MenuDraw::MenuItemSelectCallBack(const TCHAR* itemName, int itemID){
	switch(itemID) {
	case NewFile:
		if (p_musicData == nullptr) {
			File::Make_File_MusicFileIO mfIO;
			setMusicData(mfIO.getMusicFile());
		}
		else {
			File::Make_File_MusicFileIO mfIO;
			std::unique_ptr<File::Make_File_MusicData> data = mfIO.getMusicFile();
			if (data != nullptr) {
				DeleteSoundMem(p_musicData->getMusicHandle());
				p_musicData.reset();
				Singleton::Make_Singleton_BeatLineManager::getInstance()->finalize();
				setMusicData(std::move(data));
			}
		}
		break;
	case Save:
		if (p_musicData != nullptr) {
			File::Make_File_SaveFileIO saIO;
			saIO.writeSaveData(p_musicData);
		}
		break;
	case Export:
		if (p_musicData != nullptr) {
			File::Make_File_JsonIO jsIO;
			jsIO.saveNewJson(p_musicData);
		}
		break;
	case WholeQUARTER:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::QUARTER,NULL,true);
		}
		break;
	case WholeEIGHTH:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::EIGHTH,NULL,true);
		}
		break;
	case WholeSIXTEENTH:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::SIXTEENTH,NULL,true);
		}
		break;
	case WholeTHIRTYSECOND:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::THIRTYSECOND,NULL,true);
		}
		break;
	case WholeTRIPLET:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::TRIPLET,NULL,true);
		}
		break;
	case PartQUARTER:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::QUARTER, Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize(), false);
		}
		break;
	case PartEIGHTH:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::EIGHTH, Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize(), false);
		}
		break;
	case PartSIXTEENTH:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::SIXTEENTH, Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize(), false);
		}
		break;
	case PartTHIRTYSECOND:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::THIRTYSECOND, Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize(), false);
		}
		break;
	case PartTRIPLET:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::TRIPLET, Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize(), false);
		}
		break;
	case Normal:
		Make_Draw_LineContainer::setNoteType(Global::NOTETYPENORMAL);
		break;
	case Long:
		Make_Draw_LineContainer::setNoteType(Global::NOTETYPELONG);
		break;
	case Slide:
		Make_Draw_LineContainer::setNoteType(Global::NOTETYPESLIDE);
		break;
	}

}

