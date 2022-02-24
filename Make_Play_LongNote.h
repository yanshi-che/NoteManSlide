#pragma once

#include <cstdint>
#include <functional>

#include "dxlib/DxLib.h"
#include "Make_Global.h"

namespace Make {
	namespace Play {
		class Make_Play_LongNote
		{
		private:
			const double startTime;//ロングノーツの始点の時間
			const double endTime;//ロングノーツの終点の時間
			const double laneXRight;
			const double laneXLeft;
			const std::uint8_t noteType;
			const std::uint8_t laneIndex;
			const std::function<void(std::uint8_t, std::uint8_t)> nextNote;//判定を同じレーンの次のノーツに移す
			double y;
			bool done; //処理が終わったか
			bool turn; //今自分の処理順か
		public:
			Make_Play_LongNote(const double startTime,const double endTime, const std::uint8_t noteType,const std::uint8_t laneIndex, const double laneXRight,const double laneXLeft,const std::function<void(std::uint8_t, std::uint8_t)> nextNote);
			void setTurn(bool t);
			void setDone(bool b);
			void update(double nowTime);
			void draw();
		};
	}
}

