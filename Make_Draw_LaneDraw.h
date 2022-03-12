#pragma once

#include <memory>

#include "Global.h"
#include "dxlib/DxLib.h"

namespace Make {
	namespace Draw {
		class Make_Draw_LaneDraw
		{
		private:
			const std::uint32_t laneColor;     //レーンの色
			const std::uint32_t backColor;     //レーンの背景色
			const std::uint16_t laneThickness;  //レーンの太さ
			double laneWidth; //レーンの幅
			std::uint16_t laneAmount;		   //レーンの数
		public:
			Make_Draw_LaneDraw();
			void draw();
		};

	}
}