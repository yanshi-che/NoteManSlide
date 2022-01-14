#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "Game_Draw_BaseDraw.h"
#include "Game_File_MusicData.h"
#include "Game_Draw_LineContainer.h"

namespace Game {
	namespace Singleton {
		class Game_Singleton_BeatLineDraw : public Draw::Game_Draw_BaseDraw
		{
		private:
			File::Game_File_MusicData* musicData; //読み込んだ音楽のデータ
			std::vector<std::vector<std::unique_ptr<Draw::Game_Draw_LineContainer>>> barVec;//小節
			std::int8_t y;//マウスホイール用の変数
			std::uint8_t yMagnification;//マウスホイール入力による移動量
			Singleton::Game_Singleton_NoteManager* noteManager;//ノーツ関連の制御クラス

			Game_Singleton_BeatLineDraw();
			static Game_Singleton_BeatLineDraw* instance;
		public:
			static Game_Singleton_BeatLineDraw* getInstance();
			void destroyInstance();
			void setMusicData(File::Game_File_MusicData* data) noexcept;
			void initialize() override;
			//void finalize() override;
			void draw() override;
		};
	}
}
