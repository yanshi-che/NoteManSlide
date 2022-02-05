#include "Game_Draw_LineContainer.h"

std::uint8_t Game::Draw::Game_Draw_LineContainer::noteType = Game::Global::NOTETYPENORMAL;

bool Game::Draw::Game_Draw_LineContainer::clickObserver = false;

int Game::Draw::Game_Draw_LineContainer::mouseX = 0;
int Game::Draw::Game_Draw_LineContainer::mouseY = 0;
std::uint16_t Game::Draw::Game_Draw_LineContainer::startBarIDForLongNote = 0;
std::uint16_t Game::Draw::Game_Draw_LineContainer::startBeatIDForLongNote = 0;
std::uint8_t Game::Draw::Game_Draw_LineContainer::laneIDForLongNote = 0;

std::uint16_t Game::Draw::Game_Draw_LineContainer::barIDForChangeQuontize = 0;

std::uint16_t Game::Draw::Game_Draw_LineContainer::getbarIDForChangeQuontize() {
	return barIDForChangeQuontize;
}

Game::Draw::Game_Draw_LineContainer::Game_Draw_LineContainer(std::uint16_t barID,std::uint8_t amountOfLane,float time,std::uint16_t beatID,float y,float yMax) :
	barID(barID),amountOfLane(amountOfLane),time(time), beatID(beatID){
	this->y = y;
	this->yMax = yMax;
	yMin = y;

	p_mouseCheck = Singleton::Game_Singleton_MouseOperationCheck::getInstance();
	p_noteManager = Singleton::Game_Singleton_NoteManager::getInstance();
	p_noteManager->makeNoteInstance(this->barID,this->beatID,this->y,this->amountOfLane,this->time);

	laneX.resize(amountOfLane + 1);
	float laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / amountOfLane;
	for (int i = 0; i <= amountOfLane; ++i) {
		laneX[i] = laneWidth * i + Global::DRAW_X_MIN;
	}

	barIDColor = GetColor(36, 216, 236);
	std::ios::fmtflags curret_flag = std::cout.flags();
	std::ostringstream ss;
	ss << std::setw(3) << std::setfill('0') << barID + 1;
	barIDStr = ss.str();
	std::cout.flags(curret_flag);
	barIDStrWidth = GetDrawStringWidth(barIDStr.c_str(),static_cast<int>(barIDStr.size()));

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

void Game::Draw::Game_Draw_LineContainer::drawBarID()  {
	if (beatID == 0 && y < Game::Global::WINDOW_HEIGHT && y>0) {
		if (!clickObserver &&
			p_mouseCheck->isMouseClickLeftDown(&mouseX,&mouseY) &&
			0 < mouseX &&
			mouseX < barIDStrWidth &&
			y - barIDThickness < mouseY &&
			mouseY < y - barIDThickness + barIDStrWidth) {
			barIDForChangeQuontize = barID;
			barIDColor = GetColor(36,216,236);
		}
		if(barIDForChangeQuontize != barID){
			barIDColor = GetColor(255,255,255);
		}
		DrawStringF( 0 , y - barIDThickness, barIDStr.c_str(),barIDColor);
	}
}

void Game::Draw::Game_Draw_LineContainer::drawLine()  {
	if (y < Game::Global::WINDOW_HEIGHT && y>0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, brend);
		DrawLineAA(Global::DRAW_X_MIN, y, Global::DRAW_X_MAX, y, color, lineThickness);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void Game::Draw::Game_Draw_LineContainer::drawNotes()  {
	if (noteType == Global::NOTETYPENORMAL) {
		if (!clickObserver && p_mouseCheck->isMouseClickLeftDown(&mouseX,&mouseY) && checkClickBorder()) {
			for (int i = 0,iSize = static_cast<int>(laneX.size()) - 1; i < iSize; ++i) {
				if (laneX[i] < mouseX && mouseX < laneX[i + 1]) {
					p_noteManager->setNormalNote(barID, beatID, i);
					clickObserver = true;
					break;
				}
			}
		}
		if (clickObserver && p_mouseCheck->isMouseClickLeftUp(&mouseX, &mouseY)) {
			clickObserver = false;
		}
	}
	else if (noteType == Global::NOTETYPELONG) {
		if (!clickObserver && p_mouseCheck->isMouseClickLeftDown(&mouseX, &mouseY) && checkClickBorder()) {
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
		if (clickObserver && p_mouseCheck->isMouseClickLeftUp(&mouseX, &mouseY)) {
			float tempMouseY = static_cast<float>(mouseY);
			p_noteManager->setLongNote(NULL, NULL, laneIDForLongNote, &tempMouseY , false);
			clickObserver = false;
		}
	}

	p_noteManager->draw(barID,beatID);
}

void Game::Draw::Game_Draw_LineContainer::setNoteType(std::uint8_t type)  {
	noteType = type;
}

void Game::Draw::Game_Draw_LineContainer::setYMin(float y) {
	yMin = y;
}

void Game::Draw::Game_Draw_LineContainer::updateY(float upY) {
	if (upY < 0 && yMin < y || 0 < upY && y < yMax) {
		y += upY;
		if (yMax < y) {
			y = yMax;
		}
		else if (y < yMin) {
			y = yMin;
		}
	}
}


void Game::Draw::Game_Draw_LineContainer::updateYMax(float y) {
	yMax += y;
}

void Game::Draw::Game_Draw_LineContainer::updateByInitOneBar(float yWidth) {
	y += yWidth;
	yMin += yWidth;
	updateYMax(yWidth);
}

bool Game::Draw::Game_Draw_LineContainer::checkClickBorder() {
	if (std::abs(mouseY - y) <= Global::clickWidth) {
		return true;
	}
	return false;
}


float Game::Draw::Game_Draw_LineContainer::getTime() {
	return time;
}


float Game::Draw::Game_Draw_LineContainer::getY() {
	return y;
}

float Game::Draw::Game_Draw_LineContainer::getYMin() {
	return yMin;
}

float Game::Draw::Game_Draw_LineContainer::getYMax() {
	return yMax;
}
