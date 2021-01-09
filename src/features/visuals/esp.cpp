#include "esp.h"
#include <game_sdk/entitys/c_base_player.h>
#include <math/math.h>
#include <tools/render_tool.h>
#include <globals.h>
#include <features/aim_bot/aim_bot.h>


CESP* ESP = new CESP();

bool get_player_box(CBasePlayer* ent, Box& box_in)
{
	Vector origin, min, max, flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;

	origin = ent->get_render_origin();
	min = ent->collideable()->mins() + origin;
	max = ent->collideable()->maxs() + origin;

	Vector points[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	if (!Math->world_to_screen(points[3], flb) || !Math->world_to_screen(points[5], brt)
		|| !Math->world_to_screen(points[0], blb) || !Math->world_to_screen(points[4], frt)
		|| !Math->world_to_screen(points[2], frb) || !Math->world_to_screen(points[1], brb)
		|| !Math->world_to_screen(points[6], blt) || !Math->world_to_screen(points[7], flt))
		return false;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	if (left < 0 || top < 0 || right < 0 || bottom < 0)
		return false;

	for (int i = 1; i < 8; i++) {
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	box_in.x = left;
	box_in.y = top;
	box_in.w = right - left;
	box_in.h = bottom - top;
	
	return true;
}

void draw_name(CBasePlayer* ply)
{
	if (!settings::esp->draw_name)
		return;

	Box box;

	if (!get_player_box(ply, box))
		return;

	std::string name = ply->get_name();

	int w, h;
	Interfaces->surface->get_text_size(settings::esp->esp_font.at(0), get_wc_t(name.c_str()), w, h);

	if (!settings::esp->is_team_name_color)
		render_tool->draw_text(box.x + box.w * 0.5, box.y + box.h, settings::esp->esp_font.at(0), name, true, Color(settings::esp->visible_name_color));
	else
		render_tool->draw_text(box.x + box.w * 0.5, box.y + box.h, settings::esp->esp_font.at(0), name, true, ply->get_team_color());
}

void draw_box(CBasePlayer* ply)
{
	Box box;

	if (!get_player_box(ply, box))
		return;

	auto color = settings::esp->is_team_color ? ply->get_team_color() : Color(settings::esp->visible_color);

	render_tool->draw_bordered_box(box.x - 1, box.y - 1, box.w + 2, box.h + 2, 2, Color(0, 0, 0));
	render_tool->draw_bordered_box(box.x + 1, box.y + 1, box.w - 2, box.h - 2, 2, Color(0, 0, 0));
	
	render_tool->draw_bordered_box(box.x, box.y, box.w, box.h, 2, color);
}

void CESP::draw()
{
	//ender_tool->begin();

	if (!Interfaces->engine->is_in_game() || !settings::esp->box_enable)
	{
		//render_tool->end();
		return;
	}

	CBasePlayer* local_player = CBasePlayer::get_local_player();

	if (!local_player)
	{
		//render_tool->end();
		return;
	}

	for (size_t i = 1; i <= Interfaces->entity_list->get_highest_enetity_index(); ++i)
	{
		CBasePlayer* ply = (CBasePlayer*)CBasePlayer::get_by_index(i);
		
		if (!ply)
			continue;

		bool is_alive = ply->is_alive();
		bool equallp = ply == local_player;
		bool is_dormant = ply->is_dormant();

		if (!is_alive || equallp || is_dormant)
			continue;


		if (!ply->is_player())
			continue;
		
		draw_box(ply);
		draw_name(ply);

		if (AimBot->target)
		{
			auto target = (CBasePlayer*)AimBot->target;
			if (target->is_player() && target->is_alive() && !target->is_dormant())
			{
				auto bone = target->get_entity_bone(ECSPlayerBones::head_0);
				Vector screen_bone;
				if (Math->world_to_screen(bone, screen_bone))
				{
					if (AimBot->is_aiming)
					{
						render_tool->draw_line(globals->screen_width * 0.5f, globals->screen_height, screen_bone.x, screen_bone.y, Color(0, 255, 0));

						int w, h;
						Interfaces->surface->get_text_size(settings::esp->esp_font.at(0), get_wc_t(target->get_name().c_str()), w, h);
						
						render_tool->draw_text(w + 20, globals->screen_height - 20 - h, settings::esp->esp_font.at(0), target->get_name(), true, Color(0, 255, 0));
					}
				}
			}
		}
	}

	//render_tool->end();
}
