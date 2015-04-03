/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_NPAPI_SESSIONDESCRIPTION_H_
#define _WEBRTC_EVERYWHERE_NPAPI_SESSIONDESCRIPTION_H_

#include "../common/_Config.h"
#include "../common/_SessionDescription.h"

#if WE_UNDER_WINDOWS
#include <Windows.h>
#endif

#include "npapi-includes.h"

class SessionDescription
    : public NPObject
	, public _UniqueObject
{
public:
    SessionDescription(NPP instance);
    virtual ~SessionDescription();

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

	NPObjectImpl_CreateInstanceWithRef(SessionDescription);
	NPObjectImpl_NPObjectRelease(SessionDescription);
	NPObjectImpl_IsInstanceOf(SessionDescription);

	WE_INLINE void SetSdp(cpp11::shared_ptr<_SessionDescription> & sdp) { m_Sdp = sdp; }
	WE_INLINE cpp11::shared_ptr<_SessionDescription> GetSdp() { return m_Sdp; }

	NPError Init(NPVariant* RTCSessionDescriptionInit);

private:
    NPP m_npp;
	cpp11::shared_ptr<_SessionDescription> m_Sdp;
};


#endif /* _WEBRTC_EVERYWHERE_NPAPI_SESSIONDESCRIPTION_H_ */
