#pragma once

#include <cstdint>
#include <vector>
#include <utility>
#include "dxlib/DxLib.h"
#include "Global.h"

namespace Make {
	namespace Note {
		class Make_Note_LongNoteContainer
		{
		private:
			static double noteWidth; //�`�悷��m�[�c�̕��G
			const std::uint16_t barID; //�����ߖڂɑ����Ă��邩
			const std::uint16_t beatID;//���̏��߂̉��Ԗڂ̐���
			const double time;//�Ȃ̊J�n���牽�b��
			const std::uint16_t laneAmount; //���[���̐�
			const double& r_y; //�����̍��W
			std::uint32_t color;
			std::vector<std::pair<bool,bool>> noteFlag;//first�̓m�[�c���Z�b�g����Ă��邩�Asecond�͂��ꂪ�n�_�܂��͏I�_��
			std::vector<double> noteX;
			std::vector<double> noteHeight1;
			std::vector<double> noteHeight2;
			double notePointX;
			double notePointY;
			std::vector<uint16_t> noteGroup;
		public:
			Make_Note_LongNoteContainer(const std::uint16_t barID,const std::uint16_t beatID,const double& y,std::uint16_t amountOfLane,const double time);
			void setLongNoteFlag(const std::uint16_t laneID,const bool isFirstOrLast);//�m�[�c���Z�b�g���ɃZ�b�g����Ă���Ȃ�P��
			void drawLongNote();
			void setNoteHeight(const std::uint16_t laneID,const double noteHeight,const bool isFirst);
			void setNoteGroup(const std::uint16_t laneID,const std::uint16_t group);

			const std::uint16_t& getNoteGroup(const std::uint16_t laneID);
			const double& getY();
			const std::pair<bool, bool> getLongNoteFlag(const std::uint16_t laneID);
			const double& getTime();
			const std::uint16_t& getBarID();
			const std::uint16_t& getBeatID();
		};
	}
}

