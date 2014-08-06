/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/wiki/HTML/Elements/video
#pragma once
#include "../common/_Config.h"
#include "../common/_AsyncEvent.h"
#include "../common/_RTCDisplay.h"
#include "../common/_Common.h"
#include "../common/_Buffer.h"
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "webrtceverywhere_i.h"
#include "_IWebRTCEvents_CP.h"

#include <comutil.h>
#include <stdio.h>

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif


// CWebRTC
class ATL_NO_VTABLE CWebRTC :
	public _AsyncEventDispatcher,
	public _AsyncEventRaiser,
	public _RTCDisplay,
    public CComObjectRootEx<CComSingleThreadModel>,
    public IDispatchImpl<IWebRTC, &IID_IWebRTC, &LIBID_webrtceverywhereLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
    public IPersistStreamInitImpl<CWebRTC>,
    public IOleControlImpl<CWebRTC>,
    public IOleObjectImpl<CWebRTC>,
    public IOleInPlaceActiveObjectImpl<CWebRTC>,
    public IViewObjectExImpl<CWebRTC>,
    public IOleInPlaceObjectWindowlessImpl<CWebRTC>,
    public ISupportErrorInfo,
    public IConnectionPointContainerImpl<CWebRTC>,
    public CProxy_IWebRTCEvents<CWebRTC>,
    public IPersistStorageImpl<CWebRTC>,
	public IPersistPropertyBagImpl<CWebRTC>,
    public ISpecifyPropertyPagesImpl<CWebRTC>,
    public IQuickActivateImpl<CWebRTC>,
#ifndef _WIN32_WCE
    public IDataObjectImpl<CWebRTC>,
#endif
    public IProvideClassInfo2Impl<&CLSID_WebRTC, &__uuidof(_IWebRTCEvents), &LIBID_webrtceverywhereLib>,
#ifdef _WIN32_WCE // IObjectSafety is required on Windows CE for the control to be loaded correctly
    public IObjectSafetyImpl<CWebRTC, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
#endif
    public CComCoClass<CWebRTC, &CLSID_WebRTC>,
    public CComControl<CWebRTC>,
    public IObjectSafetyImpl<CWebRTC, INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA>
{
public:


	CWebRTC();

    DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
                           OLEMISC_CANTLINKINSIDE |
                           OLEMISC_INSIDEOUT |
                           OLEMISC_ACTIVATEWHENVISIBLE |
                           OLEMISC_SETCLIENTSITEFIRST
                          )

    DECLARE_REGISTRY_RESOURCEID(IDR_WEBRTC)


    BEGIN_COM_MAP(CWebRTC)
    COM_INTERFACE_ENTRY(IWebRTC)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(IViewObjectEx)
    COM_INTERFACE_ENTRY(IViewObject2)
    COM_INTERFACE_ENTRY(IViewObject)
    COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
    COM_INTERFACE_ENTRY(IOleInPlaceObject)
    COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
    COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
    COM_INTERFACE_ENTRY(IOleControl)
    COM_INTERFACE_ENTRY(IOleObject)
    COM_INTERFACE_ENTRY(IPersistStreamInit)
    COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
    COM_INTERFACE_ENTRY(IConnectionPointContainer)
    COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
    COM_INTERFACE_ENTRY(IQuickActivate)
    COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IPersistPropertyBag)
#ifndef _WIN32_WCE
    COM_INTERFACE_ENTRY(IDataObject)
#endif
    COM_INTERFACE_ENTRY(IProvideClassInfo)
    COM_INTERFACE_ENTRY(IProvideClassInfo2)
#ifdef _WIN32_WCE // IObjectSafety is required on Windows CE for the control to be loaded correctly
    COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
#endif
    COM_INTERFACE_ENTRY(IObjectSafety)
    END_COM_MAP()

    BEGIN_PROP_MAP(CWebRTC)
    PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
    PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
    // Example entries
    // PROP_ENTRY_TYPE("Property Name", dispid, clsid, vtType)
    // PROP_PAGE(CLSID_StockColorPage)
    END_PROP_MAP()

    BEGIN_CONNECTION_POINT_MAP(CWebRTC)
    CONNECTION_POINT_ENTRY(__uuidof(_IWebRTCEvents))
    END_CONNECTION_POINT_MAP()

    BEGIN_MSG_MAP(CWebRTC)
    CHAIN_MSG_MAP(CComControl<CWebRTC>)
    DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
    END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid) {
        static const IID* arr[] = {
            &IID_IWebRTC,
        };

        for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++) {
            if (InlineIsEqualGUID(*arr[i], riid)) {
                return S_OK;
            }
        }
        return S_FALSE;
    }

// IViewObjectEx
    DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IWebRTC
public:
    HRESULT OnDraw(ATL_DRAWINFO& di) {
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

        Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
        SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
        LPCTSTR pszText = _T("ATL 8.0 : WebRTC");
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

        if (bSelectOldRgn) {
            SelectClipRgn(di.hdcDraw, hRgnOld);
        }

        return S_OK;
    }


    DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void FinalRelease();

	BrowserObjectImpl_IUnknown();

    STDMETHOD(get_versionName)(BSTR* pVal);
	STDMETHOD(getUserMedia)(VARIANT constraints, VARIANT successCallback, VARIANT errorCallback);
	STDMETHOD(createDisplay)(__out IDispatch** ppDisplay);
	STDMETHOD(createSessionDescription)(VARIANT RTCSessionDescriptionInit, IDispatch** ppSdp);
    STDMETHOD(createDictOptions)(IDispatch** ppDictOptions);
    STDMETHOD(createPeerConnection)(VARIANT RTCConfiguration, VARIANT MediaConstraints, IDispatch** ppPeerConnection);
	STDMETHOD(createIceCandidate)(VARIANT RTCIceCandidateInit, IDispatch** ppIceCandidate);
	STDMETHOD(createMediaStreamTrack)(__out IDispatch** ppMediaStreamTrack);

	STDMETHOD(bindEventListener)(__in BSTR type, __in_opt VARIANT listenerCallback, __in_opt VARIANT useCapture);
	STDMETHOD(getSources)(__in_opt VARIANT successCallback);

	STDMETHOD(put_src)(__in VARIANT newVal);
	STDMETHOD(fillImageData)(__in VARIANT imageData);
	STDMETHOD(getScreenShot)(__out BSTR* base64BitmapData);
	STDMETHOD(get_videoWidth)(__out LONG* pVal);
	STDMETHOD(get_videoHeight)(__out LONG* pVal);
	STDMETHOD(get_isWebRtcPlugin)(__out VARIANT_BOOL* pVal);

	// IOleObjectImpl::SetClientSite()
	STDMETHOD(SetClientSite)(_Inout_opt_ IOleClientSite *pClientSite);

	// IPersistPropertyBagImpl::Load
	STDMETHOD(Load)(__RPC__in_opt IPropertyBag *pPropBag, __RPC__in_opt IErrorLog *pErrorLog);

	// IOleInPlaceObject::SetObjectRects
	STDMETHOD(SetObjectRects)(__RPC__in LPCRECT lprcPosRect, __RPC__in LPCRECT lprcClipRect);
	

	// _RTCDisplay implementation
	virtual HWND Handle();
	virtual void OnStartVideoRenderer();
	virtual void OnStopVideoRenderer();
	virtual void QuerySurfacePresenter(CComPtr<ISurfacePresenter> &spPtr, CComPtr<ID3D10Texture2D> &spText, int &backBuffWidth, int &backBuffHeight);

	
	HRESULT GetDispatch(CComPtr<IDispatch> &spDispatch);
	HRESULT GetHTMLWindow2(CComPtr<IHTMLWindow2> &spWindow2);

	private:
		_Buffer *m_pTempVideoBuff;
		std::vector<CComPtr<IDispatch>>m_callbacks_onplay;
		CComPtr<IViewObjectPresentSite> m_spPresentSite;
		CComPtr<ISurfacePresenter> m_spSurfacePresenter;
		CComPtr<ID3D10Texture2D> m_spText;
		CComPtr<IHTMLLocation> m_spLocation;
		CComPtr<IOleContainer> m_spContainer;
		CComPtr<IHTMLDocument2> m_spDoc;
		CComPtr<IHTMLWindow2> m_spWindow;
		int m_nBackBuffWidth;
		int m_nbackBuffHeight;
};

OBJECT_ENTRY_AUTO(__uuidof(WebRTC), CWebRTC)
