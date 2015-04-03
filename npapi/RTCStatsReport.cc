/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "NPCommon.h"
#include "RTCStats.h"
#include "RTCStatsReport.h"
#include "Utils.h"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

#define kFuncResult		"result"

NPClass RTCStatsReportClass = {
	NP_CLASS_STRUCT_VERSION,
	RTCStatsReport::Allocate,
	RTCStatsReport::Deallocate,
	RTCStatsReport::Invalidate,
	RTCStatsReport::HasMethod,
	RTCStatsReport::Invoke,
	RTCStatsReport::InvokeDefault,
	RTCStatsReport::HasProperty,
	RTCStatsReport::GetProperty,
	RTCStatsReport::SetProperty,
	RTCStatsReport::RemoveProperty,
	RTCStatsReport::NPEnumeration,
	RTCStatsReport::Construct,
};

void RTCStatsReport::Invalidate(NPObject *npobj)
{
}

bool RTCStatsReport::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return false;
}

bool RTCStatsReport::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

RTCStatsReport::RTCStatsReport(NPP instance)
	: m_npp(instance)
	, m_Stats(nullPtr)
{
	WE_DEBUG_INFO("RTCStatsReport::NewInstance()");
}

RTCStatsReport::~RTCStatsReport()
{
	m_Stats = nullPtr;

	SetDispatcher(NULL);
}

NPObject* RTCStatsReport::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new RTCStatsReport(instance));
}

void RTCStatsReport::Deallocate(NPObject* obj)
{
	delete (RTCStatsReport*)obj;
}

bool RTCStatsReport::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);

	bool ret_val = !strcmp(name, kFuncResult);

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCStatsReport::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool RTCStatsReport::Invoke(NPObject* obj, NPIdentifier methodName,
	const NPVariant* args, uint32_t argCount,
	NPVariant* result)
{
	RTCStatsReport *This = static_cast<RTCStatsReport*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(methodName);
	bool ret_val = false;
	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kFuncResult)) {
		if (This->m_Stats) {
			_AsyncEventDispatcher* dispatcher = dynamic_cast<_AsyncEventDispatcher*>(const_cast<_AsyncEventDispatcher*>(This->GetDispatcher()));
			if (dispatcher) {
				NPError err;
				std::vector<NPVariant> vect;
				std::map<std::string, cpp11::shared_ptr<_RTCStats> >::iterator it = This->m_Stats->values.begin();
				for (; it != This->m_Stats->values.end(); ++it) {
					RTCStats* _stats;
					err = RTCStats::CreateInstanceWithRef(This->m_npp, &_stats);
					if (err == NPERR_NO_ERROR) {
						_stats->SetStats((*it).second);
						_stats->SetDispatcher(dispatcher);

						NPVariant var;
						OBJECT_TO_NPVARIANT(_stats, var);
						BrowserFuncs->retainobject(var.value.objectValue); // will be released by "NPVecClear()" 
						vect.push_back(var);
						RTCStats::ReleaseInstance(&_stats);
					}
				}

				NPObject* arrayObj = NULL;
				err = Utils::CreateJsArray(This->m_npp, vect, &arrayObj);
				if (err == NPERR_NO_ERROR) {
					OBJECT_TO_NPVARIANT(arrayObj, *result);
					ret_val = true;
				}

				Utils::NPVecClear(vect);
			}
		}
	}


	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCStatsReport::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val = !strcmp(name, kPropUniqueId);

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCStatsReport::SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
	// all properties are readonly
	return false;
}

bool RTCStatsReport::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	RTCStatsReport *This = static_cast<RTCStatsReport*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropUniqueId)) {
		DOUBLE_TO_NPVARIANT(This->UniqueId(), *result);
		ret_val = true;
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCStatsReport::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
	return false;
}
