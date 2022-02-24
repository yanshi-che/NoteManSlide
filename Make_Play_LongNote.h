#pragma once

#include <cstdint>
#include <functional>

#include "dxlib/DxLib.h"
#include "Make_Global.h"

namespace Make {
	namespace Play {
		class Make_Play_LongNote
		{
		private:
			const double startTime;//�����O�m�[�c�̎n�_�̎���
			const double endTime;//�����O�m�[�c�̏I�_�̎���
			const double laneXRight;
			const double laneXLeft;
			const std::uint8_t noteType;
			const std::uint8_t laneIndex;
			const std::function<void(std::uint8_t, std::uint8_t)> nextNote;//����𓯂����[���̎��̃m�[�c�Ɉڂ�
			double y;
			bool done; //�������I�������
			bool turn; //�������̏�������
		public:
			Make_Play_LongNote(const double startTime,const double endTime, const std::uint8_t noteType,const std::uint8_t laneIndex, const double laneXRight,const double laneXLeft,const std::function<void(std::uint8_t, std::uint8_t)> nextNote);
			void setTurn(bool t);
			void setDone(bool b);
			void update(double nowTime);
			void draw();
		};
	}
}

