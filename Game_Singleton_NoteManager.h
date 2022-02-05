#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <stack>

#include "Game_Note_NormalNoteContainer.h"
#include "Game_Note_LongNoteContainer.h"


namespace Game {
	namespace Singleton {
		class Game_Singleton_NoteManager
		{
		private:
			std::vector<std::vector<std::shared_ptr<Note::Game_Note_NormalNoteContainer>>> normalNotes;
			std::vector<std::vector<std::shared_ptr<Note::Game_Note_LongNoteContainer>>> longNotes;

			std::uint16_t startBarIDForLongNote;
			std::uint16_t startBeatIDForLongNote;
			float* p_yForLong;
			std::uint16_t longNotesGroup;
			bool longNoteErase;

			std::uint16_t barIDForInitOneVector;
			static Game_Singleton_NoteManager* p_instance;
			Game_Singleton_NoteManager();
		public:
			static Game_Singleton_NoteManager* getInstance();
			void destroyInstance();

			void initVector(std::uint16_t barLength,std::uint8_t quontize);
			void initOneVector(std::uint8_t quontize);
			void makeNoteInstance(std::uint16_t barID,std::uint16_t beatID,const float& y,std::uint8_t amountOfLane,float time);
			void resetVector(bool isAll);
			void removeLongNote(std::uint16_t barID,std::uint16_t beatID,std::uint8_t laneID);
			void setNormalNote(std::uint16_t barID,std::uint16_t beatID,std::uint8_t laneID);
			void setLongNote(std::uint16_t barID,std::uint16_t beatID,std::uint8_t laneID,float* y,bool isFirst);
			void setBarIDForInitOneVector(std::uint16_t	id);

			const std::vector<std::vector<std::shared_ptr<Note::Game_Note_NormalNoteContainer>>>& getNormalNoteVector();
			const std::vector<std::vector<std::shared_ptr<Note::Game_Note_LongNoteContainer>>>& getLongNoteVector();

			void draw(std::uint16_t barID, std::uint16_t beatID);
		};
	}
}
