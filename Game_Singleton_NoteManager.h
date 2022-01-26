#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "Game_Note_NormalNoteContainer.h"
#include "Game_Note_LongNoteContainer.h"


namespace Game {
	namespace Singleton {
		class Game_Singleton_NoteManager
		{
		private:
			std::vector<std::vector<std::unique_ptr<Note::Game_Note_NormalNoteContainer>>> normalNotes;
			std::vector<std::vector<std::unique_ptr<Note::Game_Note_LongNoteContainer>>> longNotes;

			std::uint16_t startBarIDForLongNote;
			std::uint16_t startBeatIDForLongNote;
			std::int32_t* yForLong;
			std::uint16_t longNotesGroup;
			bool longNoteErase;

			std::uint16_t barIDForInitOneVector;
			static Game_Singleton_NoteManager* instance;
			Game_Singleton_NoteManager();
		public:
			static Game_Singleton_NoteManager* getInstance();
			void destroyInstance();

			void initVector(const std::uint16_t* barLength, std::uint8_t& quontize);
			void resetVector(bool isAll);
			void initOneVector(std::uint8_t& quontize);
			void makeNoteInstance(const std::uint16_t& barID,const std::uint16_t& beatID,std::int32_t* y,const std::uint8_t* numberOfRane);
			void setNormalNote(const std::uint16_t& barID,const std::uint16_t& beatID,std::uint8_t raneID);
			void setLongNote(const std::uint16_t barID, const std::uint16_t beatID, std::uint8_t raneID,std::int32_t* y,bool isFirst);
			void removeLongNote(const std::uint16_t barID, const std::uint16_t beatID, std::uint8_t raneID);
			void setBarIDForInitOneVector(std::uint16_t	id);
			void draw(const std::uint16_t& barID, const std::uint16_t& beatID);
		};
	}
}

inline void Game::Singleton::Game_Singleton_NoteManager::draw(const std::uint16_t& barID, const std::uint16_t& beatID) {
	if (normalNotes.size() != 0) {
		normalNotes[barID][beatID]->drawNote();
		longNotes[barID][beatID]->drawLongNote();
	}
}
