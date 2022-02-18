#pragma once
#include <cstdint>
#include <vector>
#include "dxlib/DxLib.h"
#include "Make_Global.h"


namespace Make {
	namespace Note {
		class Make_Note_NormalNoteContainer
		{
		private:
			static float noteWidth; //描画するノーツの幅；
			const std::uint16_t barID; //何小節目に属しているか
			const std::uint8_t beatID;//その小節の何番目の線か
			const float time;//曲の開始から何秒か
			const std::uint8_t amountOfLane; //レーンの数
			const float& r_y; //拍線の座標
			std::uint32_t color;
			std::vector<bool> noteFlag;
			std::vector<float> noteX;
			float notePointX;
			float notePointY;
		public:
			Make_Note_NormalNoteContainer(const std::uint16_t barID,const std::uint8_t beatID,const float& y,const std::uint8_t amountOfLane,const float time);
			void setNormalNoteFlag(const std::uint8_t laneID);
			void drawNote();
			const bool getNormalNoteFlag(const std::uint8_t laneID);
			const float& getTime();
			const std::uint16_t& getBarID();
			const std::uint8_t& getBeatID();
		};
	}
}