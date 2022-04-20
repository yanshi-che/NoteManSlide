#pragma once

#include <cstdint>
#include <string>

#include "dxlib/DxLib.h"
#include "Global.h"

namespace Game {
	namespace Play {
		constexpr const std::uint16_t clearGageBoxYMin{350};
		constexpr const std::uint16_t clearGageBoxYMax{50};
		constexpr const std::uint16_t clearGageBoxYClearLine{ 140 };
		constexpr const std::uint16_t clearGageBoxXWidth{ 50 };
		constexpr const std::uint16_t clearGageBoxX{ 620 };
		constexpr const std::uint16_t clearLineNum{ 70 };
		class Game_Play_Score
		{
		private:
			double gageBoxDiv;
			//�N���A�Q�[�W�֘A
			double clearGageNum;
			double clearGageNumDiv;
			double clearGageBoxY;
			//�`�F�C��
			std::uint16_t chain;
			std::string chainStr;
			//�X�R�A
			std::uint16_t score;
			std::string scoreStr;
			//����
			std::uint16_t perfect;
			std::uint16_t great;
			std::uint16_t miss;
			std::string perfectStr;
			std::string greatStr;
			std::string missStr;
			//����\��
			std::string judge;
			//�F�֌W
			std::uint16_t blend;
			std::int32_t color;
			std::int32_t edgeColor;
			std::int32_t judgeColor;
			std::int32_t clearGageColor;
			std::int32_t clearGageClearLineColor;
			//�t�H���g
			std::uint16_t initFontSize;
			std::uint16_t judgeFontSize;
			std::uint16_t clearGageFontSize;
			int font;

			void drawClearGage();
			void drawChain();
			void drawJudge();
			void drawJudgeScore();
			void drawScore();
		public:
			Game_Play_Score(int font,std::uint16_t maxChain);
			void draw();
			void plusPerfect();
			void plusGreat();
			void plusMiss();

			bool isClear();
			std::uint16_t getScore();
			std::uint16_t getPerfect();
			std::uint16_t getGreat();
			std::uint16_t getMiss();
		};
	}
}

