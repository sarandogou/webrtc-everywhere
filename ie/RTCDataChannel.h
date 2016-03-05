/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#idl-def-RTCDataChannel

#pragma once
#include "resource.h"       // main symbols

#include "../common/_Config.h"
#include "../common/_Common.h"
#include "../common/_AsyncEvent.h"
#include "../common/_RTCDataChannel.h"

#include "webrtceverywhere_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CRTCDataChannel

class ATL_NO_VTABLE CRTCDataChannel :
	public _AsyncEventRaiser,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRTCDataChannel, &CLSID_RTCDataChannel>,
	public IDispatchImpl<IRTCDataChannel, &IID_IRTCDataChannel, &LIBID_webrtceverywhereLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CRTCDataChannel();

DECLARE_REGISTRY_RESOURCEID(IDR_RTCDATACHANNEL)


BEGIN_COM_MAP(CRTCDataChannel)
	COM_INTERFACE_ENTRY(IRTCDataChannel)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();

	void FinalRelease();

public:
	STDMETHOD(get_label)(__out BSTR* pVal);
	STDMETHOD(get_ordered)(__out VARIANT_BOOL* pVal);
	STDMETHOD(get_maxRetransmitTime)(__out VARIANT* pVal);
	STDMETHOD(get_maxRetransmits)(__out VARIANT* pVal);
	STDMETHOD(get_protocol)(__out BSTR* pVal);
	STDMETHOD(get_negotiated)(__out VARIANT_BOOL* pVal);
	STDMETHOD(get_id)(__out VARIANT* pVal);
	STDMETHOD(get_readyState)(__out BSTR* pVal);
	STDMETHOD(get_bufferedAmount)(__out ULONG* pVal);
	STDMETHOD(get_binaryType)(__out BSTR* pVal);
	STDMETHOD(put_binaryType)(__in BSTR newVal);
	STDMETHOD(get_onopen)(__out VARIANT* pVal);
	STDMETHOD(put_onopen)(__in VARIANT newVal);
	STDMETHOD(get_onerror)(__out VARIANT* pVal);
	STDMETHOD(put_onerror)(__in VARIANT newVal);
	STDMETHOD(get_onclose)(__out VARIANT* pVal);
	STDMETHOD(put_onclose)(__in VARIANT newVal);
	STDMETHOD(get_onmessage)(__out VARIANT* pVal);
	STDMETHOD(put_onmessage)(__in VARIANT newVal);
	STDMETHOD(close)();
	STDMETHOD(send)(__in VARIANT data);

	void SetChannel(std::shared_ptr<_RTCDataChannel> & channel);
	std::shared_ptr<_RTCDataChannel> GetChannel();

private:
	void onopen();
	void onerror(cpp11::shared_ptr<std::string> string);
	void onclose();
	void onmessage(cpp11::shared_ptr<_MessageEvent> e);

private:
	CComPtr<IDispatch>m_callback_onopen;
	CComPtr<IDispatch>m_callback_onerror;
	CComPtr<IDispatch>m_callback_onclose;
	CComPtr<IDispatch>m_callback_onmessage;


	std::shared_ptr<_RTCDataChannel> m_Channel;
};

OBJECT_ENTRY_AUTO(__uuidof(RTCDataChannel), CRTCDataChannel)
