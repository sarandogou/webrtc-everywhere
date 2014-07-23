/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/mediacapture-streams/#idl-def-MediaSourceStates

#pragma once
#include "resource.h"       // main symbols

#include "../common/_Config.h"
#include "../common/_Common.h"

#include "webrtceverywhere_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CMediaSourceStates

class ATL_NO_VTABLE CMediaSourceStates :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMediaSourceStates, &CLSID_MediaSourceStates>,
	public IDispatchImpl<IMediaSourceStates, &IID_IMediaSourceStates, &LIBID_webrtceverywhereLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMediaSourceStates();

DECLARE_REGISTRY_RESOURCEID(IDR_MEDIASOURCESTATES)


BEGIN_COM_MAP(CMediaSourceStates)
	COM_INTERFACE_ENTRY(IMediaSourceStates)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();

	void FinalRelease();

	void SetStates(std::shared_ptr<_MediaSourceStates> & states);
	std::shared_ptr<_MediaSourceStates> GetStates();

public:


	STDMETHOD(get_sourceType)(__out BSTR* pVal);
	STDMETHOD(get_sourceId)(__out BSTR* pVal);
	STDMETHOD(get_width)(__out VARIANT* pVal);
	STDMETHOD(get_height)(__out VARIANT* pVal);
	STDMETHOD(get_frameRate)(__out VARIANT* pVal);
	STDMETHOD(get_aspectRatio)(__out VARIANT* pVal);
	STDMETHOD(get_facingMode)(__out VARIANT* pVal);
	STDMETHOD(get_volume)(__out VARIANT* pVal);

private:
	std::shared_ptr<_MediaSourceStates> m_States;
	
};

OBJECT_ENTRY_AUTO(__uuidof(MediaSourceStates), CMediaSourceStates)
