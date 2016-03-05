/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "NPCommon.h"
#include "RTCStats.h"
#include "MessageEvent.h"
#include "Utils.h"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

#define kPropData		"data"

NPClass MessageEventClass = {
	NP_CLASS_STRUCT_VERSION,
	MessageEvent::Allocate,
	MessageEvent::Deallocate,
	MessageEvent::Invalidate,
	MessageEvent::HasMethod,
	MessageEvent::Invoke,
	MessageEvent::InvokeDefault,
	MessageEvent::HasProperty,
	MessageEvent::GetProperty,
	MessageEvent::SetProperty,
	MessageEvent::RemoveProperty,
	MessageEvent::NPEnumeration,
	MessageEvent::Construct,
};

void MessageEvent::Invalidate(NPObject *npobj)
{
}

bool MessageEvent::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return false;
}

bool MessageEvent::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

MessageEvent::MessageEvent(NPP instance)
	: m_npp(instance)
	, m_Event(nullPtr)
{
	WE_DEBUG_INFO("MessageEvent::NewInstance()");
	NULL_TO_NPVARIANT(m_data);
}

MessageEvent::~MessageEvent()
{
	m_Event = nullPtr;

	NPVariant* npVar = &m_data;
	Utils::NPVariantRelease(&npVar);

	SetDispatcher(NULL);
}

void MessageEvent::SetEvent(cpp11::shared_ptr<_MessageEvent> & _event)
{
	m_Event = _event;
}

cpp11::shared_ptr<_MessageEvent> MessageEvent::GetEvent()
{
	return m_Event;
}

NPObject* MessageEvent::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new MessageEvent(instance));
}

void MessageEvent::Deallocate(NPObject* obj)
{
	delete (MessageEvent*)obj;
}

bool MessageEvent::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);

	bool ret_val = false;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MessageEvent::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool MessageEvent::Invoke(NPObject* obj, NPIdentifier methodName,
	const NPVariant* args, uint32_t argCount,
	NPVariant* result)
{
	// MessageEvent *This = static_cast<MessageEvent*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(methodName);
	bool ret_val = false;
	if (!name) {
		return ret_val;
	}


	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MessageEvent::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val = !strcmp(name, kPropData);

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MessageEvent::SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
	// all properties are readonly
	return false;
}

bool MessageEvent::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	MessageEvent *This = static_cast<MessageEvent*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropData)) {
		NPError err = NPERR_NO_ERROR;
		if (NPVARIANT_IS_NULL(This->m_data) || NPVARIANT_IS_VOID(This->m_data)) {
			if (This->m_Event->binary) {
				const uint8_t* ptr = reinterpret_cast<const uint8_t*>(This->m_Event->data->getPtr());
				size_t size = This->m_Event->data->getSize();
				std::vector<NPVariant> vect;
				for (size_t i = 0; i < size; ++i) {
					NPVariant var;
					INT32_TO_NPVARIANT(ptr[i], var);
					vect.push_back(var);
				}

				NPObject* arrayObj = NULL;
				NPError err = Utils::CreateJsArrayEx(This->m_npp, vect, "Uint8Array", &arrayObj);
				if (err == NPERR_NO_ERROR) {
					err = Utils::NPObjectGetProp(This->m_npp, arrayObj, "buffer", &This->m_data);
				}

				Utils::NPVecClear(vect);
			}
			else {
				NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Event->data->getPtr(), This->m_Event->data->getSize());
				if (npStr) {
					STRINGN_TO_NPVARIANT(npStr, This->m_Event->data->getSize(), This->m_data);
				}
				else {
					err = NPERR_OUT_OF_MEMORY_ERROR;
				}
			}
		}
		if (err == NPERR_NO_ERROR) {
			if (NPVARIANT_IS_STRING(This->m_data)) {
				NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_data.value.stringValue.UTF8Characters, This->m_data.value.stringValue.UTF8Length);
				if (npStr) {
					STRINGN_TO_NPVARIANT(npStr, This->m_data.value.stringValue.UTF8Length, *result);
					ret_val = true;
				}
			}
			else if (NPVARIANT_IS_OBJECT(This->m_data)) {
				BrowserFuncs->retainobject(This->m_data.value.objectValue);
				OBJECT_TO_NPVARIANT(This->m_data.value.objectValue, *result);
				ret_val = true;
			}
		}
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MessageEvent::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
	return false;
}
