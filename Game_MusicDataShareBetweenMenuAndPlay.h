#pragma once

#include <memory>

#include "Game_Menu_MusicData.h"

namespace Game {
	class Game_MusicDataShareBetweenMenuAndPlay
	{
	private:
		std::shared_ptr<Menu::Game_Menu_MusicData> p_musicData;
	public:
		Game_MusicDataShareBetweenMenuAndPlay();
		void setMusicData(std::shared_ptr<Menu::Game_Menu_MusicData>& p_musicData);
		Menu::Game_Menu_MusicData* getMusicData();
	};
}

