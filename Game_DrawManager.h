#pragma once

#include <memory>
#include "Game_Task.h"
#include "Game_Draw_MenuDraw.h"
#include "Game_Singleton_LaneDraw.h"
#include "Game_Singleton_BeatLineManager.h"
#include "Game_Singleton_MouseOperationCheck.h"

namespace Game {

    class Game_DrawManager : public Game_Task
    {
    private:
        Draw::Game_Draw_MenuDraw menu;
        Singleton::Game_Singleton_MouseOperationCheck* p_mouseCheck;
        Singleton::Game_Singleton_LaneDraw* p_lane;
        Singleton::Game_Singleton_BeatLineManager* p_beatLine;
    public:
        Game_DrawManager();
        void initialize() override;//‰Šú‰»
        void finalize() override;//I—¹ˆ—
        void update() override;//XV
        void draw() override;//•`‰æ

    };

}