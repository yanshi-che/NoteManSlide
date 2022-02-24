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

	if (buf[Global::lane0] == 1) {
		++key[Global::lane0];
	}
	else {
		key[Global::lane0] = 0;
	}

	if (buf[Global::lane1] == 1) {
		++key[Global::lane1];
	}
	else {
		key[Global::lane1] = 0;
	}

	if (buf[Global::lane2] == 1) {
		++key[Global::lane2];
	}
	else {
		key[Global::lane2] = 0;
	}

	if (buf[Global::lane3] == 1) {
		++key[Global::lane3];
	}
	else {
		key[Global::lane3] = 0;
	}

	if (buf[Global::lane4] == 1) {
		++key[Global::lane4];
	}
	else {
		key[Global::lane4] = 0;
	}

	if (buf[Global::lane5] == 1) {
		++key[Global::lane5];
	}
	else {
		key[Global::lane5] = 0;
	}

	if (buf[Global::laneLL] == 1) {
		++key[Global::laneLL];
	}
	else {
		key[Global::laneLL] = 0;
	}

	if (buf[Global::laneLR] == 1) {
		++key[Global::laneLR];
	}
	else {
		key[Global::laneLR] = 0;
	}

	if (buf[Global::laneRR] == 1) {
		++key[Global::laneRR];
	}
	else {
		key[Global::laneRR] = 0;
	}

	if (buf[Global::laneRL] == 1) {
		++key[Global::laneRL];
	}
	else {
		key[Global::laneRL] = 0;
	}
}

std::uint16_t Make::Singleton::Make_Singleton_KeyHitCheck::getHitKey(std::uint16_t keyNum) {
	return key[keyNum];
}