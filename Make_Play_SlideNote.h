#pragma once

#include <cstdint>
#include <functional>

#include "dxlib/DxLib.h"
#include "Make_Global.h"

namespace Make {
	namespace Play {
		class Make_Play_SlideNote
		{
		private:
			const double time;//ノーツの時間
			double y;
			const double laneXRight;
			const double laneXLeft;
			const std::uint8_t rightOrLeft;//右なら0 左なら1
			const std::uint8_t directionRightOrLeft;//右向きなら0 左向きなら1
			const std::uint8_t noteType;
			const std::uint8_t slideLaneIndexStart;//スライドノーツの開始レーン
			const std::uint8_t slideLaneIndexEnd;//スライドノーツの終了レーン
			const std::function<void(std::uint8_t, std::uint8_t)> nextNote;//判定を次のノーツに移す
			bool done; //処理が終わったか
			bool turn; //今自分の処理順か
		public:
			Make_Play_SlideNote(const double time, const std::uint8_t noteType, const double laneXRight, const double laneXLeft,const std::uint8_t rightOrLeft, const std::uint8_t directionRightOrLeft,const std::uint8_t slideLaneIndexStart,const std::uint8_t slideLaneIndexEnd,const std::function<void(std::uint8_t, std::uint8_t)> nextNote);
			void setTurn(bool t);
			void setDone(bool b);
			void update(double nowTime);
			void draw();
		};
	}
}

