#pragma once

#include <cstdint>
#include <functional>

#include "dxlib/DxLib.h"
#include "Make_Global.h"

namespace Make {
	namespace Play {
		class Make_Play_NormalNote
		{
		private:
			const double time;//ノーツの時間
			const double laneXRight;
			const double laneXLeft;
			const std::uint8_t noteType;
			const std::uint8_t laneIndex;
			const std::function<void(std::uint8_t , std::uint8_t)> nextNote;//判定を同じレーンの次のノーツに移す
			double y;
			std::int32_t noteColor;
			bool done; //処理が終わったか
			bool turn; //今自分の処理順か
		public:
			Make_Play_NormalNote(const double time, const std::uint8_t noteType, const std::uint8_t laneIndex, const double laneXRight,const double laneXLeft,const std::function<void(std::uint8_t, std::uint8_t)> nextNote);
			void check(double nowTime);
			void setTurn(bool t);
			void setDone(bool b);
			void update(double nowTime);
			void draw();
		};
	}
}

