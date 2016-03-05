/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "NPCommon.h"
#include "RTCDTMFToneChangeEvent.h"
#include "Utils.h"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

#define kPropTone		"tone"

NPClass RTCDTMFToneChangeEventClass = {
	NP_CLASS_STRUCT_VERSION,
	RTCDTMFToneChangeEvent::Allocate,
	RTCDTMFToneChangeEvent::Deallocate,
	RTCDTMFToneChangeEvent::Invalidate,
	RTCDTMFToneChangeEvent::HasMethod,
	RTCDTMFToneChangeEvent::Invoke,
	RTCDTMFToneChangeEvent::InvokeDefault,
	RTCDTMFToneChangeEvent::HasProperty,
	RTCDTMFToneChangeEvent::GetProperty,
	RTCDTMFToneChangeEvent::SetProperty,
	RTCDTMFToneChangeEvent::RemoveProperty,
	RTCDTMFToneChangeEvent::NPEnumeration,
	RTCDTMFToneChangeEvent::Construct,
};

void RTCDTMFToneChangeEvent::Invalidate(NPObject *npobj)
{
}

bool RTCDTMFToneChangeEvent::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return false;
}

bool RTCDTMFToneChangeEvent::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

RTCDTMFToneChangeEvent::RTCDTMFToneChangeEvent(NPP instance)
	: m_npp(instance)
	, m_Event(nullPtr)
{
	WE_DEBUG_INFO("RTCDTMFToneChangeEvent::NewInstance()");
}

RTCDTMFToneChangeEvent::~RTCDTMFToneChangeEvent()
{
	m_Event = nullPtr;
}

NPObject* RTCDTMFToneChangeEvent::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new RTCDTMFToneChangeEvent(instance));
}

void RTCDTMFToneChangeEvent::Deallocate(NPObject* obj)
{
	delete (RTCDTMFToneChangeEvent*)obj;
}

bool RTCDTMFToneChangeEvent::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);

	bool ret_val = false;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDTMFToneChangeEvent::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool RTCDTMFToneChangeEvent::Invoke(NPObject* obj, NPIdentifier methodName,
	const NPVariant* args, uint32_t argCount,
	NPVariant* result)
{
	// RTCDTMFToneChangeEvent *This = static_cast<RTCDTMFToneChangeEvent*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(methodName);
	bool ret_val = false;
	if (!name) {
		return ret_val;
	}


	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDTMFToneChangeEvent::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val = !strcmp(name, kPropTone);

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDTMFToneChangeEvent::SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
	// all properties are readonly
	return false;
}

bool RTCDTMFToneChangeEvent::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	RTCDTMFToneChangeEvent *This = static_cast<RTCDTMFToneChangeEvent*>(obj);
	if (!This->m_Event) {
		return false;
	}
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropTone)) {
		NPUTF8* npStrId = (NPUTF8*)Utils::MemDup(This->m_Event->tone.c_str(), This->m_Event->tone.length());
		if (npStrId) {
			STRINGZ_TO_NPVARIANT(npStrId, *result);
			ret_val = true;
		}
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDTMFToneChangeEvent::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
	return false;
}
