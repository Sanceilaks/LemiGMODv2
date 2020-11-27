#include "create_move_hook.h"
#include <hook/hooks_manager.h>
#include <game_sdk/entitys/c_base_player.h>
#include <globals.h>
#include <math/qangle.h>
#include <features/aim_bot/aim_bot.h>
#include <features/rage/rage.h>

#include <features/misc/move.h>
#include <features/misc/misc.h>

#include <interfaces.h>


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

    misc->bhop(ucmd);
    misc->legit_strafe(ucmd);   //Only one type
	
    AimBot->run(ucmd);
    rage->handle(ucmd);
	
    AimBot->antiaim(ucmd);
    
	
    normalize_angles(ucmd->viewangles);
    ucmd->viewangles.Clamp();

    move::fix_movement(ucmd, old_cmd);
    
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
    if (settings::Rage->rage_enable || settings::Rage->silent) return !settings::Rage->silent;
	
    return false;
}
