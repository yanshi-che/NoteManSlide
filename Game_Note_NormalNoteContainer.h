#pragma once
#include <cstdint>
#include <vector>
#include "dxlib/DxLib.h"
#include "Game_Global.h"


namespace Game {
	namespace Note {
		class Game_Note_NormalNoteContainer
		{
		private:
			static std::uint8_t noteWidth; //•`‰æ‚·‚éƒm[ƒc‚Ì•G
			const std::uint8_t* numberOfRane; //ƒŒ[ƒ“‚Ì”
			std::int32_t* y; //”ü‚ÌÀ•W
			std::uint32_t color;
			std::vector<bool> notesFlag;
			std::vector<std::uint16_t> noteX;
			std::uint8_t notePoint;
		public:
			Game_Note_NormalNoteContainer(std::int32_t* y,const std::uint8_t* numberOfRane);
			void setNormalNoteFlag(std::uint8_t raneID);
			void drawNote();
			bool getNormalNoteFlag(std::uint8_t raneID);
			std::vector<bool>& getAllNormalNoteFlag();
		};
	}
}

inline void Game::Note::Game_Note_NormalNoteContainer::drawNote() {
	if (*y < Game::Global::WINDOW_HEIGHT && *y>0) {
		for (int i = 0, isize = notesFlag.size(); i < isize; ++i) {
			if (notesFlag[i]) {
				DrawBox(noteX[i] - notePoint, *y - notePoint, noteX[i] + notePoint, *y + notePoint, color, true);
			}
		}
	}
}