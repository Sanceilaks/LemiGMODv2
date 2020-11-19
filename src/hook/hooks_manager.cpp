#include "hooks_manager.h"
#include <minhook/minhook.h>

CHooksManager* HooksManager = new CHooksManager();

static inline unsigned int get_virtual(void* _class, unsigned int index) { return static_cast<unsigned int>((*static_cast<int**>(_class))[index]); }

#define CREATE_TARGET(name, base, index) const auto name = reinterpret_cast<void*>(get_virtual(base, index));
#define ADD_HOOK(target, hook, original) if (MH_CreateHook(target, &hook, reinterpret_cast<void**>(&original)) != MH_OK) return false;

bool CHooksManager::init()
{
    CREATE_TARGET(create_move_target, Interfaces->client_mode, 21);
    CREATE_TARGET(view_render_target, Interfaces->client, 26);
    CREATE_TARGET(render_view_target, Interfaces->view_render, 6);

    CREATE_TARGET(end_scane_target, Interfaces->directx_device, 42);
    CREATE_TARGET(reset_target, Interfaces->directx_device, 16);
    
    CREATE_TARGET(lock_cursor_target, Interfaces->surface, 62);

    if (MH_Initialize() != MH_OK)
        return false;

    ADD_HOOK(create_move_target, create_move_hook::hook, create_move_original);
    ADD_HOOK(view_render_target, view_render_hook::hook, view_render_original);
    ADD_HOOK(render_view_target, render_view_hook::hook, render_view_original);

    ADD_HOOK(end_scane_target, end_scane_hook::hook, end_scane_original);
    ADD_HOOK(reset_target, reset_hook::hook, reset_original);

    ADD_HOOK(lock_cursor_target, i_surface_hooks::lock_cursor_hook::hook, lock_cursor_original);


    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
        return false;

    return true;
}

void CHooksManager::unhook()
{
    MH_Uninitialize();
    MH_DisableHook(MH_ALL_HOOKS);
}
