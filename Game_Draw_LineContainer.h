#pragma once

#include <cstdint>
#include <vector>
#include <cmath>
#include <memory>
#include "dxlib/DxLib.h"
#include "Game_Draw_BaseDraw.h"
#include "Game_Note_NoteContainer.h"

namespace Game {
	namespace Draw {
		class Game_Draw_LineContainer : public Game_Draw_BaseDraw
		{
		private:
			enum noteTypes {
				Normal = 1,
				Long,
			};
			static std::uint8_t noteType; //入力するノーツのタイプ。１の時は普通のノーツ。2の時はロングノーツ
			const std::uint16_t barID; //何小節目に属しているか
			const std::uint16_t barNumber;//その小節の何番目の線か
			const double time;//曲の開始から何秒か
			const std::int32_t yMax;//座標の最大値
			const std::int32_t yMin;//座標の最小値
			const std::uint8_t* numberOfRane; //レーンの数
			std::int32_t color;//拍線の色
			std::uint8_t lineThickness; //拍線の太さ
			std::int32_t y; //拍線の座標
			std::vector<std::unique_ptr<Note::Game_Note_NoteContainer>> notes;
		public:
			Game_Draw_LineContainer(std::uint16_t bID, const std::uint8_t* numberOfRane, double t, std::uint16_t bNum, std::int32_t y,std::int32_t yMax);
			void drawNotes() noexcept;
			void drawLine() noexcept;
			void drawBarID() noexcept;
			static void setNoteType(std::uint8_t type) noexcept;
			void updateY(std::int16_t y) noexcept;
			void draw() override;
		};
	}
}

