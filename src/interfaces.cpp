#include "interfaces.h"
#include <tools/logger.h>

CInterfaces* Interfaces = new CInterfaces();

static inline void print_interface(const std::string& name, DWORD address) { Logger->message(std::string(name + "\t") + std::to_string(address)); }


void CInterfaces::init()
{
	INIT_INTERFACE(client, VClient, "client.dll", "VClient017");
	INIT_INTERFACE(entity_list, VClientEntityList, "client.dll", "VClientEntityList003");

	INIT_INTERFACE(engine, VEngineClient, "engine.dll", "VEngineClient015");
	INIT_INTERFACE(render_view, VEngineRenderView, "engine.dll", "VEngineRenderView014");
	INIT_INTERFACE(model_render, IVModelRender, "engine.dll", "VEngineModel016");
	INIT_INTERFACE(engine_trace, IEngineTrace, "engine.dll", "EngineTraceClient003");

	INIT_INTERFACE(material_system, IMaterialSystem, "materialsystem.dll", "VMaterialSystem080");

	INIT_INTERFACE(surface, ISurface, "vguimatsurface", "VGUI_Surface030");

	INIT_INTERFACE(lua_shared, LUA::Shared, "lua_shared.dll", "LUASHARED003");

	do { this->client_mode = **(IClientMode***)((*(uintptr_t**)this->client)[10] + 0x5); } while (!this->client_mode);

	directx_device = **(IDirect3DDevice9***)(MemTools::pattern_scaner("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);

	view_render = **(IViewRender***)((*(uintptr_t**)client)[27] + 0x5);

	render = **(IRender***)((*(uintptr_t**)render_view)[12] + 0x5);

	render_context = material_system->GetRenderContext();
}

void CInterfaces::print_interfaces()
{
	print_interface("Client", (DWORD)client);
	print_interface("ClientMode", (DWORD)client_mode);
	print_interface("ClientEntityList", (DWORD)entity_list);
	print_interface("ViewRender", (DWORD)view_render);

	print_interface("Engine", (DWORD)engine);
	print_interface("RenderView", (DWORD)render_view);
	print_interface("IRender", (DWORD)render);
	print_interface("ITrace", (DWORD)engine_trace);

	print_interface("Direct3DDevice", (DWORD)directx_device);

	print_interface("MaterialSystem", (DWORD)material_system);

	print_interface("Surface", (DWORD)surface);
}
