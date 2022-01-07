#pragma once
#include <cstdint>
#include <vector>
#include "dxlib/DxLib.h"
#include "Game_Global.h"


namespace Game {
	namespace Draw {
		class Game_Draw_NoteContainer
		{
		private:
			static int button, mouseX, mouseY, logType; //マウスのクリック管理用
			static std::uint8_t noteWidth; //描画するノーツの幅；
			static std::uint8_t clickWidth;//拍線に対するマウスクリックの許容幅
			static bool clickObserver;//マウスがクリックされて続けているか
			const std::uint8_t noteID;//何レーン目のノーツか
			std::uint16_t raneX; //レーンの座標
			std::uint16_t raneWidth;//レーンの幅
			std::int32_t* y; //拍線の座標
			bool noteFlag;
		public:
			Game_Draw_NoteContainer(std::int32_t* y, std::uint8_t noteID, std::uint16_t raneX, std::uint16_t raneWidth);
			void setNoteFlag();
			void drawNote();
			static bool checkClick();
			static void initializeCheckClick();
		};
	}
}

