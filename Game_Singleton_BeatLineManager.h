#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <functional>

#include "Game_Draw_BaseDraw.h"
#include "Game_File_MusicData.h"
#include "Game_Draw_LineContainer.h"

namespace Game {
	namespace Singleton {
		constexpr std::uint8_t yWidthRegular{ 50 }; //�����Ɣ����̋���
		constexpr std::uint16_t initialY = { 700 }; //�ꏬ�ߖڂ̏������W
		class Game_Singleton_BeatLineManager : public Draw::Game_Draw_BaseDraw
		{
		private:
			File::Game_File_MusicData* musicData; //�ǂݍ��񂾉��y�̃f�[�^
			std::vector<std::vector<std::unique_ptr<Draw::Game_Draw_LineContainer>>> barVec;//����
			std::int8_t y;//�}�E�X�z�C�[���p�̕ϐ�
			std::uint8_t yMagnification;//�}�E�X�z�C�[�����͂ɂ��ړ���
			std::function<void()> initBarLineFunction;
			std::uint8_t quontize;
			Singleton::Game_Singleton_NoteManager* noteManager;//�m�[�c�֘A�̐���N���X

			Game_Singleton_BeatLineManager();
			static Game_Singleton_BeatLineManager* instance;
			void initAllBarLineByQuontize();
			void initOneBarLineByQuontize();
			void resetBarVec(bool isAll);
			void checkSeparate(double& separate);

		public:
			static Game_Singleton_BeatLineManager* getInstance();
			void destroyInstance();
			void setMusicData(File::Game_File_MusicData* data);
			void initialize(std::uint8_t initialQuontize, double separateBarWidth);
			//void finalize() override;
			void draw() override;
			void setInitBarLineFunc(std::uint8_t quon, bool isAll);
		};
	}
}

inline void Game::Singleton::Game_Singleton_BeatLineManager::draw() {
	if (musicData != nullptr) {
		y = GetMouseWheelRotVol() * yMagnification;
		for (int i = 0,isize = barVec.size(); i < isize; ++i) {
			for (int k = 0, ksize= barVec[i].size(); k < ksize; ++k) {
				barVec[i][k]->updateY(y);
				barVec[i][k]->draw();
			}
		}
		if (initBarLineFunction != nullptr) {
			initBarLineFunction();
			initBarLineFunction = nullptr;
		}
	}
}
