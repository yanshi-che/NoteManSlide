#pragma once

#include <memory>

#include "Make_Global.h"
#include "dxlib/DxLib.h"

namespace Make {
	namespace Draw {
		class Make_Draw_LaneDraw
		{
		private:
			const std::uint32_t laneColor;     //���[���̐F
			const std::uint8_t laneThickness;  //���[���̑���
			float laneWidth; //���[���̕�
			std::uint8_t laneAmount;		   //���[���̐�
		public:
			Make_Draw_LaneDraw();
			void draw();
		};

	}
}