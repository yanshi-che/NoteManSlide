#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "dxlib/DxLib.h"
#include "Game_Singleton_MouseOperationCheck.h"
#include "Game_Draw_LineContainer.h"

namespace Game {
	namespace Draw {
		constexpr const float backWidth{ 20.0f };
		constexpr const float barWidth{15.0f};
		constexpr const float arrowWidthX{ 10.0f };
		constexpr const float arrowWidthYAndSpace{ 5.0f };
		constexpr const float yScrMax{ Global::WINDOW_HEIGHT - backWidth };
		constexpr const float yScrMin{ backWidth };
		class Game_Draw_ScrollBar
		{
		private:
			Singleton::Game_Singleton_MouseOperationCheck* p_mouseCheck;
			std::vector<std::vector<std::shared_ptr<Game_Draw_LineContainer>>>& barVec;
			float barHeight;//バーの長さ
			float scrollWidthRate;//スクロールバーと実際の画面との比率
			float& yMagnificationByMouseWheel;
			std::int32_t backColor;
			std::int32_t barColor;
			float y;
			bool clickObserver;
			float barPointX[2];
			float arrowPointX[3];
			float arrowPointY[4];

			void drawBack();
			void drawArrow();
			void drawBar();
			void updateLineContainerY(float y);
			void clickChecker();
		public:
			Game_Draw_ScrollBar(float scrollWidthRate, std::vector<std::vector<std::shared_ptr<Game_Draw_LineContainer>>>& barVec, float& yMagnificationByMouseWheel);
			void updateBarY(float upY);
			void draw();
		};
	}
}

