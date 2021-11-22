#pragma once

#include <memory>
#include "Game_Task.h"
#include "Game_Draw_RaneDraw.h"
#include "Game_Draw_UIDraw.h"

namespace Game {

    class Game_SceneManager : public Game_Task
    {
    private:
        Game::Draw::Game_Draw_RaneDraw rane;
        Game::Draw::Game_Draw_UIDraw UI;
        //std::unique_ptr<BaseDraw> beat;
    public:
        Game_SceneManager();
        void initialize() override;//初期化
        void finalize() override;//終了処理
        void update() override;//更新
        void draw() override;//描画

    };

}