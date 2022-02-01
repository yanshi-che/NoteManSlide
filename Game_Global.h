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

		constexpr const std::uint8_t NOTETYPENORMAL{ 1 };//�m�[�c�̎���
		constexpr const std::uint8_t NOTETYPELONG{ 2 };

		constexpr const std::uint8_t QUARTER{ 4 };// �S������
		constexpr const std::uint8_t EIGHTH{ 8 };// �W������
		constexpr const std::uint8_t SIXTEENTH{ 16 };// �P�U������
		constexpr const std::uint8_t THIRTYSECOND{ 32 };// �R�Q������
		constexpr const std::uint8_t TRIPLET{ 12 };// �R�A��

		static std::uint8_t clickWidth = 8;//�����ɑ΂���}�E�X�N���b�N�̋��e��
	}
}