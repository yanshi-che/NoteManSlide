#pragma once

#include <fstream>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "boost/json.hpp"
#include "Game_Menu_MusicData.h"

using namespace boost;

namespace Game {
	namespace Menu {
		class Game_Menu_FileOperator
		{
		private:
			void getJsonVal(json::value& val);
		public:
			bool getMusicData(std::vector<std::vector<std::unique_ptr<Game_Menu_MusicData>>>& musicData);
		};
	}
}

