#pragma once

#include <memory>
#include "Game_Draw_BaseDraw.h"
#include "dxlib/DxLib.h"

namespace Game {
	namespace Singleton {
		class Game_Singleton_LaneDraw :public Draw::Game_Draw_BaseDraw
		{
		private:
			const std::uint32_t laneColor;     //レーンの色
			const std::uint8_t laneThickness;  //レーンの太さ
			std::uint16_t laneWidth; //レーンの幅
			std::uint8_t amountOfLane;		   //レーンの数
			static Game_Singleton_LaneDraw* p_instance;
			Game_Singleton_LaneDraw();
		public:
			static Game_Singleton_LaneDraw* getInstance();
			void destroyInstance();
			void draw() override;
			void setamountOfLane(std::uint8_t num);
		};

	}
}