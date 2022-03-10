#pragma once
#include <cstdint>
#include <vector>
#include "dxlib/DxLib.h"
#include "Global.h"


namespace Make {
	namespace Note {
		class Make_Note_NormalNoteContainer
		{
		private:
			static double noteWidth; //•`‰æ‚·‚éƒm[ƒc‚Ì•G
			const std::uint16_t barID; //‰½¬ß–Ú‚É‘®‚µ‚Ä‚¢‚é‚©
			const std::uint8_t beatID;//‚»‚Ì¬ß‚Ì‰½”Ô–Ú‚Ìü‚©
			const double time;//‹È‚ÌŠJn‚©‚ç‰½•b‚©
			const std::uint8_t laneAmount; //ƒŒ[ƒ“‚Ì”
			const double& r_y; //”ü‚ÌÀ•W
			std::uint32_t color;
			std::vector<bool> noteFlag;
			std::vector<double> noteX;
			double notePointX;
			double notePointY;
		public:
			Make_Note_NormalNoteContainer(const std::uint16_t barID,const std::uint8_t beatID,const double& y,const std::uint8_t amountOfLane,const double time);
			void setNormalNoteFlag(const std::uint8_t laneID);
			void drawNote();
			const bool getNormalNoteFlag(const std::uint8_t laneID);
			const double& getTime();
			const std::uint16_t& getBarID();
			const std::uint8_t& getBeatID();
		};
	}
}