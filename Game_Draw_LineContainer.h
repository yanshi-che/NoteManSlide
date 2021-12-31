#pragma once

#include <cstdint>
#include <vector>

#include "Game_Draw_BaseDraw.h"
#include "Game_File_MusicData.h"

namespace Game {
	namespace Draw {
		class Game_Draw_LineContainer : public Game_Draw_BaseDraw
		{
		private:
			const std::uint16_t barID; //�����ߖڂɑ����Ă��邩
			const std::uint8_t numberOfRane;//���[���̐�
			const double time;//�Ȃ̊J�n���牽�b��
			const std::uint16_t barNumber;//���̏��߂̉��Ԗڂ̐���
			std::int32_t color;
			std::uint8_t thickness;
			std::vector<bool> notesFlag; //�m�[�c�����Z�b�g���ꂽ���ǂ���
			std::int32_t y;
		public:
			Game_Draw_LineContainer(std::uint16_t bID, std::uint8_t numOfRane, double t, std::uint16_t bNum, std::int32_t y);
			void drawNote() noexcept;
			void drawLine() noexcept;
			void draw() override;
		};
	}
}

