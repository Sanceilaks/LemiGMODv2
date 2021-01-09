#pragma once
#include <game_sdk/interfaces/include_interfaces.h>
#include <tools/mem_tools.h>
#include <d3d9.h>

#define INTERFACES_INTERNAL

#ifdef INTERFACES_INTERNAL
	#define ADD_INTERFACE(varname, interface_type) interface_type* varname = nullptr;
	#define INIT_INTERFACE(varname, interface_type, i_module, i_name) varname = (interface_type*)(MemTools::get_interface(i_module, i_name));
#endif


class CInterfaces
{
public:
	ADD_INTERFACE(client, VClient);
	ADD_INTERFACE(engine, VEngineClient);
	ADD_INTERFACE(client_mode, IClientMode);
	ADD_INTERFACE(entity_list, VClientEntityList);
	ADD_INTERFACE(directx_device, IDirect3DDevice9);
	ADD_INTERFACE(material_system, IMaterialSystem);
	ADD_INTERFACE(view_render, IViewRender);
	ADD_INTERFACE(render_view, VEngineRenderView);
	ADD_INTERFACE(render, IRender);
	ADD_INTERFACE(model_render, IVModelRender);
	ADD_INTERFACE(surface, ISurface);
	ADD_INTERFACE(lua_shared, LUA::Shared);
	ADD_INTERFACE(engine_trace, IEngineTrace);
	ADD_INTERFACE(render_context, IMatRenderContext);
public:
	void init();

	void print_interfaces();
};

extern CInterfaces* Interfaces;

#undef INTERFACES_INTERNAL