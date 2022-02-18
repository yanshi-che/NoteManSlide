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

void Make::File::Make_File_SaveFileIO::writeSaveData(const std::shared_ptr<Make_File_MusicData>& p_musicData) {
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
	obj["MusicData"] = json::value_from(MusicData(p_musicData->getName(), p_musicData->getArtist(), p_musicData->getLevel(), p_musicData->getBpm(), p_musicData->getBarLength(), p_musicData->getTotalMinutes(), p_musicData->getBeginDelay(), p_musicData->getAmountOfLane()), sp);

	//BarLineDataObject�̍쐬
	const std::vector<std::vector<std::shared_ptr<Draw::Make_Draw_LineContainer>>>& barVec = Singleton::Make_Singleton_BeatLineManager::getInstance()->getBarVec();

	std::vector<BarLineData> barLineDataVec;
	for (int i = 0, iSize = static_cast<int>(barVec.size()); i<iSize ; i++) {
		barLineDataVec.push_back(BarLineData(i,static_cast<std::uint8_t>(barVec.at(i).size())));
	}

	obj["BarLineData"] = json::value_from(barLineDataVec, sp);

	//NoteDataObject�̍쐬
	const std::vector<std::vector<std::shared_ptr<Note::Make_Note_NormalNoteContainer>>>& normalNote = Singleton::Make_Singleton_NoteManager::getInstance()->getNormalNoteVector();
	const std::vector<std::vector<std::shared_ptr<Note::Make_Note_LongNoteContainer>>>& longNote = Singleton::Make_Singleton_NoteManager::getInstance()->getLongNoteVector();
	const std::vector<std::vector<std::shared_ptr<Note::Make_Note_SlideNoteContainer>>>& slideNote = Singleton::Make_Singleton_NoteManager::getInstance()->getSlideNoteVector();

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
			for (int l = 0, lSize = static_cast<int>(p_musicData->getAmountOfLane()); l < lSize; ++l) {
				if (normalNote.at(i).at(k)->getNormalNoteFlag(l)) {
					noteDataVector.push_back(NoteDataForSave(normalNote.at(i).at(k)->getBarID(), normalNote.at(i).at(k)->getBeatID(), Global::NOTETYPENORMAL, l, NULL, NULL, NULL, NULL));
				}
				else if (longNote.at(i).at(k)->getLongNoteFlag(l).second) {
					for (int n = 0, nSize = static_cast<int>(longNotePointDeq.size()); n < nSize; ++n) {
						if (longNote.at(i).at(k)->getNoteGroup(l) == longNotePointDeq.at(n).oldIndex) {
							noteDataVector.push_back(NoteDataForSave(longNote.at(i).at(k)->getBarID(), longNote.at(i).at(k)->getBeatID(), Global::NOTETYPELONG, l, longNotePointDeq.at(n).newIndex, NULL, NULL, NULL));
							isLongGroupLast = true;
							longNotePointDeq.erase(longNotePointDeq.begin() + n);
							break;
						}
					}
					if (!isLongGroupLast) {
						noteDataVector.push_back(NoteDataForSave(longNote.at(i).at(k)->getBarID(), longNote.at(i).at(k)->getBeatID(), Global::NOTETYPELONG, l, longNoteGroupIndex, NULL, NULL, NULL));
						longNotePointDeq.push_back(longNotePoint(longNote.at(i).at(k)->getNoteGroup(l),longNoteGroupIndex));
						++longNoteGroupIndex;
					}
					isLongGroupLast = false;
				}
			}
			if (slideNote.at(i).at(k)->getSlideNoteFlag().first) {
				noteDataVector.push_back(NoteDataForSave(normalNote.at(i).at(k)->getBarID(), normalNote.at(i).at(k)->getBeatID(), Global::NOTETYPESLIDE, NULL,NULL, 1,
					slideNote.at(i).at(k)->getNoteStartAndEnd().first.first, slideNote.at(i).at(k)->getNoteStartAndEnd().first.second));
			}
			if (slideNote.at(i).at(k)->getSlideNoteFlag().second) {
				noteDataVector.push_back(NoteDataForSave(normalNote.at(i).at(k)->getBarID(), normalNote.at(i).at(k)->getBeatID(), Global::NOTETYPESLIDE, NULL,NULL, 2,
					slideNote.at(i).at(k)->getNoteStartAndEnd().second.first, slideNote.at(i).at(k)->getNoteStartAndEnd().second.second));
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

std::pair<std::unique_ptr<Make::File::Make_File_MusicData>, json::value> Make::File::Make_File_SaveFileIO::readSaveData() {
	//�Z�[�u����t�@�C���̃p�X���擾
	char saveFilePath[MAX_PATH] = "";//�Z�[�u�t�@�C���̃p�X
	char musicFilePath[MAX_PATH] = "";//���y�t�@�C���̃p�X
	getSaveFilePath(saveFilePath,musicFilePath);
	if (saveFilePath == "" || musicFilePath == "") {
		Dialog::Make_Dialog_FailFile f;
		std::string errSentence = "�t�@�C���ǂݍ��݂Ɏ��s���܂���";
		f.failFileDlg(errSentence);
		return std::pair<std::unique_ptr<Make::File::Make_File_MusicData>, json::value>(nullptr,NULL);
	}

	//json�쐬�p�̕ϐ�
	json::object obj;
	json::value val;
	json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();

	//���y�t�@�C�����������ɓW�J�ƃn���h���̓���
	int musicHandle = 0;//���y�t�@�C���̃n���h��
	try {
		musicHandle = LoadSoundMem(musicFilePath);
		if (musicHandle == -1) {
			throw "���y�t�@�C���̓ǂݍ��݂Ɏ��s���܂���";
		}
	}
	catch (const char *e) {
		Dialog::Make_Dialog_FailFile f;
		std::string errSentence(e, 37);
		f.failFileDlg(errSentence);
		return std::pair<std::unique_ptr<Make::File::Make_File_MusicData>, json::value>(nullptr, NULL);
	}

	//�t�@�C���̓ǂݍ���
	std::ifstream readfile(saveFilePath);
	std::string s = "";
	std::string line = "";
	while (std::getline(readfile, line)) {
		s.append(line);
	}

	//�ǂݍ��񂾃t�@�C���̕����񂩂�json�`���Ƀp�[�X
	val = json::parse(s,sp);

	//���y�f�[�^�̍쐬
	MusicData mData = json::value_to<MusicData>(val);
	std::unique_ptr<Make_File_MusicData> p_musicdataForReturn =
		std::make_unique<Make_File_MusicData>(musicHandle,mData.name,mData.artist,mData.level,mData.bpm,mData.barLength,mData.totalMinutes,mData.beginDelay,mData.amountOfLane);

	return std::pair<std::unique_ptr<Make::File::Make_File_MusicData>, json::value>(std::move(p_musicdataForReturn),val);
}