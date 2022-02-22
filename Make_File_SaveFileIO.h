#pragma once

#include <boost/json.hpp>
#include <cstdint>
#include <deque>
#include <fstream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "Make_Dialog_SaveFile.h"
#include "Make_Dialog_FailFile.h"
#include "Make_Draw_BeatLineManager.h"
#include "Make_Draw_LineContainer.h"
#include "Make_File_BaseFile.h"
#include "Make_File_MusicData.h"
#include "Make_File_FileStructData.h"
#include "Make_Note_NoteManager.h"
#include "Make_Play_MusicPlayer.h"

using namespace boost;

namespace Make {
	namespace File {
		class Make_File_SaveFileIO
		{
		private:
			void getFilePath(char(&filePath)[MAX_PATH]);
			void getSaveFilePath(char(&saveFilePath)[MAX_PATH], char(&musicFilePath)[MAX_PATH]);
		public:
			void writeSaveData(const std::shared_ptr<Make_File_MusicData>& p_musicData, const std::shared_ptr <Draw::Make_Draw_BeatLineManager>& p_beatLine);
			std::tuple<std::unique_ptr<Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>, json::value> readSaveData();
		};
	}
}

