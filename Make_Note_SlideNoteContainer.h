#pragma once

#include <cstdint>
#include <utility>
#include <vector>

#include "dxlib/DxLib.h"
#include "Global.h"

namespace Make {
	namespace Note {
		class Make_Note_SlideNoteContainer
		{
		private:
			static std::uint16_t lineThickness;
			const std::uint16_t barID; //何小節目に属しているか
			const std::uint16_t beatID;//その小節の何番目の線か
			const double time;//曲の開始から何秒か
			const std::uint16_t laneAmount; //レーンの数
			const double& r_y; //拍線の座標
			std::uint32_t colorRR;
			std::uint32_t colorRL;
			std::uint32_t colorLR;
			std::uint32_t colorLL;
			std::pair<bool,bool> noteFlag;//firstが右(赤)secondが左(青)
			std::pair<bool, bool> noteDirectionRightOrLeft;//firstが右secondが左 trueなら右falseなら左
			std::vector<double> laneX;
			std::pair<std::pair<std::uint16_t,std::uint16_t>,std::pair<std::uint16_t, std::uint16_t>> noteStartAndEndLane;//firstが右secondが左,firstがstart,secondがend
			double arrowWidthBetween; //描画する矢印同士の幅

			void drawArrow();
		public:
			Make_Note_SlideNoteContainer(const std::uint16_t barID,const std::uint16_t beatID, const double& y,const std::uint16_t amountOfLane,const double time);
			void drawSlideNote();
			void setSlideNoteFlag(const std::uint16_t laneIDStart,const std::uint16_t laneIDEnd,const bool right, const bool isDirectionRight);//ノーツをセット既にセットされているなら撤去

			const std::pair<bool,bool>& getSlideNoteFlag();//trueなら右をfalseなら左を
			const std::pair<bool, bool>& getSlideNoteDirectionRightOrLeft();//firstが右secondが左 trueなら右向きfalseなら左向き
			const std::pair<std::pair<std::uint16_t, std::uint16_t>, std::pair<std::uint16_t, std::uint16_t>>& getNoteStartAndEnd();
			const double& getTime();
			const std::uint16_t& getBarID();
			const std::uint16_t& getBeatID();
		};
	}
}

