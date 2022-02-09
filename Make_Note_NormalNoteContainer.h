#pragma once
#include <cstdint>
#include <vector>
#include "dxlib/DxLib.h"
#include "Make_Global.h"


namespace Make {
	namespace Note {
		class Make_Note_NormalNoteContainer
		{
		private:
			static float noteWidth; //•`‰æ‚·‚éƒm[ƒc‚Ì•G
			const std::uint16_t barID; //‰½¬ß–Ú‚É‘®‚µ‚Ä‚¢‚é‚©
			const std::uint16_t beatID;//‚»‚Ì¬ß‚Ì‰½”Ô–Ú‚Ìü‚©
			const float time;//‹È‚ÌŠJn‚©‚ç‰½•b‚©
			const std::uint8_t amountOfLane; //ƒŒ[ƒ“‚Ì”
			const float& r_y; //”ü‚ÌÀ•W
			std::uint32_t color;
			std::vector<bool> notesFlag;
			std::vector<float> noteX;
			float notePointX;
			float notePointY;
		public:
			Make_Note_NormalNoteContainer(std::uint16_t barID,std::uint16_t beatID,const float& y,std::uint8_t amountOfLane,float time);
			void setNormalNoteFlag(std::uint8_t laneID);
			void drawNote();
			const bool getNormalNoteFlag(std::uint8_t laneID);
			const float& getTime();
			const std::uint16_t& getBarID();
			const std::uint16_t& getBeatID();
		};
	}
}