#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <functional>

#include "Make_File_MusicData.h"
#include "Make_Draw_LineContainer.h"
#include "Make_Draw_ScrollBar.h"

namespace Make {
	namespace Singleton {
		constexpr float yWidthRegular{ 150.0 }; //�����Ɣ����̋���
		constexpr float initialY = { 700.0 }; //�ꏬ�ߖڂ̏������W
		class Make_Singleton_BeatLineManager
		{
		private:
			std::shared_ptr<File::Make_File_MusicData> p_musicData; //�ǂݍ��񂾉��y�̃f�[�^
			std::vector<std::vector<std::shared_ptr<Draw::Make_Draw_LineContainer>>> barVec;//����
			std::unique_ptr<Draw::Make_Draw_ScrollBar> scrBar;
			float y;//�}�E�X�z�C�[���p�̕ϐ�
			float yMagnificationByMouseWheel;//�}�E�X�z�C�[�����͂ɂ��ړ��ʂ̔{��
			float totalScoreWidth;//�X�N���[���o�[�p�̃X�R�A�S�̂̑傫��
			std::function<void()> initBarLineFunction;//�`�揈�������ׂďI�������ɏ��������������邽�߂̊i�[�ϐ�
			std::uint8_t quontize;
			Singleton::Make_Singleton_NoteManager* p_noteManager;//�m�[�c�֘A�̐���N���X

			Make_Singleton_BeatLineManager();
			static Make_Singleton_BeatLineManager* p_instance;

			void checkSeparate(float& separate);
			void initScrollBar();
			void initAllBarLineByQuontize();
			void initOneBarLineByQuontize();
			void resetBarVec(bool isAll);
			void resetScrollBar();

		public:
			static Make_Singleton_BeatLineManager* getInstance();
			void destroyInstance();

			void initialize(std::uint8_t initialQuontize,float separateBarWidth);
			//void finalize();
			void setMusicData(const std::shared_ptr<File::Make_File_MusicData>& data);
			void setInitBarLineFunc(std::uint8_t quon, bool isAll);
			void draw();
		};
	}
}
