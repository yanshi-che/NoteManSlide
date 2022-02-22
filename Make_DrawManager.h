#pragma once

#include <memory>
#include "Make_Task.h"
#include "Make_Draw_MenuDraw.h"
#include "Make_Draw_BeatLineManager.h"
#include "Make_Singleton_MouseOperationCheck.h"

namespace Make {

    class Make_DrawManager : public Make_Task
    {
    private:
        std::unique_ptr<Draw::Make_Draw_MenuDraw> p_menu;
        Singleton::Make_Singleton_MouseOperationCheck* p_mouseCheck;
        std::shared_ptr<Draw::Make_Draw_BeatLineManager> p_beatLine;
    public:
        Make_DrawManager();
        void initialize() override;//‰Šú‰»
        void finalize() override;//I—¹ˆ—
        void update() override;//XV
        void draw() override;//•`‰æ

    };

}