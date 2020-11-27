#include "menu.h"
#include <globals.h>
#include <tools/color.h>
#include "custom_widgets.h"

#define COLOR_EDIT_FLAGS ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_NoInputs

CMenu* Menu = new CMenu();

enum class Tabs
{
	NONE,
	LEGIT,
	RAGE,
	ESP,
	VISUALS,
	MISC,
	CONFIG
};

Tabs current_tabs[6] = { Tabs::NONE , Tabs::NONE, Tabs::NONE,  Tabs::NONE,  Tabs::NONE ,  Tabs::NONE };

void draw_tabs()
{
	//ImGui::BeginChild("###tabs", ImVec2(ImGui::GetWindowWidth() - 15, 25), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	//ImGui::SameLine(0.0f, ImGui::GetWindowWidth() * 0.32f);
	//ImGui::SetCursorPosY(3);
	ImGui::BeginGroup();
	if (ImGui::Button("Legit bot")) if (current_tabs[0] == Tabs::LEGIT) current_tabs[0] = Tabs::NONE; else current_tabs[0] = Tabs::LEGIT;
	ImGui::SameLine();
	if (ImGui::Button("Rage")) if (current_tabs[1] == Tabs::RAGE) current_tabs[1] = Tabs::NONE; else current_tabs[1] = Tabs::RAGE;
	ImGui::SameLine();
	if (ImGui::Button("ESP")) if (current_tabs[2] == Tabs::ESP) current_tabs[2] = Tabs::NONE; else current_tabs[2] = Tabs::ESP;
	ImGui::SameLine();
	if (ImGui::Button("Visual")) if (current_tabs[3] == Tabs::VISUALS) current_tabs[3] = Tabs::NONE; else current_tabs[3] = Tabs::VISUALS;
	ImGui::SameLine();
	if (ImGui::Button("Misc")) if (current_tabs[4] == Tabs::MISC) current_tabs[4] = Tabs::NONE; else current_tabs[4] = Tabs::MISC;
	ImGui::SameLine();
	if (ImGui::Button("Config")) if (current_tabs[5] == Tabs::CONFIG) current_tabs[5] = Tabs::NONE; else current_tabs[5] = Tabs::CONFIG;
	ImGui::EndGroup();
	//ImGui::EndChild();
}

void draw_esp()
{
	ImGui::Begin("ESP", (bool*)0, ImGuiWindowFlags_NoScrollbar);
	float xx = ImGui::GetStyle().ItemSpacing.x;
	float yy = ImGui::GetStyle().FramePadding.y;

	ImGui::BeginChild("###ESPBox", ImVec2(ImGui::GetWindowWidth() / 2, 0), true);
	ImGui::Checkbox("Esp box", &settings::ESP->box_enable);
	ImGui::SameLine();
	if (settings::ESP->box_enable)
	{
		ImGui::Checkbox("Team color", &settings::ESP->is_team_color);
		ImGui::SameLine();
		if (!settings::ESP->is_team_color)
		{
			ImGui::ColorEdit4("###boxcolor Color", settings::ESP->visible_color, COLOR_EDIT_FLAGS);
			ImGui::SameLine();
		}
	}

	ImGui::Spacing();

	ImGui::Checkbox("Draw name", &settings::ESP->draw_name);
	ImGui::SameLine();
	if (settings::ESP->draw_name)
	{
		ImGui::Checkbox("Name team color", &settings::ESP->is_team_name_color);
		ImGui::SameLine();
		if (!settings::ESP->is_team_name_color)
		{
			ImGui::ColorEdit4("###namecolor Color", settings::ESP->visible_name_color, COLOR_EDIT_FLAGS);
			ImGui::SameLine();
		}
	}

	ImGui::Spacing();


	ImGui::EndChild();
	ImGui::SameLine();

	ImGui::BeginChild("Chams", ImVec2(ImGui::GetWindowWidth() / 2 - xx * 3, 0), true);
	ImGui::Checkbox("Chams", &settings::ESP->chams_enable);
	
	if (settings::ESP->chams_type == 0)
	{
		ImGui::SameLine();
		ImGui::ColorEdit4("###chams Color", settings::ESP->chams_color, COLOR_EDIT_FLAGS);
	}

	const char* chams_types[2] = { "flat", "wh" };
	ImGui::Combo("Chams type", &settings::ESP->chams_type, chams_types, 2);



	ImGui::EndChild();
	ImGui::End();
}

void draw_misc()
{
	ImGui::Begin("Misc", (bool*)0, ImGuiWindowFlags_NoScrollbar);
	ImGui::BeginChild("###Misc", ImVec2(0, 0), true);
	ImGui::Checkbox("Bhop", &settings::Misc->bhop_enable);
	ImGui::SameLine();
	ImGui::Checkbox("Auto strafe", &settings::Misc->auto_strafe_enable);

	ImGui::EndChild();
	ImGui::End();
}

void draw_aimbot()
{
	ImGui::Begin("Aimbot", (bool*)0, ImGuiWindowFlags_NoScrollbar);
	float xx = ImGui::GetStyle().ItemSpacing.x;
	float yy = ImGui::GetStyle().FramePadding.y;

	ImGui::BeginChild("###AimBot", ImVec2(ImGui::GetWindowWidth() / 2, 0), true);

	ImGui::Checkbox("AimBot", settings::Rage->rage_enable ? (bool*)0 : &settings::AimBot->aim_enable);
	ImGui::SameLine();
	ImGui::Checkbox("Silent", &settings::AimBot->silent);
	ImGui::SameLine();
	ImGui::Checkbox("Only visible", &settings::AimBot->only_visible);
	ImGui::SameLine();
	ImGui::Checkbox("Auto fire", &settings::AimBot->auto_fire);

	ImGui::SliderInt("Fov", &settings::AimBot->fov, 1, 360);

	ImGui::PushItemWidth(150);
	ImGui::Hotkey("AimKey", &settings::AimBot->aimkey);
	ImGui::PopItemWidth();


	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::End();
}

void draw_rage()
{
	ImGui::Begin("Rage##tab");

	ImGui::BeginChild("##Rage", ImVec2(ImGui::GetWindowWidth()/* / 2*/, 0), true);

	ImGui::Checkbox("Rage##enabled", &settings::Rage->rage_enable);
	ImGui::Checkbox("Silent##rage", &settings::Rage->silent);
	ImGui::Spacing();
	ImGui::Checkbox("AntiAim", &settings::AimBot->anti_aim_enable);
	ImGui::SameLine();
	const char* antiaim_types[3] = { "yaw", "jitter", "forward" };
	ImGui::Combo("AntiAim type", &settings::AimBot->anti_aim_type, antiaim_types, 3);
	
	ImGui::EndChild();
	
	ImGui::End();
}

void draw_visuals()
{
	ImGui::Begin("Visuals", (bool*)0, ImGuiWindowFlags_NoScrollbar);
	ImGui::BeginChild("###Visuals", ImVec2(0, 0), true);

	ImGui::Checkbox("Draw fov", &settings::Visuals->draw_fov);


	ImGui::EndChild();
	ImGui::End();
}

void CMenu::draw()
{
	if (!is_open)
	{
		ImGui::GetIO().MouseDrawCursor = false;
		return;
	}

	if (!ImGui::GetIO().MouseDrawCursor)
		ImGui::GetIO().MouseDrawCursor = true;

	ImGui::Begin("LemiProject", (bool*)0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize);
	//ImGui::SetWindowSize(ImVec2(800, 35));
	ImGui::PushFont(menu_font[10]);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	draw_tabs();
	ImGui::PopStyleVar();


	for (int i = 0; i <= 5; ++i)
	{
		switch (current_tabs[i])
		{
		case Tabs::NONE:
			break;
		case Tabs::LEGIT:
			draw_aimbot();
			break;
		case Tabs::RAGE:
			draw_rage();
			break;
		case Tabs::ESP:
			draw_esp();
			break;
		case Tabs::VISUALS:
			draw_visuals();
			break;
		case Tabs::MISC:
			draw_misc();
			break;
		case Tabs::CONFIG:
			break;
		}
	}
	
	ImGui::PopFont();

	ImGui::End();
}
