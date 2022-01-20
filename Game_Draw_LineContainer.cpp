#include "Game_Draw_LineContainer.h"

std::uint8_t Game::Draw::Game_Draw_LineContainer::noteType = Normal;

int Game::Draw::Game_Draw_LineContainer::mouseX = 0;
int Game::Draw::Game_Draw_LineContainer::mouseY = 0;
int Game::Draw::Game_Draw_LineContainer::button = 0;
int Game::Draw::Game_Draw_LineContainer::logType = 0;
bool Game::Draw::Game_Draw_LineContainer::clickObserver = false;
bool Game::Draw::Game_Draw_LineContainer::longClickObserver = false;

std::uint16_t Game::Draw::Game_Draw_LineContainer::startBarIDForLongNote = 0;
std::uint16_t Game::Draw::Game_Draw_LineContainer::startBeatIDForLongNote = 0;
std::uint8_t Game::Draw::Game_Draw_LineContainer::raneIDForLong = 0;

Game::Draw::Game_Draw_LineContainer::Game_Draw_LineContainer(std::uint16_t barID, const std::uint8_t* numberOfRane, double time, std::uint16_t beatID, std::int32_t y, std::int32_t yMax) :
	barID(barID),time(time),numberOfRane(numberOfRane), beatID(beatID), yMin(y), yMax(yMax) {
	this->y = y;
	noteManager = Singleton::Game_Singleton_NoteManager::getInstance();
	noteManager->makeNoteInstance(barID,beatID,&this->y,numberOfRane);
	raneX.resize(*numberOfRane + 1);
	std::uint16_t raneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / *numberOfRane;
	for (int i = 0; i <= *numberOfRane; ++i) {
		raneX[i] = raneWidth * i + Global::DRAW_X_MIN;
	}
	if (beatID == 0) {
		color = GetColor(0, 0, 255);
		lineThickness = 8;
	}
	else {
		if (beatID % 4 == 0) {
			color = GetColor(108, 244, 98);
		}
		else {
			color = GetColor(255, 128, 0);
		}
		lineThickness = 5;
	}
}

void Game::Draw::Game_Draw_LineContainer::drawBarID() noexcept {
	if (beatID == 0 && y < Game::Global::WINDOW_HEIGHT && y>0) {
		DrawFormatString( 0 , y - lineThickness /2, GetColor(255, 255, 255), "%d" , barID + 1);
	}
}

void Game::Draw::Game_Draw_LineContainer::drawLine() noexcept {
	if (y < Game::Global::WINDOW_HEIGHT && y>0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawLine(Global::DRAW_X_MIN, y, Global::DRAW_X_MAX, y, color, lineThickness);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
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

void Game::Draw::Game_Draw_LineContainer::drawNotes() noexcept {
	if (noteType == Normal) {
		if (isMouseClickDown()&&
			std::abs(mouseY - y) <= Global::clickWidth) {
			for (int i = 0,isize = raneX.size() - 1; i < isize; ++i) {
				if (raneX[i] < mouseX && mouseX < raneX[i + 1]) {
					noteManager->setNormalNote(barID, beatID, i);
					clickObserver = true;
					break;
				}
			}
		}
		isMouseClickUp();
	}
	else if (noteType == Long) {
		if (isMouseClickDown()&&
			std::abs(mouseY - y) <= Global::clickWidth) {
			for (int i = 0, isize = raneX.size() - 1; i < isize; ++i) {
				if (raneX[i] < mouseX && mouseX < raneX[i + 1]) {
					startBarIDForLongNote = barID;
					startBeatIDForLongNote = beatID;
					raneIDForLong = i;
					noteManager->setLongNote(barID, beatID, i,&y,true);
					clickObserver = true;
					break;
				}
			}
		}
		if (isMouseClickUp()) {
			noteManager->setLongNote(NULL, NULL, raneIDForLong, &mouseY,false);
		}
	}
	noteManager->draw(barID,beatID);
}

void Game::Draw::Game_Draw_LineContainer::setNoteType(std::uint8_t type) noexcept {
	noteType = type;
}

void Game::Draw::Game_Draw_LineContainer::updateY(std::int16_t y) noexcept {
	if (y < 0 && yMin < this->y || 0 < y && this->y < yMax) {
		this->y += y;
	}
}