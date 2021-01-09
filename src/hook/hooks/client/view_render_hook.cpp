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

void Halo_add(std::vector<IClientEntity*>& ents, ImVec4 color, float blurX, float blurY, int passes, bool additive, bool ignoreZ) {

	if (!ents.size())
		return;
	auto g_pILuaShitInterface = Interfaces->lua_shared->get_interface(LUA::Type::client);
	if (!g_pILuaShitInterface)
		return;
	g_pILuaShitInterface->CreateTable();
	g_pILuaShitInterface->PushString("r");
	g_pILuaShitInterface->PushNumber(color.x * 255);
	g_pILuaShitInterface->SetTable(-3);
	g_pILuaShitInterface->PushString("g");
	g_pILuaShitInterface->PushNumber(color.y * 255);
	g_pILuaShitInterface->SetTable(-3);
	g_pILuaShitInterface->PushString("b");
	g_pILuaShitInterface->PushNumber(color.z * 255);
	g_pILuaShitInterface->SetTable(-3);
	g_pILuaShitInterface->PushString("a");
	g_pILuaShitInterface->PushNumber(color.w * 255);
	g_pILuaShitInterface->SetTable(-3);
	g_pILuaShitInterface->PushBool(ignoreZ);
	g_pILuaShitInterface->PushBool(additive);
	g_pILuaShitInterface->PushNumber(passes);
	g_pILuaShitInterface->PushNumber(blurY);
	g_pILuaShitInterface->PushNumber(blurX);
	g_pILuaShitInterface->CreateTable();
	g_pILuaShitInterface->PushSpecial((int)LUA::Special::glob);
	for (auto it : ents) {
		g_pILuaShitInterface->GetField(-1, "Entity");
		g_pILuaShitInterface->PushNumber(it->get_index());
		g_pILuaShitInterface->Call(1, 1);
		g_pILuaShitInterface->PushSpecial((int)LUA::Special::glob);
		g_pILuaShitInterface->GetField(-1, "table");
		g_pILuaShitInterface->GetField(-1, "insert");
		g_pILuaShitInterface->Push(-6);
		g_pILuaShitInterface->Push(-5);
		g_pILuaShitInterface->Call(2, 0);
		g_pILuaShitInterface->Pop(3);
	}
	g_pILuaShitInterface->Pop(1);
	g_pILuaShitInterface->PushSpecial((int)LUA::Special::glob);
	g_pILuaShitInterface->GetField(-1, "halo");
	g_pILuaShitInterface->GetField(-1, "Add");
	g_pILuaShitInterface->Push(-4);
	g_pILuaShitInterface->Push(-11);
	g_pILuaShitInterface->Push(-7);
	g_pILuaShitInterface->Push(-9);
	g_pILuaShitInterface->Push(-11);
	g_pILuaShitInterface->Push(-13);
	g_pILuaShitInterface->Push(-15);
	g_pILuaShitInterface->Call(7, 0);
	g_pILuaShitInterface->Pop(7);
	g_pILuaShitInterface->Pop(2);
}

void __fastcall view_render_hook::hook(VClient* client, void* edx, vrect_t* rect)
{
	HooksManager->view_render_original(client, rect);
	
	Interfaces->surface->start_drawing();

	ESP->draw();
	Visuals->draw_fov();

	Interfaces->surface->finish_drawing();

	Chams->draw();

	if (!globals->screen_grab)
	{
		std::vector<IClientEntity*> out;
		for (auto i = 0; i <= Interfaces->entity_list->get_highest_enetity_index(); i++)
		{
			auto ent = CBaseEntity::get_by_index(i);
			if (ent && ent->is_player() && ent->is_alive())
			{
				out.push_back(ent);
			}
		}

		Halo_add(out, ImVec4(0, 1, 0, 1), 0, 0, 3, false, true);
	}
}
