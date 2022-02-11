#pragma once

#include <boost/json.hpp>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "Make_File_BaseFile.h"
#include "Make_File_MusicData.h"
#include "Make_Singleton_NoteManager.h"
#include "Make_Note_NormalNoteContainer.h"
#include "Make_Note_LongNoteContainer.h"
#include "Make_Global.h"

using namespace boost;

namespace Make{
	namespace File {
		struct MusicData { //jsonファイル書き込み用の構造体
			std::string name;
			std::string artist;
			std::uint8_t level;
			std::uint16_t bpm;
			std::uint16_t barLength;//曲全体の小節数
			float totalMinutes;//曲の再生時間(分)
			std::uint16_t beginDelay;//曲が始まるまでのずれ
			std::uint8_t amountOfLane;
			MusicData(std::string name,std::string artist,std::uint8_t level,std::uint16_t bpm,std::uint16_t barLength,float totalMinutes, std::uint16_t beginDelay,std::uint8_t amountOfLane);
		};

		void tag_invoke(const json::value_from_tag&, json::value& jv, const MusicData& m);//valu_from用のオーバロード関数

		struct NoteData { //jsonファイル書き込み用の構造体
			float time;//ノーツの時間
			std::uint8_t noteType;//ノーツの種類 1ならNormal 2ならLong 3ならSlide
			std::uint8_t laneIndex;//ノーツが属するレーン
			std::uint16_t longNoteGroupIndex;//各ロングノーツが属するグループ
			std::uint16_t noteIndex;//そのレーンで何番目のノーツか
			std::uint8_t rightOrLeft;//1なら右 2なら左
			std::uint8_t sildeLaneIndexStart;//スライドノーツの開始レーン
			std::uint8_t sildeLaneIndexEnd;//スライドノーツの終了レーン
			NoteData(float time, std::uint8_t noteType, std::uint8_t laneIndex, std::uint16_t longNoteGroupIndex, std::uint16_t noteIndex, std::uint8_t rightOrLeft, std::uint8_t sildeLaneIndexStart, std::uint8_t sildeLaneIndexEnd);
		};

		void tag_invoke(const json::value_from_tag&, json::value& jv, const NoteData& n);//valu_from用のオーバロード関数

		class Make_File_JsonIO : public Make_File_BaseFile
		{
		private:
			void getFilePath(char (&filePath)[MAX_PATH]);
		public:
			void saveNewJson(Make_File_MusicData* const p_musicData);
		};
	}
}

