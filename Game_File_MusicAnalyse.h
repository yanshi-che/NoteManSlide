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
			double analyseBarLengthPerMinutes(std::uint8_t& bpm) const noexcept;
			void analyseBarLength(std::uint8_t& bpm,double& totalMinutes, std::uint16_t& barLength) const noexcept;
		public:
			Game_File_MusicAnalyse();
			void analyse(std::uint8_t& bpm,double& totalMinutes,double& beginDelay,std::uint16_t& barLength);
		};

	}
}