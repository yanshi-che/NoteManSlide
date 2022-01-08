#pragma once

#include <cstdint>
#include <vector>
#include <cmath>
#include <memory>
#include "dxlib/DxLib.h"
#include "Game_Draw_BaseDraw.h"
#include "Game_Draw_NoteContainer.h"

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
			const std::uint16_t barID; //�����ߖڂɑ����Ă��邩
			const std::uint16_t barNumber;//���̏��߂̉��Ԗڂ̐���
			const double time;//�Ȃ̊J�n���牽�b��
			const std::int32_t yMax;//���W�̍ő�l
			const std::int32_t yMin;//���W�̍ŏ��l
			const std::uint8_t* numberOfRane; //���[���̐�
			std::int32_t color;//�����̐F
			std::uint8_t lineThickness; //�����̑���
			//std::vector<std::vector<bool>> longNoteFlag; //�ꎟ���ڂ̓����O�m�[�c���Z�b�g���ꂽ���ǂ���.�񎟌��ڂ͂��ꂪ�n�_�܂��͏I�_��
			std::int32_t y; //�����̍��W
			std::vector<std::unique_ptr<Game_Draw_NoteContainer>> notes;
		public:
			Game_Draw_LineContainer(std::uint16_t bID, const std::uint8_t* numberOfRane, double t, std::uint16_t bNum, std::int32_t y,std::int32_t yMax);
			void drawNotes() noexcept;
			void drawLine() noexcept;
			void drawBarID() noexcept;
			static void setNoteType(std::uint8_t type) noexcept;
			void updateY(std::int16_t y) noexcept;
			void draw() override;
		};
	}
}

