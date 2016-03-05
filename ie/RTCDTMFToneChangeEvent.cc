/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#idl-def-RTCDTMFToneChangeEvent

#include "stdafx.h"
#include "RTCDTMFToneChangeEvent.h"
#include "Utils.h"

#include "../common/_Debug.h"

CRTCDTMFToneChangeEvent::CRTCDTMFToneChangeEvent()
{
}

HRESULT CRTCDTMFToneChangeEvent::FinalConstruct()
{
	return S_OK;
}

void CRTCDTMFToneChangeEvent::FinalRelease()
{
	m_Event = nullptr;
}

STDMETHODIMP CRTCDTMFToneChangeEvent::get_tone(BSTR* pVal)
{
	if (!m_Event) {
		*pVal = CComBSTR(NULL).Detach();
		return S_OK;
	}
	return Utils::CopyAnsiString(m_Event->tone, pVal);
}
