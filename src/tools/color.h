#pragma once

#pragma warning( push )
#pragma warning( disable : 4244) //4244


#include <imgui/imgui.h>


enum Colors
{
	BLUE = (0, 0, 255),
	RED = (255, 0, 0),
	GREEN = (0, 255, 0),
	WHITE = (255, 255, 255),
	BLACK = (0, 0, 0),
};

class Color
{
public:
	// constructors
	Color()
	{
		*((int*)this) = 0;
	}
	Color(int _r, int _g, int _b)
	{
		set_color(_r, _g, _b);
	}
	Color(int _r, int _g, int _b, int _a)
	{
		set_color(_r, _g, _b, _a);
	}
	Color(const ImVec4& vec4)
	{
		set_color(vec4.x * 255, vec4.y * 255, vec4.z * 255, vec4.w * 255);
	}

	//Color(float col_arr[3])
	//{
	//	set_color(col_arr[0] * 255, col_arr[1] * 255, col_arr[2] * 255);
	//}

	Color(float arr[4])
	{
		if (arr[0] > 1.f || arr[1] > 1.f || arr[2] > 1.f || arr[3] > 1.f)
			set_color(arr[0], arr[1], arr[2], arr[3]);
		else
			set_color(arr[0] * 255, arr[1] * 255, arr[2] * 255, arr[3] * 255);
	}

	// set the color
	// r - red component (0-255)
	// g - green component (0-255)
	// b - blue component (0-255)
	// a - alpha component, controls transparency (0 - transparent, 255 - opaque);
	void set_color(int _r, int _g, int _b, int _a = 255)
	{
		_color[0] = (unsigned char)_r;
		_color[1] = (unsigned char)_g;
		_color[2] = (unsigned char)_b;
		_color[3] = (unsigned char)_a;
	}

	void get_color(int& _r, int& _g, int& _b, int& _a) const
	{
		_r = _color[0];
		_g = _color[1];
		_b = _color[2];
		_a = _color[3];
	}
	void set_raw_color(int color32)
	{
		*((int*)this) = color32;
	}

	ImU32 get_u32()
	{
		return ((_color[3] & 0xff) << 24) + ((_color[2] & 0xff) << 16) + ((_color[1] & 0xff) << 8)
			+ (_color[0] & 0xff);
		//return (ImU32)(((_color[3] & 0xff) << 24) + ((_color[0] & 0xff) << 16) + ((_color[1] & 0xff) << 8) + (_color[2] & 0xff));
	}

	int get_raw_color() const
	{
		return *((int*)this);
	}

	inline int r() const { return _color[0]; }
	inline int g() const { return _color[1]; }
	inline int b() const { return _color[2]; }
	inline int a() const { return _color[3]; }


	unsigned char& operator[](int index)
	{
		return _color[index];
	}

	const unsigned char& operator[](int index) const
	{
		return _color[index];
	}

	bool operator == (const Color& rhs) const
	{
		return (*((int*)this) == *((int*)&rhs));
	}

	bool operator != (const Color& rhs) const
	{
		return !(operator==(rhs));
	}

	Color& operator=(const Color& rhs)
	{
		set_raw_color(rhs.get_raw_color());
		return *this;
	}

public:
	unsigned char _color[4];
};

#pragma warning( pop )