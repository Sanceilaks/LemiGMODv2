#include "render_tool.h"
#include <imgui/imgui.h>
#include <imgui/impl/imgui_impl_win32.h>
#include <imgui/impl/imgui_impl_dx9.h>

#include <features/visuals/esp.h>
#include <features/menu/menu.h>
#include <interfaces.h>
#include <globals.h>

CRenderTool* RenderTool = new CRenderTool();

#pragma region RenderTool

void CRenderTool::init(IDirect3DDevice9* device)
{
	this->device = device;

	RenderTool->create_draw_font(settings::ESP->esp_font, "Corbel", 100, (int)EFontFlags::FONTFLAG_DROPSHADOW);
}

void CRenderTool::render_frame()
{
	RenderTool->render_dx();

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Menu->draw();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void CRenderTool::render_dx()
{
	for (auto call : safe_draw_calls)
	{
		call->draw();
	}
}

void CRenderTool::begin()
{
	draw_calls.clear();
}

void CRenderTool::end()
{
	std::unique_lock<std::shared_mutex> lock(mutex);
	draw_calls.swap(safe_draw_calls);
}

void CRenderTool::render_filled_box(float x, float y, float w, float h, Color color)
{
	auto call = new DrawFilledBox(x, y, w, h, color);
	draw_calls.push_back(call);
}

void CRenderTool::render_bordered_box(float x, float y, float w, float h, float t, Color color)
{
	auto call = new DrawBorderedBox(x, y, w, h, t, color);
	draw_calls.push_back(call);
}

void CRenderTool::create_draw_font(std::vector<unsigned long>& in, const char* win_name, int max_size, int flags)
{
	std::vector<unsigned long> out;

	//while (!Interfaces->surface)
	//{
	//	std::this_thread::sleep_for(std::chrono::milliseconds(25));
	//}

	for (int i = 1; i <= max_size; ++i)
	{
		unsigned long tmp = Interfaces->surface->create_font();
		Interfaces->surface->set_font_style(tmp, win_name, i, 500, 0, 0, flags);
		out.push_back(tmp);
	}

	in = out;
}

void CRenderTool::draw_filled_box(int x, int y, int w, int h, Color color)
{
	Interfaces->surface->set_drawing_color(color.r(), color.g(), color.b(), color.a());
	Interfaces->surface->draw_filled_rect(x, y, x + w, y + h);
}

void CRenderTool::draw_bordered_box(float x, float y, float w, float h, float t, Color color)
{
	Interfaces->surface->set_drawing_color(color.r(), color.g(), color.b(), color.a());
	Interfaces->surface->draw_outline_rect(x, y, x + w, y + h);
}

void CRenderTool::draw_line(int x0, int y0, int x1, int y1, Color color)
{
	Interfaces->surface->set_drawing_color(color.r(), color.g(), color.b(), color.a());
	Interfaces->surface->draw_line(x0, y0, x1, y1);
}

void CRenderTool::draw_text(int x, int y, unsigned long font, const std::string& text, bool centered, Color color)
{
	const auto surface = Interfaces->surface;
	wchar_t temp[128];
	int text_width, text_height;
	if (MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, temp, 128) > 0) {
		surface->set_text_font(font);
		if (centered) {
			surface->get_text_size(font, temp, text_width, text_height);
			surface->set_text_pos(x - text_width / 2, y);
		}
		else
			surface->set_text_pos(x, y);
		surface->set_text_color(color);
		surface->draw_text(temp, wcslen(temp));
	}
}

void CRenderTool::create_im_font(std::vector<ImFont*>& in, const char* font, int max_size, const ImWchar* glyph_ranges, const ImFontConfig* font_cfg)
{
	std::vector<ImFont*> out;
	ImGuiIO& io = ImGui::GetIO();

	for (int i = 1; i <= max_size; ++i)
	{
		auto add = io.Fonts->AddFontFromFileTTF(font, i, font_cfg, glyph_ranges);
		out.push_back(add);
	}

	in.swap(out);
}

#pragma endregion

void DrawFilledBox::draw()
{
	D3DRECT rect = { x, y, x + w, y + h };
	RenderTool->get_device()->Clear(1, &rect, D3DCLEAR_TARGET, RenderTool->get_draw_color(color), 0, 0);
}

void DrawBorderedBox::draw()
{
	auto draw_filled_rect = [](int x, int y, int w, int h, Color color) -> void
	{
		D3DRECT rect = { x, y, x + w, y + h };
		RenderTool->get_device()->Clear(1, &rect, D3DCLEAR_TARGET, RenderTool->get_draw_color(color), 0, 0);
	};

	draw_filled_rect(x, y, w, t, color);
	draw_filled_rect(x, y, t, h, color);
	draw_filled_rect(x + w, y, t, h, color);
	draw_filled_rect(x, y + h, w + t, t, color);
}
