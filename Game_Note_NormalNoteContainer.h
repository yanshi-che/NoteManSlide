#pragma once
#include <cstdint>
#include <vector>
#include "dxlib/DxLib.h"
#include "Game_Global.h"


namespace Game {
	namespace Note {
		class Game_Note_NormalNoteContainer
		{
		private:
			static std::uint8_t noteWidth; //•`‰æ‚·‚éƒm[ƒc‚Ì•G
			const std::uint16_t& r_barID; //‰½¬ß–Ú‚É‘®‚µ‚Ä‚¢‚é‚©
			const std::uint16_t& r_beatID;//‚»‚Ì¬ß‚Ì‰½”Ô–Ú‚Ìü‚©
			const double& r_time;//‹È‚ÌŠJn‚©‚ç‰½•b‚©
			const std::uint8_t& r_amountOfLane; //ƒŒ[ƒ“‚Ì”
			const std::int32_t& r_y; //”ü‚ÌÀ•W
			std::uint32_t color;
			std::vector<bool> notesFlag;
			std::vector<std::uint16_t> noteX;
			std::uint8_t notePoint;
		public:
			Game_Note_NormalNoteContainer(const std::uint16_t& barID, const std::uint16_t& beatID,const std::int32_t& y,const std::uint8_t& amountOfLane,const double& time);
			void setNormalNoteFlag(std::uint8_t laneID);
			void drawNote();
			const bool getNormalNoteFlag(std::uint8_t laneID);
			const std::vector<bool>& getAllNormalNoteFlag();
			const double& getTime();
			const std::uint16_t& getBarID();
			const std::uint16_t& getBeatID();
		};
	}
}