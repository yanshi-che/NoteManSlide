#include "Singleton_KeyHitCheck.h"

Singleton::Singleton_KeyHitCheck* Singleton::Singleton_KeyHitCheck::p_instance = nullptr;

Singleton::Singleton_KeyHitCheck::Singleton_KeyHitCheck() {
	for (int i = 0; i < keySize; ++i) {
		buf[i] = NULL;
		key[i] = NULL;
	}
}

Singleton::Singleton_KeyHitCheck* Singleton::Singleton_KeyHitCheck::getInstance() {
	if (p_instance == nullptr) {
		p_instance = new Singleton_KeyHitCheck();
	}
	return p_instance;
}

void Singleton::Singleton_KeyHitCheck::destroyInstance() {
	if (p_instance != nullptr) {
		delete p_instance;
		p_instance = nullptr;
	}
}

void Singleton::Singleton_KeyHitCheck::checkHitKey() {
	GetHitKeyStateAll(buf);//一度に通常のハードでは6個までしか入力を受け付けない

	if (buf[Config::g_lane0] == 1) {
		++key[Config::g_lane0];
	}
	else {
		key[Config::g_lane0] = 0;
	}

	if (buf[Config::g_lane1] == 1) {
		++key[Config::g_lane1];
	}
	else {
		key[Config::g_lane1] = 0;
	}

	if (buf[Config::g_lane2] == 1) {
		++key[Config::g_lane2];
	}
	else {
		key[Config::g_lane2] = 0;
	}

	if (buf[Config::g_lane3] == 1) {
		++key[Config::g_lane3];
	}
	else {
		key[Config::g_lane3] = 0;
	}

	if (buf[Config::g_lane4] == 1) {
		++key[Config::g_lane4];
	}
	else {
		key[Config::g_lane4] = 0;
	}

	if (buf[Config::g_lane5] == 1) {
		++key[Config::g_lane5];
	}
	else {
		key[Config::g_lane5] = 0;
	}

	if (buf[Config::g_laneLL] == 1) {
		++key[Config::g_laneLL];
	}
	else {
		key[Config::g_laneLL] = 0;
	}

	if (buf[Config::g_laneLR] == 1) {
		++key[Config::g_laneLR];
	}
	else {
		key[Config::g_laneLR] = 0;
	}

	if (buf[Config::g_laneRR] == 1) {
		++key[Config::g_laneRR];
	}
	else {
		key[Config::g_laneRR] = 0;
	}

	if (buf[Config::g_laneRL] == 1) {
		++key[Config::g_laneRL];
	}
	else {
		key[Config::g_laneRL] = 0;
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

	if (buf[KEY_INPUT_LEFT] == 1) {
		++key[KEY_INPUT_LEFT];
	}
	else {
		key[KEY_INPUT_LEFT] = 0;
	}

	if (buf[KEY_INPUT_RIGHT] == 1) {
		++key[KEY_INPUT_RIGHT];
	}
	else {
		key[KEY_INPUT_RIGHT] = 0;
	}
}

std::uint16_t Singleton::Singleton_KeyHitCheck::getHitKeyLong(std::uint16_t keyNum) {
	return key[keyNum];
}

bool Singleton::Singleton_KeyHitCheck::getHitKeyUsual(std::uint16_t keyNum) {
	if (buf[keyNum] == 1) {
		return true;
	}
	return false;
}