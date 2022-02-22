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
			float analyseBarLengthPerMinutes(float bpm) const noexcept;
			void analyseBarLength(float bpm,float totalMinutes, std::uint16_t& barLength) const noexcept;
		public:
			Make_File_MusicAnalyse();
			void analyse(float bpm,float totalMinutes,std::uint16_t& barLength);
		};

	}
}