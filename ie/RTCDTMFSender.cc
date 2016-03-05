/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#rtcdtmfsender

#include "stdafx.h"
#include "RTCDTMFSender.h"
#include "MediaStreamTrack.h"
#include "BrowserCallback.h"
#include "RTCDTMFToneChangeEvent.h"
#include "Utils.h"

#include "../common/_Debug.h"

CRTCDTMFSender::CRTCDTMFSender()
	: m_Sender(nullptr)
	, m_callback_ontonechange(nullptr)
{
}

HRESULT CRTCDTMFSender::FinalConstruct()
{
	return S_OK;
}

void CRTCDTMFSender::FinalRelease()
{
	m_Sender = nullptr;

	SetDispatcher(NULL);
}

void CRTCDTMFSender::SetSender(std::shared_ptr<_RTCDTMFSender> & sender)
{
	if ((m_Sender = sender)) {
		m_Sender->ontonechangeSet(std::bind(&CRTCDTMFSender::ontonechange, this, std::placeholders::_1));
	}
}

std::shared_ptr<_RTCDTMFSender> CRTCDTMFSender::GetSender()
{
	return m_Sender;
}

STDMETHODIMP CRTCDTMFSender::get_canInsertDTMF(__out VARIANT_BOOL* pVal)
{
	if (!m_Sender) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = m_Sender->canInsertDTMF() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CRTCDTMFSender::insertDTMF(__in BSTR tones, __in_opt VARIANT duration /*= 100*/, __in_opt VARIANT interToneGap /*= 50*/)
{
	if (!m_Sender || !tones) {
		CHECK_HR_RETURN(E_POINTER);
	}
	long _duration = 100, _interToneGap = 50;
	if (Utils::VariantIsInteger(duration) || Utils::VariantIsBSTR(duration)) { // optional -> duration.vt == VT_ERROR
		Utils::VariantToInteger(duration, _duration);
	}
	if (Utils::VariantIsInteger(interToneGap) || Utils::VariantIsBSTR(interToneGap)) { // optional -> interToneGap.vt == VT_ERROR
		Utils::VariantToInteger(interToneGap, _interToneGap);
	}

	char *_tones = _com_util::ConvertBSTRToString(tones);
	if (!_tones) {
		CHECK_HR_RETURN(E_OUTOFMEMORY);
	}
	m_Sender->insertDTMF(_tones, _duration, _interToneGap);
	delete[] _tones;
	return S_OK;
}

STDMETHODIMP CRTCDTMFSender::get_track(__out VARIANT* pMediaStreamTrack)
{
	if (!m_Sender) {
		CHECK_HR_RETURN(E_POINTER);
	}
	std::shared_ptr<_MediaStreamTrack>track = m_Sender->track();
	if (track) {
		CComObject<CMediaStreamTrack>* _track;
		HRESULT hr = Utils::CreateInstanceWithRef(&_track);
		if (SUCCEEDED(hr)) {
			_track->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
			_track->SetTrack(track);
			*pMediaStreamTrack = CComVariant(_track);
		}
		return hr;
	}
	else {
		*pMediaStreamTrack = CComVariant(NULL);
		return S_OK;
	}
}

STDMETHODIMP CRTCDTMFSender::get_ontonechange(__out VARIANT* pVal)
{
	if (!m_Sender) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = CComVariant(m_callback_ontonechange);
	return S_OK;
}

STDMETHODIMP CRTCDTMFSender::put_ontonechange(__in VARIANT newVal)
{
	if (!m_Sender) {
		CHECK_HR_RETURN(E_POINTER);
	}
	m_callback_ontonechange = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CRTCDTMFSender::get_toneBuffer(__out BSTR* pVal)
{
	if (!m_Sender) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiStr(m_Sender->toneBuffer(), pVal);
}

STDMETHODIMP CRTCDTMFSender::get_duration(__out LONG* pVal)
{
	if (!m_Sender) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = m_Sender->duration();
	return S_OK;
}

STDMETHODIMP CRTCDTMFSender::get_interToneGap(__out LONG* pVal)
{
	if (!m_Sender) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = m_Sender->interToneGap();
	return S_OK;
}

void CRTCDTMFSender::ontonechange(cpp11::shared_ptr<_RTCDTMFToneChangeEvent> e)
{
	if (m_callback_ontonechange) {
		BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, m_callback_ontonechange);
		if (_cb) {
			CComObject<CRTCDTMFToneChangeEvent>* _e;
			HRESULT hr = Utils::CreateInstanceWithRef(&_e);
			if (SUCCEEDED(hr)) {
				_e->SetEvent(e);
				_cb->AddDispatch(_e);
			}
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}
