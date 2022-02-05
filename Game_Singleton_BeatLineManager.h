#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <functional>

#include "Game_File_MusicData.h"
#include "Game_Draw_LineContainer.h"
#include "Game_Draw_ScrollBar.h"

namespace Game {
	namespace Singleton {
		constexpr float yWidthRegular{ 150.0 }; //�����Ɣ����̋���
		constexpr float initialY = { 700.0 }; //�ꏬ�ߖڂ̏������W
		class Game_Singleton_BeatLineManager
		{
		private:
			std::shared_ptr<File::Game_File_MusicData> p_musicData; //�ǂݍ��񂾉��y�̃f�[�^
			std::vector<std::vector<std::shared_ptr<Draw::Game_Draw_LineContainer>>> barVec;//����
			std::unique_ptr<Draw::Game_Draw_ScrollBar> scrBar;
			float y;//�}�E�X�z�C�[���p�̕ϐ�
			float yMagnificationByMouseWheel;//�}�E�X�z�C�[�����͂ɂ��ړ��ʂ̔{��
			std::function<void()> initBarLineFunction;
			std::uint8_t quontize;
			Singleton::Game_Singleton_NoteManager* p_noteManager;//�m�[�c�֘A�̐���N���X

			Game_Singleton_BeatLineManager();
			static Game_Singleton_BeatLineManager* p_instance;

			void initAllBarLineByQuontize();
			void initOneBarLineByQuontize();
			void resetBarVec(bool isAll);
			void resetScrollBar(bool isAll);
			void checkSeparate(float& separate);

		public:
			static Game_Singleton_BeatLineManager* getInstance();

			void destroyInstance();
			void initialize(std::uint8_t initialQuontize,float separateBarWidth);
			void initScrollBar(float scoreWidth);
			//void finalize();
			void setMusicData(const std::shared_ptr<File::Game_File_MusicData>& data);
			void setInitBarLineFunc(std::uint8_t quon, bool isAll);
			void draw();
		};
	}
}
