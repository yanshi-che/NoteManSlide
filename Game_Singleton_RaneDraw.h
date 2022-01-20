#pragma once

#include <memory>
#include "Game_Draw_BaseDraw.h"
#include "dxlib/DxLib.h"

namespace Game {
	namespace Singleton {
		class Game_Singleton_RaneDraw :public Draw::Game_Draw_BaseDraw
		{
		private:
			const std::uint32_t raneColor;     //レーンの色
			const std::uint8_t raneThickness;  //レーンの太さ
			std::uint16_t raneWidth; //レーンの幅
			std::uint8_t numberOfRane;		   //レーンの数
			static Game_Singleton_RaneDraw* instance;
			Game_Singleton_RaneDraw();
		public:
			static Game_Singleton_RaneDraw* getInstance();
			void destroyInstance();
			void draw() noexcept override;
			void setNumberOfRane(std::uint8_t num) noexcept;
		};

	}
}

inline void Game::Singleton::Game_Singleton_RaneDraw::draw() noexcept {
	if (numberOfRane != NULL) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		for (int i = 0; i <= numberOfRane; i++) {
			DrawLine(raneWidth * i + Global::DRAW_X_MIN, 0, raneWidth * i + Global::DRAW_X_MIN, Global::WINDOW_HEIGHT, raneColor, raneThickness);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}