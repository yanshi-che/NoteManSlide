#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <stack>

#include "Make_Note_NormalNoteContainer.h"
#include "Make_Note_LongNoteContainer.h"
#include "Make_Note_SlideNoteContainer.h"


namespace Make {
	namespace Singleton {
		class Make_Singleton_NoteManager
		{
		private:
			std::vector<std::vector<std::shared_ptr<Note::Make_Note_NormalNoteContainer>>> normalNote;
			std::vector<std::vector<std::shared_ptr<Note::Make_Note_LongNoteContainer>>> longNote;
			std::vector<std::vector<std::shared_ptr<Note::Make_Note_SlideNoteContainer>>> slideNote;

			std::uint16_t startBarID;//ロングとスライド用の始点の保存
			std::uint8_t startBeatID;
			std::uint8_t startLaneID;
			float mouseYBefore;
			float* p_yBefore;
			std::uint16_t longNoteGroup;
			bool noteErase;

			static Make_Singleton_NoteManager* p_instance;
			Make_Singleton_NoteManager();
		public:
			static Make_Singleton_NoteManager* getInstance();
			static void destroyInstance();

			void initVector(std::uint16_t barLength,std::uint8_t quontize);
			void initOneVector(std::uint8_t quontize, std::uint16_t barID);
			void makeNoteInstance(std::uint16_t barID,std::uint8_t beatID,const float& y,std::uint8_t amountOfLane,float time);
			void resetVector(bool isAll, std::uint16_t barID);
			void removeLongNote(std::uint16_t barID,std::uint8_t beatID,std::uint8_t laneID);
			void setNormalNote(std::uint16_t barID,std::uint8_t beatID,std::uint8_t laneID);
			void setLongNote(std::uint16_t barID,std::uint8_t beatID,std::uint8_t laneID,float* y,bool isFirst);
			void setLongNoteGroupe(std::uint16_t longNoteGroup);
			void setSlideNote(std::uint16_t barID, std::uint8_t beatID, std::uint8_t laneID,float mouseY,bool isFirst);

			const std::vector<std::vector<std::shared_ptr<Note::Make_Note_NormalNoteContainer>>>& getNormalNoteVector();
			const std::vector<std::vector<std::shared_ptr<Note::Make_Note_LongNoteContainer>>>& getLongNoteVector();
			const std::vector<std::vector<std::shared_ptr<Note::Make_Note_SlideNoteContainer>>>& getSlideNoteVector();

			void draw(std::uint16_t barID, std::uint8_t beatID);
		};
	}
}
