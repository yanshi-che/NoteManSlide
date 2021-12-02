#pragma once

#include <cstdint>
#include <memory>

#include "Game_File_MusicData.h"
#include "Game_File_MusicAnalyse.h"
#include "Game_Dialog_MusicInfo.h"
namespace Game {
	namespace File {
		class Game_File_MusicFileIO
		{
		public:
			std::unique_ptr<Game_File_MusicData> getMusicFile();
		};

	}
}