#pragma once

#include <cstdint>
#include <vector>

#include "Game_Draw_BaseDraw.h"
#include "Game_File_MusicData.h"

namespace Game {
	namespace Draw {
		class Game_Draw_LineContainer : public Game_Draw_BaseDraw
		{
		private:
			const std::uint16_t barID; //何小節目に属しているか
			const std::uint8_t numberOfRane;//レーンの数
			const double time;//曲の開始から何秒か
			const std::uint16_t barNumber;//その小節の何番目の線か
			std::int32_t color;
			std::uint8_t thickness;
			std::vector<bool> notesFlag; //ノーツががセットされたかどうか
			std::int32_t y;
		public:
			Game_Draw_LineContainer(std::uint16_t bID, std::uint8_t numOfRane, double t, std::uint16_t bNum, std::int32_t y);
			void drawNote() noexcept;
			void drawLine() noexcept;
			void draw() override;
		};
	}
}

