#pragma once

#include <cstdint>
#include <functional>

#include "dxlib/DxLib.h"
#include "Make_Global.h"

namespace Make {
	namespace Play {
		class Make_Play_SlideNote
		{
		private:
			const double time;//�m�[�c�̎���
			double y;
			const double laneXRight;
			const double laneXLeft;
			const std::uint8_t rightOrLeft;//�E�Ȃ�0 ���Ȃ�1
			const std::uint8_t directionRightOrLeft;//�E�����Ȃ�0 �������Ȃ�1
			const std::uint8_t noteType;
			const std::uint8_t slideLaneIndexStart;//�X���C�h�m�[�c�̊J�n���[��
			const std::uint8_t slideLaneIndexEnd;//�X���C�h�m�[�c�̏I�����[��
			const std::function<void(std::uint8_t, std::uint8_t)> nextNote;//��������̃m�[�c�Ɉڂ�
			bool done; //�������I�������
			bool turn; //�������̏�������
		public:
			Make_Play_SlideNote(const double time, const std::uint8_t noteType, const double laneXRight, const double laneXLeft,const std::uint8_t rightOrLeft, const std::uint8_t directionRightOrLeft,const std::uint8_t slideLaneIndexStart,const std::uint8_t slideLaneIndexEnd,const std::function<void(std::uint8_t, std::uint8_t)> nextNote);
			void setTurn(bool t);
			void setDone(bool b);
			void update(double nowTime);
			void draw();
		};
	}
}

