#pragma once

#include <cstdint>
namespace Make {
	namespace File {
		class Make_File_MusicData
		{
		private:
			const std::uint16_t bpm;
			const std::uint16_t barLength;//�ȑS�̂̏��ߐ�
			const float totalMinutes;//�Ȃ̍Đ�����(��)
			const std::uint16_t beginDelay;//�Ȃ��n�܂�܂ł̂���
			const std::uint8_t amountOfLane;
			const int musicHandle;
		public:
			Make_File_MusicData(int musicHandle,std::uint16_t bpm,std::uint16_t barLength,float totalMinutes,std::uint16_t beginDelay,std::uint8_t amountOfLane);
			const std::uint16_t& getBpm() noexcept;
			const std::uint16_t& getBarLength() noexcept;
			const float& getTotalMinutes() noexcept;
			const std::uint16_t& getBeginDelay()noexcept;
			const std::uint8_t& getAmountOfLane() noexcept;
			const int& getMusicHandle() noexcept;
		};

	}
}