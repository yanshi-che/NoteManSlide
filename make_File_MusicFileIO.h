#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

#include "Make_File_MusicData.h"
#include "Make_File_MusicAnalyse.h"
#include "Make_Dialog_MusicInfo.h"
#include "Make_Dialog_FailFile.h"
#include "Make_Play_MusicPlayer.h"

namespace Make {
	namespace File {
		class Make_File_MusicFileIO
		{
		public:
			std::pair<std::unique_ptr<Make_File_MusicData>,std::unique_ptr<Play::Make_Play_MusicPlayer>> getMusicFile();
		};

	}
}