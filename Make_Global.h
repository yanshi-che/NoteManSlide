#pragma once

#include <cstdint>

#include "dxlib/DxLib.h"

namespace Make {
	namespace Global {
		constexpr const std::uint16_t WINDOW_WIDTH{ 740 };//ウインドウの横幅
		constexpr const std::uint16_t WINDOW_HEIGHT{ 740 };//ウインドウの縦幅
		constexpr const std::uint8_t WINDOW_COLORBIT{ 32 };//ウインドウのカラービット
		constexpr const double DRAW_X_MIN{ 40.0 };//ウインドウの横幅
		constexpr const double DRAW_X_MAX{ 700.0 };//ウインドウの横幅
		constexpr const std::uint8_t LANE_AMOUNT{ 6 };//レーンの数

		constexpr const double MINUTE{ 60.0 };

		constexpr const std::uint8_t NOTETYPE_NORMAL{ 1 };//ノーツの識別
		constexpr const std::uint8_t NOTETYPE_LONG{ 2 };
		constexpr const std::uint8_t NOTETYPE_SLIDER{ 3 };
		constexpr const std::uint8_t NOTETYPE_SLIDEL{ 4 };

		constexpr const std::uint8_t QUARTER{ 4 };// ４分音符
		constexpr const std::uint8_t EIGHTH{ 8 };// ８分音符
		constexpr const std::uint8_t SIXTEENTH{ 16 };// １６分音符
		constexpr const std::uint8_t THIRTYSECOND{ 32 };// ３２分音符
		constexpr const std::uint8_t TRIPLET{ 12 };// ３連符

		//テストプレイ画面の描画関連
		constexpr const double PLAY_LANE_X_MAX{ 550.0};
		constexpr const double PLAY_LANE_X_MIN{ 190.0};
		constexpr const double JUDGELINE_Y{ 680 };
		constexpr const double NOTE_HEIGHT{ 3.0 };
		constexpr const double LENGTH_FROM_LANE{ 5.0 };
		constexpr const std::uint8_t ARROW_NUM_LANE{ 4 };//1レーンあたりの矢印の数
		constexpr const double ARROW_HEIGHT{ 12.0 };//描画する矢印の幅；
		constexpr const double ARROW_LENGTH{ 12.0 };//描画する矢印の幅；

		//判定
		constexpr const double PERFECT{ 0.03333 };
		constexpr const double GREAT{ 0.06666 };
		constexpr const double MISS{ 0.06999 };

		//ユーザー定義
		static double hiSpeed = 0.3;
		static std::uint16_t lane0 = KEY_INPUT_D;
		static std::uint16_t lane1 = KEY_INPUT_F;
		static std::uint16_t lane2 = KEY_INPUT_G;
		static std::uint16_t lane3 = KEY_INPUT_H;
		static std::uint16_t lane4 = KEY_INPUT_J;
		static std::uint16_t lane5 = KEY_INPUT_K;
		static std::uint16_t laneRR = KEY_INPUT_U;
		static std::uint16_t laneRL = KEY_INPUT_I;
		static std::uint16_t laneLR = KEY_INPUT_T;
		static std::uint16_t laneLL = KEY_INPUT_R;
		//
		static bool saveFlag = true;//セーブしたかどうかのフラグ
		static std::uint8_t clickWidth = 8;//拍線に対するマウスクリックの許容幅
	}
}