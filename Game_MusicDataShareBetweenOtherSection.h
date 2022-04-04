#pragma once

#include <cstdint>
#include <memory>

#include "Game_Menu_MusicData.h"

namespace Game {
	class Game_MusicDataShareBetweenOtherSection
	{
	private:
		std::shared_ptr<Menu::Game_Menu_MusicData> p_musicData;
		std::uint16_t difficulty;

	public:
		Game_MusicDataShareBetweenOtherSection();
		void setMusicData(std::shared_ptr<Menu::Game_Menu_MusicData>& p_musicData);
		void setDifficulty(std::uint16_t difficulty);

		Menu::Game_Menu_MusicData* getMusicData();
		std::uint16_t getDifficulty();
	};
}

