/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "BrowserCallback.h"
#include "../common/_AsyncEvent.h"
#include "../common/_Debug.h"

BrowserCallback::BrowserCallback(unsigned msgid, CComPtr<IDispatch> disp)
	: _BrowserCallback(msgid)
	, m_disp(disp)
	, m_params_count(0)
{
	
}

BrowserCallback::~BrowserCallback()
{
	m_disp = NULL;
	for (unsigned i = 0; i < m_params_count; ++i) {
		m_params[i].Clear();
	}
	WE_DEBUG_INFO("BrowserCallback::~BrowserCallback");
}

HRESULT BrowserCallback::AddDispatch(CComPtr<IDispatch> obj)
{
	if ((m_params_count + 1) >= kMaxParamArgs) {
		return E_BOUNDS;
	}
	m_params[m_params_count++] = obj;
	return S_OK;
}

HRESULT BrowserCallback::AddBSTR(const CComBSTR& bstr)
{
	if ((m_params_count + 1) >= kMaxParamArgs) {
		return E_BOUNDS;
	}
	m_params[m_params_count++] = bstr;
	return S_OK;
}

// _BrowserCallback implementation
bool BrowserCallback::Invoke()
{
	if (!m_disp) {
		WE_DEBUG_ERROR("No dispatcher");
		return false;
	}
	
	DISPPARAMS params = { m_params, NULL, m_params_count, 0 };
	HRESULT hr = m_disp->Invoke(0,
		IID_NULL,
		LOCALE_USER_DEFAULT,
		DISPATCH_METHOD,
		&params, NULL, NULL, NULL);
	return SUCCEEDED(hr);
}
