#include "menu.h"

#include <string>
#include <imgui/imgui.h>

#include <globals.h>

#include "custom_widgets.h"
#include "tools/color.h"

#define COLOR_EDIT_FLAGS ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview
#define COLOR_PICKER_FLAGS 
#define TUBS_NUM 7
#define TAB_SIZE_W 127.f
#define TAB_SIZE_H 50.f
#define CHILDE_SIZE_W 330.f
#define TABS_MARGIN 6.f
#define CHILD_MARGIN 8.f
#define TOGGLE_BUTTON_SIZE ImVec2(45, 14)

enum class tabs
{
	legit_bot,
	rage,
	visuals,
	props,
	color,
	misc,
	settings
};

static const char* tabs_names[] = {
	"LEGITBOT##menubutton",
	"RAGE##menubutton",
	"VISUALS##menubutton",
	"PROPS##menubutton",
	"COLOR##menubutton",
	"MISC##menubutton",
	"SETTINGS##menubutton"
};

tabs current_tab = tabs::visuals;

Menu* menu = new Menu();

//hide this
void draw_top_bar()
{
	ImGui::BeginGroup();
	{
		///logo
		ImGui::PushFont(menu->menu_button_font);

		auto text_size = ImGui::CalcTextSize("LemiProject", 0, false);
		auto p = ImVec2((text_size.x + text_size.x * 0.3f), text_size.y);


		ImGui::SetCursorPos(ImVec2(text_size.x * 0.1f, 10));

		ImGui::TextColored(ImVec4(0.3, 1, 0.3, 1), "LemiProject");

		ImGui::PopFont();

		for (auto i = 0; i < TUBS_NUM; i++)
		{
			ImVec2 pos = i == 0 ? ImVec2(p.x, 0) : ImVec2(p.x + (i + TAB_SIZE_W * static_cast<float>(i) + TABS_MARGIN * i), 0);

			if (ImGui::MenuButton(tabs_names[i], ImVec2(TAB_SIZE_W, TAB_SIZE_H), pos,
				current_tab == static_cast<tabs>(i) ? Color(42, 42, 42) : Color(32, 32, 32),
				Color(255, 255, 255), menu->menu_font))
			{
				current_tab = static_cast<tabs>(i);
			}
		}

		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + 49), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + 53), ImGui::GetColorU32(ImVec4(0.12549f, 0.12549f, 0.12549f, 1.0f)));
	}
	ImGui::EndGroup();
}

void draw_legit_bot()
{
	ImGui::BeginGroup();
	{
		ImGui::BeginGroupPanel("LegitBot", ImVec2(CHILDE_SIZE_W, -1.f), Color(ImGui::GetStyle().Colors[ImGuiCol_ChildBg]), Color(32, 32, 32));
		{
			ImGui::ToggleButton("Enable##legitbot", &settings::legit_bot->aim_enable, TOGGLE_BUTTON_SIZE);
			ImGui::ToggleButton("Only visible##legitbot", &settings::legit_bot->only_visible, TOGGLE_BUTTON_SIZE);
			{
				ImGui::ToggleButton("Auto fire##legitbot", &settings::legit_bot->auto_fire, TOGGLE_BUTTON_SIZE);
				//if (settings::legit_bot->auto_fire)
				//{
				//	ImGui::SameLine(0, 100);
				//	ImGui::Hotkey("Autofire key", &settings::legit_bot->auto_fire, ImVec2(150, 0));
				//}
			}

			ImGui::SliderFloat("Fov##legitbot", &settings::legit_bot->fov, 0.f, 180.f, "%.0f", 1.f);

			ImGui::Hotkey("Aim key", &settings::legit_bot->aimkey);

		}
		ImGui::EndGroupPanel();
	}
	ImGui::EndGroup();
	ImGui::SameLine();
	ImGui::BeginGroup();
	{
		ImGui::BeginGroupPanel("Weapon", ImVec2(CHILDE_SIZE_W, -1.f), Color(ImGui::GetStyle().Colors[ImGuiCol_ChildBg]), Color(32, 32, 32));
		{
			ImGui::Text("Weapon override settings where...");
		}
		ImGui::EndGroupPanel();
	}
	ImGui::EndGroup();
	ImGui::SameLine();
	ImGui::BeginGroup();
	{
		ImGui::BeginGroupPanel("Accuracy", ImVec2(CHILDE_SIZE_W, -1.f), Color(ImGui::GetStyle().Colors[ImGuiCol_ChildBg]), Color(32, 32, 32));
		{
			//ImGui::ToggleButton("Aim step##legitbot", &settings::legit_bot->aim_step, TOGGLE_BUTTON_SIZE);
			//if (settings::legit_bot->aim_step)
			//	ImGui::SliderFloat("Aim step amount##legitbot", &settings::legit_bot->aim_step_amount, 0.f, 25.f, "%.0f", 1.f);

			//ImGui::ToggleButton("RCS##legitbot", &settings::legit_bot->rcs_enable, TOGGLE_BUTTON_SIZE);
			//if (settings::legit_bot->rcs_enable)
			//	ImGui::SliderFloat("RCS factor##legitbot", &settings::legit_bot->rcs_factor, 1.f, 3.f, "%.2f");

			//ImGui::SliderFloat("Smooth##legitbot", &settings::legit_bot->smooth, 0.f, 40.f, "%.2f");
		}
		ImGui::EndGroupPanel();
	}
	ImGui::EndGroup();
}

void draw_rage()
{
	{

	}
}

void draw_visuals()
{
	ImGui::BeginGroup();
	{
		ImGui::BeginGroupPanel("ESP", ImVec2(CHILDE_SIZE_W, -1.f), Color(ImGui::GetStyle().Colors[ImGuiCol_ChildBg]), Color(32, 32, 32));
		{
			ImGui::ToggleButton("Enable##esp", &settings::esp->box_enable, TOGGLE_BUTTON_SIZE);
			ImGui::ToggleButton("Team color##esp", &settings::esp->is_team_color, TOGGLE_BUTTON_SIZE);
			//ImGui::ToggleButton("Only visible##esp", &settings::esp->v, TOGGLE_BUTTON_SIZE);
			ImGui::ToggleButton("Name##esp", &settings::esp->draw_name, TOGGLE_BUTTON_SIZE);
			ImGui::ToggleButton("Name team color##esp", &settings::esp->is_team_name_color, TOGGLE_BUTTON_SIZE);
			//ImGui::ToggleButton("Bone ids##espbox", &settings::esp->draw_bone_ids, TOGGLE_BUTTON_SIZE);
			//ImGui::SizedCombo("Box type##esp", &settings::esp->box_type, settings::esp->box_types, 3, ImVec2(120, 0));
			/*ImGui::Spacing();
			ImGui::ToggleButton("Health##esp", &settings::esp->draw_health, TOGGLE_BUTTON_SIZE);
			ImGui::ToggleButton("Scoped##esp", &settings::esp->draw_scoped, TOGGLE_BUTTON_SIZE);*/

			/*ImGui::Spacing();
			ImGui::ToggleButton("Draw bones#esp", &settings::esp->draw_bones, TOGGLE_BUTTON_SIZE);*/
		}
		ImGui::EndGroupPanel();
	}
	ImGui::EndGroup();
	ImGui::SameLine();
	ImGui::BeginGroup();
	{
		ImGui::BeginGroupPanel("Chams", ImVec2(CHILDE_SIZE_W, -1.f), Color(ImGui::GetStyle().Colors[ImGuiCol_ChildBg]), Color(32, 32, 32));
		{
			ImGui::ToggleButton("Enable##chams", &settings::esp->chams_enable, TOGGLE_BUTTON_SIZE);
		}
		ImGui::EndGroupPanel();
	}
	ImGui::EndGroup();
	ImGui::SameLine();
	ImGui::BeginGroup();
	{
		ImGui::BeginGroupPanel("World", ImVec2(CHILDE_SIZE_W, -1.f), Color(ImGui::GetStyle().Colors[ImGuiCol_ChildBg]), Color(32, 32, 32));
		{

		}
		ImGui::EndGroupPanel();

		ImGui::Spacing();

		ImGui::BeginGroupPanel("Self", ImVec2(CHILDE_SIZE_W, -1.f), Color(ImGui::GetStyle().Colors[ImGuiCol_ChildBg]), Color(32, 32, 32));
		{
			/*ImGui::ToggleButton("Draw fov##selfvisuals", &settings::visuals::draw_fov, TOGGLE_BUTTON_SIZE);

			ImGui::SliderInt("Fov##selfvisuals", &settings::visuals::fov, 0, 89);

			ImGui::ToggleButton("Override aspect ratio##selfvisuals", &settings::visuals::override_aspect_ratio, TOGGLE_BUTTON_SIZE);
			if (settings::visuals::override_aspect_ratio)
				ImGui::SliderFloat("Aspect ratio##selfvisuals", &settings::visuals::aspect_ratio, 0, 200, "%.0f", 1.f);*/
		}
		ImGui::EndGroupPanel();
	}
	ImGui::EndGroup();
}

void draw_props()
{
	{

	}
}

void draw_color()
{
	ImGui::BeginGroupPanel("ESP", ImVec2(CHILDE_SIZE_W, -1.f), Color(ImGui::GetStyle().Colors[ImGuiCol_ChildBg]), Color(32, 32, 32));
	{
		ImGui::ColorEdit4("Box color##espbox", settings::esp->visible_color, COLOR_EDIT_FLAGS);
		//ImGui::SameLine();
		//ImGui::ColorEdit4("Invisible##espbox", settings::esp->color, COLOR_EDIT_FLAGS);
		//ImGui::Spacing();
		//ImGui::ColorEdit4("Void health box##espbox", settings::esp->void_health_color, COLOR_EDIT_FLAGS);
		//ImGui::SameLine();
		//ImGui::ColorEdit4("Full health box##espbox", settings::esp->health_color, COLOR_EDIT_FLAGS);
	}
	ImGui::EndGroupPanel();
	
	ImGui::BeginGroupPanel("Chams", ImVec2(CHILDE_SIZE_W, -1.f), Color(ImGui::GetStyle().Colors[ImGuiCol_ChildBg]), Color(32, 32, 32));
	{
		ImGui::ColorEdit4("Chams color##chams", settings::esp->chams_color, COLOR_EDIT_FLAGS);
		//ImGui::SameLine();
		//ImGui::ColorEdit4("Invisible##espbox", settings::esp->color, COLOR_EDIT_FLAGS);
		//ImGui::Spacing();
		//ImGui::ColorEdit4("Void health box##espbox", settings::esp->void_health_color, COLOR_EDIT_FLAGS);
		//ImGui::SameLine();
		//ImGui::ColorEdit4("Full health box##espbox", settings::esp->health_color, COLOR_EDIT_FLAGS);
	}
	ImGui::EndGroupPanel();

}

void draw_misc()
{
	ImGui::BeginGroup();
	{
		ImGui::BeginGroupPanel("Movement", ImVec2(CHILDE_SIZE_W, -1.f), Color(ImGui::GetStyle().Colors[ImGuiCol_ChildBg]), Color(32, 32, 32));
		{
			ImGui::ToggleButton("Bhop##move", &settings::misc->bhop_enable, TOGGLE_BUTTON_SIZE);
			ImGui::ToggleButton("Auto strafe##move", &settings::misc->auto_strafe_enable, TOGGLE_BUTTON_SIZE);
		}
		ImGui::EndGroupPanel();
	}
	ImGui::EndGroup();
}

void draw_settings()
{
	{

	}
}

void Menu::draw()
{
	if (!is_open)
	{
		ImGui::GetIO().MouseDrawCursor = false;
		return;
	}

	if (!ImGui::GetIO().MouseDrawCursor)
		ImGui::GetIO().MouseDrawCursor = true;
	
	ImGui::ANIM_SPEED = 50.f;

	ImGui::PushFont(menu_font);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("LemiProjectWindow", static_cast<bool*>(0), ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar /*| ImGuiWindowFlags_AlwaysAutoResize*/);
	{
		ImGui::PopStyleVar();
		ImGui::SetWindowSize(ImVec2(1150, 620));

		draw_top_bar();

		switch (current_tab)
		{
		case tabs::legit_bot:
			draw_legit_bot();
			break;
		case tabs::rage:
			draw_rage();
			break;
		case tabs::visuals:
			draw_visuals();
			break;
		case tabs::color:
			draw_color();
			break;
		case tabs::props:
			draw_props();
			break;
		case tabs::misc:
			draw_misc();
			break;
		case tabs::settings:
			draw_settings();
			break;
		}
	}
	ImGui::End();
	ImGui::PopFont();
}
