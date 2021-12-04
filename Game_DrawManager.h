#pragma once

#include <memory>
#include "Game_Task.h"
#include "Game_Draw_DrawFactory.h"
#include "Game_Draw_MenuDraw.h"
#include "Game_Draw_RaneDraw.h"
#include "Game_Draw_BeatLineDraw.h"

namespace Game {

    class Game_DrawManager : public Game_Task
    {
    private:
        Draw::Game_Draw_DrawFactory drawFactory;
        Draw::Game_Draw_MenuDraw menu;
        Draw::Game_Draw_RaneDraw* rane;
        Draw::Game_Draw_BeatLineDraw* beatLine;
    public:
        Game_DrawManager();
        void initialize() override;//初期化
        void finalize() override;//終了処理
        void update() override;//更新
        void draw() override;//描画

    };

}