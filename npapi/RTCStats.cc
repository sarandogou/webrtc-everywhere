/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "NPCommon.h"
#include "RTCStats.h"
#include "Utils.h"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

#define kPropTimestamp		"timestamp"
#define kPropType			"type"
#define kPropId				"id"

#define kFuncNames			"names"
#define kFuncStat			"stat"

NPClass RTCStatsClass = {
	NP_CLASS_STRUCT_VERSION,
	RTCStats::Allocate,
	RTCStats::Deallocate,
	RTCStats::Invalidate,
	RTCStats::HasMethod,
	RTCStats::Invoke,
	RTCStats::InvokeDefault,
	RTCStats::HasProperty,
	RTCStats::GetProperty,
	RTCStats::SetProperty,
	RTCStats::RemoveProperty,
	RTCStats::NPEnumeration,
	RTCStats::Construct,
};

void RTCStats::Invalidate(NPObject *npobj)
{
}

bool RTCStats::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return false;
}

bool RTCStats::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

RTCStats::RTCStats(NPP instance)
	: m_npp(instance)
	, m_Stats(nullPtr)
{
	WE_DEBUG_INFO("RTCStats::NewInstance()");
}

RTCStats::~RTCStats()
{
	SetDispatcher(NULL);
	m_Stats = nullPtr;
}

NPObject* RTCStats::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new RTCStats(instance));
}

void RTCStats::Deallocate(NPObject* obj)
{
	delete (RTCStats*)obj;
}

bool RTCStats::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);

	bool ret_val = !strcmp(name, kFuncNames) ||
		!strcmp(name, kFuncStat)
		;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCStats::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool RTCStats::Invoke(NPObject* obj, NPIdentifier methodName,
	const NPVariant* args, uint32_t argCount,
	NPVariant* result)
{
	RTCStats *This = static_cast<RTCStats*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(methodName);
	bool ret_val = false;
	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kFuncNames)) {
		if (This->m_Stats) {
			NPError err;
			std::vector<NPVariant> vect;
			std::map<std::string, std::string>::iterator it = This->m_Stats->names.begin();
			for (; it != This->m_Stats->names.end(); ++it) {
				NPVariant var;
				NPUTF8* npStr = (NPUTF8*)Utils::MemDup((*it).first.c_str(), (*it).first.length());
				if (npStr) {
					STRINGZ_TO_NPVARIANT(npStr, var);
					vect.push_back(var);
				}
			}

			NPObject* arrayObj = NULL;
			err = Utils::CreateJsArray(This->m_npp, vect, &arrayObj);
			if (err == NPERR_NO_ERROR) {
				OBJECT_TO_NPVARIANT(arrayObj, *result);
				ret_val = true;
			}

			vect.clear(); // do not call VecClear() to free strings
		}
	}
	else if (!strcmp(name, kFuncStat)) {
		if (This->m_Stats) {
			if (argCount > 0 && NPVARIANT_IS_STRING(args[0]) && args[0].value.stringValue.UTF8Characters && args[0].value.stringValue.UTF8Length) {
				std::string strName(args[0].value.stringValue.UTF8Characters, args[0].value.stringValue.UTF8Length);
				std::map<std::string, std::string>::iterator it = This->m_Stats->names.find(strName);
				if (it != This->m_Stats->names.end()) {
					NPUTF8* npStr = (NPUTF8*)Utils::MemDup((*it).second.c_str(), (*it).second.length());
					if (npStr) {
						STRINGZ_TO_NPVARIANT(npStr, *result);
						ret_val = true;
					}
				}
				else {
					NULL_TO_NPVARIANT(*result);
					ret_val = true;
				}
			}
		}
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCStats::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val = !strcmp(name, kPropUniqueId) ||
		!strcmp(name, kPropTimestamp) ||
		!strcmp(name, kPropType) ||
		!strcmp(name, kPropId)
		 ;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCStats::SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
	// all properties are readonly
	return false;
}


bool RTCStats::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	RTCStats *This = static_cast<RTCStats*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropUniqueId)) {
		DOUBLE_TO_NPVARIANT(This->UniqueId(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropTimestamp)) {
		if (This->m_Stats) {
			DOUBLE_TO_NPVARIANT(This->m_Stats->timestamp, *result);
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropType)) {
		if (This->m_Stats) {
			NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Stats->type.c_str(), This->m_Stats->type.length());
			if (npStr) {
				STRINGZ_TO_NPVARIANT(npStr, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropId)) {
		NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Stats->id.c_str(), This->m_Stats->id.length());
		if (npStr) {
			STRINGZ_TO_NPVARIANT(npStr, *result);
			ret_val = true;
		}
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCStats::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
	return false;
}
