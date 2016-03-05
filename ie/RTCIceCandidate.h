/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#rtcicecandidate-type

#pragma once
#include "resource.h"       // main symbols

#include "../common/_Config.h"
#include "../common/_Common.h"
#include "../common/_RTCIceCandidate.h"

#include "webrtceverywhere_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CRTCIceCandidate

class ATL_NO_VTABLE CRTCIceCandidate :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRTCIceCandidate, &CLSID_RTCIceCandidate>,
	public IDispatchImpl<IRTCIceCandidate, &IID_IRTCIceCandidate, &LIBID_webrtceverywhereLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CRTCIceCandidate();

DECLARE_REGISTRY_RESOURCEID(IDR_RTCICECANDIDATE)


BEGIN_COM_MAP(CRTCIceCandidate)
	COM_INTERFACE_ENTRY(IRTCIceCandidate)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();

	void FinalRelease();

public:
	HRESULT Init(VARIANT candidateInitDict);

	WE_INLINE void SetCandidate(std::shared_ptr<_RTCIceCandidate> & candidate) { m_Candidate = candidate; }
	WE_INLINE std::shared_ptr<_RTCIceCandidate> GetCandidate() { return m_Candidate; }

	STDMETHOD(get_candidate)(BSTR* pVal);
	STDMETHOD(get_sdpMid)(BSTR* pVal);
	STDMETHOD(get_sdpMLineIndex)(USHORT* pVal);

private:
	std::shared_ptr<_RTCIceCandidate> m_Candidate;	
};

OBJECT_ENTRY_AUTO(__uuidof(RTCIceCandidate), CRTCIceCandidate)
