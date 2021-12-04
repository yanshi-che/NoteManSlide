#pragma once

#include <memory>
#include "Game_Draw_RaneDraw.h"
#include "Game_Draw_BeatLineDraw.h"

namespace Game {
	namespace Draw {
		class Game_Draw_DrawFactory
		{
		private:
			std::unique_ptr<Game_Draw_RaneDraw> rane;
			std::unique_ptr<Game_Draw_BeatLineDraw> beatLine;
		public:
			Game_Draw_DrawFactory();
			Game_Draw_RaneDraw* getRaneDrawInstance();
			Game_Draw_BeatLineDraw* getBeatLineDrawInstance();
		};
	}
}

