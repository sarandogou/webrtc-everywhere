/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "NPCommon.h"
#include "RTCDataChannel.h"
#include "RTCDataChannelEvent.h"
#include "Utils.h"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

#define kPropChannel		"channel"

NPClass RTCDataChannelEventClass = {
	NP_CLASS_STRUCT_VERSION,
	RTCDataChannelEvent::Allocate,
	RTCDataChannelEvent::Deallocate,
	RTCDataChannelEvent::Invalidate,
	RTCDataChannelEvent::HasMethod,
	RTCDataChannelEvent::Invoke,
	RTCDataChannelEvent::InvokeDefault,
	RTCDataChannelEvent::HasProperty,
	RTCDataChannelEvent::GetProperty,
	RTCDataChannelEvent::SetProperty,
	RTCDataChannelEvent::RemoveProperty,
	RTCDataChannelEvent::NPEnumeration,
	RTCDataChannelEvent::Construct,
};

void RTCDataChannelEvent::Invalidate(NPObject *npobj)
{
}

bool RTCDataChannelEvent::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return false;
}

bool RTCDataChannelEvent::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

RTCDataChannelEvent::RTCDataChannelEvent(NPP instance)
	: m_npp(instance)
	, m_Event(nullPtr)
{
	WE_DEBUG_INFO("RTCDataChannelEvent::NewInstance()");
}

RTCDataChannelEvent::~RTCDataChannelEvent()
{
	m_Event = nullPtr;

	SetDispatcher(NULL);
}

NPObject* RTCDataChannelEvent::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new RTCDataChannelEvent(instance));
}

void RTCDataChannelEvent::Deallocate(NPObject* obj)
{
	delete (RTCDataChannelEvent*)obj;
}

bool RTCDataChannelEvent::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);

	bool ret_val = false;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDataChannelEvent::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool RTCDataChannelEvent::Invoke(NPObject* obj, NPIdentifier methodName,
	const NPVariant* args, uint32_t argCount,
	NPVariant* result)
{
	// RTCDataChannelEvent *This = static_cast<RTCDataChannelEvent*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(methodName);
	bool ret_val = false;
	if (!name) {
		return ret_val;
	}


	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDataChannelEvent::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val = !strcmp(name, kPropChannel);

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDataChannelEvent::SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
	// all properties are readonly
	return false;
}

bool RTCDataChannelEvent::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	RTCDataChannelEvent *This = static_cast<RTCDataChannelEvent*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropChannel)) {
		if (!This->m_Event) {
			NULL_TO_NPVARIANT(*result);
			ret_val = true;
		}
		else {
			RTCDataChannel* _dataChannel = NULL;
			NPError err = RTCDataChannel::CreateInstanceWithRef(This->m_npp, &_dataChannel);
			if (err == NPERR_NO_ERROR) {
				_dataChannel->SetChannel(This->m_Event->channel);
				_dataChannel->SetDispatcher(const_cast<_AsyncEventDispatcher*>(This->GetDispatcher()));
				OBJECT_TO_NPVARIANT(_dataChannel, *result); _dataChannel = NULL;
				RTCDataChannel::ReleaseInstance(&_dataChannel);
				ret_val = true;
			}
		}
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDataChannelEvent::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
	return false;
}

