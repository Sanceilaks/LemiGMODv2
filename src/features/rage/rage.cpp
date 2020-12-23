#include "rage.h"

#include "globals.h"

Rage* rage = new Rage();


void Rage::handle(CUserCmd* cmd)
{
	if (!Interfaces->engine->is_in_game() || !settings::Rage->rage_enable)
		return;


	QAngle ang;
	CBasePlayer* ply = get_closest(ang, cmd);

	if (!ply)
		return;

	cmd->viewangles = ang;

	/*if (settings::AimBot->auto_fire) */cmd->buttons |= IN_ATTACK;

	if (!settings::Rage->silent)
		Interfaces->engine->set_view_angles(ang);
}



CBasePlayer* Rage::get_closest(QAngle& out_angle, CUserCmd* cmd)
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

			float fov = Math->get_fov(cmd->viewangles, aim_ang);

			if (!ent->is_visible_by(local_player))
				continue;

			//if (fov > settings::AimBot->fov)
				//continue;


			if (fov < bestfov)
			{
				bestfov = fov;
				best_angel = aim_ang;
				best_entity = ent;
			}
		}

		out_angle = best_angel;
		return best_entity;
}
