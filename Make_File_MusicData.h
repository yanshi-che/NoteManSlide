#pragma once

#include <cstdint>
#include <string>

namespace Make {
	namespace File {
		class Make_File_MusicData
		{
		private:
			const std::string name;
			const std::string artist;
			const std::uint8_t level;
			const std::uint16_t bpm;
			const std::uint16_t barLength;//‹È‘S‘Ì‚Ì¬ß”
			const float totalMinutes;//‹È‚ÌÄ¶ŠÔ(•ª)
			const std::uint16_t beginDelay;//‹È‚ªn‚Ü‚é‚Ü‚Å‚Ì‚¸‚ê
			const std::uint8_t amountOfLane;
			const int musicHandle;
		public:
			Make_File_MusicData(const int musicHandle,const std::string& name,const std::string& artist,const std::uint8_t level,const std::uint16_t bpm,const std::uint16_t barLength,const float totalMinutes,const std::uint16_t beginDelay,const std::uint8_t amountOfLane);
			const std::string& getName() noexcept;
			const std::string& getArtist() noexcept;
			const std::uint8_t& getLevel() noexcept;
			const std::uint16_t& getBpm() noexcept;
			const std::uint16_t& getBarLength() noexcept;
			const float& getTotalMinutes() noexcept;
			const std::uint16_t& getBeginDelay()noexcept;
			const std::uint8_t& getAmountOfLane() noexcept;
			const int& getMusicHandle() noexcept;
		};

	}
}