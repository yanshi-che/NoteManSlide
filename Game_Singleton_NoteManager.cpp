#include "Game_Singleton_NoteManager.h"

Game::Singleton::Game_Singleton_NoteManager* Game::Singleton::Game_Singleton_NoteManager::instance = nullptr;

Game::Singleton::Game_Singleton_NoteManager::Game_Singleton_NoteManager() {
	startBarIDForLongNote = 0;
	startBeatIDForLongNote = 0;
	longNotesGroup = 1;
	yForLong = nullptr;
	longNoteErase = false;
}

Game::Singleton::Game_Singleton_NoteManager* Game::Singleton::Game_Singleton_NoteManager::getInstance() {
	if (instance == nullptr) {
		instance = new Game_Singleton_NoteManager();
	}
	return instance;
}

void Game::Singleton::Game_Singleton_NoteManager::destroyInstance() {
	delete instance;
}

void Game::Singleton::Game_Singleton_NoteManager::resizeVector(const std::uint16_t* barLength, std::uint8_t& quontize) {
	normalNotes.resize(*barLength);
	longNotes.resize(*barLength);
	for (int i = 0; i < *barLength; i++) {
		normalNotes[i].resize(quontize);
		longNotes[i].resize(quontize);
	}
}

void Game::Singleton::Game_Singleton_NoteManager::makeNoteInstance(const std::uint16_t& barID,const std::uint16_t& beatID, std::int32_t* y,const  std::uint8_t* numberOfRane) {
	normalNotes[barID][beatID] = std::make_unique<Note::Game_Note_NormalNoteContainer>(y,numberOfRane);
	longNotes[barID][beatID] = std::make_unique<Note::Game_Note_LongNoteContainer>(y,numberOfRane);
}

void Game::Singleton::Game_Singleton_NoteManager::setNormalNote(const std::uint16_t& barID,const std::uint16_t& beatID, std::uint8_t raneID) {
	if (!longNotes[barID][beatID]->getLongNoteFlag(raneID).first) {
		normalNotes[barID][beatID]->setNormalNoteFlag(raneID);
	}
}

void Game::Singleton::Game_Singleton_NoteManager::setLongNote(const std::uint16_t barID,const std::uint16_t beatID, std::uint8_t raneID, std::int32_t* y,bool isFirst) {
	if (isFirst) {
		//既にロングノーツが設置されていた時に撤去する
		if (longNotes[barID][beatID]->getLongNoteFlag(raneID).first) {
			std::uint8_t isFirstOrLastCount = 0;
			std::uint16_t isNotHaveNote = 0;
			std::uint16_t noteGroup = longNotes[barID][beatID]->getNoteGroup(raneID);
			for (int i = barID, isize = longNotes.size(); i < isize; ++i) {
				for (int k = 0, ksize = longNotes[i].size(); k < ksize; ++k) {
					if (longNotes[i][k]->getNoteGroup(raneID)==noteGroup&&longNotes[i][k]->getLongNoteFlag(raneID).first) {
						if (longNotes[i][k]->getLongNoteFlag(raneID).second) {
							++isFirstOrLastCount;
						}
						longNotes[i][k]->setLongNoteFlag(raneID, true);
						longNotes[i][k]->setNoteHeight(raneID, 0);
						longNotes[i][k]->setNoteGroup(raneID, 0);
					}
					else {
						++isNotHaveNote;
					}
				}
				if (isNotHaveNote == longNotes[i].size()) {
					break;
				}
				isNotHaveNote = 0;
			}
			//この時点で始点終点に当たったら戻る
			if (isFirstOrLastCount == 2) {
				longNoteErase = true;
				return;
			}
			isNotHaveNote = 0;
			for (int i = barID -1; 0<= i; --i) {
				for (int k = longNotes[i].size() - 1; 0<=k ; --k) {
					if (longNotes[i][k]->getNoteGroup(raneID) == noteGroup && longNotes[i][k]->getLongNoteFlag(raneID).first) {
						longNotes[i][k]->setLongNoteFlag(raneID, true);
						longNotes[i][k]->setNoteHeight(raneID, 0);
						longNotes[i][k]->setNoteGroup(raneID, 0);
					}
					else {
						++isNotHaveNote;
					}
				}
				if (isNotHaveNote == longNotes[i].size()) {
					break;
				}
				isNotHaveNote = 0;
			}
			longNoteErase = true;
			return;
		}
		//ロングノーツがセットされていないとき
		startBarIDForLongNote = barID;
		startBeatIDForLongNote = beatID;
		yForLong = y;
		longNotes[barID][beatID]->setLongNoteFlag(raneID, isFirst);
		longNotes[barID][beatID]->setNoteGroup(raneID, longNotesGroup);
	}
	else {
		//ロングノーツの削除処理をした場合は何もせずに戻る
		if (longNoteErase) {
			longNoteErase = false;
			return;
		}
		//始点となる拍線の座標とマウスを離した座標の間に存在する拍線にロングノーツをセット
		Note::Game_Note_LongNoteContainer* last = nullptr;
		std::uint16_t count = 0;
		if (0 < *yForLong - *y) { //拍線の順番に沿ってロングノーツを伸ばした時
			for (int i = startBarIDForLongNote, isize = longNotes.size(); i < isize; ++i) {
				for (int k = 0, ksize = longNotes[i].size(); k < ksize; ++k) {
					if (longNotes[i][k]->getY() < *yForLong && *y - Global::clickWidth < longNotes[i][k]->getY()) {
						if (normalNotes[i][k]->getNormalNoteFlag(raneID)) {
							normalNotes[i][k]->setNormalNoteFlag(raneID);
						}
						longNotes[i][k]->setLongNoteFlag(raneID, false);
						longNotes[i][k]->setNoteGroup(raneID,longNotesGroup);
						last = longNotes[i][k].get();
						++count;
					}
					else if (count != 0) {
						break;
					}
				}
			}
			if (last == nullptr) {//始点から他の拍線に伸ばさなかったとき
				longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setLongNoteFlag(raneID, true);
				longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNoteGroup(raneID, 0);
			}
			else {
				if (normalNotes[startBarIDForLongNote][startBeatIDForLongNote]->getNormalNoteFlag(raneID)) {
					normalNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNormalNoteFlag(raneID);
				}
				last->setNoteHeight(raneID,*yForLong - last->getY());
				last->setLongNoteFlagFirstOrLast(raneID,true);//最後のノーツを終点に設定する
				++longNotesGroup;
			}
		}
		else {//拍線の順番と逆向きにロングノーツを伸ばした時
			for (int i = startBarIDForLongNote; 0 <= i; --i) {
				for (int k = longNotes[i].size() -1; 0 <= k; --k) {
					if (*yForLong < longNotes[i][k]->getY() && longNotes[i][k]->getY() < *y + Global::clickWidth) {
						if (normalNotes[i][k]->getNormalNoteFlag(raneID)) {
							normalNotes[i][k]->setNormalNoteFlag(raneID);
						}
						longNotes[i][k]->setLongNoteFlag(raneID, false);
						longNotes[i][k]->setNoteGroup(raneID, longNotesGroup);
						last = longNotes[i][k].get();
						++count;
					}
					else if (count != 0) {
						break;
					}
				}
			}
			if (last == nullptr) {//始点から他の拍線に伸ばさなかったとき
				longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setLongNoteFlag(raneID, true);
				longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNoteGroup(raneID, 0);
			}
			else {
				if (normalNotes[startBarIDForLongNote][startBeatIDForLongNote]->getNormalNoteFlag(raneID)) {
					normalNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNormalNoteFlag(raneID);
				}
				longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNoteHeight(raneID,last->getY() - *yForLong);
				last->setLongNoteFlagFirstOrLast(raneID,true);//最後のノーツを終点に設定する
				++longNotesGroup;
			}
		}
	}
}