#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "Game_Note_NoteContainer.h"


namespace Game {
	namespace Singleton {
		class Game_Singleton_NoteManager
		{
		private:
			std::vector<std::vector<std::unique_ptr<Note::Game_Note_NoteContainer>>> normalNotes;

			static Game_Singleton_NoteManager* instance;
			Game_Singleton_NoteManager();
		public:
			static Game_Singleton_NoteManager* getInstance();
			void destroyInstance();

			void resizeVector(const std::uint16_t* barLength, std::uint8_t& quontize);
			void makeNoteInstance(const std::uint16_t& barID,const std::uint16_t& beatID,std::int32_t* y,const std::uint8_t* numberOfRane);
			void setNote(const std::uint16_t& barID,const std::uint16_t& beatID,std::uint8_t raneID);
			void draw();
		};
	}
}

