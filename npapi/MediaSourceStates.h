/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_NPAPI_MEDIASOURCESTATES_H_
#define _WEBRTC_EVERYWHERE_NPAPI_MEDIASOURCESTATES_H_

#include "../common/_Config.h"
#include "../common/_Common.h"

#include "npapi-includes.h"

class MediaSourceStates
	: public NPObject
	, public _UniqueObject
{
public:
	MediaSourceStates(NPP instance);
	virtual ~MediaSourceStates();

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

	NPObjectImpl_CreateInstanceWithRef(MediaSourceStates);
	NPObjectImpl_NPObjectRelease(MediaSourceStates);
	NPObjectImpl_IsInstanceOf(MediaSourceStates);

	void SetStates(cpp11::shared_ptr<_MediaSourceStates> & states);
	cpp11::shared_ptr<_MediaSourceStates> GetStates();

private:
	NPP m_npp;
	cpp11::shared_ptr<_MediaSourceStates> m_States;
};

#endif /* _WEBRTC_EVERYWHERE_NPAPI_MEDIASOURCESTATES_H_ */
