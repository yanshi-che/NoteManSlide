#pragma once

#include <cstdint>
#include <vector>
#include <cmath>
#include <memory>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include "dxlib/DxLib.h"
#include "Game_Note_NormalNoteContainer.h"
#include "Game_Singleton_NoteManager.h"
#include "Game_Singleton_MouseOperationCheck.h"

namespace Game {
	namespace Draw {
		class Game_Draw_LineContainer
		{
		private:
			static std::uint8_t noteType; //���͂���m�[�c�̃^�C�v�B�P�̎��͕��ʂ̃m�[�c�B2�̎��̓����O�m�[�c
			static bool clickObserver;//�}�E�X�N���b�N�ɂ�鑀��̐���ϐ�

			static int mouseX, mouseY;//�}�E�X�N���b�N�̍��W�i�[�p�̕ϐ�
			static std::uint16_t startBarIDForLongNote;//�����O�m�[�c�p�̔����Ǘ�
			static std::uint16_t startBeatIDForLongNote;//�����O�m�[�c�p�̏��ߊǗ�
			static std::uint8_t laneIDForLongNote;//�����O�m�[�c�p�̃��[���Ǘ�

			static std::uint16_t barIDForChangeQuontize;//���߂��Ƃ̃N�I���^�C�Y�ύX�̂��߂̕ϐ�

			Singleton::Game_Singleton_NoteManager* p_noteManager;
			Singleton::Game_Singleton_MouseOperationCheck* p_mouseCheck;

			const std::uint16_t barID; //�����ߖڂɑ����Ă��邩
			const std::uint16_t beatID;//���̏��߂̉��Ԗڂ̐���
			const float time;//�Ȃ̊J�n���牽�b��
			const std::uint8_t& amountOfLane; //���[���̐�
			float yMax;//���W�̍ő�l
			float yMin;//���W�̍ŏ��l
			std::uint32_t color;//�����̐F
			std::uint8_t lineThickness; //�����̑���
			float y; //�����̍��W
			std::vector<float> laneX;
			std::uint8_t barIDThickness; //���ߔԍ��̐��̑���
			std::uint32_t barIDColor;//���ߔԍ��̐F
			std::uint8_t barIDStrWidth;//���ߔԍ��̕����̑傫��
			std::string barIDStr;
			std::uint8_t brend;

			bool checkClickBorder();
			void drawNotes() ;
			void drawLine() ;
			void drawBarID() ;
		public:
			Game_Draw_LineContainer(std::uint16_t barID,std::uint8_t amountOfLane,float time,std::uint16_t beatID,float y,float yMax);
			static void setNoteType(std::uint8_t type) ;
			static std::uint16_t getbarIDForChangeQuontize();

			float getTime();
			float getY();
			float getYMin();
			float getYMax();

			void setYMin(float y);
			void updateYMax(float y);
			void updateByInitOneBar(float yWidth);
			void updateY(float y);
			void draw();
		};
	}
}