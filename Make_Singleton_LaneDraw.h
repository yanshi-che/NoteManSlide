#pragma once

#include <memory>

#include "Make_Global.h"
#include "dxlib/DxLib.h"

namespace Make {
	namespace Singleton {
		class Make_Singleton_LaneDraw
		{
		private:
			const std::uint32_t laneColor;     //レーンの色
			const std::uint8_t laneThickness;  //レーンの太さ
			float laneWidth; //レーンの幅
			std::uint8_t amountOfLane;		   //レーンの数
			static Make_Singleton_LaneDraw* p_instance;
			Make_Singleton_LaneDraw();
		public:
			static Make_Singleton_LaneDraw* getInstance();
			void destroyInstance();
			void draw();
			void setamountOfLane(std::uint8_t num);
		};

	}
}