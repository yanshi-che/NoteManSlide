#include "Make_Global.h"

//ユーザー定義
 double Make::Global::g_hiSpeed = 0.3;
 double Make::Global::g_judgeCorrection = 0.0;
 std::uint16_t Make::Global::g_lane0 = KEY_INPUT_D;
 std::uint16_t Make::Global::g_lane1 = KEY_INPUT_F;
 std::uint16_t Make::Global::g_lane2 = KEY_INPUT_G;
 std::uint16_t Make::Global::g_lane3 = KEY_INPUT_H;
 std::uint16_t Make::Global::g_lane4 = KEY_INPUT_J;
 std::uint16_t Make::Global::g_lane5 = KEY_INPUT_K;
 std::uint16_t Make::Global::g_laneRR = KEY_INPUT_U;
 std::uint16_t Make::Global::g_laneRL = KEY_INPUT_I;
 std::uint16_t Make::Global::g_laneLR = KEY_INPUT_T;
 std::uint16_t Make::Global::g_laneLL = KEY_INPUT_R;
//ボルテコン
 std::uint16_t Make::Global::g_PAD_ID = DX_INPUT_PAD1;
 std::uint16_t Make::Global::g_BT_A = PAD_INPUT_1;
 std::uint16_t Make::Global::g_BT_B = PAD_INPUT_2;
 std::uint16_t Make::Global::g_BT_C = PAD_INPUT_3;
 std::uint16_t Make::Global::g_BT_D = PAD_INPUT_4;
 std::uint16_t Make::Global::g_FX_L = PAD_INPUT_5;
 std::uint16_t Make::Global::g_FX_R = PAD_INPUT_6;
 std::uint16_t Make::Global::g_VOL_R1 = PAD_INPUT_DOWN;
 std::uint16_t Make::Global::g_VOL_R2 = PAD_INPUT_UP;
 std::uint16_t Make::Global::g_VOL_L1 = PAD_INPUT_LEFT;
 std::uint16_t Make::Global::g_VOL_L2 = PAD_INPUT_RIGHT;
 std::uint16_t Make::Global::g_B_START = PAD_INPUT_9;
//
 bool Make::Global::g_saveFlag = true;//セーブしたかどうかのフラグ
 std::uint8_t  Make::Global::g_clickWidth = 8;//拍線に対するマウスクリックの許容幅