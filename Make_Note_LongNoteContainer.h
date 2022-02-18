#pragma once

#include <cstdint>
#include <vector>
#include <utility>
#include "dxlib/DxLib.h"
#include "Make_Global.h"

namespace Make {
	namespace Note {
		class Make_Note_LongNoteContainer
		{
		private:
			static float noteWidth; //描画するノーツの幅；
			const std::uint16_t barID; //何小節目に属しているか
			const std::uint8_t beatID;//その小節の何番目の線か
			const float time;//曲の開始から何秒か
			const std::uint8_t amountOfLane; //レーンの数
			const float& r_y; //拍線の座標
			std::uint32_t color;
			std::vector<std::pair<bool,bool>> noteFlag;//firstはノーツがセットされているか、secondはそれが始点または終点か
			std::vector<float> noteX;
			std::vector<float> noteHeight1;
			std::vector<float> noteHeight2;
			float notePointX;
			float notePointY;
			std::vector<uint16_t> noteGroup;
		public:
			Make_Note_LongNoteContainer(const std::uint16_t barID,const std::uint8_t beatID,const float& y,std::uint8_t amountOfLane,const float time);
			void setLongNoteFlag(const std::uint8_t laneID,const bool isFirstOrLast);//ノーツをセット既にセットされているなら撤去
			void drawLongNote();
			void setNoteHeight(const std::uint8_t laneID,const float noteHeight,const bool isFirst);
			void setNoteGroup(const std::uint8_t laneID,const std::uint16_t group);

			const std::uint16_t& getNoteGroup(const std::uint8_t laneID);
			const float& getY();
			const std::pair<bool, bool> getLongNoteFlag(const std::uint8_t laneID);
			const float& getTime();
			const std::uint16_t& getBarID();
			const std::uint8_t& getBeatID();
		};
	}
}

