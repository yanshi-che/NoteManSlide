#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <functional>

#include "Game_File_MusicData.h"
#include "Game_Draw_LineContainer.h"
#include "Game_Draw_ScrollBar.h"

namespace Game {
	namespace Singleton {
		constexpr float yWidthRegular{ 150.0 }; //拍線と拍線の距離
		constexpr float initialY = { 700.0 }; //一小節目の初期座標
		class Game_Singleton_BeatLineManager
		{
		private:
			std::shared_ptr<File::Game_File_MusicData> p_musicData; //読み込んだ音楽のデータ
			std::vector<std::vector<std::shared_ptr<Draw::Game_Draw_LineContainer>>> barVec;//小節
			std::unique_ptr<Draw::Game_Draw_ScrollBar> scrBar;
			float y;//マウスホイール用の変数
			float yMagnificationByMouseWheel;//マウスホイール入力による移動量の倍率
			std::function<void()> initBarLineFunction;
			std::uint8_t quontize;
			Singleton::Game_Singleton_NoteManager* p_noteManager;//ノーツ関連の制御クラス

			Game_Singleton_BeatLineManager();
			static Game_Singleton_BeatLineManager* p_instance;

			void initAllBarLineByQuontize();
			void initOneBarLineByQuontize();
			void resetBarVec(bool isAll);
			void resetScrollBar(bool isAll);
			void checkSeparate(float& separate);

		public:
			static Game_Singleton_BeatLineManager* getInstance();

			void destroyInstance();
			void initialize(std::uint8_t initialQuontize,float separateBarWidth);
			void initScrollBar(float scoreWidth);
			//void finalize();
			void setMusicData(const std::shared_ptr<File::Game_File_MusicData>& data);
			void setInitBarLineFunc(std::uint8_t quon, bool isAll);
			void draw();
		};
	}
}
