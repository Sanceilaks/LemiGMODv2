#include "read_pixels_hook.h"
#include "../../hooks_manager.h"
#include <tools/mem_tools.h>
#include <globals.h>

#include <stdio.h>
#include <intrin.h>

#include <game_sdk/interfaces/materialsystem/i_mat_render_context.h>

void __fastcall read_pixels_hook::hook(IMatRenderContext* self, uintptr_t edx, int x, int y, int w, int h, uint8_t* data, int dst)
{
	CViewSetup setup;
	static uintptr_t render_capture;
	if (!render_capture)
		render_capture = (uintptr_t)(MemTools::pattern_scaner("client.dll", "FF 50 ? 6A 20 8D 4D") + 3);
	
	//checking for a call from render_capture
	if ((uintptr_t)_ReturnAddress() == render_capture)
	{
		
		globals->screen_grab = true;

		self->ClearBuffers(true, true, true);

		Interfaces->client->GetPlayerView(setup);
		Interfaces->client->RenderView(setup, (VIEW_CLEAR_COLOR | VIEW_CLEAR_DEPTH), (RENDERVIEW_DRAWVIEWMODEL | RENDERVIEW_DRAWHUD));

		globals->screen_grab = false;
	}
	
	
	return HooksManager->read_pixels_original(self, x, y, w, h, data, dst);
}
