#pragma once

#include <cstdint>

#include "dxlib/DxLib.h"

namespace Config{
	//ユーザー定義
	extern double g_hiSpeed;
	extern double g_judgeCorrection;
	extern std::uint16_t g_lane0;
	extern std::uint16_t g_lane1;
	extern std::uint16_t g_lane2;
	extern std::uint16_t g_lane3;
	extern std::uint16_t g_lane4;
	extern std::uint16_t g_lane5;
	extern std::uint16_t g_laneRR;
	extern std::uint16_t g_laneRL;
	extern std::uint16_t g_laneLR;
	extern std::uint16_t g_laneLL;
	//ボルテコン
	extern std::uint16_t g_PAD_ID;
	extern std::uint16_t g_BT_A;
	extern std::uint16_t g_BT_B;
	extern std::uint16_t g_BT_C;
	extern std::uint16_t g_BT_D;
	extern std::uint16_t g_FX_L;
	extern std::uint16_t g_FX_R;
	extern std::uint16_t g_VOL_R1;
	extern std::uint16_t g_VOL_R2;
	extern std::uint16_t g_VOL_L1;
	extern std::uint16_t g_VOL_L2;
	extern std::uint16_t g_B_START;
}

