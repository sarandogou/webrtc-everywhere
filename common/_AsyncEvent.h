/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_COMMON_ASYNCEVENTDISPATCHER_H_
#define _WEBRTC_EVERYWHERE_COMMON_ASYNCEVENTDISPATCHER_H_

#include "_Config.h"
#include "_Common.h"

#include "webrtc/system_wrappers/interface/critical_section_wrapper.h"

#include <map>

#if WE_UNDER_WINDOWS
#	include <comutil.h>
#endif

#if !defined(WM_USER)
#define WM_USER 0x0400
#endif
#define WM_SUCCESS						(WM_USER + 101)
#define WM_ERROR						(WM_SUCCESS + 1)
#define WM_GETUSERMEDIA_SUCESS			(WM_ERROR + 1)
#define WM_GETUSERMEDIA_ERROR			(WM_GETUSERMEDIA_SUCESS + 1)
#define WM_CREATEOFFER_SUCCESS			(WM_GETUSERMEDIA_ERROR + 1)
#define WM_CREATEOFFER_ERROR			(WM_CREATEOFFER_SUCCESS + 1)
#define WM_INVALIDATE_WINDOLESS			(WM_CREATEOFFER_ERROR + 1)
#define WM_ONNEGOTIATIONNEEDED			(WM_INVALIDATE_WINDOLESS + 1)
#define WM_ONICECANDIDATE				(WM_ONNEGOTIATIONNEEDED + 1)
#define WM_ONSIGNALINGSTATECHANGE		(WM_ONICECANDIDATE + 1)
#define WM_ONADDSTREAM					(WM_ONSIGNALINGSTATECHANGE + 1)
#define WM_ONREMOVESTREAM				(WM_ONADDSTREAM + 1)
#define WM_ONICECONNECTIONSTATECHANGE	(WM_ONREMOVESTREAM + 1)


class WEBRTC_EVERYWHERE_API _AsyncEventDispatcher : public _BrowserObject
{
protected:
	_AsyncEventDispatcher();
public:
	virtual ~_AsyncEventDispatcher();
	bool SetWindow(HWND hWnd, bool bSubClass = true);
	LONGLONG GetWindowHandle();
	bool RaiseCallback(_BrowserCallback* cb);

private:
	HWND m_Hwnd;
#if WE_UNDER_WINDOWS
	WNDPROC m_Proc;
#endif
};

class WEBRTC_EVERYWHERE_API _AsyncEventRaiser
{
protected:
	_AsyncEventRaiser();
public:
	virtual ~_AsyncEventRaiser();
	void SetDispatcher(_AsyncEventDispatcher* dispatcher);
	bool RaiseCallback(_BrowserCallback* cb);
	WE_INLINE const _AsyncEventDispatcher* GetDispatcher() { return m_pDispatcher; }

private:
	_AsyncEventDispatcher* m_pDispatcher;
};

#if 0

class WEBRTC_EVERYWHERE_API _AsyncEventToken
{
protected:
	_AsyncEventToken();
public:
	virtual ~_AsyncEventToken();
	bool AddCallback(std::string id, _BrowserCallback** cb)const;
	WE_INLINE std::string id()const { return m_id; }

private:
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	std::string m_id;
#if _MSC_VER
#pragma warning(pop)
#endif
};

class WEBRTC_EVERYWHERE_API _AsyncEventHolder
{
public:
	virtual ~_AsyncEventHolder() {}
	static bool Add(const _AsyncEventToken* token, std::string id, _BrowserCallback** cb);
	static _BrowserCallback* Get(const _AsyncEventToken* token, std::string id);
	static _BrowserCallback* Pop(const _AsyncEventToken* token, std::string id);
	static bool Remove(const _AsyncEventToken* token, std::string id);
	static bool Clear();

private:
	static std::string BuildUniqueId(const _AsyncEventToken* token, std::string id);

private:
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	static std::map<std::string, _BrowserCallback*> s_callbacks;
	static webrtc::CriticalSectionWrapper *s_critsect;
#if _MSC_VER
#pragma warning(pop)
#endif
};
#endif

#endif /* _WEBRTC_EVERYWHERE_COMMON_ASYNCEVENTDISPATCHER_H_ */
