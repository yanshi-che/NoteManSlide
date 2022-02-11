#include "Make_File_JsonIO.h"

Make::File::MusicData::MusicData(std::string name, std::string artist, std::uint8_t level,std::uint16_t bpm, std::uint16_t barLength, float totalMinutes, std::uint16_t beginDelay, std::uint8_t amountOfLane) {
	this->name = name;
	this->artist = artist;
	this->level = level;
	this->bpm = bpm;
	this->barLength = barLength;
	this->totalMinutes = totalMinutes;
	this->beginDelay = beginDelay;
	this->amountOfLane = amountOfLane;
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
		{"amountOfLane",m.amountOfLane}
	};
}

Make::File::NoteData::NoteData(float time, std::uint8_t noteType, std::uint8_t laneIndex,std::uint16_t longNoteGroupIndex, std::uint16_t noteIndex, std::uint8_t rightOrLeft, std::uint8_t sildeLaneIndexStart, std::uint8_t sildeLaneIndexEnd) {
	this->time = time;
	this->noteType = noteType;
	this->laneIndex = laneIndex;
	this->longNoteGroupIndex = longNoteGroupIndex;
	this->noteIndex = noteIndex;
	this->rightOrLeft = rightOrLeft;
	this->sildeLaneIndexStart = sildeLaneIndexStart;
	this->sildeLaneIndexEnd = sildeLaneIndexEnd;
}

void Make::File::tag_invoke(const json::value_from_tag&, json::value& jv, const NoteData& n) {
	jv = {
		{ "time", n.time},
		{ "noteType", n.noteType },
		{ "laneIndex", n.laneIndex },
		{"longNoteGroupIndex",n.longNoteGroupIndex},
		{"noteIndex",n.noteIndex},
		{"rightOrLeft",n.rightOrLeft},
		{"sildeLaneIndexStart",n.sildeLaneIndexStart},
		{"sildeLaneIndexEnd",n.sildeLaneIndexEnd}
	};
}

void Make::File::Make_File_JsonIO::getFilePath(char (&filePath)[MAX_PATH]) {
	const char* title[] = { "ファイルの保存" };
	const char* filter[] = { "json\0*.json\0\0" };
	File::Make_File_BaseFile gfb;
	gfb.openExplorer(title, filter, filePath, true);
}

void Make::File::Make_File_JsonIO::saveNewJson(Make_File_MusicData* const p_musicData) {
	//セーブするファイルのパスを取得
	char filePath[MAX_PATH] = "";//セーブするファイルのパス
	getFilePath(filePath);
	if (filePath == "") {
		return;
	}

	//json作成用の変数
	json::object obj;
	json::value val;
	json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();

	//MusicDataObjectの作成
	obj["MusicData"] = json::value_from(MusicData(p_musicData->getName(), p_musicData->getArtist(), p_musicData->getLevel(),p_musicData->getBpm(),p_musicData->getBarLength(),p_musicData->getTotalMinutes(),p_musicData->getBeginDelay(),p_musicData->getAmountOfLane()),sp);

	//NotesDataObjectの作成
	std::vector<std::vector<std::shared_ptr<Note::Make_Note_NormalNoteContainer>>> normalNotes = Singleton::Make_Singleton_NoteManager::getInstance()->getNormalNoteVector();
	std::vector<std::vector<std::shared_ptr<Note::Make_Note_LongNoteContainer>>> longNotes = Singleton::Make_Singleton_NoteManager::getInstance()->getLongNoteVector();
	std::vector<std::vector<std::shared_ptr<Note::Make_Note_SlideNoteContainer>>> slideNotes = Singleton::Make_Singleton_NoteManager::getInstance()->getSlideNoteVector();

	std::vector<NoteData> noteDataVector;
	std::vector<std::uint16_t> noteIndex;
	noteIndex.resize(p_musicData->getAmountOfLane());
	for (int i = 0, iSize = static_cast<int>(p_musicData->getAmountOfLane()); i < iSize; ++i) {
		noteIndex.at(i) = 0;
	}
	std::uint16_t longNoteGroupIndex = 1;
	bool isLongGroupLast = false;
	for (int i = 0, iSize = static_cast<int>(normalNotes.size()); i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(normalNotes.at(i).size()); k < kSize; ++k) {
			for (int l = 0, lSize = static_cast<int>(p_musicData->getAmountOfLane()); l < lSize; ++l) {
				if (normalNotes.at(i).at(k)->getNormalNoteFlag(l)) {
					noteDataVector.push_back(NoteData(normalNotes.at(i).at(k)->getTime(),Global::NOTETYPENORMAL,l,NULL,noteIndex.at(l),NULL,NULL,NULL));
					++noteIndex.at(l);
				}
				else if(longNotes.at(i).at(k)->getLongNoteFlag(l).second){
					noteDataVector.push_back(NoteData(longNotes.at(i).at(k)->getTime(), Global::NOTETYPELONG, l,longNoteGroupIndex, noteIndex.at(l),NULL,NULL,NULL));
					if (!isLongGroupLast) {
						isLongGroupLast = true;
					}
					else {
						isLongGroupLast = false;
						++noteIndex.at(l);
						++longNoteGroupIndex;
					}
				}
			}
			if (slideNotes.at(i).at(k)->getSlideNoteFlag().first) {
				noteDataVector.push_back(NoteData(longNotes.at(i).at(k)->getTime(), Global::NOTETYPESLIDE, NULL, NULL, NULL, 1,
					slideNotes.at(i).at(k)->getNoteStartAndEnd().first.first, slideNotes.at(i).at(k)->getNoteStartAndEnd().first.second));
			}
			if (slideNotes.at(i).at(k)->getSlideNoteFlag().second) {
				noteDataVector.push_back(NoteData(longNotes.at(i).at(k)->getTime(), Global::NOTETYPESLIDE, NULL, NULL, NULL, 2,
					slideNotes.at(i).at(k)->getNoteStartAndEnd().second.first, slideNotes.at(i).at(k)->getNoteStartAndEnd().second.second));
			}
		}
	}

	obj["NoteData"] = json::value_from(noteDataVector,sp);

	val = json::value(obj);

	std::ofstream writeFile;
	writeFile.open(filePath, std::ios::out);
	writeFile << val << std::endl;
	writeFile.close();
}