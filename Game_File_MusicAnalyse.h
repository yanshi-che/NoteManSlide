#pragma once

#include <cstdint>

#include "Game_File_MusicData.h"
namespace Game {
	namespace File {
		class Game_File_MusicAnalyse
		{
		private:
			void analyseTotalMinute();
			void analyseBarLength();
		public:
			void analyse(char (&filePath)[MAX_PATH],std::uint8_t& bpm,double& totalMinutes,double& beginDlay,int& musicHandle,std::uint16_t& barLength); //MusicData型のインスタンスをnewで返す。
		};

	}
}