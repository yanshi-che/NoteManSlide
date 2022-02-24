#pragma once

#include <functional>
#include <memory>
#include "Make_Draw_MenuDraw.h"
#include "Make_Singleton_MouseOperationCheck.h"
#include "Make_Singleton_KeyHitCheck.h"


namespace Make {

    class Make_DrawManager
    {
    private:
        std::unique_ptr<Draw::Make_Draw_MenuDraw> p_menu;
        Singleton::Make_Singleton_MouseOperationCheck* p_mouseCheck;
        Singleton::Make_Singleton_KeyHitCheck* p_keyCheck;
        std::function<void()> drawFunc;
    public:
        Make_DrawManager();
        void initialize();
        void finalize();
        void update();
        void draw();

    };

}