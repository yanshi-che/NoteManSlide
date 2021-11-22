#pragma once

#include "Game_Task.h"
#include "Game_Config.h"
namespace Game {
	namespace Draw {
		class Game_Draw_BaseDraw : public Game_Task
		{
		public:
			Game_Draw_BaseDraw();
			void initialize() override;
			void finalize() override;
			void update() override;
			void draw() override;
		};
	}
}