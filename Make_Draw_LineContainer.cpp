#include "Make_Draw_LineContainer.h"

std::uint16_t Make::Draw::Make_Draw_LineContainer::noteType = Global::NOTETYPE_NORMAL;

bool Make::Draw::Make_Draw_LineContainer::clickObserver = false;

int Make::Draw::Make_Draw_LineContainer::mouseX = 0;
int Make::Draw::Make_Draw_LineContainer::mouseY = 0;
std::uint16_t Make::Draw::Make_Draw_LineContainer::laneIDForLongNote = 0;

std::uint16_t Make::Draw::Make_Draw_LineContainer::barIDForChangeQuontize = 0;

std::uint16_t Make::Draw::Make_Draw_LineContainer::getbarIDForChangeQuontize() {
	return barIDForChangeQuontize;
}

Make::Draw::Make_Draw_LineContainer::Make_Draw_LineContainer(const std::uint16_t barID,const double time,const std::uint16_t beatID, const std::uint16_t quontize,const double y,const double yMax, const std::shared_ptr<Note::Make_Note_NoteManager>& p_noteManager) :
	barID(barID),laneAmount(Global::LANE_AMOUNT),time(time), beatID(beatID),p_noteManager(p_noteManager){
	this->y = y;
	this->yMax = yMax;
	yMin = y;

	p_mouseCheck = Singleton::Make_Singleton_MouseOperationCheck::getInstance();
	this->p_noteManager->makeNoteInstance(this->barID,this->beatID,this->y,this->laneAmount,this->time);

	laneX.resize(laneAmount + 1);
	double laneWidth = (Global::DRAW_X_MAX - Global::DRAW_X_MIN) / laneAmount;
	for (int i = 0; i <= laneAmount; ++i) {
		laneX.at(i) = laneWidth * i + Global::DRAW_X_MIN;
	}

	barIDColor = GetColor(36, 216, 236);
	const std::ios::fmtflags curret_flag = std::cout.flags();
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
		if (quontize == Global::QUARTER) {
			color = GetColor(255, 128, 0);
		}
		else if(quontize == Global::EIGHTH){
			if (beatID % 2 == 0) {
				color = GetColor(108, 244, 98);
			}
			else {
				color = GetColor(255, 128, 0);
			}
		}
		else if (quontize == Global::SIXTEENTH) {
			if (beatID % 4 == 0) {
				color = GetColor(108, 244, 98);
			}
			else {
				color = GetColor(255, 128, 0);
			}
		}
		else if (quontize == Global::THIRTYSECOND) {
			if (beatID % 8 == 0) {
				color = GetColor(108, 244, 98);
			}
			else {
				color = GetColor(255, 128, 0);
			}
		}
		else if (quontize == Global::TRIPLET) {
			if (beatID % 3 == 0) {
				color = GetColor(108, 244, 98);
			}
			else {
				color = GetColor(255, 128, 0);
			}
		}
		brend = 96;
		lineThickness = 5;
		barIDThickness = NULL;
	}
}

void Make::Draw::Make_Draw_LineContainer::draw() {
	drawLine();
	drawBarID();
	drawNote();
}

void Make::Draw::Make_Draw_LineContainer::drawBarID()  {
	if (beatID == 0 && y < Global::WINDOW_HEIGHT && y>0) {
		if (!clickObserver &&
			p_mouseCheck->isMouseClickLeftDown(mouseX,mouseY) &&
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
		DrawStringF( 0 , static_cast<float>(y - barIDThickness), barIDStr.c_str(),barIDColor);
	}
}

void Make::Draw::Make_Draw_LineContainer::drawLine()  {
	if (y < Global::WINDOW_HEIGHT && y>0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, brend);
		DrawLineAA(static_cast<float>(Global::DRAW_X_MIN), static_cast<float>(y), static_cast<float>(Global::DRAW_X_MAX), static_cast<float>(y) , color, lineThickness);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}

void Make::Draw::Make_Draw_LineContainer::drawNote()  {
	if (noteType == Global::NOTETYPE_NORMAL) {
		setNoteNormal();
	}
	else if (noteType == Global::NOTETYPE_LONG) {
		setNoteLong();
	}
	else if (noteType == Global::NOTETYPE_SLIDER) {
		setNoteSlideR();
	}
	else if (noteType == Global::NOTETYPE_SLIDEL) {
		setNoteSlideL();
	}

	p_noteManager->draw(barID,beatID);
}

void Make::Draw::Make_Draw_LineContainer::setNoteNormal() {
	if (!clickObserver && p_mouseCheck->isMouseClickLeftDown(mouseX, mouseY) && checkClickBorder()) {
		for (int i = 0, iSize = static_cast<int>(laneX.size()) - 1; i < iSize; ++i) {
			if (laneX.at(i) < mouseX && mouseX < laneX.at(i + 1)) {
				p_noteManager->setNormalNote(barID, beatID, i);
				clickObserver = true;
				barIDForChangeQuontize = barID;
				barIDColor = GetColor(36, 216, 236);
				break;
			}
		}
	}
	if (clickObserver && p_mouseCheck->isMouseClickLeftUp(mouseX, mouseY)) {
		clickObserver = false;
	}
}

void Make::Draw::Make_Draw_LineContainer::setNoteLong() {
	if (!clickObserver && p_mouseCheck->isMouseClickLeftDown(mouseX, mouseY) && checkClickBorder()) {
		for (int i = 0, iSize = static_cast<int>(laneX.size()) - 1; i < iSize; ++i) {
			if (laneX.at(i) < mouseX && mouseX < laneX.at(i + 1)) {
				laneIDForLongNote = i;
				p_noteManager->setLongNote(barID, beatID, i, &y, true);
				clickObserver = true;
				barIDForChangeQuontize = barID;
				barIDColor = GetColor(36, 216, 236);
				break;
			}
		}
	}
	if (clickObserver && p_mouseCheck->isMouseClickLeftUp(mouseX, mouseY)) {
		double tempMouseY = static_cast<double>(mouseY);
		p_noteManager->setLongNote(NULL, NULL, laneIDForLongNote, &tempMouseY, false);
		clickObserver = false;
	}
}

void Make::Draw::Make_Draw_LineContainer::setNoteSlideR() {
	if (!clickObserver && p_mouseCheck->isMouseClickLeftDown(mouseX, mouseY) && checkClickBorder()) {
		for (int i = 0, iSize = static_cast<int>(laneX.size()) - 1; i < iSize; ++i) {
			if (laneX.at(i) < mouseX && mouseX < laneX.at(i + 1)) {
				p_noteManager->setSlideNote(barID, beatID, i, static_cast<double>(mouseX), true, true);
				clickObserver = true;
				barIDForChangeQuontize = barID;
				barIDColor = GetColor(36, 216, 236);
				break;
			}
		}
	}
	if (clickObserver && p_mouseCheck->isMouseClickLeftUp(mouseX, mouseY)) {
		for (int i = 0, iSize = static_cast<int>(laneX.size()) - 1; i < iSize; ++i) {
			if (laneX.at(i) < mouseX && mouseX < laneX.at(i + 1)) {
				p_noteManager->setSlideNote(NULL, NULL, i, static_cast<double>(mouseX), false, true);
				clickObserver = false;
				break;
			}
		}
	}
}

void Make::Draw::Make_Draw_LineContainer::setNoteSlideL() {
	if (!clickObserver && p_mouseCheck->isMouseClickLeftDown(mouseX, mouseY) && checkClickBorder()) {
		for (int i = 0, iSize = static_cast<int>(laneX.size()) - 1; i < iSize; ++i) {
			if (laneX.at(i) < mouseX && mouseX < laneX.at(i + 1)) {
				p_noteManager->setSlideNote(barID, beatID, i, static_cast<double>(mouseX), true, false);
				clickObserver = true;
				barIDForChangeQuontize = barID;
				barIDColor = GetColor(36, 216, 236);
				break;
			}
		}
	}
	if (clickObserver && p_mouseCheck->isMouseClickLeftUp(mouseX, mouseY)) {
		for (int i = 0, iSize = static_cast<int>(laneX.size()) - 1; i < iSize; ++i) {
			if (laneX.at(i) < mouseX && mouseX < laneX.at(i + 1)) {
				p_noteManager->setSlideNote(NULL, NULL, i, static_cast<double>(mouseX), false, false);
				clickObserver = false;
				break;
			}
		}
	}
}

void Make::Draw::Make_Draw_LineContainer::setNoteType(std::uint16_t type)  {
	noteType = type;
}

void Make::Draw::Make_Draw_LineContainer::setYMin(const double y) {
	yMin = y;
}

void Make::Draw::Make_Draw_LineContainer::updateY(const double upY) {
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


void Make::Draw::Make_Draw_LineContainer::updateYMax(const double y) {
	yMax += y;
}

void Make::Draw::Make_Draw_LineContainer::updateByInitOneBar(const double yWidth) {
	y += yWidth;
	yMin += yWidth;
	updateYMax(yWidth);
}

bool Make::Draw::Make_Draw_LineContainer::checkClickBorder() {
	if (std::abs(mouseY - y) <= Global::g_clickWidth) {
		return true;
	}
	return false;
}


double Make::Draw::Make_Draw_LineContainer::getTime() {
	return time;
}


double Make::Draw::Make_Draw_LineContainer::getY() {
	return y;
}

double Make::Draw::Make_Draw_LineContainer::getYMin() {
	return yMin;
}

double Make::Draw::Make_Draw_LineContainer::getYMax() {
	return yMax;
}
