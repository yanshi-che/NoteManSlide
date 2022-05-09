#include "Singleton_FpsOperator.h"

Singleton::Singleton_FpsOperator* Singleton::Singleton_FpsOperator::p_instance = nullptr;

Singleton::Singleton_FpsOperator::Singleton_FpsOperator() : sixtyWaitTime(16666), oneHundredTwentyWaitTime(8333) {
	time = GetNowHiPerformanceCount();
	if (Config::g_fps == 60) {
		waitTime = sixtyWaitTime;
		Global::g_fpsDiff = 1.0;
		configFps = 60;
	}
	else {
		waitTime = oneHundredTwentyWaitTime;
		Global::g_fpsDiff = 0.5;
		configFps = 120;
	}
	nowTime = 0;
	fpsCountTime = time;
	fpsCount = 0;
	fps = 0;
}


Singleton::Singleton_FpsOperator* Singleton::Singleton_FpsOperator::getInstance() {
	if (p_instance == nullptr) {
		p_instance = new Singleton_FpsOperator();
	}
	return p_instance;
}

void Singleton::Singleton_FpsOperator::destroyInstance() {
	if (p_instance != nullptr) {
		delete p_instance;
		p_instance = nullptr;
	}
}

void Singleton::Singleton_FpsOperator::update() {
	nowTime = GetNowHiPerformanceCount();
	Global::g_time = nowTime;
	if (configFps != Config::g_fps) {
		if (configFps != 60) {
			configFps = 60;
			waitTime = sixtyWaitTime;
		}
		else {
			configFps = 120;
			waitTime = oneHundredTwentyWaitTime;
		}
	}
}

void Singleton::Singleton_FpsOperator::drawFps() {
	++fpsCount;
	if (1000000 <= nowTime - fpsCountTime) {
		fps = fpsCount;
		fpsCount = 0;
		fpsCountTime = nowTime;
	}
	DrawFormatString(10, 10, GetColor(255, 255, 255), "%d", fps);
}

bool Singleton::Singleton_FpsOperator::wait() {
	if (waitTime <= nowTime - time) {
		time = nowTime;
		return true;
	}
	return false;
}

bool Singleton::Singleton_FpsOperator::waitForDialog() {
	if (100000 <= nowTime - time) {
		time = nowTime;
		return true;
	}
	return false;
}