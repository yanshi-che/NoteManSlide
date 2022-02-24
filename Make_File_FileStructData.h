#pragma once

#include <boost/json.hpp>
#include <cstdint>
#include <string>
#include <vector>

using namespace boost;

namespace Make{
	namespace File {
		struct MusicData { //ファイル書き込み用の構造体
			std::string name;
			std::string artist;
			std::uint8_t level;
			double bpm;
			std::uint16_t barLength;//曲全体の小節数
			double totalMinutes;//曲の再生時間(分)
			double beginDelay;//曲が始まるまでのずれ
			MusicData(std::string name, std::string artist, std::uint8_t level, double bpm, std::uint16_t barLength, double totalMinutes, double beginDelay);
		};

		void tag_invoke(const json::value_from_tag&, json::value& jv, const MusicData& m);//valu_from用のオーバロード関数

		MusicData tag_invoke(const json::value_to_tag<MusicData>&, const json::value& jv);//jsonファイルパース用オーバーロード関数

		struct NoteDataForJson { //jsonファイル書き込み用の構造体
			double time;//ノーツの時間
			std::uint8_t noteType;//ノーツの種類 1ならNormal 2ならLong 3ならSlide
			std::uint8_t laneIndex;//ノーツが属するレーン
			std::uint16_t longNoteGroupIndex;//各ロングノーツが属するグループ
			std::uint16_t noteIndex;//そのレーンで何番目のノーツか
			std::uint8_t rightOrLeft;//1なら右 2なら左
			std::uint8_t directionRightOrLeft;//1なら右 2なら左
			std::uint8_t slideLaneIndexStart;//スライドノーツの開始レーン
			std::uint8_t slideLaneIndexEnd;//スライドノーツの終了レーン
			NoteDataForJson(double time, std::uint8_t noteType, std::uint8_t laneIndex, std::uint16_t longNoteGroupIndex, std::uint16_t noteIndex, std::uint8_t rightOrLeft, std::uint8_t directionRightOrLeft, std::uint8_t slideLaneIndexStart, std::uint8_t slideLaneIndexEnd);
		};

		void tag_invoke(const json::value_from_tag&, json::value& jv, const NoteDataForJson& n);//valu_from用のオーバロード関数

		struct BarLineData {
			std::uint16_t barID;
			std::uint8_t quontize;
			BarLineData(std::uint16_t barID,std::uint8_t quontize);
		};

		void tag_invoke(const json::value_from_tag&, json::value& jv, const BarLineData& b);//valu_from用のオーバロード関数
		std::vector<BarLineData> tag_invoke(const json::value_to_tag<std::vector<BarLineData>>&, const json::value& jv);//jsonファイルパース用オーバーロード関数

		struct NoteDataForSave { //saveファイル書き込み用の構造体
			std::uint16_t barID;
			std::uint8_t beatID;
			std::uint8_t noteType;//ノーツの種類 1ならNormal 2ならLong 3ならSlide
			std::uint8_t laneIndex;//ノーツが属するレーン
			std::uint16_t longNoteGroupIndex;//各ロングノーツが属するグループ
			std::uint8_t rightOrLeft;//1なら右 2なら左
			std::uint8_t directionRightOrLeft;//1なら右 2なら左
			std::uint8_t slideLaneIndexStart;//スライドノーツの開始レーン
			std::uint8_t slideLaneIndexEnd;//スライドノーツの終了レーン
			NoteDataForSave(std::uint16_t barID, std::uint8_t beatID, std::uint8_t noteType, std::uint8_t laneIndex, std::uint16_t longNoteGroupIndex, std::uint8_t rightOrLeft, std::uint8_t directionRightOrLeft, std::uint8_t slideLaneIndexStart, std::uint8_t slideLaneIndexEnd);
		};

		void tag_invoke(const json::value_from_tag&, json::value& jv, const NoteDataForSave& n);//valu_from用のオーバロード関数
		std::vector<NoteDataForSave> tag_invoke(const json::value_to_tag<std::vector<NoteDataForSave>>&, const json::value& jv);//jsonファイルパース用オーバーロード関数
	}
}

