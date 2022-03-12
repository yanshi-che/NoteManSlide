#include "Make_Draw_BeatLineManager.h"

Make::Draw::Make_Draw_BeatLineManager::Make_Draw_BeatLineManager(){
	p_musicData = nullptr;
	scrBar = nullptr;
	p_laneDraw = nullptr;
	p_noteManager = nullptr;
	y = 0;
	totalScoreWidth = 0;
	yMagnificationByMouseWheel = 25.0;
	initBarLineFunction = nullptr;
	quontize = Global::QUARTER;
	std::uint16_t barIDForInitOneVector = 0;
}

void Make::Draw::Make_Draw_BeatLineManager::draw() {
	if (p_musicData != nullptr) {
		p_laneDraw->draw();
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
		if (initBarLineFunction != nullptr) {
			initBarLineFunction();
			initBarLineFunction = nullptr;
		}
	}
}

void Make::Draw::Make_Draw_BeatLineManager::finalize() {
	p_musicData.reset();
	scrBar.reset();
	resetBarVec(true);
	p_laneDraw.reset();
	p_noteManager.reset();
}

void Make::Draw::Make_Draw_BeatLineManager::initialize(const std::shared_ptr<File::Make_File_MusicData>& data){
	p_musicData = data;
	initOtherClass();
	initBarVec(Global::QUARTER, checkSeparate(Global::QUARTER));
}

void Make::Draw::Make_Draw_BeatLineManager::initBarVec(std::uint16_t initialQuontize,double separateBarWidth) {
	double timeSum = p_musicData->getBeginDelay();
	const double timePerBeat = (Global::MINUTE / p_musicData->getBpm() / (initialQuontize / Global::QUARTER));
	double initY = initialY;
	const double yWidth = yWidthRegular * separateBarWidth;
	double yMax = 0;
	totalScoreWidth = 0;
	p_noteManager->initVector(p_musicData->getBarLength(),initialQuontize);
	barVec.resize(p_musicData->getBarLength());
	for (int i = 0,iSize = p_musicData->getBarLength(); i < iSize; i++) {
		barVec.at(i).resize(initialQuontize);
		for (int k = 0; k < initialQuontize; k++) {
			yMax = initY + (yWidth * p_musicData->getBarLength() * initialQuontize) - Global::WINDOW_HEIGHT *0.5;
			barVec.at(i).at(k)=std::make_shared<Draw::Make_Draw_LineContainer>(i, timeSum, k,initialQuontize, initY,yMax,p_noteManager);
			timeSum += timePerBeat;
			initY -= yWidth;
			totalScoreWidth += yWidth;
		}
	}
	totalScoreWidth += Global::WINDOW_HEIGHT * 0.5;
	initScrollBar();
}

void Make::Draw::Make_Draw_BeatLineManager::initializeBySavaData(const std::shared_ptr<File::Make_File_MusicData>& data,const json::value& val) {
	p_musicData = data;
	initOtherClass();
	//各拍数ごとの時間
	const double timePerBeatQuarter = Global::MINUTE / p_musicData->getBpm();
	const double timePerBeatEighth = timePerBeatQuarter * (static_cast<double>(Global::QUARTER) / static_cast<double>(Global::EIGHTH));
	const double timePerBeatSixteenth = timePerBeatQuarter * (static_cast<double>(Global::QUARTER) / static_cast<double>(Global::SIXTEENTH));
	const double timePerBeatThirtySecond = timePerBeatQuarter * (static_cast<double>(Global::QUARTER) / static_cast<double>(Global::THIRTYSECOND));
	const double timePerBeatTriplet = timePerBeatQuarter * (static_cast<double>(Global::QUARTER) / static_cast<double>(Global::TRIPLET));

	//各拍数ごとの拍線間の距離
	const double yWidthQuarter = yWidthRegular * checkSeparate(Global::QUARTER);
	const double yWidthEighth = yWidthRegular * checkSeparate(Global::EIGHTH);
	const double yWidthSixteenth = yWidthRegular * checkSeparate(Global::SIXTEENTH);
	const double yWidthThirtySecond = yWidthRegular * checkSeparate(Global::THIRTYSECOND);
	const double yWidthTriplet = yWidthRegular * checkSeparate(Global::TRIPLET);

	double timeSum = p_musicData->getBeginDelay();
	double timePerBeat = 0;
	double initY = initialY;
	double yMax = 0;
	double yWidth = 0;
	totalScoreWidth = 0;
	p_noteManager->initVector(p_musicData->getBarLength(), NULL);
	barVec.resize(p_musicData->getBarLength());

	json::array barLineDataArray = val.as_object().at("BarLineData").as_array();
	std::uint16_t quo = 0;

	//拍線の設置
	for (int i = 0, iSize = p_musicData->getBarLength(); i < iSize; i++) {
		quo = static_cast<std::uint16_t>(barLineDataArray.at(i).at("quontize").as_int64());
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
			yMax = initY + (yWidth * p_musicData->getBarLength() * quo) - Global::WINDOW_HEIGHT * 0.5;
			barVec.at(i).at(k) = std::make_shared<Draw::Make_Draw_LineContainer>(i,timeSum, k,quo, initY, yMax,p_noteManager);
			timeSum += timePerBeat;
			initY -= yWidth;
			totalScoreWidth += yWidth;
		}
	}

	//ノーツの設置
	json::array noteDataArray = val.as_object().at("NoteData").as_array();
	std::uint16_t noteType = 0;
	bool isRight = true;
	bool isDirectionRight = true;
	bool isFirst = true;
	struct longDrawPoint {//終点が読み込まれるまでlongDrawの始点情報を保管するためのもの
		std::uint16_t barID;
		std::uint16_t beatID;
		std::uint16_t longDrawGroupIndex;
		longDrawPoint(std::uint16_t barID, std::uint16_t beatID, std::uint16_t longDrawGroupIndex) { this->barID = barID; this->beatID = beatID; this->longDrawGroupIndex = longDrawGroupIndex; }
	};
	std::deque<longDrawPoint> longDrawPointDeq;//終点が読み込まれるまでlongDrawの始点情報を保管
	for (int i = 0, iSize = static_cast<int>(noteDataArray.size()); i < iSize; ++i) {
		noteType = static_cast<std::uint16_t>(noteDataArray.at(i).at("noteType").as_int64());
		if (noteType == Global::NOTETYPE_NORMAL) {
			p_noteManager->setNormalNote(static_cast<std::uint16_t>(noteDataArray.at(i).at("barID").as_int64()),
				static_cast<std::uint16_t>(noteDataArray.at(i).at("beatID").as_int64()),
				static_cast<std::uint16_t>(noteDataArray.at(i).at("laneIndex").as_int64()));
		}
		else if (noteType == Global::NOTETYPE_LONG) {
			for (int k = 0, kSize = static_cast<int>(longDrawPointDeq.size()); k < kSize; ++k) {
				if (longDrawPointDeq.at(k).longDrawGroupIndex == noteDataArray.at(i).at("longNoteGroupIndex").as_int64()) {
					p_noteManager->setLongNoteBySavaData(longDrawPointDeq.at(k).barID,longDrawPointDeq.at(k).beatID,
						static_cast<std::uint16_t>(noteDataArray.at(i).at("barID").as_int64()),
						static_cast<std::uint16_t>(noteDataArray.at(i).at("beatID").as_int64()),
						static_cast<std::uint16_t>(noteDataArray.at(i).at("laneIndex").as_int64()));
					longDrawPointDeq.erase(longDrawPointDeq.begin() + k);
					isFirst = false;
					break;
				}
			}
			if (isFirst) {
				longDrawPointDeq.push_back(longDrawPoint(static_cast<std::uint16_t>(noteDataArray.at(i).at("barID").as_int64()),
					static_cast<std::uint16_t>(noteDataArray.at(i).at("beatID").as_int64()),
					static_cast<std::uint16_t>(noteDataArray.at(i).at("longNoteGroupIndex").as_int64())));
			}
			isFirst = true;
		}
		else if (noteType == Global::NOTETYPE_SLIDER || noteType == Global::NOTETYPE_SLIDEL) {
			if (noteDataArray.at(i).at("rightOrLeft").as_int64() == 1) {
				isRight = true;
			}
			else {
				isRight = false;
			}
			if (noteDataArray.at(i).at("directionRightOrLeft").as_int64() == 1) {
				isDirectionRight = true;
			}
			else {
				isDirectionRight = false;
			}
			p_noteManager->setSlideNoteBySavaData(static_cast<std::uint16_t>(noteDataArray.at(i).at("barID").as_int64()),
				static_cast<std::uint16_t>(noteDataArray.at(i).at("beatID").as_int64()),
				static_cast<std::uint16_t>(noteDataArray.at(i).at("slideLaneIndexStart").as_int64()),
				static_cast<std::uint16_t>(noteDataArray.at(i).at("slideLaneIndexEnd").as_int64()),isRight,isDirectionRight);
		}
	}
	totalScoreWidth += Global::WINDOW_HEIGHT * 0.5;
	initScrollBar();
}

void Make::Draw::Make_Draw_BeatLineManager::initScrollBar() {
	scrBar = std::make_unique<Draw::Make_Draw_ScrollBar>(totalScoreWidth,barVec,yMagnificationByMouseWheel);
}

void Make::Draw::Make_Draw_BeatLineManager::initOtherClass() {
	p_laneDraw = std::make_unique<Make_Draw_LaneDraw>();
	p_noteManager = std::make_shared<Note::Make_Note_NoteManager>();
}

void Make::Draw::Make_Draw_BeatLineManager::initAllBarLineByQuontizeChange() {
	resetScrollBar();
	resetBarVec(true);
	p_noteManager->resetVector(true,NULL);
	initBarVec(quontize, checkSeparate(quontize));
}

void Make::Draw::Make_Draw_BeatLineManager::initOneBarLineByQuontizeChange() {
	std::uint16_t id = Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize();
	std::uint16_t beforeQuontize = static_cast<std::uint16_t>(barVec.at(id).size());
	//ロングノーツがまたがっていたら削除処理
	for (int i = 1,iSize= static_cast<int>(barVec.at(id).size()); i < iSize; ++i) {
		for (int k = 0, kSize = Global::LANE_AMOUNT; k < kSize; ++k) {
			p_noteManager->removeLongNote(id, i, k);
		}
	}
	//vectorの初期化とリサイズ、スクロールバーのリセット
	resetScrollBar();
	resetBarVec(false);
	p_noteManager->resetVector(false,barIDForInitOneVector);
	double separate = checkSeparate(quontize);

	//ノーツの初期化
	p_noteManager->initOneVector(quontize,barIDForInitOneVector);

	// 新たな拍線の作成
	const double timePerBeat = (Global::MINUTE / p_musicData->getBpm() / (quontize / Global::QUARTER));
	double timeSum = barVec.at(id).at(0)->getTime();
	const double yWidth = yWidthRegular * separate;
	double initY = barVec.at(id).at(0)->getY();
	double yMax = barVec.at(id).at(0)->getYMax();
	double yMin = barVec.at(id).at(0)->getYMin();
	double yChange = 0;//変更した小節全体の幅
	barVec.at(id).resize(quontize);
	for (int i = 1; i < quontize; ++i) {
		timeSum += timePerBeat;
		initY -= yWidth;
		yMax -= yWidth;
		yMin -= yWidth;
		yChange -= yWidth;
		barVec.at(id).at(i) = std::make_unique<Draw::Make_Draw_LineContainer>(id,timeSum, i,quontize, initY, yMax,p_noteManager);
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

double Make::Draw::Make_Draw_BeatLineManager::checkSeparate(const std::uint16_t quontize) {
	if (quontize == Global::QUARTER) {
		return(1.0);
	}
	else if (quontize == Global::EIGHTH) {
		return(0.5);
	}
	else if (quontize == Global::SIXTEENTH) {
		return(0.25);
	}
	else if (quontize == Global::THIRTYSECOND) {
		return(0.125);
	}
	else if (quontize == Global::TRIPLET) {
		return(0.33333333);
	}
	return(1.0);
}

void Make::Draw::Make_Draw_BeatLineManager::resetBarVec(bool isAll) {
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

void Make::Draw::Make_Draw_BeatLineManager::resetScrollBar() {
	scrBar.reset();
}

void Make::Draw::Make_Draw_BeatLineManager::setInitBarLineFunc(const std::uint16_t quon,const std::uint16_t barIDForInitOneVector,const bool isAll) {
	this->quontize = quon;
	this->barIDForInitOneVector = barIDForInitOneVector;
	if (isAll) {
		initBarLineFunction = [&]{return initAllBarLineByQuontizeChange(); };
	}
	else {
		initBarLineFunction = [&]{return initOneBarLineByQuontizeChange(); };
	}
}

const std::function<void()> Make::Draw::Make_Draw_BeatLineManager::getDrawFunc() {
	return [&] {return draw(); };
}

const std::vector<std::vector<std::shared_ptr<Make::Draw::Make_Draw_LineContainer>>>& Make::Draw::Make_Draw_BeatLineManager::getBarVec() {
	return barVec;
}

const std::shared_ptr<Make::Note::Make_Note_NoteManager>& Make::Draw::Make_Draw_BeatLineManager::getNoteManager() {
	return p_noteManager;
}