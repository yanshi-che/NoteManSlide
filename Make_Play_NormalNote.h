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
		class Make_Play_NormalNote
		{
		private:
			Singleton::Make_Singleton_KeyHitCheck* p_keyHitCheck;
			const double time;//ノーツの時間
			const double laneXRight;
			const double laneXLeft;
			const std::uint8_t noteType;
			const std::uint8_t laneIndex;
			const std::function<void(std::uint8_t , std::uint8_t)> nextNote;//判定を同じレーンの次のノーツに移す
			const std::shared_ptr<Make_Play_Score>& p_score;//スコア表示
			double y;
			std::int32_t noteColor;
			std::uint16_t key;
			bool done; //処理が終わったか
			bool turn; //今自分の処理順か
		public:
			Make_Play_NormalNote(const double time, const std::uint8_t noteType, const std::uint8_t laneIndex, const double laneXRight,const double laneXLeft,const std::function<void(std::uint8_t, std::uint8_t)> nextNote, std::shared_ptr<Make_Play_Score>& p_score);
			void check(double nowTime);
			void setTurn(bool t);
			void setDone(bool d);
			void update(double nowTime);
			void updateKey();
			void draw();
		};
	}
}

