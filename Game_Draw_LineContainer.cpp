#include "Game_Draw_LineContainer.h"

std::uint8_t Game::Draw::Game_Draw_LineContainer::noteType = Game::Global::NOTETYPENORMAL;

int Game::Draw::Game_Draw_LineContainer::mouseX = 0;
int Game::Draw::Game_Draw_LineContainer::mouseY = 0;
int Game::Draw::Game_Draw_LineContainer::button = 0;
int Game::Draw::Game_Draw_LineContainer::logType = 0;
bool Game::Draw::Game_Draw_LineContainer::clickObserver = false;
bool Game::Draw::Game_Draw_LineContainer::longClickObserver = false;

std::uint16_t Game::Draw::Game_Draw_LineContainer::startBarIDForLongNote = 0;
std::uint16_t Game::Draw::Game_Draw_LineContainer::startBeatIDForLongNote = 0;
std::uint8_t Game::Draw::Game_Draw_LineContainer::laneIDForLongNote = 0;

std::uint16_t Game::Draw::Game_Draw_LineContainer::barIDForChangeQuontize = 0;

std::uint16_t Game::Draw::Game_Draw_LineContainer::getbarIDForChangeQuontize() {
	return barIDForChangeQuontize;
}

Game::Draw::Game_Draw_LineContainer::Game_Draw_LineContainer(std::uint16_t barID, const std::uint8_t& amountOfLane, double time, std::uint16_t beatID, std::int32_t y, std::int32_t yMax) :
	barID(barID),r_amountOfLane(amountOfLane),time(time), beatID(beatID){
	this->y = y;
	this->yMax = yMax;
	yMin = y;
	p_noteManager = Singleton::Game_Singleton_NoteManager::getInstance();
	p_noteManager->makeNoteInstance(this->barID,this->beatID,this->y,amountOfLane,this->time);
	laneX.resize(amountOfLane + 1);
	std::uint16_t laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / amountOfLane;
	for (int i = 0; i <= amountOfLane; ++i) {
		laneX[i] = laneWidth * i + Global::DRAW_X_MIN;
	}
	barIDColor = GetColor(36, 216, 236);
	barIDStrWidth = GetDrawFormatStringWidth("%d", barID + 1);
	if (beatID == 0) {
		color = GetColor(0, 0, 255);
		lineThickness = 8;
		barIDThickness = lineThickness / 2;
		brend = 128;
	}
	else {
		if (beatID % 4 == 0) {
			color = GetColor(108, 244, 98);
		}
		else {
			color = GetColor(255, 128, 0);
		}
		brend = 96;
		lineThickness = 5;
		barIDThickness = NULL;
	}
}

void Game::Draw::Game_Draw_LineContainer::draw() {
	drawLine();
	drawBarID();
	drawNotes();
}

void Game::Draw::Game_Draw_LineContainer::updateY(std::int8_t& y) {
	if (y < 0 && yMin < this->y || 0 < y && this->y < yMax) {
		this->y += y;
	}
}

void Game::Draw::Game_Draw_LineContainer::drawBarID()  {
	if (beatID == 0 && y < Game::Global::WINDOW_HEIGHT && y>0) {
		if (isMouseClickDown() && 0 < mouseX && mouseX < barIDStrWidth && y - barIDThickness < mouseY && mouseY < y - barIDThickness + barIDStrWidth) {
			barIDForChangeQuontize = barID;
			barIDColor = GetColor(36,216,236);
		}
		if(barIDForChangeQuontize != barID){
			barIDColor = GetColor(255,255,255);
		}
		DrawFormatString( 0 , y - barIDThickness, barIDColor, "%d" , barID + 1);
	}
}

void Game::Draw::Game_Draw_LineContainer::drawLine()  {
	if (y < Game::Global::WINDOW_HEIGHT && y>0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, brend);
		DrawLine(Global::DRAW_X_MIN, y, Global::DRAW_X_MAX, y, color, lineThickness);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void Game::Draw::Game_Draw_LineContainer::drawNotes()  {
	if (noteType == Global::NOTETYPENORMAL) {
		if (isMouseClickDown() && checkClickBorder()) {
			for (int i = 0,iSize = static_cast<int>(laneX.size()) - 1; i < iSize; ++i) {
				if (laneX[i] < mouseX && mouseX < laneX[i + 1]) {
					p_noteManager->setNormalNote(barID, beatID, i);
					clickObserver = true;
					break;
				}
			}
		}
		isMouseClickUp();
	}
	else if (noteType == Global::NOTETYPELONG) {
		if (isMouseClickDown() && checkClickBorder()) {
			for (int i = 0, iSize = static_cast<int>(laneX.size()) - 1; i < iSize; ++i) {
				if (laneX[i] < mouseX && mouseX < laneX[i + 1]) {
					startBarIDForLongNote = barID;
					startBeatIDForLongNote = beatID;
					laneIDForLongNote = i;
					p_noteManager->setLongNote(barID, beatID, i,&y,true);
					clickObserver = true;
					break;
				}
			}
		}
		if (isMouseClickUp()) {
			p_noteManager->setLongNote(NULL, NULL, laneIDForLongNote, &mouseY,false);
		}
	}

	p_noteManager->draw(barID,beatID);
}

void Game::Draw::Game_Draw_LineContainer::setNoteType(std::uint8_t type)  {
	noteType = type;
}


void Game::Draw::Game_Draw_LineContainer::setYMin(std::int32_t y) {
	yMin = y;
}

void Game::Draw::Game_Draw_LineContainer::updateYMax(std::int32_t y) {
	yMax += y;
}

void Game::Draw::Game_Draw_LineContainer::updateByInitOneBar(std::int32_t& yWidth) {
	y += yWidth;
	yMin += yWidth;
	updateYMax(yWidth);
}

bool Game::Draw::Game_Draw_LineContainer::isMouseClickDown() {
	if (!clickObserver&&
		GetMouseInputLog2(&button, &mouseX, &mouseY, &logType, true) &&
		logType == MOUSE_INPUT_LOG_DOWN &&
		button == MOUSE_INPUT_LEFT) {
		return true;
	}
	return false;
}

bool Game::Draw::Game_Draw_LineContainer::isMouseClickUp() {
	if (clickObserver &&
		GetMouseInputLog2(&button, &mouseX, &mouseY, &logType, true) &&
		logType == MOUSE_INPUT_LOG_UP &&
		button == MOUSE_INPUT_LEFT) {
		clickObserver = false;
		return true;
	}
	return false;
}

bool Game::Draw::Game_Draw_LineContainer::checkClickBorder() {
	if (std::abs(mouseY - y) <= Global::clickWidth) {
		return true;
	}
	return false;
}


double Game::Draw::Game_Draw_LineContainer::getTime() {
	return time;
}


std::int32_t Game::Draw::Game_Draw_LineContainer::getY() {
	return y;
}

std::int32_t Game::Draw::Game_Draw_LineContainer::getYMin() {
	return yMin;
}

std::int32_t Game::Draw::Game_Draw_LineContainer::getYMax() {
	return yMax;
}
