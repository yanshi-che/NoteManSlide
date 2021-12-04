#pragma once

#include <cstdint>

#include "Game_Draw_BaseDraw.h"
#include "Game_File_MusicData.h"

namespace Game {
	namespace Draw {
		class Game_Draw_BeatLineDraw : public Game_Draw_BaseDraw
		{
		private:
			File::Game_File_MusicData* musicData;
			std::uint8_t quontize;
		public:
			void setMusicData(File::Game_File_MusicData* data) noexcept;
			void setQuontize(std::uint8_t quon) noexcept;
			void draw() override;
		};
	}
}
