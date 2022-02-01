#pragma once

#include <memory>
#include "Game_Draw_BaseDraw.h"
#include "dxlib/DxLib.h"

namespace Game {
	namespace Singleton {
		class Game_Singleton_LaneDraw :public Draw::Game_Draw_BaseDraw
		{
		private:
			const std::uint32_t laneColor;     //���[���̐F
			const std::uint8_t laneThickness;  //���[���̑���
			std::uint16_t laneWidth; //���[���̕�
			std::uint8_t amountOfLane;		   //���[���̐�
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