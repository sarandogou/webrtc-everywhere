/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */

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

static const wchar_t kWindowlessClassName[] = L"WindowlessClass";
static const wchar_t kWindowlessTitle[] = L"WindowlessTitle";
ATOM CWebRTC::s_WindowlessClass = NULL;
HINSTANCE CWebRTC::s_hInstance = NULL;

CWebRTC::CWebRTC()
	: _AsyncEventDispatcher()
	, _RTCDisplay()
	, m_pTempVideoBuff(NULL)
	, m_spPresentSite(NULL)
	, m_spContainer(NULL)
	, m_spDoc(NULL)
	, m_spWindow(NULL)
	, m_hWindowlessHandle(NULL)
	, m_bVideoRendererStarted(FALSE)
{
	m_bWindowOnly = TRUE;
}

HRESULT CWebRTC::FinalConstruct()
{
	_Utils::Initialize();
	TakeFakePeerConnectionFactory();
	return S_OK;
}

void CWebRTC::FinalRelease()
{
	StopVideoRenderer();
	SetDispatcher(NULL);
	m_callbacks_onplay.clear();
	SafeDelete(&m_pTempVideoBuff);
	m_spPresentSite = NULL;
	m_spContainer = NULL;
	m_spDoc = NULL;
	m_spWindow = NULL;
	if (m_hWindowlessHandle) {
		::DestroyWindow(m_hWindowlessHandle);
		m_hWindowlessHandle = NULL;
	}
	ReleaseFakePeerConnectionFactory();
}

HRESULT CWebRTC::QueryWindow()
{
	HRESULT hr = E_UNEXPECTED;
	if (m_spWindow) {
		hr = S_OK;
	}
	else if (m_spClientSite) {
		m_spContainer = NULL;
		m_spDoc = NULL;
		hr = m_spClientSite->GetContainer(&m_spContainer);
		if (SUCCEEDED(hr)) {
			hr = m_spContainer->QueryInterface(IID_PPV_ARGS(&m_spDoc));
			if (SUCCEEDED(hr)) {
				hr = m_spDoc->get_parentWindow(&m_spWindow);
				if (SUCCEEDED(hr)) {
					hr = m_spWindow->get_location(&m_spLocation);
				}
			}
		}
	}
	
	if (SUCCEEDED(hr)) {
		// UserAgent
		static BOOL sUserAgentDefined = FALSE;
		if (!sUserAgentDefined) {
			IOmNavigator* pNavigator = NULL;
			if (SUCCEEDED(m_spWindow->get_navigator(&pNavigator))) {
				CComBSTR userAgentBSTR;
				if (SUCCEEDED(pNavigator->get_userAgent(&userAgentBSTR)) && userAgentBSTR.Length() > 0) {
					std::string userAgentStr;
					if (SUCCEEDED(Utils::ToString(&userAgentBSTR, userAgentStr)) && userAgentStr.length() > 0) {
						_Utils::SetUserAgent(userAgentStr.c_str());
						sUserAgentDefined = TRUE;
					}
				}
				SafeRelease(&pNavigator);
			}
		}
	}

	return hr;
}

// IOleObjectImpl::SetClientSite()
STDMETHODIMP CWebRTC::SetClientSite(_Inout_opt_ IOleClientSite *pClientSite)
{
	HRESULT hr = IOleObjectImpl::SetClientSite(pClientSite); // call base function
	if (SUCCEEDED(hr) && m_spClientSite) {
		HRESULT _hr = m_spClientSite->QueryInterface(IID_PPV_ARGS(&m_spPresentSite));
		if (FAILED(_hr)) {
			// IViewObjectPresentSite only supported on IE9 and later
		}
		else {
#if 0
			// OnDraw() for windowless Activex objects won't be called
			/*hr = */m_spPresentSite->SetCompositionMode(VIEW_OBJECT_COMPOSITION_MODE_SURFACEPRESENTER);
#endif
		}

		if (SUCCEEDED(QueryWindow())) {
			hr = Utils::InstallScripts(m_spWindow);
		}
	}
	return hr;
}

// IPersistPropertyBagImpl::Load
STDMETHODIMP CWebRTC::Load(__RPC__in_opt IPropertyBag *pPropBag, __RPC__in_opt IErrorLog *pErrorLog)
{
#if 0 // TODO(dmi) ignore the flag for now until everything is double checked
	CComVariant var;
	HRESULT hr = pPropBag->Read(L"windowless", &var, pErrorLog);
	if (SUCCEEDED(hr) && var.vt == VT_BSTR) {
		// Check if windowless drawing is possible (requires IE9 or later)
		m_bWindowOnly = wcscmp(_T("false"), var.bstrVal) == 0 ? TRUE : FALSE;
		if (!m_bWindowOnly && !m_hWindowlessHandle) {
			// Windowless
			if (!s_WindowlessClass) {
				if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
					GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
					reinterpret_cast<LPCWSTR>(&CWebRTC::WndProc), &s_hInstance)) {
					OutputDebugString(L"GetModuleHandleEx failed");
					return E_FAIL;
				}

				// Class not registered, register it.
				WNDCLASSEX wcex;
				memset(&wcex, 0, sizeof(wcex));
				wcex.cbSize = sizeof(wcex);
				wcex.hInstance = s_hInstance;
				wcex.lpfnWndProc = &CWebRTC::WndProc;
				wcex.lpszClassName = kWindowlessClassName;
				s_WindowlessClass = ::RegisterClassEx(&wcex);
				if (!s_WindowlessClass) {
					if (GetLastError() == ERROR_CLASS_ALREADY_EXISTS) {
						OutputDebugString(L"RegisterClassEx failed: ERROR_CLASS_ALREADY_EXISTS");
					}
					else {
						OutputDebugString(L"RegisterClassEx failed");
						return E_FAIL;
					}
				}
			} // if (!s_WindowlessClass)
			m_hWindowlessHandle = ::CreateWindowEx(0, kWindowlessClassName, kWindowlessTitle, 0,
				0, 0, 1, 1, NULL, NULL, s_hInstance, this);
			assert(m_hWindowlessHandle != NULL);
			if (m_hWindowlessHandle && !s_WindowlessClass) {
				s_WindowlessClass = GetClassWord(m_hWindowlessHandle, GCW_ATOM);
			}
			::SetWindowLongPtr(m_hWindowlessHandle, GWLP_USERDATA, (LONG_PTR)this);
			::ShowWindow(m_hWindowlessHandle, SW_HIDE);
		}
	}
#endif
	return S_OK;
}

// IOleInPlaceObject::SetObjectRects
STDMETHODIMP CWebRTC::SetObjectRects(__RPC__in LPCRECT lprcPosRect, __RPC__in LPCRECT lprcClipRect)
{
	return IOleInPlaceObjectWindowlessImpl::SetObjectRects(lprcPosRect, lprcClipRect); // IOleInPlaceObject::SetObjectRects(lprcPosRect, lprcClipRect); // call base function
}

// _RTCDisplay::Handle() implementation
HWND CWebRTC::Handle()
{
	return m_hWnd;
}

// _RTCDisplay::IsWindowless() implementation
BOOL CWebRTC::IsWindowless()
{
	return !m_bWindowOnly;
}

// _RTCDisplay::InvalidateWindowless() implementation
HRESULT CWebRTC::InvalidateWindowless(/* [unique][in] */ __RPC__in_opt LPCRECT pRect, /* [in] */ BOOL fErase)
{
	assert(IsWindowless());
	if (m_hWindowlessHandle) {
		// "m_spInPlaceSite->InvalidateRect" **MUST** be called on UI thread
		::PostMessage(m_hWindowlessHandle, WM_INVALIDATE_WINDOLESS, 0, 0); // TODO(dmi): pass "pRect" and "fErase" as LPARAM and WPARAM
	}
	return E_FAIL;
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
	m_bVideoRendererStarted = TRUE;
}

// _RTCDisplay::OnStopVideoRenderer() implementation
void CWebRTC::OnStopVideoRenderer()
{
	m_bVideoRendererStarted = FALSE;
}

LRESULT CWebRTC::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_bWindowOnly) {
		SetWindow(m_hWnd);
	}
	return S_OK;
}

LRESULT CWebRTC::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return S_OK;
}

HRESULT CWebRTC::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;
	// Set Clip region to the rectangle specified by di.prcBounds
	HRGN hRgnOld = NULL;
	if (GetClipRgn(di.hdcDraw, hRgnOld) != 1) {
		hRgnOld = NULL;
	}
	bool bSelectOldRgn = false;

	HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

	if (hRgnNew != NULL) {
		bSelectOldRgn = (SelectClipRgn(di.hdcDraw, hRgnNew) != ERROR);
	}

	if (m_bVideoRendererStarted) {
		PaintFrame(reinterpret_cast<intptr_t>(&di));
	}
	else {
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
		SetTextAlign(di.hdcDraw, TA_CENTER | TA_BASELINE);
		LPCTSTR pszText = _T("ATL 8.0 : Doubango Telecom WebRTC Video element");
#ifndef _WIN32_WCE
		TextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			pszText,
			lstrlen(pszText));
#else
		ExtTextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			ETO_OPAQUE,
			NULL,
			pszText,
			ATL::lstrlen(pszText),
			NULL);
#endif
	}

	if (bSelectOldRgn) {
		SelectClipRgn(di.hdcDraw, hRgnOld);
	}
	return S_OK;
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

#if 1
	bool gumAccepted;
	CComBSTR protocol;
	CComBSTR host;
	if (m_spLocation) {
		CHECK_HR_RETURN(hr = m_spLocation->get_protocol(&protocol));
		CHECK_HR_RETURN(hr = m_spLocation->get_host(&host));
	}
	CHECK_HR_RETURN(hr = _Utils::MsgBoxGUM(gumAccepted, protocol, host, m_hWnd));
	if (!gumAccepted) {
		if (_errorCallback) {
			BrowserCallback* _cb = new BrowserCallback(WM_GETUSERMEDIA_ERROR, _errorCallback);
			if (_cb) {
				CComBSTR err("Permission to access camera/microphone denied");
				_cb->AddBSTR(err);
				dynamic_cast<_AsyncEventDispatcher*>(this)->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
		}
		return S_OK;
	}
#endif

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

STDMETHODIMP CWebRTC::getScreenShot(__out BSTR* base64BitmapData)
{
	*base64BitmapData = NULL;

	int videoWidth = GetVideoWidth();
	int videoHeight = GetVideoHeight();

	if (videoHeight <= 0 || videoWidth <= 0) {
		return S_OK;
	}

	size_t videoSize = (videoWidth * videoHeight) << 2;
	if (!m_pTempVideoBuff || m_pTempVideoBuff->getSize() < videoSize){
		SafeDelete(&m_pTempVideoBuff);
		if ((_Buffer::New(NULL, videoSize, &m_pTempVideoBuff))) {
			CHECK_HR_RETURN(E_OUTOFMEMORY);
		}
	}

	if (CopyFromFrame(const_cast<void*>(m_pTempVideoBuff->getPtr()), videoSize) != videoSize) {
		memset(const_cast<void*>(m_pTempVideoBuff->getPtr()), 0, videoSize);
	}
	const uint8_t* imageDataPtr = (const uint8_t*)m_pTempVideoBuff->getPtr();
	
	WeError err;

	// Convert to Bitmap
	void* bmp_ptr = NULL;
	size_t bmp_size;
	if ((err = _Utils::ConvertToBMP(imageDataPtr, videoWidth, videoHeight, &bmp_ptr, &bmp_size)) != WeError_Success) {
		if (bmp_ptr) free(bmp_ptr);
		CHECK_HR_RETURN(E_FAIL);
	}
	// Convert to base64
	void* base64_ptr = NULL;
	size_t base64_size;
	err = _Utils::ConvertToBase64(bmp_ptr, bmp_size, &base64_ptr, &base64_size);
	free(bmp_ptr);
	HRESULT hr = E_FAIL;
	if (err == WeError_Success) {
		hr = Utils::CopyAnsiStr((LPCSTR)base64_ptr, base64BitmapData);
	}
	if (base64_ptr) free(base64_ptr);
	CHECK_HR_RETURN(hr);

	return S_OK;
}

STDMETHODIMP CWebRTC::get_isWebRtcPlugin(__out VARIANT_BOOL* pVal)
{
	*pVal = VARIANT_TRUE;
	return S_OK;
}

HRESULT CWebRTC::GetDispatch(CComPtr<IDispatch> &spDispatch)
{
	if (!m_spWindow) {
		CHECK_HR_RETURN(QueryWindow());
	}

	CHECK_HR_RETURN(m_spWindow->QueryInterface(IID_PPV_ARGS(&spDispatch)));
	return S_OK;
}

HRESULT CWebRTC::GetHTMLWindow2(CComPtr<IHTMLWindow2> &spWindow2)
{
	if (!m_spWindow) {
		CHECK_HR_RETURN(QueryWindow());
	}
	spWindow2 = m_spWindow;
	return S_OK;
}

LRESULT CALLBACK CWebRTC::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_INVALIDATE_WINDOLESS) {
		CWebRTC* This = dynamic_cast<CWebRTC*>(reinterpret_cast<CWebRTC*>(::GetWindowLongPtr(hwnd, GWLP_USERDATA)));
		This->m_spInPlaceSite->InvalidateRect(NULL, TRUE); // TODO(dmi): read wParam and lParam to get params for InvalidateRect
		return 1;
	}
	return ::DefWindowProc(hwnd, uMsg, wParam, lParam);
}
