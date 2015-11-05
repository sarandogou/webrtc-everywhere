/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "MediaStream.h"
#include "MediaStreamTrack.h"
#include "WebRTC.h"
#include "BrowserCallback.h"
#include "NPCommon.h"
#include "Utils.h"

extern void* NPMemDup(const void* mem, size_t n);
extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

#define kPropId									"id"
#define kPropEnded								"ended"
#define kPropOnended							"onended"
#define kPropOnaddtrack							"onaddtrack"
#define kPropOnremovetrack						"onremovetrack"

#define kFuncGetTracks                          "getTracks"
#define kFuncGetAudioTracks						"getAudioTracks"
#define kFuncGetVideoTracks						"getVideoTracks"
#define kFuncGetTrackById						"getTrackById"
#define kFuncAddTrack							"addTrack"
#define kFuncRemoveTrack						"removeTrack"
#define kFuncClone								"clone"
#define kFuncStop								"stop"

NPClass MediaStreamClass = {
	NP_CLASS_STRUCT_VERSION,
	MediaStream::Allocate,
	MediaStream::Deallocate,
	MediaStream::Invalidate,
	MediaStream::HasMethod,
	MediaStream::Invoke,
	MediaStream::InvokeDefault,
	MediaStream::HasProperty,
	MediaStream::GetProperty,
	MediaStream::SetProperty,
	MediaStream::RemoveProperty,
	MediaStream::NPEnumeration,
	MediaStream::Construct,
};

void MediaStream::Invalidate(NPObject *npobj)
{
}

bool MediaStream::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return false;
}

bool MediaStream::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    MediaStream *This = static_cast<MediaStream*>(npobj);
    NPObject* _this = NULL;
    Utils::NPObjectSet(&_this, This);
    OBJECT_TO_NPVARIANT(_this, *result);
    return true;
}

MediaStream::MediaStream(NPP instance)
	: m_npp(instance)
	, m_callback_onended(NULL)
	, m_callback_onaddtrack(NULL)
	, m_callback_onremovetrack(NULL)
	, m_Stream(nullPtr)
{
	WE_DEBUG_INFO("MediaStream::NewInstance()");
}

MediaStream::~MediaStream()
{
	Utils::NPObjectRelease(&m_callback_onended);
	Utils::NPObjectRelease(&m_callback_onaddtrack);
	Utils::NPObjectRelease(&m_callback_onremovetrack);

	m_Stream = nullPtr;

	SetDispatcher(NULL);
}

NPObject* MediaStream::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new MediaStream(instance));
}

void MediaStream::Deallocate(NPObject* obj)
{
	delete (MediaStream*)obj;
}

bool MediaStream::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);

	bool ret_val = !strcmp(name, kFuncGetTracks) ||
        !strcmp(name, kFuncGetAudioTracks) ||
		!strcmp(name, kFuncGetVideoTracks) ||
		!strcmp(name, kFuncGetTrackById) ||
		!strcmp(name, kFuncAddTrack) ||
		!strcmp(name, kFuncRemoveTrack) ||
		!strcmp(name, kFuncClone) ||
		!strcmp(name, kFuncStop)
		;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MediaStream::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool MediaStream::Invoke(NPObject* obj, NPIdentifier methodName,
	const NPVariant* args, uint32_t argCount,
	NPVariant* result)
{
	MediaStream *This = static_cast<MediaStream*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(methodName);
	bool ret_val = false;
	if (!name) {
		return ret_val;
	}

    if (!strcmp(name, kFuncGetTracks)) {
        ret_val = (This->getTracks(_TrackTypeAll, result) == NPERR_NO_ERROR);
    }
	else if (!strcmp(name, kFuncGetAudioTracks)) {
		ret_val = (This->getTracks(_TrackTypeAudio, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kFuncGetVideoTracks)) {
		ret_val = (This->getTracks(_TrackTypeVideo, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kFuncGetTrackById)) {
		if (This->m_Stream && argCount > 0) {
			std::string trackId = Utils::VariantToString((NPVariant*)&args[0]);
			if (!trackId.empty()) {
				cpp11::shared_ptr<_MediaStreamTrack> track = This->m_Stream->getTrackById(trackId.c_str());
				if (track) {
					MediaStreamTrack* _track;
					NPError err = MediaStreamTrack::CreateInstanceWithRef(This->m_npp, &_track);
					if (err == NPERR_NO_ERROR) {
						_track->SetDispatcher(const_cast<_AsyncEventDispatcher*>(This->GetDispatcher()));
						_track->SetTrack(track);
						ret_val = true;
						OBJECT_TO_NPVARIANT(_track, *result);
					}
				}
				else {
					ret_val = true;
					VOID_TO_NPVARIANT(*result);
				}
			}
		}
	}
	else if (!strcmp(name, kFuncAddTrack)) {
		if (This->m_Stream && argCount > 0) {
			NPObject* npObj = Utils::VariantToObject((NPVariant*)&args[0]);
			MediaStreamTrack* _mediaStreamTrack = (MediaStreamTrack*)(MediaStreamTrack::IsInstanceOf(npObj) ? npObj : Utils::NPObjectUpCast(npObj));
			if (_mediaStreamTrack) {
				This->m_Stream->addTrack(_mediaStreamTrack->GetTrack().get());
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kFuncRemoveTrack)) {
		if (This->m_Stream && argCount > 0) {
			NPObject* npObj = Utils::VariantToObject((NPVariant*)&args[0]);
			MediaStreamTrack* _mediaStreamTrack = (MediaStreamTrack*)(MediaStreamTrack::IsInstanceOf(npObj) ? npObj : Utils::NPObjectUpCast(npObj));
			if (_mediaStreamTrack) {
				This->m_Stream->removeTrack(_mediaStreamTrack->GetTrack().get());
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kFuncClone)) {
		if (This->m_Stream) {
			cpp11::shared_ptr<_MediaStream>stream = This->m_Stream->clone();
			if (stream) {
				MediaStream* _stream;
				NPError err = MediaStream::CreateInstanceWithRef(This->m_npp, &_stream);
				if (err == NPERR_NO_ERROR) {
					_stream->SetDispatcher(const_cast<_AsyncEventDispatcher*>(This->GetDispatcher()));
					_stream->SetStream(stream);
					OBJECT_TO_NPVARIANT(_stream, *result);
					ret_val = true;
				}
			}
		}
	}
	else if (!strcmp(name, kFuncStop)) {
		if (This->m_Stream) {
			This->m_Stream->stop();
		}
		ret_val = true;
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MediaStream::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val = !strcmp(name, kPropUniqueId) ||
        !strcmp(name, kPropId) ||
		!strcmp(name, kPropEnded) ||
		!strcmp(name, kPropOnended) ||
		!strcmp(name, kPropOnaddtrack) ||
		!strcmp(name, kPropOnremovetrack)
		;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MediaStream::SetProperty(NPObject *npobj, NPIdentifier propertyName, const NPVariant *value)
{
	MediaStream *This = static_cast<MediaStream*>(npobj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

    if (!strcmp(name, kPropUniqueId)) {
		// readonly
	}
	else if (!strcmp(name, kPropId)) {
		// readonly
	}
	else if (!strcmp(name, kPropEnded)) {
		// readonly
	}
	else if (!strcmp(name, kPropOnended)) {
		Utils::NPObjectSet(&This->m_callback_onended, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}
	else if (!strcmp(name, kPropOnaddtrack)) {
		Utils::NPObjectSet(&This->m_callback_onaddtrack, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}
	else if (!strcmp(name, kPropOnremovetrack)){
		Utils::NPObjectSet(&This->m_callback_onremovetrack, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}


bool MediaStream::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	MediaStream *This = static_cast<MediaStream*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

    if (!strcmp(name, kPropUniqueId)) {
        DOUBLE_TO_NPVARIANT(This->UniqueId(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropId)) {
		if (This->m_Stream) {
			NPUTF8* npStrId = (NPUTF8*)Utils::MemDup(This->m_Stream->id(), we_strlen(This->m_Stream->id()));
			if (npStrId) {
				STRINGZ_TO_NPVARIANT(npStrId, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropEnded)) {
		if (This->m_Stream) {
			BOOLEAN_TO_NPVARIANT(This->m_Stream->ended(), *result);
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropOnended)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onended, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropOnaddtrack)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onaddtrack, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropOnremovetrack)){
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onremovetrack, result) == NPERR_NO_ERROR);
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool MediaStream::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
	return false;
}

void MediaStream::SetStream(cpp11::shared_ptr<_MediaStream> & stream)
{
	if ((m_Stream = stream)) {
		m_Stream->onendedSet(cpp11::bind(&MediaStream::onended, this));
		m_Stream->onaddtrackSet(cpp11::bind(&MediaStream::onaddtrack, this));
		m_Stream->onremovetrackSet(cpp11::bind(&MediaStream::onremovetrack, this));
	}
}

cpp11::shared_ptr<_MediaStream> MediaStream::GetStream()
{
	return m_Stream;
}

void MediaStream::onended()
{
	if (m_callback_onended) {
		BrowserCallback* _cb = new BrowserCallback(m_npp, WM_SUCCESS, m_callback_onended);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void MediaStream::onaddtrack()
{
	if (m_callback_onaddtrack) {
		BrowserCallback* _cb = new BrowserCallback(m_npp, WM_SUCCESS, m_callback_onaddtrack);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void MediaStream::onremovetrack()
{
	if (m_callback_onremovetrack) {
		BrowserCallback* _cb = new BrowserCallback(m_npp, WM_SUCCESS, m_callback_onremovetrack);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

NPError MediaStream::getTracks(_TrackType type, NPVariant* Tracks)
{
	if (!m_Stream) {
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
	_AsyncEventDispatcher* dispatcher = dynamic_cast<_AsyncEventDispatcher*>(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
	if (!dispatcher) {
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}

	NPError err;
	std::vector<NPVariant> vect;
    cpp11::shared_ptr<_Sequence<_MediaStreamTrack> > _tracks;
    cpp11::shared_ptr<_Sequence<_MediaStreamTrack> > tracks(new _Sequence<_MediaStreamTrack>());
    if ((type & _TrackTypeAudio) == _TrackTypeAudio && (_tracks = m_Stream->getAudioTracks()) && _tracks.get()) {
        tracks->AddSeq(_tracks.get());
    }
    if ((type & _TrackTypeVideo) == _TrackTypeVideo && (_tracks = m_Stream->getVideoTracks()) && _tracks.get()) {
        tracks->AddSeq(_tracks.get());
    }
	
    for (size_t i = 0; i < tracks->values.size(); ++i) {
        if (!tracks->values[i]) {
            continue;
        }
        MediaStreamTrack* _track;
        err = MediaStreamTrack::CreateInstanceWithRef(m_npp, &_track);
        if (err == NPERR_NO_ERROR) {
            _track->SetDispatcher(dispatcher);
            _track->SetTrack(tracks->values[i]);
            
            NPVariant var;
            OBJECT_TO_NPVARIANT(_track, var);
            BrowserFuncs->retainobject(var.value.objectValue); // will be release by "NPVecClear()"
            
            vect.push_back(var);
            MediaStreamTrack::ReleaseInstance(&_track);
        }
    }
	

	NPObject* arrayObj = NULL;
	err = Utils::CreateJsArray(m_npp, vect, &arrayObj);
	if (err == NPERR_NO_ERROR) {
		OBJECT_TO_NPVARIANT(arrayObj, *Tracks);
	}

	Utils::NPVecClear(vect);

	return err;
}