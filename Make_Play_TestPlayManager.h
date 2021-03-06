#pragma once

#include <functional>
#include <deque>
#include <memory>
#include <vector>

#include "dxlib/DxLib.h"
#include "boost/json.hpp"
#include "Global.h"
#include "Config_Config.h"
#include "Make_File_MusicData.h"
#include "Make_Play_MusicPlayer.h"
#include "Make_Play_Lane.h"
#include "Make_Play_BarLine.h"
#include "Make_Play_NormalNote.h"
#include "Make_Play_LongNote.h"
#include "Make_Play_SlideNote.h"
#include "Make_Play_Score.h"
#include "Game_Play_effect.h"
#include "Game_Play_SoundEffect.h"
#include "Singleton_KeyHitCheck.h"

using namespace boost;

namespace Make {
	namespace Play {
		class Make_Play_TestPlayManager
		{
		private:
			std::shared_ptr<Make_Play_MusicPlayer> p_musicPlayer; //音楽再生用クラス
			std::shared_ptr<Make_Play_Score> p_score;//スコア表示
			std::shared_ptr<Game::Play::Game_Play_Effect> p_effect;//エフェクト
			std::shared_ptr<Game::Play::Game_Play_SoundEffect> p_soundEffect;//サウンドエフェクト
			std::unique_ptr<Make_Play_Lane> p_lane;//レーン周りの描画
			std::vector<std::unique_ptr<Make_Play_BarLine>> barLineVec; //小節線
			//各ノーツ格納用
			std::vector<std::vector<std::unique_ptr<Make_Play_NormalNote>>> normalNoteVec;//レーンごとに格納
			std::vector<std::vector<std::unique_ptr<Make_Play_LongNote>>> longNoteVec;//レーンごとに格納
			std::vector<std::vector<std::unique_ptr<Make_Play_SlideNote>>> slideNoteVec;//右0か左1かで格納
			//各レーンの処理する順番が来たノーツの格納用
			std::vector<Make_Play_NormalNote*> normalNote;
			std::vector<Make_Play_LongNote*> longNote;
			std::vector<Make_Play_SlideNote*> slideNote;
			//処理する順番のノーツのカウンタ
			std::vector<std::uint16_t> normalCount;
			std::vector<std::uint16_t> longCount;
			std::vector<std::uint16_t> slideCount;

			::Singleton::Singleton_KeyHitCheck* p_keyHitCheck;

			LONGLONG startClock;
			double nowTime;
			bool isGameStart;
			bool isMusicStart;
			bool isAuto;

			double startDelay;
			std::int32_t strColor;
			std::int32_t downColor;

			std::function<void()> drawNoteFunc;

			void nextNote(const std::uint16_t noteType, const std::uint16_t laneIndex);//判定を同じレーンの次のノーツに移す
			void draw();
			void drawAuto();
			void drawBeforeStart();
			void drawDown();
			void drawHiSpeed();
			void drawJudgeCorrection();
			void drawNote();
			void playUpdate();
			void setYUpdateBorder();
			void toggleAuto();
		public:
			Make_Play_TestPlayManager();
			void finalize();
			void initialize(const json::value& val,const std::shared_ptr<Make_Play_MusicPlayer>& p_musicPlayer,const std::shared_ptr<File::Make_File_MusicData>& p_musicData);
			void update();
			void updateKey();
			const std::function<void()> getDrawFunc();
			const std::function<void()> getUpdateFunc();
		};
	}
}

