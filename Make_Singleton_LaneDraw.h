#pragma once

#include <memory>

#include "Make_Global.h"
#include "dxlib/DxLib.h"

namespace Make {
	namespace Singleton {
		class Make_Singleton_LaneDraw
		{
		private:
			const std::uint32_t laneColor;     //���[���̐F
			const std::uint8_t laneThickness;  //���[���̑���
			float laneWidth; //���[���̕�
			std::uint8_t amountOfLane;		   //���[���̐�
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