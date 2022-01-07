#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "Game_Draw_BaseDraw.h"
#include "Game_File_MusicData.h"
#include "Game_Draw_LineContainer.h"

namespace Game {
	namespace Draw {
		class Game_Draw_BeatLineDraw : public Game_Draw_BaseDraw
		{
		private:
			File::Game_File_MusicData* musicData;
			std::vector<std::vector<std::unique_ptr<Game_Draw_LineContainer>>> barVec;
			std::int8_t y;
			std::uint8_t yMagnification;
		public:
			Game_Draw_BeatLineDraw();
			void setMusicData(File::Game_File_MusicData* data) noexcept;
			void initialize() override;
			//void finalize() override;
			void draw() override;
		};
	}
}
