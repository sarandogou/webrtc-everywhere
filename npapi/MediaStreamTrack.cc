/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "NPCommon.h"
#include "MediaStreamTrack.h"
#include "BrowserCallback.h"
#include "MediaSourceStates.h"
#include "WebRTC.h"
#include "SourceInfo.h"
#include "Utils.h"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

#define kPropKind									"kind"
#define kPropId										"id"
#define kPropLabel									"label"
#define kPropEnabled								"enabled"
#define kPropMuted									"muted"
#define kPropOnmute									"onmute"
#define kPropOnunmute								"onunmute"
#define kPropReadonly								"readonly"
#define kPropRemote									"remote"
#define kPropReadyState								"readyState"
#define kPropOnstarted								"onstarted"
#define kPropOnended								"onended"
#define kPropOnoverconstrained						"onoverconstrained"

#define kFuncGetSourceInfos							"getSourceInfos"
#define kFuncConstraints							"constraints"
#define kFuncStates									"states"
#define kFuncCapabilities							"capabilities"
#define kFuncApplyConstraints						"applyConstraints"
#define kFuncClone									"clone"
#define kFuncStop									"stop"

NPClass MediaStreamTrackClass = {
	NP_CLASS_STRUCT_VERSION,
	MediaStreamTrack::Allocate,
	MediaStreamTrack::Deallocate,
	MediaStreamTrack::Invalidate,
	MediaStreamTrack::HasMethod,
	MediaStreamTrack::Invoke,
	MediaStreamTrack::InvokeDefault,
	MediaStreamTrack::HasProperty,
	MediaStreamTrack::GetProperty,
	MediaStreamTrack::SetProperty,
	MediaStreamTrack::RemoveProperty,
	MediaStreamTrack::NPEnumeration,
	MediaStreamTrack::Construct,
};

void MediaStreamTrack::Invalidate(NPObject *npobj)
{
}

bool MediaStreamTrack::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return false;
}

bool MediaStreamTrack::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

MediaStreamTrack::MediaStreamTrack(NPP instance)
	: m_npp(instance)
	, m_Track(nullPtr)
	, m_callback_onmute(NULL)
	, m_callback_onunmute(NULL)
	, m_callback_onstarted(NULL)
	, m_callback_onended(NULL)
	, m_callback_onoverconstrained(NULL)
{
	WE_DEBUG_INFO("MediaStreamTrack::NewInstance()");
}

MediaStreamTrack::~MediaStreamTrack()
{
	m_Track = nullPtr;

	Utils::NPObjectRelease(&m_callback_onmute);
	Utils::NPObjectRelease(&m_callback_onunmute);
	Utils::NPObjectRelease(&m_callback_onstarted);
	Utils::NPObjectRelease(&m_callback_onended);
	Utils::NPObjectRelease(&m_callback_onoverconstrained);

	SetDispatcher(NULL);
}

void MediaStreamTrack::SetTrack(cpp11::shared_ptr<_MediaStreamTrack> & track)
{
	if ((m_Track = track)) {
		m_Track->onmuteSet(cpp11::bind(&MediaStreamTrack::onmute, this));
		m_Track->onunmuteSet(cpp11::bind(&MediaStreamTrack::onunmute, this));
		m_Track->onstartedSet(cpp11::bind(&MediaStreamTrack::onstarted, this));
		m_Track->onendedSet(cpp11::bind(&MediaStreamTrack::onended, this));
		m_Track->onoverconstrainedSet(cpp11::bind(&MediaStreamTrack::onoverconstrained, this));
	}
}

cpp11::shared_ptr<_MediaStreamTrack> MediaStreamTrack::GetTrack()
{
	return m_Track;
}
NPObject* MediaStreamTrack::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new MediaStreamTrack(instance));
}

void MediaStreamTrack::Deallocate(NPObject* obj)
{
	delete (MediaStreamTrack*)obj;
}

bool MediaStreamTrack::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);

	bool ret_val = !strcmp(name, kFuncGetSourceInfos) ||
		!strcmp(name, kFuncConstraints) ||
		!strcmp(name, kFuncStates) ||
		!strcmp(name, kFuncCapabilities) ||
		!strcmp(name, kFuncApplyConstraints) ||
		!strcmp(name, kFuncClone) ||
		!strcmp(name, kFuncStop)
		;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MediaStreamTrack::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool MediaStreamTrack::Invoke(NPObject* obj, NPIdentifier methodName,
	const NPVariant* args, uint32_t argCount,
	NPVariant* result)
{
	MediaStreamTrack *This = static_cast<MediaStreamTrack*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(methodName);
	bool ret_val = false;
	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kFuncGetSourceInfos)) {
		NPObject* obj = NULL;
		NPError err = MediaStreamTrack::getSources(This->m_npp, const_cast<_AsyncEventDispatcher*>(This->GetDispatcher()), &obj);
		if (err == NPERR_NO_ERROR) {
			OBJECT_TO_NPVARIANT(obj, *result);
			ret_val = true;
		}
	}
	else if (!strcmp(name, kFuncConstraints)) {
		if (This->m_Track) {
			// TODO: not implemented yet
			NULL_TO_NPVARIANT(*result);
			ret_val = false;
		}
	}
	else if (!!strcmp(name, kFuncStates)) {
		if (This->m_Track) {
			MediaSourceStates* _states;
			NPError err = MediaSourceStates::CreateInstanceWithRef(This->m_npp, &_states);
			if (err == NPERR_NO_ERROR) {
                cpp11::shared_ptr<_MediaSourceStates> states = This->m_Track->states();
				_states->SetStates(states);
				OBJECT_TO_NPVARIANT(_states, *result);
				ret_val = true;
			}
		}
	}
	else if (!!strcmp(name, kFuncCapabilities)) {
		if (This->m_Track) {
			// TODO: not implemented yet
			NULL_TO_NPVARIANT(*result);
			ret_val = false;
		}
	}
	else if (!!strcmp(name, kFuncApplyConstraints)) {
		if (This->m_Track) {
			// TODO: not implemented yet
			NULL_TO_NPVARIANT(*result);
			ret_val = false;
		}
	}
	else if (!!strcmp(name, kFuncClone)) {
		if (This->m_Track) {
			// TODO: not implemented yet
			NULL_TO_NPVARIANT(*result);
			ret_val = false;
		}
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MediaStreamTrack::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val = !strcmp(name, kPropUniqueId) ||
		!strcmp(name, kPropKind) ||
		!strcmp(name, kPropId) ||
		!strcmp(name, kPropLabel) ||
		!strcmp(name, kPropEnabled) ||
		!strcmp(name, kPropMuted) ||
		!strcmp(name, kPropOnmute) ||
		!strcmp(name, kPropOnunmute) ||
		!strcmp(name, kPropReadonly) ||
		!strcmp(name, kPropRemote) ||
		!strcmp(name, kPropReadyState) ||
		!strcmp(name, kPropOnstarted) ||
		!strcmp(name, kPropOnended) ||
		!strcmp(name, kPropOnoverconstrained)
		;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MediaStreamTrack::SetProperty(NPObject *npobj, NPIdentifier propertyName, const NPVariant *value)
{
	MediaStreamTrack *This = static_cast<MediaStreamTrack*>(npobj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropKind)) {
		// readonly
		ret_val = false;
	}
	else if (!strcmp(name, kPropId)) {
		// readonly
		ret_val = false;
	}
	else if (!strcmp(name, kPropLabel)) {
		// readonly
		ret_val = false;
	}
	else if (!strcmp(name, kPropEnabled)) {
		if (This->m_Track && NPVARIANT_IS_BOOLEAN(*value)) {
			This->m_Track->enabledSet(value->value.boolValue);
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropMuted)) {
		// readonly
		ret_val = false;
	}
	else if (!strcmp(name, kPropOnmute)) {
		Utils::NPObjectSet(&This->m_callback_onmute, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}
	else if (!strcmp(name, kPropOnunmute)) {
		Utils::NPObjectSet(&This->m_callback_onunmute, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}
	else if (!strcmp(name, kPropReadonly)) {
		// readonly
		ret_val = false;
	}
	else if (!strcmp(name, kPropRemote)) {
		// readonly
		ret_val = false;
	}
	else if (!strcmp(name, kPropReadyState)) {
		// readonly
		ret_val = false;
	}
	else if (!strcmp(name, kPropOnstarted)) {
		Utils::NPObjectSet(&This->m_callback_onstarted, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}
	else if (!strcmp(name, kPropOnended)) {
		Utils::NPObjectSet(&This->m_callback_onended, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}
	else if (!strcmp(name, kPropOnoverconstrained)) {
		Utils::NPObjectSet(&This->m_callback_onoverconstrained, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MediaStreamTrack::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	MediaStreamTrack *This = static_cast<MediaStreamTrack*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropUniqueId)) {
		DOUBLE_TO_NPVARIANT(This->UniqueId(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropKind)) {
		if (This->m_Track) {
			NPUTF8* npStrKind = (NPUTF8*)Utils::MemDup(This->m_Track->kind(), we_strlen(This->m_Track->kind()));
			if (npStrKind) {
				STRINGZ_TO_NPVARIANT(npStrKind, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropId)) {
		if (This->m_Track) {
			NPUTF8* npStrId = (NPUTF8*)Utils::MemDup(This->m_Track->id(), we_strlen(This->m_Track->id()));
			if (npStrId) {
				STRINGZ_TO_NPVARIANT(npStrId, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropLabel)) {
		if (This->m_Track) {
			NPUTF8* npStrLabel = (NPUTF8*)Utils::MemDup(This->m_Track->label(), we_strlen(This->m_Track->label()));
			if (npStrLabel) {
				STRINGZ_TO_NPVARIANT(npStrLabel, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropEnabled)) {
		if (This->m_Track) {
			BOOLEAN_TO_NPVARIANT(This->m_Track->enabled(), *result);
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropMuted)) {
		if (This->m_Track) {
			BOOLEAN_TO_NPVARIANT(This->m_Track->muted(), *result);
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropOnmute)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onmute, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropOnunmute)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onunmute, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropReadonly)) {
		if (This->m_Track) {
			BOOLEAN_TO_NPVARIANT(This->m_Track->readonly(), *result);
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropRemote)) {
		if (This->m_Track) {
			BOOLEAN_TO_NPVARIANT(This->m_Track->remote(), *result);
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropReadyState)) {
		if (This->m_Track) {
			NPUTF8* npStrState = (NPUTF8*)Utils::MemDup(This->m_Track->readyState(), we_strlen(This->m_Track->readyState()));
			if (npStrState) {
				STRINGZ_TO_NPVARIANT(npStrState, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropOnstarted)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onstarted, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropOnended)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onended, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropOnoverconstrained)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onoverconstrained, result) == NPERR_NO_ERROR);
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MediaStreamTrack::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
	return false;
}


void MediaStreamTrack::onmute()
{
	if (m_callback_onmute) {
		BrowserCallback* _cb = new BrowserCallback(m_npp, WM_SUCCESS, m_callback_onmute);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void MediaStreamTrack::onunmute()
{
	if (m_callback_onunmute) {
		BrowserCallback* _cb = new BrowserCallback(m_npp, WM_SUCCESS, m_callback_onunmute);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void MediaStreamTrack::onstarted()
{
	if (m_callback_onstarted) {
		BrowserCallback* _cb = new BrowserCallback(m_npp, WM_SUCCESS, m_callback_onstarted);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void MediaStreamTrack::onended()
{
	if (m_callback_onended) {
		BrowserCallback* _cb = new BrowserCallback(m_npp, WM_SUCCESS, m_callback_onended);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void MediaStreamTrack::onoverconstrained()
{
	if (m_callback_onoverconstrained) {
		BrowserCallback* _cb = new BrowserCallback(m_npp, WM_SUCCESS, m_callback_onoverconstrained);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

NPError MediaStreamTrack::getSources(NPP npp, _AsyncEventDispatcher* dispatcher, NPObject** Infos)
{
	if (!dispatcher || !Infos || *Infos) {
		CHECK_NPERR_RETURN(NPERR_INVALID_PARAM);
	}

	std::vector<NPVariant> vect;
	NPError err;
	cpp11::shared_ptr<_Sequence<_SourceInfo> > sources = _MediaStreamTrack::getSourceInfos();
	if (sources) {
		for (size_t i = 0; i < sources->values.size(); ++i) {
			if (!sources->values[i]) {
				continue;
			}
			SourceInfo* _source;
			err = SourceInfo::CreateInstanceWithRef(npp, &_source);
			if (err == NPERR_NO_ERROR) {
				_source->SetInfo(sources->values[i]);
				
				NPVariant var;
				OBJECT_TO_NPVARIANT(_source, var);
				BrowserFuncs->retainobject(var.value.objectValue); // will be release by "NPVecClear()" 
				vect.push_back(var);
				SourceInfo::ReleaseInstance(&_source);
			}
		}
	}
		
	err = Utils::CreateJsArray(npp, vect, Infos);
	Utils::NPVecClear(vect);

	return err;
}