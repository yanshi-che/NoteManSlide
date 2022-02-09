#pragma once

#include "Windows.h"
#include <string>
#include "dxlib/DxLib.h"

namespace Make {
	namespace File {
		class Make_File_BaseFile
		{
		public:
			void openExplorer(const char* title[], const char* filter[], char(&filePath)[MAX_PATH],bool isSave) const;
		};
	}
}
