#pragma once

#include <cstdint>
namespace Game {
	namespace File {
		class Game_File_MusicData
		{
		private:
			const std::uint16_t bpm;
			const std::uint16_t barLength;//曲全体の小節数
			const float totalMinutes;//曲の再生時間(分)
			const std::uint16_t beginDelay;//曲が始まるまでのずれ
			const std::uint8_t amountOfLane;
			const int musicHandle;
		public:
			Game_File_MusicData(int musicHandle,std::uint16_t bpm,std::uint16_t barLength,float totalMinutes,std::uint16_t beginDelay,std::uint8_t amountOfLane);
			const std::uint16_t& getBpm() noexcept;
			const std::uint16_t& getBarLength() noexcept;
			const float& getTotalMinutes() noexcept;
			const std::uint16_t& getBeginDelay()noexcept;
			const std::uint8_t& getAmountOfLane() noexcept;
			const int& getMusicHandle() noexcept;
		};

	}
}