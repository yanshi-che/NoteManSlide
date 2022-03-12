#pragma once

#include <memory>

#include "Global.h"
#include "dxlib/DxLib.h"

namespace Make {
	namespace Draw {
		class Make_Draw_LaneDraw
		{
		private:
			const std::uint32_t laneColor;     //���[���̐F
			const std::uint32_t backColor;     //���[���̔w�i�F
			const std::uint16_t laneThickness;  //���[���̑���
			double laneWidth; //���[���̕�
			std::uint16_t laneAmount;		   //���[���̐�
		public:
			Make_Draw_LaneDraw();
			void draw();
		};

	}
}