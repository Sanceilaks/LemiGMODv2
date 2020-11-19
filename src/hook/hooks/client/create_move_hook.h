#pragma once
#include <game_sdk/interfaces/client/i_client_mode.h>

namespace create_move_hook
{
	using fn = bool(__thiscall*)(IClientMode*, float, CUserCmd* ucmd);
	extern bool __stdcall hook(float frame_time, CUserCmd* ucmd);
}