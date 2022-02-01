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
			std::int32_t* p_yForLong;
			std::uint16_t longNotesGroup;
			bool longNoteErase;

			std::uint16_t barIDForInitOneVector;
			static Game_Singleton_NoteManager* p_instance;
			Game_Singleton_NoteManager();
		public:
			static Game_Singleton_NoteManager* getInstance();
			void destroyInstance();

			void initVector(const std::uint16_t& barLength, std::uint8_t& quontize);
			void initOneVector(std::uint8_t& quontize);
			void makeNoteInstance(const std::uint16_t& barID,const std::uint16_t& beatID,const std::int32_t& y,const std::uint8_t& amountOfLane,const double& time);
			void resetVector(bool isAll);
			void removeLongNote(const std::uint16_t barID, const std::uint16_t beatID, std::uint8_t laneID);
			void setNormalNote(const std::uint16_t& barID,const std::uint16_t& beatID,std::uint8_t laneID);
			void setLongNote(const std::uint16_t barID, const std::uint16_t beatID, std::uint8_t laneID,std::int32_t* y,bool isFirst);
			void setBarIDForInitOneVector(std::uint16_t	id);

			const std::vector<std::vector<std::shared_ptr<Note::Game_Note_NormalNoteContainer>>>& getNormalNoteVector();
			const std::vector<std::vector<std::shared_ptr<Note::Game_Note_LongNoteContainer>>>& getLongNoteVector();

			void draw(const std::uint16_t& barID, const std::uint16_t& beatID);
		};
	}
}
