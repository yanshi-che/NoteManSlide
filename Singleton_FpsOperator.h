#pragma once

#include "dxlib/DxLib.h"
#include "Global.h"
#include "Config_Config.h"

namespace Singleton {
	class Singleton_FpsOperator
	{
		LONGLONG nowTime;
		LONGLONG time;
		LONGLONG waitTime;
		const LONGLONG sixtyWaitTime;
		const LONGLONG oneHundredTwentyWaitTime;
		int configFps;
		int fps;
		int fpsCount;
		LONGLONG fpsCountTime;

		Singleton_FpsOperator();
		static Singleton_FpsOperator* p_instance;

	public:
		static Singleton_FpsOperator* getInstance();
		static void destroyInstance();

		void update();

		void drawFps();

		bool wait();

		bool waitForDialog();
	};
}

