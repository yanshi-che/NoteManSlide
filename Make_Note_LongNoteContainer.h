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
			Make_Note_LongNoteContainer(std::uint16_t barID,std::uint8_t beatID,const float& y,std::uint8_t amountOfLane,float time);
			void setLongNoteFlag(std::uint8_t laneID,bool isFirstOrLast);//ノーツをセット既にセットされているなら撤去
			void drawLongNote();
			void setNoteHeight(std::uint8_t laneID, float noteHeight,bool isFirst);
			void setNoteGroup(std::uint8_t laneID, std::uint16_t group);

			const std::uint16_t& getNoteGroup(std::uint8_t laneID);
			const float& getY();
			const std::pair<bool, bool> getLongNoteFlag(std::uint8_t laneID);
			const float& getTime();
			const std::uint16_t& getBarID();
			const std::uint8_t& getBeatID();
		};
	}
}

