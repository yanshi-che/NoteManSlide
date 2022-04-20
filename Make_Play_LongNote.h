#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

#include "dxlib/DxLib.h"
#include "Global.h"
#include "Config_Config.h"
#include "Make_Play_Score.h"
#include "Singleton_KeyHitCheck.h"

namespace Make {
	namespace Play {
		class Make_Play_LongNote
		{
		private:
			::Singleton::Singleton_KeyHitCheck* p_keyHitCheck;
			const double startTime;//ロングノーツの始点の時間
			const double endTime;//ロングノーツの終点の時間
			const double laneXRight;
			const double laneXLeft;
			const std::uint16_t noteType;
			const std::uint16_t laneIndex;
			const std::function<void(std::uint16_t, std::uint16_t)> nextNote;//判定を同じレーンの次のノーツに移す
			const std::shared_ptr<Make_Play_Score>& p_score;//スコア表示
			std::vector<double> judgeTime;
			std::uint16_t judgeTimeCount;
			double nowJudgeTime;
			double y;
			double yUpdateBorderMin;
			double yUpdateBorderMax;
			double longNoteHeight;
			std::uint16_t alpha;
			std::int32_t noteColor;
			std::uint16_t key;
			bool done; //処理が終わったか
			bool turn; //今自分の処理順か
			bool isHit;
		public:
			Make_Play_LongNote(const double startTime,const double endTime, const double sixteenthTime, const std::uint16_t noteType,const std::uint16_t laneIndex, const double laneXRight,const double laneXLeft,const std::function<void(std::uint16_t, std::uint16_t)> nextNote, const std::shared_ptr<Make_Play_Score>& p_score);
			void check(double nowTime);
			void setTurn(bool t);
			void setDone(bool d);
			void setYUpdateBorder();
			void update(double nowTime);
			void updateKey();
			void draw(double nowTime);
		};
	}
}

