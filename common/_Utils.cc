/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#include "_Utils.h"
#include "_RTCDisplay.h"
#include "_AsyncEvent.h"
#include "_Debug.h"
#include "_Common.h"

#if WE_UNDER_WINDOWS
#	include "windows.h"
#	include <comutil.h>
#	include "talk/base/win32socketinit.h"
#endif

#include "talk/base/ssladapter.h"
#include "talk/base/thread.h"

static bool g_bInitialized = false;
#if WE_UNDER_WINDOWS
static bool g_winCoInitialize = false;
#endif

webrtc::CriticalSectionWrapper* _Utils::s_unique_objs_cs = webrtc::CriticalSectionWrapper::CreateCriticalSection();
std::map<long, const _UniqueObject*> _Utils::s_unique_objs;

_Utils::_Utils()
{

}

_Utils::~_Utils()
{

}

WeError _Utils::Initialize(WeError(*InitializeAdditionals) (void) /*= NULL*/)
{
    if(!g_bInitialized) {
#if 0
        StartDebug();
#endif

#if WE_UNDER_WINDOWS
		HRESULT hr = E_FAIL; // CoInitializeEx(NULL, COINIT_MULTITHREADED);
		g_winCoInitialize = SUCCEEDED(hr);
		talk_base::EnsureWinsockInit();
#if 0
		static talk_base::Thread w32_thread;
		talk_base::ThreadManager::Instance()->SetCurrentThread(&w32_thread);
#endif
#endif
		talk_base::InitializeSSL();
		talk_base::InitializeSSLThread();
        g_bInitialized = true;
    }
	if (InitializeAdditionals) {
		return InitializeAdditionals();
	}
    return WeError_Success;
}

WeError _Utils::DeInitialize(void)
{
	if (g_bInitialized) {
		talk_base::CleanupSSL();
		g_bInitialized = false;
#if WE_UNDER_WINDOWS
		if (g_winCoInitialize) {
			CoUninitialize();
		}
#endif
	}
	return WeError_Success;
}

WeError _Utils::StartDebug(void)
{
#if WE_UNDER_WINDOWS
    if (AllocConsole()) {
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
        SetConsoleTitleA("WebRTC extension for Safari, Opera, FireFox and IE");
        return WeError_Success;
    }
    return WeError_OutOfMemory;
#else
    return WeError_Success;
#endif
}

WeError _Utils::StopDebug(void)
{
#if WE_UNDER_WINDOWS
    return (FreeConsole() == TRUE) ? WeError_Success : WeError_System;
#else
    return WeError_Success;
#endif
}

std::string _Utils::ToString(long val)
{
	char str[22];
	sprintf(str, "%ld", val);
	return std::string(str);
}

class _NPAsyncData {
public:
	_NPAsyncData(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
		: hWnd(_hWnd)
		, uMsg(_uMsg)
		, wParam(_wParam)
		, lParam(_lParam)
	{}
	HWND hWnd;
	UINT uMsg;
	WPARAM wParam;
	LPARAM lParam;
};
static void _NPWndProc(void *npdata)
{
	_NPAsyncData* _npdata = reinterpret_cast<_NPAsyncData*>(npdata);
	_Utils::WndProc(_npdata->hWnd, _npdata->uMsg, _npdata->wParam, _npdata->lParam);
	delete _npdata;
}

bool _Utils::RaiseCallback(LONGLONG handle, _BrowserCallback* cb)
{
	if (!cb) {
		return false;
	}
	HWND hWnd = reinterpret_cast<HWND>(handle);
	bool ret = false;
	
	// retain() callback object
	cb->RetainObject();

#if WE_UNDER_WINDOWS
	if (hWnd) {
		ret = (PostMessage(hWnd, cb->GetMsgId(), reinterpret_cast<WPARAM>(cb), NULL) == TRUE);
	}
	else {
		WE_DEBUG_WARN("Not handle associated to the window yet");
		_Utils::WndProc(hWnd, cb->GetMsgId(), reinterpret_cast<WPARAM>(cb), NULL);
		ret = true;
	}
#elif WE_UNDER_APPLE
	_NPAsyncData* _npdata = new _NPAsyncData(hWnd, cb->GetMsgId(), reinterpret_cast<WPARAM>(cb), NULL);
	if (_npdata) {
		dispatch_async(dispatch_get_main_queue(), ^{
			_NPWndProc(_npdata);
		});
		ret = true;
	}
#else
#error "Not implemented"
#endif

	// release() callback object
	if (ret) {
		// all is ok -> object will be freed by the async functin
	}
	else {
		cb->ReleaseObject();
	}
	return ret;
}

LRESULT CALLBACK _Utils::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
#if		WE_UNDER_WINDOWS
		case WM_PAINT:
		{
			_RTCDisplay* display = dynamic_cast<_RTCDisplay*>(reinterpret_cast<_RTCDisplay*>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
			if (display && display->PaintFrame()) {
				return 0;
			}
			else {
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);

				RECT rc;
				GetClientRect(hWnd, &rc);
				// Set Clip region to the rectangle specified by di.prcBounds
				HRGN hRgnOld = NULL;
				if (GetClipRgn(hdc, hRgnOld) != 1) {
					hRgnOld = NULL;
				}
				bool bSelectOldRgn = false;

				HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

				if (hRgnNew != NULL) {
					bSelectOldRgn = (SelectClipRgn(hdc, hRgnNew) != ERROR);
				}

				Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
				SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
				LPCTSTR pszText = TEXT("ATL 8.0 : WebRTC Plugin");
#ifndef _WIN32_WCE
				TextOut(hdc,
					(rc.left + rc.right) / 2,
					(rc.top + rc.bottom) / 2,
					pszText,
					lstrlen(pszText));
#else
				ExtTextOut(hdc,
					(rc.left + rc.right) / 2,
					(rc.top + rc.bottom) / 2,
					ETO_OPAQUE,
					NULL,
					pszText,
					ATL::lstrlen(pszText),
					NULL);
#endif

				if (bSelectOldRgn) {
					SelectClipRgn(hdc, hRgnOld);
				}

				EndPaint(hWnd, &ps);
			}
			break;
		}
#endif /* WE_UNDER_WINDOWS */

		case WM_SUCCESS:
		case WM_ERROR:
		case WM_GETUSERMEDIA_SUCESS:
		case WM_GETUSERMEDIA_ERROR:
		case WM_CREATEOFFER_SUCCESS:
		case WM_CREATEOFFER_ERROR:
		case WM_ONNEGOTIATIONNEEDED:
		case WM_ONICECANDIDATE:
		case WM_ONSIGNALINGSTATECHANGE:
		case WM_ONADDSTREAM:
		case WM_ONREMOVESTREAM:
		case WM_ONICECONNECTIONSTATECHANGE:
		{
			_BrowserCallback* _cb = reinterpret_cast<_BrowserCallback*>(wParam);
			if (_cb) {
				_cb->Invoke();
				_cb->ReleaseObject();
			}
			break;
		}
	}

#if WE_UNDER_WINDOWS
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
#else
	return 0;
#endif /* WE_UNDER_WINDOWS */
}

long _Utils::UniqueId()
{
    static long __unique_id = 1;
    
    _Utils::s_unique_objs_cs->Enter();
    long _id = __unique_id++;
    _Utils::s_unique_objs_cs->Leave();
    
    return _id;
}

const _UniqueObject* _Utils::UniqueObjFind(long id)
{
    const _UniqueObject* obj = NULL;
    _Utils::s_unique_objs_cs->Enter();
    std::map<long, const _UniqueObject*>::iterator it = _Utils::s_unique_objs.find(id);
    if (it != _Utils::s_unique_objs.end()) {
        obj = (*it).second;
    }
    _Utils::s_unique_objs_cs->Leave();
    return obj;
}

void _Utils::UniqueObjAdd(const _UniqueObject* obj)
{
    _Utils::s_unique_objs_cs->Enter();
    if (obj) {
        _Utils::s_unique_objs[obj->UniqueId()] = obj;
    }
    _Utils::s_unique_objs_cs->Leave();
}

void _Utils::UniqueObjRemove(long id)
{
    _Utils::s_unique_objs_cs->Enter();
    _Utils::s_unique_objs.erase(id);
    _Utils::s_unique_objs_cs->Leave();
}
