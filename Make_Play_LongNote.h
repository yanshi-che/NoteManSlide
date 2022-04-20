#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

#include "dxlib/DxLib.h"
#include "Global.h"
#include "Config_Config.h"
#include "Make_Play_Score.h"
#include "Singleton_KeyHitCheck.h"

namespace Make {
	namespace Play {
		class Make_Play_LongNote
		{
		private:
			::Singleton::Singleton_KeyHitCheck* p_keyHitCheck;
			const double startTime;//�����O�m�[�c�̎n�_�̎���
			const double endTime;//�����O�m�[�c�̏I�_�̎���
			const double laneXRight;
			const double laneXLeft;
			const std::uint16_t noteType;
			const std::uint16_t laneIndex;
			const std::function<void(std::uint16_t, std::uint16_t)> nextNote;//����𓯂����[���̎��̃m�[�c�Ɉڂ�
			const std::shared_ptr<Make_Play_Score>& p_score;//�X�R�A�\��
			std::vector<double> judgeTime;
			std::uint16_t judgeTimeCount;
			double nowJudgeTime;
			double y;
			double yUpdateBorderMin;
			double yUpdateBorderMax;
			double longNoteHeight;
			std::uint16_t alpha;
			std::int32_t noteColor;
			std::uint16_t key;
			bool done; //�������I�������
			bool turn; //�������̏�������
			bool isHit;
		public:
			Make_Play_LongNote(const double startTime,const double endTime, const double sixteenthTime, const std::uint16_t noteType,const std::uint16_t laneIndex, const double laneXRight,const double laneXLeft,const std::function<void(std::uint16_t, std::uint16_t)> nextNote, const std::shared_ptr<Make_Play_Score>& p_score);
			void check(double nowTime);
			void setTurn(bool t);
			void setDone(bool d);
			void setYUpdateBorder();
			void update(double nowTime);
			void updateKey();
			void draw(double nowTime);
		};
	}
}

