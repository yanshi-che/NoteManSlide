#pragma once

#include <boost/json.hpp>
#include <cstdint>
#include <functional>
#include <memory>
#include <deque>
#include <vector>

#include "Make_File_MusicData.h"
#include "Make_Draw_LineContainer.h"
#include "Make_Draw_ScrollBar.h"
#include "Make_Draw_LaneDraw.h"
#include "Make_Note_NoteManager.h"

using namespace boost;

namespace Make {
	namespace Draw {
		constexpr double yWidthRegular{ 150.0 }; //拍線と拍線の距離
		constexpr double initialY = { 700.0 }; //一小節目の初期座標
		class Make_Draw_BeatLineManager
		{
		private:
			std::shared_ptr<File::Make_File_MusicData> p_musicData; //読み込んだ音楽のデータ
			std::shared_ptr<Note::Make_Note_NoteManager> p_noteManager;//ノーツ関連の制御クラス
			std::vector<std::vector<std::shared_ptr<Draw::Make_Draw_LineContainer>>> barVec;//小節
			std::unique_ptr<Draw::Make_Draw_ScrollBar> scrBar;//スクロールバーの描画クラス
			std::unique_ptr<Make_Draw_LaneDraw> p_laneDraw;//レーンの描画クラス

			double y;//マウスホイール用の変数
			double yMagnificationByMouseWheel;//マウスホイール入力による移動量の倍率
			double totalScoreWidth;//スクロールバー用のスコア全体の大きさ
			std::function<void()> initBarLineFunction;//描画処理がすべて終わった後に初期化処理をするための格納変数
			std::uint8_t quontize;
			std::uint16_t barIDForInitOneVector;

			void draw();
			void initScrollBar();
			void initOtherClass();
			void initAllBarLineByQuontizeChange();
			void initOneBarLineByQuontizeChange();
			void resetBarVec(bool isAll);
			void resetScrollBar();

			double checkSeparate(const std::uint8_t quontize);

		public:
			Make_Draw_BeatLineManager();

			void finalize();
			void initialize(const std::shared_ptr<File::Make_File_MusicData>& data);
			void initBarVec(std::uint8_t initialQuontize,double separateBarWidth);
			void initializeBySavaData(const std::shared_ptr<File::Make_File_MusicData>& data,const json::value& val);
			void setInitBarLineFunc(const std::uint8_t quon,const std::uint16_t barIDForInitOneVector,const bool isAll);

			const std::function<void()> getDrawFunc();
			const std::vector<std::vector<std::shared_ptr<Draw::Make_Draw_LineContainer>>>& getBarVec();
			const std::shared_ptr<Note::Make_Note_NoteManager>& getNoteManager();
		};
	}
}
