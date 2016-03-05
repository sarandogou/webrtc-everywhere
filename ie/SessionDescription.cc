/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */

// http://www.w3.org/TR/webrtc/#session-description-model

#include "stdafx.h"
#include "SessionDescription.h"
#include "Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"

#include <comutil.h>
#include <stdio.h>
#include <atlcom.h>

CSessionDescription::CSessionDescription()
	: m_Sdp(NULL)
{

}

HRESULT CSessionDescription::FinalConstruct()
{
	return S_OK;
}

void CSessionDescription::FinalRelease()
{
	m_Sdp = NULL;
}

HRESULT CSessionDescription::Init(VARIANT RTCSessionDescriptionInit)
{
	CComPtr<IDispatch>rtcSessionDescriptionInit = Utils::VariantToDispatch(RTCSessionDescriptionInit);
	if (!rtcSessionDescriptionInit) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}

	HRESULT hr;

	BSTR bstrType;
	CHECK_HR_RETURN(hr = Utils::DispatchGetPropBSTR(rtcSessionDescriptionInit, L"type", bstrType));
	BSTR bstrSdp;
	CHECK_HR_RETURN(hr = Utils::DispatchGetPropBSTR(rtcSessionDescriptionInit, L"sdp", bstrSdp));

	char* lpszType = _com_util::ConvertBSTRToString(bstrType);
	char* lpszSdp = _com_util::ConvertBSTRToString(bstrSdp);

	m_Sdp = std::make_shared<_SessionDescription>(
		lpszSdp,
		we_strlen(lpszSdp),
		lpszType,
		we_strlen(lpszType));
	if (lpszType) delete[] lpszType;
	if (lpszSdp) delete[] lpszSdp;

	return S_OK;
}

STDMETHODIMP CSessionDescription::get_type(__out BSTR* pVal)
{
	if (!m_Sdp) {
		CHECK_HR_RETURN(E_POINTER);
	}
	const _Buffer* pcType = m_Sdp->getType();
    if (pcType && pcType->getPtr()) {
		std::string type((const char*)pcType->getPtr(), pcType->getSize());
		return Utils::CopyAnsiString(type, pVal);
    }
    else {
        *pVal = NULL;
		return S_OK;
    }
}

STDMETHODIMP CSessionDescription::put_type(__in BSTR newVal)
{
	char* lpszType = _com_util::ConvertBSTRToString(newVal);
	if (!lpszType) {
		CHECK_HR_RETURN(E_OUTOFMEMORY);
	}
	const _Buffer* _sdp = m_Sdp ? m_Sdp->getSdp() : NULL;
	std::shared_ptr<_SessionDescription> newSdp = std::make_shared<_SessionDescription>(
		_sdp ? _sdp->getPtr() : NULL,
		_sdp ? _sdp->getSize() : 0,
		lpszType,
		we_strlen(lpszType));
	delete[] lpszType;
	m_Sdp = newSdp;
	return S_OK;
}

STDMETHODIMP CSessionDescription::get_sdp(__out BSTR* pVal)
{
	if (!m_Sdp) {
		CHECK_HR_RETURN(E_POINTER);
	}
	const _Buffer* pcSdp = m_Sdp->getSdp();
    if (pcSdp && pcSdp->getPtr()) {
		std::string sdp((const char*)pcSdp->getPtr(), pcSdp->getSize());
		return Utils::CopyAnsiString(sdp, pVal);
    }
    else {
        *pVal = NULL;
		return S_OK;
    }
}

STDMETHODIMP CSessionDescription::put_sdp(__in BSTR newVal)
{
	char* lpszSdp = _com_util::ConvertBSTRToString(newVal);
	if (!lpszSdp) {
		CHECK_HR_RETURN(E_OUTOFMEMORY);
	}
	const _Buffer* _type = m_Sdp ? m_Sdp->getType() : NULL;
	std::shared_ptr<_SessionDescription> newSdp = std::make_shared<_SessionDescription>(
		lpszSdp,
		we_strlen(lpszSdp),
		_type ? _type->getPtr() : NULL,
		_type ? _type->getSize() : 0);
	delete[] lpszSdp;
	m_Sdp = newSdp;
	return S_OK;
}

