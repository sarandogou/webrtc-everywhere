/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#event-datachannel-message

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


// CMessageEvent

class ATL_NO_VTABLE CMessageEvent :
	public _AsyncEventRaiser,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMessageEvent, &CLSID_MessageEvent>,
	public IDispatchImpl<IMessageEvent, &IID_IMessageEvent, &LIBID_webrtceverywhereLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMessageEvent();

DECLARE_REGISTRY_RESOURCEID(IDR_MESSAGEEVENT)


BEGIN_COM_MAP(CMessageEvent)
	COM_INTERFACE_ENTRY(IMessageEvent)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();

	void FinalRelease();

	STDMETHOD(get_data)(VARIANT* pVal);

	void SetEvent(std::shared_ptr<_MessageEvent> & _event);
	std::shared_ptr<_MessageEvent> GetEvent();

private:
	std::shared_ptr<_MessageEvent> m_Event;
	CComVariant m_data;
};

OBJECT_ENTRY_AUTO(__uuidof(MessageEvent), CMessageEvent)
