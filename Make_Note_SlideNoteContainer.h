#pragma once

#include <cstdint>
#include <utility>
#include <vector>

#include "dxlib/DxLib.h"
#include "Make_Global.h"

namespace Make {
	namespace Note {
		constexpr const std::uint8_t arrowNumInLane{ 4 };//1���[��������̖��̐�
		constexpr const double arrowHeight{ 8.0 };//�`�悷����̕��G
		constexpr const double arrowLength{ 8.0 };//�`�悷����̕��G
		class Make_Note_SlideNoteContainer
		{
		private:
			static std::uint8_t lineThickness;
			const std::uint16_t barID; //�����ߖڂɑ����Ă��邩
			const std::uint8_t beatID;//���̏��߂̉��Ԗڂ̐���
			const double time;//�Ȃ̊J�n���牽�b��
			const std::uint8_t laneAmount; //���[���̐�
			const double& r_y; //�����̍��W
			std::uint32_t colorR;
			std::uint32_t colorL;
			std::pair<bool,bool> noteFlag;//first���E(��)second����(��)
			std::pair<bool, bool> noteDirectionRightOrLeft;//first���Esecond���� true�Ȃ�Efalse�Ȃ獶
			std::vector<double> laneX;
			std::pair<std::pair<std::uint8_t,std::uint8_t>,std::pair<std::uint8_t, std::uint8_t>> noteStartAndEndLane;//first���Esecond����,first��start,second��end
			double arrowWidthBetween; //�`�悷���󓯎m�̕�

			void drawArrow();
		public:
			Make_Note_SlideNoteContainer(const std::uint16_t barID,const std::uint8_t beatID, const double& y,const std::uint8_t amountOfLane,const double time);
			void drawSlideNote();
			void setSlideNoteFlag(const std::uint8_t laneIDStart,const std::uint8_t laneIDEnd,const bool right, const bool isDirectionRight);//�m�[�c���Z�b�g���ɃZ�b�g����Ă���Ȃ�P��

			const std::pair<bool,bool>& getSlideNoteFlag();//true�Ȃ�E��false�Ȃ獶��
			const std::pair<bool, bool>& getSlideNoteDirectionRightOrLeft();//first���Esecond���� true�Ȃ�E����false�Ȃ獶����
			const std::pair<std::pair<std::uint8_t, std::uint8_t>, std::pair<std::uint8_t, std::uint8_t>>& getNoteStartAndEnd();
			const double& getTime();
			const std::uint16_t& getBarID();
			const std::uint8_t& getBeatID();
		};
	}
}

