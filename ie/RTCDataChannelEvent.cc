/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#idl-def-RTCDataChannelEvent

#include "stdafx.h"
#include "RTCDataChannelEvent.h"
#include "Utils.h"
#include "RTCDataChannel.h"

#include "../common/_Debug.h"


CRTCDataChannelEvent::CRTCDataChannelEvent()
{
}

HRESULT CRTCDataChannelEvent::FinalConstruct()
{
	return S_OK;
}

void CRTCDataChannelEvent::FinalRelease()
{
	m_Event = nullptr;

	SetDispatcher(NULL);
}

STDMETHODIMP CRTCDataChannelEvent::get_channel(VARIANT* pVal)
{
	if (!m_Event) {
		*pVal = CComVariant(NULL);
		return S_OK;
	}

	CComObject<CRTCDataChannel>* _channel;
	CHECK_HR_RETURN(Utils::CreateInstanceWithRef(&_channel));
	_channel->SetChannel(m_Event->channel);
	_channel->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
	*pVal = CComVariant(_channel);
	return S_OK;
}