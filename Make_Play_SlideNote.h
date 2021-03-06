#pragma once

#include <cstdint>
#include <functional>
#include <memory>

#include "dxlib/DxLib.h"
#include "Global.h"
#include "Config_Config.h"
#include "Make_Play_Score.h"
#include "Game_Play_effect.h"
#include "Game_Play_SoundEffect.h"
#include "Singleton_KeyHitCheck.h"

namespace Make {
	namespace Play {
		class Make_Play_SlideNote
		{
		private:
			::Singleton::Singleton_KeyHitCheck* p_keyHitCheck;
			const double time;//ノーツの時間
			double y;
			double yUpdateBorderMin;
			double yUpdateBorderMax;
			const double laneXStart;
			const double laneXEnd;
			const double laneWidth;
			const double arrowWidthBetween;
			const std::uint16_t rightOrLeft;//右なら0 左なら1
			const std::uint16_t directionRightOrLeft;//右向きなら0 左向きなら1
			const std::uint16_t noteType;
			const std::uint16_t slideLaneIndexStart;//スライドノーツの開始レーン
			const std::uint16_t slideLaneIndexEnd;//スライドノーツの終了レーン
			const std::function<void(std::uint16_t, std::uint16_t)> nextNote;//判定を次のノーツに移す
			const std::shared_ptr<Make_Play_Score>& p_score;//スコア表示
			const std::shared_ptr<Game::Play::Game_Play_Effect>& p_effect;//エフェクト
			const std::shared_ptr<Game::Play::Game_Play_SoundEffect>& p_soundEffect;//サウンドエフェクト
			std::uint32_t colorRR;
			std::uint32_t colorRL;
			std::uint32_t colorLR;
			std::uint32_t colorLL;
			std::uint16_t key;
			bool done; //処理が終わったか
			bool turn; //今自分の処理順か
			bool isAuto;

			void drawLine();
			void drawArrow();
		public:
			Make_Play_SlideNote(const double time, const std::uint16_t noteType, const double laneXStart, const double laneXEnd, const double laneWidth,const double arrowWidthBetween,const std::uint16_t rightOrLeft, const std::uint16_t directionRightOrLeft,const std::uint16_t slideLaneIndexStart,const std::uint16_t slideLaneIndexEnd,const std::function<void(std::uint16_t, std::uint16_t)> nextNote, const std::shared_ptr<Make_Play_Score>& p_score, const std::shared_ptr<Game::Play::Game_Play_Effect>& p_effect, const std::shared_ptr<Game::Play::Game_Play_SoundEffect>& p_soundEffect);
			void check(double nowTime);
			void setTurn(bool t);
			void setDone(bool d);
			void setAuto();
			void setYUpdateBorder();
			void update(double nowTime);
			void updateKey();
			void draw(double nowTime);
		};
	}
}

