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
#include "Make_Note_NormalNoteContainer.h"
#include "Make_Note_NoteManager.h"
#include "Make_Singleton_MouseOperationCheck.h"

namespace Make {
	namespace Draw {
		class Make_Draw_LineContainer
		{
		private:
			static std::uint8_t noteType; //���͂���m�[�c�̃^�C�v�B�P�̎��͕��ʂ̃m�[�c�B2�̎��̓����O�m�[�c
			static bool clickObserver;//�}�E�X�N���b�N�ɂ�鑀��̐���ϐ�

			static int mouseX, mouseY;//�}�E�X�N���b�N�̍��W�i�[�p�̕ϐ�
			static std::uint8_t laneIDForLongNote;//�����O�m�[�c�p�̃��[���Ǘ�

			static std::uint16_t barIDForChangeQuontize;//���߂��Ƃ̃N�I���^�C�Y�ύX�̂��߂̕ϐ�

			const std::shared_ptr<Note::Make_Note_NoteManager>& p_noteManager;
			Singleton::Make_Singleton_MouseOperationCheck* p_mouseCheck;

			const std::uint16_t barID; //�����ߖڂɑ����Ă��邩
			const std::uint8_t beatID;//���̏��߂̉��Ԗڂ̐���
			const double time;//�Ȃ̊J�n���牽�b��
			const std::uint8_t laneAmount; //���[���̐�
			double yMax;//���W�̍ő�l
			double yMin;//���W�̍ŏ��l
			std::uint32_t color;//�����̐F
			std::uint8_t lineThickness; //�����̑���
			double y; //�����̍��W
			std::vector<double> laneX;
			std::uint8_t barIDThickness; //���ߔԍ��̐��̑���
			std::uint32_t barIDColor;//���ߔԍ��̐F
			std::uint8_t barIDStrWidth;//���ߔԍ��̕����̑傫��
			std::string barIDStr;
			std::uint8_t brend;

			bool checkClickBorder();
			void drawNote() ;
			void drawLine() ;
			void drawBarID() ;
		public:
			Make_Draw_LineContainer(const std::uint16_t barID,const double time,const std::uint8_t beatID,const double y,const double yMax,const std::shared_ptr<Note::Make_Note_NoteManager>& p_noteManager);
			static void setNoteType(const std::uint8_t type) ;
			static std::uint16_t getbarIDForChangeQuontize();

			void setYMin(const double y);
			void updateYMax(const double y);
			void updateByInitOneBar(const double yWidth);
			void updateY(const double y);
			void draw();

			double getTime();
			double getY();
			double getYMin();
			double getYMax();
		};
	}
}