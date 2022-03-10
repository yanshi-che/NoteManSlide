#pragma once

#include <cstdint>

#include "dxlib/DxLib.h"
#include "Config_Config.h"

namespace Singleton {
	constexpr const std::uint16_t keySize{ 256 };
	class Singleton_KeyHitCheck
	{
	private:
		char buf[keySize];
		std::uint16_t key[keySize];

		Singleton_KeyHitCheck();
		static Singleton_KeyHitCheck* p_instance;
	public:
		static Singleton_KeyHitCheck* getInstance();
		static void destroyInstance();

		void checkHitKey();
		std::uint16_t getHitKeyLong(std::uint16_t keyNum);
		bool getHitKeyUsual(std::uint16_t keyNum);
	};
}

