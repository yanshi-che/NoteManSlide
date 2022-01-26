#pragma once

#include <cstdint>
#include <vector>
#include <cmath>
#include <memory>
#include "dxlib/DxLib.h"
#include "Game_Draw_BaseDraw.h"
#include "Game_Note_NormalNoteContainer.h"
#include "Game_Singleton_NoteManager.h"

namespace Game {
	namespace Draw {
		class Game_Draw_LineContainer : public Game_Draw_BaseDraw
		{
		private:
			static std::uint8_t noteType; //入力するノーツのタイプ。１の時は普通のノーツ。2の時はロングノーツ
			static int button, mouseX, mouseY, logType; //マウスのクリック管理
			static bool clickObserver;//マウスがクリックされて続けているか
			static bool longClickObserver;

			static std::uint16_t startBarIDForLongNote;//ロングノーツ用の拍線管理
			static std::uint16_t startBeatIDForLongNote;//ロングノーツ用の小節管理
			static std::uint8_t raneIDForLong;//ロングノーツ用のレーン管理

			static std::uint16_t barIDForChangeQuontize;//小節ごとのクオンタイズ変更のための変数

			Singleton::Game_Singleton_NoteManager* noteManager;
			const std::uint16_t barID; //何小節目に属しているか
			const std::uint16_t beatID;//その小節の何番目の線か
			const double time;//曲の開始から何秒か
			const std::uint8_t* numberOfRane; //レーンの数
			std::int32_t yMax;//座標の最大値
			std::int32_t yMin;//座標の最小値
			std::int32_t color;//拍線の色
			std::uint8_t lineThickness; //拍線の太さ
			std::int32_t y; //拍線の座標
			std::vector<std::uint16_t> raneX;
			std::uint8_t barIDThickness; //小節番号の線の太さ
			std::int32_t barIDColor;//小節番号の色
			std::uint8_t barIDStrWidth;//小節番号の文字の大きさ

			bool isMouseClickDown();
			bool isMouseClickUp();
			bool checkClickBorder();
			void drawNotes() ;
			void drawLine() ;
			void drawBarID() ;
		public:
			Game_Draw_LineContainer(std::uint16_t barID, const std::uint8_t* numberOfRane, double time, std::uint16_t beatID, std::int32_t y,std::int32_t yMax);
			static void setNoteType(std::uint8_t type) ;
			static std::uint16_t getbarIDForChangeQuontize();
			double getTime();
			std::int32_t getY();
			std::int32_t getYMin();
			void setYMin(std::int32_t y);
			std::int32_t getYMax();
			void updateYMax(std::int32_t y);
			void updateByInitOneBar(std::int32_t& yWidth);
			void updateY(std::int8_t& y);
			void draw() override;
		};
	}
}

inline void Game::Draw::Game_Draw_LineContainer::draw() {
	drawLine();
	drawBarID();
	drawNotes();
}

inline void Game::Draw::Game_Draw_LineContainer::updateY(std::int8_t& y)  {
	if (y < 0 && yMin < this->y || 0 < y && this->y < yMax) {
		this->y += y;
	}
}