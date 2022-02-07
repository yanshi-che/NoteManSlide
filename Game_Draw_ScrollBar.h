#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "dxlib/DxLib.h"
#include "Game_Singleton_MouseOperationCheck.h"
#include "Game_Draw_LineContainer.h"

namespace Game {
	namespace Draw {
		constexpr const float backWidth{ 20.0f };
		constexpr const float barWidth{15.0f};
		constexpr const float barHeightMin{ 40.0f };
		constexpr const float arrowWidthX{ 10.0f };
		constexpr const float arrowWidthYAndSpace{ 5.0f };
		constexpr const float yScrMax{ Global::WINDOW_HEIGHT - backWidth };
		constexpr const float yScrMin{ backWidth };
		class Game_Draw_ScrollBar
		{
		private:
			Singleton::Game_Singleton_MouseOperationCheck* p_mouseCheck;
			std::vector<std::vector<std::shared_ptr<Game_Draw_LineContainer>>>& barVec;
			int mouseX, mouseY;//�}�E�X�N���b�N�̍��W�i�[�p�̕ϐ�
			float  widthMaxOnClick, widthMinOnClick;//bar���N���b�N���Ă���Ƃ��̍ő�l�ŏ��l�����߂邽�߂̕ϐ�
			float barYBefore;
			float barHeight;//�o�[�̒���
			float scrollWidthRate;//�X�N���[���o�[�Ǝ��ۂ̉�ʂƂ̔䗦
			float& yMagnificationByMouseWheel;//�}�E�X�z�C�[�����͂ɑ΂����ʈړ��̔{��
			std::int32_t backColor;
			std::int32_t barColor;
			std::int32_t arrowUpColor;
			std::int32_t arrowDownColor;
			float y;//bar��y���W
			bool clickObserver;//�N���b�N�̐���p
			float barPointX[2];//bar��x���W�i�[
			float arrowPointX[3];//�㉺���̒��_�̂����W
			float arrowPointY[4];//�㉺���̒��_�̂����W

			void drawBack();
			void drawArrow();
			void drawBar();
			void updateLineContainerY(float y);
			void setBarY(float sY);
			void clickCheck();
			void borderCheck();
		public:
			Game_Draw_ScrollBar(float scrollWidth, std::vector<std::vector<std::shared_ptr<Game_Draw_LineContainer>>>& barVec, float& yMagnificationByMouseWheel);
			void updateBarY(float upY);
			void draw();
		};
	}
}

