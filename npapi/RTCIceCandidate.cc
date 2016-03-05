/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "NPCommon.h"
#include "RTCIceCandidate.h"
#include "Utils.h"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

#define kPropCandidate									"candidate"
#define kPropSdpMid										"sdpMid"
#define kPropSdpMLineIndex								"sdpMLineIndex"

NPClass RTCIceCandidateClass = {
	NP_CLASS_STRUCT_VERSION,
	RTCIceCandidate::Allocate,
	RTCIceCandidate::Deallocate,
	RTCIceCandidate::Invalidate,
	RTCIceCandidate::HasMethod,
	RTCIceCandidate::Invoke,
	RTCIceCandidate::InvokeDefault,
	RTCIceCandidate::HasProperty,
	RTCIceCandidate::GetProperty,
	RTCIceCandidate::SetProperty,
	RTCIceCandidate::RemoveProperty,
	RTCIceCandidate::NPEnumeration,
	RTCIceCandidate::Construct,
};

void RTCIceCandidate::Invalidate(NPObject *npobj)
{
}

bool RTCIceCandidate::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return false;
}

bool RTCIceCandidate::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

RTCIceCandidate::RTCIceCandidate(NPP instance)
	: m_npp(instance)
	, m_Candidate(nullPtr)
{
	WE_DEBUG_INFO("RTCIceCandidate::NewInstance()");
}

RTCIceCandidate::~RTCIceCandidate()
{
	m_Candidate = nullPtr;
}

NPObject* RTCIceCandidate::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new RTCIceCandidate(instance));
}

void RTCIceCandidate::Deallocate(NPObject* obj)
{
	delete (RTCIceCandidate*)obj;
}

bool RTCIceCandidate::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);

	bool ret_val = false;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCIceCandidate::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool RTCIceCandidate::Invoke(NPObject* obj, NPIdentifier methodName,
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

bool RTCIceCandidate::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val = !strcmp(name, kPropUniqueId) ||
		!strcmp(name, kPropCandidate) ||
		!strcmp(name, kPropSdpMid) ||
		!strcmp(name, kPropSdpMLineIndex)
		;
	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCIceCandidate::SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
	// all properties are readonly
	return false;
}

bool RTCIceCandidate::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	RTCIceCandidate *This = static_cast<RTCIceCandidate*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropUniqueId)) {
		DOUBLE_TO_NPVARIANT(This->UniqueId(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropCandidate)) {
		if (This->m_Candidate) {
			NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Candidate->candidate(), we_strlen(This->m_Candidate->candidate()));
			if (npStr) {
				STRINGZ_TO_NPVARIANT(npStr, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropSdpMid)) {
		if (This->m_Candidate) {
			NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Candidate->sdpMid(), we_strlen(This->m_Candidate->sdpMid()));
			if (npStr) {
				STRINGZ_TO_NPVARIANT(npStr, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropSdpMLineIndex)) {
		if (This->m_Candidate) {
			INT32_TO_NPVARIANT(This->m_Candidate->sdpMLineIndex(), *result);
			ret_val = true;
		}
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCIceCandidate::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
	return false;
}

NPError RTCIceCandidate::Init(NPVariant* candidateInitDict)
{
	if (NPVARIANT_IS_STRING(*candidateInitDict) && candidateInitDict->value.stringValue.UTF8Characters && candidateInitDict->value.stringValue.UTF8Length) {
		std::string strCandidate(candidateInitDict->value.stringValue.UTF8Characters, candidateInitDict->value.stringValue.UTF8Length);
		m_Candidate = cpp11::shared_ptr<_RTCIceCandidate>(new _RTCIceCandidate(strCandidate.c_str()));
	}
	else if (NPVARIANT_IS_OBJECT(*candidateInitDict) && candidateInitDict->value.objectValue) {
		NPObject* npObj = candidateInitDict->value.objectValue;
		RTCIceCandidate* _candidateInitDict = (RTCIceCandidate*)(RTCIceCandidate::IsInstanceOf(npObj) ? npObj : Utils::NPObjectUpCast(npObj));
		if (!_candidateInitDict) {
			CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
		}

		std::string strCandidate, strSdpMid;
		NPError err;
		CHECK_NPERR_RETURN(err = Utils::NPObjectGetPropString(m_npp, _candidateInitDict, "candidate", strCandidate));
		CHECK_NPERR_RETURN(err = Utils::NPObjectGetPropString(m_npp, _candidateInitDict, "sdpMid", strSdpMid));
		double doubleSdpMLineIndex;
		CHECK_NPERR_RETURN(err = Utils::NPObjectGetPropNumber(m_npp, _candidateInitDict, "sdpMLineIndex", doubleSdpMLineIndex));
		
		m_Candidate = cpp11::shared_ptr<_RTCIceCandidate>(new _RTCIceCandidate(strCandidate.c_str(), strSdpMid.c_str(), (unsigned short)doubleSdpMLineIndex));
	}

	if (!m_Candidate) {
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}

	return NPERR_NO_ERROR;
}