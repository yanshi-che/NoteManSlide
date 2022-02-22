#pragma once

#include <memory>

#include "Make_Global.h"
#include "dxlib/DxLib.h"

namespace Make {
	namespace Draw {
		class Make_Draw_LaneDraw
		{
		private:
			const std::uint32_t laneColor;     //レーンの色
			const std::uint8_t laneThickness;  //レーンの太さ
			float laneWidth; //レーンの幅
			std::uint8_t laneAmount;		   //レーンの数
		public:
			Make_Draw_LaneDraw();
			void draw();
		};

	}
}