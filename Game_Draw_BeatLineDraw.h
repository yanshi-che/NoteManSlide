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
			std::uint8_t quontize;
			std::vector<std::vector<std::unique_ptr<Game_Draw_LineContainer>>> barVec;
		public:
			Game_Draw_BeatLineDraw();
			void setMusicData(File::Game_File_MusicData* data) noexcept;
			void setQuontize(std::uint8_t quon) noexcept;
			void initialize() override;
			void draw() override;
		};
	}
}
