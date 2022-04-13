#pragma once

#include <cstdint>

namespace Global {
	constexpr const std::uint16_t WINDOW_WIDTH{ 740 };//�E�C���h�E�̉���
	constexpr const std::uint16_t WINDOW_HEIGHT{ 740 };//�E�C���h�E�̏c��
	constexpr const std::uint16_t WINDOW_COLORBIT{ 32 };//�E�C���h�E�̃J���[�r�b�g
	constexpr const double DRAW_X_MIN{ 40.0 };//�E�C���h�E�̉���
	constexpr const double DRAW_X_MAX{ 700.0 };//�E�C���h�E�̉���
	constexpr const std::uint16_t LANE_AMOUNT{ 6 };//���[���̐�

	constexpr const double MINUTE{ 60.0 };

	constexpr const std::uint16_t NOTETYPE_NORMAL{ 1 };//�m�[�c�̎���
	constexpr const std::uint16_t NOTETYPE_LONG{ 2 };
	constexpr const std::uint16_t NOTETYPE_SLIDER{ 3 };
	constexpr const std::uint16_t NOTETYPE_SLIDEL{ 4 };

	constexpr const std::uint16_t QUARTER{ 4 };// �S������
	constexpr const std::uint16_t EIGHTH{ 8 };// �W������
	constexpr const std::uint16_t SIXTEENTH{ 16 };// �P�U������
	constexpr const std::uint16_t THIRTYSECOND{ 32 };// �R�Q������
	constexpr const std::uint16_t TRIPLET{ 12 };// �R�A��

	//�e�X�g�v���C��ʂ̕`��֘A
	constexpr const double PLAY_LANE_X_MAX{ 550.0 };
	constexpr const double PLAY_LANE_X_MIN{ 190.0 };
	constexpr const double JUDGELINE_Y{ 680 };
	constexpr const double NOTE_HEIGHT{ 3.0 };
	constexpr const double LENGTH_FROM_LANE{ 5.0 };
	constexpr const std::uint16_t ARROW_NUM_LANE{ 3 };//1���[��������̖��̐�
	constexpr const double ARROW_HEIGHT{ 12.0 };//�`�悷����̕��G
	constexpr const double ARROW_LENGTH{ 12.0 };//�`�悷����̕��G

	//����
	constexpr const double PERFECT{ 0.03333 };
	constexpr const double GREAT{ 0.06666 };
	constexpr const double MISS{ 0.06999 };

	//
	extern bool g_saveFlag;//�Z�[�u�������ǂ����̃t���O
	extern std::uint16_t g_clickWidth;//�����ɑ΂���}�E�X�N���b�N�̋��e��
}