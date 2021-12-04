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
        std::unique_ptr<Draw::Game_Draw_DrawFactory> drawFactory;
        Draw::Game_Draw_MenuDraw menu;
        Draw::Game_Draw_RaneDraw* rane;
        Draw::Game_Draw_BeatLineDraw* beatLine;
    public:
        Game_DrawManager();
        void initialize() override;//‰Šú‰»
        void finalize() override;//I—¹ˆ—
        void update() override;//XV
        void draw() override;//•`‰æ

    };

}