#pragma once

#include "dxlib/DxLib.h"

namespace Game {
	namespace Play {
		class Game_Play_SoundEffect
		{
		private:
			int soundEffectHandle;
		public:
			Game_Play_SoundEffect();
			~Game_Play_SoundEffect();
			void playSoundEffect();
		};
	}
}

