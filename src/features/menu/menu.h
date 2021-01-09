#pragma once
#include <imgui/imgui.h>

class Menu
{
public:
	ImFont* menu_button_font = nullptr;
	ImFont* menu_font = nullptr;
	
	void draw();

	bool is_open = true;
}; extern Menu* menu;