#include "move.h"
#include <game_sdk/entitys/c_base_entity.h>
#include "game_sdk/entitys/c_base_player.h"

void move::fix_movement(CUserCmd* cmd, CUserCmd old_cmd)
{
    CBasePlayer* local_player = CBasePlayer::get_local_player();

    if (!local_player || !local_player->is_alive())
        return;

    if (local_player->get_move_type() == MOVETYPE_LADDER)
        return;

    float f1, f2, yaw_delta = cmd->viewangles.y - old_cmd.viewangles.y;
    if (old_cmd.viewangles.y < 0.f)
        f1 = 360.0f + old_cmd.viewangles.y;
    else
        f1 = old_cmd.viewangles.y;

    if (cmd->viewangles.y < 0.0f)
        f2 = 360.0f + cmd->viewangles.y;
    else
        f2 = cmd->viewangles.y;

    if (f2 < f1)
        yaw_delta = abs(f2 - f1);
    else
        yaw_delta = 360.0f - abs(f1 - f2);

    yaw_delta = 360.0f - yaw_delta;

    cmd->forwardmove = cos(DEG2RAD(yaw_delta)) * old_cmd.forwardmove + cos(DEG2RAD(yaw_delta + 90.f)) * old_cmd.sidemove;
    cmd->sidemove = sin(DEG2RAD(yaw_delta)) * old_cmd.forwardmove + sin(DEG2RAD(yaw_delta + 90.f)) * old_cmd.sidemove;

    cmd->buttons &= ~IN_MOVERIGHT;
    cmd->buttons &= ~IN_MOVELEFT;
    cmd->buttons &= ~IN_FORWARD;
    cmd->buttons &= ~IN_BACK;
}
