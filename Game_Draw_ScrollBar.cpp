#include "Game_Draw_ScrollBar.h"

Game::Draw::Game_Draw_ScrollBar::Game_Draw_ScrollBar(float scrollWidth, std::vector<std::vector<std::shared_ptr<Game_Draw_LineContainer>>>& barVec, float& yMagnificationByMouseWheel) :
barVec(barVec),yMagnificationByMouseWheel(yMagnificationByMouseWheel){
	scrollWidthRate = (Global::WINDOW_HEIGHT - backWidth * 2.0f) / scrollWidth;
	barHeight = (Global::WINDOW_HEIGHT - backWidth * 2.0f) * scrollWidthRate;
	y = Global::WINDOW_HEIGHT - (barHeight + backWidth);
	clickObserver = false;
	backColor = GetColor(102, 102, 102);
	barColor = GetColor(179, 179, 179);
	barPointX[0] = Global::WINDOW_WIDTH - backWidth + (backWidth - barWidth) * 0.5f;
	barPointX[1] = Global::WINDOW_WIDTH - (backWidth - barWidth) * 0.5f;
	arrowPointX[0] = Global::WINDOW_WIDTH - arrowWidthX - arrowWidthYAndSpace;//ç∂ë§
	arrowPointX[1] = Global::WINDOW_WIDTH - arrowWidthX * 0.5 - arrowWidthYAndSpace;//ê^ÇÒíÜ
	arrowPointX[2] = Global::WINDOW_WIDTH - arrowWidthYAndSpace;//âEë§
	arrowPointY[0] = Global::WINDOW_HEIGHT - arrowWidthX - arrowWidthYAndSpace;//â∫ñÓàÛÇÃíÍï”
	arrowPointY[1] = arrowWidthX + arrowWidthYAndSpace;//è„ñÓàÛÇÃíÍï”
	arrowPointY[2] = Global::WINDOW_HEIGHT - arrowWidthX;//â∫ñÓàÛÇÃï˚å¸
	arrowPointY[3] = arrowWidthYAndSpace;//è„ñÓàÛÇÃï˚å¸
}

void Game::Draw::Game_Draw_ScrollBar::drawBack() {
	DrawBoxAA(Global::WINDOW_WIDTH - backWidth, 0, Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT, backColor, true);
}

void Game::Draw::Game_Draw_ScrollBar::drawArrow() {
	DrawTriangleAA(arrowPointX[0],arrowPointY[1],arrowPointX[1],arrowPointY[3],arrowPointX[2],arrowPointY[1],barColor,true);//è„ñÓàÛ
	DrawTriangleAA(arrowPointX[0], arrowPointY[0], arrowPointX[1], arrowPointY[2], arrowPointX[2], arrowPointY[0], barColor, true);//â∫ñÓàÛ
}

void Game::Draw::Game_Draw_ScrollBar::drawBar() {
	DrawBoxAA(barPointX[0], y, barPointX[1], y + barHeight, barColor, true);
}

void Game::Draw::Game_Draw_ScrollBar::clickChecker() {

}

void Game::Draw::Game_Draw_ScrollBar::updateLineContainerY(float y) {

}

void Game::Draw::Game_Draw_ScrollBar::updateBarY(float upY) {
	if (0 < upY && yScrMin < y || upY < 0 && y + barHeight < yScrMax) {
		y -= upY * scrollWidthRate;
		if (yScrMax < y + barHeight) {
			y = yScrMax - barHeight;
		}
		else if(y < yScrMin){
			y = yScrMin;
		}
	}
}

void Game::Draw::Game_Draw_ScrollBar::draw() {
	drawBack();
	drawBar();
	drawArrow();
}