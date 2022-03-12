#include "Make_File_SaveFileIO.h"

void Make::File::Make_File_SaveFileIO::getFilePath(char(&filePath)[MAX_PATH]) {
	const char* title[] = { "�t�@�C���̕ۑ�" };
	const char* filter[] = { "noteman\0*.noteman\0\0" };
	File::Make_File_BaseFile gfb;
	gfb.openExplorer(title, filter, filePath, true);
}

void Make::File::Make_File_SaveFileIO::getSaveFilePath(char(&saveFilePath)[MAX_PATH], char(&musicFilePath)[MAX_PATH]) {
	Dialog::Make_Dialog_SaveFile dlg;
	dlg.getSaveFilePathFromDlg(saveFilePath, musicFilePath);
}

void Make::File::Make_File_SaveFileIO::writeSaveData(const std::shared_ptr<Make_File_MusicData>& p_musicData,const std::shared_ptr<Draw::Make_Draw_BeatLineManager>& p_beatLine) {
	//�Z�[�u����t�@�C���̃p�X���擾
	char filePath[MAX_PATH] = "";//�Z�[�u����t�@�C���̃p�X
	getFilePath(filePath);

	//json�쐬�p�̕ϐ�
	json::object obj;
	json::value val;
	json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();

	//MusicDataObject�̍쐬
	obj["MusicData"] = json::value_from(MusicData(p_musicData->getName(), p_musicData->getArtist(), p_musicData->getLevel(), p_musicData->getBpm(), p_musicData->getBarLength(), p_musicData->getTotalMinutes(), p_musicData->getBeginDelay()), sp);

	//BarLineDataObject�̍쐬
	const std::vector<std::vector<std::shared_ptr<Draw::Make_Draw_LineContainer>>>& barVec = p_beatLine->getBarVec();

	std::vector<BarLineData> barLineDataVec;
	for (int i = 0, iSize = static_cast<int>(barVec.size()); i<iSize ; i++) {
		barLineDataVec.push_back(BarLineData(i,static_cast<std::uint16_t>(barVec.at(i).size())));
	}

	obj["BarLineData"] = json::value_from(barLineDataVec, sp);

	//NoteDataObject�̍쐬
	const std::vector<std::vector<std::shared_ptr<Note::Make_Note_NormalNoteContainer>>>& normalNote = p_beatLine->getNoteManager()->getNormalNoteVector();
	const std::vector<std::vector<std::shared_ptr<Note::Make_Note_LongNoteContainer>>>& longNote = p_beatLine->getNoteManager()->getLongNoteVector();
	const std::vector<std::vector<std::shared_ptr<Note::Make_Note_SlideNoteContainer>>>& slideNote = p_beatLine->getNoteManager()->getSlideNoteVector();

	struct longNotePoint {//�I�_���ǂݍ��܂��܂�longNote�̎n�_����ۊǂ��邽�߂̂���
		std::uint16_t oldIndex;
		std::uint16_t newIndex;
		longNotePoint(std::uint16_t oldIndex, std::uint16_t newIndex) { this->oldIndex = oldIndex;  this->newIndex = newIndex; }
	};
	std::deque<longNotePoint> longNotePointDeq;//�I�_���ǂݍ��܂��܂�longNote�̎n�_����ۊ�
	std::vector<NoteDataForSave> noteDataVector;
	std::uint16_t longNoteGroupIndex = 1;
	bool isLongGroupLast = false;
	for (int i = 0, iSize = static_cast<int>(normalNote.size()); i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(normalNote.at(i).size()); k < kSize; ++k) {
			for (int l = 0, lSize = static_cast<int>(Global::LANE_AMOUNT); l < lSize; ++l) {
				if (normalNote.at(i).at(k)->getNormalNoteFlag(l)) {
					noteDataVector.push_back(NoteDataForSave(normalNote.at(i).at(k)->getBarID(), normalNote.at(i).at(k)->getBeatID(), Global::NOTETYPE_NORMAL, l, NULL, NULL,NULL, NULL, NULL));
				}
				else if (longNote.at(i).at(k)->getLongNoteFlag(l).second) {
					for (int n = 0, nSize = static_cast<int>(longNotePointDeq.size()); n < nSize; ++n) {
						if (longNote.at(i).at(k)->getNoteGroup(l) == longNotePointDeq.at(n).oldIndex) {
							noteDataVector.push_back(NoteDataForSave(longNote.at(i).at(k)->getBarID(), longNote.at(i).at(k)->getBeatID(), Global::NOTETYPE_LONG, l, longNotePointDeq.at(n).newIndex, NULL,NULL, NULL, NULL));
							isLongGroupLast = true;
							longNotePointDeq.erase(longNotePointDeq.begin() + n);
							break;
						}
					}
					if (!isLongGroupLast) {
						noteDataVector.push_back(NoteDataForSave(longNote.at(i).at(k)->getBarID(), longNote.at(i).at(k)->getBeatID(), Global::NOTETYPE_LONG, l, longNoteGroupIndex, NULL, NULL,NULL, NULL));
						longNotePointDeq.push_back(longNotePoint(longNote.at(i).at(k)->getNoteGroup(l),longNoteGroupIndex));
						++longNoteGroupIndex;
					}
					isLongGroupLast = false;
				}
			}
			if (slideNote.at(i).at(k)->getSlideNoteFlag().first) {
				if (slideNote.at(i).at(k)->getSlideNoteDirectionRightOrLeft().first) {
					noteDataVector.push_back(NoteDataForSave(normalNote.at(i).at(k)->getBarID(), normalNote.at(i).at(k)->getBeatID(), Global::NOTETYPE_SLIDER, NULL, NULL, 1,1,
						slideNote.at(i).at(k)->getNoteStartAndEnd().first.first, slideNote.at(i).at(k)->getNoteStartAndEnd().first.second));
				}
				else {
					noteDataVector.push_back(NoteDataForSave(normalNote.at(i).at(k)->getBarID(), normalNote.at(i).at(k)->getBeatID(), Global::NOTETYPE_SLIDER, NULL, NULL, 1, 2,
						slideNote.at(i).at(k)->getNoteStartAndEnd().first.first, slideNote.at(i).at(k)->getNoteStartAndEnd().first.second));
				}
			}
			if (slideNote.at(i).at(k)->getSlideNoteFlag().second) {
				if (slideNote.at(i).at(k)->getSlideNoteDirectionRightOrLeft().second) {
					noteDataVector.push_back(NoteDataForSave(normalNote.at(i).at(k)->getBarID(), normalNote.at(i).at(k)->getBeatID(), Global::NOTETYPE_SLIDEL, NULL, NULL, 2,1,
						slideNote.at(i).at(k)->getNoteStartAndEnd().second.first, slideNote.at(i).at(k)->getNoteStartAndEnd().second.second));
				}
				else {
					noteDataVector.push_back(NoteDataForSave(normalNote.at(i).at(k)->getBarID(), normalNote.at(i).at(k)->getBeatID(), Global::NOTETYPE_SLIDEL, NULL, NULL, 2,2,
						slideNote.at(i).at(k)->getNoteStartAndEnd().second.first, slideNote.at(i).at(k)->getNoteStartAndEnd().second.second));
				}
			}
		}
	}

	obj["NoteData"] = json::value_from(noteDataVector, sp);

	val = json::value(obj);

	std::ofstream writeFile;
	writeFile.open(filePath, std::ios::out);
	writeFile << val << std::endl;
	writeFile.close();
}

std::tuple<std::unique_ptr<Make::File::Make_File_MusicData>, std::unique_ptr<Make::Play::Make_Play_MusicPlayer>, json::value> Make::File::Make_File_SaveFileIO::readSaveData() {
	//�Z�[�u����t�@�C���̃p�X���擾
	char saveFilePath[MAX_PATH] = "";//�Z�[�u�t�@�C���̃p�X
	char musicFilePath[MAX_PATH] = "";//���y�t�@�C���̃p�X
	getSaveFilePath(saveFilePath,musicFilePath);

	if (saveFilePath[0] == NULL || musicFilePath[0] == NULL) {
		return std::tuple<std::unique_ptr<Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>, json::value>(nullptr, nullptr, NULL);
	}
	//json�쐬�p�̕ϐ�
	json::value val;
	json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();

	//���y�t�@�C�����������ɓW�J�ƃn���h���̓���
	int musicHandle = 0;//���y�t�@�C���̃n���h��
	int softSoundHandle = 0;
	int channels, bitsPerSample, samplesParSec;
	try {
		musicHandle = LoadSoundMem(musicFilePath);
		if (musicHandle == -1) {
			throw "���y�t�@�C���̓ǂݍ��݂Ɏ��s���܂���";
		}
		softSoundHandle = LoadSoftSound(musicFilePath);
		if (softSoundHandle == -1) {
			throw "�\�t�g�E�F�A�T�E���h�n���h���̓ǂݍ��݂Ɏ��s���܂���";
		}
		GetSoftSoundFormat(softSoundHandle, &channels, &bitsPerSample, &samplesParSec);
	}
	catch (const char *e) {
		Dialog::Make_Dialog_FailFile f;
		std::string errSentence(e, 37);
		f.failFileDlg(errSentence);
		return std::tuple<std::unique_ptr<Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>, json::value>(nullptr, nullptr,NULL);
	}
	DeleteSoftSound(softSoundHandle);

	//�t�@�C���̓ǂݍ���
	std::string s = "";
	std::string line = "";
	try {
		std::ifstream readfile(saveFilePath);
		if (!readfile) {
			throw "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���";
		}
		while (std::getline(readfile, line)) {
			s.append(line);
		}
	}
	catch (const char* e) {
		Dialog::Make_Dialog_FailFile f;
		std::string errSentence(e);
		f.failFileDlg(errSentence);
		return std::tuple<std::unique_ptr<Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>, json::value>(nullptr, nullptr, NULL);
	}

	//�ǂݍ��񂾃t�@�C���̕����񂩂�json�`���Ƀp�[�X
	val = json::parse(s,sp);

	MusicData mData = json::value_to<MusicData>(val);

	return std::tuple<std::unique_ptr<Make_File_MusicData>, std::unique_ptr<Play::Make_Play_MusicPlayer>, json::value>(std::make_unique<Make_File_MusicData>(mData.name, mData.artist, mData.level, mData.bpm, mData.barLength, mData.totalMinutes, mData.beginDelay),
		std::make_unique<Play::Make_Play_MusicPlayer>(musicHandle,channels,bitsPerSample,samplesParSec),val);
}