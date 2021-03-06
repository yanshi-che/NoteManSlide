#include "Make_Draw_MenuDraw.h"

std::shared_ptr<SceneChanger> Make::Draw::Make_Draw_MenuDraw::sceneChanger = nullptr;
std::shared_ptr<Make::File::Make_File_MusicData> Make::Draw::Make_Draw_MenuDraw::p_musicData = nullptr;
std::shared_ptr<Make::Play::Make_Play_MusicPlayer> Make::Draw::Make_Draw_MenuDraw::p_musicPlayer = nullptr;
std::shared_ptr<Make::Draw::Make_Draw_BeatLineManager> Make::Draw::Make_Draw_MenuDraw::p_beatLine = nullptr;
std::shared_ptr<Make::Play::Make_Play_TestPlayManager> Make::Draw::Make_Draw_MenuDraw::p_testPlay = nullptr;
std::function<void()> Make::Draw::Make_Draw_MenuDraw::drawFunc = nullptr;
std::function<void()> Make::Draw::Make_Draw_MenuDraw::updateFunc = nullptr;
bool Make::Draw::Make_Draw_MenuDraw::isPlaying = false;
bool Make::Draw::Make_Draw_MenuDraw::playFinalize = false;
bool Make::Draw::Make_Draw_MenuDraw::isFileOpen = false;
bool Make::Draw::Make_Draw_MenuDraw::existUpdateFunc = false;
const std::filesystem::path Make::Draw::Make_Draw_MenuDraw::firstPath = std::filesystem::current_path();

Make::Draw::Make_Draw_MenuDraw::Make_Draw_MenuDraw(std::shared_ptr<SceneChanger>& sceneChanger){
	this->sceneChanger = sceneChanger;
	p_beatLine = std::make_shared<Draw::Make_Draw_BeatLineManager>();
	drawFunc = p_beatLine->getDrawFunc();
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "ファイル(&F)", File);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "新規作成(&Ctrl+N)", NewFile);
	AddKeyAccel_ID(NewFile,KEY_INPUT_N,1,0,0);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "開く(&Ctrl+O)", Open);
	AddKeyAccel_ID(Open, KEY_INPUT_O, 1, 0, 0);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "保存(&Ctrl+S)", Save);
	AddKeyAccel_ID(Save, KEY_INPUT_S, 1, 0, 0);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "エクスポート(&Ctrl+Shift+E)", Export);
	AddKeyAccel_ID(Export, KEY_INPUT_E, 1, 0, 1);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, TRUE, NULL, 0);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, File, FALSE, "終了(&Ctrl+Shift+X)", Exit);
	AddKeyAccel_ID(Exit, KEY_INPUT_X, 1, 0,1);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, MENUITEM_IDTOP, FALSE, "テスト(&T)", Test);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, Test, FALSE, "テストプレイ開始(&Ctrl+P)", Play);
	AddKeyAccel_ID(Play, KEY_INPUT_P, 1, 0, 0);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, Test, FALSE, "テストプレイ終了(&Ctrl+E)", Stop);
	AddKeyAccel_ID(Stop, KEY_INPUT_E, 1, 0, 0);
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
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, NoteType, FALSE, "通常(&Ctrl+F1)", Normal);
	AddKeyAccel_ID(Normal, KEY_INPUT_F1, 1, 0, 0);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, NoteType, FALSE, "ロング(&Ctrl+F2)", Long);
	AddKeyAccel_ID(Long, KEY_INPUT_F2, 1, 0, 0);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, NoteType, FALSE, "スライドR(&Ctrl+F3)", SlideR);
	AddKeyAccel_ID(SlideR, KEY_INPUT_F3, 1, 0, 0);
	AddMenuItem(MENUITEM_ADD_CHILD, NULL, NoteType, FALSE, "スライドL(&Ctrl+F4)", SlideL);
	AddKeyAccel_ID(SlideL, KEY_INPUT_F4, 1, 0, 0);
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
		if (p_musicData == nullptr && !isPlaying && !isFileOpen) {
			isFileOpen = true;
			File::Make_File_MusicFileIO mfIO;
			std::pair<std::unique_ptr<File::Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>> pair = mfIO.getMusicFile();;
			p_musicPlayer = std::move(pair.second);
			setMusicDataFromNewFile(std::move(pair.first));
			isFileOpen = false;
		}
		else if(!isPlaying && !isFileOpen){
			isFileOpen = true;
			File::Make_File_MusicFileIO mfIO;
			std::pair<std::unique_ptr<File::Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>> pair = mfIO.getMusicFile();
			if (pair.first != nullptr && pair.second!= nullptr) {
				p_musicData.reset();
				p_musicPlayer.reset();
				p_beatLine->finalize();
				p_musicPlayer = std::move(pair.second);
				setMusicDataFromNewFile(std::move(pair.first));
			}
			isFileOpen = false;
		}
		break;
	case Open:
		if (p_musicData == nullptr && !isPlaying && !isFileOpen) {
			isFileOpen = true;
			File::Make_File_SaveFileIO sfIO;
			std::tuple<std::unique_ptr<File::Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>, json::value> tuple = sfIO.readSaveData();
			if (std::get<0>(tuple) != nullptr && std::get<1>(tuple) != nullptr && std::get<2>(tuple) != NULL) {
				p_musicPlayer = std::move(std::get<1>(tuple));
				setMusicDataFromSaveFile(std::move(std::get<0>(tuple)), std::get<2>(tuple));
			}
			isFileOpen = false;
		}
		else if(!isPlaying && !isFileOpen){
			isFileOpen = true;
			File::Make_File_SaveFileIO sfIO;
			std::tuple<std::unique_ptr<File::Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>, json::value> tuple = sfIO.readSaveData();
			if (std::get<0>(tuple) != nullptr && std::get<1>(tuple) != nullptr && std::get<2>(tuple) != NULL) {
				p_musicData.reset();
				p_musicPlayer.reset();
				p_beatLine->finalize();
				p_musicPlayer = std::move(std::get<1>(tuple));
				setMusicDataFromSaveFile(std::move(std::get<0>(tuple)), std::get<2>(tuple));
			}
			isFileOpen = false;
		}
		break;
	case Save:
		if (p_musicData != nullptr && !isPlaying) {
			File::Make_File_SaveFileIO saIO;
			saIO.writeSaveData(p_musicData,p_beatLine);
		}
		break;
	case Export:
		if (p_musicData != nullptr && !isPlaying) {
			File::Make_File_JsonIO jsIO;
			jsIO.saveNewJson(p_musicData,p_beatLine->getNoteManager());
		}
		break;
	case Exit:
		sceneChanger->changeScene(Scene::Home);
		break;
	case Play:
		if (p_musicData != nullptr && !isPlaying){
			std::filesystem::current_path(firstPath);
			File::Make_File_JsonIO jsIO;
			json::value val;
			jsIO.getJsonVal(p_musicData, p_beatLine->getNoteManager(),val);
			p_testPlay = std::make_shared<Play::Make_Play_TestPlayManager>();
			p_testPlay->initialize(val,p_musicPlayer,p_musicData);
			drawFunc = p_testPlay->getDrawFunc();
			updateFunc = p_testPlay->getUpdateFunc();
			isPlaying = true;
			existUpdateFunc = true;
		}
		break;
	case Stop:
		if (p_musicData != nullptr && isPlaying) {
			drawFunc = p_beatLine->getDrawFunc();
			isPlaying = false;
			playFinalize = true;
			existUpdateFunc = true;
		}
		break;
	case WholeQUARTER:
		if (p_musicData != nullptr && !isPlaying) {
			p_beatLine->setInitBarLineFunc(Global::QUARTER,NULL,true);
		}
		break;
	case WholeEIGHTH:
		if (p_musicData != nullptr && !isPlaying) {
			p_beatLine->setInitBarLineFunc(Global::EIGHTH,NULL,true);
		}
		break;
	case WholeSIXTEENTH:
		if (p_musicData != nullptr && !isPlaying) {
			p_beatLine->setInitBarLineFunc(Global::SIXTEENTH,NULL,true);
		}
		break;
	case WholeTHIRTYSECOND:
		if (p_musicData != nullptr && !isPlaying) {
			p_beatLine->setInitBarLineFunc(Global::THIRTYSECOND,NULL,true);
		}
		break;
	case WholeTRIPLET:
		if (p_musicData != nullptr && !isPlaying) {
			p_beatLine->setInitBarLineFunc(Global::TRIPLET,NULL,true);
		}
		break;
	case PartQUARTER:
		if (p_musicData != nullptr && !isPlaying) {
			p_beatLine->setInitBarLineFunc(Global::QUARTER, Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize(), false);
		}
		break;
	case PartEIGHTH:
		if (p_musicData != nullptr && !isPlaying) {
			p_beatLine->setInitBarLineFunc(Global::EIGHTH, Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize(), false);
		}
		break;
	case PartSIXTEENTH:
		if (p_musicData != nullptr && !isPlaying) {
			p_beatLine->setInitBarLineFunc(Global::SIXTEENTH, Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize(), false);
		}
		break;
	case PartTHIRTYSECOND:
		if (p_musicData != nullptr && !isPlaying) {
			p_beatLine->setInitBarLineFunc(Global::THIRTYSECOND, Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize(), false);
		}
		break;
	case PartTRIPLET:
		if (p_musicData != nullptr && !isPlaying) {
			p_beatLine->setInitBarLineFunc(Global::TRIPLET, Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize(), false);
		}
		break;
	case Normal:
		Make_Draw_LineContainer::setNoteType(Global::NOTETYPE_NORMAL);
		break;
	case Long:
		Make_Draw_LineContainer::setNoteType(Global::NOTETYPE_LONG);
		break;
	case SlideR:
		Make_Draw_LineContainer::setNoteType(Global::NOTETYPE_SLIDER);
		break;
	case SlideL:
		Make_Draw_LineContainer::setNoteType(Global::NOTETYPE_SLIDEL);
		break;
	}

}

void Make::Draw::Make_Draw_MenuDraw::finalize() {
	p_beatLine->finalize();
	p_beatLine.reset();
	if (p_testPlay != nullptr) {
		p_testPlay->finalize();
		p_testPlay.reset();
	}
	p_musicData.reset();
	p_musicPlayer.reset();
	ClearKeyAccel();
	DeleteMenuItemAll();
	std::filesystem::current_path(firstPath);
}

void Make::Draw::Make_Draw_MenuDraw::resetDrawFunc() {
	drawFunc = nullptr;
	if (playFinalize) {
		p_testPlay->finalize();
		p_testPlay.reset();
		playFinalize = false;
	}
}

void Make::Draw::Make_Draw_MenuDraw::resetUpdateFunc() {
	updateFunc = nullptr;
	existUpdateFunc = false;
	if (playFinalize) {
		p_testPlay->finalize();
		p_testPlay.reset();
		playFinalize = false;
	}
}

bool Make::Draw::Make_Draw_MenuDraw::checkUpdateFunc() {
	return existUpdateFunc;
}

std::function<void()> Make::Draw::Make_Draw_MenuDraw::getDrawFunc() {
	return drawFunc;
}

std::function<void()> Make::Draw::Make_Draw_MenuDraw::getUpdateFunc() {
	return updateFunc;
}