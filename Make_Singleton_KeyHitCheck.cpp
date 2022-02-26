#include "Make_Singleton_KeyHitCheck.h"

Make::Singleton::Make_Singleton_KeyHitCheck* Make::Singleton::Make_Singleton_KeyHitCheck::p_instance = nullptr;

Make::Singleton::Make_Singleton_KeyHitCheck::Make_Singleton_KeyHitCheck() {
	for (int i = 0; i < keySize; ++i) {
		buf[i] = NULL;
		key[i] = NULL;
	}
}

Make::Singleton::Make_Singleton_KeyHitCheck* Make::Singleton::Make_Singleton_KeyHitCheck::getInstance() {
	if (p_instance == nullptr) {
		p_instance = new Make_Singleton_KeyHitCheck();
	}
	return p_instance;
}

void Make::Singleton::Make_Singleton_KeyHitCheck::destroyInstance() {
	if (p_instance != nullptr) {
		delete p_instance;
		p_instance = nullptr;
	}
}

void Make::Singleton::Make_Singleton_KeyHitCheck::checkHitKey() {
	GetHitKeyStateAll(buf);//一度に通常のハードでは6個までしか入力を受け付けない

	if (buf[Global::g_lane0] == 1) {
		++key[Global::g_lane0];
	}
	else {
		key[Global::g_lane0] = 0;
	}

	if (buf[Global::g_lane1] == 1) {
		++key[Global::g_lane1];
	}
	else {
		key[Global::g_lane1] = 0;
	}

	if (buf[Global::g_lane2] == 1) {
		++key[Global::g_lane2];
	}
	else {
		key[Global::g_lane2] = 0;
	}

	if (buf[Global::g_lane3] == 1) {
		++key[Global::g_lane3];
	}
	else {
		key[Global::g_lane3] = 0;
	}

	if (buf[Global::g_lane4] == 1) {
		++key[Global::g_lane4];
	}
	else {
		key[Global::g_lane4] = 0;
	}

	if (buf[Global::g_lane5] == 1) {
		++key[Global::g_lane5];
	}
	else {
		key[Global::g_lane5] = 0;
	}

	if (buf[Global::g_laneLL] == 1) {
		++key[Global::g_laneLL];
	}
	else {
		key[Global::g_laneLL] = 0;
	}

	if (buf[Global::g_laneLR] == 1) {
		++key[Global::g_laneLR];
	}
	else {
		key[Global::g_laneLR] = 0;
	}

	if (buf[Global::g_laneRR] == 1) {
		++key[Global::g_laneRR];
	}
	else {
		key[Global::g_laneRR] = 0;
	}

	if (buf[Global::g_laneRL] == 1) {
		++key[Global::g_laneRL];
	}
	else {
		key[Global::g_laneRL] = 0;
	}

	if (buf[KEY_INPUT_UP] == 1) {
		++key[KEY_INPUT_UP];
	}
	else {
		key[KEY_INPUT_UP] = 0;
	}

	if (buf[KEY_INPUT_DOWN] == 1) {
		++key[KEY_INPUT_DOWN];
	}
	else {
		key[KEY_INPUT_DOWN] = 0;
	}
}

std::uint16_t Make::Singleton::Make_Singleton_KeyHitCheck::getHitKeyForNote(std::uint16_t keyNum) {
	return key[keyNum];
}

bool Make::Singleton::Make_Singleton_KeyHitCheck::getHitKeyUsual(std::uint16_t keyNum) {
	if (buf[keyNum] == 1) {
		return true;
	}
	return false;
}