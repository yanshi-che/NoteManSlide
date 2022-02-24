#pragma once

#include <cstdint>

#include "dxlib/DxLib.h"
#include "Make_Global.h"

namespace Make {
	namespace Singleton {
		constexpr const std::uint16_t keySize{ 256 };
		class Make_Singleton_KeyHitCheck
		{
		private:
			char buf[keySize];
			std::uint16_t key[keySize];

			Make_Singleton_KeyHitCheck();
			static Make_Singleton_KeyHitCheck* p_instance;
		public:
			static Make_Singleton_KeyHitCheck* getInstance();
			static void destroyInstance();

			void checkHitKey();
			std::uint16_t getHitKey(std::uint16_t keyNum);
		};
	}
}

