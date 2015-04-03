/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/mediacapture-streams/#idl-def-SourceInfo

#pragma once
#include "resource.h"       // main symbols

#include "../common/_Config.h"
#include "../common/_Common.h"

#include "webrtceverywhere_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CSourceInfo

class ATL_NO_VTABLE CSourceInfo :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSourceInfo, &CLSID_SourceInfo>,
	public IDispatchImpl<ISourceInfo, &IID_ISourceInfo, &LIBID_webrtceverywhereLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CSourceInfo();

DECLARE_REGISTRY_RESOURCEID(IDR_SOURCEINFO)


BEGIN_COM_MAP(CSourceInfo)
	COM_INTERFACE_ENTRY(ISourceInfo)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();

	void FinalRelease();

	void SetInfo(std::shared_ptr<_SourceInfo> & info);
	std::shared_ptr<_SourceInfo> GetInfo();

public:
	STDMETHOD(get_sourceId)(__out BSTR* pVal);
	STDMETHOD(get_id)(__out BSTR* pVal);
	STDMETHOD(get_kind)(__out BSTR* pVal);
	STDMETHOD(get_label)(__out BSTR* pVal);
	STDMETHOD(get_facing)(__out BSTR* pVal);

private:
	std::shared_ptr<_SourceInfo> m_Info;
	
};

OBJECT_ENTRY_AUTO(__uuidof(SourceInfo), CSourceInfo)
