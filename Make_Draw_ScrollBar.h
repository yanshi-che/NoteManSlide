#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <functional>

#include "dxlib/DxLib.h"
#include "Make_Singleton_MouseOperationCheck.h"
#include "Make_Draw_LineContainer.h"

namespace Make {
	namespace Draw {
		constexpr const double backWidth{ 20.0 };//スクロールバーの背景の幅
		constexpr const double barWidth{15.0};//スクロールバーの幅
		constexpr const double barHeightMin{ 40.0 };//スクロールバーの最低限の長さ
		constexpr const double arrowWidthX{ 10.0 };//矢印の底辺
		constexpr const double arrowWidthYAndSpace{ 5.0 };//矢印の高さとスクロールバーの背景の端からの距離
		constexpr const double yScrMax{ Global::WINDOW_HEIGHT - backWidth };//スクロールバー座標の最大値
		constexpr const double yScrMin{ backWidth };//スクロールバー座標の最小値
		class Make_Draw_ScrollBar
		{
		private:
			Singleton::Make_Singleton_MouseOperationCheck* p_mouseCheck;
			std::vector<std::vector<std::shared_ptr<Make_Draw_LineContainer>>>& barVec;
			int mouseX, mouseY;//マウスクリックの座標格納用の変数
			double  widthMaxOnClick, widthMinOnClick;//barをクリックしているときの最大値最小値を求めるための変数
			double barYBefore;//ひとつ前のマウスのy座標を格納
			double barHeight;//バーの長さ
			double scrollWidthRate;//スクロールバーと実際の画面との比率
			const double& yMagnificationByMouseWheel;//マウスホイール入力に対する画面移動の倍率
			std::int32_t backColor;
			std::int32_t barColor;
			std::int32_t arrowUpColor;
			std::int32_t arrowDownColor;
			double y;//barのy座標
			bool clickObserver;//クリックの制御用
			double barPointX[2];//barのx座標格納
			double arrowPointX[3];//上下矢印の頂点のｘ座標
			double arrowPointY[4];//上下矢印の頂点のｙ座標
			std::function<void()> function;//barもしくはarrowのfunctionの格納

			void arrowFunction(const bool isUp);
			void barFunction();
			void borderCheck();
			void clickCheck();
			void drawBack();
			void drawArrow();
			void drawBar();
			void setBarY(const double sY);
			void updateLineContainerY(const double y);
		public:
			Make_Draw_ScrollBar(const double scrollWidth,std::vector<std::vector<std::shared_ptr<Make_Draw_LineContainer>>>& barVec,const double& yMagnificationByMouseWheel);
			void draw();
			void updateBarY(const double upY);
		};
	}
}


