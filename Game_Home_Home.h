#pragma once

#include <cstdint>
#include <memory>

#include "dxlib/DxLib.h"
#include "Task.h"
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

			std::uint8_t boxWidth;
			std::int8_t boxCount;
			std::uint16_t blend;
			std::int8_t blendDiff;

			void drawOption();
			void drawTitle();
		public:
			Game_Home_Home(std::shared_ptr<SceneChanger>& p_sceneChanger);
			void initialize() override;
			void finalize() override;
			void update() override;
			void draw() override;
		};
	}
}

