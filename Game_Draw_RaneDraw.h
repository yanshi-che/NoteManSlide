#pragma once

#include <memory>
#include "Game_Draw_BaseDraw.h"
#include "dxlib/DxLib.h"

namespace Game {
	namespace Draw {
		class Game_Draw_RaneDraw :public Game::Draw::Game_Draw_BaseDraw
		{
		private:
			const std::uint32_t raneColor;     //���[���̐F
			const std::uint8_t raneThickness;  //���[���̑���
			std::uint8_t numberOfRane;		   //���[���̐�
		public:
			Game_Draw_RaneDraw();
			void draw() noexcept override;
			void setNumberOfRane(std::uint8_t num) noexcept;
			const std::uint8_t& getNumberOfRane() noexcept;
		};

	}
}