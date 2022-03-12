#pragma once

#include <cstdint>

#include "dxlib/DxLib.h"
#include "Global.h"

namespace Game {
	namespace Play {
		constexpr const std::uint16_t effectHandleSize{ 15 };
		class Game_Play_Effect
		{
		private:
			double laneX[Global::LANE_AMOUNT];
			int perfectEffectHandle[effectHandleSize];
			int greatEffectHandle[effectHandleSize];
			int missEffectHandle[effectHandleSize];
			std::uint16_t effectCount[Global::LANE_AMOUNT][3];
			bool isEffect[Global::LANE_AMOUNT][3];
		public:
			Game_Play_Effect();
			void finalize();
			void setPerfect(std::uint16_t laneIndex);
			void setGreat(std::uint16_t laneIndex);
			void setMiss(std::uint16_t laneIndex);
			void draw();

			bool loadEffect();
		};
	}
}

