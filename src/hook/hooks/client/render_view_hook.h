#pragma once
#include <game_sdk/interfaces/client/i_view_render.h>
#include <game_sdk/classes/c_view_setup.h>

namespace render_view_hook
{
	using fn = void(__thiscall*)(IViewRender*, CViewSetup&, int, int);
	extern void __fastcall hook(IViewRender* view_render, void* edx, CViewSetup& setup, int clear_flags, int what_to_draw);
}