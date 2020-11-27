#pragma once
#include <game_sdk/classes/c_user_cmd.h>
#include <game_sdk/entitys/c_base_player.h>
#include <math/qangle.h>

class Rage
{
public:
	CBasePlayer* get_closest(QAngle& out_angle, CUserCmd* cmd);
	void handle(CUserCmd* ucmd);

	
}; extern Rage* rage;