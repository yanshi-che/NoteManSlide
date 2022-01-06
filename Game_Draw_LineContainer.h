#pragma once

#include <cstdint>
#include <vector>
#include <cmath>

#include "Game_Draw_BaseDraw.h"
#include "Game_File_MusicData.h"

namespace Game {
	namespace Draw {
		class Game_Draw_LineContainer : public Game_Draw_BaseDraw
		{
		private:
			enum noteTypes {
				Normal = 1,
				Long,
			};
			static std::uint8_t noteType; //���͂���m�[�c�̃^�C�v�B�P�̎��͕��ʂ̃m�[�c�B2�̎��̓����O�m�[�c
			static int button, mouseX, mouseY, logType; //�}�E�X�̃N���b�N�Ǘ��p
			static std::uint8_t noteWidth; //�`�悷��m�[�c�̕��G
			static bool clickObserver;//�}�E�X���N���b�N����đ����Ă��邩
			const std::uint16_t barID; //�����ߖڂɑ����Ă��邩
			const std::uint16_t barNumber;//���̏��߂̉��Ԗڂ̐���
			const std::uint8_t numberOfRane;//���[���̐�
			const double time;//�Ȃ̊J�n���牽�b��
			std::vector<std::uint16_t> raneX; //�e���[���̍��W
			std::uint16_t raneWidth;//���[���̕�
			std::int32_t color;//�����̐F
			std::uint8_t lineThickness; //�����̑���
			std::vector<bool> noteFlag; //�m�[�c���Z�b�g���ꂽ���ǂ���
			std::vector<std::vector<bool>> longNoteFlag; //�ꎟ���ڂ̓����O�m�[�c���Z�b�g���ꂽ���ǂ���.�񎟌��ڂ͂��ꂪ�n�_�܂��͏I�_��
			std::int32_t y; //�����̍��W
			const std::int32_t yMax;//���W�̍ő�l
			const std::int32_t yMin;//���W�̍ŏ��l
			std::uint8_t clickWidth;//�����ɑ΂���}�E�X�N���b�N�̋��e��
		public:
			Game_Draw_LineContainer(std::uint16_t bID, std::uint8_t numOfRane, double t, std::uint16_t bNum, std::int32_t y,std::int32_t yMax);
			void drawNote() noexcept;
			void drawLongNote() noexcept;
			void drawLine() noexcept;
			static void setNoteType(std::uint8_t type) noexcept;
			void updateY(std::int16_t y) noexcept;
			void draw() override;
		};
	}
}

