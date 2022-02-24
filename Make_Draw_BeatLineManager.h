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
#include "Make_Note_NoteManager.h"

using namespace boost;

namespace Make {
	namespace Draw {
		constexpr double yWidthRegular{ 150.0 }; //�����Ɣ����̋���
		constexpr double initialY = { 700.0 }; //�ꏬ�ߖڂ̏������W
		class Make_Draw_BeatLineManager
		{
		private:
			std::shared_ptr<File::Make_File_MusicData> p_musicData; //�ǂݍ��񂾉��y�̃f�[�^
			std::shared_ptr<Note::Make_Note_NoteManager> p_noteManager;//�m�[�c�֘A�̐���N���X
			std::vector<std::vector<std::shared_ptr<Draw::Make_Draw_LineContainer>>> barVec;//����
			std::unique_ptr<Draw::Make_Draw_ScrollBar> scrBar;//�X�N���[���o�[�̕`��N���X
			std::unique_ptr<Make_Draw_LaneDraw> p_laneDraw;//���[���̕`��N���X

			double y;//�}�E�X�z�C�[���p�̕ϐ�
			double yMagnificationByMouseWheel;//�}�E�X�z�C�[�����͂ɂ��ړ��ʂ̔{��
			double totalScoreWidth;//�X�N���[���o�[�p�̃X�R�A�S�̂̑傫��
			std::function<void()> initBarLineFunction;//�`�揈�������ׂďI�������ɏ��������������邽�߂̊i�[�ϐ�
			std::uint8_t quontize;
			std::uint16_t barIDForInitOneVector;

			void draw();
			void initScrollBar();
			void initOtherClass();
			void initAllBarLineByQuontizeChange();
			void initOneBarLineByQuontizeChange();
			void resetBarVec(bool isAll);
			void resetScrollBar();

			double checkSeparate(const std::uint8_t quontize);

		public:
			Make_Draw_BeatLineManager();

			void finalize();
			void initialize(const std::shared_ptr<File::Make_File_MusicData>& data);
			void initBarVec(std::uint8_t initialQuontize,double separateBarWidth);
			void initializeBySavaData(const std::shared_ptr<File::Make_File_MusicData>& data,const json::value& val);
			void setInitBarLineFunc(const std::uint8_t quon,const std::uint16_t barIDForInitOneVector,const bool isAll);

			const std::function<void()> getDrawFunc();
			const std::vector<std::vector<std::shared_ptr<Draw::Make_Draw_LineContainer>>>& getBarVec();
			const std::shared_ptr<Note::Make_Note_NoteManager>& getNoteManager();
		};
	}
}
