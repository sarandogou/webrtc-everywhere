/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */


// http://www.w3.org/TR/webrtc/#interface-definition
// http://www.w3.org/TR/webrtc/#rtcpeerconnection-interface-extensions-1
// http://www.w3.org/TR/webrtc/#rtcpeerconnection-interface-extensions-2
#include "stdafx.h"
#include "PeerConnection.h"
#include "MediaStream.h"
#include "MediaStreamTrack.h"
#include "MediaStreamEvent.h"
#include "SessionDescription.h"
#include "BrowserCallback.h"
#include "RTCIceCandidate.h"
#include "RTCPeerConnectionIceEvent.h"
#include "RTCStatsReport.h"
#include "RTCDTMFSender.h"
#include "RTCDataChannel.h"
#include "RTCDataChannelEvent.h"
#include "WebRTC.h"
#include "Utils.h"

#include "../common/_Debug.h"

#include <atlsafe.h>

CPeerConnection::CPeerConnection()
	: m_Peer(nullptr)
	, m_callback_onnegotiationneeded(NULL)
	, m_callback_onicecandidate(NULL)
	, m_callback_onsignalingstatechange(NULL)
	, m_callback_onaddstream(NULL)
	, m_callback_onremovestream(NULL)
	, m_callback_oniceconnectionstatechange(NULL)
{
}

HRESULT CPeerConnection::FinalConstruct()
{
	return S_OK;
}

void CPeerConnection::FinalRelease()
{
	m_callback_onnegotiationneeded = NULL;
	m_callback_onicecandidate = NULL;
	m_callback_onsignalingstatechange = NULL;
	m_callback_onaddstream = NULL;
	m_callback_onremovestream = NULL;
	m_callback_oniceconnectionstatechange = NULL;

	m_Peer = nullptr;

	SetDispatcher(NULL);
}

HRESULT CPeerConnection::Init(VARIANT RTCConfiguration, VARIANT MediaConstraints)
{
	HRESULT hr;

	std::shared_ptr<_MediaConstraintsObj> mediaConstraints;
	CHECK_HR_RETURN (hr = Utils::BuildMediaConstraintsObjs(MediaConstraints, mediaConstraints));

	std::shared_ptr<_RTCConfiguration> rtcConf;
	CHECK_HR_RETURN(hr = Utils::BuildRTCConfiguration(RTCConfiguration, rtcConf));

	m_Peer = std::make_shared<_PeerConnection>();
	if (!m_Peer->Init(rtcConf.get(), mediaConstraints.get())) {
		m_Peer = nullptr;
		return E_FAIL;
	}

	// set callback functions
	m_Peer->SetCallback_onnegotiationneeded(std::bind(&CPeerConnection::onnegotiationneeded, this));
	m_Peer->SetCallback_onicecandidate(std::bind(&CPeerConnection::onicecandidate, this, std::placeholders::_1));
	m_Peer->SetCallback_onsignalingstatechange(std::bind(&CPeerConnection::onsignalingstatechange, this));
	m_Peer->SetCallback_onaddstream(std::bind(&CPeerConnection::onaddstream, this, std::placeholders::_1));
	m_Peer->SetCallback_onremovestream(std::bind(&CPeerConnection::onremovestream, this, std::placeholders::_1));
	m_Peer->SetCallback_oniceconnectionstatechange(std::bind(&CPeerConnection::oniceconnectionstatechange, this));
	m_Peer->SetCallback_ondatachannel(std::bind(&CPeerConnection::ondatachannel, this, std::placeholders::_1));

	return S_OK;
}

STDMETHODIMP CPeerConnection::createOffer(__in_opt VARIANT successCallback, __in_opt VARIANT failureCallback, __in_opt VARIANT mediaConstraints)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}

	HRESULT hr = S_OK;

	std::shared_ptr<_MediaConstraintsObj> _mediaConstraints;
	CHECK_HR_RETURN(hr = Utils::BuildMediaConstraintsObjs(mediaConstraints, _mediaConstraints));

	CComPtr<IDispatch>_successCallback = Utils::VariantToDispatch(successCallback);
	CComPtr<IDispatch>_failureCallback = Utils::VariantToDispatch(failureCallback);

	bool ret = m_Peer->CreateOffer(
		[_successCallback, this](std::shared_ptr<_SessionDescription> sdp) {
			if (_successCallback) {
				CComObject<CSessionDescription>* _sdp;
				HRESULT _hr = Utils::CreateInstanceWithRef(&_sdp);
				if (SUCCEEDED(_hr)) {
					_sdp->SetSdp(sdp);
					BrowserCallback* _cb = new BrowserCallback(WM_CREATEOFFER_SUCCESS, _successCallback);
					if (_cb) {
						_cb->AddDispatch(_sdp);
						this->RaiseCallback(_cb);
						SafeReleaseObject(&_cb);
					}
					SafeRelease(&_sdp);
				}
			}
		},
			[_failureCallback, this](std::shared_ptr<std::string> error) {
			if (_failureCallback) {
				BrowserCallback* _cb = new BrowserCallback(WM_CREATEOFFER_ERROR, _failureCallback);
				if (_cb) {
					CComBSTR err(error->c_str());
					_cb->AddBSTR(err);
					this->RaiseCallback(_cb);
					SafeReleaseObject(&_cb);
				}
			}
		},
		_mediaConstraints.get()
	);
	
	if (!ret) {
		if (_failureCallback) {
			BrowserCallback* _cb = new BrowserCallback(WM_ERROR, _failureCallback);
			if (_cb) {
				CComBSTR err("Failed to create offer");
				_cb->AddBSTR(err);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
		}
		return S_OK;
	}

	return hr;
}

STDMETHODIMP CPeerConnection::createAnswer(__in_opt VARIANT successCallback, __in_opt VARIANT failureCallback, __in_opt VARIANT mediaConstraints)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}

	HRESULT hr = S_OK;

	std::shared_ptr<_MediaConstraintsObj> _mediaConstraints;
	CHECK_HR_RETURN(hr = Utils::BuildMediaConstraintsObjs(mediaConstraints, _mediaConstraints));

	CComPtr<IDispatch>_successCallback = Utils::VariantToDispatch(successCallback);
	CComPtr<IDispatch>_failureCallback = Utils::VariantToDispatch(failureCallback);

	bool ret = m_Peer->CreateAnswer(
		[_successCallback, this](std::shared_ptr<_SessionDescription> sdp) {
		if (_successCallback) {
			CComObject<CSessionDescription>* _sdp;
			HRESULT _hr = Utils::CreateInstanceWithRef(&_sdp);
			if (SUCCEEDED(_hr)) {
				_sdp->SetSdp(sdp);
				BrowserCallback* _cb = new BrowserCallback(WM_CREATEOFFER_SUCCESS, _successCallback);
				if (_cb) {
					_cb->AddDispatch(_sdp);
					this->RaiseCallback(_cb);
					SafeReleaseObject(&_cb);
				}
				SafeRelease(&_sdp);
			}
		}
	},
		[_failureCallback, this](std::shared_ptr<std::string> error) {
		if (_failureCallback) {
			BrowserCallback* _cb = new BrowserCallback(WM_CREATEOFFER_ERROR, _failureCallback);
			if (_cb) {
				CComBSTR err(error->c_str());
				_cb->AddBSTR(err);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
		}
	},
		_mediaConstraints.get()
		);

	if (!ret) {
		if (_failureCallback) {
			BrowserCallback* _cb = new BrowserCallback(WM_ERROR, _failureCallback);
			if (_cb) {
				CComBSTR err("Failed to create answer");
				_cb->AddBSTR(err);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
		}
		return S_OK;
	}

	return hr;
}

STDMETHODIMP CPeerConnection::setLocalDescription(__in VARIANT RTCSessionDescription, __in_opt VARIANT successCallback, __in_opt VARIANT failureCallback)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}
	
	HRESULT hr = S_OK;

	CComPtr<IDispatch>sdp = Utils::VariantToDispatch(RTCSessionDescription);
	if (!sdp) {
		return E_INVALIDARG;
	}
	CComPtr<ISessionDescription> _sdp = NULL;
	hr = sdp->QueryInterface(&_sdp);
	if (FAILED(hr)) {
		return hr;
	}
	CSessionDescription* pSdp = dynamic_cast<CSessionDescription*>(_sdp.p);
	if (!pSdp) {
		return E_INVALIDARG;
	}

	CComPtr<IDispatch>_successCallback = Utils::VariantToDispatch(successCallback);
	CComPtr<IDispatch>_failureCallback = Utils::VariantToDispatch(failureCallback);

	bool ret = m_Peer->SetLocalDescription(
		pSdp->GetSdp().get(),
		[_successCallback, this]() {
		if (_successCallback) {
			BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, _successCallback);
			if (_cb) {
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
		}
	},
		[_failureCallback, this](std::shared_ptr<std::string> error) {
		if (_failureCallback) {
			BrowserCallback* _cb = new BrowserCallback(WM_ERROR, _failureCallback);
			if (_cb) {
				CComBSTR err(error->c_str());
				_cb->AddBSTR(err);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
		}
	}
	);

	if (!ret) {
		if (_failureCallback) {
			BrowserCallback* _cb = new BrowserCallback(WM_ERROR, _failureCallback);
			if (_cb) {
				CComBSTR err("Failed to set local description");
				_cb->AddBSTR(err);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
		}
		return S_OK;
	}

	return hr;
}

STDMETHODIMP CPeerConnection::get_localDescription(__out VARIANT* pVal)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}
	
	std::shared_ptr<_SessionDescription>sdp = m_Peer->LocalDescription();
	if (sdp) {
		CComObject<CSessionDescription>* _sdp;
		HRESULT hr = Utils::CreateInstanceWithRef(&_sdp);
		if (FAILED(hr)) {
			return hr;
		}
		_sdp->SetSdp(sdp);
		*pVal = CComVariant(_sdp);
	}
	else {
		*pVal = CComVariant(NULL);
	}	

	return S_OK;
}

STDMETHODIMP CPeerConnection::setRemoteDescription(__in VARIANT RTCSessionDescription, __in_opt VARIANT successCallback, __in_opt VARIANT failureCallback)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}

	HRESULT hr = S_OK;

	CComPtr<IDispatch>sdp = Utils::VariantToDispatch(RTCSessionDescription);
	if (!sdp) {
		return E_INVALIDARG;
	}
	CComPtr<ISessionDescription> _sdp = NULL;
	hr = sdp->QueryInterface(&_sdp);
	if (FAILED(hr)) {
		return hr;
	}
	CSessionDescription* pSdp = dynamic_cast<CSessionDescription*>(_sdp.p);
	if (!pSdp) {
		return E_INVALIDARG;
	}

	CComPtr<IDispatch>_successCallback = Utils::VariantToDispatch(successCallback);
	CComPtr<IDispatch>_failureCallback = Utils::VariantToDispatch(failureCallback);

	bool ret = m_Peer->SetRemoteDescription(
		pSdp->GetSdp().get(),
		[_successCallback, this]() {
		if (_successCallback) {
			BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, _successCallback);
			if (_cb) {
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
		}
	},
		[_failureCallback, this](std::shared_ptr<std::string> error) {
		if (_failureCallback) {
			BrowserCallback* _cb = new BrowserCallback(WM_CREATEOFFER_ERROR, _failureCallback);
			if (_cb) {
				CComBSTR err(error->c_str());
				_cb->AddBSTR(err);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
		}
	}
	);

	if (!ret) {
		if (_failureCallback) {
			BrowserCallback* _cb = new BrowserCallback(WM_ERROR, _failureCallback);
			if (_cb) {
				CComBSTR err("Failed to set remote description");
				_cb->AddBSTR(err);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
		}
		return S_OK;
	}

	return hr;
}

STDMETHODIMP CPeerConnection::get_remoteDescription(__out VARIANT* pVal)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}

	std::shared_ptr<_SessionDescription>sdp = m_Peer->RemoteDescription();
	if (sdp) {
		CComObject<CSessionDescription>* _sdp;
		HRESULT hr = Utils::CreateInstanceWithRef(&_sdp);
		if (FAILED(hr)) {
			return hr;
		}
		_sdp->SetSdp(sdp);
		*pVal = CComVariant(_sdp);
	}
	else {
		*pVal = CComVariant(NULL);
	}

	return S_OK;
}

STDMETHODIMP CPeerConnection::get_signalingState(__out BSTR* pVal)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiStr(m_Peer->SignalingState(), pVal);
}

STDMETHODIMP CPeerConnection::updateIce(__in VARIANT RTCConfiguration, __in_opt VARIANT mediaConstraints)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}

	HRESULT hr;
	
	std::shared_ptr<_RTCConfiguration> _rtcConf;
	CHECK_HR_RETURN(hr = Utils::BuildRTCConfiguration(RTCConfiguration, _rtcConf));

	std::shared_ptr<_MediaConstraintsObj> _mediaConstraints;
	CHECK_HR_RETURN(hr = Utils::BuildMediaConstraintsObjs(mediaConstraints, _mediaConstraints));

	return (m_Peer->UpdateIce(_rtcConf.get(), _mediaConstraints.get()) ? S_OK : E_FAIL);
}

STDMETHODIMP CPeerConnection::addIceCandidate(__in VARIANT RTCIceCandidate, __in VARIANT successCallback, __in VARIANT failureCallback)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}

	HRESULT hr = S_OK;

	CComPtr<IDispatch>iceCandidate = Utils::VariantToDispatch(RTCIceCandidate);
	if (!iceCandidate) {
		return E_INVALIDARG;
	}
	CComPtr<IRTCIceCandidate> _iceCandidate = NULL;
	hr = iceCandidate->QueryInterface(&_iceCandidate);
	if (FAILED(hr)) {
		return hr;
	}
	CRTCIceCandidate* pIceCandidate = dynamic_cast<CRTCIceCandidate*>(_iceCandidate.p);
	if (!pIceCandidate) {
		return E_INVALIDARG;
	}

	CComPtr<IDispatch>_successCallback = Utils::VariantToDispatch(successCallback);
	CComPtr<IDispatch>_failureCallback = Utils::VariantToDispatch(failureCallback);

	bool ret = m_Peer->AddIceCandidate(
		pIceCandidate->GetCandidate().get(),
		[_successCallback, this]() {
			if (_successCallback) {
				BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, _successCallback);
				if (_cb) {
					this->RaiseCallback(_cb);
					SafeReleaseObject(&_cb);
				}
			}
		},
			[_failureCallback, this](std::shared_ptr<std::string> error) {
			if (_failureCallback) {
				BrowserCallback* _cb = new BrowserCallback(WM_CREATEOFFER_ERROR, _failureCallback);
				if (_cb) {
					CComBSTR err(error->c_str());
					_cb->AddBSTR(err);
					this->RaiseCallback(_cb);
					SafeReleaseObject(&_cb);
				}
			}
		}
	);

	if (!ret)
	{
		return E_FAIL;
	}

	return hr;
}

STDMETHODIMP CPeerConnection::get_iceGatheringState(__out BSTR* pVal)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiStr(m_Peer->IceGatheringState(), pVal);
}

STDMETHODIMP CPeerConnection::get_iceConnectionState(__out BSTR* pVal)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiStr(m_Peer->IceConnectionState(), pVal);
}

STDMETHODIMP CPeerConnection::getLocalStreams(__out VARIANT* MediaStreams)
{
	return getStreams(FALSE/*local*/, MediaStreams);
}

STDMETHODIMP CPeerConnection::getRemoteStreams(__out VARIANT* MediaStreams)
{
	return getStreams(TRUE/*remote*/, MediaStreams);
}

STDMETHODIMP CPeerConnection::getStreamById(__in BSTR streamId, __out VARIANT* MediaStream)
{
	if (!m_Peer || !streamId) {
		CHECK_HR_RETURN(E_POINTER);
	}

	char *_streamId = _com_util::ConvertBSTRToString(streamId);
	if (!_streamId) {
		CHECK_HR_RETURN(E_OUTOFMEMORY);
	}

	std::shared_ptr<_MediaStream> stream = m_Peer->GetStreamById(_streamId);
	delete[] _streamId;
	if (stream) {
		CComObject<CMediaStream>* _stream;
		HRESULT hr = Utils::CreateInstanceWithRef(&_stream);
		if (SUCCEEDED(hr)) {
			_stream->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
			_stream->SetStream(stream);
			hr = CComVariant(_stream).Detach(MediaStream);
		}
		return hr;
	}
	else {
		return CComVariant(NULL).Detach(MediaStream);
	}
}

STDMETHODIMP CPeerConnection::addStream(__in VARIANT stream, __in_opt VARIANT mediaConstraints)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}

	CComPtr<IDispatch>_stream = Utils::VariantToDispatch(stream);
	if (!_stream) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}
	CComPtr<IMediaStream> _mediaStream = NULL;
	HRESULT hr = _stream->QueryInterface(&_mediaStream);
	if (FAILED(hr)) {
		return hr;
	}

	CMediaStream* pStream = dynamic_cast<CMediaStream*>(_mediaStream.p);
	assert(pStream);
	if (!pStream) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}

	std::shared_ptr<_MediaConstraintsObj> _mediaConstraints;
	CHECK_HR_RETURN(hr = Utils::BuildMediaConstraintsObjs(mediaConstraints, _mediaConstraints));
	if (!m_Peer->AddStream(pStream->GetStream().get(), _mediaConstraints.get())) {
		CHECK_HR_RETURN(E_FAIL);
	}

	return S_OK;
}

STDMETHODIMP CPeerConnection::removeStream(__in VARIANT stream)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}

	CComPtr<IDispatch>_stream = Utils::VariantToDispatch(stream);
	if (!_stream) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}
	CComPtr<IMediaStream> _mediaStream = NULL;
	HRESULT hr = _stream->QueryInterface(&_mediaStream);
	CHECK_HR_RETURN(hr);

	CMediaStream* pStream = dynamic_cast<CMediaStream*>(_mediaStream.p);
	assert(pStream);
	if (!pStream) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}
	
	if (!m_Peer->RemoveStream(pStream->GetStream().get())) {
		CHECK_HR_RETURN(E_FAIL);
	}

	return S_OK;
}

STDMETHODIMP CPeerConnection::close()
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return m_Peer->Close() ? S_OK : E_FAIL;
}

STDMETHODIMP CPeerConnection::getStats(__in VARIANT selector, __in_opt VARIANT successCallback, __in_opt VARIANT failureCallback)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}

	// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-getStats-void-MediaStreamTrack-selector-RTCStatsCallback-successCallback-RTCPeerConnectionErrorCallback-failureCallback
	// Standard: void getStats (MediaStreamTrack? selector, RTCStatsCallback successCallback, RTCPeerConnectionErrorCallback failureCallback);
	// Chrome: void getStats (RTCStatsCallback successCallback, RTCPeerConnectionErrorCallback failureCallback);
	// Chrome issue: "selector" is nullable and not optional
	HRESULT hr;
	CComPtr<IDispatch>_selector = Utils::VariantToDispatch(selector);
	CComPtr<IDispatch>_successCallback = Utils::VariantToDispatch(successCallback);
	CComPtr<IDispatch>_failureCallback = Utils::VariantToDispatch(failureCallback);
	if (!_selector && !_successCallback && !_failureCallback) {
		return S_OK;
	}

	CComPtr<IMediaStreamTrack> _mediaStreamTrack = NULL;
	if (_selector) {
		hr = _selector->QueryInterface(&_mediaStreamTrack);
		if (FAILED(hr)) {
			_failureCallback = _successCallback;
			_successCallback = _selector;
			_selector = NULL;
		}
	}
	
	_MediaStreamTrackBase* pSelector = NULL;
	if (_mediaStreamTrack){
		CMediaStreamTrack* pTrack = dynamic_cast<CMediaStreamTrack*>(_mediaStreamTrack.p);
		if (pTrack) {
			pSelector = dynamic_cast<_MediaStreamTrackBase*>(pTrack->GetTrack().get());
		}
	}

	bool ret = m_Peer->GetStats(
		pSelector,
		[_successCallback, this](std::shared_ptr<_RTCStatsReport> report) {
			if (_successCallback){
				CComObject<CRTCStatsReport>* _report;
				HRESULT _hr = Utils::CreateInstanceWithRef(&_report);
				if (SUCCEEDED(_hr)) {
					BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, _successCallback);
					if (_cb) {
						_report->SetStats(report);
						_report->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
						_cb->AddDispatch(_report);
						this->RaiseCallback(_cb);
						SafeReleaseObject(&_cb);
					}
					SafeRelease(&_report);
				}
			}
		},
		[_failureCallback, this](std::shared_ptr<std::string> error) {
			if (_failureCallback){
				BrowserCallback* _cb = new BrowserCallback(WM_ERROR, _failureCallback);
				if (_cb) {
					CComBSTR err(error->c_str());
					_cb->AddBSTR(err);
					this->RaiseCallback(_cb);
					SafeReleaseObject(&_cb);
				}
			}
		});
		
	if (!ret && _failureCallback) {
		BrowserCallback* _cb = new BrowserCallback(WM_ERROR, _failureCallback);
		if (_cb) {
			CComBSTR err("Global error");
			_cb->AddBSTR(err);
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
	return S_OK;
}

STDMETHODIMP CPeerConnection::createDTMFSender(__in VARIANT MediaStreamTrack, __out VARIANT* RTCDTMFSender)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}
	CComPtr<IDispatch>_MediaStreamTrack = Utils::VariantToDispatch(MediaStreamTrack);
	if (!_MediaStreamTrack) {
		CHECK_HR_RETURN(E_POINTER);
	}
	
	HRESULT hr;
	CComPtr<IMediaStreamTrack> _mediaStreamTrack = NULL;
	CHECK_HR_RETURN(hr = _MediaStreamTrack->QueryInterface(&_mediaStreamTrack));
	CMediaStreamTrack* pMediaStreamTrack = dynamic_cast<CMediaStreamTrack*>(_mediaStreamTrack.p);
	if (!pMediaStreamTrack) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}
	cpp11::shared_ptr<_RTCDTMFSender>sender =  m_Peer->CreateDtmfSender(pMediaStreamTrack->GetTrack().get());
	if (!sender) {
		CHECK_HR_RETURN(E_POINTER);
	}
	CComObject<CRTCDTMFSender>* _sender;
	CHECK_HR_RETURN(hr = Utils::CreateInstanceWithRef(&_sender));
	_sender->SetSender(sender);
	_sender->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
	*RTCDTMFSender = CComVariant(_sender);
	return S_OK;
}

STDMETHODIMP CPeerConnection::createDataChannel(__in BSTR label/*[TreatNullAs=EmptyString]*/, __in_opt VARIANT dataChannelDict, __out VARIANT* DataChannel)
{
	if (!m_Peer) {
		CHECK_HR_RETURN(E_POINTER);
	}
	HRESULT hr;
	cpp11::shared_ptr<_RTCDataChannelInit> _dataChannelDict;
	CHECK_HR_RETURN(hr = Utils::BuildRTCDataChannelInit(dataChannelDict, _dataChannelDict));

	char *_label = _com_util::ConvertBSTRToString(label ? label : _T(""));
	if (!_label) {
		CHECK_HR_RETURN(E_OUTOFMEMORY);
	}

	cpp11::shared_ptr<_RTCDataChannel> dataChannel = m_Peer->CreateDataChannel(_label, _dataChannelDict);
	delete[] _label;
	CComObject<CRTCDataChannel>* _dataChannel;
	CHECK_HR_RETURN(hr = Utils::CreateInstanceWithRef(&_dataChannel));
	_dataChannel->SetChannel(dataChannel);
	_dataChannel->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
	*DataChannel = CComVariant(_dataChannel);
	return S_OK;
}

STDMETHODIMP CPeerConnection::put_onnegotiationneeded(VARIANT newVal)
{
	m_callback_onnegotiationneeded = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CPeerConnection::get_onnegotiationneeded(VARIANT* pVal)
{
	*pVal = CComVariant(m_callback_onnegotiationneeded);
	return S_OK;
}

STDMETHODIMP CPeerConnection::put_onicecandidate(VARIANT newVal)
{
	m_callback_onicecandidate = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CPeerConnection::get_onicecandidate(VARIANT* pVal)
{
	*pVal = CComVariant(m_callback_onicecandidate);
	return S_OK;
}

STDMETHODIMP CPeerConnection::put_onsignalingstatechange(VARIANT newVal)
{
	m_callback_onsignalingstatechange = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CPeerConnection::get_onsignalingstatechange(VARIANT* pVal)
{
	*pVal = CComVariant(m_callback_onsignalingstatechange);
	return S_OK;
}

STDMETHODIMP CPeerConnection::put_onaddstream(VARIANT newVal)
{
	m_callback_onaddstream = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CPeerConnection::get_onaddstream(VARIANT* pVal)
{
	*pVal = CComVariant(m_callback_onaddstream);
	return S_OK;
}

STDMETHODIMP CPeerConnection::put_onremovestream(VARIANT newVal)
{
	m_callback_onremovestream = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CPeerConnection::get_onremovestream(VARIANT* pVal)
{
	*pVal = CComVariant(m_callback_onremovestream);
	return S_OK;
}

STDMETHODIMP CPeerConnection::put_oniceconnectionstatechange(VARIANT newVal)
{
	m_callback_oniceconnectionstatechange = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CPeerConnection::get_oniceconnectionstatechange(VARIANT* pVal)
{
	*pVal = CComVariant(m_callback_oniceconnectionstatechange);
	return S_OK;
}

STDMETHODIMP CPeerConnection::put_ondatachannel(__in VARIANT newVal)
{
	m_callback_ondatachannel = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CPeerConnection::get_ondatachannel(__out VARIANT* pVal)
{
	*pVal = CComVariant(m_callback_ondatachannel);
	return S_OK;
}


void CPeerConnection::onnegotiationneeded()
{
	if (m_callback_onnegotiationneeded) {
		BrowserCallback* _cb = new BrowserCallback(WM_ONNEGOTIATIONNEEDED, m_callback_onnegotiationneeded);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void CPeerConnection::onicecandidate(std::shared_ptr<_RTCPeerConnectionIceEvent> e)
{
	if (m_callback_onicecandidate) {
		CComObject<CRTCPeerConnectionIceEvent>* _candidateEvent;
		HRESULT _hr = Utils::CreateInstanceWithRef(&_candidateEvent);
		if (SUCCEEDED(_hr)) {
			_candidateEvent->SetEvent(e);
			BrowserCallback* _cb = new BrowserCallback(WM_ONICECANDIDATE, m_callback_onicecandidate);
			if (_cb) {
				_cb->AddDispatch(_candidateEvent);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
			SafeRelease(&_candidateEvent);
		}
	}
}

void CPeerConnection::onsignalingstatechange()
{
	if (m_callback_onsignalingstatechange) {
		BrowserCallback* _cb = new BrowserCallback(WM_ONSIGNALINGSTATECHANGE, m_callback_onsignalingstatechange);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void CPeerConnection::onaddstream(std::shared_ptr<_MediaStreamEvent> e)
{
	if (m_callback_onaddstream) {
		CComObject<CMediaStreamEvent>* _event;
		HRESULT _hr = Utils::CreateInstanceWithRef(&_event);
		if (SUCCEEDED(_hr)) {
			_event->SetEvent(e);
			BrowserCallback* _cb = new BrowserCallback(WM_ONADDSTREAM, m_callback_onaddstream);
			if (_cb) {
				_event->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
				_cb->AddDispatch(_event);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
			SafeRelease(&_event);
		}
	}
}

void CPeerConnection::onremovestream(std::shared_ptr<_MediaStreamEvent> e)
{
	if (m_callback_onremovestream) {
		CComObject<CMediaStreamEvent>* _event;
		HRESULT _hr = Utils::CreateInstanceWithRef(&_event);
		if (SUCCEEDED(_hr)) {
			_event->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
			_event->SetEvent(e);
			BrowserCallback* _cb = new BrowserCallback(WM_ONREMOVESTREAM, m_callback_onremovestream);
			if (_cb) {
				_cb->AddDispatch(_event);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
			SafeRelease(&_event);
		}
	}
}

void CPeerConnection::oniceconnectionstatechange()
{
	if (m_callback_oniceconnectionstatechange) {
		BrowserCallback* _cb = new BrowserCallback(WM_ONICECONNECTIONSTATECHANGE, m_callback_oniceconnectionstatechange);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void CPeerConnection::ondatachannel(cpp11::shared_ptr<_RTCDataChannelEvent> e)
{
	if (m_callback_ondatachannel) {
		CComObject<CRTCDataChannelEvent>* _event;
		HRESULT _hr = Utils::CreateInstanceWithRef(&_event);
		if (SUCCEEDED(_hr)) {
			_event->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
			_event->SetEvent(e);
			BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, m_callback_ondatachannel);
			if (_cb) {
				_cb->AddDispatch(_event);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
			SafeRelease(&_event);
		}
	}
}

HRESULT CPeerConnection::getStreams(__in BOOL remote, __out VARIANT* MediaStreams)
{
	HRESULT hr = S_OK;
	if (!m_Peer) {
		return E_POINTER;
	}

	CComPtr<CWebRTC> pluginInstance = dynamic_cast<CWebRTC*>(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
	if (!pluginInstance) {
		CHECK_HR_RETURN(E_POINTER);
	}

	CComPtr<IDispatch> spDispatch;
	CHECK_HR_RETURN(hr = pluginInstance->GetDispatch(spDispatch));

	std::vector<CComVariant> vect;
	std::shared_ptr<_Sequence<_MediaStream> > streams = remote ? m_Peer->GetRemoteStreams() : m_Peer->GetLocalStreams();
	if (streams) {
		for (size_t i = 0; i < streams->values.size(); ++i) {
			if (!streams->values[i]) {
				continue;
			}
			CComObject<CMediaStream>* _stream;
			hr = Utils::CreateInstanceWithRef(&_stream);
			if (SUCCEEDED(hr)) {
				_stream->SetDispatcher(pluginInstance);
				_stream->SetStream(streams->values[i]);
				vect.push_back(CComVariant(_stream));
				SafeRelease(&_stream);
			}
		}
	}

	CComQIPtr<IDispatchEx> spArray;
	CHECK_HR_RETURN(hr = Utils::CreateJsArray(spDispatch, vect, spArray));

	*MediaStreams = CComVariant(spArray.Detach());
	return hr;
}