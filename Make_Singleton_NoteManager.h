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

			void draw(const std::uint16_t barID,const std::uint8_t beatID);
			void initVector(const std::uint16_t barLength,const std::uint8_t quontize);
			void initOneVector(const std::uint8_t quontize,const std::uint16_t barID);
			void resizeOneVector(const std::uint16_t barID, const std::uint8_t quontize);
			void makeNoteInstance(const std::uint16_t barID,const std::uint8_t beatID,const float& y,const std::uint8_t amountOfLane,const float time);
			void resetVector(const bool isAll,const std::uint16_t barID);
			void removeLongNote(const std::uint16_t barID,const std::uint8_t beatID,const std::uint8_t laneID);
			void setNormalNote(const std::uint16_t barID,const std::uint8_t beatID,const std::uint8_t laneID);
			void setLongNote(const std::uint16_t barID,const std::uint8_t beatID,const std::uint8_t laneID,float* y,const bool isFirst);
			void setLongNoteBySavaData(const std::uint16_t startBarID, const std::uint8_t startBeatID, const std::uint16_t endBarID, const std::uint8_t endBeatID, const std::uint8_t laneID);
			void setLongNoteGroupe(const std::uint16_t longNoteGroup);
			void setSlideNote(const std::uint16_t barID,const std::uint8_t beatID,const std::uint8_t laneID,const float mouseY,const bool isFirst);
			void setSlideNoteBySavaData(const std::uint16_t barID, const std::uint8_t beatID, const std::uint8_t start, const std::uint8_t end,const bool isRight);

			const std::vector<std::vector<std::shared_ptr<Note::Make_Note_NormalNoteContainer>>>& getNormalNoteVector();
			const std::vector<std::vector<std::shared_ptr<Note::Make_Note_LongNoteContainer>>>& getLongNoteVector();
			const std::vector<std::vector<std::shared_ptr<Note::Make_Note_SlideNoteContainer>>>& getSlideNoteVector();

		};
	}
}
