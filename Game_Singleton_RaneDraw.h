#pragma once

#include <memory>
#include "Game_Draw_BaseDraw.h"
#include "dxlib/DxLib.h"

namespace Game {
	namespace Singleton {
		class Game_Singleton_RaneDraw :public Draw::Game_Draw_BaseDraw
		{
		private:
			const std::uint32_t raneColor;     //���[���̐F
			const std::uint8_t raneThickness;  //���[���̑���
			std::uint16_t raneWidth; //���[���̕�
			std::uint8_t numberOfRane;		   //���[���̐�
			static Game_Singleton_RaneDraw* instance;
			Game_Singleton_RaneDraw();
		public:
			static Game_Singleton_RaneDraw* getInstance();
			void destroyInstance();
			void draw() noexcept override;
			void setNumberOfRane(std::uint8_t num) noexcept;
		};

	}
}