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
			static std::uint8_t noteWidth; //描画するノーツの幅；
			const std::uint16_t& r_barID; //何小節目に属しているか
			const std::uint16_t& r_beatID;//その小節の何番目の線か
			const double& r_time;//曲の開始から何秒か
			const std::uint8_t& r_amountOfLane; //レーンの数
			const std::int32_t& r_y; //拍線の座標
			std::uint32_t color;
			std::vector<bool> notesFlag;
			std::vector<std::uint16_t> noteX;
			std::uint8_t notePoint;
		public:
			Game_Note_NormalNoteContainer(const std::uint16_t& barID, const std::uint16_t& beatID,const std::int32_t& y,const std::uint8_t& amountOfLane,const double& time);
			void setNormalNoteFlag(std::uint8_t laneID);
			void drawNote();
			const bool getNormalNoteFlag(std::uint8_t laneID);
			const std::vector<bool>& getAllNormalNoteFlag();
			const double& getTime();
			const std::uint16_t& getBarID();
			const std::uint16_t& getBeatID();
		};
	}
}