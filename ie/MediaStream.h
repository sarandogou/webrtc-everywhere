/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/mediacapture-streams/#mediastream

#pragma once
#include "resource.h"       // main symbols

#include "../common/_Config.h"
#include "../common/_Common.h"
#include "../common/_MediaStream.h"
#include "../common/_AsyncEvent.h"

#include "webrtceverywhere_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CMediaStream

class ATL_NO_VTABLE CMediaStream :
	public _AsyncEventRaiser,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMediaStream, &CLSID_MediaStream>,
	public IDispatchImpl<IMediaStream, &IID_IMediaStream, &LIBID_webrtceverywhereLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CMediaStream();

DECLARE_REGISTRY_RESOURCEID(IDR_MEDIASTREAM)


BEGIN_COM_MAP(CMediaStream)
	COM_INTERFACE_ENTRY(IMediaStream)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

public:

	void SetStream(std::shared_ptr<_MediaStream> & stream);
	std::shared_ptr<_MediaStream> GetStream();

	STDMETHOD(get_id)(__out BSTR* pVal);
	STDMETHOD(getAudioTracks)(__out VARIANT* Tracks);
	STDMETHOD(getVideoTracks)(__out VARIANT* Tracks);
	STDMETHOD(getTracks)(__out VARIANT* Tracks);
	STDMETHOD(getTrackById)(__in BSTR trackId, __out VARIANT* MediaStreamTrack);
	STDMETHOD(addTrack)(__in VARIANT MediaStreamTrack);
	STDMETHOD(removeTrack)(__in VARIANT MediaStreamTrack);
	STDMETHOD(clone)(__out VARIANT* MediaStream);
	STDMETHOD(get_ended)(__out VARIANT_BOOL* pVal);
	STDMETHOD(get_onended)(__out VARIANT* pVal);
	STDMETHOD(put_onended)(__in VARIANT newVal);
	STDMETHOD(get_onaddtrack)(__out VARIANT* pVal);
	STDMETHOD(put_onaddtrack)(__in VARIANT newVal);
	STDMETHOD(get_onremovetrack)(__out VARIANT* pVal);
	STDMETHOD(put_onremovetrack)(__in VARIANT newVal);
	STDMETHOD(stop)();

private:
	HRESULT getTracks(_TrackType type, VARIANT* Tracks);

	// callbacks
	void onended();
	void onaddtrack();
	void onremovetrack();

private:
	std::shared_ptr<_MediaStream> m_Stream;

	// callbacks
	CComPtr<IDispatch>m_callback_onended;
	CComPtr<IDispatch>m_callback_onaddtrack;
	CComPtr<IDispatch>m_callback_onremovetrack;
};

OBJECT_ENTRY_AUTO(__uuidof(MediaStream), CMediaStream)
