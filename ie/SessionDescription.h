/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#session-description-model

#pragma once
#include "../common/_Config.h"
#include "../common/_SessionDescription.h"
#include "resource.h"       // main symbols

#include "webrtceverywhere_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CSessionDescription

class ATL_NO_VTABLE CSessionDescription :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CSessionDescription, &CLSID_SessionDescription>,
    public IDispatchImpl<ISessionDescription, &IID_ISessionDescription, &LIBID_webrtceverywhereLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CSessionDescription();

    DECLARE_REGISTRY_RESOURCEID(IDR_SESSIONDESCRIPTION)


    BEGIN_COM_MAP(CSessionDescription)
    COM_INTERFACE_ENTRY(ISessionDescription)
    COM_INTERFACE_ENTRY(IDispatch)
    END_COM_MAP()



    DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

	HRESULT Init(VARIANT RTCSessionDescriptionInit);

public:
	WE_INLINE void SetSdp(std::shared_ptr<_SessionDescription> & sdp) { m_Sdp = sdp; }
	WE_INLINE std::shared_ptr<_SessionDescription> GetSdp() { return m_Sdp; }

    STDMETHOD(get_type)(__out BSTR* pVal);
	STDMETHOD(put_type)(__in BSTR newVal);
    STDMETHOD(get_sdp)(__out BSTR* pVal);
	STDMETHOD(put_sdp)(__in BSTR newVal);

	

private:
	std::shared_ptr<_SessionDescription> m_Sdp;
};

OBJECT_ENTRY_AUTO(__uuidof(SessionDescription), CSessionDescription)
