#pragma once

#include <cstdint>
#include <memory>

#include "dxlib/DxLib.h"
#include "Task.h"
#include "Game_PlayResultShare.h"
#include "Game_MusicDataShareBetweenOtherSection.h"
#include "Game_Menu_FileOperator.h"
#include "Singleton_KeyHitCheck.h"

namespace Game {
	namespace Result {
		class Game_Result_Result : public Task
		{
		private:
			Singleton::Singleton_KeyHitCheck* p_keyHitCheck;
			const std::shared_ptr<Game_MusicDataShareBetweenOtherSection>& p_musicDataShare;
			const std::shared_ptr<Game_PlayResultShare>& p_playResultShare;
			std::uint16_t perfect;
			std::uint16_t great;
			std::uint16_t miss;
			std::uint16_t score;
			bool isPlayToEnd;
			bool isClear;
			int font;
			int jisFont;
			int titleFont;
			std::int32_t fontColor;
			std::int32_t edgeColor;
			std::string clearStr;

			void saveData();
		public:
			Game_Result_Result(std::shared_ptr<SceneChanger>& p_sceneChanger,const std::shared_ptr<Game_MusicDataShareBetweenOtherSection>& p_musicDataShare,const std::shared_ptr<Game::Game_PlayResultShare>& p_playResultShare);
			void initialize() override;
			void finalize() override;
			void update() override;
			void draw() override;
		};
	}
}

