#pragma once
#include <imgui/imgui.h>
#include <vector>

class CMenu
{
public:
	std::vector<ImFont*> menu_font;
	void draw();

	bool is_open;
}; extern CMenu* Menu;