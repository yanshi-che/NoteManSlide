#pragma once

#include <cstdint>

#include "dxlib/DxLib.h"
#include "Task.h"
#include "Game_PlayResultShare.h"
#include "Singleton_KeyHitCheck.h"

namespace Game {
	namespace Result {
		class Game_Result_Result : public Task
		{
		private:
			Singleton::Singleton_KeyHitCheck* p_keyHitCheck;
			std::uint16_t perfect;
			std::uint16_t great;
			std::uint16_t miss;
			int font;
			std::int32_t fontColor;
			std::int32_t edgeColor;
		public:
			Game_Result_Result(std::shared_ptr<SceneChanger>& p_sceneChanger,std::shared_ptr<Game::Game_PlayResultShare>& p_playResultShare);
			void initialize() override;
			void finalize() override;
			void update() override;
			void draw() override;
		};
	}
}

