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
#include <D3D9.h>
#include <D3D10_1.h> // Requires Windows Vista or later
#include <DXGI.h> // Requires Windows 7 or later

// http://msdn.microsoft.com/en-us/library/windows/desktop/bb694526(v=vs.85).aspx
typedef HRESULT(WINAPI *fnD3D10CreateDevice1)(
	_In_   IDXGIAdapter *pAdapter,
	_In_   D3D10_DRIVER_TYPE DriverType,
	_In_   HMODULE Software,
	_In_   UINT Flags,
	_In_   D3D10_FEATURE_LEVEL1 HardwareLevel,
	_In_   UINT SDKVersion,
	_Out_  ID3D10Device1 **ppDevice
	);
// http://msdn.microsoft.com/en-us/library/windows/desktop/ff471318(v=vs.85).aspx
typedef HRESULT(WINAPI *fnCreateDXGIFactory1)(
	_In_   REFIID riid,
	_Out_  void **ppFactory
	);


CWebRTC::CWebRTC()
	: _AsyncEventDispatcher()
	, _RTCDisplay()
	, m_pTempVideoBuff(NULL)
	, m_spPresentSite(NULL)
	, m_spSurfacePresenter(NULL)
	, m_spContainer(NULL)
	, m_spDoc(NULL)
	, m_spWindow(NULL)
	, m_nBackBuffWidth(0)
	, m_nbackBuffHeight(0)
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
	m_spSurfacePresenter = NULL;
	m_spText = NULL;
	m_spContainer = NULL;
	m_spDoc = NULL;
	m_spWindow = NULL;
	ReleaseFakePeerConnectionFactory();
}

#if 0
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
			/*hr = */m_spPresentSite->SetCompositionMode(VIEW_OBJECT_COMPOSITION_MODE_SURFACEPRESENTER);
		}

		HRESULT hr = S_OK;

		_hr = m_spClientSite->GetContainer(&m_spContainer);
		if (SUCCEEDED(_hr)) {
			_hr = m_spContainer->QueryInterface(IID_PPV_ARGS(&m_spDoc));
			if (SUCCEEDED(_hr)) {
				_hr = m_spDoc->get_parentWindow(&m_spWindow);
				if (SUCCEEDED(_hr)) {
					_hr = m_spWindow->get_location(&m_spLocation);
				}
			}
		}

		if (m_spWindow) {
			_hr = Utils::InstallScripts(m_spWindow);
		}
	}
	return hr;
}

// IPersistPropertyBagImpl::Load
STDMETHODIMP CWebRTC::Load(__RPC__in_opt IPropertyBag *pPropBag, __RPC__in_opt IErrorLog *pErrorLog)
{
	CComVariant var;
	HRESULT hr = pPropBag->Read(L"windowless", &var, pErrorLog);
	if (SUCCEEDED(hr) && var.vt == VT_BSTR) {
		// Check if windowless drawing is possible (requires IE9 or later)
		if (m_spPresentSite) {
			m_bWindowOnly = wcscmp(_T("false"), var.bstrVal) == 0 ? TRUE : FALSE;
		}
	}
	return S_OK;
}

// IOleInPlaceObject::SetObjectRects
STDMETHODIMP CWebRTC::SetObjectRects(__RPC__in LPCRECT lprcPosRect, __RPC__in LPCRECT lprcClipRect)
{
	HRESULT hr = IOleInPlaceObjectWindowlessImpl::SetObjectRects(lprcPosRect, lprcClipRect); // IOleInPlaceObject::SetObjectRects(lprcPosRect, lprcClipRect); // call base function
	if (SUCCEEDED(hr) && m_spPresentSite && !m_bWindowOnly) {
		LONG w = lprcPosRect->right - lprcPosRect->left;
		LONG h = lprcPosRect->bottom - lprcPosRect->top;
		if (w > 0 && h > 0) {
			CComPtr<ISurfacePresenter> spSurfacePresenter;
			CComPtr<ID3D10Device1> device = NULL;
			HMODULE d3d10_1_dll = LoadLibraryA("d3d10_1.dll");
			HMODULE dxgi_dll = NULL;
			HRESULT _hr;
			if (d3d10_1_dll) {
				fnD3D10CreateDevice1 implD3D10CreateDevice1 = (fnD3D10CreateDevice1)GetProcAddress(d3d10_1_dll, "D3D10CreateDevice1");
				if (implD3D10CreateDevice1) {
					CComPtr<IDXGIAdapter> adapter = NULL;
					dxgi_dll = LoadLibraryA("dxgi.dll");
					if (dxgi_dll && 0) {
						fnCreateDXGIFactory1 implCreateDXGIFactory1 = (fnCreateDXGIFactory1)GetProcAddress(dxgi_dll, "CreateDXGIFactory1");
						if (implCreateDXGIFactory1) {
							_hr = implCreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&adapter);
						}
					}
					_hr = implD3D10CreateDevice1(
						adapter,
						D3D10_DRIVER_TYPE_HARDWARE,
						NULL,
						D3D10_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS | D3D10_CREATE_DEVICE_BGRA_SUPPORT,
						D3D10_FEATURE_LEVEL_10_0,
						D3D10_1_SDK_VERSION,
						&device);
				}
			}
			_hr = m_spPresentSite->CreateSurfacePresenter(
				device,
				w,
				h,
				1,
				DXGI_FORMAT_B8G8R8A8_UNORM,
				VIEW_OBJECT_ALPHA_MODE_PREMULTIPLIED,
				&spSurfacePresenter);
			if (SUCCEEDED(_hr)) {
				D3D10_TEXTURE2D_DESC desc;
				desc.Width = w;
				desc.Height = h;
				desc.MipLevels = 1;
				desc.ArraySize = 1;
				desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				desc.SampleDesc.Count = 1;
				desc.SampleDesc.Quality = 0;
				desc.Usage = D3D10_USAGE_DYNAMIC;
				desc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
				desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
				desc.MiscFlags = 0;

				CComPtr<ID3D10Texture2D> spText = NULL;
				hr = device->CreateTexture2D(&desc, NULL, &spText);
				if (SUCCEEDED(hr)) {
					m_spSurfacePresenter = spSurfacePresenter;
					m_spText = spText;
					m_nBackBuffWidth = w;
					m_nbackBuffHeight = h;
				}
			}

			if (d3d10_1_dll) {
				FreeLibrary(d3d10_1_dll);
			}
			if (dxgi_dll) {
				FreeLibrary(dxgi_dll);
			}
		}
	}
	return hr;
}
#endif

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

// QuerySurfacePresenter::OnStopVideoRenderer() implementation
void CWebRTC::QuerySurfacePresenter(CComPtr<ISurfacePresenter> &spPtr, CComPtr<ID3D10Texture2D> &spText, int &backBuffWidth, int &backBuffHeight)
{
	backBuffWidth = m_nBackBuffWidth;
	backBuffHeight = m_nbackBuffHeight;
	spPtr = m_spSurfacePresenter;
	spText = m_spText;
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
		CHECK_HR_RETURN(E_POINTER);
	}

	CHECK_HR_RETURN(m_spWindow->QueryInterface(IID_PPV_ARGS(&spDispatch)));
	return S_OK;
}

HRESULT CWebRTC::GetHTMLWindow2(CComPtr<IHTMLWindow2> &spWindow2)
{
	if (!m_spWindow) {
		CHECK_HR_RETURN(E_POINTER);
	}
	spWindow2 = m_spWindow;
	return S_OK;
}
