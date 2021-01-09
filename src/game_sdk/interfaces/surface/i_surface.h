#pragma once
#include <tools/color.h>
#include <tools/mem_tools.h>

static const wchar_t* get_wc_t(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

enum FontDrawType_t
{
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT = 0,

	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT = 2,
};

enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

struct IntRect
{
	int x0;
	int y0;
	int x1;
	int y1;
};

typedef unsigned long HFont;
typedef unsigned int VPANEL;

enum class FontDrawType
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2,
};

class ISurface
{
public:			//https://imgur.com/vmGXsx7
	void unlock_cursor()
	{
		using orig_fn = void(__thiscall*)(ISurface*);
		return (*(orig_fn**)this)[61](this);
	}

	void lock_cursor()
	{
		using orig_fn = void(__thiscall*)(ISurface*);
		return (*(orig_fn**)this)[62](this);
	}

	void set_drawing_color(int r, int g, int b, int a = 255)
	{
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[11](this, r, g, b, a);
	}

	void set_drawing_color(Color color)
	{
		using original_fn = void(__thiscall*)(ISurface*, Color);
		return (*(original_fn**)this)[10](this, color);
	}
	
	void draw_filled_rect(int x0, int y0, int x1, int y1)
	{
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[12](this, x0, y0, x1, y1);
	}

	void draw_outline_rect(int x0, int y0, int x1, int y1)
	{
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[14](this, x0, y0, x1, y1);
	}

	void draw_line(int x0, int y0, int x1, int y1)
	{
		using original_fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(original_fn**)this)[15](this, x0, y0, x1, y1);
	}

	void set_text_font(unsigned long font)
	{
		using fn = void(__thiscall*)(ISurface*, unsigned long);
		return (*(fn**)this)[17](this, font);
	}

	void set_text_color(Color color)
	{
		using fn = void(__thiscall*)(ISurface*, Color color);
		return (*(fn**)this)[18](this, color);
	}

	void set_text_color(int r, int g, int b, unsigned int a = 0)
	{
		using fn = void(__thiscall*)(ISurface*, int, int, int, unsigned int);
		return (*(fn**)this)[19](this, r, g, b, a);
	}
	
	void set_text_pos(int x, int y)
	{
		using fn = void(__thiscall*)(ISurface*, int, int);
		return (*(fn**)this)[20](this, x, y);
	}

	void draw_text(const wchar_t* text, int text_len)
	{
		using fn = void(__thiscall*)(ISurface*, const wchar_t*, int, int);
		return (*(fn**)this)[22](this, text, text_len, 0);
	}

	unsigned long create_font()
	{
		using fn = unsigned long(__thiscall*)(ISurface*);
		return (*(fn**)this)[66](this);
	}

	bool set_font_style(unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		using fn = bool(__thiscall*)(ISurface*, unsigned long, const char*, int, int, int, int, int, int, int);
		return (*(fn**)this)[67](this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}
	
	void get_text_size(unsigned long font, const wchar_t* text, int& wide, int& tall)
	{
		using fn = void(__thiscall*)(ISurface*, unsigned long, const wchar_t*, int&, int&);
		return (*(fn**)this)[76](this, font, text, wide, tall);
	}

	void draw_outlined_circle(int x, int y, int radius, int segments)	//100
	{
		using fn = void(__thiscall*)(ISurface*, int, int, int, int);
		return (*(fn**)this)[100](this, x, y, radius, segments);
	}


	void draw_filled_rect_array(IntRect* rects, int rect_num)
	{
		using fn = void(__thiscall*)(void*, void*, int);
		static fn func;

		if (!func)
			func = (fn)(MemTools::pattern_scaner("vguimatsurface.dll", "55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 48"));

		func(this, rects, rect_num);
	}
	
	void start_drawing()
	{
		using StartDrawingFn = void(__thiscall*)(void*);
		static StartDrawingFn StartDrawing;

		if (!StartDrawing)
			StartDrawing = (StartDrawingFn)(MemTools::pattern_scaner("vguimatsurface.dll", "55 8B EC 64 A1 ?? ?? ?? ?? 6A FF 68 ?? ?? ?? ?? 50 64 89 25 ?? ?? ?? ?? 83 EC 14"));

		StartDrawing(this);
	}

	void finish_drawing()
	{
		using FinishDrawingFn = void(__thiscall*)(void*);
		static FinishDrawingFn FinishDrawing;

		if (!FinishDrawing)
			FinishDrawing = (FinishDrawingFn)(MemTools::pattern_scaner("vguimatsurface.dll", "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 ?? ?? ?? ?? 50 64 89 25 ?? ?? ?? ?? 51 56 6A 00"));

		FinishDrawing(this);
	}
};