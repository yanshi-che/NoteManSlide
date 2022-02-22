#pragma once

#include "dxlib/DxLib.h"

namespace Make {
	namespace Play {
		class Make_Play_MusicPlayer
		{
		private:
			const int musicHandle;//�������ɓǂݍ��񂾉��y�t�@�C���̎��ʎq
			const int channels;//�`�����l����
			const int bitsPerSample;//�ʎq���r�b�g�[�x
			const int samplesParSec;//�T���v�����O���g�����擾
		public:
			Make_Play_MusicPlayer(const int musicHandle,const int channels,const int bitsPerSample,const int samplesParSec);
			~Make_Play_MusicPlayer();
		};
	}
}

