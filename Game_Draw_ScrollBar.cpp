#include "Game_Draw_ScrollBar.h"

Game::Draw::Game_Draw_ScrollBar::Game_Draw_ScrollBar(float scrollWidth, std::vector<std::vector<std::shared_ptr<Game_Draw_LineContainer>>>& barVec, float& yMagnificationByMouseWheel) :
	barVec(barVec), yMagnificationByMouseWheel(yMagnificationByMouseWheel) {
	mouseX = 0;
	mouseY = 0;
	widthMaxOnClick = 0;
	widthMinOnClick = 0;
	barYBefore = 0;
	p_mouseCheck = Singleton::Game_Singleton_MouseOperationCheck::getInstance();
	scrollWidthRate = (Global::WINDOW_HEIGHT - backWidth * 2.0f - barHeightMin) / scrollWidth;
	barHeight = (Global::WINDOW_HEIGHT - backWidth * 2.0f) * scrollWidthRate + barHeightMin;
	y = Global::WINDOW_HEIGHT - (barHeight + backWidth);
	clickObserver = false;
	function = nullptr;
	backColor = GetColor(102, 102, 102);
	barColor = GetColor(179, 179, 179);
	arrowUpColor = GetColor(179, 179, 179);
	arrowDownColor = GetColor(179, 179, 179);
	barPointX[0] = Global::WINDOW_WIDTH - backWidth + (backWidth - barWidth) * 0.5f;
	barPointX[1] = Global::WINDOW_WIDTH - (backWidth - barWidth) * 0.5f;
	arrowPointX[0] = Global::WINDOW_WIDTH - arrowWidthX - arrowWidthYAndSpace;//ç∂ë§
	arrowPointX[1] = Global::WINDOW_WIDTH - arrowWidthX * 0.5 - arrowWidthYAndSpace;//ê^ÇÒíÜ
	arrowPointX[2] = Global::WINDOW_WIDTH - arrowWidthYAndSpace;//âEë§
	arrowPointY[0] = Global::WINDOW_HEIGHT - arrowWidthX - arrowWidthYAndSpace;//â∫ñÓàÛÇÃíÍï”
	arrowPointY[1] = arrowWidthX;//è„ñÓàÛÇÃíÍï”
	arrowPointY[2] = Global::WINDOW_HEIGHT - arrowWidthX;//â∫ñÓàÛÇÃï˚å¸
	arrowPointY[3] = arrowWidthYAndSpace;//è„ñÓàÛÇÃï˚å¸
}

void Game::Draw::Game_Draw_ScrollBar::arrowFunction(bool isUp) {
	if (Global::WINDOW_WIDTH - backWidth < mouseX && mouseX < Global::WINDOW_WIDTH) {
		if (isUp && 0 < mouseY && mouseY < backWidth) {
			updateBarY(yMagnificationByMouseWheel);
			updateLineContainerY(yMagnificationByMouseWheel);
		}
		else if(Global::WINDOW_HEIGHT - backWidth < mouseY && mouseY < Global::WINDOW_HEIGHT){
			updateBarY(-yMagnificationByMouseWheel);
			updateLineContainerY(-yMagnificationByMouseWheel);
		}
	}
}

void Game::Draw::Game_Draw_ScrollBar::barFunction() {
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) &&
		backWidth + widthMinOnClick < mouseY && mouseY < Global::WINDOW_HEIGHT - backWidth - widthMaxOnClick) {
		barYBefore = y;
		setBarY(static_cast<float>(mouseY) - widthMinOnClick);
		updateLineContainerY((barYBefore - y) / scrollWidthRate);
	}
}

void Game::Draw::Game_Draw_ScrollBar::borderCheck() {
	if (!clickObserver) {
		GetMousePoint(&mouseX, &mouseY);
		if (barPointX[0] < mouseX && mouseX < barPointX[1] &&
			y < mouseY && mouseY < y + barHeight) {
			barColor = GetColor(219, 219, 219);
		}
		else {
			barColor = GetColor(179, 179, 179);
		}
		if (Global::WINDOW_WIDTH - backWidth < mouseX && mouseX < Global::WINDOW_WIDTH) {
			if (yScrMax < mouseY && mouseY < Global::WINDOW_HEIGHT) {
				arrowDownColor = GetColor(79, 200, 225);
			}
			else {
				arrowDownColor = GetColor(179, 179, 179);
			}
			if (0 < mouseY && mouseY < yScrMin) {
				arrowUpColor = GetColor(79, 200, 225);
			}
			else {
				arrowUpColor = GetColor(179, 179, 179);
			}
		}
		else {
			arrowDownColor = GetColor(179, 179, 179);
			arrowUpColor = GetColor(179, 179, 179);
		}
	}
}

void Game::Draw::Game_Draw_ScrollBar::clickCheck() {
	if (!clickObserver && p_mouseCheck->isMouseClickLeftDown(mouseX, mouseY)) {
		if (barPointX[0] < mouseX && mouseX < barPointX[1] &&
			y < mouseY && mouseY < y + barHeight) {
			clickObserver = true;
			barColor = GetColor(255, 255, 255);
			widthMaxOnClick = y + barHeight - mouseY;
			widthMinOnClick = mouseY - y;
			function = [&] {return barFunction(); };
		}
		else if (Global::WINDOW_WIDTH - backWidth < mouseX && mouseX < Global::WINDOW_WIDTH) {
			if (0 < mouseY && mouseY < backWidth) {
				clickObserver = true;
				arrowUpColor = GetColor(13,0,174);
				function = [&] {return arrowFunction(true); };
			}
			else if(Global::WINDOW_HEIGHT - backWidth < mouseY && mouseY < Global::WINDOW_HEIGHT){
				clickObserver = true;
				arrowDownColor = GetColor(13, 0, 174);
				function = [&] {return arrowFunction(false); };
			}
		}
	}

	if (clickObserver && function != nullptr) {
		GetMousePoint(&mouseX, &mouseY);
		function();
		if (p_mouseCheck->isMouseClickLeftUp(mouseX, mouseY)) {
			clickObserver = false;
			function = nullptr;
		}
	}
}

void Game::Draw::Game_Draw_ScrollBar::draw() {
	borderCheck();
	clickCheck();
	drawBack();
	drawBar();
	drawArrow();
}

void Game::Draw::Game_Draw_ScrollBar::drawArrow() {
	DrawTriangleAA(arrowPointX[0], arrowPointY[1], arrowPointX[1], arrowPointY[3], arrowPointX[2], arrowPointY[1], arrowUpColor, true);//è„ñÓàÛ
	DrawTriangleAA(arrowPointX[0], arrowPointY[0], arrowPointX[1], arrowPointY[2], arrowPointX[2], arrowPointY[0], arrowDownColor, true);//â∫ñÓàÛ
}

void Game::Draw::Game_Draw_ScrollBar::drawBack() {
	DrawBoxAA(Global::WINDOW_WIDTH - backWidth, 0, Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT, backColor, true);
}

void Game::Draw::Game_Draw_ScrollBar::drawBar() {
	DrawBoxAA(barPointX[0], y, barPointX[1], y + barHeight, barColor, true);
}

void Game::Draw::Game_Draw_ScrollBar::setBarY(float sY) {
	y = sY;
	if (yScrMax < y + barHeight) {
		y = yScrMax - barHeight;
	}
	else if (y < yScrMin) {
		y = yScrMin;
	}
}

void Game::Draw::Game_Draw_ScrollBar::updateLineContainerY(float y) {
	for (int i = 0, iSize = static_cast<int>(barVec.size()); i < iSize; ++i) {
		for (int k = 0, kSize = static_cast<int>(barVec[i].size()); k < kSize; ++k) {
			barVec[i][k]->updateY(y);
		}
	}
}

void Game::Draw::Game_Draw_ScrollBar::updateBarY(float upY) {
	if (0 < upY && yScrMin < y || upY < 0 && y + barHeight < yScrMax) {
		y -= upY * scrollWidthRate;
		if (yScrMax < y + barHeight) {
			y = yScrMax - barHeight;
		}
		else if (y < yScrMin) {
			y = yScrMin;
		}
	}
}
