/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */

// http://www.w3.org/TR/webrtc/#rtcstats-dictionary

#include "stdafx.h"
#include "RTCStats.h"
#include "Utils.h"
#include "WebRTC.h"

#include "../common/_Debug.h"

CRTCStats::CRTCStats()
	: m_Stats(nullptr)
{
}

HRESULT CRTCStats::FinalConstruct()
{
	return S_OK;
}

void CRTCStats::FinalRelease()
{
	m_Stats = nullptr;
}

STDMETHODIMP CRTCStats::get_timestamp(__out DOUBLE* pVal)
{
	*pVal = m_Stats ? m_Stats->timestamp : 0.0;
	return S_OK;
}

STDMETHODIMP CRTCStats::get_type(__out BSTR* pVal)
{
	if (!m_Stats) {
		*pVal = CComBSTR(NULL).Detach();
		return S_OK;
	}
	return Utils::CopyAnsiString(m_Stats->type, pVal);
}

STDMETHODIMP CRTCStats::get_id(__out BSTR* pVal)
{
	if (!m_Stats) {
		*pVal = CComBSTR(NULL).Detach();
		return S_OK;
	}
	return Utils::CopyAnsiString(m_Stats->id, pVal);
}

STDMETHODIMP CRTCStats::names(__out VARIANT* Names)
{
	if (!m_Stats) {
		return CComVariant(NULL).Detach(Names);
	}

	HRESULT hr;
	CComPtr<CWebRTC> pluginInstance = dynamic_cast<CWebRTC*>(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
	if (!pluginInstance) {
		CHECK_HR_RETURN(E_POINTER);
	}

	CComPtr<IDispatch> spDispatch;
	CHECK_HR_RETURN(hr = pluginInstance->GetDispatch(spDispatch));

	std::vector<CComVariant> vect;
	std::map<std::string, std::string>::iterator it = m_Stats->names.begin();
	for (; it != m_Stats->names.end(); ++it) {
		vect.push_back(CComBSTR((*it).first.c_str()));
	}

	CComQIPtr<IDispatchEx> spArray;
	CHECK_HR_RETURN(hr = Utils::CreateJsArray(spDispatch, vect, spArray));
	*Names = CComVariant(spArray.Detach());

	return hr;
}

STDMETHODIMP CRTCStats::stat(__in BSTR name, __out BSTR* pVal)
{
	if (!m_Stats) {
		*pVal = CComBSTR(NULL).Detach();
		return S_OK;
	}
	char* lpszName = _com_util::ConvertBSTRToString(name);
	if (!lpszName) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}
	std::map<std::string, std::string>::iterator it = m_Stats->names.find(std::string(lpszName));
	delete[]lpszName;
	if (it != m_Stats->names.end()) {
		return Utils::CopyAnsiString((*it).second, pVal);
	}
	else {
		*pVal = CComBSTR(NULL).Detach();
		return S_OK;
	}
}