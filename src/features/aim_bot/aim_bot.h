#pragma once
#include <game_sdk/classes/c_user_cmd.h>



class CAimBot
{
public:
	bool is_aiming = false;

	void run(CUserCmd* cmd);

	void antiaim(CUserCmd* ucmd);
}; extern CAimBot* AimBot;