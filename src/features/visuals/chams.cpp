#include "chams.h"
#include <interfaces.h>
#include <globals.h>
#include <features/menu/menu.h>
#include <game_sdk/entitys/c_base_player.h>

#define TEXTURE_GROUP_MODEL							"Model textures"
#define STUDIO_RENDER					0x00000001

CChams* Chams = new CChams();

void CChams::draw()
{
	if (!Interfaces->engine->is_in_game() || !settings::esp->chams_enable /*|| Menu->is_open*/)
		return;

	if (Interfaces->engine->is_taking_screenshot())
		return;

	CBasePlayer* local_player = CBasePlayer::get_local_player();

	float colormod[4] = { 1.f,1.f,1.f, 0.5f }; //models/player   models/debug/debugwhite
	IMaterial* DebugWhite = Interfaces->material_system->FindMaterial("models/debug/debugwhite", TEXTURE_GROUP_MODEL);
	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
	DebugWhite->SetMaterialVarFlag(MATERIAL_VAR_SELFILLUM, true);
	DebugWhite->AddRef();

	Interfaces->render->Push3DView(globals->view, 0, nullptr, Interfaces->view_render->GetFrustum());


	//if (settings::AimBot->fake_angel)
	//{
	//	auto last = local_player->get_angels();
	//	local_player->set_view_angels(Globals->last_angel);

	//	Interfaces->model_render->ForcedMaterialOverride(DebugWhite);
	//	Interfaces->render_view->SetColorModulation(settings::ESP->chams_color);
	//	Interfaces->render_view->SetBlend(settings::ESP->chams_color[3]);
	//	local_player->draw_model(STUDIO_RENDER);
	//	Interfaces->model_render->ForcedMaterialOverride(nullptr);

	//	local_player->set_view_angels(last);
	//}

	for (int i = 1; i <= Interfaces->engine->get_max_clients(); i++) 
	{
		CBasePlayer* player = (CBasePlayer*)CBasePlayer::get_by_index(i);

		if (!player || !player->is_player() || !player->is_alive() || player == local_player || player->is_dormant())
			continue;

		if (settings::esp->chams_type == 1)
		{
			player->draw_model(STUDIO_RENDER);
			Interfaces->model_render->ForcedMaterialOverride(nullptr);
		}
		else if (settings::esp->chams_type == 0)	//settings::ESP->chams_color
		{
			Interfaces->model_render->ForcedMaterialOverride(DebugWhite);
			Interfaces->render_view->SetColorModulation(settings::esp->chams_color);
			Interfaces->render_view->SetBlend(settings::esp->chams_color[3]);
			player->draw_model(STUDIO_RENDER);
			Interfaces->model_render->ForcedMaterialOverride(nullptr);
		}
	}
	Interfaces->render->PopView(Interfaces->view_render->GetFrustum());
}
