#pragma once
#include <game_sdk/classes/c_user_cmd.h>



class Misc
{
public:
	void bhop(CUserCmd* cmd);
	void legit_strafe(CUserCmd* ucmd);
	void rage_strafe(CUserCmd* ucmd);
	
	
}; extern Misc* misc;