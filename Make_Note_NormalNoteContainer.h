#pragma once
#include <cstdint>
#include <vector>
#include "dxlib/DxLib.h"
#include "Make_Global.h"


namespace Make {
	namespace Note {
		class Make_Note_NormalNoteContainer
		{
		private:
			static float noteWidth; //�`�悷��m�[�c�̕��G
			const std::uint16_t barID; //�����ߖڂɑ����Ă��邩
			const std::uint8_t beatID;//���̏��߂̉��Ԗڂ̐���
			const float time;//�Ȃ̊J�n���牽�b��
			const std::uint8_t laneAmount; //���[���̐�
			const float& r_y; //�����̍��W
			std::uint32_t color;
			std::vector<bool> noteFlag;
			std::vector<float> noteX;
			float notePointX;
			float notePointY;
		public:
			Make_Note_NormalNoteContainer(const std::uint16_t barID,const std::uint8_t beatID,const float& y,const std::uint8_t amountOfLane,const float time);
			void setNormalNoteFlag(const std::uint8_t laneID);
			void drawNote();
			const bool getNormalNoteFlag(const std::uint8_t laneID);
			const float& getTime();
			const std::uint16_t& getBarID();
			const std::uint8_t& getBeatID();
		};
	}
}