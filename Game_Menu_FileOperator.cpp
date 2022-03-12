#include "Game_Menu_FileOperator.h"

bool Game::Menu::Game_Menu_FileOperator::getMusicData(std::vector<std::vector<std::unique_ptr<Game_Menu_MusicData>>>& musicData) {
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
		//難易度別スコアと曲読み込み用パス
		const std::uint16_t difficultySize = 3;
		std::string scoreDirPath[difficultySize] = { "","","" };
		std::string difficultyPath[difficultySize] = { "\\score\\easy","\\score\\normal","\\score\\hard" };
		std::string musicDirPath = "";
		//曲とスコアのパス
		std::string scorePath = "";
		std::string musicPath = "";
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
				for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(scoreDirPath[k])) {
					scorePath = entry.path().string();
					break;
				}
				if (scorePath.at(0) == NULL) {
					continue;
				}
				for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(musicDirPath)) {
					musicPath = entry.path().string();
					break;
				}
				if (musicPath.at(0) == NULL) {
					continue;
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
				musicData.at(i).push_back(std::make_unique<Game_Menu_MusicData>(Game_Menu_MusicData(musicPath, scorePath, std::string(obj.at("name").as_string().c_str()),
					std::string(obj.at("artist").as_string().c_str()), static_cast<std::uint16_t>(obj.at("level").as_int64()), obj.at("bpm").as_double(),
					static_cast<std::uint16_t>(obj.at("barLength").as_int64()), obj.at("totalMinute").as_double(), obj.at("beginDelay").as_double())));
				line = "";
				s = "";
				scorePath = "";
				musicPath = "";
			}
		}
	}
	catch (...) {
		return false;
	}
	return true;
}