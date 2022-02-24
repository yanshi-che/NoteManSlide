#pragma once

#include "dxlib/DxLib.h"
#include "Make_Global.h"

namespace Make {
	namespace Play {
		class Make_Play_BarLine
		{
		private:
			double time;
			double y;
			std::int32_t color;
		public:
			Make_Play_BarLine(const double time);
			void update(double nowTime);
			void draw();
		};
	}
}

