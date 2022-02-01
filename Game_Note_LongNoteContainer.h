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
			const std::uint16_t& r_barID; //何小節目に属しているか
			const std::uint16_t& r_beatID;//その小節の何番目の線か
			const double& r_time;//曲の開始から何秒か
			const std::uint8_t& r_amountOfLane; //レーンの数
			const std::int32_t& r_y; //拍線の座標
			std::uint32_t color;
			std::vector<std::pair<bool,bool>> notesFlag;//firstはノーツがセットされているか、secondはそれが始点または終点か
			std::vector<std::uint16_t> notesX;
			std::vector<int32_t> notesHeight;
			std::uint8_t notePoint;
			std::vector<uint16_t> notesGroup;
		public:
			Game_Note_LongNoteContainer(const std::uint16_t& barID,const std::uint16_t& beatID,const std::int32_t& y, const std::uint8_t& amountOfLane,const double& time);
			void setLongNoteFlag(std::uint8_t laneID,bool isFirstOrLast);//ノーツをセット既にセットされているなら撤去
			void drawLongNote();
			void setLongNoteFlagFirstOrLast(std::uint8_t laneID,bool is);
			void setNoteHeight(std::uint8_t laneID, std::int32_t noteHeight);
			void setNoteGroup(std::uint8_t laneID, std::uint16_t group);
			const std::uint16_t& getNoteGroup(std::uint8_t laneID);
			const std::int32_t& getY();
			const std::pair<bool, bool> getLongNoteFlag(std::uint8_t laneID);
			const std::vector<std::pair<bool, bool>>& getAllLongNoteFlag();
			const double& getTime();
			const std::uint16_t& getBarID();
			const std::uint16_t& getBeatID();
		};
	}
}

