/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */


// http://www.w3.org/TR/webrtc/#rtcicecandidate-type

#include "stdafx.h"
#include "RTCIceCandidate.h"
#include "Utils.h"

#include "../common/_Debug.h"

CRTCIceCandidate::CRTCIceCandidate()
	: m_Candidate(nullptr)
{
}

HRESULT CRTCIceCandidate::FinalConstruct()
{
	return S_OK;
}

void CRTCIceCandidate::FinalRelease()
{
	m_Candidate = nullptr;
}

HRESULT CRTCIceCandidate::Init(VARIANT candidateInitDict)
{
	if (candidateInitDict.vt == VT_BSTR) {
		char* lpszCandidate = _com_util::ConvertBSTRToString(candidateInitDict.bstrVal);
		if (!lpszCandidate) {
			CHECK_HR_RETURN(E_INVALIDARG);
		}
		m_Candidate = std::make_shared<_RTCIceCandidate>(lpszCandidate);
		delete[]lpszCandidate;
	}
	else {
		CComPtr<IDispatch>_candidateInitDict = Utils::VariantToDispatch(candidateInitDict); // http://www.w3.org/TR/webrtc/#idl-def-RTCIceCandidateInit
		if (!_candidateInitDict) {
			CHECK_HR_RETURN(E_NOINTERFACE);
		}

		BSTR bstrCandidate;
		HRESULT hr = Utils::DispatchGetPropBSTR(_candidateInitDict, L"candidate", bstrCandidate);
		if (FAILED(hr)) {
			return hr;
		}
		BSTR bstrSdpMid;
		CHECK_HR_RETURN(hr = Utils::DispatchGetPropBSTR(_candidateInitDict, L"sdpMid", bstrSdpMid));

		long longSdpMLineIndex;
		CHECK_HR_RETURN(hr = Utils::DispatchGetPropInteger(_candidateInitDict, L"sdpMLineIndex", longSdpMLineIndex));

		char* lpszCandidate = _com_util::ConvertBSTRToString(bstrCandidate);
		char* lpszSdpMid = _com_util::ConvertBSTRToString(bstrSdpMid);
		m_Candidate = std::make_shared<_RTCIceCandidate>((lpszCandidate ? lpszCandidate : ""), (lpszSdpMid ? lpszSdpMid : ""), (unsigned short)longSdpMLineIndex);
		if (lpszCandidate) delete[]lpszCandidate;
		if (lpszSdpMid) delete[]lpszSdpMid;
	}

	return S_OK;
}

STDMETHODIMP CRTCIceCandidate::get_candidate(BSTR* pVal)
{
	if (!m_Candidate) {// NULL candidate used as hack to signal end of gathering
		*pVal = CComBSTR(NULL).Detach();
		return S_OK;
	}
	return Utils::CopyAnsiStr(m_Candidate->candidate(), pVal);
}

STDMETHODIMP CRTCIceCandidate::get_sdpMid(BSTR* pVal)
{
	if (!m_Candidate) {
		*pVal = CComBSTR(NULL).Detach();
		return S_OK;
	}
	return Utils::CopyAnsiStr(m_Candidate->sdpMid(), pVal);
}

STDMETHODIMP CRTCIceCandidate::get_sdpMLineIndex(USHORT* pVal)
{
	if (!m_Candidate) {
		*pVal = 0;
		return S_OK;
	}
	*pVal = m_Candidate->sdpMLineIndex();
	return S_OK;
}
