#include "Make_Singleton_BeatLineManager.h"

#include <string>

Make::Singleton::Make_Singleton_BeatLineManager* Make::Singleton::Make_Singleton_BeatLineManager::p_instance = nullptr;

Make::Singleton::Make_Singleton_BeatLineManager* Make::Singleton::Make_Singleton_BeatLineManager::getInstance() {
	if (p_instance == nullptr) {
		p_instance = new Make_Singleton_BeatLineManager();
	}
	return p_instance;
}

void Make::Singleton::Make_Singleton_BeatLineManager::destroyInstance() {
	if (p_instance != nullptr) {
		delete p_instance;
		p_instance = nullptr;
	}
}

Make::Singleton::Make_Singleton_BeatLineManager::Make_Singleton_BeatLineManager(){
	p_musicData = nullptr;
	scrBar = nullptr;
	p_laneDraw = nullptr;
	p_noteManager = nullptr;
	y = 0;
	totalScoreWidth = 0;
	yMagnificationByMouseWheel = 25.0f;
	initBarLineFunction = nullptr;
	quontize = Global::QUARTER;
	std::uint16_t barIDForInitOneVector = 0;
}

void Make::Singleton::Make_Singleton_BeatLineManager::draw() {
	if (p_musicData != nullptr) {
		y = GetMouseWheelRotVolF() * yMagnificationByMouseWheel;
		if (y != 0) {
			scrBar->updateBarY(y);
		}
		scrBar->draw();
		for (int i = 0, iSize = static_cast<int>(barVec.size()); i < iSize; ++i) {
			for (int k = 0, kSize = static_cast<int>(barVec.at(i).size()); k < kSize; ++k) {
				if (y != 0) {
					barVec.at(i).at(k)->updateY(y);
				}
				barVec.at(i).at(k)->draw();
			}
		}
		p_laneDraw->draw();
		if (initBarLineFunction != nullptr) {
			initBarLineFunction();
			initBarLineFunction = nullptr;
		}
	}
}

void Make::Singleton::Make_Singleton_BeatLineManager::finalize() {
	p_musicData.reset();
	scrBar.reset();
	resetBarVec(true);
	p_laneDraw.reset();
	Make_Singleton_NoteManager::destroyInstance();
}

void Make::Singleton::Make_Singleton_BeatLineManager::initialize(const std::shared_ptr<File::Make_File_MusicData>& data){
	p_musicData = data;
	initSingletons();
	initBarVec(4, 1.0f);
}

void Make::Singleton::Make_Singleton_BeatLineManager::initBarVec(std::uint8_t initialQuontize,float separateBarWidth) {
	float timeSum = p_musicData->getBeginDelay();
	const float timePerBeat = (p_musicData->getTotalMinutes() * Global::MINUTE / p_musicData->getBarLength() / initialQuontize);
	float initY = initialY;
	const float yWidth = yWidthRegular * separateBarWidth;
	float yMax = 0;
	totalScoreWidth = 0;
	p_noteManager->initVector(p_musicData->getBarLength(),initialQuontize);
	barVec.resize(p_musicData->getBarLength());
	std::uint8_t amountOfLane = p_musicData->getAmountOfLane();
	for (int i = 0,iSize = p_musicData->getBarLength(); i < iSize; i++) {
		barVec.at(i).resize(initialQuontize);
		for (int k = 0; k < initialQuontize; k++) {
			yMax = initY + (yWidth * p_musicData->getBarLength() * initialQuontize) - Make::Global::WINDOW_HEIGHT *0.5f;
			barVec.at(i).at(k)=std::make_shared<Draw::Make_Draw_LineContainer>(i, amountOfLane, timeSum, k, initY,yMax);
			timeSum += timePerBeat;
			initY -= yWidth;
			totalScoreWidth += yWidth;
		}
	}
	totalScoreWidth += Make::Global::WINDOW_HEIGHT * 0.5f;
	initScrollBar();
}

void Make::Singleton::Make_Singleton_BeatLineManager::initializeBySavaData(const std::shared_ptr<File::Make_File_MusicData>& data,const json::value val) {
	p_musicData = data;
	initSingletons();
	//各拍数ごとの時間
	const float forTimePerBeat = p_musicData->getTotalMinutes() * Global::MINUTE / p_musicData->getBarLength();
	const float timePerBeatQuarter = forTimePerBeat / Global::QUARTER;
	const float timePerBeatEighth = forTimePerBeat / Global::EIGHTH;
	const float timePerBeatSixteenth = forTimePerBeat / Global::SIXTEENTH;
	const float timePerBeatThirtySecond = forTimePerBeat / Global::THIRTYSECOND;
	const float timePerBeatTriplet = forTimePerBeat / Global::TRIPLET;

	//各拍数ごとの拍線間の距離
	const float yWidthQuarter = yWidthRegular * checkSeparate(Global::QUARTER);
	const float yWidthEighth = yWidthRegular * checkSeparate(Global::EIGHTH);
	const float yWidthSixteenth = yWidthRegular * checkSeparate(Global::SIXTEENTH);
	const float yWidthThirtySecond = yWidthRegular * checkSeparate(Global::THIRTYSECOND);
	const float yWidthTriplet = yWidthRegular * checkSeparate(Global::TRIPLET);

	float timeSum = p_musicData->getBeginDelay();
	float timePerBeat = 0;
	float initY = initialY;
	float yMax = 0;
	float yWidth = 0;
	totalScoreWidth = 0;
	std::uint8_t amountOfLane = p_musicData->getAmountOfLane();
	p_noteManager->initVector(p_musicData->getBarLength(), NULL);
	barVec.resize(p_musicData->getBarLength());

	json::array barLineDataArray = val.as_object().at("BarLineData").as_array();
	std::uint8_t quo = 0;

	//拍線の設置
	for (int i = 0, iSize = p_musicData->getBarLength(); i < iSize; i++) {
		quo = static_cast<std::uint8_t>(barLineDataArray.at(i).at("quontize").as_int64());
		p_noteManager->resizeOneVector(i, quo);
		barVec.at(i).resize(quo);
		if (quo == Global::QUARTER) {
			yWidth = yWidthQuarter;
			timePerBeat = timePerBeatQuarter;
		}
		else if (quo == Global::EIGHTH) {
			yWidth = yWidthEighth;
			timePerBeat = timePerBeatEighth;
		}else if (quo == Global::SIXTEENTH) {
			yWidth = yWidthSixteenth;
			timePerBeat = timePerBeatSixteenth;
		}else if (quo == Global::THIRTYSECOND) {
			yWidth = yWidthThirtySecond;
			timePerBeat = timePerBeatThirtySecond;
		}else if (quo == Global::TRIPLET) {
			yWidth = yWidthTriplet;
			timePerBeat = timePerBeatTriplet;
		}

		for (int k = 0; k < quo; k++) {
			yMax = initY + (yWidth * p_musicData->getBarLength() * quo) - Make::Global::WINDOW_HEIGHT * 0.5f;
			barVec.at(i).at(k) = std::make_shared<Draw::Make_Draw_LineContainer>(i, amountOfLane, timeSum, k, initY, yMax);
			timeSum += timePerBeat;
			initY -= yWidth;
			totalScoreWidth += yWidth;
		}
	}

	//ノーツの設置
	json::array noteDataArray = val.as_object().at("NoteData").as_array();
	std::uint8_t noteType = 0;
	bool isRight = true;
	bool isFirst = true;
	struct longNotePoint {//終点が読み込まれるまでlongNoteの始点情報を保管するためのもの
		std::uint16_t barID;
		std::uint8_t beatID;
		std::uint16_t longNoteGroupIndex;
		longNotePoint(std::uint16_t barID, std::uint8_t beatID, std::uint16_t longNoteGroupIndex) { this->barID = barID; this->beatID = beatID; this->longNoteGroupIndex = longNoteGroupIndex; }
	};
	std::deque<longNotePoint> longNotePointDeq;//終点が読み込まれるまでlongNoteの始点情報を保管
	for (int i = 0, iSize = static_cast<int>(noteDataArray.size()); i < iSize; ++i) {
		noteType = static_cast<std::uint8_t>(noteDataArray.at(i).at("noteType").as_int64());
		if (noteType == Global::NOTETYPENORMAL) {
			p_noteManager->setNormalNote(static_cast<std::uint16_t>(noteDataArray.at(i).at("barID").as_int64()),
				static_cast<std::uint8_t>(noteDataArray.at(i).at("beatID").as_int64()),
				static_cast<std::uint8_t>(noteDataArray.at(i).at("laneIndex").as_int64()));
		}
		else if (noteType == Global::NOTETYPELONG) {
			for (int k = 0, kSize = static_cast<int>(longNotePointDeq.size()); k < kSize; ++k) {
				if (longNotePointDeq.at(k).longNoteGroupIndex == noteDataArray.at(i).at("longNoteGroupIndex").as_int64()) {
					p_noteManager->setLongNoteBySavaData(longNotePointDeq.at(k).barID,longNotePointDeq.at(k).beatID,
						static_cast<std::uint16_t>(noteDataArray.at(i).at("barID").as_int64()),
						static_cast<std::uint8_t>(noteDataArray.at(i).at("beatID").as_int64()),
						static_cast<std::uint8_t>(noteDataArray.at(i).at("laneIndex").as_int64()));
					longNotePointDeq.erase(longNotePointDeq.begin() + k);
					isFirst = false;
					break;
				}
			}
			if (isFirst) {
				longNotePointDeq.push_back(longNotePoint(static_cast<std::uint16_t>(noteDataArray.at(i).at("barID").as_int64()),
					static_cast<std::uint8_t>(noteDataArray.at(i).at("beatID").as_int64()),
					static_cast<std::uint16_t>(noteDataArray.at(i).at("longNoteGroupIndex").as_int64())));
			}
			isFirst = true;
		}
		else if (noteType == Global::NOTETYPESLIDE) {
			if (noteDataArray.at(i).at("rightOrLeft").as_int64() == 1) {
				isRight = true;
			}
			else {
				isRight = false;
			}
			p_noteManager->setSlideNoteBySavaData(static_cast<std::uint16_t>(noteDataArray.at(i).at("barID").as_int64()),
				static_cast<std::uint8_t>(noteDataArray.at(i).at("beatID").as_int64()),
				static_cast<std::uint8_t>(noteDataArray.at(i).at("slideLaneIndexStart").as_int64()),
				static_cast<std::uint8_t>(noteDataArray.at(i).at("slideLaneIndexEnd").as_int64()),isRight);
		}
	}
	totalScoreWidth += Make::Global::WINDOW_HEIGHT * 0.5f;
	initScrollBar();
}

void Make::Singleton::Make_Singleton_BeatLineManager::initScrollBar() {
	scrBar = std::make_unique<Draw::Make_Draw_ScrollBar>(totalScoreWidth,barVec,yMagnificationByMouseWheel);
}

void Make::Singleton::Make_Singleton_BeatLineManager::initSingletons() {
	p_laneDraw = std::make_unique<Make_Draw_LaneDraw>();
	p_laneDraw->setamountOfLane(p_musicData->getAmountOfLane());
	p_noteManager = Make_Singleton_NoteManager::getInstance();
}

void Make::Singleton::Make_Singleton_BeatLineManager::initAllBarLineByQuontizeChange() {
	resetScrollBar();
	resetBarVec(true);
	p_noteManager->resetVector(true,NULL);
	initBarVec(quontize, checkSeparate(quontize));
}

void Make::Singleton::Make_Singleton_BeatLineManager::initOneBarLineByQuontizeChange() {
	std::uint16_t id = Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize();
	std::uint16_t beforeQuontize = static_cast<std::uint16_t>(barVec.at(id).size());
	//ロングノーツがまたがっていたら削除処理
	for (int i = 1,iSize= static_cast<int>(barVec.at(id).size()); i < iSize; ++i) {
		for (int k = 0, kSize = p_musicData->getAmountOfLane(); k < kSize; ++k) {
			p_noteManager->removeLongNote(id, i, k);
		}
	}
	//vectorの初期化とリサイズ、スクロールバーのリセット
	resetScrollBar();
	resetBarVec(false);
	p_noteManager->resetVector(false,barIDForInitOneVector);
	float separate = checkSeparate(quontize);

	//ノーツの初期化
	p_noteManager->initOneVector(quontize,barIDForInitOneVector);

	// 新たな拍線の作成
	const float timePerBeat = (p_musicData->getTotalMinutes() * Global::MINUTE / p_musicData->getBarLength() / quontize);
	float timeSum = barVec.at(id).at(0)->getTime();
	const float yWidth = yWidthRegular * separate;
	float initY = barVec.at(id).at(0)->getY();
	float yMax = barVec.at(id).at(0)->getYMax();
	float yMin = barVec.at(id).at(0)->getYMin();
	float yChange = 0;//変更した小節全体の幅
	std::uint8_t amountOfLane = p_musicData->getAmountOfLane();
	barVec.at(id).resize(quontize);
	for (int i = 1; i < quontize; ++i) {
		timeSum += timePerBeat;
		initY -= yWidth;
		yMax -= yWidth;
		yMin -= yWidth;
		yChange -= yWidth;
		barVec.at(id).at(i) = std::make_unique<Draw::Make_Draw_LineContainer>(id, amountOfLane, timeSum, i, initY, yMax);
		barVec.at(id).at(i)->setYMin(yMin);
	}

	//変更した小節より後の小節の座標調整
	yChange -= yWidth;
	if (id < p_musicData->getBarLength() - 1) {
		yChange = yChange + (barVec.at(id).at(0)->getY() - barVec.at(id + 1).at(0)->getY());//変化量
		for (int i = 0; i < id; ++i) {
			for (int k = 0,kSize = static_cast<int>(barVec.at(i).size()); k < kSize; ++k) {
				barVec.at(i).at(k)->updateYMax(yChange);
			}
		}
		for (int i = id + 1,iSize = static_cast<int>(barVec.size()); i < iSize; ++i) {
			for (int k = 0, kSize = static_cast<int>(barVec.at(i).size()); k < kSize; ++k) {
				barVec.at(i).at(k)->updateByInitOneBar(yChange);
			}
		}
	}

	//スクロールバーの初期化
	totalScoreWidth -= yChange;
	initScrollBar();
	scrBar->updateBarY(barVec.at(0).at(0)->getY() - initialY);
}

float Make::Singleton::Make_Singleton_BeatLineManager::checkSeparate(const std::uint8_t quontize) {
	if (quontize == Global::QUARTER) {
		return(1.0f);
	}
	else if (quontize == Global::EIGHTH) {
		return(0.5f);
	}
	else if (quontize == Global::SIXTEENTH) {
		return(0.25f);
	}
	else if (quontize == Global::THIRTYSECOND) {
		return(0.125f);
	}
	else if (quontize == Global::TRIPLET) {
		return(0.3333f);
	}
	return(1.0f);
}

void Make::Singleton::Make_Singleton_BeatLineManager::resetBarVec(bool isAll) {
	if (isAll) {
		for (int i = 0, iSize = static_cast<int>(barVec.size()); i < iSize; ++i) {
			for (int k = 0, kSize = static_cast<int>(barVec.at(i).size()); k < kSize; ++k) {
				barVec.at(i).at(k).reset();
			}
		}
	}
	else {
		const std::uint16_t id = Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize();
		for (int i = 1, iSize = static_cast<int>(barVec.at(id).size()); i < iSize; ++i) {
			barVec.at(id).at(i).reset();
		}
	}
}

void Make::Singleton::Make_Singleton_BeatLineManager::resetScrollBar() {
	scrBar.reset();
}

void Make::Singleton::Make_Singleton_BeatLineManager::setInitBarLineFunc(const std::uint8_t quon,const std::uint16_t barIDForInitOneVector,const bool isAll) {
	this->quontize = quon;
	this->barIDForInitOneVector = barIDForInitOneVector;
	if (isAll) {
		initBarLineFunction = [&]{return initAllBarLineByQuontizeChange(); };
	}
	else {
		initBarLineFunction = [&]{return initOneBarLineByQuontizeChange(); };
	}
}

const std::vector<std::vector<std::shared_ptr<Make::Draw::Make_Draw_LineContainer>>>& Make::Singleton::Make_Singleton_BeatLineManager::getBarVec() {
	return barVec;
}