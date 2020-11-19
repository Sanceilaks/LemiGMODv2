#pragma once
#include <d3d9.h>

namespace end_scane_hook
{
	using fn = long(__stdcall*)(IDirect3DDevice9*);
	extern long __stdcall hook(IDirect3DDevice9* device);
}