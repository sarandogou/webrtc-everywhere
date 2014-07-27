/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "NPCommon.h"
#include "SessionDescription.h"
#include "Utils.h"

#define kPropType	"type"
#define kPropSdp	"sdp"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

NPClass SessionDescriptionClass = {
    NP_CLASS_STRUCT_VERSION,
    SessionDescription::Allocate,
    SessionDescription::Deallocate,
    SessionDescription::Invalidate,
    SessionDescription::HasMethod,
    SessionDescription::Invoke,
    SessionDescription::InvokeDefault,
    SessionDescription::HasProperty,
    SessionDescription::GetProperty,
    SessionDescription::SetProperty,
    SessionDescription::RemoveProperty,
    SessionDescription::NPEnumeration,
    SessionDescription::Construct,
};

void SessionDescription::Invalidate(NPObject *npobj)
{
}

bool SessionDescription::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
    return false;
}

bool SessionDescription::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return false;
}

SessionDescription::SessionDescription(NPP instance)
    : m_npp(instance)
	, m_Sdp(nullPtr)
{
    WE_DEBUG_INFO("SessionDescription::NewInstance()");
}

SessionDescription::~SessionDescription()
{
	m_Sdp = nullPtr;
}

NPObject* SessionDescription::Allocate(NPP instance, NPClass* npclass)
{
    return (NPObject*)(new SessionDescription(instance));
}

void SessionDescription::Deallocate(NPObject* obj)
{
    delete (SessionDescription*)obj;
}

bool SessionDescription::HasMethod(NPObject* obj, NPIdentifier methodName)
{
    char* name = BrowserFuncs->utf8fromidentifier(methodName);

    bool ret_val = false;

    BrowserFuncs->memfree(name);
    return ret_val;
}

bool SessionDescription::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
    return true;
}

bool SessionDescription::Invoke(NPObject* obj, NPIdentifier methodName,
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

bool SessionDescription::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
    char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val = !strcmp(name, kPropUniqueId) ||
				   !strcmp(name, kPropType) ||
                   !strcmp(name, kPropSdp);

    BrowserFuncs->memfree(name);
    return ret_val;
}

bool SessionDescription::SetProperty(NPObject *npobj, NPIdentifier propertyName, const NPVariant *value)
{
	SessionDescription *This = static_cast<SessionDescription*>(npobj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropType) && NPVARIANT_IS_STRING(*value)) {
		const _Buffer* _sdp = This->m_Sdp ? This->m_Sdp->getSdp() : NULL;
		cpp11::shared_ptr<_SessionDescription> newSdp(new _SessionDescription(
			_sdp ? _sdp->getPtr() : NULL,
			_sdp ? _sdp->getSize() : 0,
			value->value.stringValue.UTF8Characters,
			value->value.stringValue.UTF8Length));
		This->m_Sdp = newSdp;
		ret_val = true;
	}
	else if (!strcmp(name, kPropSdp) && NPVARIANT_IS_STRING(*value)) {
		const _Buffer* _type = This->m_Sdp ? This->m_Sdp->getType() : NULL;
		cpp11::shared_ptr<_SessionDescription> newSdp(new _SessionDescription(
			value->value.stringValue.UTF8Characters,
			value->value.stringValue.UTF8Length,
			_type ? _type->getPtr() : NULL,
			_type ? _type->getSize() : 0));
		This->m_Sdp = newSdp;
		ret_val = true;
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool SessionDescription::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	SessionDescription *This = static_cast<SessionDescription*>(obj);
    char* name = BrowserFuncs->utf8fromidentifier(propertyName);
    bool ret_val = false;

    if (!name) {
        return ret_val;
    }

	if (!strcmp(name, kPropUniqueId)) {
		DOUBLE_TO_NPVARIANT(This->UniqueId(), *result);
		ret_val = true;
	}
    else if (!strcmp(name, kPropType)) {
		const _Buffer* pcType = This->m_Sdp ? This->m_Sdp->getType() : NULL;
        if (pcType && pcType->getPtr()) {
			char* npStr = (char*)Utils::MemDup(pcType->getPtr(), pcType->getSize());
            if (npStr) {
                STRINGZ_TO_NPVARIANT(npStr, *result);
                ret_val = true;
            }
        }
    }
    else if (!strcmp(name, kPropSdp)) {
		const _Buffer* pcSdp = This->m_Sdp ? This->m_Sdp->getSdp() : NULL;
        if (pcSdp && pcSdp->getPtr()) {
			char* npStr = (char*)Utils::MemDup(pcSdp->getPtr(), pcSdp->getSize());
            if (npStr) {
                STRINGZ_TO_NPVARIANT(npStr, *result);
                ret_val = true;
            }
        }
    }

    BrowserFuncs->memfree(name);
    return ret_val;
}

bool SessionDescription::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
    return false;
}

NPError SessionDescription::Init(NPVariant* RTCSessionDescriptionInit)
{
	NPObject* rtcSessionDescriptionInit = Utils::VariantToObject(RTCSessionDescriptionInit);
	if (!rtcSessionDescriptionInit) {
		CHECK_NPERR_RETURN(NPERR_INVALID_PARAM);
	}

	std::string strType, strSdp;

	CHECK_NPERR_RETURN(Utils::NPObjectGetPropString(m_npp, rtcSessionDescriptionInit, "type", strType));
	CHECK_NPERR_RETURN(Utils::NPObjectGetPropString(m_npp, rtcSessionDescriptionInit, "sdp", strSdp));
    
	m_Sdp = cpp11::shared_ptr<_SessionDescription>(new _SessionDescription(
		strSdp.c_str(), strSdp.length(),
		strType.c_str(), strType.length()));

	return NPERR_NO_ERROR;
}