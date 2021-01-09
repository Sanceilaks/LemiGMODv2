#pragma once
#include <cstdint>


class IMatRenderContext;

namespace read_pixels_hook
{
	using fn = void(__thiscall*)(IMatRenderContext*, int, int, int, int, unsigned char*, int);
	extern void __fastcall hook(IMatRenderContext* self, uintptr_t edx, int x, int y, int w, int h, uint8_t* data, int dst);
}
