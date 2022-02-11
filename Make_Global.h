#pragma once

#include <cstdint>

namespace Make {
	namespace Global {
		constexpr const std::uint16_t WINDOW_WIDTH{ 740 };//ウインドウの横幅
		constexpr const std::uint16_t WINDOW_HEIGHT{ 740 };//ウインドウの縦幅
		constexpr const std::uint8_t WINDOW_COLORBIT{ 32 };//ウインドウのカラービット
		constexpr const float DRAW_X_MIN{ 40.0f };//ウインドウの横幅
		constexpr const float DRAW_X_MAX{ 700.0f };//ウインドウの横幅

		constexpr const float MINUTE{ 60.0f };

		constexpr const std::uint8_t NOTETYPENORMAL{ 1 };//ノーツの識別
		constexpr const std::uint8_t NOTETYPELONG{ 2 };
		constexpr const std::uint8_t NOTETYPESLIDE{ 3 };

		constexpr const std::uint8_t QUARTER{ 4 };// ４分音符
		constexpr const std::uint8_t EIGHTH{ 8 };// ８分音符
		constexpr const std::uint8_t SIXTEENTH{ 16 };// １６分音符
		constexpr const std::uint8_t THIRTYSECOND{ 32 };// ３２分音符
		constexpr const std::uint8_t TRIPLET{ 12 };// ３連符

		static std::uint8_t clickWidth = 8;//拍線に対するマウスクリックの許容幅
	}
}