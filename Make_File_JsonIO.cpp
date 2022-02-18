#include "Make_File_JsonIO.h"

void Make::File::Make_File_JsonIO::getFilePath(char (&filePath)[MAX_PATH]) {
	const char* title[] = { "ファイルの保存" };
	const char* filter[] = { "json\0*.json\0\0" };
	File::Make_File_BaseFile gfb;
	gfb.openExplorer(title, filter, filePath, true);
}

void Make::File::Make_File_JsonIO::saveNewJson(const std::shared_ptr<Make_File_MusicData>& p_musicData) {
	//セーブするファイルのパスを取得
	char filePath[MAX_PATH] = "";//セーブするファイルのパス
	getFilePath(filePath);
	if (filePath == "") {
		Dialog::Make_Dialog_FailFile f;
		std::string errSentence = "ファイル読み込みに失敗しました";
		f.failFileDlg(errSentence);
		return;
	}

	//json作成用の変数
	json::object obj;
	json::value val;
	json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();

	//MusicDataObjectの作成
	obj["MusicData"] = json::value_from(MusicData(p_musicData->getName(), p_musicData->getArtist(), p_musicData->getLevel(),p_musicData->getBpm(),p_musicData->getBarLength(),p_musicData->getTotalMinutes(),p_musicData->getBeginDelay(),p_musicData->getAmountOfLane()),sp);

	//NoteDataObjectの作成
	const std::vector<std::vector<std::shared_ptr<Note::Make_Note_NormalNoteContainer>>>& normalNote = Singleton::Make_Singleton_NoteManager::getInstance()->getNormalNoteVector();
	const std::vector<std::vector<std::shared_ptr<Note::Make_Note_LongNoteContainer>>>& longNote = Singleton::Make_Singleton_NoteManager::getInstance()->getLongNoteVector();
	const std::vector<std::vector<std::shared_ptr<Note::Make_Note_SlideNoteContainer>>>& slideNote = Singleton::Make_Singleton_NoteManager::getInstance()->getSlideNoteVector();

	std::vector<NoteDataForJson> noteDataVector;
	std::vector<std::uint16_t> noteIndex;
	noteIndex.resize(p_musicData->getAmountOfLane());
	for (int i = 0, iSize = static_cast<int>(p_musicData->getAmountOfLane()); i < iSize; ++i) {
		noteIndex.at(i) = 0;
	}
	struct longNotePoint {//終点が読み込まれるまでlongNoteの始点情報を保管するためのもの
		std::uint16_t oldIndex;
		std::uint16_t newIndex;
		longNotePoint(std::uint16_t oldIndex, std::uint16_t newIndex) { this->oldIndex = oldIndex;  this->newIndex = newIndex; }
	};
	std::deque<longNotePoint> longNotePointDeq;//終点が読み込まれるまでlongNoteの始点情報を保管
	std::uint16_t longNoteGroupIndex = 1;
	bool isLongGroupLast = false;
	for (int i = 0, iSize = static_cast<int>(normalNote.size()); i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(normalNote.at(i).size()); k < kSize; ++k) {
			for (int l = 0, lSize = static_cast<int>(p_musicData->getAmountOfLane()); l < lSize; ++l) {
				if (normalNote.at(i).at(k)->getNormalNoteFlag(l)) {
					noteDataVector.push_back(NoteDataForJson(normalNote.at(i).at(k)->getTime(),Global::NOTETYPENORMAL,l,NULL,noteIndex.at(l),NULL,NULL,NULL));
					++noteIndex.at(l);
				}
				else if(longNote.at(i).at(k)->getLongNoteFlag(l).second){
					for (int n = 0, nSize = static_cast<int>(longNotePointDeq.size()); n < nSize; ++n) {
						if (longNote.at(i).at(k)->getNoteGroup(l) == longNotePointDeq.at(n).oldIndex) {
							noteDataVector.push_back(NoteDataForJson(longNote.at(i).at(k)->getTime(), Global::NOTETYPELONG, l, longNotePointDeq.at(n).newIndex,noteIndex.at(l), NULL, NULL, NULL));
							isLongGroupLast = true;
							longNotePointDeq.erase(longNotePointDeq.begin() + n);
							break;
						}
					}
					if (!isLongGroupLast) {
						noteDataVector.push_back(NoteDataForJson(longNote.at(i).at(k)->getTime(), Global::NOTETYPELONG, l, longNoteGroupIndex, noteIndex.at(l),NULL, NULL, NULL));
						longNotePointDeq.push_back(longNotePoint(longNote.at(i).at(k)->getNoteGroup(l), longNoteGroupIndex));
						++longNoteGroupIndex;
					}
					isLongGroupLast = false;
				}
			}
			if (slideNote.at(i).at(k)->getSlideNoteFlag().first) {
				noteDataVector.push_back(NoteDataForJson(slideNote.at(i).at(k)->getTime(), Global::NOTETYPESLIDE, NULL, NULL, NULL, 1,
					slideNote.at(i).at(k)->getNoteStartAndEnd().first.first, slideNote.at(i).at(k)->getNoteStartAndEnd().first.second));
			}
			if (slideNote.at(i).at(k)->getSlideNoteFlag().second) {
				noteDataVector.push_back(NoteDataForJson(slideNote.at(i).at(k)->getTime(), Global::NOTETYPESLIDE, NULL, NULL, NULL, 2,
					slideNote.at(i).at(k)->getNoteStartAndEnd().second.first, slideNote.at(i).at(k)->getNoteStartAndEnd().second.second));
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