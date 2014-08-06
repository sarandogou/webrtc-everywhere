/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */

#pragma once
#include "resource.h"       // main symbols

#include "../common/_Config.h"
#include "../common/_Common.h"
#include "../common/_AsyncEvent.h"

#include "webrtceverywhere_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CRTCPeerConnectionIceEvent

class ATL_NO_VTABLE CRTCPeerConnectionIceEvent :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRTCPeerConnectionIceEvent, &CLSID_RTCPeerConnectionIceEvent>,
	public IDispatchImpl<IRTCPeerConnectionIceEvent, &IID_IRTCPeerConnectionIceEvent, &LIBID_webrtceverywhereLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CRTCPeerConnectionIceEvent();

DECLARE_REGISTRY_RESOURCEID(IDR_RTCPEERCONNECTIONICEEVENT)


BEGIN_COM_MAP(CRTCPeerConnectionIceEvent)
	COM_INTERFACE_ENTRY(IRTCPeerConnectionIceEvent)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();

	void FinalRelease();

public:
	void SetEvent(std::shared_ptr<_RTCPeerConnectionIceEvent> & e);
	std::shared_ptr<_RTCPeerConnectionIceEvent> GetEvent();

	STDMETHOD(get_candidate)(__out VARIANT* pVal);

private:
	std::shared_ptr<_RTCPeerConnectionIceEvent> m_Event;

};

OBJECT_ENTRY_AUTO(__uuidof(RTCPeerConnectionIceEvent), CRTCPeerConnectionIceEvent)
