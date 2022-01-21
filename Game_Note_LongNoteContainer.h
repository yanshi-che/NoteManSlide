#pragma once

#include <cstdint>
#include <vector>
#include <utility>
#include "dxlib/DxLib.h"
#include "Game_Global.h"

namespace Game {
	namespace Note {
		class Game_Note_LongNoteContainer
		{
		private:
			static std::uint8_t noteWidth; //�`�悷��m�[�c�̕��G
			const std::uint8_t* numberOfRane; //���[���̐�
			std::int32_t* y; //�����̍��W
			std::uint32_t color;
			std::vector<std::pair<bool,bool>> notesFlag;//first�̓m�[�c���Z�b�g����Ă��邩�Asecond�͂��ꂪ�n�_�܂��͏I�_��
			std::vector<std::uint16_t> notesX;
			std::vector<int32_t> notesHeight;
			std::uint8_t notePoint;
			std::vector<uint16_t> notesGroup;
		public:
			Game_Note_LongNoteContainer(std::int32_t* y, const std::uint8_t* numberOfRane);
			void setLongNoteFlag(std::uint8_t raneID,bool isFirstOrLast);//�m�[�c���Z�b�g���ɃZ�b�g����Ă���Ȃ�P��
			void drawLongNote();
			void setLongNoteFlagFirstOrLast(std::uint8_t raneID,bool is);
			void setNoteHeight(std::uint8_t raneID, std::int32_t noteHeight);
			void setNoteGroup(std::uint8_t raneID, std::uint16_t group);
			std::uint16_t getNoteGroup(std::uint8_t raneID);
			const std::int32_t& getY();
			std::pair<bool, bool> getLongNoteFlag(std::uint8_t raneID);
			std::vector<std::pair<bool, bool>>& getAllLongNoteFlag();
		};
	}
}

inline void Game::Note::Game_Note_LongNoteContainer::drawLongNote() {
	if (*y < Game::Global::WINDOW_HEIGHT && *y>0) {
		for (int i = 0, isize = notesFlag.size(); i < isize; ++i) {
			if (notesFlag[i].first && notesFlag[i].second) {
				DrawBox(notesX[i] - notePoint, *y - notePoint, notesX[i] + notePoint, *y + notePoint + notesHeight[i], color, true);
			}
		}
	}
}

