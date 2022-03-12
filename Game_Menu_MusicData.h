#pragma once

#include <cstdint>
#include <string>

namespace Game {
	namespace Menu {
		class Game_Menu_MusicData
		{
		private:
			const std::string musicPath;
			const std::string scorePath;
			const std::string name;
			const std::string artist;
			const std::uint16_t level;
			const double bpm;
			const std::uint16_t barLength;//‹È‘S‘Ì‚Ì¬ß”
			const double totalMinutes;//‹È‚ÌÄ¶ŠÔ(•ª)
			const double beginDelay;//‹È‚ªn‚Ü‚é‚Ü‚Å‚Ì‚¸‚ê
		public:
			Game_Menu_MusicData(const std::string& musicPath, const std::string& scorePath,const std::string& name, const std::string& artist, const std::uint16_t level, const double bpm, const std::uint16_t barLength, const double totalMinutes, const double beginDelay);
			const std::string& getMusicPath() noexcept;
			const std::string& getScorePath() noexcept;
			const std::string& getName() noexcept;
			const std::string& getArtist() noexcept;
			const std::uint16_t& getLevel() noexcept;
			const double& getBpm() noexcept;
			const std::uint16_t& getBarLength() noexcept;
			const double& getTotalMinutes() noexcept;
			const double& getBeginDelay()noexcept;
		};
	}
}

