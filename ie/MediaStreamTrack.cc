/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */

// http://www.w3.org/TR/mediacapture-streams/#idl-def-MediaStreamTrack

#include "stdafx.h"
#include "MediaStreamTrack.h"
#include "BrowserCallback.h"
#include "MediaSourceStates.h"
#include "WebRTC.h"
#include "SourceInfo.h"
#include "Utils.h"

#include "../common/_Debug.h"


CMediaStreamTrack::CMediaStreamTrack()
	: m_Track(nullptr)
	, m_callback_onmute(NULL)
	, m_callback_onunmute(NULL)
	, m_callback_onstarted(NULL)
	, m_callback_onended(NULL)
	, m_callback_onoverconstrained(NULL)
{
}

HRESULT CMediaStreamTrack::FinalConstruct()
{
	return S_OK;
}

void CMediaStreamTrack::FinalRelease()
{
	m_callback_onmute = NULL;
	m_callback_onunmute = NULL;
	m_callback_onstarted = NULL;
	m_callback_onended = NULL;
	m_callback_onoverconstrained = NULL;
	
	m_Track = nullptr;

	SetDispatcher(NULL);
}

void CMediaStreamTrack::SetTrack(std::shared_ptr<_MediaStreamTrack> & track)
{
	if ((m_Track = track)) {
		m_Track->onmuteSet(std::bind(&CMediaStreamTrack::onmute, this));
		m_Track->onunmuteSet(std::bind(&CMediaStreamTrack::onunmute, this));
		m_Track->onstartedSet(std::bind(&CMediaStreamTrack::onstarted, this));
		m_Track->onendedSet(std::bind(&CMediaStreamTrack::onended, this));
		m_Track->onoverconstrainedSet(std::bind(&CMediaStreamTrack::onoverconstrained, this));
	}
}

std::shared_ptr<_MediaStreamTrack> CMediaStreamTrack::GetTrack()
{ 
	return m_Track;
}

STDMETHODIMP CMediaStreamTrack::get_kind(__out BSTR* pVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiStr(m_Track->kind(), pVal);
}

STDMETHODIMP CMediaStreamTrack::get_id(__out BSTR* pVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiStr(m_Track->id(), pVal);
}

STDMETHODIMP CMediaStreamTrack::get_label(__out BSTR* pVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiStr(m_Track->label(), pVal);
}

STDMETHODIMP CMediaStreamTrack::get_enabled(__out VARIANT_BOOL* pVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}

	*pVal = m_Track->enabled() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CMediaStreamTrack::put_enabled(__in VARIANT_BOOL newVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return m_Track->enabledSet(newVal != VARIANT_FALSE) ? S_OK : E_FAIL;
}

STDMETHODIMP CMediaStreamTrack::get_muted(__out VARIANT_BOOL* pVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = m_Track->muted() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CMediaStreamTrack::get_onmute(__out VARIANT* pVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = CComVariant(m_callback_onmute);
	return S_OK;
}

STDMETHODIMP CMediaStreamTrack::put_onmute(__in VARIANT newVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	m_callback_onmute = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CMediaStreamTrack::get_onunmute(__out VARIANT* pVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = CComVariant(m_callback_onunmute);
	return S_OK;
}

STDMETHODIMP CMediaStreamTrack::put_onunmute(__in VARIANT newVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	m_callback_onunmute = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CMediaStreamTrack::get_readonly(__out VARIANT_BOOL* pVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = m_Track->readonly() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CMediaStreamTrack::get_remote(__out VARIANT_BOOL* pVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = m_Track->remote() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CMediaStreamTrack::get_readyState(__out BSTR* pVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiStr(m_Track->readyState(), pVal);
}

STDMETHODIMP CMediaStreamTrack::get_onstarted(__out VARIANT* pVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = CComVariant(m_callback_onstarted);
	return S_OK;
}

STDMETHODIMP CMediaStreamTrack::put_onstarted(__in VARIANT newVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	m_callback_onstarted = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CMediaStreamTrack::get_onended(__out VARIANT* pVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = CComVariant(m_callback_onended);
	return S_OK;
}

STDMETHODIMP CMediaStreamTrack::put_onended(__in VARIANT newVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	m_callback_onended = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CMediaStreamTrack::getSourceInfos(__out VARIANT* Infos)
{
	HRESULT hr = S_OK;

	CComPtr<CWebRTC> pluginInstance = dynamic_cast<CWebRTC*>(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
	if (!pluginInstance) {
		CHECK_HR_RETURN(E_POINTER);
	}

	CComPtr<IDispatch> spDispatch;
	CHECK_HR_RETURN(hr = pluginInstance->GetDispatch(spDispatch));

	return CMediaStreamTrack::getSources(spDispatch, Infos);
}

STDMETHODIMP CMediaStreamTrack::constraints(__out VARIANT* MediaTrackConstraints)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return (E_NOTIMPL);
}

STDMETHODIMP CMediaStreamTrack::states(__out VARIANT* MediaSourceStates)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	CComObject<CMediaSourceStates>* _states;
	HRESULT hr = Utils::CreateInstanceWithRef(&_states);
	if (SUCCEEDED(hr)) {
		_states->SetStates(m_Track->states());
		*MediaSourceStates = CComVariant(_states);
	}
	return hr;
}

STDMETHODIMP CMediaStreamTrack::capabilities(__out VARIANT* AllCapabilities)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return (E_NOTIMPL);
}

STDMETHODIMP CMediaStreamTrack::applyConstraints(__in VARIANT MediaTrackConstraints)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return (E_NOTIMPL);
}

STDMETHODIMP CMediaStreamTrack::get_onoverconstrained(__out VARIANT* pVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = CComVariant(m_callback_onoverconstrained);
	return S_OK;
}

STDMETHODIMP CMediaStreamTrack::put_onoverconstrained(__in VARIANT newVal)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	m_callback_onoverconstrained = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CMediaStreamTrack::clone(__out VARIANT* MediaStreamTrack)
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return (E_NOTIMPL);
}

STDMETHODIMP CMediaStreamTrack::stop()
{
	if (!m_Track) {
		CHECK_HR_RETURN(E_POINTER);
	}
	m_Track->stop();
	return S_OK;
}

// not part of the standard but used by Chrome
HRESULT CMediaStreamTrack::getSources(__in CComPtr<IDispatch> spDispatch, __out VARIANT* Infos)
{
	HRESULT hr = S_OK;

	std::vector<CComVariant> vect;
	std::shared_ptr<_Sequence<_SourceInfo> > sources = _MediaStreamTrack::getSourceInfos();
	if (sources) {
		for (size_t i = 0; i < sources->values.size(); ++i) {
			if (!sources->values[i]) {
				continue;
			}
			CComObject<CSourceInfo>* _source;
			hr = Utils::CreateInstanceWithRef(&_source);
			if (SUCCEEDED(hr)) {
				_source->SetInfo(sources->values[i]);
				vect.push_back(CComVariant(_source));
				SafeRelease(&_source);
			}
		}
	}

	CComQIPtr<IDispatchEx> spArray;
	CHECK_HR_RETURN(hr = Utils::CreateJsArray(spDispatch, vect, spArray));

	*Infos = CComVariant(spArray.Detach());
	return hr;
}

void CMediaStreamTrack::onmute()
{
	if (m_callback_onmute) {
		BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, m_callback_onmute);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void CMediaStreamTrack::onunmute()
{
	if (m_callback_onunmute) {
		BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, m_callback_onunmute);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void CMediaStreamTrack::onstarted()
{
	if (m_callback_onstarted) {
		BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, m_callback_onstarted);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void CMediaStreamTrack::onended()
{
	if (m_callback_onended) {
		BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, m_callback_onended);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void CMediaStreamTrack::onoverconstrained()
{
	if (m_callback_onoverconstrained) {
		BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, m_callback_onoverconstrained);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}