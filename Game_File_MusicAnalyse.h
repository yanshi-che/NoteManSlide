#pragma once

#include <cstdint>
#include <cmath>

#include "Game_File_MusicData.h"
namespace Game {
	namespace File {
		class Game_File_MusicAnalyse
		{
		private:
			const std::uint8_t COUNTOFBEAT;
			float analyseBarLengthPerMinutes(std::uint16_t bpm) const noexcept;
			void analyseBarLength(std::uint16_t bpm,float totalMinutes, std::uint16_t& barLength) const noexcept;
		public:
			Game_File_MusicAnalyse();
			void analyse(std::uint16_t bpm,float totalMinutes,std::uint16_t& barLength);
		};

	}
}