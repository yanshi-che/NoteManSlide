#pragma once

#include <cstdint>

namespace Game {
	namespace Global {
		constexpr const std::uint16_t WINDOW_WIDTH{ 720 };//ウインドウの横幅
		constexpr const std::uint16_t WINDOW_HEIGHT{ 740 };//ウインドウの縦幅
		constexpr const std::uint8_t WINDOW_COLORBIT{ 32 };//ウインドウのカラービット
		constexpr const std::uint16_t DRAW_X_MIN{ 20 };//ウインドウの横幅
		constexpr const std::uint16_t DRAW_X_MAX{ 700 };//ウインドウの横幅
		constexpr const double MINUTE{ 60.0 };
		static std::uint8_t clickWidth = 8;//拍線に対するマウスクリックの許容幅
	}
}