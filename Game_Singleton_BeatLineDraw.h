#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "Game_Draw_BaseDraw.h"
#include "Game_File_MusicData.h"
#include "Game_Draw_LineContainer.h"

namespace Game {
	namespace Singleton {
		constexpr std::uint8_t yWidthRegular{ 50 }; //拍線と拍線の距離
		constexpr std::uint16_t initialY = { 700 }; //一小節目の初期座標
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
			void setMusicData(File::Game_File_MusicData* data);
			void initialize(std::uint8_t initialQuontize, double separateBarWidth);
			//void finalize() override;
			void draw() override;
			void initAllBarLineByQuontize(std::uint8_t quontize);
			void initOneBarLineByQuontize(std::uint8_t quontize);
			void resetBarVec();
		};
	}
}

inline void Game::Singleton::Game_Singleton_BeatLineDraw::draw() {
	if (musicData != nullptr) {
		y = GetMouseWheelRotVol() * yMagnification;
		for (int i = 0,isize = barVec.size(); i < isize; ++i) {
			for (int k = 0, ksize= barVec[i].size(); k < ksize; ++k) {
				barVec[i][k]->updateY(y);
				barVec[i][k]->draw();
			}
		}
	}
}
