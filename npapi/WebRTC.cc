/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_NavigatorUserMedia.h"
#include "../common/_Debug.h"
#include "WebRTC.h"
#include "MediaStream.h"
#include "SessionDescription.h"
#include "PeerConnection.h"
#include "RTCIceCandidate.h"
#include "BrowserCallback.h"
#include "MediaStreamTrack.h"
#include "NPCommon.h"
#include "Utils.h"
#if WE_UNDER_WINDOWS
#include <Windows.h>
#endif

#define kPropVersion						"versionName"
#define kPropSrc							"src"
#define kPropVideoWidth						"videoWidth"
#define kPropVideoHeight					"videoHeight"
#define kPropIsWebRtcPlugin					"isWebRtcPlugin"

#define kFuncGetUserMedia					"getUserMedia"
#define kFuncCreateSessionDescription		"createSessionDescription"
#define kFuncCreatePeerConnection			"createPeerConnection"
#define kFuncCreateIceCandidate				"createIceCandidate"
#define kFuncCreateMediaStreamTrack			"createMediaStreamTrack"
#define kFuncCreateDisplay                  "createDisplay"
#define kFuncBindEventListener				"bindEventListener"
#define kFuncAddEventListener				"addEventListener"
#define kFuncGetSources						"getSources"
#define kFuncFillImageData					"fillImageData"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

extern NPClass SessionDescriptionClass;
extern NPClass MediaStreamClass;

NPClass WebRTCClass = {
    NP_CLASS_STRUCT_VERSION,
    WebRTC::Allocate,
    WebRTC::Deallocate,
    WebRTC::Invalidate,
    WebRTC::HasMethod,
    WebRTC::Invoke,
    WebRTC::InvokeDefault,
    WebRTC::HasProperty,
    WebRTC::GetProperty,
    WebRTC::SetProperty,
    WebRTC::RemoveProperty,
    WebRTC::NPEnumeration,
    WebRTC::Construct,
};

void WebRTC::Invalidate(NPObject *npobj)
{
}

bool WebRTC::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
    return false;
}

bool WebRTC::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return false;
}

WebRTC::WebRTC(NPP instance)
	: _AsyncEventDispatcher()
	, _AsyncEventRaiser()
	, _RTCDisplay()
	, m_npp(instance)
#if WE_UNDER_APPLE
    , m_pRootLayer(NULL)
#endif
	, m_pTempVideoBuff(NULL)
{
    WE_DEBUG_INFO("WebRTC::NewInstance()");
}

WebRTC::~WebRTC()
{
	for (size_t i = 0; i < m_callbacks_onplay.size(); ++i) {
		Utils::NPObjectRelease(&m_callbacks_onplay[i]);
	}
	m_callbacks_onplay.clear();
	StopVideoRenderer();
	SetDispatcher(NULL);
	SafeDelete(&m_pTempVideoBuff);
#if WE_UNDER_APPLE
    SetRootLayer(NULL);
#endif
    
	WE_DEBUG_INFO("WebRTC::~WebRTC");
}

NPObject* WebRTC::Allocate(NPP instance, NPClass* npclass)
{
    return (NPObject*)(new WebRTC(instance));
}

void WebRTC::Deallocate(NPObject* obj)
{
    delete (WebRTC*)obj;
}

bool WebRTC::HasMethod(NPObject* obj, NPIdentifier methodName)
{
    char* name = BrowserFuncs->utf8fromidentifier(methodName);

    bool ret_val = 
		!strcmp(name, kFuncGetUserMedia) ||
		!strcmp(name, kFuncCreateSessionDescription) ||
		!strcmp(name, kFuncCreatePeerConnection) ||
		!strcmp(name, kFuncCreateIceCandidate) ||
		!strcmp(name, kFuncCreateMediaStreamTrack) ||
		!strcmp(name, kFuncCreateDisplay) ||
		!strcmp(name, kFuncBindEventListener) ||
		!strcmp(name, kFuncAddEventListener) ||
		!strcmp(name, kFuncGetSources) ||
		!strcmp(name, kFuncFillImageData)
		;
    BrowserFuncs->memfree(name);
    return ret_val;
}

bool WebRTC::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
    return false;
}

bool WebRTC::Invoke(NPObject* obj, NPIdentifier methodName,
                    const NPVariant* args, uint32_t argCount,
                    NPVariant* result)
{
    WebRTC *This = reinterpret_cast<WebRTC*>((WebRTC*)obj);
    char* name = BrowserFuncs->utf8fromidentifier(methodName);
    bool ret_val = false;
    if (!name) {
        return ret_val;
    }

	if (!strcmp(name, kFuncGetUserMedia)) {
		NPObjectAutoRef constraints(argCount > 0 ? Utils::VariantToObject((NPVariant*)&args[0]) : NULL);
		NPObjectAutoRef successCallback(argCount > 1 ? Utils::VariantToObject((NPVariant*)&args[1]) : NULL);
		NPObjectAutoRef errorCallback(argCount > 2 ? Utils::VariantToObject((NPVariant*)&args[2]) : NULL);

		cpp11::shared_ptr<_MediaStreamConstraints> mediaStreamConstraints;

		ret_val = (Utils::BuildMediaStreamConstraints(This->m_npp, constraints, mediaStreamConstraints) == NPERR_NO_ERROR);
		if (ret_val) {
			_NavigatorUserMedia::getUserMedia(
				mediaStreamConstraints.get(),
				[successCallback, This](cpp11::shared_ptr<_MediaStream> stream) {
				if (successCallback) {
					MediaStream* _stream;
					NPError err = MediaStream::CreateInstanceWithRef(This->m_npp, &_stream);
					if (err == NPERR_NO_ERROR) {
						BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_GETUSERMEDIA_SUCESS, successCallback);
						if (_cb) {
							_stream->SetStream(stream);
							_stream->SetDispatcher(This);
							_cb->AddObject(_stream);
							dynamic_cast<_AsyncEventDispatcher*>(This)->RaiseCallback(_cb);
							SafeReleaseObject(&_cb);
						}
						MediaStream::ReleaseInstance(&_stream);
					}
				}
			},
				[errorCallback, This](cpp11::shared_ptr<_NavigatorUserMediaError> e) {
				if (errorCallback) {
					BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_GETUSERMEDIA_ERROR, errorCallback);
					if (_cb) {
						_cb->AddString((void*)e->constraintName.c_str(), e->constraintName.length());
						dynamic_cast<_AsyncEventDispatcher*>(This)->RaiseCallback(_cb);
						SafeReleaseObject(&_cb);
					}
				}
			}
			);
		}
	}
    else if (!strcmp(name, kFuncCreateSessionDescription)) {
        if (argCount > 0) {
			SessionDescription* sdp;
			NPError err = SessionDescription::CreateInstanceWithRef(This->m_npp, &sdp);
			if (err == NPERR_NO_ERROR) {
				if ((err = sdp->Init((NPVariant*)&args[0])) == NPERR_NO_ERROR) {
					OBJECT_TO_NPVARIANT(sdp, *result); sdp = NULL, ret_val = true;
				}
				SessionDescription::ReleaseInstance(&sdp);
			}
        }
    }
	else if (!strcmp(name, kFuncCreatePeerConnection)) {
		NPObject* RTCConfiguration = argCount > 0 ? Utils::VariantToObject((NPVariant*)&args[0]) : NULL;
		NPObject* MediaConstraints = argCount > 1 ? Utils::VariantToObject((NPVariant*)&args[1]) : NULL;
		PeerConnection* pc;
		NPError err = PeerConnection::CreateInstanceWithRef(This->m_npp, &pc);
		if (err == NPERR_NO_ERROR) {
			if ((err = pc->Init(RTCConfiguration, MediaConstraints)) == NPERR_NO_ERROR) {
				pc->SetDispatcher(dynamic_cast<_AsyncEventDispatcher*>(This));
				OBJECT_TO_NPVARIANT(pc, *result); pc = NULL, ret_val = true;
			}
			PeerConnection::ReleaseInstance(&pc);
		}
	}
	else if (!strcmp(name, kFuncCreateIceCandidate)) {
		if (argCount > 0) {
			RTCIceCandidate* cand;
			NPError err = RTCIceCandidate::CreateInstanceWithRef(This->m_npp, &cand);
			if (err == NPERR_NO_ERROR) {
				if ((err = cand->Init((NPVariant*)&args[0])) == NPERR_NO_ERROR) {
					OBJECT_TO_NPVARIANT(cand, *result); cand = NULL, ret_val = true;
				}
				RTCIceCandidate::ReleaseInstance(&cand);
			}
		}
	}
	else if (!strcmp(name, kFuncCreateMediaStreamTrack)) {
		MediaStreamTrack* track;
		NPError err = MediaStreamTrack::CreateInstanceWithRef(This->m_npp, &track);
		if (err == NPERR_NO_ERROR) {
			OBJECT_TO_NPVARIANT(track, *result); track = NULL, ret_val = true;
			MediaStreamTrack::ReleaseInstance(&track);
		}
	}
    else if (!strcmp(name, kFuncCreateDisplay)) {
        NPObject* jsObj = NULL;
        NPError err = Utils::CreateDocumentElementObject(This->m_npp, &jsObj);
        if (err == NPERR_NO_ERROR) {
            NPVariant val;
            STRINGZ_TO_NPVARIANT("application/webrtc-everywhere", val);
            ret_val = jsObj->_class->setProperty(jsObj, BrowserFuncs->getstringidentifier("type"), &val);
            if (ret_val) {
                OBJECT_TO_NPVARIANT(jsObj, *result);
            }
            else {
                Utils::NPObjectRelease(&jsObj);
            }
        }
    }
	else if (!strcmp(name, kFuncBindEventListener) || !strcmp(name, kFuncAddEventListener)) {
		if (argCount > 1 && NPVARIANT_IS_STRING(args[0])) {
			if (args[0].value.stringValue.UTF8Length == 4 && !strncmp(args[0].value.stringValue.UTF8Characters, "play", 4)) {
				NPObject* callback = NULL;
				Utils::NPObjectSet(&callback, Utils::VariantToObject((NPVariant*)&args[1]));
				if (callback) {
					ret_val = true;
					This->m_callbacks_onplay.push_back(callback);
				}
			}
		}
	}
	else if (!strcmp(name, kFuncGetSources)) {
		NPObjectAutoRef successCallback(argCount > 0 ? Utils::VariantToObject((NPVariant*)&args[0]) : NULL);
		if (successCallback) {
			NPObject* sources = NULL;
			NPError err = MediaStreamTrack::getSources(This->m_npp, This, &sources);
			if (err == NPERR_NO_ERROR) {
				BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_SUCCESS, successCallback);
				if (_cb) {
					_cb->AddObject(sources);
					dynamic_cast<_AsyncEventDispatcher*>(This)->RaiseCallback(_cb);
					SafeReleaseObject(&_cb);
					ret_val = true;
				}
			}
			Utils::NPObjectRelease(&sources);
		}
		else {
			ret_val = true;
		}
	}
	else if (!strcmp(name, kFuncFillImageData)) {
		if (argCount > 0 && NPVARIANT_IS_OBJECT(args[0]) && args[0].value.objectValue) {
			NPError err;

			int videoWidth = This->GetVideoWidth();
			int videoHeight = This->GetVideoHeight();

			if (videoHeight > 0 && videoWidth > 0) {
				double width = 0, height = 0;
				NPVariant varData;
				err = Utils::NPObjectGetProp(This->m_npp, args[0].value.objectValue, "data", &varData);
				if (err == NPERR_NO_ERROR) {
					err = Utils::NPObjectGetPropNumber(This->m_npp, args[0].value.objectValue, "width", width);
				}
				if (err == NPERR_NO_ERROR) {
					err = Utils::NPObjectGetPropNumber(This->m_npp, args[0].value.objectValue, "height", height);
				}

				if (err == NPERR_NO_ERROR && NPVARIANT_IS_OBJECT(varData) && varData.value.objectValue && (int)width == videoWidth && (int)height == videoHeight) {
					size_t videoSize = (videoWidth * videoHeight * 4);

					if (!This->m_pTempVideoBuff || This->m_pTempVideoBuff->getSize() < videoSize){
						SafeDelete(&This->m_pTempVideoBuff);
						if ((_Buffer::New(NULL, videoSize, &This->m_pTempVideoBuff))) {
							err = NPERR_OUT_OF_MEMORY_ERROR;
						}
					}

					if (err == NPERR_NO_ERROR) {
						if (This->CopyFromFrame(const_cast<void*>(This->m_pTempVideoBuff->getPtr()), videoSize) != videoSize) {
							memset(const_cast<void*>(This->m_pTempVideoBuff->getPtr()), 0, videoSize);
						}

						char s[25];
						const uint8_t* imageDataPtr = (const uint8_t*)This->m_pTempVideoBuff->getPtr();
						NPVariant var;
						long index;
						for (long x = 0; x < width; ++x) {
							for (long y = 0; y < height; ++y) {
								index = (long)(x + y * width) * 4;
								for (long comp = 0; comp < 4; ++comp) { // (a, r, g, b) -> (r, g, b, a)
									sprintf(s, "%ld", (int32_t)index + comp);
									INT32_TO_NPVARIANT(imageDataPtr[index + ((comp + 0) & 3)], var);
                                    if (!(ret_val = varData.value.objectValue->_class->setProperty(varData.value.objectValue, BrowserFuncs->getstringidentifier(s), &var))) {
                                        break;
                                    }
									//if (!(ret_val = BrowserFuncs->setproperty(This->m_npp, varData.value.objectValue, BrowserFuncs->getstringidentifier(s), &var))) {
										//break;
									//}
								}
							}
						}
					}
				}
			}
		}
	}    

    BrowserFuncs->memfree(name);
    return ret_val;
}

bool WebRTC::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
    char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = !strcmp(name, kPropVersion) ||
		!strcmp(name, kPropSrc) ||
		!strcmp(name, kPropVideoWidth) ||
		!strcmp(name, kPropVideoHeight) ||
		!strcmp(name, kPropIsWebRtcPlugin);
    BrowserFuncs->memfree(name);
    return ret_val;
}

bool WebRTC::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	WebRTC *This = reinterpret_cast<WebRTC*>((WebRTC*)obj);
    char* name = BrowserFuncs->utf8fromidentifier(propertyName);
    bool ret_val = false;

    if (!name) {
        return ret_val;
    }

    if (!strcmp(name, kPropVersion)) {
		char* npStr = (char*)Utils::MemDup(kPluginVersionString, strlen(kPluginVersionString));
        if (npStr) {
            STRINGZ_TO_NPVARIANT(npStr, *result);
            ret_val = true;
        }
    }
	else if (!strcmp(name, kPropSrc)) {
		VOID_TO_NPVARIANT(*result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropVideoWidth)) {
		INT32_TO_NPVARIANT(This->GetVideoWidth(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropVideoHeight)) {
		INT32_TO_NPVARIANT(This->GetVideoHeight(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropIsWebRtcPlugin)) {
		BOOLEAN_TO_NPVARIANT(true, *result);
		ret_val = true;
	}

    BrowserFuncs->memfree(name);
    return ret_val;
}

bool WebRTC::SetProperty(NPObject *npobj, NPIdentifier propertyName, const NPVariant *value)
{
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	WebRTC *This = reinterpret_cast<WebRTC*>((WebRTC*)npobj);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropSrc)) {
		NPObject* npObj = Utils::VariantToObject((NPVariant*)value);
		MediaStream* _mediaStream = (MediaStream*)(MediaStream::IsInstanceOf(npObj) ? npObj : Utils::NPObjectUpCast(npObj));
		if (_mediaStream) {
			cpp11::shared_ptr<_MediaStream> stream = _mediaStream->GetStream();
			if (stream) {
				This->StartVideoRenderer(stream->GetVideoTrack());
			}
		}
		else {
			This->StopVideoRenderer();
		}
		ret_val = true;
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool WebRTC::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
    return false;
}


//
// _RTCDisplay implementation
//
#if WE_UNDER_WINDOWS
HWND WebRTC::Handle()
{
	return reinterpret_cast<HWND>(GetWindowHandle());
}
#elif WE_UNDER_APPLE
CALayer* WebRTC::Layer()
{
	return m_pRootLayer;
}
#endif



// _RTCDisplay::OnStartVideoRenderer() implementation
void WebRTC::OnStartVideoRenderer()
{
	if (m_callbacks_onplay.size()) {
		for (size_t i = 0; i < m_callbacks_onplay.size(); ++i) {
			BrowserCallback* _cb = new BrowserCallback(m_npp, WM_SUCCESS, m_callbacks_onplay[i]);
			if (_cb) {
				_cb->AddObject(this); // not part of the standard: no arg to the callback
				dynamic_cast<_AsyncEventDispatcher*>(this)->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
		}
	}
}

// _RTCDisplay::OnStopVideoRenderer() implementation
void WebRTC::OnStopVideoRenderer()
{

}
