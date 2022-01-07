#pragma once
#include <cstdint>
#include <vector>
#include "dxlib/DxLib.h"
#include "Game_Global.h"


namespace Game {
	namespace Draw {
		class Game_Draw_NoteContainer
		{
		private:
			static int button, mouseX, mouseY, logType; //�}�E�X�̃N���b�N�Ǘ��p
			static std::uint8_t noteWidth; //�`�悷��m�[�c�̕��G
			static std::uint8_t clickWidth;//�����ɑ΂���}�E�X�N���b�N�̋��e��
			static bool clickObserver;//�}�E�X���N���b�N����đ����Ă��邩
			const std::uint8_t noteID;//�����[���ڂ̃m�[�c��
			std::uint16_t raneX; //���[���̍��W
			std::uint16_t raneWidth;//���[���̕�
			std::int32_t* y; //�����̍��W
			bool noteFlag;
		public:
			Game_Draw_NoteContainer(std::int32_t* y, std::uint8_t noteID, std::uint16_t raneX, std::uint16_t raneWidth);
			void setNoteFlag();
			void drawNote();
			static bool checkClick();
			static void initializeCheckClick();
		};
	}
}

