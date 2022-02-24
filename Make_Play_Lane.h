#pragma once

#include <cstdint>

#include "dxlib/DxLib.h"
#include "Make_Global.h"
#include "Make_Singleton_KeyHitCheck.h"

namespace Make {
	namespace Play {
		class Make_Play_Lane
		{
		private:
			double laneX[Global::LANE_AMOUNT + 1];
			std::int32_t laneColor;
			std::int32_t backColor;
			std::int32_t judgeLineColor;
			std::int32_t keyHitColor;

			Singleton::Make_Singleton_KeyHitCheck* keyHitCheck;

			void drawLane();
			void drawBack();
			void drawJudgeLine();
			void drawKeyHitLane();
			void drawDown();
		public:
			Make_Play_Lane();
			void draw();
		};
	}
}
