#pragma once

#include <functional>
#include <fstream>
#include <deque>
#include <memory>
#include <vector>

#include "dxlib/DxLib.h"
#include "boost/json.hpp"
#include "Task.h"
#include "Global.h"
#include "Config_Config.h"
#include "Game_MusicDataShareBetweenOtherSection.h"
#include "Game_PlayResultShare.h"
#include "Game_Menu_MusicData.h"
#include "Game_Play_Lane.h"
#include "Game_Play_BarLine.h"
#include "Game_Play_NormalNote.h"
#include "Game_Play_LongNote.h"
#include "Game_Play_SlideNote.h"
#include "Game_Play_Score.h"
#include "Game_Play_Effect.h"
#include "Singleton_KeyHitCheck.h"

using namespace boost;

namespace Game {
	namespace Play {
		class Game_Play_PlayManager : public Task
		{
		private:
			std::shared_ptr<Game_MusicDataShareBetweenOtherSection>& p_musicDataShare;
			std::shared_ptr<Game::Game_PlayResultShare>& p_playResultShare;

			std::shared_ptr<Game_Play_Score> p_score;//スコア表示
			std::shared_ptr<Game_Play_Effect> p_effect;//エフェクト
			std::unique_ptr<Game_Play_Lane> p_lane;//レーン周りの描画
			std::vector<std::unique_ptr<Game_Play_BarLine>> barLineVec; //小節線
			//各ノーツ格納用
			std::vector<std::vector<std::unique_ptr<Game_Play_NormalNote>>> normalNoteVec;//レーンごとに格納
			std::vector<std::vector<std::unique_ptr<Game_Play_LongNote>>> longNoteVec;//レーンごとに格納
			std::vector<std::vector<std::unique_ptr<Game_Play_SlideNote>>> slideNoteVec;//右0か左1かで格納
			//各レーンの処理する順番が来たノーツの格納用
			std::vector<Game_Play_NormalNote*> normalNote;
			std::vector<Game_Play_LongNote*> longNote;
			std::vector<Game_Play_SlideNote*> slideNote;
			//処理する順番のノーツのカウンタ
			std::vector<std::uint16_t> normalCount;
			std::vector<std::uint16_t> longCount;
			std::vector<std::uint16_t> slideCount;

			Singleton::Singleton_KeyHitCheck* p_keyHitCheck;

			LONGLONG startTime;
			double nowTime;
			double startDelay;
			bool isGameStart;
			bool isMusicStart;

			std::int32_t fontColor;
			std::int32_t downColor;
			std::int32_t edgeColor;

			int configFont;
			int musicHandle;

			bool isLoadFail;

			bool isPlayToEnd;

			std::function<void()> drawNoteFunc;

			void nextNote(const std::uint16_t noteType, const std::uint16_t laneIndex);//判定を同じレーンの次のノーツに移す
			void drawBeforeStart();
			void drawDown();
			void drawHiSpeed();
			void drawJudgeCorrection();
			void drawNote();
			void updateKey();
			void playUpdate();
			void setYUpdateBorder();

			bool initializeNote(const std::uint16_t laneAmount, const double timePerBeat, std::uint16_t& maxChain);
		public:
			Game_Play_PlayManager(std::shared_ptr<SceneChanger>& p_sceneChanger, std::shared_ptr<Game_MusicDataShareBetweenOtherSection>& p_musicDataShare, std::shared_ptr<Game::Game_PlayResultShare>& p_playResultShare);
			void initialize() override;
			void finalize() override;
			void update() override;
			void draw() override;
		};
	}
}

