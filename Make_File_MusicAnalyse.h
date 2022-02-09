#pragma once

#include <cstdint>
#include <cmath>

#include "Make_File_MusicData.h"
namespace Make {
	namespace File {
		class Make_File_MusicAnalyse
		{
		private:
			const std::uint8_t COUNTOFBEAT;
			float analyseBarLengthPerMinutes(std::uint16_t bpm) const noexcept;
			void analyseBarLength(std::uint16_t bpm,float totalMinutes, std::uint16_t& barLength) const noexcept;
		public:
			Make_File_MusicAnalyse();
			void analyse(std::uint16_t bpm,float totalMinutes,std::uint16_t& barLength);
		};

	}
}