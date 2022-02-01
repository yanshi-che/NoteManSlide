#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <functional>

#include "Game_Draw_BaseDraw.h"
#include "Game_File_MusicData.h"
#include "Game_Draw_LineContainer.h"

namespace Game {
	namespace Singleton {
		constexpr std::uint8_t yWidthRegular{ 50 }; //拍線と拍線の距離
		constexpr std::uint16_t initialY = { 700 }; //一小節目の初期座標
		class Game_Singleton_BeatLineManager : public Draw::Game_Draw_BaseDraw
		{
		private:
			std::shared_ptr<File::Game_File_MusicData> p_musicData; //読み込んだ音楽のデータ
			std::vector<std::vector<std::unique_ptr<Draw::Game_Draw_LineContainer>>> barVec;//小節
			std::int8_t y;//マウスホイール用の変数
			std::uint8_t yMagnification;//マウスホイール入力による移動量
			std::function<void()> initBarLineFunction;
			std::uint8_t quontize;
			Singleton::Game_Singleton_NoteManager* p_noteManager;//ノーツ関連の制御クラス

			Game_Singleton_BeatLineManager();
			static Game_Singleton_BeatLineManager* p_instance;

			void initAllBarLineByQuontize();
			void initOneBarLineByQuontize();
			void resetBarVec(bool isAll);
			void checkSeparate(double& separate);

		public:
			static Game_Singleton_BeatLineManager* getInstance();

			void destroyInstance();
			void initialize(std::uint8_t initialQuontize, double separateBarWidth);
			//void finalize() override;
			void setMusicData(std::shared_ptr<File::Game_File_MusicData> data);
			void setInitBarLineFunc(std::uint8_t quon, bool isAll);
			void draw() override;
		};
	}
}
