#include "Game_Singleton_NoteManager.h"

Game::Singleton::Game_Singleton_NoteManager* Game::Singleton::Game_Singleton_NoteManager::instance = nullptr;

Game::Singleton::Game_Singleton_NoteManager::Game_Singleton_NoteManager() {
	startBarIDForLongNote = 0;
	startBeatIDForLongNote = 0;
	yForLong = nullptr;
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
	normalNotes[barID][beatID]->setNoteFlag(raneID);
}

void Game::Singleton::Game_Singleton_NoteManager::setLongNote(const std::uint16_t barID,const std::uint16_t beatID, std::uint8_t raneID, std::int32_t* y,bool isFirst) {
	if (isFirst) {
		startBarIDForLongNote = barID;
		startBeatIDForLongNote = beatID;
		yForLong = y;
		longNotes[barID][beatID]->setLongNoteFlag(raneID, isFirst);
	}
	else {
		Note::Game_Note_LongNoteContainer* last = nullptr;
		if (0 < *yForLong - *y) {
			for (int i = startBarIDForLongNote, isize = longNotes.size(); i < isize; ++i) {
				for (int k = 0, ksize = longNotes[i].size(); k < ksize; ++k) {
					if (longNotes[i][k]->getY() < *yForLong && *y < longNotes[i][k]->getY()) {
						longNotes[i][k]->setLongNoteFlag(raneID, false);
						last = longNotes[i][k].get();
					}
				}
			}
		}
		else {
			for (int i = startBarIDForLongNote; 0 <= i; --i) {
				for (int k = longNotes[i].size() -1; 0 <= k; --k) {
					if (*yForLong < longNotes[i][k]->getY() && longNotes[i][k]->getY() < *y) {
						longNotes[i][k]->setLongNoteFlag(raneID, false);
						last = longNotes[i][k].get();
					}
				}
			}
		}
		last->setLastNoteTrue(raneID);
	}
}