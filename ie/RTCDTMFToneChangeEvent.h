/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#idl-def-RTCDTMFToneChangeEvent

#pragma once
#include "resource.h"       // main symbols

#include "../common/_Config.h"
#include "../common/_Common.h"

#include "webrtceverywhere_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CRTCDTMFToneChangeEvent

class ATL_NO_VTABLE CRTCDTMFToneChangeEvent :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRTCDTMFToneChangeEvent, &CLSID_RTCDTMFToneChangeEvent>,
	public IDispatchImpl<IRTCDTMFToneChangeEvent, &IID_IRTCDTMFToneChangeEvent, &LIBID_webrtceverywhereLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CRTCDTMFToneChangeEvent();

DECLARE_REGISTRY_RESOURCEID(IDR_RTCDTMFTONECHANGEEVENT)


BEGIN_COM_MAP(CRTCDTMFToneChangeEvent)
	COM_INTERFACE_ENTRY(IRTCDTMFToneChangeEvent)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();

	void FinalRelease();

public:
	WE_INLINE void SetEvent(std::shared_ptr<_RTCDTMFToneChangeEvent> & _event) { m_Event = _event; }
	WE_INLINE std::shared_ptr<_RTCDTMFToneChangeEvent> GetEvent() { return m_Event; }

private:
	std::shared_ptr<_RTCDTMFToneChangeEvent> m_Event;

public:

	STDMETHOD(get_tone)(BSTR* pVal);
};

OBJECT_ENTRY_AUTO(__uuidof(RTCDTMFToneChangeEvent), CRTCDTMFToneChangeEvent)
