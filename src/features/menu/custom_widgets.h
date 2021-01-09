#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <tools/color.h>


namespace ImGui
{
	static float ANIM_SPEED = 0.009f;

	IMGUI_API bool RoundedButtonEx(const char* label, const ImVec2& size_args, float rounding, ImGuiButtonFlags flags);
	IMGUI_API bool RoundedButton(const char* label, float rounding = 2.f, const ImVec2& size = ImVec2(0, 0));

	IMGUI_API void ToggleButton(const char* str_id, bool* v, const ImVec2& size = ImVec2(0, 0));

	IMGUI_API bool MenuButton(const char* label, const ImVec2& size_args, const ImVec2& pos, Color color, Color text_color, ImFont* font);

	IMGUI_API void BeginGroupPanel(const char* label, const ImVec2& size = ImVec2(-1.f, -1.f), Color bg_color = Color(0, 0, 0), Color text_bg_color = Color(0, 0, 0));
	IMGUI_API void EndGroupPanel();

	IMGUI_API bool SizedCombo(const char* label, int* current_item, const char* const items[], int items_count, ImVec2 size, int height_in_items = -1);

	IMGUI_API bool Hotkey(const char* label, int* k, const ImVec2& size_arg = ImVec2(0, 0));
}
