#pragma once

#include "../common/_Config.h"
#include "../common/_Common.h"

#if WE_UNDER_WINDOWS
#	include <atlbase.h>
#	include <atlcom.h>
#	include <atlctl.h>
#endif

class _AsyncEventToken;

class BrowserCallback
	: public _BrowserCallback
{
public:
	BrowserCallback(unsigned msgid, CComPtr<IDispatch> disp);
	virtual ~BrowserCallback();
	
	BrowserObjectImpl_Inline();

	HRESULT AddDispatch(CComPtr<IDispatch> obj);
	HRESULT AddBSTR(const CComBSTR& bstr);

	// _BrowserCallback implementation
	virtual bool Invoke();

private:
	CComPtr<IDispatch> m_disp;
	unsigned m_params_count;
	CComVariant m_params[kMaxParamArgs];
};
