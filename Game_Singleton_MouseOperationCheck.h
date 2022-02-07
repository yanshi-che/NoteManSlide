#pragma once

#include "dxlib/DxLib.h"

namespace Game {
	namespace Singleton {
		class Game_Singleton_MouseOperationCheck
		{
		private:
			static Game_Singleton_MouseOperationCheck* p_instance;
			Game_Singleton_MouseOperationCheck();
			bool mouseClickLeftDown, mouseClickLeftUp;
			int mouseX, mouseY;//�}�E�X�N���b�N�̍��W�i�[�p�̕ϐ�
			int button, logType;//�}�E�X�̃N���b�N�Ǘ�
		public:
			static  Game_Singleton_MouseOperationCheck* getInstance();
			void destroyInstance();
			void checkMouseClick();//�K�v�ƂȂ鏈���̍ŏ�ʂ̏����ŌĂԂ���
			bool isMouseClickLeftDown(int& x, int& y);//���W�̊l���ɂ͂�����g��
			bool isMouseClickLeftUp(int& x, int& y);//���W�̊l���ɂ͂�����g��
		};
	}
}

