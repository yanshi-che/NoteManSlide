#include "Make_Note_NoteManager.h"

Make::Note::Make_Note_NoteManager::Make_Note_NoteManager(){
	startBarID = 0;
	startBeatID = 0;
	startLaneID = 0;
	longNoteGroup = 1;
	p_yBefore = nullptr;
	noteErase = false;
	mouseYBefore = 0;
}

void Make::Note::Make_Note_NoteManager::draw(const std::uint16_t barID,const std::uint8_t beatID) {
	if (normalNote.size() != 0) {
		normalNote.at(barID).at(beatID)->drawNote();
		longNote.at(barID).at(beatID)->drawLongNote();
		slideNote.at(barID).at(beatID)->drawSlideNote();
	}
}

void Make::Note::Make_Note_NoteManager::initVector(const std::uint16_t barLength,const std::uint8_t quontize) {
	normalNote.resize(barLength);
	longNote.resize(barLength);
	slideNote.resize(barLength);
	if (quontize != NULL) {
		for (int i = 0; i < barLength; ++i) {
			normalNote.at(i).resize(quontize);
			longNote.at(i).resize(quontize);
			slideNote.at(i).resize(quontize);
		}
	}
}

void Make::Note::Make_Note_NoteManager::resizeOneVector(const std::uint16_t barID, const std::uint8_t quontize) {
	normalNote.at(barID).resize(quontize);
	longNote.at(barID).resize(quontize);
	slideNote.at(barID).resize(quontize);
}

void Make::Note::Make_Note_NoteManager::initOneVector(const std::uint8_t quontize,const std::uint16_t barID) {
	normalNote.at(barID).resize(quontize);
	longNote.at(barID).resize(quontize);
	slideNote.at(barID).resize(quontize);
}

void Make::Note::Make_Note_NoteManager::makeNoteInstance(const std::uint16_t barID,const std::uint8_t beatID,const double& y,const std::uint8_t laneAmount,double time) {
	normalNote.at(barID).at(beatID) = std::make_shared<Note::Make_Note_NormalNoteContainer>(barID,beatID,y,laneAmount,time);
	longNote.at(barID).at(beatID) = std::make_shared<Note::Make_Note_LongNoteContainer>(barID,beatID,y,laneAmount,time);
	slideNote.at(barID).at(beatID) = std::make_shared<Note::Make_Note_SlideNoteContainer>(barID, beatID, y, laneAmount, time);
}

void Make::Note::Make_Note_NoteManager::resetVector(const bool isAll,const std::uint16_t barID){
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

void Make::Note::Make_Note_NoteManager::removeLongNote(const std::uint16_t barID,const std::uint8_t beatID,const std::uint8_t laneID) {
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

void Make::Note::Make_Note_NoteManager::setNormalNote(const std::uint16_t barID,const std::uint8_t beatID,const std::uint8_t laneID) {
	if (!longNote.at(barID).at(beatID)->getLongNoteFlag(laneID).first) {
		normalNote.at(barID).at(beatID)->setNormalNoteFlag(laneID);
	}
}

void Make::Note::Make_Note_NoteManager::setLongNote(const std::uint16_t barID,const std::uint8_t beatID,const std::uint8_t laneID,double* y,const bool isFirst) {
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
				return;
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
				return;
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

void Make::Note::Make_Note_NoteManager::setLongNoteBySavaData(const std::uint16_t startBarID, const std::uint8_t startBeatID, const std::uint16_t endBarID, const std::uint8_t endBeatID, const std::uint8_t laneID) {
	std::stack<Note::Make_Note_LongNoteContainer*> stackLong;
	const double startY = longNote.at(startBarID).at(startBeatID)->getY();
	const double endY = longNote.at(endBarID).at(endBeatID)->getY();

	//始点終点の処理
	longNote.at(startBarID).at(startBeatID)->setLongNoteFlag(laneID,true);
	longNote.at(startBarID).at(startBeatID)->setNoteGroup(laneID, longNoteGroup);
	longNote.at(startBarID).at(startBeatID)->setNoteHeight(laneID, startY - endY, true);
	longNote.at(endBarID).at(endBeatID)->setLongNoteFlag(laneID, true);
	longNote.at(endBarID).at(endBeatID)->setNoteGroup(laneID, longNoteGroup);
	longNote.at(endBarID).at(endBeatID)->setNoteHeight(laneID, startY - endY, false);

	//間の処理
	std::uint8_t count = 0;
	bool isFirstNote = true;
	for (int i = startBarID, iSize = static_cast<int>(longNote.size()); i < iSize; ++i) {//範囲内の拍線の検索
		for (int k = 0, kSize = static_cast<int>(longNote.at(i).size()); k < kSize; ++k) {
			if (longNote.at(i).at(k)->getY() < startY && endY < longNote.at(i).at(k)->getY()) {
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
	while (stackLong.size() != 0) {//ロングノーツのセットとノーマルノーツの撤去
		stackLong.top()->setLongNoteFlag(laneID, false);
		stackLong.top()->setNoteGroup(laneID, longNoteGroup);
		stackLong.pop();
	}
	++longNoteGroup;
}

void Make::Note::Make_Note_NoteManager::setLongNoteGroupe(const std::uint16_t longNoteGroup) {
	this->longNoteGroup = longNoteGroup;
}

void Make::Note::Make_Note_NoteManager::setSlideNote(const std::uint16_t barID,const std::uint8_t beatID,const std::uint8_t laneID,const double mouseY,const bool isFirst, const bool isRight) {
	if (isFirst) {
		if (slideNote.at(barID).at(beatID)->getSlideNoteFlag().first &&
			slideNote.at(barID).at(beatID)->getNoteStartAndEnd().first.second <= laneID &&
			laneID <= slideNote.at(barID).at(beatID)->getNoteStartAndEnd().first.first) {
			slideNote.at(barID).at(beatID)->setSlideNoteFlag(NULL,NULL,isRight,false);
			noteErase = true;
			return;
		}
		else if(slideNote.at(barID).at(beatID)->getSlideNoteFlag().second &&
			slideNote.at(barID).at(beatID)->getNoteStartAndEnd().second.first <= laneID &&
			laneID <= slideNote.at(barID).at(beatID)->getNoteStartAndEnd().second.second){
			slideNote.at(barID).at(beatID)->setSlideNoteFlag(NULL, NULL, isRight,false);
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
		if (isRight) {
			if (slideNote.at(startBarID).at(startBeatID)->getSlideNoteFlag().first) {
				slideNote.at(startBarID).at(startBeatID)->setSlideNoteFlag(NULL, NULL, isRight,false);
			}
			if (0 < mouseYBefore - mouseY) {
				slideNote.at(startBarID).at(startBeatID)->setSlideNoteFlag(startLaneID, laneID, isRight,false);
			}
			else if (mouseYBefore - mouseY < 0) {
				slideNote.at(startBarID).at(startBeatID)->setSlideNoteFlag(startLaneID, laneID, isRight,true);
			}
		}
		else {
			if (slideNote.at(startBarID).at(startBeatID)->getSlideNoteFlag().second) {
				slideNote.at(startBarID).at(startBeatID)->setSlideNoteFlag(NULL, NULL, isRight,false);
			}
			if (0 < mouseYBefore - mouseY) {
				slideNote.at(startBarID).at(startBeatID)->setSlideNoteFlag(startLaneID, laneID, isRight,false);
			}
			else if (mouseYBefore - mouseY < 0) {
				slideNote.at(startBarID).at(startBeatID)->setSlideNoteFlag(startLaneID, laneID, isRight,true);
			}
		}
	}
}

void Make::Note::Make_Note_NoteManager::setSlideNoteBySavaData(const std::uint16_t barID, const std::uint8_t beatID, const std::uint8_t start, const std::uint8_t end, const bool isRight, const bool isDirectionRight) {
	if (isRight) {
		slideNote.at(barID).at(beatID)->setSlideNoteFlag(start, end, true,isDirectionRight);
	}
	else{
		slideNote.at(barID).at(beatID)->setSlideNoteFlag(start, end, false,isDirectionRight);
	}
}

const std::vector<std::vector<std::shared_ptr<Make::Note::Make_Note_NormalNoteContainer>>>& Make::Note::Make_Note_NoteManager::getNormalNoteVector() {
	return normalNote;
}

const std::vector<std::vector<std::shared_ptr<Make::Note::Make_Note_LongNoteContainer>>>& Make::Note::Make_Note_NoteManager::getLongNoteVector() {
	return longNote;
}

const std::vector<std::vector<std::shared_ptr<Make::Note::Make_Note_SlideNoteContainer>>>& Make::Note::Make_Note_NoteManager::getSlideNoteVector() {
	return slideNote;
}