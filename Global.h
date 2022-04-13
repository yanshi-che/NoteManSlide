#pragma once

#include <cstdint>

namespace Global {
	constexpr const std::uint16_t WINDOW_WIDTH{ 740 };//ウインドウの横幅
	constexpr const std::uint16_t WINDOW_HEIGHT{ 740 };//ウインドウの縦幅
	constexpr const std::uint16_t WINDOW_COLORBIT{ 32 };//ウインドウのカラービット
	constexpr const double DRAW_X_MIN{ 40.0 };//ウインドウの横幅
	constexpr const double DRAW_X_MAX{ 700.0 };//ウインドウの横幅
	constexpr const std::uint16_t LANE_AMOUNT{ 6 };//レーンの数

	constexpr const double MINUTE{ 60.0 };

	constexpr const std::uint16_t NOTETYPE_NORMAL{ 1 };//ノーツの識別
	constexpr const std::uint16_t NOTETYPE_LONG{ 2 };
	constexpr const std::uint16_t NOTETYPE_SLIDER{ 3 };
	constexpr const std::uint16_t NOTETYPE_SLIDEL{ 4 };

	constexpr const std::uint16_t QUARTER{ 4 };// ４分音符
	constexpr const std::uint16_t EIGHTH{ 8 };// ８分音符
	constexpr const std::uint16_t SIXTEENTH{ 16 };// １６分音符
	constexpr const std::uint16_t THIRTYSECOND{ 32 };// ３２分音符
	constexpr const std::uint16_t TRIPLET{ 12 };// ３連符

	//テストプレイ画面の描画関連
	constexpr const double PLAY_LANE_X_MAX{ 550.0 };
	constexpr const double PLAY_LANE_X_MIN{ 190.0 };
	constexpr const double JUDGELINE_Y{ 680 };
	constexpr const double NOTE_HEIGHT{ 3.0 };
	constexpr const double LENGTH_FROM_LANE{ 5.0 };
	constexpr const std::uint16_t ARROW_NUM_LANE{ 3 };//1レーンあたりの矢印の数
	constexpr const double ARROW_HEIGHT{ 12.0 };//描画する矢印の幅；
	constexpr const double ARROW_LENGTH{ 12.0 };//描画する矢印の幅；

	//判定
	constexpr const double PERFECT{ 0.03333 };
	constexpr const double GREAT{ 0.06666 };
	constexpr const double MISS{ 0.06999 };

	//
	extern bool g_saveFlag;//セーブしたかどうかのフラグ
	extern std::uint16_t g_clickWidth;//拍線に対するマウスクリックの許容幅
}