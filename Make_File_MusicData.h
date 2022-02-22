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
			const float bpm;
			const std::uint16_t barLength;//‹È‘S‘Ì‚Ì¬ß”
			const float totalMinutes;//‹È‚ÌÄ¶ŠÔ(•ª)
			const std::uint16_t beginDelay;//‹È‚ªn‚Ü‚é‚Ü‚Å‚Ì‚¸‚ê
		public:
			Make_File_MusicData(const std::string& name,const std::string& artist,const std::uint8_t level,const float bpm,const std::uint16_t barLength,const float totalMinutes,const std::uint16_t beginDelay);
			const std::string& getName() noexcept;
			const std::string& getArtist() noexcept;
			const std::uint8_t& getLevel() noexcept;
			const float& getBpm() noexcept;
			const std::uint16_t& getBarLength() noexcept;
			const float& getTotalMinutes() noexcept;
			const std::uint16_t& getBeginDelay()noexcept;
		};

	}
}