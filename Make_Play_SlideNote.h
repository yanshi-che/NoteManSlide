#pragma once

#include <cstdint>
#include <functional>
#include <memory>

#include "dxlib/DxLib.h"
#include "Make_Global.h"
#include "Make_Play_Score.h"
#include "Make_Singleton_KeyHitCheck.h"

namespace Make {
	namespace Play {
		class Make_Play_SlideNote
		{
		private:
			Singleton::Make_Singleton_KeyHitCheck* p_keyHitCheck;
			const double time;//�m�[�c�̎���
			double y;
			const double laneXStart;
			const double laneXEnd;
			const double laneWidth;
			const double arrowWidthBetween;
			const std::uint8_t rightOrLeft;//�E�Ȃ�0 ���Ȃ�1
			const std::uint8_t directionRightOrLeft;//�E�����Ȃ�0 �������Ȃ�1
			const std::uint8_t noteType;
			const std::uint8_t slideLaneIndexStart;//�X���C�h�m�[�c�̊J�n���[��
			const std::uint8_t slideLaneIndexEnd;//�X���C�h�m�[�c�̏I�����[��
			const std::function<void(std::uint8_t, std::uint8_t)> nextNote;//��������̃m�[�c�Ɉڂ�
			const std::shared_ptr<Make_Play_Score>& p_score;//�X�R�A�\��
			std::uint32_t colorR;
			std::uint32_t colorL;
			std::uint16_t key;
			bool done; //�������I�������
			bool turn; //�������̏�������

			void drawLine();
			void drawArrow();
		public:
			Make_Play_SlideNote(const double time, const std::uint8_t noteType, const double laneXStart, const double laneXEnd, const double laneWidth,const double arrowWidthBetween,const std::uint8_t rightOrLeft, const std::uint8_t directionRightOrLeft,const std::uint8_t slideLaneIndexStart,const std::uint8_t slideLaneIndexEnd,const std::function<void(std::uint8_t, std::uint8_t)> nextNote, const std::shared_ptr<Make_Play_Score>& p_score);
			void check(double nowTime);
			void setTurn(bool t);
			void setDone(bool d);
			void update(double nowTime);
			void draw();
		};
	}
}

