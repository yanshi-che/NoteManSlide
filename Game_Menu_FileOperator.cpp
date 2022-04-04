#include "Game_Menu_FileOperator.h"

Game::Menu::SaveDataInit::SaveDataInit() {
	isPerfect = false;
	isFullChain = false;
	isClear = false;
	bestScore = NULL;
}

void Game::Menu::tag_invoke(const json::value_from_tag&, json::value& jv, const SaveDataInit& s) {
	jv = {
		{"isPerfect",s.isPerfect},
		{"isFullChain",s.isFullChain},
		{"isClear",s.isClear},
		{ "bestScore", s.bestScore },
	};
}

void Game::Menu::Game_Menu_FileOperator::getScoreData(std::vector<std::vector<std::shared_ptr<Game_Menu_MusicData>>>& musicData) {
	//ファイルの読み込み用
	std::string s = "";
	std::string line = "";
	//json作成用の変数
	json::object obj;
	json::value val;
	json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();
	for (int i = 0, iSize = static_cast<int>(musicData.size()); i < iSize; ++i) {
		try {
			std::ifstream readfile(musicData.at(i).at(0)->getSavePath());
			if (!readfile) {
				continue;
			}
			while (std::getline(readfile, line)) {
				s.append(line);
			}

			val = json::parse(s, sp);
			obj = val.at("easy").as_object();
			musicData.at(i).at(0)->setIsPerfect(obj.at("isPerfect").as_bool());
			musicData.at(i).at(0)->setIsFullChain(obj.at("isFullChain").as_bool());
			musicData.at(i).at(0)->setIsClear(obj.at("isClear").as_bool());
			musicData.at(i).at(0)->setBestScore(static_cast<std::uint16_t>(obj.at("bestScore").as_int64()));

			obj = val.at("normal").as_object();
			musicData.at(i).at(1)->setIsPerfect(obj.at("isPerfect").as_bool());
			musicData.at(i).at(1)->setIsFullChain(obj.at("isFullChain").as_bool());
			musicData.at(i).at(1)->setIsClear(obj.at("isClear").as_bool());
			musicData.at(i).at(1)->setBestScore(static_cast<std::uint16_t>(obj.at("bestScore").as_int64()));

			obj = val.at("hard").as_object();
			musicData.at(i).at(2)->setIsPerfect(obj.at("isPerfect").as_bool());
			musicData.at(i).at(2)->setIsFullChain(obj.at("isFullChain").as_bool());
			musicData.at(i).at(2)->setIsClear(obj.at("isClear").as_bool());
			musicData.at(i).at(2)->setBestScore(static_cast<std::uint16_t>(obj.at("bestScore").as_int64()));
		}
		catch (...) {
			continue;
		}
	}
}

bool Game::Menu::Game_Menu_FileOperator::getMusicData(std::vector<std::vector<std::shared_ptr<Game_Menu_MusicData>>>& musicData) {
	try {
		//登録されている譜面が入ったディレクトリの読み込み
		std::string firstPath = ".\\musicData";
		std::vector<std::string> musicDataPathVec;
		for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(firstPath)) {
			if (entry.is_directory()) {
				musicDataPathVec.push_back(entry.path().string());
			}
		}

		//ファイルの読み込み用
		std::string s = "";
		std::string line = "";
		//難易度別スコアと曲読み込み用とセーブデータのディレクトリパス
		const std::uint16_t difficultySize = 3;
		std::string scoreDirPath[difficultySize] = { "","","" };
		std::string difficultyPath[difficultySize] = { "\\score\\easy","\\score\\normal","\\score\\hard" };
		std::string musicDirPath = "";
		std::string saveDataDirPath = "";
		//曲とスコアとセーブデータのパス
		std::string scorePath = "";
		std::string musicPath = "";
		std::string saveDataPath = "";
		//json作成用の変数
		json::object obj;
		json::value val;
		json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();
		musicData.resize(musicDataPathVec.size());
		for (int i = 0, iSize = static_cast<int>(musicDataPathVec.size()); i < iSize; ++i) {
			//難易度ごとに読み込み
			for (int k = 0; k < difficultySize; ++k) {
				scoreDirPath[k] = musicDataPathVec.at(i);
				scoreDirPath[k].append(difficultyPath[k]);
				musicDirPath = musicDataPathVec.at(i);
				musicDirPath.append("\\music");
				saveDataDirPath = musicDataPathVec.at(i);
				saveDataDirPath.append("\\saveData");
				//スコアファイル
				for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(scoreDirPath[k])) {
					scorePath = entry.path().string();
					break;
				}
				if (scorePath.empty()) {
					continue;
				}
				//音楽ファイル
				for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(musicDirPath)) {
					musicPath = entry.path().string();
					break;
				}
				if (musicPath.empty()) {
					continue;
				}
				//セーブデータ
				for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(saveDataDirPath)) {
					saveDataPath = entry.path().string();
					break;
				}
				if (saveDataPath.empty()) {
					saveDataPath = saveDataDirPath;
					saveDataPath.append("\\saveData.json");
				}
				std::ifstream readfile(scorePath);
				if (!readfile) {
					continue;
				}
				while (std::getline(readfile, line)) {
					s.append(line);
				}
				val = json::parse(s, sp);
				obj = val.at("MusicData").as_object();
				musicData.at(i).push_back(std::make_shared<Game_Menu_MusicData>(Game_Menu_MusicData(musicPath, scorePath,saveDataPath, std::string(obj.at("name").as_string().c_str()),
					std::string(obj.at("artist").as_string().c_str()), static_cast<std::uint16_t>(obj.at("level").as_int64()), obj.at("bpm").as_double(),
					static_cast<std::uint16_t>(obj.at("barLength").as_int64()), obj.at("totalMinute").as_double(), obj.at("beginDelay").as_double())));
				line = "";
				s = "";
				scorePath = "";
				musicPath = "";
				saveDataPath = "";
			}
		}
		//セーブデータ読み込み
		getScoreData(musicData);
	}
	catch (...) {
		return false;
	}


	return true;
}

void Game::Menu::Game_Menu_FileOperator::saveResultData(const bool isPerfect, const  bool isFullChain, const bool isClear, const std::uint16_t score, const std::shared_ptr<Game_MusicDataShareBetweenOtherSection>& p_musicDataShare){
	//ファイルの読み込み用
	std::string s = "";
	std::string line = "";
	//json作成用の変数
	json::object obj;
	json::value val;
	json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();
	std::ifstream readfile(p_musicDataShare->getMusicData()->getSavePath());
	if (!readfile) {
		obj["easy"] = json::value_from(SaveDataInit());
		obj["normal"] = json::value_from(SaveDataInit());
		obj["hard"] = json::value_from(SaveDataInit());

		val = json::value(obj);

		std::ofstream writeFile;
		writeFile.open(p_musicDataShare->getMusicData()->getSavePath(), std::ios::out);
		writeFile << val << std::endl;
		writeFile.close();

		readfile = std::ifstream(p_musicDataShare->getMusicData()->getSavePath());
	}

	while (std::getline(readfile, line)) {
		s.append(line);
	}

	std::string difficulty = "";
	if (p_musicDataShare->getDifficulty() == 0) {
		difficulty = "easy";
	}
	else if (p_musicDataShare->getDifficulty() == 1) {
		difficulty = "normal";
	}
	else if (p_musicDataShare->getDifficulty() == 2) {
		difficulty = "hard";
	}

	val = json::parse(s, sp);

	obj = val.as_object();

	obj.at(difficulty).as_object().at("isPerfect") = isPerfect;
	obj.at(difficulty).as_object().at("isFullChain") = isFullChain;
	obj.at(difficulty).as_object().at("isClear") = isClear;
	if (p_musicDataShare->getMusicData()->getBestScore() < score) {
		obj.at(difficulty).as_object().at("bestScore") = score;
	}

	val = json::value(obj);

	std::ofstream writeFile;
	writeFile.open(p_musicDataShare->getMusicData()->getSavePath(), std::ios::out);
	writeFile << val << std::endl;
	writeFile.close();
}