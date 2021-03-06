#pragma once
#include <cstdint>
#include <vector>
#include "dxlib/DxLib.h"
#include "Global.h"


namespace Make {
	namespace Note {
		class Make_Note_NormalNoteContainer
		{
		private:
			static double noteWidth; //描画するノーツの幅；
			const std::uint16_t barID; //何小節目に属しているか
			const std::uint16_t beatID;//その小節の何番目の線か
			const double time;//曲の開始から何秒か
			const std::uint16_t laneAmount; //レーンの数
			const double& r_y; //拍線の座標
			std::uint32_t color;
			std::vector<bool> noteFlag;
			std::vector<double> noteX;
			double notePointX;
			double notePointY;
		public:
			Make_Note_NormalNoteContainer(const std::uint16_t barID,const std::uint16_t beatID,const double& y,const std::uint16_t amountOfLane,const double time);
			void setNormalNoteFlag(const std::uint16_t laneID);
			void drawNote();
			const bool getNormalNoteFlag(const std::uint16_t laneID);
			const double& getTime();
			const std::uint16_t& getBarID();
			const std::uint16_t& getBeatID();
		};
	}
}