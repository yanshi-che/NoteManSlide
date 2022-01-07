#pragma once

#include <cstdint>
namespace Game {
	namespace File {
		class Game_File_MusicData
		{
		private:
			const std::uint16_t bpm;
			const std::uint16_t barLength;//�ȑS�̂̏��ߐ�
			const double totalMinutes;//�Ȃ̍Đ�����(��)
			const double beginDelay;//�Ȃ��n�܂�܂ł̂���
			const std::uint8_t numberOfRane;
			const int musicHandle;
		public:
			Game_File_MusicData(int musicHandle, std::uint16_t bpm, std::uint16_t barLength, double totalMinutes,double beginDelay,std::uint8_t numberOfRane);
			const std::uint16_t& getBpm() noexcept;
			const std::uint16_t& getBarLength() noexcept;
			const double& getTotalMinutes() noexcept;
			const double& getBeginDelay()noexcept;
			const std::uint8_t& getNumberOfRane() noexcept;
			const int& getMusicHandle() noexcept;
		};

	}
}