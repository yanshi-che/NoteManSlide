#pragma once

#include <memory>
#include "Game_Task.h"
#include "Game_Draw_MenuDraw.h"
#include "Game_Singleton_RaneDraw.h"
#include "Game_Singleton_BeatLineManager.h"

namespace Game {

    class Game_DrawManager : public Game_Task
    {
    private:
        Draw::Game_Draw_MenuDraw menu;
        Singleton::Game_Singleton_RaneDraw* rane;
        Singleton::Game_Singleton_BeatLineManager* beatLine;
    public:
        Game_DrawManager();
        void initialize() override;//初期化
        void finalize() override;//終了処理
        void update() override;//更新
        void draw() override;//描画

    };

}

inline void Game::Game_DrawManager::draw() {
    beatLine->draw();
    rane->draw();
}