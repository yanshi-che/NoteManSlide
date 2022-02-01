#include "Game_Singleton_NoteManager.h"

Game::Singleton::Game_Singleton_NoteManager* Game::Singleton::Game_Singleton_NoteManager::p_instance = nullptr;

Game::Singleton::Game_Singleton_NoteManager::Game_Singleton_NoteManager() {
	startBarIDForLongNote = 0;
	startBeatIDForLongNote = 0;
	longNotesGroup = 1;
	p_yForLong = nullptr;
	longNoteErase = false;
	barIDForInitOneVector = 0;
}

Game::Singleton::Game_Singleton_NoteManager* Game::Singleton::Game_Singleton_NoteManager::getInstance() {
	if (p_instance == nullptr) {
		p_instance = new Game_Singleton_NoteManager();
	}
	return p_instance;
}

void Game::Singleton::Game_Singleton_NoteManager::destroyInstance() {
	delete p_instance;
}

void Game::Singleton::Game_Singleton_NoteManager::draw(const std::uint16_t& barID, const std::uint16_t& beatID) {
	if (normalNotes.size() != 0) {
		normalNotes[barID][beatID]->drawNote();
		longNotes[barID][beatID]->drawLongNote();
	}
}

void Game::Singleton::Game_Singleton_NoteManager::initVector(const std::uint16_t& barLength, std::uint8_t& quontize) {
	normalNotes.resize(barLength);
	longNotes.resize(barLength);
	for (int i = 0; i < barLength; ++i) {
		normalNotes[i].resize(quontize);
		longNotes[i].resize(quontize);
	}
}

void Game::Singleton::Game_Singleton_NoteManager::initOneVector(std::uint8_t& quontize) {
	normalNotes[barIDForInitOneVector].resize(quontize);
	longNotes[barIDForInitOneVector].resize(quontize);
}

void Game::Singleton::Game_Singleton_NoteManager::makeNoteInstance(const std::uint16_t& barID,const std::uint16_t& beatID,const std::int32_t& y,const std::uint8_t& amountOfLane,const double& time) {
	normalNotes[barID][beatID] = std::make_shared<Note::Game_Note_NormalNoteContainer>(barID,beatID,y,amountOfLane,time);
	longNotes[barID][beatID] = std::make_shared<Note::Game_Note_LongNoteContainer>(barID,beatID,y,amountOfLane,time);
}

void Game::Singleton::Game_Singleton_NoteManager::resetVector(bool isAll) {
	if (isAll) {
		for (int i = 0, iSize = static_cast<int>(normalNotes.size()); i < iSize; ++i) {
			for (int k = 0, kSize = static_cast<int>(normalNotes[i].size()); k < kSize; ++k) {
				normalNotes[i][k].reset();
				longNotes[i][k].reset();
			}
		}
	}
	else {
		for (int i = 1, iSize = static_cast<int>(normalNotes[barIDForInitOneVector].size()); i < iSize; ++i) {
			normalNotes[barIDForInitOneVector][i].reset();
			longNotes[barIDForInitOneVector][i].reset();
		}
	}
}

void Game::Singleton::Game_Singleton_NoteManager::removeLongNote(const std::uint16_t barID, const std::uint16_t beatID, std::uint8_t laneID) {
	if (longNotes[barID][beatID]->getLongNoteFlag(laneID).first) {
		std::uint8_t isFirstOrLastCount = 0;
		std::uint16_t isNotHaveNote = 0;
		std::uint16_t noteGroup = longNotes[barID][beatID]->getNoteGroup(laneID);
		for (int i = barID, iSize = static_cast<int>(longNotes.size()); i < iSize; ++i) {
			for (int k = 0, kSize = static_cast<int>(longNotes[i].size()); k < kSize; ++k) {
				if (longNotes[i][k]->getNoteGroup(laneID) == noteGroup && longNotes[i][k]->getLongNoteFlag(laneID).first) {
					if (longNotes[i][k]->getLongNoteFlag(laneID).second) {
						++isFirstOrLastCount;
					}
					longNotes[i][k]->setLongNoteFlag(laneID, true);
					longNotes[i][k]->setNoteHeight(laneID, 0);
					longNotes[i][k]->setNoteGroup(laneID, 0);
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
		for (int i = barID - 1; 0 <= i; --i) {
			for (int k = static_cast<int>(longNotes[i].size()) - 1; 0 <= k; --k) {
				if (longNotes[i][k]->getNoteGroup(laneID) == noteGroup && longNotes[i][k]->getLongNoteFlag(laneID).first) {
					longNotes[i][k]->setLongNoteFlag(laneID, true);
					longNotes[i][k]->setNoteHeight(laneID, 0);
					longNotes[i][k]->setNoteGroup(laneID, 0);
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
	}
}

void Game::Singleton::Game_Singleton_NoteManager::setBarIDForInitOneVector(std::uint16_t id) {
	barIDForInitOneVector = id;
}


void Game::Singleton::Game_Singleton_NoteManager::setNormalNote(const std::uint16_t& barID,const std::uint16_t& beatID, std::uint8_t laneID) {
	if (!longNotes[barID][beatID]->getLongNoteFlag(laneID).first) {
		normalNotes[barID][beatID]->setNormalNoteFlag(laneID);
	}
}

void Game::Singleton::Game_Singleton_NoteManager::setLongNote(const std::uint16_t barID,const std::uint16_t beatID, std::uint8_t laneID, std::int32_t* y,bool isFirst) {
	if (isFirst) {
		//既にロングノーツが設置されていた時に撤去する
		removeLongNote(barID, beatID, laneID);
		if (longNoteErase) {
			return;
		}
		//ロングノーツがセットされていないとき
		startBarIDForLongNote = barID;
		startBeatIDForLongNote = beatID;
		p_yForLong = y;
		longNotes[barID][beatID]->setLongNoteFlag(laneID, isFirst);
		longNotes[barID][beatID]->setNoteGroup(laneID, longNotesGroup);
	}
	else {
		//ロングノーツの削除処理をした場合は何もせずに戻る
		if (longNoteErase) {
			longNoteErase = false;
			return;
		}
		//TODO　一番上にある拍線からロングノーツを描画するという仕様上、それが画面外に出ると描画されなくなる
		//始点となる拍線の座標とマウスを離した座標の間に存在する拍線にロングノーツをセット
		std::stack<Note::Game_Note_NormalNoteContainer*> stackNormal;
		std::stack<Note::Game_Note_LongNoteContainer*> stackLong;
		std::uint16_t count = 0;
		if (0 < *p_yForLong - *y) { //拍線の順番に沿ってロングノーツを伸ばした時
			for (int i = startBarIDForLongNote, iSize = static_cast<int>(longNotes.size()); i < iSize; ++i) {//ロングノーツの検索
				for (int k = 0, kSize = static_cast<int>(longNotes[i].size()); k < kSize; ++k) {
					if (longNotes[i][k]->getY() < *p_yForLong && *y - Global::clickWidth < longNotes[i][k]->getY()) {
						stackNormal.push(normalNotes[i][k].get());
						stackLong.push(longNotes[i][k].get());
						++count;
					}
					else if (count != 0) {
						break;
					}
				}
			}
			if (stackLong.size() == 0) {//始点から他の拍線に伸ばさなかったとき
				longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setLongNoteFlag(laneID, true);
				longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNoteGroup(laneID, 0);
			}
			else {
				if (normalNotes[startBarIDForLongNote][startBeatIDForLongNote]->getNormalNoteFlag(laneID)) {//始点のノーマルノーツを消す
					normalNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNormalNoteFlag(laneID);
				}
				count = 0;
				while (stackLong.size() != 0) {//ロングノーツのセットとノーマルノーツの撤去
					if (!longNoteErase && stackLong.top()->getLongNoteFlag(laneID).first) {//別のロングノーツが範囲内に含まれていた時削除
						removeLongNote(stackLong.top()->getBarID(), stackLong.top()->getBeatID(), laneID);
					}
					if (count != 0) {
						stackLong.top()->setLongNoteFlag(laneID, false);
					}
					else {//終点の処理
						stackLong.top()->setLongNoteFlag(laneID, true);
						stackLong.top()->setNoteHeight(laneID, *p_yForLong - stackLong.top()->getY());
						++count;
					}
					if (stackNormal.top()->getNormalNoteFlag(laneID)) {
						stackNormal.top()->setNormalNoteFlag(laneID);
					}
					stackLong.top()->setNoteGroup(laneID, longNotesGroup);
					stackNormal.pop();
					stackLong.pop();
				}
			}
		}
		else {//拍線の順番と逆向きにロングノーツを伸ばした時
			for (int i = startBarIDForLongNote; 0 <= i; --i) {//ロングノーツの検索
				for (int k = static_cast<int>(longNotes[i].size()) -1; 0 <= k; --k) {
					if (*p_yForLong < longNotes[i][k]->getY() && longNotes[i][k]->getY() < *y + Global::clickWidth) {
						stackNormal.push(normalNotes[i][k].get());
						stackLong.push(longNotes[i][k].get());
						++count;
					}
					else if (count != 0) {
						break;
					}
				}
			}
			if (stackLong.size() == 0) {//始点から他の拍線に伸ばさなかったとき
				longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setLongNoteFlag(laneID, true);
				longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNoteGroup(laneID, 0);
			}
			else {
				if (normalNotes[startBarIDForLongNote][startBeatIDForLongNote]->getNormalNoteFlag(laneID)) {//始点のノーマルノーツを消す
					normalNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNormalNoteFlag(laneID);
				}
				count = 0;
				while (stackLong.size() != 0) {//ロングノーツのセットとノーマルノーツの撤去
					if (!longNoteErase && stackLong.top()->getLongNoteFlag(laneID).first) {//別のロングノーツが範囲内に含まれていた時削除
						removeLongNote(stackLong.top()->getBarID(), stackLong.top()->getBeatID(), laneID);
					}
					if (count != 0) {
						stackLong.top()->setLongNoteFlag(laneID, false);
					}
					else {//終点の処理
						stackLong.top()->setLongNoteFlag(laneID, true);
						longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNoteHeight(laneID, stackLong.top()->getY() - *p_yForLong);
						++count;
					}
					if (stackNormal.top()->getNormalNoteFlag(laneID)) {
						stackNormal.top()->setNormalNoteFlag(laneID);
					}
					stackLong.top()->setNoteGroup(laneID, longNotesGroup);
					stackNormal.pop();
					stackLong.pop();
				}
			}
		}
		longNoteErase = false;
		++longNotesGroup;
	}
}

const std::vector<std::vector<std::shared_ptr<Game::Note::Game_Note_NormalNoteContainer>>>& Game::Singleton::Game_Singleton_NoteManager::getNormalNoteVector() {
	return normalNotes;
}

const std::vector<std::vector<std::shared_ptr<Game::Note::Game_Note_LongNoteContainer>>>& Game::Singleton::Game_Singleton_NoteManager::getLongNoteVector() {
	return longNotes;
}