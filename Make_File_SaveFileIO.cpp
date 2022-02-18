#include "Make_File_SaveFileIO.h"

void Make::File::Make_File_SaveFileIO::getFilePath(char(&filePath)[MAX_PATH]) {
	const char* title[] = { "ファイルの保存" };
	const char* filter[] = { "noteman\0*.noteman\0\0" };
	File::Make_File_BaseFile gfb;
	gfb.openExplorer(title, filter, filePath, true);
}

void Make::File::Make_File_SaveFileIO::getSaveFilePath(char(&saveFilePath)[MAX_PATH], char(&musicFilePath)[MAX_PATH]) {
	Dialog::Make_Dialog_SaveFile dlg;
	dlg.getSaveFilePathFromDlg(saveFilePath, musicFilePath);
}

void Make::File::Make_File_SaveFileIO::writeSaveData(const std::shared_ptr<Make_File_MusicData>& p_musicData) {
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
	obj["MusicData"] = json::value_from(MusicData(p_musicData->getName(), p_musicData->getArtist(), p_musicData->getLevel(), p_musicData->getBpm(), p_musicData->getBarLength(), p_musicData->getTotalMinutes(), p_musicData->getBeginDelay(), p_musicData->getAmountOfLane()), sp);

	//BarLineDataObjectの作成
	const std::vector<std::vector<std::shared_ptr<Draw::Make_Draw_LineContainer>>>& barVec = Singleton::Make_Singleton_BeatLineManager::getInstance()->getBarVec();

	std::vector<BarLineData> barLineDataVec;
	for (int i = 0, iSize = static_cast<int>(barVec.size()); i<iSize ; i++) {
		barLineDataVec.push_back(BarLineData(i,static_cast<std::uint8_t>(barVec.at(i).size())));
	}

	obj["BarLineData"] = json::value_from(barLineDataVec, sp);

	//NoteDataObjectの作成
	const std::vector<std::vector<std::shared_ptr<Note::Make_Note_NormalNoteContainer>>>& normalNote = Singleton::Make_Singleton_NoteManager::getInstance()->getNormalNoteVector();
	const std::vector<std::vector<std::shared_ptr<Note::Make_Note_LongNoteContainer>>>& longNote = Singleton::Make_Singleton_NoteManager::getInstance()->getLongNoteVector();
	const std::vector<std::vector<std::shared_ptr<Note::Make_Note_SlideNoteContainer>>>& slideNote = Singleton::Make_Singleton_NoteManager::getInstance()->getSlideNoteVector();

	struct longNotePoint {//終点が読み込まれるまでlongNoteの始点情報を保管するためのもの
		std::uint16_t oldIndex;
		std::uint16_t newIndex;
		longNotePoint(std::uint16_t oldIndex, std::uint16_t newIndex) { this->oldIndex = oldIndex;  this->newIndex = newIndex; }
	};
	std::deque<longNotePoint> longNotePointDeq;//終点が読み込まれるまでlongNoteの始点情報を保管
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
	//セーブするファイルのパスを取得
	char saveFilePath[MAX_PATH] = "";//セーブファイルのパス
	char musicFilePath[MAX_PATH] = "";//音楽ファイルのパス
	getSaveFilePath(saveFilePath,musicFilePath);
	if (saveFilePath == "" || musicFilePath == "") {
		Dialog::Make_Dialog_FailFile f;
		std::string errSentence = "ファイル読み込みに失敗しました";
		f.failFileDlg(errSentence);
		return std::pair<std::unique_ptr<Make::File::Make_File_MusicData>, json::value>(nullptr,NULL);
	}

	//json作成用の変数
	json::object obj;
	json::value val;
	json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();

	//音楽ファイルをメモリに展開とハンドルの入手
	int musicHandle = 0;//音楽ファイルのハンドル
	try {
		musicHandle = LoadSoundMem(musicFilePath);
		if (musicHandle == -1) {
			throw "音楽ファイルの読み込みに失敗しました";
		}
	}
	catch (const char *e) {
		Dialog::Make_Dialog_FailFile f;
		std::string errSentence(e, 37);
		f.failFileDlg(errSentence);
		return std::pair<std::unique_ptr<Make::File::Make_File_MusicData>, json::value>(nullptr, NULL);
	}

	//ファイルの読み込み
	std::ifstream readfile(saveFilePath);
	std::string s = "";
	std::string line = "";
	while (std::getline(readfile, line)) {
		s.append(line);
	}

	//読み込んだファイルの文字列からjson形式にパース
	val = json::parse(s,sp);

	//音楽データの作成
	MusicData mData = json::value_to<MusicData>(val);
	std::unique_ptr<Make_File_MusicData> p_musicdataForReturn =
		std::make_unique<Make_File_MusicData>(musicHandle,mData.name,mData.artist,mData.level,mData.bpm,mData.barLength,mData.totalMinutes,mData.beginDelay,mData.amountOfLane);

	return std::pair<std::unique_ptr<Make::File::Make_File_MusicData>, json::value>(std::move(p_musicdataForReturn),val);
}