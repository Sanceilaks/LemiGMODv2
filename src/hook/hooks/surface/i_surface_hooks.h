#pragma once
#include <game_sdk/interfaces/surface/i_surface.h>

namespace i_surface_hooks
{
	namespace lock_cursor_hook
	{
		using fn = void(__thiscall*)(ISurface*);
		extern void __stdcall hook();
	}
}