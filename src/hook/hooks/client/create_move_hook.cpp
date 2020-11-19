#include "create_move_hook.h"
#include <hook/hooks_manager.h>
#include <game_sdk/entitys/c_base_player.h>
#include <globals.h>
#include <math/qangle.h>
#include <features/aim_bot/aim_bot.h>

#include <interfaces.h>

#define	FL_ONGROUND				(1<<0)

void fix_movment(CUserCmd* cmd, CUserCmd old_cmd)
{
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


void bhop(CUserCmd* cmd)
{
    if (!settings::Misc->bhop_enable)
        return;

    CBasePlayer* local_player = CBasePlayer::get_local_player();
    static bool last_jumped = false, should_fake = false;

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

void auto_strafe(CUserCmd* cmd)
{
    if (!settings::Misc->auto_strafe_enable)
        return;

    CBasePlayer* local_player = CBasePlayer::get_local_player();

    if (!local_player || !local_player->is_alive())
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

bool __stdcall create_move_hook::hook(float frame_time, CUserCmd* ucmd)
{
    static int ChokedPackets = 0;
    ChokedPackets++;

    DWORD move;
    _asm mov move, ebp;
    bool& sendpacket = *(***(bool****)(move)-1);

    HooksManager->create_move_original(Interfaces->client_mode, frame_time, ucmd);

    if (!ucmd)
        return false;

    CBasePlayer* local_player = CBasePlayer::get_local_player();

    if (!local_player)
        return false;

    if (!local_player->is_alive())
        return false;

    const auto old_cmd = *ucmd;

    bhop(ucmd);
    auto_strafe(ucmd);
    AimBot->run(ucmd);

    AimBot->antiaim(ucmd);

    normalize_angles(ucmd->viewangles);
    ucmd->viewangles.Clamp();

    
    fix_movment(ucmd, old_cmd);
    
    //if (settings::AimBot->fake_angel)
    //{
    //    if (ChokedPackets < 1)
    //    {
    //        sendpacket = false;
    //        ucmd->viewangles += 90.0f;
    //    }
    //    else
    //    {
    //        sendpacket = true;
    //        ucmd->viewangles -= 90.0f;
    //        ChokedPackets = 0;
    //    }
    //}

    if (sendpacket)
    {
        Globals->last_angel = ucmd->viewangles;
    }

    if (AimBot->is_aiming) return !settings::AimBot->silent;

    return false;
}
