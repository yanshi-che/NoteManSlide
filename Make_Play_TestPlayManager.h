#pragma once

#include <functional>
#include <deque>
#include <memory>
#include <vector>

#include "dxlib/DxLib.h"
#include "boost/json.hpp"
#include "Make_File_MusicData.h"
#include "Make_Play_MusicPlayer.h"
#include "Make_Play_Lane.h"
#include "Make_Play_BarLine.h"
#include "Make_Play_NormalNote.h"
#include "Make_Play_LongNote.h"
#include "Make_Play_SlideNote.h"
#include "Make_Play_Score.h"
#include "Make_Singleton_KeyHitCheck.h"

using namespace boost;

namespace Make {
	namespace Play {
		class Make_Play_TestPlayManager
		{
		private:
			std::shared_ptr<Make_Play_MusicPlayer> p_musicPlayer; //���y�Đ��p�N���X
			std::shared_ptr<Make_Play_Score> p_score;//�X�R�A�\��
			std::unique_ptr<Make_Play_Lane> p_lane;//���[������̕`��
			std::vector<std::unique_ptr<Make_Play_BarLine>> barLineVec; //���ߐ�
			//�e�m�[�c�i�[�p
			std::vector<std::vector<std::unique_ptr<Make_Play_NormalNote>>> normalNoteVec;//���[�����ƂɊi�[
			std::vector<std::vector<std::unique_ptr<Make_Play_LongNote>>> longNoteVec;//���[�����ƂɊi�[
			std::vector<std::vector<std::unique_ptr<Make_Play_SlideNote>>> slideNoteVec;//�E0����1���Ŋi�[
			//�e���[���̏������鏇�Ԃ������m�[�c�̊i�[�p
			std::vector<Make_Play_NormalNote*> normalNote;
			std::vector<Make_Play_LongNote*> longNote;
			std::vector<Make_Play_SlideNote*> slideNote;
			//�������鏇�Ԃ̃m�[�c�̃J�E���^
			std::vector<std::uint16_t> normalCount;
			std::vector<std::uint16_t> longCount;
			std::vector<std::uint16_t> slideCount;

			Singleton::Make_Singleton_KeyHitCheck* p_keyHitCheck;

			LONGLONG startClock;
			double nowTime;
			bool isStart;
			bool isMusicStart;

			double startDelay;
			std::int32_t strColor;
			std::int32_t downColor;

			void nextNote(const std::uint8_t noteType, const std::uint8_t laneIndex);//����𓯂����[���̎��̃m�[�c�Ɉڂ�
			void draw();
			void drawDown();
			void drawHiSpeed();
			void drawJudgeCorrection();
		public:
			Make_Play_TestPlayManager();
			void finalize();
			void initialize(const json::value& val,const std::shared_ptr<Make_Play_MusicPlayer>& p_musicPlayer,const std::shared_ptr<File::Make_File_MusicData>& p_musicData);
			void updateKey();
			const std::function<void()> getDrawFunc();
		};
	}
}

