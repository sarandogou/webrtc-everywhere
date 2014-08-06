/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */

// http://www.w3.org/TR/webrtc/#idl-def-MediaStreamEvent

#include "stdafx.h"
#include "MediaStreamEvent.h"
#include "MediaStream.h"
#include "Utils.h"

#include "../common/_Debug.h"


CMediaStreamEvent::CMediaStreamEvent()
	: m_Event(nullptr)
{
}

HRESULT CMediaStreamEvent::FinalConstruct()
{
	return S_OK;
}

void CMediaStreamEvent::FinalRelease()
{
	m_Event = nullptr;
	SetDispatcher(NULL);
}

void CMediaStreamEvent::SetEvent(std::shared_ptr<_MediaStreamEvent> & e)
{
	m_Event = e;
}

std::shared_ptr<_MediaStreamEvent> CMediaStreamEvent::GetEvent()
{
	return m_Event;
}

STDMETHODIMP CMediaStreamEvent::get_stream(__out VARIANT* pVal)
{
	if (!m_Event) {
		CHECK_HR_RETURN(E_POINTER);
	}
	if (!m_Event->stream) {
		return CComVariant(NULL).Detach(pVal);
	}

	CComObject<CMediaStream>* _stream;
	HRESULT _hr = Utils::CreateInstanceWithRef(&_stream);
	CHECK_HR_RETURN(_hr);
	_stream->SetStream(m_Event->stream);
	_hr = CComVariant(_stream).Detach(pVal);
	SafeRelease(&_stream);
	return _hr;
}