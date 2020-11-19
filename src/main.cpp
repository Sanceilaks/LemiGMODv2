#include <Windows.h>
#include <hack_core.h>

bool before_inject(void* dll)
{
	return true;
}

void init(void* dll)
{
	HackCore->init(dll);
}


BOOL WINAPI DllMain(HINSTANCE dll, DWORD reason, LPVOID lp_reserved)
{
	DisableThreadLibraryCalls(dll);

	if (reason == DLL_PROCESS_ATTACH && before_inject(dll))
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)init, dll, NULL, NULL);
	return TRUE;
}