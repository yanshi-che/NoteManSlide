#pragma once

#include <cstdint>
#include <vector>
#include <utility>
#include "dxlib/DxLib.h"
#include "Global.h"

namespace Make {
	namespace Note {
		class Make_Note_LongNoteContainer
		{
		private:
			static double noteWidth; //描画するノーツの幅；
			const std::uint16_t barID; //何小節目に属しているか
			const std::uint16_t beatID;//その小節の何番目の線か
			const double time;//曲の開始から何秒か
			const std::uint16_t laneAmount; //レーンの数
			const double& r_y; //拍線の座標
			std::uint32_t color;
			std::vector<std::pair<bool,bool>> noteFlag;//firstはノーツがセットされているか、secondはそれが始点または終点か
			std::vector<double> noteX;
			std::vector<double> noteHeight1;
			std::vector<double> noteHeight2;
			double notePointX;
			double notePointY;
			std::vector<uint16_t> noteGroup;
		public:
			Make_Note_LongNoteContainer(const std::uint16_t barID,const std::uint16_t beatID,const double& y,std::uint16_t amountOfLane,const double time);
			void setLongNoteFlag(const std::uint16_t laneID,const bool isFirstOrLast);//ノーツをセット既にセットされているなら撤去
			void drawLongNote();
			void setNoteHeight(const std::uint16_t laneID,const double noteHeight,const bool isFirst);
			void setNoteGroup(const std::uint16_t laneID,const std::uint16_t group);

			const std::uint16_t& getNoteGroup(const std::uint16_t laneID);
			const double& getY();
			const std::pair<bool, bool> getLongNoteFlag(const std::uint16_t laneID);
			const double& getTime();
			const std::uint16_t& getBarID();
			const std::uint16_t& getBeatID();
		};
	}
}

