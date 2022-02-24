#pragma once

#include <cstdint>
#include <utility>
#include <vector>

#include "dxlib/DxLib.h"
#include "Make_Global.h"

namespace Make {
	namespace Note {
		constexpr const std::uint8_t arrowNumInLane{ 4 };//1レーンあたりの矢印の数
		constexpr const double arrowHeight{ 8.0 };//描画する矢印の幅；
		constexpr const double arrowLength{ 8.0 };//描画する矢印の幅；
		class Make_Note_SlideNoteContainer
		{
		private:
			static std::uint8_t lineThickness;
			const std::uint16_t barID; //何小節目に属しているか
			const std::uint8_t beatID;//その小節の何番目の線か
			const double time;//曲の開始から何秒か
			const std::uint8_t laneAmount; //レーンの数
			const double& r_y; //拍線の座標
			std::uint32_t colorR;
			std::uint32_t colorL;
			std::pair<bool,bool> noteFlag;//firstが右(赤)secondが左(青)
			std::pair<bool, bool> noteDirectionRightOrLeft;//firstが右secondが左 trueなら右falseなら左
			std::vector<double> laneX;
			std::pair<std::pair<std::uint8_t,std::uint8_t>,std::pair<std::uint8_t, std::uint8_t>> noteStartAndEndLane;//firstが右secondが左,firstがstart,secondがend
			double arrowWidthBetween; //描画する矢印同士の幅

			void drawArrow();
		public:
			Make_Note_SlideNoteContainer(const std::uint16_t barID,const std::uint8_t beatID, const double& y,const std::uint8_t amountOfLane,const double time);
			void drawSlideNote();
			void setSlideNoteFlag(const std::uint8_t laneIDStart,const std::uint8_t laneIDEnd,const bool right, const bool isDirectionRight);//ノーツをセット既にセットされているなら撤去

			const std::pair<bool,bool>& getSlideNoteFlag();//trueなら右をfalseなら左を
			const std::pair<bool, bool>& getSlideNoteDirectionRightOrLeft();//firstが右secondが左 trueなら右向きfalseなら左向き
			const std::pair<std::pair<std::uint8_t, std::uint8_t>, std::pair<std::uint8_t, std::uint8_t>>& getNoteStartAndEnd();
			const double& getTime();
			const std::uint16_t& getBarID();
			const std::uint8_t& getBeatID();
		};
	}
}

