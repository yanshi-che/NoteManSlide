#pragma once

#include <memory>

#include "Game_Global.h"
#include "dxlib/DxLib.h"

namespace Game {
	namespace Singleton {
		class Game_Singleton_LaneDraw
		{
		private:
			const std::uint32_t laneColor;     //���[���̐F
			const std::uint8_t laneThickness;  //���[���̑���
			float laneWidth; //���[���̕�
			std::uint8_t amountOfLane;		   //���[���̐�
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