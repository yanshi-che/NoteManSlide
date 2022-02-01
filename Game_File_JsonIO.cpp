#include "Game_File_JsonIO.h"

Game::File::MusicData::MusicData(std::uint16_t bpm, std::uint16_t barLength, double totalMinutes, double beginDelay, std::uint8_t amountOfLane) {
	this->bpm = bpm;
	this->barLength = barLength;
	this->totalMinutes = totalMinutes;
	this->beginDelay = beginDelay;
	this->amountOfLane = amountOfLane;
}

void Game::File::tag_invoke(const json::value_from_tag&, json::value& jv, const MusicData& m) {
	jv = {
		{ "bpm", m.bpm },
		{ "barLength", m.barLength },
		{ "totalMinute", m.totalMinutes },
		{"beginDelay",m.beginDelay},
		{"amountOfLane",m.amountOfLane}
	};
}

Game::File::NoteData::NoteData(double time, std::uint8_t noteType, std::uint8_t laneIndex, bool longNoteType, std::uint16_t longNoteGroupIndex, std::uint16_t noteIndex) {
	this->time = time;
	this->noteType = noteType;
	this->laneIndex = laneIndex;
	this->longNoteType = longNoteType;
	this->longNoteGroupIndex = longNoteGroupIndex;
	this->noteIndex = noteIndex;
}

void Game::File::tag_invoke(const json::value_from_tag&, json::value& jv, const NoteData& n) {
	jv = {
		{ "time", n.time},
		{ "noteType", n.noteType },
		{ "laneIndex", n.laneIndex },
		{"longNoteType",n.longNoteType},
		{"longNoteGroupIndex",n.longNoteGroupIndex},
		{"noteIndex",n.noteIndex}
	};
}

void Game::File::Game_File_JsonIO::getFilePath(char (&filePath)[MAX_PATH]) {
	const char* title[] = { "�t�@�C���̕ۑ�" };
	const char* filter[] = { "json\0*.json\0\0" };
	File::Game_File_BaseFile gfb;
	gfb.openExplorer(title, filter, filePath, true);
}

void Game::File::Game_File_JsonIO::saveNewJson(Game_File_MusicData* p_musicData) {
	//�Z�[�u����t�@�C���̃p�X���擾
	char filePath[MAX_PATH] = "";//�Z�[�u����t�@�C���̃p�X
	getFilePath(filePath);
	if (filePath == "") {
		return;
	}

	//json�쐬�p�̕ϐ�
	json::object obj;
	json::value val;
	json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();

	//MusicDataObject�̍쐬
	val = json::value_from(MusicData(p_musicData->getBpm(),p_musicData->getBarLength(),p_musicData->getTotalMinutes(),p_musicData->getBeginDelay(),p_musicData->getAmountOfLane()),sp);
	obj["MusicData"] = val;

	//NotesDataObject�̍쐬
	std::vector<std::vector<std::shared_ptr<Note::Game_Note_NormalNoteContainer>>> normalNotes = Singleton::Game_Singleton_NoteManager::getInstance()->getNormalNoteVector();
	std::vector<std::vector<std::shared_ptr<Note::Game_Note_LongNoteContainer>>> longNotes = Singleton::Game_Singleton_NoteManager::getInstance()->getLongNoteVector();

	std::vector<NoteData> noteDataVector;
	std::vector<std::uint16_t> noteIndex;
	noteIndex.resize(p_musicData->getAmountOfLane());
	for (int i = 0, iSize = static_cast<int>(p_musicData->getAmountOfLane()); i < iSize; ++i) {
		noteIndex[i] = 0;
	}
	std::uint16_t longNoteGroupIndex = 1;
	bool isLongGroupLast = false;
	for (int i = 0, iSize = static_cast<int>(normalNotes.size()); i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(normalNotes[i].size()); k < kSize; ++k) {
			for (int l = 0, lSize = static_cast<int>(p_musicData->getAmountOfLane()); l < lSize; ++l) {
				if (normalNotes[i][k]->getNormalNoteFlag(l)) {
					noteDataVector.push_back(NoteData(normalNotes[i][k]->getTime(),Global::NOTETYPENORMAL,l,false,0,noteIndex[l]));
					++noteIndex[l];
				}
				else if(longNotes[i][k]->getLongNoteFlag(l).second){
					noteDataVector.push_back(NoteData(longNotes[i][k]->getTime(), Global::NOTETYPELONG, l, true, longNoteGroupIndex, noteIndex[l]));
					if (!isLongGroupLast) {
						isLongGroupLast = true;
					}
					else {
						isLongGroupLast = false;
						++noteIndex[l];
						++longNoteGroupIndex;
					}
				}
			}
		}
	}

	val = json::value_from(noteDataVector,sp);
	obj["NoteData"] = val;

	val = json::value(obj);

	std::ofstream writing_file;
	writing_file.open(filePath, std::ios::out);
	writing_file << val << std::endl;
	writing_file.close();
}