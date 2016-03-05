/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "stdafx.h"
#include "resource.h"
#include "webrtceverywhere_i.h"
#include "dllmain.h"

CwebrtceverywhereModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
#if 0
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
	{
		_Utils::Initialize();
		break;
	}
	case DLL_PROCESS_DETACH:
	{
		_Utils::DeInitialize();
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
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved);
}
