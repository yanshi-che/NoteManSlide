#pragma once
#include <cstdint>
#include <vector>
#include "dxlib/DxLib.h"
#include "Game_Global.h"


namespace Game {
	namespace Note {
		class Game_Note_NoteContainer
		{
		private:
			static std::uint8_t noteWidth; //�`�悷��m�[�c�̕��G
			const std::uint8_t* numberOfRane; //���[���̐�
			std::int32_t* y; //�����̍��W
			std::uint32_t color;
			std::vector<bool> notesFlag;
			std::vector<std::uint16_t> noteX;
			std::uint8_t notePoint;
		public:
			Game_Note_NoteContainer(std::int32_t* y,const std::uint8_t* numberOfRane);
			void setNoteFlag(std::uint8_t raneID);
			void drawNote();
			std::vector<bool>& getNoteFlag();
		};
	}
}

