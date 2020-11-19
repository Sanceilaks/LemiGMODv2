#pragma once
#include <game_sdk/interfaces/client/v_client.h>
#include <math/math.h>

namespace view_render_hook
{
	using fn = void(__thiscall*)(VClient*, vrect_t* rect);
	extern void __fastcall hook(VClient* client, void* edx, vrect_t* rect);
}