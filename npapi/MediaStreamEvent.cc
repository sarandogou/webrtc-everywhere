/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "NPCommon.h"
#include "MediaStream.h"
#include "MediaStreamEvent.h"
#include "Utils.h"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

#define kPropStream		"stream"

NPClass MediaStreamEventClass = {
	NP_CLASS_STRUCT_VERSION,
	MediaStreamEvent::Allocate,
	MediaStreamEvent::Deallocate,
	MediaStreamEvent::Invalidate,
	MediaStreamEvent::HasMethod,
	MediaStreamEvent::Invoke,
	MediaStreamEvent::InvokeDefault,
	MediaStreamEvent::HasProperty,
	MediaStreamEvent::GetProperty,
	MediaStreamEvent::SetProperty,
	MediaStreamEvent::RemoveProperty,
	MediaStreamEvent::NPEnumeration,
	MediaStreamEvent::Construct,
};

void MediaStreamEvent::Invalidate(NPObject *npobj)
{
}

bool MediaStreamEvent::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return false;
}

bool MediaStreamEvent::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

MediaStreamEvent::MediaStreamEvent(NPP instance)
	: m_npp(instance)
	, m_Event(nullPtr)
{
	WE_DEBUG_INFO("MediaStreamEvent::NewInstance()");
}

MediaStreamEvent::~MediaStreamEvent()
{
	m_Event = nullPtr;
	SetDispatcher(NULL);
}

void MediaStreamEvent::SetEvent(cpp11::shared_ptr<_MediaStreamEvent> & e)
{
	m_Event = e;
}

cpp11::shared_ptr<_MediaStreamEvent> MediaStreamEvent::GetEvent()
{
	return m_Event;
}

NPObject* MediaStreamEvent::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new MediaStreamEvent(instance));
}

void MediaStreamEvent::Deallocate(NPObject* obj)
{
	delete (MediaStreamEvent*)obj;
}

bool MediaStreamEvent::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);

	bool ret_val = false;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MediaStreamEvent::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool MediaStreamEvent::Invoke(NPObject* obj, NPIdentifier methodName,
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

bool MediaStreamEvent::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val = !strcmp(name, kPropUniqueId) || !strcmp(name, kPropStream);

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MediaStreamEvent::SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
	// all properties are readonly
	return false;
}


bool MediaStreamEvent::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	MediaStreamEvent *This = static_cast<MediaStreamEvent*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropUniqueId)) {
		DOUBLE_TO_NPVARIANT(This->UniqueId(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropStream)) {
		if (This->m_Event) {
			if (This->m_Event->stream) {
				MediaStream* _stream;
				NPError err = MediaStream::CreateInstanceWithRef(This->m_npp, &_stream);
				if (err == NPERR_NO_ERROR) {
					_stream->SetStream(This->m_Event->stream);
					OBJECT_TO_NPVARIANT(_stream, *result);
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

bool MediaStreamEvent::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
	return false;
}
