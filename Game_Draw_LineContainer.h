#pragma once

#include <cstdint>
#include <vector>
#include <cmath>
#include <memory>
#include "dxlib/DxLib.h"
#include "Game_Draw_BaseDraw.h"
#include "Game_Note_NormalNoteContainer.h"
#include "Game_Singleton_NoteManager.h"

namespace Game {
	namespace Draw {
		class Game_Draw_LineContainer : public Game_Draw_BaseDraw
		{
		private:
			static std::uint8_t noteType; //���͂���m�[�c�̃^�C�v�B�P�̎��͕��ʂ̃m�[�c�B2�̎��̓����O�m�[�c
			static int button, mouseX, mouseY, logType; //�}�E�X�̃N���b�N�Ǘ�
			static bool clickObserver;//�}�E�X���N���b�N����đ����Ă��邩
			static bool longClickObserver;

			static std::uint16_t startBarIDForLongNote;//�����O�m�[�c�p�̔����Ǘ�
			static std::uint16_t startBeatIDForLongNote;//�����O�m�[�c�p�̏��ߊǗ�
			static std::uint8_t laneIDForLongNote;//�����O�m�[�c�p�̃��[���Ǘ�

			static std::uint16_t barIDForChangeQuontize;//���߂��Ƃ̃N�I���^�C�Y�ύX�̂��߂̕ϐ�

			Singleton::Game_Singleton_NoteManager* p_noteManager;
			const std::uint16_t barID; //�����ߖڂɑ����Ă��邩
			const std::uint16_t beatID;//���̏��߂̉��Ԗڂ̐���
			const double time;//�Ȃ̊J�n���牽�b��
			const std::uint8_t& r_amountOfLane; //���[���̐�
			std::int32_t yMax;//���W�̍ő�l
			std::int32_t yMin;//���W�̍ŏ��l
			std::int32_t color;//�����̐F
			std::uint8_t lineThickness; //�����̑���
			std::int32_t y; //�����̍��W
			std::vector<std::uint16_t> laneX;
			std::uint8_t barIDThickness; //���ߔԍ��̐��̑���
			std::int32_t barIDColor;//���ߔԍ��̐F
			std::uint8_t barIDStrWidth;//���ߔԍ��̕����̑傫��
			std::uint8_t brend;

			bool isMouseClickDown();
			bool isMouseClickUp();
			bool checkClickBorder();
			void drawNotes() ;
			void drawLine() ;
			void drawBarID() ;
		public:
			Game_Draw_LineContainer(std::uint16_t barID, const std::uint8_t& amountOfLane, double time, std::uint16_t beatID, std::int32_t y,std::int32_t yMax);
			static void setNoteType(std::uint8_t type) ;
			static std::uint16_t getbarIDForChangeQuontize();

			double getTime();
			std::int32_t getY();
			std::int32_t getYMin();
			std::int32_t getYMax();

			void setYMin(std::int32_t y);
			void updateYMax(std::int32_t y);
			void updateByInitOneBar(std::int32_t& yWidth);
			void updateY(std::int8_t& y);
			void draw() override;
		};
	}
}