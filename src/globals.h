#pragma once
#include <game_sdk/classes/c_view_setup.h>
#include <math/qangle.h>

namespace settings
{
	enum AntiAimType
	{
		yaw = 0,
		jitter,
		forward
	};

	class CESP
	{
	public:
		bool box_enable = true;
		float visible_color[4] = { 1, 0, 0, 1 };
		bool is_team_color = false;

		bool draw_name = true;
		float visible_name_color[4] = { 1, 0, 0, 1 };
		bool is_team_name_color = false;
		std::vector<unsigned long> esp_font;

		bool chams_enable = true;
		int chams_type = 0;  //0 - flat; 1 - wh
		float chams_color[4] = { 1, 0, 0, 1 };
	}; extern CESP* ESP;

	class CMisc
	{
	public:
		bool bhop_enable = true;
		bool auto_strafe_enable = false;

	}; extern CMisc* Misc;

	class CAimBot
	{
	public:
		bool aim_enable = true;
		bool silent = true;
		bool only_visible = true;
		bool auto_fire = false;
		int fov = 20;

		bool anti_aim_enable = false;
		int anti_aim_type = AntiAimType::yaw;
		//bool fake_angel = false;

		int aimkey = VK_MENU;

	}; extern CAimBot* AimBot;

	class CRage
	{
	public:
		bool rage_enable = false;
		bool silent = true;
		bool only_visible = true;
		
	}; extern CRage* Rage;
	
	class CVisuals
	{
	public:
		bool draw_fov = false;

	}; extern CVisuals* Visuals;
}


class CGlobals
{
public:
	int screen_width = 0, screen_height = 0;
	CViewSetup view;

	bool win_buttons[1032];

	QAngle last_angel;

}; extern CGlobals* Globals;

static bool is_key_presed(int key)
{
	return Globals->win_buttons[key];
}