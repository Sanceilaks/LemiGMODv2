#include "aim_bot.h"
#include <game_sdk/entitys/c_base_player.h>
#include <math/qangle.h>
#include <globals.h>

CAimBot* AimBot = new CAimBot();

CBasePlayer* get_closest_player(QAngle& in_best_angel, CUserCmd* ucmd)
{
	CBasePlayer* local_player = CBasePlayer::get_local_player();

	if (!local_player)
		return nullptr;

	float bestfov = 360.f;
	QAngle best_angel = QAngle(0, 0, 0);
	CBasePlayer* best_entity = nullptr;


	for (int i = 0; i <= Interfaces->entity_list->get_highest_enetity_index(); ++i)
	{
		CBasePlayer* ent = (CBasePlayer*)CBasePlayer::get_by_index(i);

		if (!ent)
			continue;

		if (ent == local_player || !ent->is_player() || !ent->is_alive())
			continue;

		auto hit_pos = ent->get_entity_bone(ECSPlayerBones::head_0);

		QAngle aim_ang = CalcAngle(local_player->get_eye_pos(), hit_pos);

		float fov = Math->get_fov(ucmd->viewangles, aim_ang);

		if (settings::AimBot->only_visible && !ent->is_visible_by(local_player))
			continue;

		if (fov > settings::AimBot->fov)
			continue;


		if (fov < bestfov)
		{
			bestfov = fov;
			best_angel = aim_ang;
			best_entity = ent;
		}
	}

	in_best_angel = best_angel;
	return best_entity;
}


void CAimBot::run(CUserCmd* cmd)
{
	if (!Interfaces->engine->is_in_game() || !settings::AimBot->aim_enable)
		return;
	

	QAngle ang;
	CBasePlayer* ply = get_closest_player(ang, cmd);

	if (!ply)
		return;

	if (GetAsyncKeyState(settings::AimBot->aimkey) || settings::AimBot->aimkey == 0)
	{
		cmd->viewangles = ang;

		if (settings::AimBot->auto_fire) cmd->buttons |= IN_ATTACK;

		if (!settings::AimBot->silent)
			Interfaces->engine->set_view_angles(ang);

		//if (settings::AimBot->auto_fire) cmd->buttons &= ~IN_ATTACK;

		is_aiming = true;
	}
	else
	{
		is_aiming = false;
	}

}

void CAimBot::antiaim(CUserCmd* ucmd)
{
	if (!settings::AimBot->anti_aim_enable)
		return;

	if (ucmd->buttons & IN_ATTACK || ucmd->buttons & IN_USE)
		return;

	if (settings::AimBot->anti_aim_type == settings::AntiAimType::yaw)
	{
		ucmd->viewangles.x = 89;
		ucmd->viewangles.y += 180;
	}
	else if (settings::AimBot->anti_aim_type == settings::AntiAimType::jitter)
	{
		static bool switcher = false;
		if (switcher)
			ucmd->viewangles -= 218;
		else
			ucmd->viewangles -= 10;
		switcher = !switcher;

		ucmd->viewangles -= 90;
	}
	else if (settings::AimBot->anti_aim_type == settings::AntiAimType::forward)
	{
		ucmd->viewangles.x = 89.f;
		ucmd->viewangles.y *= -1.f;
		ucmd->viewangles.z = 0.f;
		ucmd->viewangles.Clamp();
	}
}
