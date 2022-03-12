#include "Make_File_FileStructData.h"

Make::File::MusicData::MusicData(std::string name, std::string artist, std::uint16_t level, double bpm, std::uint16_t barLength, double totalMinutes, double beginDelay) {
	this->name = name;
	this->artist = artist;
	this->level = level;
	this->bpm = bpm;
	this->barLength = barLength;
	this->totalMinutes = totalMinutes;
	this->beginDelay = beginDelay;
}

void Make::File::tag_invoke(const json::value_from_tag&, json::value& jv, const MusicData& m) {
	jv = {
		{"name",m.name},
		{"artist",m.artist},
		{"level",m.level},
		{ "bpm", m.bpm },
		{ "barLength", m.barLength },
		{ "totalMinute", m.totalMinutes },
		{"beginDelay",m.beginDelay},
	};
}

Make::File::MusicData Make::File::tag_invoke(const json::value_to_tag<MusicData>&, const json::value& jv) {
	const json::value& val = jv.as_object().at("MusicData");
	return MusicData(std::string(val.at("name").as_string().c_str()),std::string(val.at("artist").as_string().c_str()),
		static_cast<std::uint16_t>(val.at("level").as_int64()), val.at("bpm").as_double(),
		static_cast<std::uint16_t>(val.at("barLength").as_int64()),val.at("totalMinute").as_double(),
		val.at("beginDelay").as_double());
}

Make::File::BarLineData::BarLineData(std::uint16_t barID,std::uint16_t quontize) {
	this->barID = barID;
	this->quontize = quontize;
}

void Make::File::tag_invoke(const json::value_from_tag&, json::value& jv, const BarLineData& b) {
	jv = {
		{"barID",b.barID},
		{"quontize",b.quontize}
	};
}

std::vector<Make::File::BarLineData> Make::File::tag_invoke(const json::value_to_tag<std::vector<BarLineData>>&, const json::value& jv) {
	std::vector<BarLineData> b;
	const json::array array = jv.as_object().at("BarLineData").as_array();
	for (int i = 0, iSize = static_cast<int>(array.size()); i < iSize; ++i) {
		b.push_back(BarLineData(static_cast<std::uint16_t>(array[i].at("barID").as_int64()),static_cast<std::uint16_t>(array[i].at("quontize").as_int64())));
	}
	return b;
}

Make::File::NoteDataForJson::NoteDataForJson(double time, std::uint16_t noteType, std::uint16_t laneIndex, std::uint16_t longNoteGroupIndex, std::uint16_t noteIndex, std::uint16_t rightOrLeft, std::uint16_t directionRightOrLeft, std::uint16_t slideLaneIndexStart, std::uint16_t slideLaneIndexEnd) {
	this->time = time;
	this->noteType = noteType;
	this->laneIndex = laneIndex;
	this->longNoteGroupIndex = longNoteGroupIndex;
	this->noteIndex = noteIndex;
	this->rightOrLeft = rightOrLeft;
	this->directionRightOrLeft = directionRightOrLeft;
	this->slideLaneIndexStart = slideLaneIndexStart;
	this->slideLaneIndexEnd = slideLaneIndexEnd;
}

void Make::File::tag_invoke(const json::value_from_tag&, json::value& jv, const NoteDataForJson& n) {
	jv = {
		{ "time", n.time},
		{ "noteType", n.noteType },
		{ "laneIndex", n.laneIndex },
		{"longNoteGroupIndex",n.longNoteGroupIndex},
		{"noteIndex",n.noteIndex},
		{"rightOrLeft",n.rightOrLeft},
		{"directionRightOrLeft",n.directionRightOrLeft},
		{"slideLaneIndexStart",n.slideLaneIndexStart},
		{"slideLaneIndexEnd",n.slideLaneIndexEnd}
	};
}

Make::File::NoteDataForSave::NoteDataForSave(std::uint16_t barID, std::uint16_t beatID, std::uint16_t noteType, std::uint16_t laneIndex, std::uint16_t longNoteGroupIndex, std::uint16_t rightOrLeft, std::uint16_t directionRightOrLeft, std::uint16_t slideLaneIndexStart, std::uint16_t slideLaneIndexEnd) {
	this->barID = barID;
	this->beatID = beatID;
	this->noteType = noteType;
	this->laneIndex = laneIndex;
	this->longNoteGroupIndex = longNoteGroupIndex;
	this->rightOrLeft = rightOrLeft;
	this->directionRightOrLeft = directionRightOrLeft;
	this->slideLaneIndexStart = slideLaneIndexStart;
	this->slideLaneIndexEnd = slideLaneIndexEnd;
}

void Make::File::tag_invoke(const json::value_from_tag&, json::value& jv, const NoteDataForSave& n) {
	jv = {
		{ "barID", n.barID},
		{ "beatID", n.beatID},
		{ "noteType", n.noteType },
		{ "laneIndex", n.laneIndex },
		{"longNoteGroupIndex",n.longNoteGroupIndex},
		{"rightOrLeft",n.rightOrLeft},
		{"directionRightOrLeft",n.directionRightOrLeft},
		{"slideLaneIndexStart",n.slideLaneIndexStart},
		{"slideLaneIndexEnd",n.slideLaneIndexEnd}
	};
}

std::vector<Make::File::NoteDataForSave> Make::File::tag_invoke(const json::value_to_tag<std::vector<NoteDataForSave>>&, const json::value& jv) {
	std::vector<NoteDataForSave> n;
	const json::array array = jv.as_object().at("NoteData").as_array();
	for (int i = 0,iSize = static_cast<int>(array.size()); i < iSize; ++i) {
		n.push_back(NoteDataForSave(
			static_cast<std::uint16_t>(array.at(i).at("barID").as_int64()),
			static_cast<std::uint16_t>(array.at(i).at("beatID").as_int64()),
			static_cast<std::uint16_t>(array.at(i).at("noteType").as_int64()),
			static_cast<std::uint16_t>(array.at(i).at("laneIndex").as_int64()),
			static_cast<std::uint16_t>(array.at(i).at("longNoteGroupIndex").as_int64()),
			static_cast<std::uint16_t>(array.at(i).at("rightOrLeft").as_int64()),
			static_cast<std::uint16_t>(array.at(i).at("directionRightOrLeft").as_int64()),
			static_cast<std::uint16_t>(array.at(i).at("slideLaneIndexStart").as_int64()),
			static_cast<std::uint16_t>(array.at(i).at("slideLaneIndexEnd").as_int64())));
	}
	return n;
}