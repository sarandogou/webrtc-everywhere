/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#rtcdtmfsender
#pragma once
#include "resource.h"       // main symbols

#include "../common/_Config.h"
#include "../common/_Common.h"
#include "../common/_MediaStreamTrack.h"
#include "../common/_AsyncEvent.h"
#include "../common/_RTCDTMFSender.h"

#include "webrtceverywhere_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CRTCDTMFSender

class ATL_NO_VTABLE CRTCDTMFSender :
	public _AsyncEventRaiser,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRTCDTMFSender, &CLSID_RTCDTMFSender>,
	public IDispatchImpl<IRTCDTMFSender, &IID_IRTCDTMFSender, &LIBID_webrtceverywhereLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CRTCDTMFSender();

DECLARE_REGISTRY_RESOURCEID(IDR_RTCDTMFSENDER)


BEGIN_COM_MAP(CRTCDTMFSender)
	COM_INTERFACE_ENTRY(IRTCDTMFSender)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();

	void FinalRelease();

public:
	void SetSender(std::shared_ptr<_RTCDTMFSender> & sender);
	std::shared_ptr<_RTCDTMFSender> GetSender();

private:
	void ontonechange(cpp11::shared_ptr<_RTCDTMFToneChangeEvent> e);

private:
	std::shared_ptr<_RTCDTMFSender> m_Sender;
	CComPtr<IDispatch>m_callback_ontonechange;

public:

	STDMETHOD(get_canInsertDTMF)(__out VARIANT_BOOL* pVal);
	STDMETHOD(insertDTMF)(__in BSTR tones, __in_opt VARIANT duration, __in_opt VARIANT interToneGap);
	STDMETHOD(get_track)(__out VARIANT* pMediaStreamTrack);
	STDMETHOD(get_ontonechange)(__out VARIANT* pVal);
	STDMETHOD(put_ontonechange)(__in VARIANT newVal);
	STDMETHOD(get_toneBuffer)(__out BSTR* pVal);
	STDMETHOD(get_duration)(__out LONG* pVal);
	STDMETHOD(get_interToneGap)(__out LONG* pVal);
};

OBJECT_ENTRY_AUTO(__uuidof(RTCDTMFSender), CRTCDTMFSender)
