#pragma once

#include <cstdint>
#include <fstream>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "boost/json.hpp"
#include "Game_Menu_MusicData.h"
#include "Game_MusicDataShareBetweenOtherSection.h"

using namespace boost;

namespace Game {
	namespace Menu {
		struct SaveDataInit {
			bool isPerfect;
			bool isFullChain;
			bool isClear;
			bool isPlayed;
			std::uint16_t bestScore;
			SaveDataInit();
		};

		void tag_invoke(const json::value_from_tag&, json::value& jv, const SaveDataInit& s);//valu_from用のオーバロード関数

		class Game_Menu_FileOperator
		{
		private:
			void getScoreData(std::vector<std::vector<std::shared_ptr<Game_Menu_MusicData>>>& musicData);
		public:
			bool getMusicData(std::vector<std::vector<std::shared_ptr<Game_Menu_MusicData>>>& musicData);
			void saveResultData(const bool isPerfect,const  bool isFullChain,const bool isClear,const std::uint16_t score,const std::shared_ptr<Game_MusicDataShareBetweenOtherSection>& p_musicDataShare);
		};
	}
}

