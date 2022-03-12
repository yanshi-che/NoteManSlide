#include "Game_Play_PlayManager.h"


Game::Play::Game_Play_PlayManager::Game_Play_PlayManager(std::shared_ptr<SceneChanger>& p_sceneChanger, std::shared_ptr<Game_MusicDataShareBetweenMenuAndPlay>& p_musicDataShare): Task(p_sceneChanger) {
	this->p_musicDataShare = p_musicDataShare;
	p_lane = nullptr;
	p_score = nullptr;
	drawNoteFunc = [&] {return drawBeforeStart(); };
	startClock = 0;
	isMusicStart = false;
	isLoadFail = false;
	nowTime = 0;
	startDelay = 5.0;
	configFont = 0;
	musicHandle = 0;
	downColor = GetColor(0, 0, 0);
	fontColor = GetColor(255, 255, 255);
	edgeColor = GetColor(0, 128, 128);
	p_keyHitCheck = ::Singleton::Singleton_KeyHitCheck::getInstance();
}

void Game::Play::Game_Play_PlayManager::initialize() {
	configFont = CreateFontToHandle("Pristina", 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	const std::uint16_t laneAmount = Global::LANE_AMOUNT;

	normalNoteVec.resize(laneAmount);
	longNoteVec.resize(laneAmount);
	slideNoteVec.resize(2);
	normalNote.resize(laneAmount);
	longNote.resize(laneAmount);
	slideNote.resize(2);
	normalCount.resize(laneAmount);
	longCount.resize(laneAmount);
	slideCount.resize(2);

	std::vector<bool> isFirst;//�����O�m�[�c�̏������ł����t���O
	std::vector<double> startTime;//�����O�m�[�c�̏������Ŏn�_�̎��Ԃ�ۊ�
	isFirst.resize(laneAmount);
	startTime.resize(laneAmount);
	for (int i = 0; i < laneAmount; ++i) {
		normalCount.at(i) = 0;
		longCount.at(i) = 0;
		isFirst.at(i) = true;
		startTime.at(i) = 0;
	}
	slideCount.at(0) = 0;
	slideCount.at(1) = 0;

	//���ߐ��̏�����
	barLineVec.resize(p_musicDataShare->getMusicData()->getBarLength());
	const double timePerBeat = (Global::MINUTE / p_musicDataShare->getMusicData()->getBpm()) * Global::QUARTER;
	double timeSum = p_musicDataShare->getMusicData()->getBeginDelay() + startDelay;
	for (int i = 0, iSize = static_cast<int>(barLineVec.size()); i < iSize; ++i) {
		barLineVec.at(i) = std::make_unique<Game_Play_BarLine>(timeSum);
		timeSum += timePerBeat;
	}

	//�m�[�c�̏�����
	if (!initializeNote(laneAmount, timePerBeat)){
		DrawBox(30, 200, 710, 500, GetColor(0, 0, 0), true);
		DrawString(80, 300, "���ʃf�[�^�܂��͉��y�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B\n�f�B���N�g���\���A�܂��̓t�@�C���ɖ�肪����\��������܂��B", fontColor, edgeColor);
		DrawString(80, 420, "5�b��Ƀ��j���[�ɖ߂�܂�", fontColor, edgeColor);
		ScreenFlip();
		Sleep(5000);
		isLoadFail = true;
		p_sceneChanger->changeScene(Scene::GameMenu);
		return;
	}

	//���y�t�@�C���̓ǂݍ���
	try {
		musicHandle = LoadSoundMem(p_musicDataShare->getMusicData()->getMusicPath().c_str());
	}
	catch (...) {
		DrawBox(30, 200, 710, 500, GetColor(0, 0, 0), true);
		DrawString(80, 300, "���y�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B\n�f�B���N�g���\���A�܂��̓t�@�C���ɖ�肪����\��������܂��B", fontColor, edgeColor);
		DrawString(80, 420, "5�b��Ƀ��j���[�ɖ߂�܂�", fontColor, edgeColor);
		ScreenFlip();
		Sleep(5000);
		isLoadFail = true;
		p_sceneChanger->changeScene(Scene::GameMenu);
		return;
	}

	//���[������̕`��
	p_lane = std::make_unique<Game_Play_Lane>();
	//�X�R�A�̕`��
	p_score = std::make_unique<Game_Play_Score>(configFont);

	for (int i = 0; i < laneAmount; ++i) {
		if (normalNoteVec.at(i).size() != NULL) {
			normalNote.at(i) = normalNoteVec.at(i).at(0).get();
			normalNote.at(i)->setTurn(true);
		}
		if (longNoteVec.at(i).size() != NULL) {
			longNote.at(i) = longNoteVec.at(i).at(0).get();
			longNote.at(i)->setTurn(true);
		}
	}
	if (slideNoteVec.at(0).size() != NULL) {
		slideNote.at(0) = slideNoteVec.at(0).at(0).get();
		slideNote.at(0)->setTurn(true);
	}
	if (slideNoteVec.at(1).size() != NULL) {
		slideNote.at(1) = slideNoteVec.at(1).at(0).get();
		slideNote.at(1)->setTurn(true);
	}
}

void Game::Play::Game_Play_PlayManager::finalize() {
	DeleteFontToHandle(configFont);
	DeleteSoundMem(musicHandle);
	p_lane.reset();
	p_score.reset();
	p_musicDataShare.reset();
}

void Game::Play::Game_Play_PlayManager::update() {
	if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_UP) == 1 || 60 < p_keyHitCheck->getHitKeyLong(KEY_INPUT_UP)) {
		if (Config::g_hiSpeed < 1.5) {
			Config::g_hiSpeed += 0.01;
		}
	}
	else if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_DOWN) == 1 || 60 < p_keyHitCheck->getHitKeyLong(KEY_INPUT_DOWN)) {
		if (0.02 < Config::g_hiSpeed) {
			Config::g_hiSpeed -= 0.01;
		}
	}
	if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_RIGHT) == 1 || 60 < p_keyHitCheck->getHitKeyLong(KEY_INPUT_RIGHT)) {
		if (Config::g_judgeCorrection < 0.05) {
			Config::g_judgeCorrection += 0.01;
		}
	}
	else if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_LEFT) == 1 || 60 < p_keyHitCheck->getHitKeyLong(KEY_INPUT_LEFT)) {
		if (-0.05 < Config::g_judgeCorrection) {
			Config::g_judgeCorrection -= 0.01;
		}
	}
}

void Game::Play::Game_Play_PlayManager::draw() {
	if (!isLoadFail) {
		p_lane->draw();
		p_score->draw();
		drawNoteFunc();
		drawDown();
		drawHiSpeed();
		drawJudgeCorrection();
	}
}

void Game::Play::Game_Play_PlayManager::drawBeforeStart() {
	DrawString(280, 330, "Press Space to Start", fontColor);
	if (p_keyHitCheck->getHitKeyUsual(KEY_INPUT_SPACE)) {
		this->startClock = GetNowHiPerformanceCount();
		drawNoteFunc = [&] {return drawNote(); };
	}
}

void Game::Play::Game_Play_PlayManager::drawDown() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxAA(static_cast<float>(Global::PLAY_LANE_X_MIN + 1), static_cast<float>(Global::JUDGELINE_Y + 1.0), static_cast<float>(Global::PLAY_LANE_X_MAX - 1), static_cast<float>(Global::WINDOW_HEIGHT), downColor, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Game::Play::Game_Play_PlayManager::drawHiSpeed() {
	DrawStringToHandle(10, 200, "HiSpeed :", fontColor,configFont ,edgeColor);
	DrawFormatStringToHandle(100, 200, fontColor,configFont, "%.1f", Config::g_hiSpeed * 10.0,edgeColor);
}

void Game::Play::Game_Play_PlayManager::drawJudgeCorrection() {
	DrawStringToHandle(10, 230, "  judge :", fontColor,configFont,edgeColor);
	DrawFormatStringToHandle(100, 230, fontColor,configFont, "%.1f", Config::g_judgeCorrection * 100.0,edgeColor);
}

void Game::Play::Game_Play_PlayManager::drawNote() {
	nowTime = (double)((GetNowHiPerformanceCount() - startClock)) / 1000000.0;
	if (!isMusicStart && startDelay <= nowTime) {
		PlaySoundMem(musicHandle, DX_PLAYTYPE_BACK, true);
		isMusicStart = true;
	}
	for (int i = 0, iSize = static_cast<int>(barLineVec.size()); i < iSize; ++i) {
		barLineVec.at(i)->update(nowTime);
		barLineVec.at(i)->draw();
	}
	//���W�X�V
	for (int i = 0, iSize = Global::LANE_AMOUNT; i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(normalNoteVec.at(i).size()); k < kSize; ++k) {
			normalNoteVec.at(i).at(k)->update(nowTime);
			normalNoteVec.at(i).at(k)->draw();
		}
		for (int k = 0, kSize = static_cast<int>(longNoteVec.at(i).size()); k < kSize; ++k) {
			longNoteVec.at(i).at(k)->update(nowTime);
			longNoteVec.at(i).at(k)->draw();
		}
		if (normalNote.at(i) != nullptr) {
			normalNote.at(i)->check(nowTime);
		}
		if (longNote.at(i) != nullptr) {
			longNote.at(i)->check(nowTime);
		}
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(0).size()); i < iSize; ++i) {
		slideNoteVec.at(0).at(i)->update(nowTime);
		slideNoteVec.at(0).at(i)->draw();
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(1).size()); i < iSize; ++i) {
		slideNoteVec.at(1).at(i)->update(nowTime);
		slideNoteVec.at(1).at(i)->draw();
	}
	if (slideNote.at(0) != nullptr) {
		slideNote.at(0)->check(nowTime);
	}
	if (slideNote.at(1) != nullptr) {
		slideNote.at(1)->check(nowTime);
	}
}

void Game::Play::Game_Play_PlayManager::nextNote(const std::uint16_t noteType, const std::uint16_t laneIndex) {
	if (noteType == Global::NOTETYPE_NORMAL) {
		++normalCount.at(laneIndex);
		if (normalCount.at(laneIndex) < normalNoteVec.at(laneIndex).size()) {
			normalNote.at(laneIndex) = normalNoteVec.at(laneIndex).at(normalCount.at(laneIndex)).get();
			normalNote.at(laneIndex)->setTurn(true);
		}
		else {
			normalNote.at(laneIndex) = nullptr;
		}
	}
	else if (noteType == Global::NOTETYPE_LONG) {
		++longCount.at(laneIndex);
		if (longCount.at(laneIndex) < longNoteVec.at(laneIndex).size()) {
			longNote.at(laneIndex) = longNoteVec.at(laneIndex).at(longCount.at(laneIndex)).get();
			longNote.at(laneIndex)->setTurn(true);
		}
		else {
			longNote.at(laneIndex) = nullptr;
		}
	}
	else if (noteType == Global::NOTETYPE_SLIDER || noteType == Global::NOTETYPE_SLIDEL) {
		++slideCount.at(laneIndex);
		if (slideCount.at(laneIndex) < slideNoteVec.at(laneIndex).size()) {
			slideNote.at(laneIndex) = slideNoteVec.at(laneIndex).at(slideCount.at(laneIndex)).get();
			slideNote.at(laneIndex)->setTurn(true);
		}
		else {
			slideNote.at(laneIndex) = nullptr;
		}
	}
}

void Game::Play::Game_Play_PlayManager::updateKey() {
	for (int i = 0, iSize = Global::LANE_AMOUNT; i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(normalNoteVec.at(i).size()); k < kSize; ++k) {
			normalNoteVec.at(i).at(k)->updateKey();
		}
		for (int k = 0, kSize = static_cast<int>(longNoteVec.at(i).size()); k < kSize; ++k) {
			longNoteVec.at(i).at(k)->updateKey();
		}
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(0).size()); i < iSize; ++i) {
		slideNoteVec.at(0).at(i)->updateKey();
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(1).size()); i < iSize; ++i) {
		slideNoteVec.at(1).at(i)->updateKey();
	}

}

bool Game::Play::Game_Play_PlayManager::initializeNote(const std::uint16_t laneAmount, const double timePerBeat) {

	std::vector<bool> isFirst;//�����O�m�[�c�̏������ł����t���O
	std::vector<double> startTime;//�����O�m�[�c�̏������Ŏn�_�̎��Ԃ�ۊ�
	isFirst.resize(laneAmount);
	startTime.resize(laneAmount);
	for (int i = 0; i < laneAmount; ++i) {
		isFirst.at(i) = true;
		startTime.at(i) = 0;
	}

	//���[���̂����W
	double laneX[Global::LANE_AMOUNT + 1];
	const double laneWidth = (Global::PLAY_LANE_X_MAX - Global::PLAY_LANE_X_MIN) / laneAmount;
	for (int i = 0; i <= laneAmount; ++i) {
		laneX[i] = laneWidth * i + Global::PLAY_LANE_X_MIN;
	}

	//�X�R�A�̓ǂݍ���
	std::string line = "";
	std::string s = "";
	std::ifstream readfile(p_musicDataShare->getMusicData()->getScorePath());
	if (!readfile) {
		return false;
	}
	while (std::getline(readfile, line)) {
		s.append(line);
	}

	try {
		json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();
		json::value val = json::parse(s, sp);

		//�m�[�c�̏�����
		const json::array noteDataArray = val.as_object().at("NoteData").as_array();
		const double sixteenthTime = timePerBeat / Global::SIXTEENTH;
		const double arrowWidthBetween = laneWidth / Global::ARROW_NUM_LANE;
		std::uint16_t noteType;
		std::uint16_t laneIndex;
		std::uint16_t directionRightOrLeft;
		std::uint16_t slideNoteIndexStart;
		std::uint16_t slideNoteIndexEnd;
		std::function<void(std::uint16_t, std::uint16_t)> nextNoteFunc = [&](std::uint16_t n, std::uint16_t l) {return nextNote(n, l); };
		for (int i = 0, iSize = static_cast<int>(noteDataArray.size()); i < iSize; ++i) {
			noteType = static_cast<std::uint16_t>(noteDataArray.at(i).at("noteType").as_int64());
			laneIndex = static_cast<std::uint16_t>(noteDataArray.at(i).at("laneIndex").as_int64());
			if (noteType == Global::NOTETYPE_NORMAL) {
				normalNoteVec.at(laneIndex)
					.push_back(std::make_unique<Game_Play_NormalNote>(
						noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
						laneIndex, laneX[laneIndex], laneX[laneIndex + 1], nextNoteFunc, p_score));
			}
			else if (noteType == Global::NOTETYPE_LONG) {
				if (isFirst.at(laneIndex)) {
					startTime.at(laneIndex) = noteDataArray.at(i).at("time").as_double() + startDelay;
					isFirst.at(laneIndex) = false;
				}
				else {
					longNoteVec.at(laneIndex)
						.push_back(std::make_unique<Game_Play_LongNote>(
							startTime.at(laneIndex), noteDataArray.at(i).at("time").as_double() + startDelay, sixteenthTime, noteType,
							laneIndex, laneX[laneIndex], laneX[laneIndex + 1], nextNoteFunc, p_score));
					isFirst.at(laneIndex) = true;
				}
			}
			else if (noteType == Global::NOTETYPE_SLIDER || noteType == Global::NOTETYPE_SLIDEL) {
				if (noteDataArray.at(i).at("rightOrLeft").as_int64() == 1) {
					laneIndex = 0;
				}
				else {
					laneIndex = 1;
				}
				if (noteDataArray.at(i).at("directionRightOrLeft").as_int64() == 1) {
					directionRightOrLeft = 0;
				}
				else {
					directionRightOrLeft = 1;
				}
				slideNoteIndexStart = static_cast<std::uint16_t>(noteDataArray.at(i).at("slideLaneIndexStart").as_int64());
				slideNoteIndexEnd = static_cast<std::uint16_t>(noteDataArray.at(i).at("slideLaneIndexEnd").as_int64());
				if (laneIndex == 0) {
					if (directionRightOrLeft == 0) {//�E�̉E����
						slideNoteVec.at(laneIndex)
							.push_back(std::make_unique<Game_Play_SlideNote>(
								noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
								laneX[slideNoteIndexStart], laneX[slideNoteIndexEnd + 1], laneWidth, arrowWidthBetween, laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc, p_score));
					}
					else {//�E�̍�����
						slideNoteVec.at(laneIndex)
							.push_back(std::make_unique<Game_Play_SlideNote>(
								noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
								laneX[slideNoteIndexStart + 1], laneX[slideNoteIndexEnd], laneWidth, arrowWidthBetween, laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc, p_score));
					}
				}
				else {//���̉E����
					if (directionRightOrLeft == 0) {
						slideNoteVec.at(laneIndex)
							.push_back(std::make_unique<Game_Play_SlideNote>(
								noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
								laneX[slideNoteIndexStart], laneX[slideNoteIndexEnd + 1], laneWidth, arrowWidthBetween, laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc, p_score));
					}
					else {//���̍�����
						slideNoteVec.at(laneIndex)
							.push_back(std::make_unique<Game_Play_SlideNote>(
								noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
								laneX[slideNoteIndexStart + 1], laneX[slideNoteIndexEnd], laneWidth, arrowWidthBetween, laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc, p_score));
					}
				}
			}
		}
	}
	catch (...) {
		return false;
	}

	return true;
}