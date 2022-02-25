#pragma once

#include <cstdint>
#include <functional>
#include <memory>

#include "dxlib/DxLib.h"
#include "Make_Global.h"
#include "Make_Play_Score.h"
#include "Make_Singleton_KeyHitCheck.h"

namespace Make {
	namespace Play {
		class Make_Play_SlideNote
		{
		private:
			Singleton::Make_Singleton_KeyHitCheck* p_keyHitCheck;
			const double time;//ノーツの時間
			double y;
			const double laneXStart;
			const double laneXEnd;
			const double laneWidth;
			const double arrowWidthBetween;
			const std::uint8_t rightOrLeft;//右なら0 左なら1
			const std::uint8_t directionRightOrLeft;//右向きなら0 左向きなら1
			const std::uint8_t noteType;
			const std::uint8_t slideLaneIndexStart;//スライドノーツの開始レーン
			const std::uint8_t slideLaneIndexEnd;//スライドノーツの終了レーン
			const std::function<void(std::uint8_t, std::uint8_t)> nextNote;//判定を次のノーツに移す
			const std::shared_ptr<Make_Play_Score>& p_score;//スコア表示
			std::uint32_t colorR;
			std::uint32_t colorL;
			std::uint16_t key;
			bool done; //処理が終わったか
			bool turn; //今自分の処理順か

			void drawLine();
			void drawArrow();
		public:
			Make_Play_SlideNote(const double time, const std::uint8_t noteType, const double laneXStart, const double laneXEnd, const double laneWidth,const double arrowWidthBetween,const std::uint8_t rightOrLeft, const std::uint8_t directionRightOrLeft,const std::uint8_t slideLaneIndexStart,const std::uint8_t slideLaneIndexEnd,const std::function<void(std::uint8_t, std::uint8_t)> nextNote, const std::shared_ptr<Make_Play_Score>& p_score);
			void check(double nowTime);
			void setTurn(bool t);
			void setDone(bool d);
			void update(double nowTime);
			void draw();
		};
	}
}

