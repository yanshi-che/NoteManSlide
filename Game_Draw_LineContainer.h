#pragma once

#include <cstdint>
#include <vector>
#include <cmath>
#include <memory>
#include "dxlib/DxLib.h"
#include "Game_Draw_BaseDraw.h"
#include "Game_Note_NoteContainer.h"
#include "Game_Singleton_NoteManager.h"

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
			static std::uint8_t clickWidth;//�����ɑ΂���}�E�X�N���b�N�̋��e��
			static bool clickObserver;//�}�E�X���N���b�N����đ����Ă��邩

			Singleton::Game_Singleton_NoteManager* noteManager;
			const std::uint16_t barID; //�����ߖڂɑ����Ă��邩
			const std::uint16_t beatID;//���̏��߂̉��Ԗڂ̐���
			const double time;//�Ȃ̊J�n���牽�b��
			const std::int32_t yMax;//���W�̍ő�l
			const std::int32_t yMin;//���W�̍ŏ��l
			const std::uint8_t* numberOfRane; //���[���̐�
			std::int32_t color;//�����̐F
			std::uint8_t lineThickness; //�����̑���
			std::int32_t y; //�����̍��W
			std::vector<std::uint16_t> raneX;

			static bool checkClick();
			static void initializeCheckClick();
			void drawNotes() noexcept;
			void drawLine() noexcept;
			void drawBarID() noexcept;
		public:
			Game_Draw_LineContainer(std::uint16_t barID, const std::uint8_t* numberOfRane, double time, std::uint16_t beatID, std::int32_t y,std::int32_t yMax);
			static void setNoteType(std::uint8_t type) noexcept;
			void updateY(std::int16_t y) noexcept;
			void draw() override;
		};
	}
}

