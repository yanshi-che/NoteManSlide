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
		public:
			bool getMusicData(std::vector<std::vector<std::shared_ptr<Game_Menu_MusicData>>>& musicData);
		};
	}
}

