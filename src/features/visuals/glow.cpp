#include "glow.h"
#include <globals.h>

#include <game_sdk/interfaces/materialsystem/i_mat_render_context.h>

#define FULL_FRAME_TEXTURE "_rt_FullFrameFB"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"

void CGlowSystem::add_object(CGlowObject obj)
{
	if (obj.valid())
		this->glow_objects.push_back(obj);
}

void CGlowSystem::render()
{
	auto view_setup = globals->view;
	
	auto render_context = Interfaces->material_system->GetRenderContext();

	render_context->PushRenderTargetAndViewport();

	Vector orig_color;
	Interfaces->render_view->GetColorModulation(orig_color.Base());
	float orig_blend = Interfaces->render_view->GetBlend();

	auto full_frame_texture = Interfaces->material_system->FindTexture(FULL_FRAME_TEXTURE, TEXTURE_GROUP_RENDER_TARGET);
	
	for (auto i : glow_objects)
	{
		
	}

	glow_objects.clear();
}
