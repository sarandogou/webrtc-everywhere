/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_NPAPI_RTCDATACHANNEL_H_
#define _WEBRTC_EVERYWHERE_NPAPI_RTCDATACHANNEL_H_

#include "../common/_Config.h"
#include "../common/_Common.h"
#include "../common/_AsyncEvent.h"
#include "../common/_RTCDataChannel.h"


#include "npapi-includes.h"

class RTCDataChannel
	: public NPObject
	, public _AsyncEventRaiser
{
public:
	RTCDataChannel(NPP instance);
	virtual ~RTCDataChannel();

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

	NPObjectImpl_CreateInstanceWithRef(RTCDataChannel);
	NPObjectImpl_NPObjectRelease(RTCDataChannel);
	NPObjectImpl_IsInstanceOf(RTCDataChannel);

	void SetChannel(cpp11::shared_ptr<_RTCDataChannel> & channel);
	cpp11::shared_ptr<_RTCDataChannel> GetChannel();

private:
	// callbacks
	void onopen();
	void onerror(cpp11::shared_ptr<std::string> string);
	void onclose();
	void onmessage(cpp11::shared_ptr<_MessageEvent> e);

private:
	NPP m_npp;

	// callbacks
	NPObject* m_callback_onopen;
	NPObject* m_callback_onerror;
	NPObject* m_callback_onclose;
	NPObject* m_callback_onmessage;

	cpp11::shared_ptr<_RTCDataChannel> m_Channel;
};

#endif /* _WEBRTC_EVERYWHERE_NPAPI_RTCDATACHANNEL_H_ */
