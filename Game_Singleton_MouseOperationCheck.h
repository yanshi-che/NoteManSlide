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
			int button, logType;//マウスのクリック管理
			bool isMouseClickLeftDown(int* mouseX,int* mouseY);
			bool isMouseClickLeftUp(int* mouseX, int* mouseY);

		};
	}
}

