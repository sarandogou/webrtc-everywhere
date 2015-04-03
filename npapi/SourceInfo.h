/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_NPAPI_SOURCEINFO_H_
#define _WEBRTC_EVERYWHERE_NPAPI_SOURCEINFO_H_

#include "../common/_Config.h"
#include "../common/_Common.h"

#include "npapi-includes.h"

class SourceInfo
	: public NPObject
	, public _UniqueObject
{
public:
	SourceInfo(NPP instance);
	virtual ~SourceInfo();

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

	NPObjectImpl_CreateInstanceWithRef(SourceInfo);
	NPObjectImpl_NPObjectRelease(SourceInfo);
	NPObjectImpl_IsInstanceOf(SourceInfo);

	void SetInfo(cpp11::shared_ptr<_SourceInfo> & info);
	cpp11::shared_ptr<_SourceInfo> GetInfo();

private:
	NPP m_npp;
	cpp11::shared_ptr<_SourceInfo> m_Info;
};

#endif /* _WEBRTC_EVERYWHERE_NPAPI_SOURCEINFO_H_ */
