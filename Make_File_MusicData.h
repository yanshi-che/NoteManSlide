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
			const std::uint16_t barLength;//曲全体の小節数
			const float totalMinutes;//曲の再生時間(分)
			const std::uint16_t beginDelay;//曲が始まるまでのずれ
			const std::uint8_t amountOfLane;
			const int musicHandle;
		public:
			Make_File_MusicData(int musicHandle, std::string name, std::string artist, std::uint8_t level,std::uint16_t bpm,std::uint16_t barLength,float totalMinutes,std::uint16_t beginDelay,std::uint8_t amountOfLane);
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