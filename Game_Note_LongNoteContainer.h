#pragma once

#include <cstdint>
#include <vector>
#include <utility>
#include "dxlib/DxLib.h"
#include "Game_Global.h"

namespace Game {
	namespace Note {
		class Game_Note_LongNoteContainer
		{
		private:
			static std::uint8_t noteWidth; //描画するノーツの幅；
			const std::uint8_t* numberOfRane; //レーンの数
			std::int32_t* y; //拍線の座標
			std::uint32_t color;
			std::vector<std::pair<bool,bool>> notesFlag;//firstはノーツがセットされているか、secondはそれが始点または終点か
			std::vector<std::uint16_t> noteX;
			std::int32_t noteHeight;
			std::uint8_t notePoint;
		public:
			Game_Note_LongNoteContainer(std::int32_t* y, const std::uint8_t* numberOfRane);
			void setLongNoteFlag(std::uint8_t raneID,bool isFirstOrLast);
			void drawLongNote();
			void setLastNoteTrue(std::uint8_t raneID);
			void setNoteHeight(std::int32_t noteHeight);
			const std::int32_t& getY();
			//std::pair<bool, bool> getLongNoteFlag();
			//std::vector<std::vector<bool>>& getAllLongNoteFlag();
		};
	}
}

inline void Game::Note::Game_Note_LongNoteContainer::drawLongNote() {
	if (*y < Game::Global::WINDOW_HEIGHT && *y>0) {
		for (int i = 0, isize = notesFlag.size(); i < isize; ++i) {
			if (notesFlag[i].first) {
				DrawBox(noteX[i] - notePoint * 0.75, *y - notePoint * 0.75, noteX[i] + notePoint * 0.75, *y + notePoint * 0.75, GetColor(255, 255, 0), true);
				if (notesFlag[i].first && notesFlag[i].second) {
					DrawBox(noteX[i] - notePoint, *y - notePoint - noteHeight, noteX[i] + notePoint, *y + notePoint, color, true);
				}
			}
		}
	}
}

