/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "NPCommon.h"
#include "SourceInfo.h"
#include "Utils.h"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

#define kPropSourceId						"sourceId"
#define kPropId								"id"
#define kPropKind							"kind"
#define kPropLabel							"label"
#define kPropFacing							"facing"

NPClass SourceInfoClass = {
	NP_CLASS_STRUCT_VERSION,
	SourceInfo::Allocate,
	SourceInfo::Deallocate,
	SourceInfo::Invalidate,
	SourceInfo::HasMethod,
	SourceInfo::Invoke,
	SourceInfo::InvokeDefault,
	SourceInfo::HasProperty,
	SourceInfo::GetProperty,
	SourceInfo::SetProperty,
	SourceInfo::RemoveProperty,
	SourceInfo::NPEnumeration,
	SourceInfo::Construct,
};

void SourceInfo::Invalidate(NPObject *npobj)
{
}

bool SourceInfo::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return false;
}

bool SourceInfo::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

SourceInfo::SourceInfo(NPP instance)
	: m_npp(instance)
	, m_Info(nullPtr)
{
	WE_DEBUG_INFO("SourceInfo::NewInstance()");
}

SourceInfo::~SourceInfo()
{
	m_Info = nullPtr;
}

void SourceInfo::SetInfo(cpp11::shared_ptr<_SourceInfo> & info)
{
	m_Info = info;
}

cpp11::shared_ptr<_SourceInfo> SourceInfo::GetInfo()
{
	return m_Info;
}

NPObject* SourceInfo::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new SourceInfo(instance));
}

void SourceInfo::Deallocate(NPObject* obj)
{
	delete (SourceInfo*)obj;
}

bool SourceInfo::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);

	bool ret_val = false;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool SourceInfo::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool SourceInfo::Invoke(NPObject* obj, NPIdentifier methodName,
	const NPVariant* args, uint32_t argCount,
	NPVariant* result)
{
	// SourceInfo *This = dynamic_cast<SourceInfo*>((SourceInfo*)obj);
	char* name = BrowserFuncs->utf8fromidentifier(methodName);
	bool ret_val = false;
	if (!name) {
		return ret_val;
	}



	BrowserFuncs->memfree(name);
	return ret_val;
}

bool SourceInfo::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val = !strcmp(name, kPropUniqueId) ||
		!strcmp(name, kPropSourceId) ||
		!strcmp(name, kPropId) ||
		!strcmp(name, kPropKind) ||
		!strcmp(name, kPropLabel) ||
		!strcmp(name, kPropFacing)
		;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool SourceInfo::SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
	// all properties are readonly
	return false;
}

bool SourceInfo::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	SourceInfo *This = static_cast<SourceInfo*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropUniqueId)) {
		DOUBLE_TO_NPVARIANT(This->UniqueId(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropSourceId) || !strcmp(name, kPropId)) {
		if (This->m_Info) {
			NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Info->sourceId.c_str(), This->m_Info->sourceId.length());
			if (npStr) {
				STRINGZ_TO_NPVARIANT(npStr, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropKind)) {
		if (This->m_Info) {
			NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Info->kind.c_str(), This->m_Info->kind.length());
			if (npStr) {
				STRINGZ_TO_NPVARIANT(npStr, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropLabel) ) {
		if (This->m_Info) {
			NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Info->label.c_str(), This->m_Info->label.length());
			if (npStr) {
				STRINGZ_TO_NPVARIANT(npStr, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropFacing)) {
		if (This->m_Info) {
			NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Info->facing.c_str(), This->m_Info->facing.length());
			if (npStr) {
				STRINGZ_TO_NPVARIANT(npStr, *result);
				ret_val = true;
			}
		}
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool SourceInfo::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
	return false;
}
