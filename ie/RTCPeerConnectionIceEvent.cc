/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */


// RTCPeerConnectionIceEvent.cc : Implementation of CRTCPeerConnectionIceEvent

#include "stdafx.h"
#include "RTCIceCandidate.h"
#include "RTCPeerConnectionIceEvent.h"
#include "Utils.h"

#include "../common/_Debug.h"

CRTCPeerConnectionIceEvent::CRTCPeerConnectionIceEvent()
	: m_Event(nullptr)
{
}

HRESULT CRTCPeerConnectionIceEvent::FinalConstruct()
{
	return S_OK;
}

void CRTCPeerConnectionIceEvent::FinalRelease()
{
	m_Event = nullptr;
}

void CRTCPeerConnectionIceEvent::SetEvent(std::shared_ptr<_RTCPeerConnectionIceEvent> & e)
{
	m_Event = e;
}

std::shared_ptr<_RTCPeerConnectionIceEvent> CRTCPeerConnectionIceEvent::GetEvent()
{
	return m_Event;
}


STDMETHODIMP CRTCPeerConnectionIceEvent::get_candidate(__out VARIANT* pVal)
{
	if (!m_Event || !m_Event->candidate) {
		CComVariant(NULL).Detach(pVal);
		return S_OK;
	}

	CComObject<CRTCIceCandidate>* _candidate;
	HRESULT _hr = Utils::CreateInstanceWithRef(&_candidate);
	CHECK_HR_RETURN(_hr);
	_candidate->SetCandidate(m_Event->candidate);
	_hr = CComVariant(_candidate).Detach(pVal);
	SafeRelease(&_candidate);
	return _hr;
}
