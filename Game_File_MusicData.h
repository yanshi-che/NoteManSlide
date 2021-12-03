#pragma once

#include "dxlib/DxLib.h"
#include <cstdint>
namespace Game {
	namespace File {
		class Game_File_MusicData
		{
		private:
			const std::uint8_t bpm;
			const std::uint16_t barLength;
			const double totalMinutes;
			const double beginDelay;
			const int musicHandle;
		public:
			Game_File_MusicData(int musicHandle, std::uint8_t bpm, std::uint16_t barLength, double totalMinutes,double beginDelay);
			const std::uint8_t& getBpm() noexcept;
			const std::uint16_t& getBarLength() noexcept;
			const double& getTotalMinutes() noexcept;
			const double& getBeginDelay()noexcept;
			const int& getMusicHandle() noexcept;
		};

	}
}