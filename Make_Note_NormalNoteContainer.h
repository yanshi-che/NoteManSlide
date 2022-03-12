#pragma once
#include <cstdint>
#include <vector>
#include "dxlib/DxLib.h"
#include "Global.h"


namespace Make {
	namespace Note {
		class Make_Note_NormalNoteContainer
		{
		private:
			static double noteWidth; //�`�悷��m�[�c�̕��G
			const std::uint16_t barID; //�����ߖڂɑ����Ă��邩
			const std::uint16_t beatID;//���̏��߂̉��Ԗڂ̐���
			const double time;//�Ȃ̊J�n���牽�b��
			const std::uint16_t laneAmount; //���[���̐�
			const double& r_y; //�����̍��W
			std::uint32_t color;
			std::vector<bool> noteFlag;
			std::vector<double> noteX;
			double notePointX;
			double notePointY;
		public:
			Make_Note_NormalNoteContainer(const std::uint16_t barID,const std::uint16_t beatID,const double& y,const std::uint16_t amountOfLane,const double time);
			void setNormalNoteFlag(const std::uint16_t laneID);
			void drawNote();
			const bool getNormalNoteFlag(const std::uint16_t laneID);
			const double& getTime();
			const std::uint16_t& getBarID();
			const std::uint16_t& getBeatID();
		};
	}
}