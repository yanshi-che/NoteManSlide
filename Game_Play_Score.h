#pragma once

#include <cstdint>
#include <string>

#include "dxlib/DxLib.h"

namespace Game {
	namespace Play {
		class Game_Play_Score
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
			std::int32_t edgeColor;
			std::int32_t judgeColor;
			std::uint16_t initFontSize;
			std::uint16_t judgeFontSize;
			int font;

			void drawJudge();
			void drawScore();
		public:
			Game_Play_Score(int font);
			void draw();
			void plusPerfect();
			void plusGreat();
			void plusMiss();

			std::uint16_t getPerfect();
			std::uint16_t getGreat();
			std::uint16_t getMiss();
		};
	}
}

