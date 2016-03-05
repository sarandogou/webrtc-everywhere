/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "NPCommon.h"
#include "MediaSourceStates.h"
#include "Utils.h"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

#define kPropSourceType			"sourceType"
#define kPropSourceId			"sourceId"
#define kPropWidth				"width"
#define kPropHeight				"height"
#define kPropFrameRate			"frameRate"
#define kPropAspectRatio		"aspectRatio"
#define kPropFacingMode			"facingMode"
#define kPropVolume				"volume"


NPClass MediaSourceStatesClass = {
	NP_CLASS_STRUCT_VERSION,
	MediaSourceStates::Allocate,
	MediaSourceStates::Deallocate,
	MediaSourceStates::Invalidate,
	MediaSourceStates::HasMethod,
	MediaSourceStates::Invoke,
	MediaSourceStates::InvokeDefault,
	MediaSourceStates::HasProperty,
	MediaSourceStates::GetProperty,
	MediaSourceStates::SetProperty,
	MediaSourceStates::RemoveProperty,
	MediaSourceStates::NPEnumeration,
	MediaSourceStates::Construct,
};

void MediaSourceStates::Invalidate(NPObject *npobj)
{
}

bool MediaSourceStates::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return false;
}

bool MediaSourceStates::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

MediaSourceStates::MediaSourceStates(NPP instance)
	: m_npp(instance)
	, m_States(nullPtr)
{
	WE_DEBUG_INFO("MediaSourceStates::NewInstance()");
}

MediaSourceStates::~MediaSourceStates()
{
	m_States = nullPtr;
}

void MediaSourceStates::SetStates(cpp11::shared_ptr<_MediaSourceStates> & states)
{
	m_States = states;
}

cpp11::shared_ptr<_MediaSourceStates> MediaSourceStates::GetStates()
{
	return m_States;
}

NPObject* MediaSourceStates::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new MediaSourceStates(instance));
}

void MediaSourceStates::Deallocate(NPObject* obj)
{
	delete (MediaSourceStates*)obj;
}

bool MediaSourceStates::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);

	bool ret_val = false;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MediaSourceStates::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool MediaSourceStates::Invoke(NPObject* obj, NPIdentifier methodName,
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

bool MediaSourceStates::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val = !strcmp(name, kPropUniqueId) ||
		!strcmp(name, kPropSourceType) ||
		!strcmp(name, kPropSourceId) ||
		!strcmp(name, kPropWidth) ||
		!strcmp(name, kPropHeight) ||
		!strcmp(name, kPropFrameRate) ||
		!strcmp(name, kPropAspectRatio) ||
		!strcmp(name, kPropFacingMode) ||
		!strcmp(name, kPropVolume)
		;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MediaSourceStates::SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
	// all properties are readonly
	return false;
}

bool MediaSourceStates::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	MediaSourceStates *This = static_cast<MediaSourceStates*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropUniqueId)) {
		DOUBLE_TO_NPVARIANT(This->UniqueId(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropSourceType)) {
		if (This->m_States) {
			NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_States->sourceType.c_str(), This->m_States->sourceType.length());
			if (npStr) {
				STRINGZ_TO_NPVARIANT(npStr, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropSourceId)) {
		if (This->m_States) {
			NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_States->sourceId.c_str(), This->m_States->sourceId.length());
			if (npStr) {
				STRINGZ_TO_NPVARIANT(npStr, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropWidth)) {
		if (This->m_States) {
			if (This->m_States->width <= 0) {
				NULL_TO_NPVARIANT(*result);
			}
			else {
				INT32_TO_NPVARIANT((int32_t)This->m_States->width, *result);
			}
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropHeight)) {
		if (This->m_States) {
			if (This->m_States->height <= 0) {
				NULL_TO_NPVARIANT(*result);
			}
			else {
				INT32_TO_NPVARIANT((int32_t)This->m_States->height, *result);
			}
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropFrameRate)) {
		if (This->m_States) {
			if (This->m_States->frameRate <= 0) {
				NULL_TO_NPVARIANT(*result);
			}
			else {
				DOUBLE_TO_NPVARIANT(This->m_States->frameRate, *result);
			}
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropAspectRatio)) {
		if (This->m_States) {
			if (This->m_States->aspectRatio <= 0) {
				NULL_TO_NPVARIANT(*result);
			}
			else {
				DOUBLE_TO_NPVARIANT(This->m_States->aspectRatio, *result);
			}
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropFacingMode)) {
		if (This->m_States) {
			if (This->m_States->facingMode.empty()) {
				NULL_TO_NPVARIANT(*result);
			}
			else {
				NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_States->facingMode.c_str(), This->m_States->facingMode.length());
				if (npStr) {
					STRINGZ_TO_NPVARIANT(npStr, *result);
					ret_val = true;
				}
			}
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropVolume)) {
		if (This->m_States) {
            DOUBLE_TO_NPVARIANT((double)This->m_States->volume, *result);
			ret_val = true;
		}
	}
	
	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MediaSourceStates::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
	return false;
}
