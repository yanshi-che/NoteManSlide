#pragma once

#include <cstdint>
#include <memory>

#include "Game_File_BaseFile.h"
#include "Game_File_MusicData.h"
#include "Game_File_MusicAnalyse.h"
namespace Game {
	namespace File {
		class Game_File_MusicFileIO :public Game::File::Game_File_BaseFile
		{
		private:
			void inputMusicInfo(std::uint8_t& bpm,double& totalMinutes,double& beginDlay);
		public:
			std::unique_ptr<Game_File_MusicData> openMusicFile();
		};

	}
}