#include "Make_Play_TestPlayManager.h"


Make::Play::Make_Play_TestPlayManager::Make_Play_TestPlayManager() {
	p_musicPlayer = nullptr;
	p_lane = nullptr;
}

void Make::Play::Make_Play_TestPlayManager::draw() {
	p_lane->draw();
}

void Make::Play::Make_Play_TestPlayManager::finalize() {
	p_musicPlayer.reset();
	p_lane.reset();
}

void Make::Play::Make_Play_TestPlayManager::initialize(const json::value& val, const std::shared_ptr<Make_Play_MusicPlayer>& p_musicPlayer, const std::shared_ptr<File::Make_File_MusicData>& p_musicData) {
	this->p_musicPlayer = p_musicPlayer;
	const std::uint8_t laneAmount = Global::LANE_AMOUNT;

	normalNoteVec.resize(laneAmount);
	longNoteVec.resize(laneAmount);
	slideNoteVec.resize(laneAmount);
	normalNote.resize(laneAmount);
	longNote.resize(laneAmount);
	slideNote.resize(laneAmount);
	normalCount.resize(laneAmount);
	longCount.resize(laneAmount);
	slideCount.resize(2);

	std::vector<bool> isFirst;//ロングノーツの初期化でつかうフラグ
	std::vector<double> startTime;//ロングノーツの初期化で始点の時間を保管
	isFirst.reserve(laneAmount);
	for (int i = 0; i < laneAmount; ++i) {
		normalCount.at(i) = 0;
		longCount.at(i) = 0;
		slideCount.at(i) = 0;
		isFirst.at(i) = false;
		startTime.at(i) = 0;
	}

	//小節線の初期化
	barLineVec.resize(p_musicData->getBarLength());
	const double timePerBeat = (Global::MINUTE / p_musicData->getBpm()) * Global::QUARTER;
	double timeSum = p_musicData->getBeginDelay();
	for (int i = 0, iSize = static_cast<int>(barLineVec.size()); i < iSize; ++i) {
		barLineVec.at(i) = std::make_unique<Make_Play_BarLine>(timeSum);
		timeSum += timePerBeat;
	}

	//レーンのｘ座標
	double laneX[laneAmount + 1];
	const double laneWidth = (Global::PLAY_LANE_X_MAX - Global::PLAY_LANE_X_MIN) / laneAmount;
	for (int i = 0; i <= laneAmount; ++i) {
		laneX[i] = laneWidth * i + Global::DRAW_X_MIN;
	}

	//レーン周りの描画
	p_lane = std::make_unique<Make_Play_Lane>();

	json::array noteDataArray = val.as_object().at("NoteData").as_array();
	std::uint8_t noteType;
	std::uint8_t laneIndex;
	std::uint8_t directionRightOrLeft;
	std::uint8_t slideNoteIndexStart;
	std::uint8_t slideNoteIndexEnd;
	std::function<void(std::uint8_t, std::uint8_t)> nextNoteFunc = [&](std::uint8_t n, std::uint8_t l) {return nextNote(n,l); };
	for (int i = 0, iSize = static_cast<int>(noteDataArray.size()); i< iSize; ++i) {
		noteType = static_cast<std::uint8_t>(noteDataArray.at(i).at("noteType").as_int64());
		laneIndex = static_cast<std::uint8_t>(noteDataArray.at(i).at("laneInde").as_int64());
		if (noteType == Global::NOTETYPE_NORMAL) {
			normalNoteVec.at(laneIndex)
				.push_back(std::make_unique<Make_Play_NormalNote>(
					noteDataArray.at(i).at("time").as_double(), noteType,
					laneIndex, laneX[laneIndex], laneX[laneIndex + 1], nextNoteFunc));
		}
		else if (noteType == Global::NOTETYPE_LONG) {
			if (isFirst.at(laneIndex)) {
				startTime.at(laneIndex) = noteDataArray.at(i).at("time").as_double();
				isFirst.at(laneIndex) = false;
			}
			else {
				longNoteVec.at(laneIndex)
					.push_back(std::make_unique<Make_Play_LongNote>(
						startTime.at(laneIndex),noteDataArray.at(i).at("time").as_double(), noteType,
						laneIndex, laneX[laneIndex], laneX[laneIndex + 1], nextNoteFunc));
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
			slideNoteIndexStart = static_cast<std::uint8_t>(noteDataArray.at(i).at("slideLaneIndexStart").as_int64());
			slideNoteIndexEnd = static_cast<std::uint8_t>(noteDataArray.at(i).at("slideLaneIndexEnd").as_int64());
			slideNoteVec.at(laneIndex)
				.push_back(std::make_unique<Make_Play_SlideNote>(
					noteDataArray.at(i).at("time").as_double(), noteType,
					laneX[slideNoteIndexStart], laneX[slideNoteIndexEnd],laneIndex,directionRightOrLeft,slideNoteIndexStart,slideNoteIndexEnd, nextNoteFunc));
		}
	}
}

void Make::Play::Make_Play_TestPlayManager::nextNote(const std::uint8_t noteType, const std::uint8_t laneIndex) {
	if (noteType == Global::NOTETYPE_NORMAL) {
		++normalCount.at(laneIndex);
		if (normalCount.at(laneIndex) < normalNoteVec.at(laneIndex).size()) {
			normalNote.at(laneIndex) = normalNoteVec.at(laneIndex).at(normalCount.at(laneIndex)).get();
		}
		else {
			normalNote.at(laneIndex) = nullptr;
		}
	}
	else if (noteType == Global::NOTETYPE_LONG) {
		++longCount.at(laneIndex);
		if (longCount.at(laneIndex) < longNoteVec.at(laneIndex).size()) {
			longNote.at(laneIndex) = longNoteVec.at(laneIndex).at(longCount.at(laneIndex)).get();
		}
		else {
			longNote.at(laneIndex) = nullptr;
		}
	}
	else if (noteType == Global::NOTETYPE_SLIDER || noteType == Global::NOTETYPE_SLIDEL) {
		++slideCount.at(laneIndex);
		if (slideCount.at(laneIndex) < slideNoteVec.at(laneIndex).size()) {
			slideNote.at(laneIndex) = slideNoteVec.at(laneIndex).at(slideCount.at(laneIndex)).get();
		}
		else {
			slideNote.at(laneIndex) = nullptr;
		}
	}
}

const std::function<void()> Make::Play::Make_Play_TestPlayManager::getDrawFunc() {
	return [&] {return draw(); };
}