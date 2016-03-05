/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "NPCommon.h"
#include "RTCDTMFSender.h"
#include "MediaStreamTrack.h"
#include "BrowserCallback.h"
#include "RTCDTMFToneChangeEvent.h"
#include "Utils.h"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

#define kPropCanInsertDTMF		"canInsertDTMF"
#define kPropTrack				"track"
#define kPropOntonechange		"ontonechange"
#define kPropToneBuffer			"toneBuffer"
#define kPropDuration			"duration"
#define kPropInterToneGap		"interToneGap"

#define kFuncInsertDTMF			"insertDTMF"


NPClass RTCDTMFSenderClass = {
	NP_CLASS_STRUCT_VERSION,
	RTCDTMFSender::Allocate,
	RTCDTMFSender::Deallocate,
	RTCDTMFSender::Invalidate,
	RTCDTMFSender::HasMethod,
	RTCDTMFSender::Invoke,
	RTCDTMFSender::InvokeDefault,
	RTCDTMFSender::HasProperty,
	RTCDTMFSender::GetProperty,
	RTCDTMFSender::SetProperty,
	RTCDTMFSender::RemoveProperty,
	RTCDTMFSender::NPEnumeration,
	RTCDTMFSender::Construct,
};

void RTCDTMFSender::Invalidate(NPObject *npobj)
{
}

bool RTCDTMFSender::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return false;
}

bool RTCDTMFSender::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

RTCDTMFSender::RTCDTMFSender(NPP instance)
	: m_npp(instance)
	, m_Sender(nullPtr)
	, m_callback_ontonechange(NULL)
{
	WE_DEBUG_INFO("RTCDTMFSender::NewInstance()");
}

RTCDTMFSender::~RTCDTMFSender()
{
	Utils::NPObjectRelease(&m_callback_ontonechange);
	m_Sender = nullPtr;

	SetDispatcher(NULL);
}

void RTCDTMFSender::SetSender(cpp11::shared_ptr<_RTCDTMFSender> & sender)
{
	if ((m_Sender = sender)) {
		m_Sender->ontonechangeSet(cpp11::bind(&RTCDTMFSender::ontonechange, this, cpp11::placeholders::_1));
	}
}

cpp11::shared_ptr<_RTCDTMFSender> RTCDTMFSender::GetSender()
{
	return m_Sender;
}

NPObject* RTCDTMFSender::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new RTCDTMFSender(instance));
}

void RTCDTMFSender::Deallocate(NPObject* obj)
{
	delete (RTCDTMFSender*)obj;
}

bool RTCDTMFSender::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);

	bool ret_val = !strcmp(name, kFuncInsertDTMF);

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDTMFSender::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool RTCDTMFSender::Invoke(NPObject* npobj, NPIdentifier methodName,
	const NPVariant* args, uint32_t argCount,
	NPVariant* result)
{
	RTCDTMFSender *This = static_cast<RTCDTMFSender*>(npobj);
	if (!This->m_Sender) {
		return false;
	}
	char* name = BrowserFuncs->utf8fromidentifier(methodName);
	bool ret_val = false;
	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kFuncInsertDTMF)) {
		if (argCount > 0 && args[0].type == NPVariantType_String && args[0].value.stringValue.UTF8Length) {
			std::string tones(args[0].value.stringValue.UTF8Characters, args[0].value.stringValue.UTF8Length);
			long duration = 100, interToneGap = 50;
			if (argCount > 1) {
				if (args[1].type == NPVariantType_Double) duration = (long)args[1].value.doubleValue;
				else if (args[1].type == NPVariantType_String && args[1].value.stringValue.UTF8Length) duration = atol(std::string(args[1].value.stringValue.UTF8Characters, args[1].value.stringValue.UTF8Length).c_str());
			}
			if (argCount > 2) {
				if (args[2].type == NPVariantType_Double) interToneGap = (long)args[2].value.doubleValue;
				else if (args[2].type == NPVariantType_String && args[2].value.stringValue.UTF8Length) interToneGap = atol(std::string(args[2].value.stringValue.UTF8Characters, args[2].value.stringValue.UTF8Length).c_str());
			}
			This->m_Sender->insertDTMF(tones.c_str(), duration, interToneGap);
			ret_val = true;
		}
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDTMFSender::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val = !strcmp(name, kPropCanInsertDTMF) ||
		!strcmp(name, kPropTrack) ||
		!strcmp(name, kPropOntonechange) ||
		!strcmp(name, kPropToneBuffer) ||
		!strcmp(name, kPropDuration) ||
		!strcmp(name, kPropInterToneGap)
		;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDTMFSender::SetProperty(NPObject *npobj, NPIdentifier propertyName, const NPVariant *value)
{
	RTCDTMFSender *This = static_cast<RTCDTMFSender*>(npobj);
	if (!This->m_Sender) {
		return false;
	}
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropOntonechange)) {
		Utils::NPObjectSet(&This->m_callback_ontonechange, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDTMFSender::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	RTCDTMFSender *This = static_cast<RTCDTMFSender*>(obj);
	if (!This->m_Sender) {
		return false;
	}
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropCanInsertDTMF)) {
		BOOLEAN_TO_NPVARIANT(This->m_Sender->canInsertDTMF(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropTrack)) {
		cpp11::shared_ptr<_MediaStreamTrack>streamTrack = This->m_Sender->track();
		if (streamTrack) {
			MediaStreamTrack* _streamTrack;
			NPError err = MediaStreamTrack::CreateInstanceWithRef(This->m_npp, &_streamTrack);
			if (err == NPERR_NO_ERROR) {
				_streamTrack->SetDispatcher(const_cast<_AsyncEventDispatcher*>(This->GetDispatcher()));
				_streamTrack->SetTrack(streamTrack);
				OBJECT_TO_NPVARIANT(_streamTrack, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropOntonechange)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_ontonechange, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropToneBuffer)) {
		NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Sender->toneBuffer(), we_strlen(This->m_Sender->toneBuffer()));
		if (npStr) {
			STRINGZ_TO_NPVARIANT(npStr, *result);
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropDuration)) {
		INT32_TO_NPVARIANT((int32_t)This->m_Sender->duration(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropInterToneGap)) {
		INT32_TO_NPVARIANT((int32_t)This->m_Sender->interToneGap(), *result);
		ret_val = true;
	}
	

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDTMFSender::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
	return false;
}

void RTCDTMFSender::ontonechange(cpp11::shared_ptr<_RTCDTMFToneChangeEvent> e)
{
	if (m_callback_ontonechange) {
		if (m_callback_ontonechange) {
			BrowserCallback* _cb = new BrowserCallback(m_npp, WM_SUCCESS, m_callback_ontonechange);
			if (_cb) {
				RTCDTMFToneChangeEvent *_e = NULL;
				NPError err = RTCDTMFToneChangeEvent::CreateInstanceWithRef(m_npp, &_e);
				if (err == NPERR_NO_ERROR) {
					_e->SetEvent(e);
					_cb->AddObject(_e);
				}
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
				RTCDTMFToneChangeEvent::ReleaseInstance(&_e);
			}
		}
	}
}