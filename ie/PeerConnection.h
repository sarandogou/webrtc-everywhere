/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#interface-definition
// http://www.w3.org/TR/webrtc/#rtcpeerconnection-interface-extensions-1
// http://www.w3.org/TR/webrtc/#rtcpeerconnection-interface-extensions-2

#pragma once
#include "resource.h"       // main symbols

#include "webrtceverywhere_i.h"

#include "../common/_Config.h"
#include "../common/_PeerConnection.h"
#include "../common/_AsyncEvent.h"
#include "../common/_Common.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CPeerConnection

class ATL_NO_VTABLE CPeerConnection :
	public _AsyncEventRaiser,
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CPeerConnection, &CLSID_PeerConnection>,
    public IDispatchImpl<IPeerConnection, &IID_IPeerConnection, &LIBID_webrtceverywhereLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CPeerConnection();

    DECLARE_REGISTRY_RESOURCEID(IDR_PEERCONNECTION)


    BEGIN_COM_MAP(CPeerConnection)
    COM_INTERFACE_ENTRY(IPeerConnection)
    COM_INTERFACE_ENTRY(IDispatch)
    END_COM_MAP()



    DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();

	void FinalRelease();

	BrowserObjectImpl_IUnknown();

public:
	HRESULT Init(VARIANT RTCConfiguration, VARIANT MediaConstraints);

	STDMETHOD(createOffer)(__in_opt VARIANT successCallback, __in_opt VARIANT failureCallback, __in_opt VARIANT MediaConstraints);
	STDMETHOD(createAnswer)(__in_opt VARIANT successCallback, __in_opt VARIANT failureCallback, __in_opt VARIANT MediaConstraints);
	STDMETHOD(setLocalDescription)(__in VARIANT RTCSessionDescription, __in_opt VARIANT successCallback, __in_opt VARIANT failureCallback);
	STDMETHOD(get_localDescription)(__out VARIANT* pVal);
	STDMETHOD(setRemoteDescription)(__in VARIANT RTCSessionDescription, __in_opt VARIANT successCallback, __in_opt VARIANT failureCallback);
	STDMETHOD(get_remoteDescription)(__out VARIANT* pVal);
	STDMETHOD(get_signalingState)(__out BSTR* pVal);
	STDMETHOD(updateIce)(__in VARIANT RTCConfiguration, __in_opt VARIANT MediaConstraints);
	STDMETHOD(addIceCandidate)(__in VARIANT RTCIceCandidate, __in VARIANT successCallback, __in VARIANT failureCallback);
	STDMETHOD(get_iceGatheringState)(__out BSTR* pVal);
	STDMETHOD(get_iceConnectionState)(__out BSTR* pVal);
	STDMETHOD(getLocalStreams)(__out VARIANT* MediaStreams);
	STDMETHOD(getRemoteStreams)(__out VARIANT* MediaStreams);
	STDMETHOD(getStreamById)(__in BSTR streamId, __out VARIANT* MediaStream);
	STDMETHOD(addStream)(__in VARIANT stream, __in_opt VARIANT MediaConstraints);
	STDMETHOD(removeStream)(__in VARIANT stream);
	STDMETHOD(close)();
	STDMETHOD(getStats)(__in VARIANT selector, __in_opt VARIANT successCallback, __in_opt VARIANT failureCallback);
	STDMETHOD(createDTMFSender)(__in VARIANT MediaStreamTrack, __out VARIANT* RTCDTMFSender);
	STDMETHOD(createDataChannel)(__in BSTR label, __in_opt VARIANT dataChannelDict, __out VARIANT* DataChannel);

	STDMETHOD(put_onnegotiationneeded)(__in VARIANT newVal);
	STDMETHOD(get_onnegotiationneeded)(__out VARIANT* pVal);
	STDMETHOD(put_onicecandidate)(__in VARIANT newVal);
	STDMETHOD(get_onicecandidate)(__out VARIANT* pVal);
	STDMETHOD(put_onsignalingstatechange)(__in VARIANT newVal);
	STDMETHOD(get_onsignalingstatechange)(__out VARIANT* pVal);
	STDMETHOD(put_onaddstream)(__in VARIANT newVal);
	STDMETHOD(get_onaddstream)(__out VARIANT* pVal);
	STDMETHOD(put_onremovestream)(__in VARIANT newVal);
	STDMETHOD(get_onremovestream)(__out VARIANT* pVal);
	STDMETHOD(put_oniceconnectionstatechange)(__in VARIANT newVal);
	STDMETHOD(get_oniceconnectionstatechange)(__out VARIANT* pVal);
	STDMETHOD(put_ondatachannel)(__in VARIANT newVal);
	STDMETHOD(get_ondatachannel)(__out VARIANT* pVal);

private:
	// callbacks
	void onnegotiationneeded();
	void onicecandidate(std::shared_ptr<_RTCPeerConnectionIceEvent> e);
	void onsignalingstatechange();
	void onaddstream(std::shared_ptr<_MediaStreamEvent> stream);
	void onremovestream(std::shared_ptr<_MediaStreamEvent> stream);
	void oniceconnectionstatechange();
	void ondatachannel(cpp11::shared_ptr<_RTCDataChannelEvent> e);

	HRESULT getStreams(__in BOOL remote, __out VARIANT* MediaStreams);

private:
	std::shared_ptr<_PeerConnection> m_Peer;

	// callbacks
	CComPtr<IDispatch>m_callback_onnegotiationneeded;
	CComPtr<IDispatch>m_callback_onicecandidate;
	CComPtr<IDispatch>m_callback_onsignalingstatechange;
	CComPtr<IDispatch>m_callback_onaddstream;
	CComPtr<IDispatch>m_callback_onremovestream;
	CComPtr<IDispatch>m_callback_oniceconnectionstatechange;
	CComPtr<IDispatch>m_callback_ondatachannel;
public:

	
};

OBJECT_ENTRY_AUTO(__uuidof(PeerConnection), CPeerConnection)
