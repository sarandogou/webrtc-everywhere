/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Config.h"
#include "../common/_Utils.h"

#	include <comutil.h>
#include <Windows.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
#if 1
    switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
	{
		//CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
		_Utils::Initialize();
		break;
	}
	case DLL_PROCESS_DETACH:
	{
		_Utils::DeInitialize();
		//CoUninitialize();
		break;
	}
	case DLL_THREAD_ATTACH:
	{
		break;
	}
	case DLL_THREAD_DETACH:
	{
		break;
	}
    }
#endif
    return TRUE;
}

