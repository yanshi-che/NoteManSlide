#pragma once

#include <cstdint>
#include <vector>
#include <utility>
#include "dxlib/DxLib.h"
#include "Game_Global.h"

namespace Game {
	namespace Note {
		class Game_Note_LongNoteContainer
		{
		private:
			static float noteWidth; //�`�悷��m�[�c�̕��G
			const std::uint16_t barID; //�����ߖڂɑ����Ă��邩
			const std::uint16_t beatID;//���̏��߂̉��Ԗڂ̐���
			const float time;//�Ȃ̊J�n���牽�b��
			const std::uint8_t amountOfLane; //���[���̐�
			const float& r_y; //�����̍��W
			std::uint32_t color;
			std::vector<std::pair<bool,bool>> notesFlag;//first�̓m�[�c���Z�b�g����Ă��邩�Asecond�͂��ꂪ�n�_�܂��͏I�_��
			std::vector<float> notesX;
			std::vector<float> notesHeight1;
			std::vector<float> notesHeight2;
			float notePointX;
			float notePointY;
			std::vector<uint16_t> notesGroup;
		public:
			Game_Note_LongNoteContainer(std::uint16_t barID,std::uint16_t beatID,const float& y,std::uint8_t amountOfLane,float time);
			void setLongNoteFlag(std::uint8_t laneID,bool isFirstOrLast);//�m�[�c���Z�b�g���ɃZ�b�g����Ă���Ȃ�P��
			void drawLongNote();
			void setNoteHeight(std::uint8_t laneID, float noteHeight,bool isOne);
			void setNoteGroup(std::uint8_t laneID, std::uint16_t group);
			const std::uint16_t& getNoteGroup(std::uint8_t laneID);
			const float& getY();
			const std::pair<bool, bool> getLongNoteFlag(std::uint8_t laneID);
			const float& getTime();
			const std::uint16_t& getBarID();
			const std::uint16_t& getBeatID();
		};
	}
}

