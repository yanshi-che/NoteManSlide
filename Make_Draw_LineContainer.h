#pragma once

#include <cstdint>
#include <vector>
#include <cmath>
#include <memory>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include "dxlib/DxLib.h"
#include "Make_Note_NormalNoteContainer.h"
#include "Make_Note_NoteManager.h"
#include "Make_Singleton_MouseOperationCheck.h"

namespace Make {
	namespace Draw {
		class Make_Draw_LineContainer
		{
		private:
			static std::uint8_t noteType; //入力するノーツのタイプ。１の時は普通のノーツ。2の時はロングノーツ
			static bool clickObserver;//マウスクリックによる操作の制御変数

			static int mouseX, mouseY;//マウスクリックの座標格納用の変数
			static std::uint8_t laneIDForLongNote;//ロングノーツ用のレーン管理

			static std::uint16_t barIDForChangeQuontize;//小節ごとのクオンタイズ変更のための変数

			const std::shared_ptr<Note::Make_Note_NoteManager>& p_noteManager;
			Singleton::Make_Singleton_MouseOperationCheck* p_mouseCheck;

			const std::uint16_t barID; //何小節目に属しているか
			const std::uint8_t beatID;//その小節の何番目の線か
			const double time;//曲の開始から何秒か
			const std::uint8_t laneAmount; //レーンの数
			double yMax;//座標の最大値
			double yMin;//座標の最小値
			std::uint32_t color;//拍線の色
			std::uint8_t lineThickness; //拍線の太さ
			double y; //拍線の座標
			std::vector<double> laneX;
			std::uint8_t barIDThickness; //小節番号の線の太さ
			std::uint32_t barIDColor;//小節番号の色
			std::uint8_t barIDStrWidth;//小節番号の文字の大きさ
			std::string barIDStr;
			std::uint8_t brend;

			bool checkClickBorder();
			void drawNote() ;
			void drawLine() ;
			void drawBarID() ;
		public:
			Make_Draw_LineContainer(const std::uint16_t barID,const double time,const std::uint8_t beatID,const double y,const double yMax,const std::shared_ptr<Note::Make_Note_NoteManager>& p_noteManager);
			static void setNoteType(const std::uint8_t type) ;
			static std::uint16_t getbarIDForChangeQuontize();

			void setYMin(const double y);
			void updateYMax(const double y);
			void updateByInitOneBar(const double yWidth);
			void updateY(const double y);
			void draw();

			double getTime();
			double getY();
			double getYMin();
			double getYMax();
		};
	}
}