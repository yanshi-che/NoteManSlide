#pragma once

#include <memory>

#include "Make_Global.h"
#include "dxlib/DxLib.h"

namespace Make {
	namespace Singleton {
		class Make_Draw_LaneDraw
		{
		private:
			const std::uint32_t laneColor;     //レーンの色
			const std::uint8_t laneThickness;  //レーンの太さ
			float laneWidth; //レーンの幅
			std::uint8_t amountOfLane;		   //レーンの数
		public:
			Make_Draw_LaneDraw();
			void draw();
			void setamountOfLane(const std::uint8_t num);
		};

	}
}