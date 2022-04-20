#include "Global.h"

double Global::g_fpsDiff = 1.0;
LONGLONG Global::g_time = 0;

bool Global::g_saveFlag = true;//セーブしたかどうかのフラグ
std::uint16_t  Global::g_clickWidth = 8;//拍線に対するマウスクリックの許容幅