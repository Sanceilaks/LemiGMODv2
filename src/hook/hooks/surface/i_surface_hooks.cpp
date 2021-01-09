#include "i_surface_hooks.h"
#include <features/menu/menu.h>
#include <interfaces.h>
#include <hook/hooks_manager.h>

void __stdcall i_surface_hooks::lock_cursor_hook::hook()
{
	if (menu->is_open)
		Interfaces->surface->unlock_cursor();
	else
		HooksManager->lock_cursor_original(Interfaces->surface);
}
