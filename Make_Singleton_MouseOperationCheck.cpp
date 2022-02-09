#include "Make_Singleton_MouseOperationCheck.h"

Make::Singleton::Make_Singleton_MouseOperationCheck*  Make::Singleton::Make_Singleton_MouseOperationCheck::p_instance = nullptr;

Make::Singleton::Make_Singleton_MouseOperationCheck::Make_Singleton_MouseOperationCheck() {
	mouseX = 0;
	mouseY = 0;
	logType = 0;
	button = 0;
	mouseClickLeftDown = false;
	mouseClickLeftUp = false;
}

Make::Singleton::Make_Singleton_MouseOperationCheck* Make::Singleton::Make_Singleton_MouseOperationCheck::getInstance() {
	if (p_instance == nullptr) {
		p_instance = new Make_Singleton_MouseOperationCheck();
	}
	return p_instance;
}

void Make::Singleton::Make_Singleton_MouseOperationCheck::destroyInstance() {
	delete p_instance;
}

void Make::Singleton::Make_Singleton_MouseOperationCheck::checkMouseClick() {
	if (GetMouseInputLog2(&button, &mouseX, &mouseY, &logType, true) && button == MOUSE_INPUT_LEFT) {
		if (logType == MOUSE_INPUT_LOG_DOWN) {
			mouseClickLeftDown = true;
		}
		if (logType == MOUSE_INPUT_LOG_UP) {
			mouseClickLeftUp = true;
		}
	}
	else {
		mouseClickLeftUp = false;
		mouseClickLeftDown = false;
	}
}

bool Make::Singleton::Make_Singleton_MouseOperationCheck::isMouseClickLeftDown(int& x, int& y) {
	if (mouseClickLeftDown) {
		x = mouseX;
		y = mouseY;
	}
	return mouseClickLeftDown;
}

bool Make::Singleton::Make_Singleton_MouseOperationCheck::isMouseClickLeftUp(int& x, int& y) {
	if (mouseClickLeftUp) {
		x = mouseX;
		y = mouseY;
	}
	return mouseClickLeftUp;
}