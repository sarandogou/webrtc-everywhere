/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/mediacapture-streams/#idl-def-MediaStreamTrack

#pragma once
#include "resource.h"       // main symbols

#include "../common/_Config.h"
#include "../common/_Common.h"
#include "../common/_MediaStreamTrack.h"
#include "../common/_AsyncEvent.h"

#include "webrtceverywhere_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CMediaStreamTrack

class ATL_NO_VTABLE CMediaStreamTrack :
	public _AsyncEventRaiser,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMediaStreamTrack, &CLSID_MediaStreamTrack>,
	public IDispatchImpl<IMediaStreamTrack, &IID_IMediaStreamTrack, &LIBID_webrtceverywhereLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMediaStreamTrack();

DECLARE_REGISTRY_RESOURCEID(IDR_MEDIASTREAMTRACK)


BEGIN_COM_MAP(CMediaStreamTrack)
	COM_INTERFACE_ENTRY(IMediaStreamTrack)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();

	void FinalRelease();

public:
	void SetTrack(std::shared_ptr<_MediaStreamTrack> & track);
	std::shared_ptr<_MediaStreamTrack> GetTrack();

private:
	std::shared_ptr<_MediaStreamTrack> m_Track;
public:

	STDMETHOD(get_kind)(__out BSTR* pVal);
	STDMETHOD(get_id)(__out BSTR* pVal);
	STDMETHOD(get_label)(__out BSTR* pVal);
	STDMETHOD(get_enabled)(__out VARIANT_BOOL* pVal);
	STDMETHOD(put_enabled)(__in VARIANT_BOOL newVal);
	STDMETHOD(get_muted)(__out VARIANT_BOOL* pVal);
	STDMETHOD(get_onmute)(__out VARIANT* pVal);
	STDMETHOD(put_onmute)(__in VARIANT newVal);
	STDMETHOD(get_onunmute)(__out VARIANT* pVal);
	STDMETHOD(put_onunmute)(__in VARIANT newVal);
	STDMETHOD(get_readonly)(__out VARIANT_BOOL* pVal);
	STDMETHOD(get_remote)(__out VARIANT_BOOL* pVal);
	STDMETHOD(get_readyState)(__out BSTR* pVal);
	STDMETHOD(get_onstarted)(__out VARIANT* pVal);
	STDMETHOD(put_onstarted)(__in VARIANT newVal);
	STDMETHOD(get_onended)(__out VARIANT* pVal);
	STDMETHOD(put_onended)(__in VARIANT newVal);
	STDMETHOD(getSourceInfos)(__out VARIANT* Infos);
	STDMETHOD(constraints)(__out VARIANT* MediaTrackConstraints);
	STDMETHOD(states)(__out VARIANT* MediaSourceStates);
	STDMETHOD(capabilities)(__out VARIANT* AllCapabilities);
	STDMETHOD(applyConstraints)(__in VARIANT MediaTrackConstraints);
	STDMETHOD(get_onoverconstrained)(__out VARIANT* pVal);
	STDMETHOD(put_onoverconstrained)(__in VARIANT newVal);
	STDMETHOD(clone)(__out VARIANT* MediaStreamTrack);
	STDMETHOD(stop)();

	// not part of the standard but used by Chrome
	static HRESULT getSources(__in CComPtr<IDispatch> spDispatch, __out VARIANT* Infos);

private:

	void onmute();
	void onunmute();
	void onstarted();
	void onended();
	void onoverconstrained();

private:
	CComPtr<IDispatch>m_callback_onmute;
	CComPtr<IDispatch>m_callback_onunmute;
	CComPtr<IDispatch>m_callback_onstarted;
	CComPtr<IDispatch>m_callback_onended;
	CComPtr<IDispatch>m_callback_onoverconstrained;
};

OBJECT_ENTRY_AUTO(__uuidof(MediaStreamTrack), CMediaStreamTrack)
