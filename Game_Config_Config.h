#pragma once

#include <cstdint>
#include <fstream>
#include <string>

#include "boost/json.hpp"
#include "dxlib/DxLib.h"
#include "Task.h"
#include "Config_Config.h"
#include "Singleton_KeyHitCheck.h"

using namespace boost;

namespace Game {
	namespace Config {
		class Game_Config_Config : public Task
		{
		private:
			Singleton::Singleton_KeyHitCheck* p_keyCheck;
			double hiSpeed;
			double judgeCorrection;
			std::int32_t fontColor;
			std::int32_t edgeColor;
			int font;
			bool isFail;

			void drawKeyConf();
		public:
			Game_Config_Config(std::shared_ptr<SceneChanger>& p_sceneChanger);
			void initialize() override;
			void finalize() override;
			void update() override;
			void draw() override;
		};
	}
}

