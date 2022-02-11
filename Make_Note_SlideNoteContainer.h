#pragma once

#include <cstdint>
#include <utility>
#include <vector>

#include "dxlib/DxLib.h"
#include "Make_Global.h"

namespace Make {
	namespace Note {
		constexpr const std::uint8_t arrowNumInLane{ 4 };//1���[��������̖��̐�
		constexpr const float arrowHeight{ 8.0f };//�`�悷����̕��G
		constexpr const float arrowLength{ 8.0f };//�`�悷����̕��G
		class Make_Note_SlideNoteContainer
		{
		private:
			static std::uint8_t lineThickness;
			const std::uint16_t barID; //�����ߖڂɑ����Ă��邩
			const std::uint16_t beatID;//���̏��߂̉��Ԗڂ̐���
			const float time;//�Ȃ̊J�n���牽�b��
			const std::uint8_t amountOfLane; //���[���̐�
			const float& r_y; //�����̍��W
			std::uint32_t colorR;
			std::uint32_t colorL;
			std::pair<bool,bool> notesFlag;//first���Esecond����
			std::vector<float> laneX;
			std::pair<std::pair<std::uint8_t,std::uint8_t>,std::pair<std::uint8_t, std::uint8_t>> noteStartAndEndLane;//first���Esecond����,first��start,second��end
			float arrowWidthBetween; //�`�悷���󓯎m�̕�

			void drawArrow();
		public:
			Make_Note_SlideNoteContainer(std::uint16_t barID, std::uint16_t beatID, const float& y, std::uint8_t amountOfLane, float time);
			void drawSlideNote();
			void setSlideNoteFlag(std::uint8_t laneIDStart, std::uint8_t laneIDEnd,bool right);//�m�[�c���Z�b�g���ɃZ�b�g����Ă���Ȃ�P��

			const std::pair<bool,bool>& getSlideNoteFlag();//true�Ȃ�E��false�Ȃ獶��
			const std::pair<std::pair<std::uint8_t, std::uint8_t>, std::pair<std::uint8_t, std::uint8_t>>& getNoteStartAndEnd();
			const float& getTime();
			const std::uint16_t& getBarID();
			const std::uint16_t& getBeatID();
		};
	}
}

