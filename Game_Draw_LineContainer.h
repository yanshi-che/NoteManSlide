#pragma once

#include <cstdint>

#include "Game_Draw_BaseDraw.h"
#include "Game_File_MusicData.h"

namespace Game {
	namespace Draw {
		class Game_Draw_LineContainer : public Game_Draw_BaseDraw
		{
		private:
			const std::uint8_t numberOfRane;
			double time;
			std::uint16_t barNumber;
			std::uint8_t quontize;
			bool notesFlag[];
		public:
			Game_Draw_LineContainer();
			void drawNote();
			void drawLine();
			void initialize() override;
			void draw() override;
		};
	}
}

