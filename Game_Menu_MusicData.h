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
			const std::string savePath;
			const std::string name;
			const std::string artist;
			const std::uint16_t level;
			const double bpm;
			const std::uint16_t barLength;//ã»ëSëÃÇÃè¨êﬂêî
			const double totalMinutes;//ã»ÇÃçƒê∂éûä‘(ï™)
			const double beginDelay;//ã»Ç™énÇ‹ÇÈÇ‹Ç≈ÇÃÇ∏ÇÍ
			bool isPerfect;
			bool isFullChain;
			bool isClear;
			bool isPlayed;
			std::uint16_t bestScore;
		public:
			Game_Menu_MusicData(const std::string& musicPath, const std::string& scorePath, const std::string& savePath,const std::string& name, const std::string& artist, const std::uint16_t level, const double bpm, const std::uint16_t barLength, const double totalMinutes, const double beginDelay);
			const std::string& getMusicPath() noexcept;
			const std::string& getScorePath() noexcept;
			const std::string& getSavePath() noexcept;
			const std::string& getName() noexcept;
			const std::string& getArtist() noexcept;
			const std::uint16_t& getLevel() noexcept;
			const double& getBpm() noexcept;
			const std::uint16_t& getBarLength() noexcept;
			const double& getTotalMinutes() noexcept;
			const double& getBeginDelay()noexcept;
			const bool& getIsPerfect() noexcept;
			const bool& getIsFullChain() noexcept;
			const bool& getIsClear() noexcept;
			const bool& getIsPlayed() noexcept;
			const std::uint16_t& getBestScore() noexcept;

			void setIsPerfect(const bool isPerfect) noexcept;
			void setIsFullChain(const bool isFullChain) noexcept;
			void setIsClear(const bool isClear) noexcept;
			void setIsPlayed(const bool isPlayed) noexcept;
			void setBestScore(const std::uint16_t bestScore) noexcept;
		};
	}
}

