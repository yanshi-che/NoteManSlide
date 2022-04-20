#pragma once

#include <cstdint>
#include <memory>

#include "dxlib/DxLib.h"
#include "Task.h"
#include "Global.h"
#include "SceneChanger.h"
#include "Singleton_KeyHitCheck.h"

namespace Game {
	namespace Home {
		class Game_Home_Home : public Task
		{
		private:
			::Singleton::Singleton_KeyHitCheck* p_keyHitCheck;

			int titleFontHandle;
			int optionFontHandle;
			std::int32_t fontColor;
			std::int32_t edgeColor;

			std::uint16_t boxWidth;
			std::int16_t boxCount;
			std::uint16_t blend;
			std::int16_t blendDiff;

			void blendDiffUpdate();
			void drawOption();
			void drawTitle();
			void drawKeyConf();
		public:
			Game_Home_Home(std::shared_ptr<SceneChanger>& p_sceneChanger);
			void initialize() override;
			void finalize() override;
			void update() override;
			void draw() override;
		};
	}
}

