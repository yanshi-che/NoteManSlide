#pragma once

#include <iostream>
#include <memory>
#include <deque>
#include <vector>

#include "boost/json.hpp"
#include "dxlib/DxLib.h"
#include "Task.h"
#include "Global.h"
#include "SceneChanger.h"
#include "Game_Menu_MusicData.h"
#include "Game_Menu_FileOperator.h"
#include "Game_MusicDataShareBetweenOtherSection.h"
#include "Singleton_KeyHitCheck.h"

using namespace boost;

namespace Game {
	namespace Menu {
		constexpr const std::uint16_t musicListSize{ 7 };
		constexpr const std::uint16_t difficultyCountBorder{ 3 };
		class Game_Menu_MenuManager : public Task
		{
		private:
			Singleton::Singleton_KeyHitCheck* p_keyHitCheck;
			std::shared_ptr<Game_MusicDataShareBetweenOtherSection>& p_musicDataShare;
			std::unique_ptr<Game_Menu_FileOperator> p_fileOp;
			std::vector<std::vector<std::shared_ptr<Game_Menu_MusicData>>> musicDataVec;
			std::deque<std::uint16_t> musicDataVecElementDeq;
			std::vector<std::shared_ptr<Game_Menu_MusicData>>* p_focusedMusicData;
			//フォントデータのハンドル
			int focusedMusicListFontHandle;
			int notFocusedMusicListFontHandle;
			int focusedMusicFontHandle;
			int difficultyFontHandle;
			//色
			int fontColor;
			int edgeColor;

			std::int16_t difficultyCount;
			std::string bestScore[3];
			std::string clearStatus[3];
			std::string bpm;
			std::string easyNum;
			std::string normalNum;
			std::string hardNum;

			std::uint16_t blend;
			std::int16_t blendDiff;

			bool isFail;

			void blendDiffUpdate();
			void drawMusicList();
			void drawFocusedMusicData();
			void drawKeyConf();
			void setDifficultyFocusedMusicDataStr();
			void setNextFocusedMusicData();
			void setPrevFocusedMusicData();
		public:
			Game_Menu_MenuManager(std::shared_ptr<SceneChanger>& p_sceneChanger, std::shared_ptr<Game_MusicDataShareBetweenOtherSection>& p_musicDataShare);
			void initialize() override;
			void finalize() override;
			void update() override;
			void draw() override;
		};
	}
}

