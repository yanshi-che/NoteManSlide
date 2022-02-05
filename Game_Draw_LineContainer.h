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
#include "Game_Note_NormalNoteContainer.h"
#include "Game_Singleton_NoteManager.h"
#include "Game_Singleton_MouseOperationCheck.h"

namespace Game {
	namespace Draw {
		class Game_Draw_LineContainer
		{
		private:
			static std::uint8_t noteType; //入力するノーツのタイプ。１の時は普通のノーツ。2の時はロングノーツ
			static bool clickObserver;//マウスクリックによる操作の制御変数

			static int mouseX, mouseY;//マウスクリックの座標格納用の変数
			static std::uint16_t startBarIDForLongNote;//ロングノーツ用の拍線管理
			static std::uint16_t startBeatIDForLongNote;//ロングノーツ用の小節管理
			static std::uint8_t laneIDForLongNote;//ロングノーツ用のレーン管理

			static std::uint16_t barIDForChangeQuontize;//小節ごとのクオンタイズ変更のための変数

			Singleton::Game_Singleton_NoteManager* p_noteManager;
			Singleton::Game_Singleton_MouseOperationCheck* p_mouseCheck;

			const std::uint16_t barID; //何小節目に属しているか
			const std::uint16_t beatID;//その小節の何番目の線か
			const float time;//曲の開始から何秒か
			const std::uint8_t& amountOfLane; //レーンの数
			float yMax;//座標の最大値
			float yMin;//座標の最小値
			std::uint32_t color;//拍線の色
			std::uint8_t lineThickness; //拍線の太さ
			float y; //拍線の座標
			std::vector<float> laneX;
			std::uint8_t barIDThickness; //小節番号の線の太さ
			std::uint32_t barIDColor;//小節番号の色
			std::uint8_t barIDStrWidth;//小節番号の文字の大きさ
			std::string barIDStr;
			std::uint8_t brend;

			bool checkClickBorder();
			void drawNotes() ;
			void drawLine() ;
			void drawBarID() ;
		public:
			Game_Draw_LineContainer(std::uint16_t barID,std::uint8_t amountOfLane,float time,std::uint16_t beatID,float y,float yMax);
			static void setNoteType(std::uint8_t type) ;
			static std::uint16_t getbarIDForChangeQuontize();

			float getTime();
			float getY();
			float getYMin();
			float getYMax();

			void setYMin(float y);
			void updateYMax(float y);
			void updateByInitOneBar(float yWidth);
			void updateY(float y);
			void draw();
		};
	}
}