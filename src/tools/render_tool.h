#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <tools/color.h>


class CRenderTool
{
private:
	IDirect3DDevice9* device;
	//mutable std::shared_mutex mutex;
	//std::vector<CBaseCall*> draw_calls;
	//std::vector<CBaseCall*> safe_draw_calls;

public:
	IDirect3DDevice9* get_device() { return device; }

	void init(IDirect3DDevice9* device);
	void render_frame();	//Render frame with menu and visual
	//void render_dx();		//Render DX

	//void begin();			//Use when start drawing
	//void end();				//Use when end drawing

	//DWORD get_draw_color(Color color) const { return D3DCOLOR_ARGB(color.a(), color.r(), color.g(), color.b()); }

	//void render_filled_box(float x, float y, float w, float h, Color color);
	//void render_bordered_box(float x, float y, float w, float h, float t, Color color);


	void create_draw_font(std::vector<unsigned long>& in, const char* win_name, int max_size, int flags);
	void draw_filled_box(int x, int y, int w, int h, Color color);
	void draw_bordered_box(float x, float y, float w, float h, float t, Color color);
	void draw_line(int x0, int y0, int x1, int y1, Color color);
	void draw_text(int x, int y, unsigned long font, const std::string& text, bool centered, Color color);

	//void create_im_font(std::vector<ImFont*>& in, const char* font = "C:\\Windows\\Fonts\\Corbel.ttf", int max_size = 30, const ImWchar* glyph_ranges = NULL, const ImFontConfig* font_cfg = NULL);
};

extern CRenderTool* render_tool;