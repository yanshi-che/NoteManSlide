#pragma once

#include <cstdint>
#include <functional>
#include <memory>

#include "dxlib/DxLib.h"
#include "Global.h"
#include "Config_Config.h"
#include "Make_Play_Score.h"
#include "Game_Play_effect.h"
#include "Game_Play_SoundEffect.h"
#include "Singleton_KeyHitCheck.h"

namespace Make {
	namespace Play {
		class Make_Play_NormalNote
		{
		private:
			::Singleton::Singleton_KeyHitCheck* p_keyHitCheck;
			const double time;//�m�[�c�̎���
			const double laneXRight;
			const double laneXLeft;
			const std::uint16_t noteType;
			const std::uint16_t laneIndex;
			const std::function<void(std::uint16_t , std::uint16_t)> nextNote;//����𓯂����[���̎��̃m�[�c�Ɉڂ�
			const std::shared_ptr<Make_Play_Score>& p_score;//�X�R�A�\��
			const std::shared_ptr<Game::Play::Game_Play_Effect>& p_effect;//�G�t�F�N�g
			const std::shared_ptr<Game::Play::Game_Play_SoundEffect>& p_soundEffect;//�T�E���h�G�t�F�N�g
			double y;
			double yUpdateBorderMin;
			double yUpdateBorderMax;
			std::int32_t noteColor;
			std::uint16_t key;
			bool done; //�������I�������
			bool turn; //�������̏�������
			bool isAuto;
		public:
			Make_Play_NormalNote(const double time, const std::uint16_t noteType, const std::uint16_t laneIndex, const double laneXRight,const double laneXLeft,const std::function<void(std::uint16_t, std::uint16_t)> nextNote, std::shared_ptr<Make_Play_Score>& p_score, const std::shared_ptr<Game::Play::Game_Play_Effect>& p_effect, const std::shared_ptr<Game::Play::Game_Play_SoundEffect>& p_soundEffect);
			void check(double nowTime);
			void setAuto();
			void setTurn(bool t);
			void setDone(bool d);
			void setYUpdateBorder();
			void update(double nowTime);
			void updateKey();
			void draw(double nowTime);
		};
	}
}

