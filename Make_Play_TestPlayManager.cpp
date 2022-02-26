#include "Make_Play_TestPlayManager.h"


Make::Play::Make_Play_TestPlayManager::Make_Play_TestPlayManager() {
	p_musicPlayer = nullptr;
	p_lane = nullptr;
	p_score = nullptr;
	startClock = 0;
	isStart = false;
	isMusicStart = false;
	nowTime = 0;
	startDelay = 5.0;
	downColor = GetColor(0, 0, 0);
	strColor = GetColor(255, 255, 255);
	p_keyHitCheck = Singleton::Make_Singleton_KeyHitCheck::getInstance();
}

void Make::Play::Make_Play_TestPlayManager::draw() {
	p_lane->draw();
	p_score->draw();
	if (!isStart) {
		DrawString(280, 330, "Press Space to Start", strColor);
		if (p_keyHitCheck->getHitKeyUsual(KEY_INPUT_SPACE)) {
			this->startClock = GetNowHiPerformanceCount();
			isStart = true;
		}
	}
	else {
		nowTime = (double)((GetNowHiPerformanceCount() - startClock)) / 1000000.0;
		if (!isMusicStart && startDelay <= nowTime) {
			p_musicPlayer->startMusicFromHead();
			isMusicStart = true;
		}
		for (int i = 0, iSize = static_cast<int>(barLineVec.size()); i < iSize; ++i) {
			barLineVec.at(i)->update(nowTime);
			barLineVec.at(i)->draw();
		}
		//座標更新
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

	drawDown();
	if (p_keyHitCheck->getHitKeyForNote(KEY_INPUT_UP) == 1 || 60 < p_keyHitCheck->getHitKeyForNote(KEY_INPUT_UP)) {
		if (Global::g_hiSpeed < 1.5) {
			Global::g_hiSpeed += 0.01;
		}
	}
	else if (p_keyHitCheck->getHitKeyForNote(KEY_INPUT_DOWN) == 1 || 60 < p_keyHitCheck->getHitKeyForNote(KEY_INPUT_DOWN)) {
		if ( 0.02 < Global::g_hiSpeed) {
			Global::g_hiSpeed -= 0.01;
		}
	}
	drawHiSpeed();
}

void Make::Play::Make_Play_TestPlayManager::drawDown() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxAA(static_cast<float>(Global::PLAY_LANE_X_MIN + 1), static_cast<float>(Global::JUDGELINE_Y + 1.0), static_cast<float>(Global::PLAY_LANE_X_MAX - 1), static_cast<float>(Global::WINDOW_HEIGHT), downColor, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Make::Play::Make_Play_TestPlayManager::drawHiSpeed() {
	DrawStringF(10, 200,"HiSpeed :", strColor);
	DrawFormatStringF(100,200,strColor,"%.1f",Global::g_hiSpeed * 10);
}

void Make::Play::Make_Play_TestPlayManager::finalize() {
	p_musicPlayer.reset();
	p_lane.reset();
	p_score.reset();
}

void Make::Play::Make_Play_TestPlayManager::initialize(const json::value& val, const std::shared_ptr<Make_Play_MusicPlayer>& p_musicPlayer, const std::shared_ptr<File::Make_File_MusicData>& p_musicData) {
	this->p_musicPlayer = p_musicPlayer;
	const std::uint8_t laneAmount = Global::LANE_AMOUNT;

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

	//ノーツの初期化
	const json::array noteDataArray = val.as_object().at("NoteData").as_array();
	const double sixteenthTime = timePerBeat / Global::SIXTEENTH;
	const double arrowWidthBetween = laneWidth / Global::ARROW_NUM_LANE;
	std::uint8_t noteType;
	std::uint8_t laneIndex;
	std::uint8_t directionRightOrLeft;
	std::uint8_t slideNoteIndexStart;
	std::uint8_t slideNoteIndexEnd;
	std::function<void(std::uint8_t, std::uint8_t)> nextNoteFunc = [&](std::uint8_t n, std::uint8_t l) {return nextNote(n,l); };
	for (int i = 0, iSize = static_cast<int>(noteDataArray.size()); i< iSize; ++i) {
		noteType = static_cast<std::uint8_t>(noteDataArray.at(i).at("noteType").as_uint64());
		laneIndex = static_cast<std::uint8_t>(noteDataArray.at(i).at("laneIndex").as_uint64());
		if (noteType == Global::NOTETYPE_NORMAL) {
			normalNoteVec.at(laneIndex)
				.push_back(std::make_unique<Make_Play_NormalNote>(
					noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
					laneIndex, laneX[laneIndex], laneX[laneIndex + 1], nextNoteFunc,p_score));
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
						laneIndex, laneX[laneIndex], laneX[laneIndex + 1], nextNoteFunc,p_score));
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
			slideNoteIndexStart = static_cast<std::uint8_t>(noteDataArray.at(i).at("slideLaneIndexStart").as_uint64());
			slideNoteIndexEnd = static_cast<std::uint8_t>(noteDataArray.at(i).at("slideLaneIndexEnd").as_uint64());
			if (laneIndex == 0) {
				if (directionRightOrLeft == 0) {//右の右向き
					slideNoteVec.at(laneIndex)
						.push_back(std::make_unique<Make_Play_SlideNote>(
							noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
							laneX[slideNoteIndexStart], laneX[slideNoteIndexEnd + 1],laneWidth, arrowWidthBetween, laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc,p_score));
				}
				else {//右の左向き
					slideNoteVec.at(laneIndex)
						.push_back(std::make_unique<Make_Play_SlideNote>(
							noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
							laneX[slideNoteIndexStart + 1], laneX[slideNoteIndexEnd],laneWidth, arrowWidthBetween, laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc,p_score));
				}
			}
			else {//左の右向き
				if (directionRightOrLeft == 0) {
					slideNoteVec.at(laneIndex)
						.push_back(std::make_unique<Make_Play_SlideNote>(
							noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
							laneX[slideNoteIndexStart], laneX[slideNoteIndexEnd + 1], laneWidth, arrowWidthBetween ,laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc,p_score));
				}
				else {//左の左向き
					slideNoteVec.at(laneIndex)
						.push_back(std::make_unique<Make_Play_SlideNote>(
							noteDataArray.at(i).at("time").as_double() + startDelay, noteType,
							laneX[slideNoteIndexStart + 1], laneX[slideNoteIndexEnd], laneWidth, arrowWidthBetween, laneIndex, directionRightOrLeft, slideNoteIndexStart, slideNoteIndexEnd, nextNoteFunc,p_score));
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

void Make::Play::Make_Play_TestPlayManager::nextNote(const std::uint8_t noteType, const std::uint8_t laneIndex) {
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

const std::function<void()> Make::Play::Make_Play_TestPlayManager::getDrawFunc() {
	return [&] {return draw(); };
}