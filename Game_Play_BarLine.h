#pragma once

#include "dxlib/DxLib.h"
#include "Global.h"
#include "Config_Config.h"

namespace Game {
	namespace Play {
		class Game_Play_BarLine
		{
		private:
			double time;
			double y;
			double yUpdateBorderMin;
			double yUpdateBorderMax;
			std::int32_t color;
		public:
			Game_Play_BarLine(const double time);
			void setYUpdateBorder();
			void update(double nowTime);
			void draw(double nowTime);
		};
	}
}

