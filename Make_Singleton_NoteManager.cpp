#include "Make_Singleton_NoteManager.h"

Make::Singleton::Make_Singleton_NoteManager* Make::Singleton::Make_Singleton_NoteManager::p_instance = nullptr;

Make::Singleton::Make_Singleton_NoteManager::Make_Singleton_NoteManager() {
	startBarIDForLongNote = 0;
	startBeatIDForLongNote = 0;
	longNotesGroup = 1;
	p_yForLong = nullptr;
	longNoteErase = false;
	barIDForInitOneVector = 0;
}

Make::Singleton::Make_Singleton_NoteManager* Make::Singleton::Make_Singleton_NoteManager::getInstance() {
	if (p_instance == nullptr) {
		p_instance = new Make_Singleton_NoteManager();
	}
	return p_instance;
}

void Make::Singleton::Make_Singleton_NoteManager::destroyInstance() {
	delete p_instance;
}

void Make::Singleton::Make_Singleton_NoteManager::draw(std::uint16_t barID,std::uint16_t beatID) {
	if (normalNotes.size() != 0) {
		normalNotes[barID][beatID]->drawNote();
		longNotes[barID][beatID]->drawLongNote();
	}
}

void Make::Singleton::Make_Singleton_NoteManager::initVector(std::uint16_t barLength, std::uint8_t quontize) {
	normalNotes.resize(barLength);
	longNotes.resize(barLength);
	for (int i = 0; i < barLength; ++i) {
		normalNotes[i].resize(quontize);
		longNotes[i].resize(quontize);
	}
}

void Make::Singleton::Make_Singleton_NoteManager::initOneVector(std::uint8_t quontize) {
	normalNotes[barIDForInitOneVector].resize(quontize);
	longNotes[barIDForInitOneVector].resize(quontize);
}

void Make::Singleton::Make_Singleton_NoteManager::makeNoteInstance(std::uint16_t barID,std::uint16_t beatID,const float& y,std::uint8_t amountOfLane,float time) {
	normalNotes[barID][beatID] = std::make_shared<Note::Make_Note_NormalNoteContainer>(barID,beatID,y,amountOfLane,time);
	longNotes[barID][beatID] = std::make_shared<Note::Make_Note_LongNoteContainer>(barID,beatID,y,amountOfLane,time);
}

void Make::Singleton::Make_Singleton_NoteManager::resetVector(bool isAll) {
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

void Make::Singleton::Make_Singleton_NoteManager::removeLongNote(std::uint16_t barID,std::uint16_t beatID, std::uint8_t laneID) {
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
					longNotes[i][k]->setNoteHeight(laneID, 0,true);
					longNotes[i][k]->setNoteHeight(laneID, 0, false);
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
		//���̎��_�Ŏn�_�I�_�ɓ���������߂�
		if (isFirstOrLastCount == 2) {
			longNoteErase = true;
			return;
		}
		isNotHaveNote = 0;
		for (int i = barID - 1; 0 <= i; --i) {
			for (int k = static_cast<int>(longNotes[i].size()) - 1; 0 <= k; --k) {
				if (longNotes[i][k]->getNoteGroup(laneID) == noteGroup && longNotes[i][k]->getLongNoteFlag(laneID).first) {
					longNotes[i][k]->setLongNoteFlag(laneID, true);
					longNotes[i][k]->setNoteHeight(laneID, 0,true);
					longNotes[i][k]->setNoteHeight(laneID, 0, false);
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

void Make::Singleton::Make_Singleton_NoteManager::setBarIDForInitOneVector(std::uint16_t id) {
	barIDForInitOneVector = id;
}


void Make::Singleton::Make_Singleton_NoteManager::setNormalNote(std::uint16_t barID,std::uint16_t beatID, std::uint8_t laneID) {
	if (!longNotes[barID][beatID]->getLongNoteFlag(laneID).first) {
		normalNotes[barID][beatID]->setNormalNoteFlag(laneID);
	}
}

void Make::Singleton::Make_Singleton_NoteManager::setLongNote(std::uint16_t barID,std::uint16_t beatID, std::uint8_t laneID, float* y,bool isFirst) {
	if (isFirst) {
		//���Ƀ����O�m�[�c���ݒu����Ă������ɓP������
		removeLongNote(barID, beatID, laneID);
		if (longNoteErase) {
			return;
		}
		//�����O�m�[�c���Z�b�g����Ă��Ȃ��Ƃ�
		startBarIDForLongNote = barID;
		startBeatIDForLongNote = beatID;
		p_yForLong = y;
		longNotes[barID][beatID]->setLongNoteFlag(laneID, isFirst);
		longNotes[barID][beatID]->setNoteGroup(laneID, longNotesGroup);
	}
	else {
		//�����O�m�[�c�̍폜�����������ꍇ�͉��������ɖ߂�
		if (longNoteErase) {
			longNoteErase = false;
			return;
		}
		//TODO�@�ݒu���o�O��
		//�n�_�ƂȂ锏���̍��W�ƃ}�E�X�𗣂������W�̊Ԃɑ��݂��锏���Ƀ����O�m�[�c���Z�b�g
		std::stack<Note::Make_Note_NormalNoteContainer*> stackNormal;
		std::stack<Note::Make_Note_LongNoteContainer*> stackLong;
		std::uint8_t count = 0;
		bool isFirst = true;

		if (0 < *p_yForLong - *y) { //�����̏��Ԃɉ����ă����O�m�[�c��L�΂�����
			for (int i = startBarIDForLongNote, iSize = static_cast<int>(longNotes.size()); i < iSize; ++i) {//�͈͓��̔����̌���
				for (int k = 0, kSize = static_cast<int>(longNotes[i].size()); k < kSize; ++k) {
					if (longNotes[i][k]->getY() < *p_yForLong && *y - Global::clickWidth < longNotes[i][k]->getY()) {
						stackNormal.push(normalNotes[i][k].get());
						stackLong.push(longNotes[i][k].get());
						++count;
						isFirst = false;
					}
				}
				if (count == 0 && !isFirst) {
					break;
				}
				count = 0;
			}

			if (stackLong.size() == 0) {//�n�_���瑼�̔����ɐL�΂��Ȃ������Ƃ�
				longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setLongNoteFlag(laneID, true);
				longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNoteGroup(laneID, 0);
			}
			else {
				if (normalNotes[startBarIDForLongNote][startBeatIDForLongNote]->getNormalNoteFlag(laneID)) {//�n�_�̃m�[�}���m�[�c������
					normalNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNormalNoteFlag(laneID);
				}
				isFirst = true;
				while (stackLong.size() != 0) {//�����O�m�[�c�̃Z�b�g�ƃm�[�}���m�[�c�̓P��
					if (!longNoteErase && stackLong.top()->getLongNoteFlag(laneID).first) {//�ʂ̃����O�m�[�c���͈͓��Ɋ܂܂�Ă������폜
						removeLongNote(stackLong.top()->getBarID(), stackLong.top()->getBeatID(), laneID);
					}
					if (!isFirst) {
						stackLong.top()->setLongNoteFlag(laneID, false);
					}
					else {//�I�_�̏���
						stackLong.top()->setLongNoteFlag(laneID, true);
						longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNoteHeight(laneID, *p_yForLong - stackLong.top()->getY(),true);
						stackLong.top()->setNoteHeight(laneID, *p_yForLong - stackLong.top()->getY(),false);
						isFirst = false;
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
		else {//�����̏��ԂƋt�����Ƀ����O�m�[�c��L�΂�����
			for (int i = startBarIDForLongNote; 0 <= i; --i) {//�͈͓��̔����̌���
				for (int k = static_cast<int>(longNotes[i].size()) -1; 0 <= k; --k) {
					if (*p_yForLong < longNotes[i][k]->getY() && longNotes[i][k]->getY() < *y + Global::clickWidth) {
						stackNormal.push(normalNotes[i][k].get());
						stackLong.push(longNotes[i][k].get());
						++count;
						isFirst = false;
					}
				}
				if (count == 0 && !isFirst) {
					break;
				}
				count = 0;
			}
			if (stackLong.size() == 0) {//�n�_���瑼�̔����ɐL�΂��Ȃ������Ƃ�
				longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setLongNoteFlag(laneID, true);
				longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNoteGroup(laneID, 0);
			}
			else {
				if (normalNotes[startBarIDForLongNote][startBeatIDForLongNote]->getNormalNoteFlag(laneID)) {//�n�_�̃m�[�}���m�[�c������
					normalNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNormalNoteFlag(laneID);
				}
				isFirst = true;
				while (stackLong.size() != 0) {//�����O�m�[�c�̃Z�b�g�ƃm�[�}���m�[�c�̓P��
					if (!longNoteErase && stackLong.top()->getLongNoteFlag(laneID).first) {//�ʂ̃����O�m�[�c���͈͓��Ɋ܂܂�Ă������폜
						removeLongNote(stackLong.top()->getBarID(), stackLong.top()->getBeatID(), laneID);
					}
					if (!isFirst) {
						stackLong.top()->setLongNoteFlag(laneID, false);
					}
					else {//�I�_�̏���
						stackLong.top()->setLongNoteFlag(laneID, true);
						longNotes[startBarIDForLongNote][startBeatIDForLongNote]->setNoteHeight(laneID,stackLong.top()->getY() - *p_yForLong,false);
						stackLong.top()->setNoteHeight(laneID, stackLong.top()->getY() - *p_yForLong,true);
						isFirst = false;
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

const std::vector<std::vector<std::shared_ptr<Make::Note::Make_Note_NormalNoteContainer>>>& Make::Singleton::Make_Singleton_NoteManager::getNormalNoteVector() {
	return normalNotes;
}

const std::vector<std::vector<std::shared_ptr<Make::Note::Make_Note_LongNoteContainer>>>& Make::Singleton::Make_Singleton_NoteManager::getLongNoteVector() {
	return longNotes;
}