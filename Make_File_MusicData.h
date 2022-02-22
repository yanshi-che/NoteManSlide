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
			const std::uint16_t barLength;//曲全体の小節数
			const float totalMinutes;//曲の再生時間(分)
			const std::uint16_t beginDelay;//曲が始まるまでのずれ
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