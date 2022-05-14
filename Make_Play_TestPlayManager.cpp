#include "Make_Play_TestPlayManager.h"


Make::Play::Make_Play_TestPlayManager::Make_Play_TestPlayManager() {
	p_musicPlayer = nullptr;
	p_lane = nullptr;
	p_score = nullptr;
	p_effect = nullptr;
	p_soundEffect = nullptr;
	drawNoteFunc = [&] {return drawBeforeStart(); };
	startClock = 0;
	isGameStart = false;
	isMusicStart = false;
	isAuto = false;
	nowTime = 0;
	startDelay = 5.0;
	downColor = GetColor(0, 0, 0);
	strColor = GetColor(255, 255, 255);
	p_keyHitCheck = ::Singleton::Singleton_KeyHitCheck::getInstance();
}

void Make::Play::Make_Play_TestPlayManager::draw() {
	p_lane->draw();
	p_score->draw();
	drawNoteFunc();
	drawDown();
	p_effect->draw();
	drawHiSpeed();
	drawJudgeCorrection();
	drawAuto();
}

void Make::Play::Make_Play_TestPlayManager::drawAuto() {
	DrawStringF(10, 100, "Auto Mode :", strColor);
	if (isAuto) {
		DrawStringF(110, 100, "on", strColor);
	}
	else {
		DrawStringF(110, 100, "off", strColor);
	}
}

void Make::Play::Make_Play_TestPlayManager::drawBeforeStart() {
	DrawString(280, 330, "Press Space to Start", strColor);
}

void Make::Play::Make_Play_TestPlayManager::drawDown() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxAA(static_cast<float>(Global::PLAY_LANE_X_MIN + 1), static_cast<float>(Global::JUDGELINE_Y + 1.0), static_cast<float>(Global::PLAY_LANE_X_MAX - 1), static_cast<float>(Global::WINDOW_HEIGHT), downColor, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Make::Play::Make_Play_TestPlayManager::drawHiSpeed() {
	DrawStringF(10, 200,"HiSpeed :", strColor);
	DrawFormatStringF(100,200,strColor,"%.1f",Config::g_hiSpeed * 10.0);
}

void Make::Play::Make_Play_TestPlayManager::drawJudgeCorrection() {
	DrawStringF(10, 230, "判定調整 :", strColor);
	DrawFormatStringF(100, 230, strColor, "%.1f", Config::g_judgeCorrection * 1000.0);
}

void Make::Play::Make_Play_TestPlayManager::drawNote() {
	for (int i = 0, iSize = static_cast<int>(barLineVec.size()); i < iSize; ++i) {
		barLineVec.at(i)->draw(nowTime);
	}
	//座標更新
	for (int i = 0, iSize = Global::LANE_AMOUNT; i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(normalNoteVec.at(i).size()); k < kSize; ++k) {
			normalNoteVec.at(i).at(k)->draw(nowTime);
		}
		for (int k = 0, kSize = static_cast<int>(longNoteVec.at(i).size()); k < kSize; ++k) {
			longNoteVec.at(i).at(k)->draw(nowTime);
		}
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(0).size()); i < iSize; ++i) {
		slideNoteVec.at(0).at(i)->draw(nowTime);
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(1).size()); i < iSize; ++i) {
		slideNoteVec.at(1).at(i)->draw(nowTime);
	}
}

void Make::Play::Make_Play_TestPlayManager::finalize() {
	p_musicPlayer->stopMusic();
	p_musicPlayer.reset();
	p_lane.reset();
	p_score.reset();
	p_effect->finalize();
	p_effect.reset();
	p_soundEffect.reset();
}

void Make::Play::Make_Play_TestPlayManager::initialize(const json::value& val, const std::shared_ptr<Make_Play_MusicPlayer>& p_musicPlayer, const std::shared_ptr<File::Make_File_MusicData>& p_musicData) {
	this->p_musicPlayer = p_musicPlayer;
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

	std::vector<bool> isFirst;//ロングノーツの初期化でつかうフラグ
	std::vector<double> startTime;//ロングノーツの初期化で始点の時間を保管
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

	//小節線の初期化
	barLineVec.resize(p_musicData->getBarLength());
	const double timePerBeat = (Global::MINUTE / p_musicData->getBpm()) * Global::QUARTER;
	double timeSum = p_musicData->getBeginDelay() + startDelay;
	for (int i = 0, iSize = static_cast<int>(barLineVec.size()); i < iSize; ++i) {
		barLineVec.at(i) = std::make_unique<Make_Play_BarLine>(timeSum);
		timeSum += timePerBeat;
	}

	//レーンのｘ座標
	double laneX[laneAmount + 1];
	const double laneWidth = (Global::PLAY_LANE_X_MAX - Global::PLAY_LANE_X_MIN) / laneAmount;
	for (int i = 0; i <= laneAmount; ++i) {
		laneX[i] = laneWidth * i + Global::PLAY_LANE_X_MIN;
	}

	//レーン周りの描画
	p_lane = std::make_unique<Make_Play_Lane>();
	//スコアの描画
	p_score = std::make_unique<Make_Play_Score>();
	//エフェクト
	p_effect = std::make_shared<Game::Play::Game_Play_Effect>();
	p_effect->loadEffect();
	//サウンドエフェクト
	p_soundEffect = std::make_shared<Game::Play::Game_Play_SoundEffect>();

	//ノーツの初期化
	const json::array noteDataArray = val.as_object().at("NoteData").as_array();
	const double sixteenthTime = timePerBeat / Global::SIXTEENTH;
	const double arrowWidthBetween = laneWidth / Global::ARROW_NUM_LANE;
	std::uint16_t noteType;
	std::uint16_t laneIndex;
	std::uint16_t directionRightOrLeft;
	std::uint16_t slideNoteIndexStart;
	std::uint16_t slideNoteIndexEnd;
	std::function<void(std::uint16_t, std::uint16_t)> nextNoteFunc = [&](std::uint16_t n, std::uint16_t l) {return nextNote(n,l); };
	for (int i = 0, iSize = static_cast<int>(noteDataArray.size()); i< iSize; ++i) {
		noteType = static_cast<std::uint16_t>(noteDataArray.at(i).at("noteType").as_uint64());
		laneIndex = static_cast<std::uint16_t>(noteDataArray.at(i).at("laneIndex").as_uint64());
		if (noteType == Global::NOTETYPE_NORMAL) {
			normalNoteVec.at(laneIndex)
				.push_back(std::make_unique<Make_Play_NormalNote>(
					noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
					laneIndex, laneX[laneIndex], laneX[laneIndex + 1], nextNoteFunc,p_score, p_effect, p_soundEffect));
		}
		else if (noteType == Global::NOTETYPE_LONG) {
			if (isFirst.at(laneIndex)) {
				startTime.at(laneIndex) = noteDataArray.at(i).at("time").as_double()+ startDelay;
				isFirst.at(laneIndex) = false;
			}
			else {
				longNoteVec.at(laneIndex)
					.push_back(std::make_unique<Make_Play_LongNote>(
						startTime.at(laneIndex),noteDataArray.at(i).at("time").as_double() + startDelay,sixteenthTime ,noteType,
						laneIndex, laneX[laneIndex], laneX[laneIndex + 1], nextNoteFunc,p_score, p_effect, p_soundEffect));
				isFirst.at(laneIndex) = true;
			}
		}
		else if (noteType == Global::NOTETYPE_SLIDER || noteType == Global::NOTETYPE_SLIDEL) {
			if (noteDataArray.at(i).at("rightOrLeft").as_uint64() == 1) {
				laneIndex = 0;
			}
			else {
				laneIndex = 1;
			}
			if (noteDataArray.at(i).at("directionRightOrLeft").as_uint64() == 1) {
				directionRightOrLeft = 0;
			}
			else {
				directionRightOrLeft = 1;
			}
			slideNoteIndexStart = static_cast<std::uint16_t>(noteDataArray.at(i).at("slideLaneIndexStart").as_uint64());
			slideNoteIndexEnd = static_cast<std::uint16_t>(noteDataArray.at(i).at("slideLaneIndexEnd").as_uint64());
			if (laneIndex == 0) {
				if (directionRightOrLeft == 0) {//右の右向き
					slideNoteVec.at(laneIndex)
						.push_back(std::make_unique<Make_Play_SlideNote>(
							noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
							laneX[slideNoteIndexStart], laneX[slideNoteIndexEnd + 1],laneWidth, arrowWidthBetween, laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc,p_score, p_effect, p_soundEffect));
				}
				else {//右の左向き
					slideNoteVec.at(laneIndex)
						.push_back(std::make_unique<Make_Play_SlideNote>(
							noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
							laneX[slideNoteIndexStart + 1], laneX[slideNoteIndexEnd],laneWidth, arrowWidthBetween, laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc,p_score, p_effect, p_soundEffect));
				}
			}
			else {//左の右向き
				if (directionRightOrLeft == 0) {
					slideNoteVec.at(laneIndex)
						.push_back(std::make_unique<Make_Play_SlideNote>(
							noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
							laneX[slideNoteIndexStart], laneX[slideNoteIndexEnd + 1], laneWidth, arrowWidthBetween ,laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc,p_score, p_effect, p_soundEffect));
				}
				else {//左の左向き
					slideNoteVec.at(laneIndex)
						.push_back(std::make_unique<Make_Play_SlideNote>(
							noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
							laneX[slideNoteIndexStart + 1], laneX[slideNoteIndexEnd], laneWidth, arrowWidthBetween, laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc,p_score, p_effect, p_soundEffect));
				}
			}
		}
	}

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

void Make::Play::Make_Play_TestPlayManager::nextNote(const std::uint16_t noteType, const std::uint16_t laneIndex) {
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

void Make::Play::Make_Play_TestPlayManager::setYUpdateBorder() {
	//小節線
	for (int i = 0, iSize = static_cast<int>(barLineVec.size()); i < iSize; ++i) {
		barLineVec.at(i)->setYUpdateBorder();
	}
	//ノーツ
	for (int i = 0, iSize = Global::LANE_AMOUNT; i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(normalNoteVec.at(i).size()); k < kSize; ++k) {
			normalNoteVec.at(i).at(k)->setYUpdateBorder();
		}
		for (int k = 0, kSize = static_cast<int>(longNoteVec.at(i).size()); k < kSize; ++k) {
			longNoteVec.at(i).at(k)->setYUpdateBorder();
		}
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(0).size()); i < iSize; ++i) {
		slideNoteVec.at(0).at(i)->setYUpdateBorder();
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(1).size()); i < iSize; ++i) {
		slideNoteVec.at(1).at(i)->setYUpdateBorder();
	}
}

void Make::Play::Make_Play_TestPlayManager::playUpdate() {
	nowTime = (double)(Global::g_time - startClock) / 1000000.0;
	if (!isMusicStart && isGameStart && startDelay <= nowTime) {
		p_musicPlayer->startMusicFromHead();
		isMusicStart = true;
	}
	for (int i = 0, iSize = static_cast<int>(barLineVec.size()); i < iSize; ++i) {
		barLineVec.at(i)->update(nowTime);
	}
	//座標更新
	for (int i = 0, iSize = Global::LANE_AMOUNT; i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(normalNoteVec.at(i).size()); k < kSize; ++k) {
			normalNoteVec.at(i).at(k)->update(nowTime);
		}
		for (int k = 0, kSize = static_cast<int>(longNoteVec.at(i).size()); k < kSize; ++k) {
			longNoteVec.at(i).at(k)->update(nowTime);
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
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(1).size()); i < iSize; ++i) {
		slideNoteVec.at(1).at(i)->update(nowTime);
	}
	if (slideNote.at(0) != nullptr) {
		slideNote.at(0)->check(nowTime);
	}
	if (slideNote.at(1) != nullptr) {
		slideNote.at(1)->check(nowTime);
	}
}

void Make::Play::Make_Play_TestPlayManager::update() {
	if (!isMusicStart && p_keyHitCheck->getHitKeyUsual(KEY_INPUT_SPACE)) {
		this->startClock = Global::g_time;
		drawNoteFunc = [&] {return drawNote(); };
		isGameStart = true;
	}
	if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_UP) == 1) {
		if (Config::g_hiSpeed < 1.5) {
			Config::g_hiSpeed += 0.01;
			setYUpdateBorder();
		}
	}
	else if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_DOWN) == 1) {
		if (0.02 < Config::g_hiSpeed) {
			Config::g_hiSpeed -= 0.01;
			setYUpdateBorder();
		}
	}
	if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_RIGHT) == 1) {
		if (Config::g_judgeCorrection < 0.05) {
			Config::g_judgeCorrection += 0.001;
		}
	}
	else if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_LEFT) == 1) {
		if (-0.05 < Config::g_judgeCorrection) {
			Config::g_judgeCorrection -= 0.001;
		}
	}
	if (p_keyHitCheck->getHitKeyLong(KEY_INPUT_A) == 1) {
		toggleAuto();
	}
	p_effect->update();
	playUpdate();
}

void Make::Play::Make_Play_TestPlayManager::updateKey() {
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

void Make::Play::Make_Play_TestPlayManager::toggleAuto() {
	if (isAuto) {
		isAuto = false;
	}
	else {
		isAuto = true;
	}
	for (int i = 0, iSize = Global::LANE_AMOUNT; i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(normalNoteVec.at(i).size()); k < kSize; ++k) {
			normalNoteVec.at(i).at(k)->setAuto();
		}
		for (int k = 0, kSize = static_cast<int>(longNoteVec.at(i).size()); k < kSize; ++k) {
			longNoteVec.at(i).at(k)->setAuto();
		}
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(0).size()); i < iSize; ++i) {
		slideNoteVec.at(0).at(i)->setAuto();
	}
	for (int i = 0, iSize = static_cast<int>(slideNoteVec.at(1).size()); i < iSize; ++i) {
		slideNoteVec.at(1).at(i)->setAuto();
	}
}

const std::function<void()> Make::Play::Make_Play_TestPlayManager::getDrawFunc() {
	return [&] {return draw(); };

}

const std::function<void()> Make::Play::Make_Play_TestPlayManager::getUpdateFunc() {
	return [&] {return update(); };
}