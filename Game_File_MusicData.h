#pragma once

#include <cstdint>
namespace Game {
	namespace File {
		class Game_File_MusicData
		{
		private:
			const std::uint16_t bpm;
			const std::uint16_t barLength;//曲全体の小節数
			const double totalMinutes;//曲の再生時間(分)
			const double beginDelay;//曲が始まるまでのずれ
			const std::uint8_t numberOfRane;
			const int musicHandle;
		public:
			Game_File_MusicData(int musicHandle, std::uint16_t bpm, std::uint16_t barLength, double totalMinutes,double beginDelay,std::uint8_t numberOfRane);
			const std::uint16_t& getBpm() noexcept;
			const std::uint16_t& getBarLength() noexcept;
			const double& getTotalMinutes() noexcept;
			const double& getBeginDelay()noexcept;
			const std::uint8_t& getNumberOfRane() noexcept;
			const int& getMusicHandle() noexcept;
		};

	}
}