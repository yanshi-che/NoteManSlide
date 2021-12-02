#pragma once

#include "Game_Draw_BaseDraw.h"
#include "dxlib/DxLib.h"

namespace Game {
	namespace Draw {
		class Game_Draw_RaneDraw :public Game::Draw::Game_Draw_BaseDraw
		{
		private:
			const std::uint32_t raneColor;     //レーンの色
			const std::uint8_t raneThickness;  //レーンの太さ
			std::uint8_t numberOfRane;		   //レーンの数
			void raneDraw() const noexcept;
		public:
			Game_Draw_RaneDraw();
			void draw() override;
			void setNumberOfRane(std::uint8_t num) noexcept;
			const std::uint8_t& getNumberOfRane() noexcept;
		};

	}
}