#pragma once

#include "dxlib/DxLib.h"

namespace Make {
	namespace Singleton {
		class Make_Singleton_MouseOperationCheck
		{
		private:
			static Make_Singleton_MouseOperationCheck* p_instance;
			Make_Singleton_MouseOperationCheck();
			bool mouseClickLeftDown, mouseClickLeftUp;
			int mouseX, mouseY;//�}�E�X�N���b�N�̍��W�i�[�p�̕ϐ�
			int button, logType;//�}�E�X�̃N���b�N�Ǘ�
		public:
			static Make_Singleton_MouseOperationCheck* getInstance();
			static void destroyInstance();
			void checkMouseClick();//�K�v�ƂȂ鏈���̍ŏ�ʂ̏����ŌĂԂ���
			bool isMouseClickLeftDown(int& x, int& y);//���W�̊l���ɂ͂�����g��
			bool isMouseClickLeftUp(int& x, int& y);//���W�̊l���ɂ͂�����g��
		};
	}
}

