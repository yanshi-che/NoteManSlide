#pragma once

#include <cstdint>

namespace Game {
	namespace Global {
		constexpr const std::uint16_t WINDOW_WIDTH{ 720 };//�E�C���h�E�̉���
		constexpr const std::uint16_t WINDOW_HEIGHT{ 740 };//�E�C���h�E�̏c��
		constexpr const std::uint8_t WINDOW_COLORBIT{ 32 };//�E�C���h�E�̃J���[�r�b�g
		constexpr const std::uint16_t DRAW_X_MIN{ 20 };//�E�C���h�E�̉���
		constexpr const std::uint16_t DRAW_X_MAX{ 700 };//�E�C���h�E�̉���
		constexpr const double MINUTE{ 60.0 };
		static std::uint8_t clickWidth = 8;//�����ɑ΂���}�E�X�N���b�N�̋��e��
	}
}