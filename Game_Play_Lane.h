#pragma once

#include <cstdint>

#include "dxlib/DxLib.h"
#include "Global.h"
#include "Config_Config.h"
#include "Singleton_KeyHitCheck.h"

namespace Game {
	namespace Play {
		constexpr const double keyHitLineWidth{ 1.0 };
		class Game_Play_Lane
		{
		private:
			double laneX[Global::LANE_AMOUNT + 1];
			double laneWidth;
			std::int32_t laneColor;
			std::int32_t backColor;
			std::int32_t judgeLineColor;
			std::int32_t keyHitColor;

			Singleton::Singleton_KeyHitCheck* p_keyHitCheck;

			void drawLane();
			void drawBack();
			void drawJudgeLine();
			void drawKeyHitLane();
		public:
			Game_Play_Lane();
			void draw();
		};
	}
}

