#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <functional>

#include "dxlib/DxLib.h"
#include "Make_Singleton_MouseOperationCheck.h"
#include "Make_Draw_LineContainer.h"

namespace Make {
	namespace Draw {
		constexpr const double backWidth{ 20.0 };//�X�N���[���o�[�̔w�i�̕�
		constexpr const double barWidth{15.0};//�X�N���[���o�[�̕�
		constexpr const double barHeightMin{ 40.0 };//�X�N���[���o�[�̍Œ���̒���
		constexpr const double arrowWidthX{ 10.0 };//���̒��
		constexpr const double arrowWidthYAndSpace{ 5.0 };//���̍����ƃX�N���[���o�[�̔w�i�̒[����̋���
		constexpr const double yScrMax{ Global::WINDOW_HEIGHT - backWidth };//�X�N���[���o�[���W�̍ő�l
		constexpr const double yScrMin{ backWidth };//�X�N���[���o�[���W�̍ŏ��l
		class Make_Draw_ScrollBar
		{
		private:
			Singleton::Make_Singleton_MouseOperationCheck* p_mouseCheck;
			std::vector<std::vector<std::shared_ptr<Make_Draw_LineContainer>>>& barVec;
			int mouseX, mouseY;//�}�E�X�N���b�N�̍��W�i�[�p�̕ϐ�
			double  widthMaxOnClick, widthMinOnClick;//bar���N���b�N���Ă���Ƃ��̍ő�l�ŏ��l�����߂邽�߂̕ϐ�
			double barYBefore;//�ЂƂO�̃}�E�X��y���W���i�[
			double barHeight;//�o�[�̒���
			double scrollWidthRate;//�X�N���[���o�[�Ǝ��ۂ̉�ʂƂ̔䗦
			const double& yMagnificationByMouseWheel;//�}�E�X�z�C�[�����͂ɑ΂����ʈړ��̔{��
			std::int32_t backColor;
			std::int32_t barColor;
			std::int32_t arrowUpColor;
			std::int32_t arrowDownColor;
			double y;//bar��y���W
			bool clickObserver;//�N���b�N�̐���p
			double barPointX[2];//bar��x���W�i�[
			double arrowPointX[3];//�㉺���̒��_�̂����W
			double arrowPointY[4];//�㉺���̒��_�̂����W
			std::function<void()> function;//bar��������arrow��function�̊i�[

			void arrowFunction(const bool isUp);
			void barFunction();
			void borderCheck();
			void clickCheck();
			void drawBack();
			void drawArrow();
			void drawBar();
			void setBarY(const double sY);
			void updateLineContainerY(const double y);
		public:
			Make_Draw_ScrollBar(const double scrollWidth,std::vector<std::vector<std::shared_ptr<Make_Draw_LineContainer>>>& barVec,const double& yMagnificationByMouseWheel);
			void draw();
			void updateBarY(const double upY);
		};
	}
}


