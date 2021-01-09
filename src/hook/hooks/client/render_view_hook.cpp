#include "render_view_hook.h"
#include <interfaces.h>
#include <hook/hooks_manager.h>
#include <iostream>
#include <globals.h>

void __fastcall render_view_hook::hook(IViewRender* view_render, void* edx, CViewSetup& setup, int clear_flags, int what_to_draw)
{

	globals->view = setup;

	return HooksManager->render_view_original(view_render, setup, clear_flags, what_to_draw);
}
