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
		constexpr const float barHeightMin{ 40.0f };
		constexpr const float arrowWidthX{ 10.0f };
		constexpr const float arrowWidthYAndSpace{ 5.0f };
		constexpr const float yScrMax{ Global::WINDOW_HEIGHT - backWidth };
		constexpr const float yScrMin{ backWidth };
		class Game_Draw_ScrollBar
		{
		private:
			Singleton::Game_Singleton_MouseOperationCheck* p_mouseCheck;
			std::vector<std::vector<std::shared_ptr<Game_Draw_LineContainer>>>& barVec;
			int mouseX, mouseY;//マウスクリックの座標格納用の変数
			float  widthMaxOnClick, widthMinOnClick;//barをクリックしているときの最大値最小値を求めるための変数
			float barYBefore;
			float barHeight;//バーの長さ
			float scrollWidthRate;//スクロールバーと実際の画面との比率
			float& yMagnificationByMouseWheel;//マウスホイール入力に対する画面移動の倍率
			std::int32_t backColor;
			std::int32_t barColor;
			std::int32_t arrowUpColor;
			std::int32_t arrowDownColor;
			float y;//barのy座標
			bool clickObserver;//クリックの制御用
			float barPointX[2];//barのx座標格納
			float arrowPointX[3];//上下矢印の頂点のｘ座標
			float arrowPointY[4];//上下矢印の頂点のｙ座標

			void drawBack();
			void drawArrow();
			void drawBar();
			void updateLineContainerY(float y);
			void setBarY(float sY);
			void clickCheck();
			void borderCheck();
		public:
			Game_Draw_ScrollBar(float scrollWidth, std::vector<std::vector<std::shared_ptr<Game_Draw_LineContainer>>>& barVec, float& yMagnificationByMouseWheel);
			void updateBarY(float upY);
			void draw();
		};
	}
}

