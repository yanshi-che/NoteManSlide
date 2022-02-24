#pragma once

#include <cstdint>
#include <string>

#include "dxlib/DxLib.h"

namespace Make {
	namespace Play {
		class Make_Play_Score
		{
		private:
			std::uint16_t perfect;
			std::uint16_t great;
			std::uint16_t miss;
			std::string p;
			std::string g;
			std::string m;
			std::int32_t color;
		public:
			Make_Play_Score();
			void draw();
			void minusPerfect();
			void minusGreat();
			void minusMiss();
			void plusPerfect();
			void plusGreat();
			void plusMiss();
			void resetScore();
		};
	}
}

