#pragma once

#include <cstdint>

namespace Game {
	class Game_PlayResultShare
	{
	private:
		std::uint16_t perfect;
		std::uint16_t great;
		std::uint16_t miss;
		std::uint16_t score;
		bool isPlayToEnd;
		bool isClear;
	public:
		Game_PlayResultShare();
		void setPerfect(std::uint16_t perfect);
		void setGreat(std::uint16_t great);
		void setMiss(std::uint16_t miss);
		void setScore(std::uint16_t score);
		void setIsPlayToEnd(bool isPlayToEnd);
		void setIsClear(bool isClear);

		std::uint16_t getPerfect();
		std::uint16_t getGreat();
		std::uint16_t getMiss();
		std::uint16_t getScore();
		bool getIsPlayToEnd();
		bool getIsClear();
	};
}

