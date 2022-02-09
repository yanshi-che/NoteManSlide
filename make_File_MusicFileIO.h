#pragma once

#include <cstdint>
#include <memory>

#include "Make_File_MusicData.h"
#include "Make_File_MusicAnalyse.h"
#include "Make_Dialog_MusicInfo.h"
namespace Make {
	namespace File {
		class Make_File_MusicFileIO
		{
		public:
			std::unique_ptr<Make_File_MusicData> getMusicFile();
		};

	}
}