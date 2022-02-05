#pragma once

#include "dxlib/DxLib.h"

namespace Game {
	namespace Singleton {
		class Game_Singleton_MouseOperationCheck
		{
		private:
			static Game_Singleton_MouseOperationCheck* p_instance;
			Game_Singleton_MouseOperationCheck();
		public:
			static  Game_Singleton_MouseOperationCheck* getInstance();
			void destroyInstance();
			int  mouseX, mouseY; //�}�E�X�̃N���b�N�Ǘ�
			int button, logType;//�}�E�X�̃N���b�N�Ǘ�
			bool isMouseClickLeftDown();
			bool isMouseClickLeftUp();

		};
	}
}

