#pragma once

#include <boost/json.hpp>
#include <cstdint>
#include <functional>
#include <memory>
#include <deque>
#include <vector>


#include "Make_File_MusicData.h"
#include "Make_Draw_LineContainer.h"
#include "Make_Draw_ScrollBar.h"
#include "Make_Draw_LaneDraw.h"
#include "Make_Singleton_NoteManager.h"

using namespace boost;

namespace Make {
	namespace Singleton {
		constexpr float yWidthRegular{ 150.0 }; //�����Ɣ����̋���
		constexpr float initialY = { 700.0 }; //�ꏬ�ߖڂ̏������W
		class Make_Singleton_BeatLineManager
		{
		private:
			std::shared_ptr<File::Make_File_MusicData> p_musicData; //�ǂݍ��񂾉��y�̃f�[�^
			std::vector<std::vector<std::shared_ptr<Draw::Make_Draw_LineContainer>>> barVec;//����
			std::unique_ptr<Draw::Make_Draw_ScrollBar> scrBar;//�X�N���[���o�[�̕`��N���X
			std::unique_ptr<Make_Draw_LaneDraw> p_laneDraw;//���[���̕`��N���X
			float y;//�}�E�X�z�C�[���p�̕ϐ�
			float yMagnificationByMouseWheel;//�}�E�X�z�C�[�����͂ɂ��ړ��ʂ̔{��
			float totalScoreWidth;//�X�N���[���o�[�p�̃X�R�A�S�̂̑傫��
			std::function<void()> initBarLineFunction;//�`�揈�������ׂďI�������ɏ��������������邽�߂̊i�[�ϐ�
			std::uint8_t quontize;
			std::uint16_t barIDForInitOneVector;

			Make_Singleton_NoteManager* p_noteManager;//�m�[�c�֘A�̐���N���X

			Make_Singleton_BeatLineManager();
			static Make_Singleton_BeatLineManager* p_instance;

			void initScrollBar();
			void initSingletons();
			void initAllBarLineByQuontizeChange();
			void initOneBarLineByQuontizeChange();
			void resetBarVec(bool isAll);
			void resetScrollBar();

			float checkSeparate(const std::uint8_t quontize);

		public:
			static Make_Singleton_BeatLineManager* getInstance();
			static void destroyInstance();

			void finalize();
			void initialize(const std::shared_ptr<File::Make_File_MusicData>& data);
			void initBarVec(std::uint8_t initialQuontize,float separateBarWidth);
			void initializeBySavaData(const std::shared_ptr<File::Make_File_MusicData>& data,const json::value val);
			void setInitBarLineFunc(const std::uint8_t quon,const std::uint16_t barIDForInitOneVector,const bool isAll);
			void draw();

			const std::vector<std::vector<std::shared_ptr<Draw::Make_Draw_LineContainer>>>& getBarVec();
		};
	}
}
