/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */

// http://www.w3.org/TR/mediacapture-streams/#mediastream

#include "stdafx.h"
#include "MediaStream.h"
#include "MediaStreamTrack.h"
#include "WebRTC.h"
#include "BrowserCallback.h"
#include "Utils.h"

#include "../common/_Debug.h"

CMediaStream::CMediaStream()
	: m_Stream(nullptr)
	, m_callback_onended(NULL)
	, m_callback_onaddtrack(NULL)
	, m_callback_onremovetrack(NULL)
{

}

HRESULT CMediaStream::FinalConstruct()
{
	return S_OK;
}

void CMediaStream::FinalRelease()
{
	m_callback_onended = NULL;
	m_callback_onaddtrack = NULL;
	m_callback_onremovetrack = NULL;

	m_Stream = nullptr;

	SetDispatcher(NULL);
}

void CMediaStream::SetStream(std::shared_ptr<_MediaStream> & stream)
{ 
	if ((m_Stream = stream)) {
		m_Stream->onendedSet(std::bind(&CMediaStream::onended, this));
		m_Stream->onaddtrackSet(std::bind(&CMediaStream::onaddtrack, this));
		m_Stream->onremovetrackSet(std::bind(&CMediaStream::onremovetrack, this));
	}
}

std::shared_ptr<_MediaStream> CMediaStream::GetStream()
{ 
	return m_Stream; 
}


STDMETHODIMP CMediaStream::get_id(BSTR* pVal)
{
	if (!m_Stream) {
		return E_POINTER;
	}
	return Utils::CopyAnsiStr(m_Stream->id(), pVal);
}

STDMETHODIMP CMediaStream::getAudioTracks(__out VARIANT* Tracks)
{
	return getTracks(_TrackTypeAudio, Tracks);
}

STDMETHODIMP CMediaStream::getVideoTracks(__out VARIANT* Tracks)
{
	return getTracks(_TrackTypeVideo, Tracks);
}

STDMETHODIMP CMediaStream::getTracks(__out VARIANT* Tracks)
{
	return getTracks(_TrackTypeAll, Tracks);
}

STDMETHODIMP CMediaStream::getTrackById(__in BSTR trackId, __out VARIANT* MediaStreamTrack)
{
	if (!m_Stream) {
		CHECK_HR_RETURN(E_POINTER);
	}
	char* lpszTrackId = _com_util::ConvertBSTRToString(trackId);

	if (!lpszTrackId) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}

	std::shared_ptr<_MediaStreamTrack> track = m_Stream->getTrackById(lpszTrackId);
	delete[] lpszTrackId;
	if (track) {
		CComObject<CMediaStreamTrack>* _track;
		HRESULT hr = Utils::CreateInstanceWithRef(&_track);
		if (SUCCEEDED(hr)) {
			_track->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
			_track->SetTrack(track);
			*MediaStreamTrack = CComVariant(_track);
		}
		return hr;
	}
	else {
		*MediaStreamTrack = CComVariant(NULL);
		return S_OK;
	}	
}


STDMETHODIMP CMediaStream::addTrack(__in VARIANT MediaStreamTrack)
{
	HRESULT hr;
	if (!m_Stream) {
		CHECK_HR_RETURN(E_POINTER);
	}

	CComPtr<IDispatch>_track = Utils::VariantToDispatch(MediaStreamTrack);
	if (!_track) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}

	CComPtr<IMediaStreamTrack> _mediaStreamTrack = NULL;
	CHECK_HR_RETURN(hr = _track->QueryInterface(&_mediaStreamTrack));
	
	CMediaStreamTrack* pTrack = dynamic_cast<CMediaStreamTrack*>(_mediaStreamTrack.p);
	assert(pTrack);
	if (!pTrack) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}
	
	m_Stream->addTrack(pTrack->GetTrack().get());

	return S_OK;
}

STDMETHODIMP CMediaStream::removeTrack(__in VARIANT MediaStreamTrack)
{
	HRESULT hr;
	if (!m_Stream) {
		CHECK_HR_RETURN(E_POINTER);
	}

	CComPtr<IDispatch>_track = Utils::VariantToDispatch(MediaStreamTrack);
	if (!_track) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}

	CComPtr<IMediaStreamTrack> _mediaStreamTrack = NULL;
	CHECK_HR_RETURN(hr = _track->QueryInterface(&_mediaStreamTrack));

	CMediaStreamTrack* pTrack = dynamic_cast<CMediaStreamTrack*>(_mediaStreamTrack.p);
	assert(pTrack);
	if (!pTrack) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}

	m_Stream->removeTrack(pTrack->GetTrack().get());

	return S_OK;
}

STDMETHODIMP CMediaStream::clone(__out VARIANT* MediaStream)
{
	if (!m_Stream) {
		CHECK_HR_RETURN(E_POINTER);
	}

	std::shared_ptr<_MediaStream>stream = m_Stream->clone();
	if (!stream) {
		*MediaStream = CComVariant(NULL);
		return S_OK;
	}

	CComObject<CMediaStream>* _stream;
	HRESULT hr = Utils::CreateInstanceWithRef(&_stream);
	if (SUCCEEDED(hr)) {
		_stream->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
		_stream->SetStream(stream);
		*MediaStream = CComVariant(_stream);
	}
	return hr;
}

STDMETHODIMP CMediaStream::get_ended(__out VARIANT_BOOL* pVal)
{
	if (!m_Stream) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = m_Stream->ended() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CMediaStream::get_onended(__out VARIANT* pVal)
{
	if (!m_Stream) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = CComVariant(m_callback_onended);
	return S_OK;
}

STDMETHODIMP CMediaStream::put_onended(__in VARIANT newVal)
{
	if (!m_Stream) {
		CHECK_HR_RETURN(E_POINTER);
	}
	m_callback_onended = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CMediaStream::get_onaddtrack(__out VARIANT* pVal)
{
	if (!m_Stream) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = CComVariant(m_callback_onaddtrack);
	return S_OK;
}

STDMETHODIMP CMediaStream::put_onaddtrack(__in VARIANT newVal)
{
	if (!m_Stream) {
		CHECK_HR_RETURN(E_POINTER);
	}
	m_callback_onaddtrack = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CMediaStream::get_onremovetrack(__out VARIANT* pVal)
{
	if (!m_Stream) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = CComVariant(m_callback_onremovetrack);
	return S_OK;
}

STDMETHODIMP CMediaStream::put_onremovetrack(__in VARIANT newVal)
{
	if (!m_Stream) {
		CHECK_HR_RETURN(E_POINTER);
	}
	m_callback_onremovetrack = Utils::VariantToDispatch(newVal);
	return S_OK;
}


// not part of the standard but used by Chrome
STDMETHODIMP CMediaStream::stop()
{
	if (m_Stream) {
		m_Stream->stop();
	}
	return S_OK;
}

HRESULT CMediaStream::getTracks(_TrackType type, VARIANT* Tracks)
{
	HRESULT hr = S_OK;
	if (!m_Stream) {
		CHECK_HR_RETURN(E_POINTER);
	}

	CComPtr<CWebRTC> pluginInstance = dynamic_cast<CWebRTC*>(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
	if (!pluginInstance) {
		CHECK_HR_RETURN(E_POINTER);
	}

	CComPtr<IDispatch> spDispatch;
	CHECK_HR_RETURN(hr = pluginInstance->GetDispatch(spDispatch));

	std::vector<CComVariant> vect;
	std::shared_ptr<_Sequence<_MediaStreamTrack> > _tracks;
	cpp11::shared_ptr<_Sequence<_MediaStreamTrack> > tracks(new _Sequence<_MediaStreamTrack>());
	if ((type & _TrackTypeAudio) == _TrackTypeAudio && (_tracks = m_Stream->getAudioTracks()) && _tracks.get()) {
		tracks->AddSeq(_tracks.get());
	}
	if ((type & _TrackTypeVideo) == _TrackTypeVideo && (_tracks = m_Stream->getVideoTracks()) && _tracks.get()) {
		tracks->AddSeq(_tracks.get());
	}
	
	for (size_t i = 0; i < tracks->values.size(); ++i) {
		if (!tracks->values[i]) {
			continue;
		}
		CComObject<CMediaStreamTrack>* _track;
		hr = Utils::CreateInstanceWithRef(&_track);
		if (SUCCEEDED(hr)) {
			_track->SetDispatcher(pluginInstance);
			_track->SetTrack(tracks->values[i]);
			vect.push_back(CComVariant(_track));
			SafeRelease(&_track);
		}
	}

	CComQIPtr<IDispatchEx> spArray;
	CHECK_HR_RETURN(hr = Utils::CreateJsArray(spDispatch, vect, spArray));

	*Tracks = CComVariant(spArray.Detach());
	return hr;
}

void CMediaStream::onended()
{
	if (m_callback_onended) {
		BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, m_callback_onended);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void CMediaStream::onaddtrack()
{
	if (m_callback_onaddtrack) {
		BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, m_callback_onaddtrack);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void CMediaStream::onremovetrack()
{
	if (m_callback_onremovetrack) {
		BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, m_callback_onremovetrack);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}