#pragma once

#include <boost/json.hpp>
#include <cstdint>
#include <deque>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "Make_Dialog_FailFile.h"
#include "Make_File_BaseFile.h"
#include "Make_File_MusicData.h"
#include "Make_File_FileStructData.h"
#include "Make_Singleton_NoteManager.h"
#include "Make_Global.h"

using namespace boost;

namespace Make{
	namespace File {
		class Make_File_JsonIO : public Make_File_BaseFile
		{
		private:
			void getFilePath(char (&filePath)[MAX_PATH]);
		public:
			void saveNewJson(const std::shared_ptr<Make_File_MusicData>& p_musicData);
		};
	}
}

