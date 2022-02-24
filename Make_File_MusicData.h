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
			const double bpm;
			const std::uint16_t barLength;//�ȑS�̂̏��ߐ�
			const double totalMinutes;//�Ȃ̍Đ�����(��)
			const double beginDelay;//�Ȃ��n�܂�܂ł̂���
		public:
			Make_File_MusicData(const std::string& name,const std::string& artist,const std::uint8_t level,const double bpm,const std::uint16_t barLength,const double totalMinutes,const double beginDelay);
			const std::string& getName() noexcept;
			const std::string& getArtist() noexcept;
			const std::uint8_t& getLevel() noexcept;
			const double& getBpm() noexcept;
			const std::uint16_t& getBarLength() noexcept;
			const double& getTotalMinutes() noexcept;
			const double& getBeginDelay()noexcept;
		};

	}
}