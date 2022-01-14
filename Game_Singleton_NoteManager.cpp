#include "Game_Singleton_NoteManager.h"

Game::Singleton::Game_Singleton_NoteManager* Game::Singleton::Game_Singleton_NoteManager::instance = nullptr;


Game::Singleton::Game_Singleton_NoteManager::Game_Singleton_NoteManager() {}

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
	for (int i = 0; i < *barLength; i++) {
		normalNotes[i].resize(quontize);
	}
}

void Game::Singleton::Game_Singleton_NoteManager::makeNoteInstance(const std::uint16_t& barID,const std::uint16_t& beatID, std::int32_t* y,const  std::uint8_t* numberOfRane) {
	normalNotes[barID][beatID] = std::make_unique<Note::Game_Note_NoteContainer>(y,numberOfRane);
}

void Game::Singleton::Game_Singleton_NoteManager::setNote(const std::uint16_t& barID,const std::uint16_t& beatID, std::uint8_t raneID) {
	normalNotes[barID][beatID]->setNoteFlag(raneID);
}

void Game::Singleton::Game_Singleton_NoteManager::draw() {
	if (normalNotes.size() != 0) {
		for (int i = 0; i < normalNotes.size(); i++) {
			for (int k = 0; k < normalNotes[i].size(); k++) {
				normalNotes[i][k]->drawNote();
			}
		}
	}
}