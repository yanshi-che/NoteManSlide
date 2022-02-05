#pragma once

#include <memory>

#include "Game_Global.h"
#include "dxlib/DxLib.h"

namespace Game {
	namespace Singleton {
		class Game_Singleton_LaneDraw
		{
		private:
			const std::uint32_t laneColor;     //レーンの色
			const std::uint8_t laneThickness;  //レーンの太さ
			float laneWidth; //レーンの幅
			std::uint8_t amountOfLane;		   //レーンの数
			static Game_Singleton_LaneDraw* p_instance;
			Game_Singleton_LaneDraw();
		public:
			static Game_Singleton_LaneDraw* getInstance();
			void destroyInstance();
			void draw();
			void setamountOfLane(std::uint8_t num);
		};

	}
}