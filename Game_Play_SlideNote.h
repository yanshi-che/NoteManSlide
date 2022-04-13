#pragma once

#include <cstdint>
#include <functional>
#include <memory>

#include "dxlib/DxLib.h"
#include "Global.h"
#include "Config_Config.h"
#include "Game_Play_Score.h"
#include "Game_Play_Effect.h"
#include "Singleton_KeyHitCheck.h"

namespace Game {
	namespace Play {
		class Game_Play_SlideNote
		{
		private:
			::Singleton::Singleton_KeyHitCheck* p_keyHitCheck;
			const double time;//�m�[�c�̎���
			const double laneXStart;
			const double laneXEnd;
			const double laneWidth;
			const double arrowWidthBetween;
			const std::uint16_t rightOrLeft;//�E�Ȃ�0 ���Ȃ�1
			const std::uint16_t directionRightOrLeft;//�E�����Ȃ�0 �������Ȃ�1
			const std::uint16_t noteType;
			const std::uint16_t slideLaneIndexStart;//�X���C�h�m�[�c�̊J�n���[��
			const std::uint16_t slideLaneIndexEnd;//�X���C�h�m�[�c�̏I�����[��
			const std::function<void(std::uint16_t, std::uint16_t)> nextNote;//��������̃m�[�c�Ɉڂ�
			const std::shared_ptr<Game_Play_Score>& p_score;//�X�R�A�\��
			const std::shared_ptr<Game_Play_Effect>& p_effect;//�G�t�F�N�g
			std::uint32_t colorRR;
			std::uint32_t colorRL;
			std::uint32_t colorLR;
			std::uint32_t colorLL;
			std::uint16_t key;
			double y;
			double yUpdateBorderMin;
			double yUpdateBorderMax;
			bool done; //�������I�������
			bool turn; //�������̏�������

			void drawLine();
			void drawArrow();
		public:
			Game_Play_SlideNote(const double time, const std::uint16_t noteType, const double laneXStart, const double laneXEnd, const double laneWidth, const double arrowWidthBetween, const std::uint16_t rightOrLeft, const std::uint16_t directionRightOrLeft, const std::uint16_t slideLaneIndexStart, const std::uint16_t slideLaneIndexEnd, const std::function<void(std::uint16_t, std::uint16_t)> nextNote, const std::shared_ptr<Game_Play_Score>& p_score, const std::shared_ptr<Game_Play_Effect>& p_effect);
			void check(double nowTime);
			void setTurn(bool t);
			void setDone(bool d);
			void setYUpdateBorder();
			void update(double nowTime);
			void updateKey();
			void draw();
		};
	}
}

