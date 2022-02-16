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
					noteDataVector.push_back(NoteDataForSave(normalNote.at(i).at(k)->getBarID(), normalNote.at(i).at(k)->getBeatID(), Global::NOTETYPELONG, l, longNoteGroupIndex, NULL, NULL, NULL));
					if (!isLongGroupLast) {
						isLongGroupLast = true;
					}
					else {
						isLongGroupLast = false;
						++longNoteGroupIndex;
					}
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