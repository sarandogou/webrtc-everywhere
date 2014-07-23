/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */

// http://www.w3.org/wiki/HTML/Elements/video
#include "stdafx.h"
#include "WebRTC.h"
#include "MediaStream.h"
#include "SessionDescription.h"
#include "DictOptions.h"
#include "PeerConnection.h"
#include "RTCIceCandidate.h"
#include "BrowserCallback.h"
#include "MediaStreamTrack.h"
#include "Utils.h"

#include "../common/_NavigatorUserMedia.h"
#include "../common/_Debug.h"

#include <activscp.h>

CWebRTC::CWebRTC()
	: _AsyncEventDispatcher()
	, _RTCDisplay()
	, m_pTempVideoBuff(NULL)
{
	m_bWindowOnly = TRUE;
}

HRESULT CWebRTC::FinalConstruct()
{
	_Utils::Initialize();
	TakeFakePeerConnectionFactory();
	return S_OK;
}

// _RTCDisplay::Handle() implementation
HWND CWebRTC::Handle()
{
	return m_hWnd;
}

// _RTCDisplay::OnStartVideoRenderer() implementation
void CWebRTC::OnStartVideoRenderer()
{
	if (m_callbacks_onplay.size()) {
		for (size_t i = 0; i < m_callbacks_onplay.size(); ++i) {
			BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, m_callbacks_onplay[i]);
			if (_cb) {
				_cb->AddDispatch(this); // not part of the standard: no arg to the callback
				dynamic_cast<_AsyncEventDispatcher*>(this)->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
		}
	}
}

// _RTCDisplay::OnStopVideoRenderer() implementation
void CWebRTC::OnStopVideoRenderer()
{

}

LRESULT CWebRTC::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SetWindow(m_hWnd);
	return S_OK;
}

void CWebRTC::FinalRelease()
{
	StopVideoRenderer();
	SetDispatcher(NULL);
	m_callbacks_onplay.clear();
	SafeDelete(&m_pTempVideoBuff);
	ReleaseFakePeerConnectionFactory();
}

STDMETHODIMP CWebRTC::get_versionName(BSTR* pVal)
{
	return Utils::CopyAnsiStr(kPluginVersionString, pVal);
}

STDMETHODIMP CWebRTC::createSessionDescription(VARIANT RTCSessionDescriptionInit, IDispatch** ppSdp)
{
	CComObject<CSessionDescription>* pSdp = NULL;
	HRESULT hr;

	CHECK_HR_BAIL(hr = Utils::CreateInstanceWithRef(&pSdp));
	CHECK_HR_BAIL(hr = pSdp->Init(RTCSessionDescriptionInit));
	
	*ppSdp = pSdp, pSdp = NULL;

bail:
	SafeRelease(&pSdp);
	return hr;
}

STDMETHODIMP CWebRTC::createDisplay(__out IDispatch** ppDisplay)
{
	CComObject<CWebRTC>* pDisplay = NULL;
	HRESULT hr;

	CHECK_HR_BAIL(hr = Utils::CreateInstanceWithRef(&pDisplay));
	
	pDisplay->SetDispatcher(this);

	*ppDisplay = pDisplay, pDisplay = NULL;

bail:
	SafeRelease(&pDisplay);
	return hr;
}

STDMETHODIMP CWebRTC::getUserMedia(VARIANT constraints, VARIANT successCallback, VARIANT errorCallback)
{
	HRESULT hr = S_OK;

	CComPtr<IDispatch>_constraints = Utils::VariantToDispatch(constraints);
	CComPtr<IDispatch>_successCallback = Utils::VariantToDispatch(successCallback);
	CComPtr<IDispatch>_errorCallback = Utils::VariantToDispatch(errorCallback);

	std::shared_ptr<_MediaStreamConstraints> mediaStreamConstraints;

	hr = Utils::BuildMediaStreamConstraints(constraints, mediaStreamConstraints);
	
	_NavigatorUserMedia::getUserMedia(
		mediaStreamConstraints.get(),
		[_successCallback, this](std::shared_ptr<_MediaStream> stream) {
			if (_successCallback) {
				CComObject<CMediaStream>* _stream;
				HRESULT _hr = Utils::CreateInstanceWithRef(&_stream);
				if (SUCCEEDED(_hr)) {
					BrowserCallback* _cb = new BrowserCallback(WM_GETUSERMEDIA_SUCESS, _successCallback);
					if (_cb) {
						_stream->SetStream(stream);
						_stream->SetDispatcher(this);
						_cb->AddDispatch(_stream);
						dynamic_cast<_AsyncEventDispatcher*>(this)->RaiseCallback(_cb);
						SafeReleaseObject(&_cb);
					}
					SafeRelease(&_stream);
				}
			}
		},
		[_errorCallback, this](std::shared_ptr<_NavigatorUserMediaError> e) {
			if (_errorCallback) {
				BrowserCallback* _cb = new BrowserCallback(WM_GETUSERMEDIA_ERROR, _errorCallback);
				if (_cb) {
					CComBSTR err(e->constraintName.c_str());
					_cb->AddBSTR(err);
					dynamic_cast<_AsyncEventDispatcher*>(this)->RaiseCallback(_cb);
					SafeReleaseObject(&_cb);
				}
			}
		}
		);

		return hr;
}

STDMETHODIMP CWebRTC::createDictOptions(IDispatch** ppDictOptions)
{
	CComObject<CDictOptions>* pDictOptions;
	HRESULT hr;

	CHECK_HR_RETURN(hr = Utils::CreateInstanceWithRef(&pDictOptions));

	*ppDictOptions = pDictOptions;
	return S_OK;
}


STDMETHODIMP CWebRTC::createPeerConnection(VARIANT RTCConfiguration, VARIANT/*optional*/ MediaConstraints, IDispatch** ppPeerConnection)
{
	CComObject<CPeerConnection>* pPeerConnection;
	HRESULT hr;
	CHECK_HR_RETURN(hr = Utils::CreateInstanceWithRef(&pPeerConnection));

	hr = pPeerConnection->Init(RTCConfiguration, MediaConstraints);
	if (FAILED(hr)) {
		SafeRelease(&pPeerConnection);
		return hr;
	}
	pPeerConnection->SetDispatcher(this);

	*ppPeerConnection = pPeerConnection;
	return S_OK;
}

STDMETHODIMP CWebRTC::createIceCandidate(VARIANT RTCIceCandidateInit, IDispatch** ppIceCandidate)
{
	CComObject<CRTCIceCandidate>* pIceCandidate;
	HRESULT hr;

	CHECK_HR_BAIL(hr = Utils::CreateInstanceWithRef(&pIceCandidate));
	CHECK_HR_BAIL(hr = pIceCandidate->Init(RTCIceCandidateInit));

	*ppIceCandidate = pIceCandidate, pIceCandidate = NULL;

bail:
	SafeRelease(&pIceCandidate);
	return hr;
}

STDMETHODIMP CWebRTC::createMediaStreamTrack(__out IDispatch** ppMediaStreamTrack)
{
	CComObject<CMediaStreamTrack>* pMediaStreamTrack;
	HRESULT hr;
	
	CHECK_HR_BAIL(hr = Utils::CreateInstanceWithRef(&pMediaStreamTrack));
	*ppMediaStreamTrack = pMediaStreamTrack, pMediaStreamTrack = NULL;
	
bail:
	SafeRelease(&pMediaStreamTrack);
	return hr;
}

STDMETHODIMP CWebRTC::bindEventListener(__in BSTR type, __in_opt VARIANT listenerCallback, __in_opt VARIANT useCapture)
{
	if (!type) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}
	char* lpszType = _com_util::ConvertBSTRToString(type);
	if (!lpszType) {
		CHECK_HR_RETURN(E_OUTOFMEMORY);
	}
	if (!strcmp(lpszType, "play")) {
		CComPtr<IDispatch> callback = Utils::VariantToDispatch(listenerCallback);
		if (callback) {
			m_callbacks_onplay.push_back(callback);
		}
	}

	delete[]lpszType;

	return S_OK;
}

STDMETHODIMP CWebRTC::getSources(__in_opt VARIANT successCallback)
{
	CComPtr<IDispatch>_successCallback = Utils::VariantToDispatch(successCallback);
	if (!_successCallback) {
		return S_OK;
	}
	HRESULT hr;
	CComVariant var;
	CComPtr<IDispatch> spDispatch;
	CHECK_HR_RETURN(hr = GetDispatch(spDispatch));
	CHECK_HR_RETURN(hr = CMediaStreamTrack::getSources(spDispatch, &var));

	CComPtr<IDispatch>_sources = Utils::VariantToDispatch(var);
	if (!_sources) {
		CHECK_HR_RETURN(E_NOINTERFACE);
	}

	BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, _successCallback);
	if (!_cb) {
		CHECK_HR_RETURN(E_OUTOFMEMORY);
	}
	_cb->AddDispatch(_sources);
	dynamic_cast<_AsyncEventDispatcher*>(this)->RaiseCallback(_cb);
	SafeReleaseObject(&_cb);
	
	return S_OK;
}

STDMETHODIMP CWebRTC::put_src(VARIANT newVal)
{
	CComPtr<IDispatch>mediaStream = Utils::VariantToDispatch(newVal);
	if (mediaStream) {
		CComPtr<IMediaStream> _mediaStream = NULL;
		HRESULT hr;
		CHECK_HR_RETURN(hr = mediaStream->QueryInterface(&_mediaStream));

		CMediaStream* pStream = dynamic_cast<CMediaStream*>(_mediaStream.p);
		if (!pStream) {
			CHECK_HR_RETURN(E_INVALIDARG);
		}
		std::shared_ptr<_MediaStream> stream = pStream->GetStream();
		if (stream) {
			StartVideoRenderer(stream->GetVideoTrack());
		}
	}
	else {
		StopVideoRenderer();
	}
	return S_OK;
}

STDMETHODIMP CWebRTC::get_videoWidth(__out LONG* pVal)
{
	*pVal = (LONG)GetVideoWidth();
	return S_OK;
}

STDMETHODIMP CWebRTC::get_videoHeight(__out LONG* pVal)
{
	*pVal = (LONG)GetVideoHeight();
	return S_OK;
}

STDMETHODIMP CWebRTC::fillImageData(__in VARIANT imageData)
{
	HRESULT hr = S_OK;

	CComQIPtr<IDispatchEx> spImageData = CComQIPtr<IDispatchEx>(Utils::VariantToDispatch(imageData));
	if (!spImageData) {
		CHECK_HR_RETURN(E_NOINTERFACE);
	}
	
	int videoWidth = GetVideoWidth();
	int videoHeight = GetVideoHeight();

	if (videoHeight <= 0 || videoWidth <= 0) {
		return S_OK;
	}

	long index, width = 0, height = 0;
	VARIANT varData;
	CHECK_HR_RETURN(hr = Utils::DispatchGetProp(spImageData.p, L"data", &varData));
	CHECK_HR_RETURN(hr = Utils::DispatchGetPropInteger(spImageData.p, L"width", width));
	CHECK_HR_RETURN(hr = Utils::DispatchGetPropInteger(spImageData.p, L"height", height));

	CComQIPtr<IDispatchEx> spDataArray = CComQIPtr<IDispatchEx>(Utils::VariantToDispatch(varData));
	if (!spDataArray) {
		CHECK_HR_RETURN(E_NOINTERFACE);
	}

	if (width != videoWidth || height != videoHeight) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}

	size_t videoSize = (videoWidth * videoHeight * 4);

	if (!m_pTempVideoBuff || m_pTempVideoBuff->getSize() < videoSize){
		SafeDelete(&m_pTempVideoBuff);
		if ((_Buffer::New(NULL, videoSize, &m_pTempVideoBuff))) {
			CHECK_HR_RETURN(E_OUTOFMEMORY);
		}
	}

	if (CopyFromFrame(const_cast<void*>(m_pTempVideoBuff->getPtr()), videoSize) != videoSize) {
		memset(const_cast<void*>(m_pTempVideoBuff->getPtr()), 0, videoSize);
	}

	WCHAR wcharIndex[25];
	DISPID dispID;
	VARIANT vParam;
	vParam.vt = VT_I4;
	DISPID indexNamedArgs[] = { DISPID_PROPERTYPUT };
	DISPPARAMS params = { &vParam, indexNamedArgs, 1, 1 };
	const uint8_t* imageDataPtr = (const uint8_t*)m_pTempVideoBuff->getPtr();
	for (long x = 0; x < width; ++x) {
		for (long y = 0; y < height; ++y) {
			index = (x + y * width) * 4;
			for (long comp = 0; comp < 4; ++comp) { // (a, r, g, b) -> (r, g, b, a)
				wsprintf(wcharIndex, _T("%ld\0"), index + comp);
				CHECK_HR_RETURN(hr = spDataArray->GetDispID(CComBSTR(wcharIndex), fdexNameEnsure, &dispID));
				vParam.lVal = imageDataPtr[index + ((comp + 0) & 3)];
				CHECK_HR_RETURN(hr = spDataArray->InvokeEx(dispID, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUT, &params, NULL, NULL, NULL));
			}
		}
	}
	return hr;
}

STDMETHODIMP CWebRTC::get_isWebRtcPlugin(__out VARIANT_BOOL* pVal)
{
	*pVal = VARIANT_TRUE;
	return S_OK;
}

HRESULT CWebRTC::GetDispatch(CComPtr<IDispatch> &spDispatch)
{
	HRESULT hr = S_OK;
	IHTMLDocument2* pDoc = NULL;

	CComPtr<IOleContainer> spContainer;
	CComPtr<IHTMLDocument2> spDoc;
	CComPtr<IHTMLWindow2> spWindow;

	CHECK_HR_BAIL(hr = m_spClientSite->GetContainer(&spContainer));
	CHECK_HR_BAIL(hr = spContainer->QueryInterface(IID_IHTMLDocument2, (void**)&pDoc));
	CHECK_HR_BAIL(hr = pDoc->get_parentWindow(&spWindow));
	CHECK_HR_BAIL(hr = spWindow->QueryInterface(IID_IDispatch, (void**)&spDispatch));

bail:
	return hr;
}