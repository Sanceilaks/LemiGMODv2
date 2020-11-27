#include "end_scane_hook.h"
#include <hook/hooks_manager.h>

#include <imgui/imgui.h>
#include <imgui/impl/imgui_impl_win32.h>
#include <imgui/impl/imgui_impl_dx9.h>

#include <tools/render_tool.h>

#include <globals.h>
#include <features/menu/menu.h>

static bool is_init = false;
static WNDPROC wnd_proc = nullptr;

LRESULT STDMETHODCALLTYPE my_wndproc(HWND window, UINT message_type, WPARAM w_param, LPARAM l_param)
{
    if (message_type == WM_KEYDOWN)
    {
        if (w_param == VK_INSERT)
            Menu->is_open = !Menu->is_open;


        Globals->win_buttons[w_param] = true;
    }
    else if (message_type == WM_KEYUP)
    {
        Globals->win_buttons[w_param] = false;
    }

    if (ImGui_ImplWin32_WndProcHandler(window, message_type, w_param, l_param) && Menu->is_open)
    {
        return true;
    }

    return CallWindowProc(wnd_proc, window, message_type, w_param, l_param);
}

void init(IDirect3DDevice9* device)
{
    ImGui::CreateContext();

    auto game_hwnd = FindWindowW(L"Valve001", nullptr);
    if (game_hwnd != NULL)
    {
        ImGui_ImplWin32_Init(game_hwnd);
        ImGui_ImplDX9_Init(device);

        ImGui::GetIO().IniFilename = nullptr;
        ImGui::StyleColorsDark();

        memset(Globals->win_buttons, false, 1032 * sizeof(bool));

        wnd_proc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(game_hwnd, GWLP_WNDPROC, LONG_PTR(my_wndproc)));

        RenderTool->init(device);

        RenderTool->create_im_font(Menu->menu_font, "C:\\Windows\\Fonts\\Corbel.ttf", 30);
       
        Interfaces->engine->get_screen_size(Globals->screen_width, Globals->screen_height);

        is_init = true;
    }
}

long __stdcall end_scane_hook::hook(IDirect3DDevice9* device)
{
    auto ret = HooksManager->end_scane_original(device);

    int w, h;

    Interfaces->engine->get_screen_size(w, h);

    if (w != Globals->screen_width || h != Globals->screen_height)
        RenderTool->init(device);

    Globals->screen_width = w;
    Globals->screen_height = h;


    if (!is_init)
        init(device);

    IDirect3DStateBlock9* pixel_state = NULL;
    IDirect3DVertexDeclaration9* vertex_declaration;
    IDirect3DVertexShader9* vertex_shader;


    device->CreateStateBlock(D3DSBT_PIXELSTATE, &pixel_state);
    device->GetVertexDeclaration(&vertex_declaration);
    device->GetVertexShader(&vertex_shader);

    device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
	
    RenderTool->render_frame();

    pixel_state->Apply();
    pixel_state->Release();
    device->SetVertexDeclaration(vertex_declaration);
    device->SetVertexShader(vertex_shader);
	
    return ret;
}
