#include "Make_Draw_MenuDraw.h"

std::shared_ptr<Make::File::Make_File_MusicData> Make::Draw::Make_Draw_MenuDraw::p_musicData = nullptr;

Make::Draw::Make_Draw_MenuDraw::Make_Draw_MenuDraw(){
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "ファイル(&F)", File);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "新規作成(&N)", NewFile);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "開く(&O)", Open);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "保存(&S)", Save);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "エクスポート(&E)", Export);
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
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "クオンタイズ(小節)", PartQUONTIZE);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "4分音符", PartQUARTER);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "8分音符", PartEIGHTH);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "16分音符", PartSIXTEENTH);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "32分音符", PartTHIRTYSECOND);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, PartQUONTIZE, FALSE, "3連符", PartTRIPLET);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "ノーツの種類", NoteType);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, NoteType, FALSE, "通常", Normal);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, NoteType, FALSE, "ロング", Long);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, NoteType, FALSE, "スライド", Slide);
	SetMenuItemSelectCallBackFunction(MenuItemSelectCallBack);
}

void Make::Draw::Make_Draw_MenuDraw::setMusicData(std::unique_ptr<File::Make_File_MusicData> md) {
	p_musicData= std::move(md);
	if (p_musicData!=nullptr) {
		Singleton::Make_Singleton_LaneDraw::getInstance()->setamountOfLane(p_musicData.get()->getAmountOfLane());
		Singleton::Make_Singleton_BeatLineManager::getInstance()->setMusicData(p_musicData);
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
			//finalize処理
		}
		break;
	case Save:
		if (p_musicData != nullptr) {

		}
		break;
	case Export:
		if (p_musicData != nullptr) {
			File::Make_File_JsonIO jsIO;
			jsIO.saveNewJson(p_musicData.get());
		}
		break;
	case WholeQUARTER:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::QUARTER,true);
		}
		break;
	case WholeEIGHTH:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::EIGHTH,true);
		}
		break;
	case WholeSIXTEENTH:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::SIXTEENTH,true);
		}
		break;
	case WholeTHIRTYSECOND:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::THIRTYSECOND,true);
		}
		break;
	case WholeTRIPLET:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::TRIPLET,true);
		}
		break;
	case PartQUARTER:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_NoteManager::getInstance()->setBarIDForInitOneVector(Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize());
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::QUARTER, false);
		}
		break;
	case PartEIGHTH:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_NoteManager::getInstance()->setBarIDForInitOneVector(Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize());
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::EIGHTH, false);
		}
		break;
	case PartSIXTEENTH:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_NoteManager::getInstance()->setBarIDForInitOneVector(Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize());
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::SIXTEENTH, false);
		}
		break;
	case PartTHIRTYSECOND:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_NoteManager::getInstance()->setBarIDForInitOneVector(Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize());
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::THIRTYSECOND, false);
		}
		break;
	case PartTRIPLET:
		if (p_musicData != nullptr) {
			Singleton::Make_Singleton_NoteManager::getInstance()->setBarIDForInitOneVector(Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize());
			Singleton::Make_Singleton_BeatLineManager::getInstance()->setInitBarLineFunc(Global::TRIPLET, false);
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

