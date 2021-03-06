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
			const std::uint16_t level;
			const double bpm;
			const std::uint16_t barLength;//曲全体の小節数
			const double totalMinutes;//曲の再生時間(分)
			const double beginDelay;//曲が始まるまでのずれ
		public:
			Make_File_MusicData(const std::string& name,const std::string& artist,const std::uint16_t level,const double bpm,const std::uint16_t barLength,const double totalMinutes,const double beginDelay);
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