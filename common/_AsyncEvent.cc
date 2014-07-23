/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */

#include "_AsyncEvent.h"
#include "_Utils.h"
#include "_Debug.h"

//
// _AsyncEventDispatcher
//

_AsyncEventDispatcher::_AsyncEventDispatcher()
	: m_Hwnd(NULL)
#if WE_UNDER_WINDOWS
	, m_Proc(NULL)
#endif
{

}

_AsyncEventDispatcher::~_AsyncEventDispatcher()
{
	SetWindow(NULL, false);
}

bool _AsyncEventDispatcher::SetWindow(HWND hWnd, bool bSubClass /*= true*/)
{
#if WE_UNDER_WINDOWS
	if (m_Hwnd && m_Proc) {
		SetWindowLongPtr(m_Hwnd, GWL_WNDPROC, (LONG)m_Proc);
		// SetWindowLongPtr(m_Hwnd, DWLP_USER, (LONG)NULL);
		m_Proc = NULL;
	}

	if ((m_Hwnd = hWnd)) {
		if (bSubClass) {
			m_Proc = (WNDPROC)SetWindowLongPtr(m_Hwnd, GWL_WNDPROC, (LONG)_Utils::WndProc);
			if (!m_Proc) {
				WE_DEBUG_ERROR("SetWindowLongPtr() failed with errcode=%d", GetLastError());
				return false;
			}
			// SetWindowLongPtr(m_Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
		}
	}
#endif

	return true;
}

LONGLONG _AsyncEventDispatcher::GetWindowHandle()
{
	return reinterpret_cast<LONGLONG>(m_Hwnd);
}

bool _AsyncEventDispatcher::RaiseCallback(_BrowserCallback* cb)
{
	return _Utils::RaiseCallback(GetWindowHandle(), cb);
}

//
//	_AsyncEventRaiser
//

_AsyncEventRaiser::_AsyncEventRaiser()
	: m_pDispatcher(NULL)
{

}

_AsyncEventRaiser::~_AsyncEventRaiser()
{
	SetDispatcher(NULL);
}
	
void _AsyncEventRaiser::SetDispatcher(_AsyncEventDispatcher* dispatcher)
{
	if (m_pDispatcher) {
		m_pDispatcher->ReleaseObject();
		m_pDispatcher = NULL;
	}
	if (dispatcher) {
		m_pDispatcher = dynamic_cast<_AsyncEventDispatcher*>(dispatcher->RetainObject());
	}
}

bool _AsyncEventRaiser::RaiseCallback(_BrowserCallback* cb)
{
	assert(m_pDispatcher != NULL);
	return m_pDispatcher->RaiseCallback(cb);
}

#if 0
//
// _AsyncEventToken
//
_AsyncEventToken::_AsyncEventToken()
{
	static long __id = 1;

	m_id = _Utils::ToString(we_atomic_inc(&__id));
}

_AsyncEventToken::~_AsyncEventToken()
{

}

bool _AsyncEventToken::AddCallback(std::string id, _BrowserCallback** cb)const
{
	return _AsyncEventHolder::Add(this, "callback_getUserMediaSuccess", cb);
}



//
//	_AsyncEventHolder
//

webrtc::CriticalSectionWrapper* _AsyncEventHolder::s_critsect = webrtc::CriticalSectionWrapper::CreateCriticalSection();
std::map<std::string, _BrowserCallback*> _AsyncEventHolder::s_callbacks;

bool _AsyncEventHolder::Add(const _AsyncEventToken* token, std::string _id, _BrowserCallback** cb)
{
	std::string id = BuildUniqueId(token, _id);
	s_critsect->Enter();
	std::map<std::string, _BrowserCallback*>::iterator it = s_callbacks.find(id);
	if (it != s_callbacks.end()) {
		if (it->second) {
			delete it->second;
		}
		s_callbacks.erase(it);
	}
	s_callbacks[id] = *cb;
	*cb = NULL;
	s_critsect->Leave();
	return true;
}

_BrowserCallback* _AsyncEventHolder::Get(const _AsyncEventToken* token, std::string _id)
{
	std::string id = BuildUniqueId(token, _id);
	_BrowserCallback* ret = NULL;
	s_critsect->Enter();
	std::map<std::string, _BrowserCallback*>::iterator it = s_callbacks.find(id);
	if (it != s_callbacks.end()) {
		ret = it->second;
	}
	s_critsect->Leave();
	return ret;
}

_BrowserCallback* _AsyncEventHolder::Pop(const _AsyncEventToken* token, std::string _id)
{
	std::string id = BuildUniqueId(token, _id);
	_BrowserCallback* ret = NULL;
	s_critsect->Enter();
	std::map<std::string, _BrowserCallback*>::iterator it = s_callbacks.find(id);
	if (it != s_callbacks.end()) {
		ret = it->second;
		s_callbacks.erase(it);
	}
	s_critsect->Leave();
	return ret;
}

bool _AsyncEventHolder::Remove(const _AsyncEventToken* token, std::string _id)
{
	std::string id = BuildUniqueId(token, _id);
	s_critsect->Enter();
	std::map<std::string, _BrowserCallback*>::iterator it = s_callbacks.find(id);
	if (it != s_callbacks.end()) {
		if (it->second) {
			delete it->second;
		}
		s_callbacks.erase(it);
	}
	s_critsect->Leave();
	return true;
}

bool _AsyncEventHolder::Clear()
{
	s_critsect->Enter();
	std::map<std::string, _BrowserCallback*>::iterator it = s_callbacks.begin();
	for (; it != s_callbacks.end(); ++it) {
		if (it->second) {
			delete it->second;
		}
	}
	s_callbacks.clear();
	s_critsect->Leave();
	return true;
}

std::string _AsyncEventHolder::BuildUniqueId(const _AsyncEventToken* token, std::string id)
{
	return token->id() + std::string("_") + id;
}
#endif