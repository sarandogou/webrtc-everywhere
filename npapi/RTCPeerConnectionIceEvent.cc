/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "NPCommon.h"
#include "RTCIceCandidate.h"
#include "RTCPeerConnectionIceEvent.h"
#include "Utils.h"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

#define kPropCandidate		"candidate"

NPClass RTCPeerConnectionIceEventClass = {
	NP_CLASS_STRUCT_VERSION,
	RTCPeerConnectionIceEvent::Allocate,
	RTCPeerConnectionIceEvent::Deallocate,
	RTCPeerConnectionIceEvent::Invalidate,
	RTCPeerConnectionIceEvent::HasMethod,
	RTCPeerConnectionIceEvent::Invoke,
	RTCPeerConnectionIceEvent::InvokeDefault,
	RTCPeerConnectionIceEvent::HasProperty,
	RTCPeerConnectionIceEvent::GetProperty,
	RTCPeerConnectionIceEvent::SetProperty,
	RTCPeerConnectionIceEvent::RemoveProperty,
	RTCPeerConnectionIceEvent::NPEnumeration,
	RTCPeerConnectionIceEvent::Construct,
};

void RTCPeerConnectionIceEvent::Invalidate(NPObject *npobj)
{
}

bool RTCPeerConnectionIceEvent::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return false;
}

bool RTCPeerConnectionIceEvent::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

RTCPeerConnectionIceEvent::RTCPeerConnectionIceEvent(NPP instance)
	: m_npp(instance)
	, m_Event(nullPtr)
{
	WE_DEBUG_INFO("RTCPeerConnectionIceEvent::NewInstance()");
}

RTCPeerConnectionIceEvent::~RTCPeerConnectionIceEvent()
{
	m_Event = nullPtr;
}

void RTCPeerConnectionIceEvent::SetEvent(cpp11::shared_ptr<_RTCPeerConnectionIceEvent> & e)
{
	m_Event = e;
}

cpp11::shared_ptr<_RTCPeerConnectionIceEvent> RTCPeerConnectionIceEvent::GetEvent()
{
	return m_Event;
}
NPObject* RTCPeerConnectionIceEvent::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new RTCPeerConnectionIceEvent(instance));
}

void RTCPeerConnectionIceEvent::Deallocate(NPObject* obj)
{
	delete (RTCPeerConnectionIceEvent*)obj;
}

bool RTCPeerConnectionIceEvent::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);

	bool ret_val = false;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCPeerConnectionIceEvent::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool RTCPeerConnectionIceEvent::Invoke(NPObject* obj, NPIdentifier methodName,
	const NPVariant* args, uint32_t argCount,
	NPVariant* result)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);
	bool ret_val = false;
	if (!name) {
		return ret_val;
	}



	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCPeerConnectionIceEvent::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val = !strcmp(name, kPropUniqueId) || !strcmp(name, kPropCandidate);

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCPeerConnectionIceEvent::SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
	// all properties are readonly
	return false;
}

bool RTCPeerConnectionIceEvent::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	RTCPeerConnectionIceEvent *This = static_cast<RTCPeerConnectionIceEvent*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropUniqueId)) {
		DOUBLE_TO_NPVARIANT(This->UniqueId(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropCandidate)) {
		if (This->m_Event) {
			if (This->m_Event->candidate) {
				RTCIceCandidate* _candidate;
				NPError err = RTCIceCandidate::CreateInstanceWithRef(This->m_npp, &_candidate);
				if (err == NPERR_NO_ERROR) {
					_candidate->SetCandidate(This->m_Event->candidate);
					OBJECT_TO_NPVARIANT(_candidate, *result);
					ret_val = true;
				}
			}
			else {
				NULL_TO_NPVARIANT(*result);
				ret_val = true;
			}
		}
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCPeerConnectionIceEvent::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
	return false;
}
