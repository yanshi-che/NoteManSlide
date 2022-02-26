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
		extern double g_hiSpeed;
		extern double g_judgeCorrection;
		extern std::uint16_t g_lane0;
		extern std::uint16_t g_lane1;
		extern std::uint16_t g_lane2;
		extern std::uint16_t g_lane3;
		extern std::uint16_t g_lane4;
		extern std::uint16_t g_lane5;
		extern std::uint16_t g_laneRR;
		extern std::uint16_t g_laneRL;
		extern std::uint16_t g_laneLR;
		extern std::uint16_t g_laneLL;
		//ボルテコン
		extern std::uint16_t g_PAD_ID;
		extern std::uint16_t g_BT_A;
		extern std::uint16_t g_BT_B;
		extern std::uint16_t g_BT_C;
		extern std::uint16_t g_BT_D;
		extern std::uint16_t g_FX_L;
		extern std::uint16_t g_FX_R;
		extern std::uint16_t g_VOL_R1;
		extern std::uint16_t g_VOL_R2;
		extern std::uint16_t g_VOL_L1;
		extern std::uint16_t g_VOL_L2;
		extern std::uint16_t g_B_START;
		//
		extern bool g_saveFlag;//セーブしたかどうかのフラグ
		extern std::uint8_t g_clickWidth;//拍線に対するマウスクリックの許容幅
	}
}