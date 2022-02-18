#pragma once

#include <cstdint>
#include <vector>
#include <utility>
#include "dxlib/DxLib.h"
#include "Make_Global.h"

namespace Make {
	namespace Note {
		class Make_Note_LongNoteContainer
		{
		private:
			static float noteWidth; //�`�悷��m�[�c�̕��G
			const std::uint16_t barID; //�����ߖڂɑ����Ă��邩
			const std::uint8_t beatID;//���̏��߂̉��Ԗڂ̐���
			const float time;//�Ȃ̊J�n���牽�b��
			const std::uint8_t amountOfLane; //���[���̐�
			const float& r_y; //�����̍��W
			std::uint32_t color;
			std::vector<std::pair<bool,bool>> noteFlag;//first�̓m�[�c���Z�b�g����Ă��邩�Asecond�͂��ꂪ�n�_�܂��͏I�_��
			std::vector<float> noteX;
			std::vector<float> noteHeight1;
			std::vector<float> noteHeight2;
			float notePointX;
			float notePointY;
			std::vector<uint16_t> noteGroup;
		public:
			Make_Note_LongNoteContainer(const std::uint16_t barID,const std::uint8_t beatID,const float& y,std::uint8_t amountOfLane,const float time);
			void setLongNoteFlag(const std::uint8_t laneID,const bool isFirstOrLast);//�m�[�c���Z�b�g���ɃZ�b�g����Ă���Ȃ�P��
			void drawLongNote();
			void setNoteHeight(const std::uint8_t laneID,const float noteHeight,const bool isFirst);
			void setNoteGroup(const std::uint8_t laneID,const std::uint16_t group);

			const std::uint16_t& getNoteGroup(const std::uint8_t laneID);
			const float& getY();
			const std::pair<bool, bool> getLongNoteFlag(const std::uint8_t laneID);
			const float& getTime();
			const std::uint16_t& getBarID();
			const std::uint8_t& getBeatID();
		};
	}
}

