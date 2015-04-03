/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_NPAPI_PEERCONNECTION_H_
#define _WEBRTC_EVERYWHERE_NPAPI_PEERCONNECTION_H_

#include "../common/_Config.h"
#include "../common/_PeerConnection.h"
#include "../common/_AsyncEvent.h"
#include "../common/_Common.h"

#include "npapi-includes.h"

class PeerConnection
	: public NPObject
	, public _AsyncEventRaiser
	, public _UniqueObject
{
public:
	PeerConnection(NPP instance);
	virtual ~PeerConnection();

public:
	static NPObject* Allocate(NPP instance, NPClass* npclass);
	static void Deallocate(NPObject* obj);
	static bool HasMethod(NPObject* obj, NPIdentifier methodName);
	static bool InvokeDefault(NPObject* obj, const NPVariant* args,
		uint32_t argCount, NPVariant* result);
	static bool Invoke(NPObject* obj, NPIdentifier methodName,
		const NPVariant* args, uint32_t argCount,
		NPVariant* result);
	static bool HasProperty(NPObject* obj, NPIdentifier propertyName);
	static bool GetProperty(NPObject* obj, NPIdentifier propertyName,
		NPVariant* result);
	static bool SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value);
	static bool RemoveProperty(NPObject *npobj, NPIdentifier name);
	static bool NPEnumeration(NPObject *npobj, NPIdentifier **value,
		uint32_t *count);
	static void Invalidate(NPObject *npobj);
	static bool Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result);

	NPObjectImpl_CreateInstanceWithRef(PeerConnection);
	NPObjectImpl_NPObjectRelease(PeerConnection);
	NPObjectImpl_IsInstanceOf(PeerConnection);

	NPError Init(NPObject* RTCConfiguration, NPObject* MediaConstraints);

private:
	// callbacks
	void onnegotiationneeded();
	void onicecandidate(cpp11::shared_ptr<_RTCPeerConnectionIceEvent> e);
	void onsignalingstatechange();
	void onaddstream(cpp11::shared_ptr<_MediaStreamEvent> stream);
	void onremovestream(cpp11::shared_ptr<_MediaStreamEvent> stream);
	void oniceconnectionstatechange();
	void ondatachannel(cpp11::shared_ptr<_RTCDataChannelEvent> e);

	NPError getStreams(bool remote, NPVariant* MediaStreams);

private:
	NPP m_npp;
	cpp11::shared_ptr<_PeerConnection> m_Peer;

	// callbacks
	NPObject* m_callback_onnegotiationneeded;
	NPObject* m_callback_onicecandidate;
	NPObject* m_callback_onsignalingstatechange;
	NPObject* m_callback_onaddstream;
	NPObject* m_callback_onremovestream;
	NPObject* m_callback_oniceconnectionstatechange;
	NPObject* m_callback_ondatachannel;
};

#endif /* _WEBRTC_EVERYWHERE_NPAPI_PEERCONNECTION_H_ */
