#include "hack_core.h"
#include <interfaces.h>
#include <tools/logger.h>
#include <hook/hooks_manager.h>

#include <tools/render_tool.h>

#include <stdio.h>
#include <intrin.h>

CHackCore* HackCore = new CHackCore();

void CHackCore::init(void* dll)
{
	this->dll = dll;

//#ifdef _DEBUG
	AllocConsole();
	freopen("CONOUT$", "wb", stdout);
	freopen("CONOUT$", "wb", stderr);
	freopen("CONIN$", "rb", stdin);
//#endif

	Interfaces->init();

//#ifdef _DEBUG
	Logger->init();
//#else
	//Logger->init(LoggerMethod::game_method);
//#endif

	Interfaces->print_interfaces();

	if (!HooksManager->init())
		Logger->error("Hooks init error!");

	render_tool->init(Interfaces->directx_device);
}
