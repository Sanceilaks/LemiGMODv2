#include "reset_hook.h"
#include <hook/hooks_manager.h>

#include <imgui/imgui.h>
#include <imgui/impl/imgui_impl_dx9.h>

long __stdcall reset_hook::hook(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    auto ret = HooksManager->reset_original(device, pPresentationParameters);

    ImGui_ImplDX9_InvalidateDeviceObjects();

    if (ret > 0)
        ImGui_ImplDX9_CreateDeviceObjects();

    return ret;
}
