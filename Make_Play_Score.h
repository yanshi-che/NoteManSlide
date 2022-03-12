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
			std::string judge;
			std::uint16_t blend;
			std::int32_t color;
			std::int32_t judgeColor;
			std::uint16_t initFontSize;
			std::uint16_t judgeFontSize;
			void drawJudge();
			void drawScore();
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

