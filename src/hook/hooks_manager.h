#pragma once
#include "hooks/include_all.h"
#include <interfaces.h>

#define HOOKMANAGERINTERNAL

#ifdef HOOKMANAGERINTERNAL
#define CREATE_ORIGINAL(fn, name) fn name = nullptr;
#endif

class CHooksManager
{
public:
	CREATE_ORIGINAL(create_move_hook::fn, create_move_original);
	CREATE_ORIGINAL(end_scane_hook::fn, end_scane_original);
	CREATE_ORIGINAL(reset_hook::fn, reset_original);
	CREATE_ORIGINAL(view_render_hook::fn, view_render_original);
	CREATE_ORIGINAL(render_view_hook::fn, render_view_original);
	CREATE_ORIGINAL(i_surface_hooks::lock_cursor_hook::fn, lock_cursor_original);
	CREATE_ORIGINAL(read_pixels_hook::fn, read_pixels_original);
public:
	bool init();

	void unhook();
};

extern CHooksManager* HooksManager;

#undef HOOKMANAGERINTERNAL