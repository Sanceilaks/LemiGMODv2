#include "view_render_hook.h"
#include <interfaces.h>
#include <hook/hooks_manager.h>
#include <globals.h>
#include <game_sdk/entitys/c_base_player.h>
#include <features/visuals/chams.h>
#include <features/visuals/esp.h>
#include <features/visuals/visuals.h>

#define TEXTURE_GROUP_MODEL							"Model textures"
#define STUDIO_RENDER					0x00000001


void __fastcall view_render_hook::hook(VClient* client, void* edx, vrect_t* rect)
{
	HooksManager->view_render_original(client, rect);

	Chams->draw();

	Interfaces->surface->start_drawing();

	ESP->draw();
	Visuals->draw_fov();

	Interfaces->surface->finish_drawing();
}
