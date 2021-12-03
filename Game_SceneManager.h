#pragma once

#include <memory>
#include "Game_Task.h"
#include "Game_Draw_RaneDraw.h"
#include "Game_Draw_UIDraw.h"

namespace Game {

    class Game_SceneManager : public Game_Task
    {
    private:
        Draw::Game_Draw_RaneDraw rane;
        Draw::Game_Draw_UIDraw UI;
    public:
        Game_SceneManager();
        void initialize() override;//‰Šú‰»
        void finalize() override;//I—¹ˆ—
        void update() override;//XV
        void draw() override;//•`‰æ

    };

}