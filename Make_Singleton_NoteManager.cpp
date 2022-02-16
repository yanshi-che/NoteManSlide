#include "Make_Singleton_NoteManager.h"

Make::Singleton::Make_Singleton_NoteManager* Make::Singleton::Make_Singleton_NoteManager::p_instance = nullptr;

Make::Singleton::Make_Singleton_NoteManager::Make_Singleton_NoteManager(){
	startBarID = 0;
	startBeatID = 0;
	startLaneID = 0;
	longNoteGroup = 1;
	p_yBefore = nullptr;
	noteErase = false;
	mouseYBefore = 0;
}

Make::Singleton::Make_Singleton_NoteManager* Make::Singleton::Make_Singleton_NoteManager::getInstance() {
	if (p_instance == nullptr) {
		p_instance = new Make_Singleton_NoteManager();
	}
	return p_instance;
}

void Make::Singleton::Make_Singleton_NoteManager::destroyInstance(){
	if (p_instance != nullptr) {
		delete p_instance;
		p_instance = nullptr;
	}
}

void Make::Singleton::Make_Singleton_NoteManager::draw(std::uint16_t barID,std::uint8_t beatID) {
	if (normalNote.size() != 0) {
		slideNote.at(barID).at(beatID)->drawSlideNote();
		normalNote.at(barID).at(beatID)->drawNote();
		longNote.at(barID).at(beatID)->drawLongNote();
	}
}

void Make::Singleton::Make_Singleton_NoteManager::initVector(std::uint16_t barLength, std::uint8_t quontize) {
	normalNote.resize(barLength);
	longNote.resize(barLength);
	slideNote.resize(barLength);
	for (int i = 0; i < barLength; ++i) {
		normalNote.at(i).resize(quontize);
		longNote.at(i).resize(quontize);
		slideNote.at(i).resize(quontize);
	}
}

void Make::Singleton::Make_Singleton_NoteManager::initOneVector(std::uint8_t quontize, std::uint16_t barID) {
	normalNote.at(barID).resize(quontize);
	longNote.at(barID).resize(quontize);
	slideNote.at(barID).resize(quontize);
}

void Make::Singleton::Make_Singleton_NoteManager::makeNoteInstance(std::uint16_t barID,std::uint8_t beatID,const float& y,std::uint8_t amountOfLane,float time) {
	normalNote.at(barID).at(beatID) = std::make_shared<Note::Make_Note_NormalNoteContainer>(barID,beatID,y,amountOfLane,time);
	longNote.at(barID).at(beatID) = std::make_shared<Note::Make_Note_LongNoteContainer>(barID,beatID,y,amountOfLane,time);
	slideNote.at(barID).at(beatID) = std::make_shared<Note::Make_Note_SlideNoteContainer>(barID, beatID, y, amountOfLane, time);
}

void Make::Singleton::Make_Singleton_NoteManager::resetVector(bool isAll, std::uint16_t barID){
	if (isAll) {
		for (int i = 0,iSize = static_cast<int>(normalNote.size()); i < iSize; ++i) {
			for (int k = 0,kSize = static_cast<int>(normalNote.at(i).size()); k < kSize; ++k) {
				normalNote.at(i).at(k).reset();
				longNote.at(i).at(k).reset();
				slideNote.at(i).at(k).reset();
			}
		}
	}
	else {
		for (int i = 1,iSize = static_cast<int>(normalNote.at(barID).size()); i < iSize; ++i) {
			normalNote.at(barID).at(i).reset();
			longNote.at(barID).at(i).reset();
			slideNote.at(barID).at(i).reset();
		}
	}
}

void Make::Singleton::Make_Singleton_NoteManager::removeLongNote(std::uint16_t barID,std::uint8_t beatID, std::uint8_t laneID) {
	if (longNote.at(barID).at(beatID)->getLongNoteFlag(laneID).first) {
		std::uint8_t isFirstOrLastCount = 0;
		std::uint16_t isNotHaveNote = 0;
		const std::uint16_t noteGroup = longNote.at(barID).at(beatID)->getNoteGroup(laneID);
		for (int i = barID,iSize = static_cast<int>(longNote.size()); i < iSize; ++i) {
			for (int k = 0,kSize = static_cast<int>(longNote.at(i).size()); k < kSize; ++k) {
				if (longNote.at(i).at(k)->getNoteGroup(laneID) == noteGroup && longNote.at(i).at(k)->getLongNoteFlag(laneID).first) {
					if (longNote.at(i).at(k)->getLongNoteFlag(laneID).second) {
						++isFirstOrLastCount;
					}
					longNote.at(i).at(k)->setLongNoteFlag(laneID, true);
					longNote.at(i).at(k)->setNoteHeight(laneID, 0,true);
					longNote.at(i).at(k)->setNoteHeight(laneID, 0, false);
					longNote.at(i).at(k)->setNoteGroup(laneID, 0);
				}
				else {
					++isNotHaveNote;
				}
			}
			if (isNotHaveNote == longNote.at(i).size()) {
				break;
			}
			isNotHaveNote = 0;
		}
		//この時点で始点終点に当たったら戻る
		if (isFirstOrLastCount == 2) {
			noteErase = true;
			return;
		}
		isNotHaveNote = 0;
		for (int i = barID - 1; 0 <= i; --i) {
			for (int k = static_cast<int>(longNote.at(i).size()) - 1; 0 <= k; --k) {
				if (longNote.at(i).at(k)->getNoteGroup(laneID) == noteGroup && longNote.at(i).at(k)->getLongNoteFlag(laneID).first) {
					longNote.at(i).at(k)->setLongNoteFlag(laneID, true);
					longNote.at(i).at(k)->setNoteHeight(laneID, 0,true);
					longNote.at(i).at(k)->setNoteHeight(laneID, 0, false);
					longNote.at(i).at(k)->setNoteGroup(laneID, 0);
				}
				else {
					++isNotHaveNote;
				}
			}
			if (isNotHaveNote == longNote.at(i).size()) {
				break;
			}
			isNotHaveNote = 0;
		}
		noteErase = true;
	}
}

void Make::Singleton::Make_Singleton_NoteManager::setNormalNote(std::uint16_t barID,std::uint8_t beatID, std::uint8_t laneID) {
	if (!longNote.at(barID).at(beatID)->getLongNoteFlag(laneID).first) {
		normalNote.at(barID).at(beatID)->setNormalNoteFlag(laneID);
	}
}

void Make::Singleton::Make_Singleton_NoteManager::setLongNote(std::uint16_t barID,std::uint8_t beatID, std::uint8_t laneID, float* y,bool isFirst) {
	if (isFirst) {
		//既にロングノーツが設置されていた時に撤去する
		removeLongNote(barID, beatID, laneID);
		if (noteErase) {
			return;
		}
		//ロングノーツがセットされていないとき
		startBarID = barID;
		startBeatID = beatID;
		p_yBefore = y;
		longNote.at(barID).at(beatID)->setLongNoteFlag(laneID, isFirst);
		longNote.at(barID).at(beatID)->setNoteGroup(laneID, longNoteGroup);
	}
	else {
		//ロングノーツの削除処理をした場合は何もせずに戻る
		if (noteErase) {
			noteErase = false;
			return;
		}
		//始点となる拍線の座標とマウスを離した座標の間に存在する拍線にロングノーツをセット
		std::stack<Note::Make_Note_NormalNoteContainer*> stackNormal;
		std::stack<Note::Make_Note_LongNoteContainer*> stackLong;
		std::uint8_t count = 0;
		bool isFirstNote = true;

		if (0 < *p_yBefore - *y) { //拍線の順番に沿ってロングノーツを伸ばした時
			for (int i = startBarID,iSize = static_cast<int>(longNote.size()); i < iSize; ++i) {//範囲内の拍線の検索
				for (int k = 0,kSize = static_cast<int>(longNote.at(i).size()); k < kSize; ++k) {
					if (longNote.at(i).at(k)->getY() < *p_yBefore && *y - Global::clickWidth < longNote.at(i).at(k)->getY()) {
						stackNormal.push(normalNote.at(i).at(k).get());
						stackLong.push(longNote.at(i).at(k).get());
						++count;
						isFirstNote = false;
					}
				}
				if (count == 0 && !isFirstNote) {
					break;
				}
				count = 0;
			}

			if (stackLong.size() == 0) {//始点から他の拍線に伸ばさなかったとき
				longNote.at(startBarID).at(startBeatID)->setLongNoteFlag(laneID, true);
				longNote.at(startBarID).at(startBeatID)->setNoteGroup(laneID, 0);
			}
			else {
				if (normalNote.at(startBarID).at(startBeatID)->getNormalNoteFlag(laneID)) {//始点のノーマルノーツを消す
					normalNote.at(startBarID).at(startBeatID)->setNormalNoteFlag(laneID);
				}
				isFirstNote = true;
				while (stackLong.size() != 0) {//ロングノーツのセットとノーマルノーツの撤去
					if (!noteErase && stackLong.top()->getLongNoteFlag(laneID).first) {//別のロングノーツが範囲内に含まれていた時削除
						removeLongNote(stackLong.top()->getBarID(), stackLong.top()->getBeatID(), laneID);
					}
					if (!isFirstNote) {
						stackLong.top()->setLongNoteFlag(laneID, false);
					}
					else {//終点の処理
						stackLong.top()->setLongNoteFlag(laneID, true);
						longNote.at(startBarID).at(startBeatID)->setNoteHeight(laneID, *p_yBefore - stackLong.top()->getY(),true);
						stackLong.top()->setNoteHeight(laneID, *p_yBefore - stackLong.top()->getY(),false);
						isFirstNote = false;
					}
					if (stackNormal.top()->getNormalNoteFlag(laneID)) {
						stackNormal.top()->setNormalNoteFlag(laneID);
					}
					stackLong.top()->setNoteGroup(laneID, longNoteGroup);
					stackNormal.pop();
					stackLong.pop();
				}
			}
		}
		else {//拍線の順番と逆向きにロングノーツを伸ばした時
			for (int i = startBarID; 0 <= i; --i) {//範囲内の拍線の検索
				for (int k = static_cast<int>(longNote.at(i).size()) -1; 0 <= k; --k) {
					if (*p_yBefore < longNote.at(i).at(k)->getY() && longNote.at(i).at(k)->getY() < *y + Global::clickWidth) {
						stackNormal.push(normalNote.at(i).at(k).get());
						stackLong.push(longNote.at(i).at(k).get());
						++count;
						isFirstNote = false;
					}
				}
				if (count == 0 && !isFirstNote) {
					break;
				}
				count = 0;
			}
			if (stackLong.size() == 0) {//始点から他の拍線に伸ばさなかったとき
				longNote.at(startBarID).at(startBeatID)->setLongNoteFlag(laneID, true);
				longNote.at(startBarID).at(startBeatID)->setNoteGroup(laneID, 0);
			}
			else {
				if (normalNote.at(startBarID).at(startBeatID)->getNormalNoteFlag(laneID)) {//始点のノーマルノーツを消す
					normalNote.at(startBarID).at(startBeatID)->setNormalNoteFlag(laneID);
				}
				isFirstNote = true;
				while (stackLong.size() != 0) {//ロングノーツのセットとノーマルノーツの撤去
					if (!noteErase && stackLong.top()->getLongNoteFlag(laneID).first) {//別のロングノーツが範囲内に含まれていた時削除
						removeLongNote(stackLong.top()->getBarID(), stackLong.top()->getBeatID(), laneID);
					}
					if (!isFirstNote) {
						stackLong.top()->setLongNoteFlag(laneID, false);
					}
					else {//終点の処理
						stackLong.top()->setLongNoteFlag(laneID, true);
						longNote.at(startBarID).at(startBeatID)->setNoteHeight(laneID,stackLong.top()->getY() - *p_yBefore,false);
						stackLong.top()->setNoteHeight(laneID, stackLong.top()->getY() - *p_yBefore,true);
						isFirstNote = false;
					}
					if (stackNormal.top()->getNormalNoteFlag(laneID)) {
						stackNormal.top()->setNormalNoteFlag(laneID);
					}
					stackLong.top()->setNoteGroup(laneID, longNoteGroup);
					stackNormal.pop();
					stackLong.pop();
				}
			}
		}
		noteErase = false;
		++longNoteGroup;
	}
}

void Make::Singleton::Make_Singleton_NoteManager::setLongNoteGroupe(std::uint16_t longNoteGroup) {
	this->longNoteGroup = longNoteGroup;
}

void Make::Singleton::Make_Singleton_NoteManager::setSlideNote(std::uint16_t barID, std::uint8_t beatID, std::uint8_t laneID,float mouseY, bool isFirst) {
	if (isFirst) {
		if (slideNote.at(barID).at(beatID)->getSlideNoteFlag().first &&
			slideNote.at(barID).at(beatID)->getNoteStartAndEnd().first.second <= laneID &&
			laneID <= slideNote.at(barID).at(beatID)->getNoteStartAndEnd().first.first) {
			slideNote.at(barID).at(beatID)->setSlideNoteFlag(NULL,NULL,true);
			noteErase = true;
			return;
		}
		else if(slideNote.at(barID).at(beatID)->getSlideNoteFlag().second &&
			slideNote.at(barID).at(beatID)->getNoteStartAndEnd().second.first <= laneID &&
			laneID <= slideNote.at(barID).at(beatID)->getNoteStartAndEnd().second.second){
			slideNote.at(barID).at(beatID)->setSlideNoteFlag(NULL, NULL, false);
			noteErase = true;
			return;
		}
		startBarID = barID;
		startBeatID = beatID;
		startLaneID = laneID;
		mouseYBefore = mouseY;
	}
	else {
		if (noteErase) {
			noteErase = false;
			return;
		}
		if (0 < mouseYBefore - mouseY) {
			if (slideNote.at(startBarID).at(startBeatID)->getSlideNoteFlag().first) {
				slideNote.at(startBarID).at(startBeatID)->setSlideNoteFlag(NULL, NULL, true);
			}
			slideNote.at(startBarID).at(startBeatID)->setSlideNoteFlag(startLaneID, laneID, true);
		}
		else if(mouseYBefore - mouseY < 0){
			if (slideNote.at(startBarID).at(startBeatID)->getSlideNoteFlag().second) {
				slideNote.at(startBarID).at(startBeatID)->setSlideNoteFlag(NULL, NULL, false);
			}
			slideNote.at(startBarID).at(startBeatID)->setSlideNoteFlag(startLaneID, laneID, false);
		}
	}
}

const std::vector<std::vector<std::shared_ptr<Make::Note::Make_Note_NormalNoteContainer>>>& Make::Singleton::Make_Singleton_NoteManager::getNormalNoteVector() {
	return normalNote;
}

const std::vector<std::vector<std::shared_ptr<Make::Note::Make_Note_LongNoteContainer>>>& Make::Singleton::Make_Singleton_NoteManager::getLongNoteVector() {
	return longNote;
}

const std::vector<std::vector<std::shared_ptr<Make::Note::Make_Note_SlideNoteContainer>>>& Make::Singleton::Make_Singleton_NoteManager::getSlideNoteVector() {
	return slideNote;
}