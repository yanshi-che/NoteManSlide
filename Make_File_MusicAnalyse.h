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
			double analyseBarLengthPerMinutes(double bpm) const noexcept;
			void analyseBarLength(double bpm,double totalMinutes, std::uint16_t& barLength) const noexcept;
		public:
			Make_File_MusicAnalyse();
			void analyse(double bpm,double totalMinutes,std::uint16_t& barLength);
		};

	}
}