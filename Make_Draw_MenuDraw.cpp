#include "Make_Draw_MenuDraw.h"

std::shared_ptr<Make::File::Make_File_MusicData> Make::Draw::Make_Draw_MenuDraw::p_musicData = nullptr;
std::shared_ptr<Make::Play::Make_Play_MusicPlayer> Make::Draw::Make_Draw_MenuDraw::p_musicPlayer = nullptr;
std::shared_ptr<Make::Draw::Make_Draw_BeatLineManager> Make::Draw::Make_Draw_MenuDraw::p_beatLine = nullptr;

Make::Draw::Make_Draw_MenuDraw::Make_Draw_MenuDraw(std::shared_ptr<Draw::Make_Draw_BeatLineManager> p_beatLine){
	this->p_beatLine = p_beatLine;
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

void Make::Draw::Make_Draw_MenuDraw::setMusicDataFromNewFile(const std::shared_ptr<File::Make_File_MusicData> md) {
	p_musicData	= md;
	if (p_musicData!=nullptr) {
		p_beatLine->initialize(p_musicData);
	}
}

void Make::Draw::Make_Draw_MenuDraw::setMusicDataFromSaveFile(std::unique_ptr<File::Make_File_MusicData> md,const json::value val) {
	p_musicData = std::move(md);
	if (p_musicData != nullptr) {
		p_beatLine->initializeBySavaData(p_musicData,val);
	}
}

void Make::Draw::Make_Draw_MenuDraw::MenuItemSelectCallBack(const TCHAR* itemName, int itemID){
	switch(itemID) {
	case NewFile:
		if (p_musicData == nullptr) {
			File::Make_File_MusicFileIO mfIO;
			std::pair<std::unique_ptr<File::Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>> pair = mfIO.getMusicFile();;
			p_musicPlayer = std::move(pair.second);
			setMusicDataFromNewFile(std::move(pair.first));
		}
		else {
			File::Make_File_MusicFileIO mfIO;
			std::pair<std::unique_ptr<File::Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>> pair = mfIO.getMusicFile();
			if (pair.first != nullptr && pair.second!= nullptr) {
				p_musicData.reset();
				p_musicPlayer.reset();
				p_beatLine->finalize();
				p_musicPlayer = std::move(pair.second);
				setMusicDataFromNewFile(std::move(pair.first));
			}
		}
		break;
	case Open:
		if (p_musicData == nullptr) {
			File::Make_File_SaveFileIO sfIO;
			std::tuple<std::unique_ptr<File::Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>, json::value> tuple = sfIO.readSaveData();
			if (std::get<0>(tuple) != nullptr && std::get<1>(tuple) != nullptr && std::get<2>(tuple) != NULL) {
				p_musicPlayer = std::move(std::get<1>(tuple));
				setMusicDataFromSaveFile(std::move(std::get<0>(tuple)), std::get<2>(tuple));
			}
		}
		else {
			File::Make_File_SaveFileIO sfIO;
			std::tuple<std::unique_ptr<File::Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>, json::value> tuple = sfIO.readSaveData();
			if (std::get<0>(tuple) != nullptr && std::get<1>(tuple) != nullptr && std::get<2>(tuple) != NULL) {
				p_musicData.reset();
				p_musicPlayer.reset();
				p_beatLine->finalize();
				p_musicPlayer = std::move(std::get<1>(tuple));
				setMusicDataFromSaveFile(std::move(std::get<0>(tuple)), std::get<2>(tuple));
			}
		}
		break;
	case Save:
		if (p_musicData != nullptr) {
			File::Make_File_SaveFileIO saIO;
			saIO.writeSaveData(p_musicData,p_beatLine);
		}
		break;
	case Export:
		if (p_musicData != nullptr) {
			File::Make_File_JsonIO jsIO;
			jsIO.saveNewJson(p_musicData,p_beatLine->getNoteManager());
		}
		break;
	case WholeQUARTER:
		if (p_musicData != nullptr) {
			p_beatLine->setInitBarLineFunc(Global::QUARTER,NULL,true);
		}
		break;
	case WholeEIGHTH:
		if (p_musicData != nullptr) {
			p_beatLine->setInitBarLineFunc(Global::EIGHTH,NULL,true);
		}
		break;
	case WholeSIXTEENTH:
		if (p_musicData != nullptr) {
			p_beatLine->setInitBarLineFunc(Global::SIXTEENTH,NULL,true);
		}
		break;
	case WholeTHIRTYSECOND:
		if (p_musicData != nullptr) {
			p_beatLine->setInitBarLineFunc(Global::THIRTYSECOND,NULL,true);
		}
		break;
	case WholeTRIPLET:
		if (p_musicData != nullptr) {
			p_beatLine->setInitBarLineFunc(Global::TRIPLET,NULL,true);
		}
		break;
	case PartQUARTER:
		if (p_musicData != nullptr) {
			p_beatLine->setInitBarLineFunc(Global::QUARTER, Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize(), false);
		}
		break;
	case PartEIGHTH:
		if (p_musicData != nullptr) {
			p_beatLine->setInitBarLineFunc(Global::EIGHTH, Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize(), false);
		}
		break;
	case PartSIXTEENTH:
		if (p_musicData != nullptr) {
			p_beatLine->setInitBarLineFunc(Global::SIXTEENTH, Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize(), false);
		}
		break;
	case PartTHIRTYSECOND:
		if (p_musicData != nullptr) {
			p_beatLine->setInitBarLineFunc(Global::THIRTYSECOND, Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize(), false);
		}
		break;
	case PartTRIPLET:
		if (p_musicData != nullptr) {
			p_beatLine->setInitBarLineFunc(Global::TRIPLET, Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize(), false);
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

