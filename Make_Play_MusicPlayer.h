#pragma once

#include "dxlib/DxLib.h"
#include <cstdint>

namespace Make {
	namespace Play {
		class Make_Play_MusicPlayer
		{
		private:
			const int musicHandle;//メモリに読み込んだ音楽ファイルの識別子
			const int channels;//チャンネル数
			const int bitsPerSample;//量子化ビット深度
			const int samplesParSec;//サンプリング周波数を取得
		public:
			Make_Play_MusicPlayer(const int musicHandle,const int channels,const int bitsPerSample,const int samplesParSec);
			~Make_Play_MusicPlayer();
			void startMusicFromHead();
			void startMusicFromMiddle();
			void stopMusic();
			void setMusicSec(std::uint16_t second);
			void forwardOneSec();
			void backOneSec();
			bool isMiddle();
		};
	}
}

