#include "misc.h"


#include "globals.h"
#include "game_sdk/entitys/c_base_player.h"

#define	FL_ONGROUND				(1<<0)

Misc* misc = new Misc();

void Misc::bhop(CUserCmd* cmd)
{
    if (!settings::Misc->bhop_enable)
        return;

    CBasePlayer* local_player = CBasePlayer::get_local_player();
    static bool last_jumped = false, should_fake = false;

    if (!local_player || !local_player->is_alive())
        return;

    if (local_player->get_move_type() == MOVETYPE_LADDER)
        return;

    if (!last_jumped && should_fake)
    {
        should_fake = false;
        cmd->buttons |= IN_JUMP;
    }
    else if (cmd->buttons & IN_JUMP)
    {
        if (local_player->get_flags() & FL_ONGROUND)
        {
            last_jumped = true;
            should_fake = true;
        }
        else
        {
            cmd->buttons &= ~IN_JUMP;
            last_jumped = false;
        }
    }
    else
    {
        last_jumped = false;
        should_fake = false;
    }
}


void Misc::legit_strafe(CUserCmd* cmd)
{
    if (!settings::Misc->auto_strafe_enable)
        return;

    CBasePlayer* local_player = CBasePlayer::get_local_player();

    if (!local_player || !local_player->is_alive())
        return;

    if (local_player->get_move_type() == MOVETYPE_LADDER)
        return;

    if (!(cmd->buttons & IN_JUMP) || !(local_player->get_flags() & FL_ONGROUND))
        return;

    Vector view_angles;
    Interfaces->engine->get_view_angles(view_angles);

    static bool side_switch = false;
    side_switch = !side_switch;

    cmd->forwardmove = 0.f;
    cmd->sidemove = side_switch ? 450.f : -450.f;

    float velocity_yaw = local_player->get_velocity().y;

    float rotation = Math->fclamp< float >(RAD2DEG(std::atan2(15.f, local_player->get_velocity().Length2D())), 0.f, 90.f);

    float abs_yaw = std::fabs(normalize_angel(velocity_yaw - view_angles.y));

    float ideal_yaw_rotation = (side_switch ? rotation : -rotation) + (abs_yaw < 5.f ? velocity_yaw : view_angles.y);

    float cos_rot = std::cos(DEG2RAD(view_angles.y - ideal_yaw_rotation));
    float sin_rot = std::sin(DEG2RAD(view_angles.y - ideal_yaw_rotation));

    cmd->forwardmove = (cos_rot * cmd->forwardmove) - (sin_rot * cmd->sidemove);
    cmd->sidemove = (sin_rot * cmd->forwardmove) + (cos_rot * cmd->sidemove);
}
