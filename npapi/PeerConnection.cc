/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "NPCommon.h"
#include "PeerConnection.h"
#include "MediaStream.h"
#include "MediaStreamTrack.h"
#include "MediaStreamEvent.h"
#include "SessionDescription.h"
#include "BrowserCallback.h"
#include "RTCIceCandidate.h"
#include "RTCPeerConnectionIceEvent.h"
#include "RTCStatsReport.h"
#include "RTCDTMFSender.h"
#include "RTCDataChannel.h"
#include "RTCDataChannelEvent.h"
#include "WebRTC.h"
#include "NPCommon.h"
#include "Utils.h"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

#define kPropLocalDescription						"localDescription"
#define kPropRemoteDescription						"remoteDescription"
#define kPropSignalingState							"signalingState"
#define kPropIceGatheringState						"iceGatheringState"
#define kPropIceConnectionState						"iceConnectionState"
#define kPropOnnegotiationneeded					"onnegotiationneeded"
#define kPropOnicecandidate							"onicecandidate"
#define kPropOnsignalingstatechange					"onsignalingstatechange"
#define kPropOnaddstream							"onaddstream"
#define kPropOnremovestream							"onremovestream"
#define kPropOniceconnectionstatechange				"oniceconnectionstatechange"
#define kPropOndatachannel							"ondatachannel"

#define kFuncCreateOffer							"createOffer"
#define kFuncCreateAnswer							"createAnswer"
#define kFuncSetLocalDescription					"setLocalDescription"
#define kFuncSetRemoteDescription					"setRemoteDescription"
#define kFuncUpdateIce								"updateIce"
#define kFuncAddIceCandidate						"addIceCandidate"
#define kFuncGetLocalStreams						"getLocalStreams"
#define kFuncGetRemoteStreams						"getRemoteStreams"
#define kFuncGetStreamById							"getStreamById"
#define kFuncAddStream								"addStream"
#define kFuncRemoveStream							"removeStream"
#define kFuncClose									"close"
#define kFuncGetStats								"getStats"
#define kFuncCreateDTMFSender						"createDTMFSender"
#define kFuncCreateDataChannel						"createDataChannel"

NPClass PeerConnectionClass = {
	NP_CLASS_STRUCT_VERSION,
	PeerConnection::Allocate,
	PeerConnection::Deallocate,
	PeerConnection::Invalidate,
	PeerConnection::HasMethod,
	PeerConnection::Invoke,
	PeerConnection::InvokeDefault,
	PeerConnection::HasProperty,
	PeerConnection::GetProperty,
	PeerConnection::SetProperty,
	PeerConnection::RemoveProperty,
	PeerConnection::NPEnumeration,
	PeerConnection::Construct,
};

void PeerConnection::Invalidate(NPObject *npobj)
{
}

bool PeerConnection::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return false;
}

bool PeerConnection::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

PeerConnection::PeerConnection(NPP instance)
	: m_npp(instance)
	, m_Peer(nullPtr)
	, m_callback_onnegotiationneeded(NULL)
	, m_callback_onicecandidate(NULL)
	, m_callback_onsignalingstatechange(NULL)
	, m_callback_onaddstream(NULL)
	, m_callback_onremovestream(NULL)
	, m_callback_oniceconnectionstatechange(NULL)
	, m_callback_ondatachannel(NULL)
{
	WE_DEBUG_INFO("PeerConnection::NewInstance()");
}

PeerConnection::~PeerConnection()
{
	Utils::NPObjectRelease(&m_callback_onnegotiationneeded);
	Utils::NPObjectRelease(&m_callback_onicecandidate);
	Utils::NPObjectRelease(&m_callback_onsignalingstatechange);
	Utils::NPObjectRelease(&m_callback_onaddstream);
	Utils::NPObjectRelease(&m_callback_onremovestream);
	Utils::NPObjectRelease(&m_callback_oniceconnectionstatechange);
	Utils::NPObjectRelease(&m_callback_ondatachannel);

	m_Peer = nullPtr;

	SetDispatcher(NULL);
}

NPError PeerConnection::Init(NPObject* RTCConfiguration, NPObject* MediaConstraints)
{
	NPError err = NPERR_NO_ERROR;

	cpp11::shared_ptr<_MediaConstraintsObj> mediaConstraints;
	CHECK_NPERR_RETURN(err = Utils::BuildMediaConstraintsObjs(m_npp, MediaConstraints, mediaConstraints));

	cpp11::shared_ptr<_RTCConfiguration> rtcConf;
	CHECK_NPERR_RETURN(err = Utils::BuildRTCConfiguration(m_npp, RTCConfiguration, rtcConf));

	m_Peer = cpp11::shared_ptr<_PeerConnection>(new _PeerConnection());
	if (!m_Peer->Init(rtcConf.get(), mediaConstraints.get())) {
		m_Peer = nullPtr;
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}

	// set callback functions
	m_Peer->SetCallback_onnegotiationneeded(cpp11::bind(&PeerConnection::onnegotiationneeded, this));
	m_Peer->SetCallback_onicecandidate(cpp11::bind(&PeerConnection::onicecandidate, this, cpp11::placeholders::_1));
	m_Peer->SetCallback_onsignalingstatechange(cpp11::bind(&PeerConnection::onsignalingstatechange, this));
	m_Peer->SetCallback_onaddstream(cpp11::bind(&PeerConnection::onaddstream, this, cpp11::placeholders::_1));
	m_Peer->SetCallback_onremovestream(cpp11::bind(&PeerConnection::onremovestream, this, cpp11::placeholders::_1));
	m_Peer->SetCallback_oniceconnectionstatechange(cpp11::bind(&PeerConnection::oniceconnectionstatechange, this));
	m_Peer->SetCallback_ondatachannel(cpp11::bind(&PeerConnection::ondatachannel, this, cpp11::placeholders::_1));

	return NPERR_NO_ERROR;
}

NPObject* PeerConnection::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new PeerConnection(instance));
}

void PeerConnection::Deallocate(NPObject* obj)
{
	delete (PeerConnection*)obj;
}

bool PeerConnection::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);

	bool ret_val = !strcmp(name, kFuncCreateOffer) ||
		!strcmp(name, kFuncCreateAnswer) ||
		!strcmp(name, kFuncSetLocalDescription) ||
		!strcmp(name, kFuncSetRemoteDescription) ||
		!strcmp(name, kFuncUpdateIce) ||
		!strcmp(name, kFuncAddIceCandidate) ||
		!strcmp(name, kFuncGetLocalStreams) ||
		!strcmp(name, kFuncGetRemoteStreams) ||
		!strcmp(name, kFuncGetStreamById) ||
		!strcmp(name, kFuncAddStream) ||
		!strcmp(name, kFuncRemoveStream) ||
		!strcmp(name, kFuncClose) ||
		!strcmp(name, kFuncGetStats) ||
		!strcmp(name, kFuncCreateDTMFSender) ||
		!strcmp(name, kFuncCreateDataChannel)
		;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool PeerConnection::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool PeerConnection::Invoke(NPObject* obj, NPIdentifier methodName,
	const NPVariant* args, uint32_t argCount,
	NPVariant* result)
{
	PeerConnection *This = static_cast<PeerConnection*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(methodName);
	bool ret_val = false;
	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kFuncCreateOffer)) {
		if (This->m_Peer) {
			NPObjectAutoRef successCallback(argCount > 0 ? Utils::VariantToObject((NPVariant*)&args[0]) : NULL);
			NPObjectAutoRef failureCallback(argCount > 1 ? Utils::VariantToObject((NPVariant*)&args[1]) : NULL);
			NPObjectAutoRef mediaConstraints(argCount > 2 ? Utils::VariantToObject((NPVariant*)&args[2]) : NULL);

			NPError err;

			cpp11::shared_ptr<_MediaConstraintsObj> _mediaConstraints;
			err = Utils::BuildMediaConstraintsObjs(This->m_npp, mediaConstraints, _mediaConstraints);
			if (err == NPERR_NO_ERROR) {
				ret_val = This->m_Peer->CreateOffer(
					[successCallback, This](cpp11::shared_ptr<_SessionDescription> sdp) {
					if (successCallback) {
						SessionDescription* _sdp;
						NPError _err = SessionDescription::CreateInstanceWithRef(This->m_npp, &_sdp);
						if (_err == NPERR_NO_ERROR) {
							_sdp->SetSdp(sdp);
							BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_CREATEOFFER_SUCCESS, successCallback);
							if (_cb) {
								_cb->AddObject(_sdp);
								This->RaiseCallback(_cb);
								SafeReleaseObject(&_cb);
							}
							SessionDescription::ReleaseInstance(&_sdp);
						}
					}
				},
					[failureCallback, This](cpp11::shared_ptr<std::string> error) {
					if (failureCallback) {
						BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_CREATEOFFER_ERROR, failureCallback);
						if (_cb) {
							_cb->AddString((void*)error->c_str(), error->length());
							This->RaiseCallback(_cb);
							SafeReleaseObject(&_cb);
						}
					}
				},
				_mediaConstraints.get());
			}
		}
	}
	else if (!strcmp(name, kFuncCreateAnswer)) {
		if (This->m_Peer) {
			NPObjectAutoRef successCallback(argCount > 0 ? Utils::VariantToObject((NPVariant*)&args[0]) : NULL);
			NPObjectAutoRef failureCallback(argCount > 1 ? Utils::VariantToObject((NPVariant*)&args[1]) : NULL);
			NPObjectAutoRef mediaConstraints(argCount > 2 ? Utils::VariantToObject((NPVariant*)&args[2]) : NULL);

			NPError err;

			cpp11::shared_ptr<_MediaConstraintsObj> _mediaConstraints;
			err = Utils::BuildMediaConstraintsObjs(This->m_npp, mediaConstraints, _mediaConstraints);
			if (err == NPERR_NO_ERROR) {
				ret_val = This->m_Peer->CreateAnswer(
					[successCallback, This](cpp11::shared_ptr<_SessionDescription> sdp) {
					if (successCallback) {
						SessionDescription* _sdp;
						NPError _err = SessionDescription::CreateInstanceWithRef(This->m_npp, &_sdp);
						if (_err == NPERR_NO_ERROR) {
							_sdp->SetSdp(sdp);
							BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_CREATEOFFER_SUCCESS, successCallback);
							if (_cb) {
								_cb->AddObject(_sdp);
								This->RaiseCallback(_cb);
								SafeReleaseObject(&_cb);
							}
							SessionDescription::ReleaseInstance(&_sdp);
						}
					}
				},
					[failureCallback, This](cpp11::shared_ptr<std::string> error) {
					if (failureCallback) {
						BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_CREATEOFFER_ERROR, failureCallback);
						if (_cb) {
							_cb->AddString((void*)error->c_str(), error->length());
							This->RaiseCallback(_cb);
							SafeReleaseObject(&_cb);
						}
					}
				},
					_mediaConstraints.get());
			}
		}
	}
	else if (!strcmp(name, kFuncSetLocalDescription)) {
		if (This->m_Peer && argCount > 0) {
			NPObject* npObj = Utils::VariantToObject((NPVariant*)&args[0]);
			SessionDescription* sdp = (SessionDescription*)(SessionDescription::IsInstanceOf(npObj) ? npObj : Utils::NPObjectUpCast(npObj));
			if (sdp) {
				NPObjectAutoRef successCallback(argCount > 1 ? Utils::VariantToObject((NPVariant*)&args[1]) : NULL);
				NPObjectAutoRef failureCallback(argCount > 2 ? Utils::VariantToObject((NPVariant*)&args[2]) : NULL);
				ret_val = This->m_Peer->SetLocalDescription(
					sdp->GetSdp().get(),
					[successCallback, This]() {
					if (successCallback) {
						BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_SUCCESS, successCallback);
						if (_cb) {
							This->RaiseCallback(_cb);
							SafeReleaseObject(&_cb);
						}
					}
				},
					[failureCallback, This](cpp11::shared_ptr<std::string> error) {
					if (failureCallback) {
						BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_CREATEOFFER_ERROR, failureCallback);
						if (_cb) {
							_cb->AddString((void*)error->c_str(), error->length());
							This->RaiseCallback(_cb);
							SafeReleaseObject(&_cb);
						}
					}
				}
				);
			}
		}
	}
	else if (!strcmp(name, kFuncSetRemoteDescription)) {
		if (This->m_Peer && argCount > 0) {
			NPObject* npObj = Utils::VariantToObject((NPVariant*)&args[0]);
			SessionDescription* sdp = (SessionDescription*)(SessionDescription::IsInstanceOf(npObj) ? npObj : Utils::NPObjectUpCast(npObj));
			if (sdp) {
				NPObjectAutoRef successCallback(argCount > 1 ? Utils::VariantToObject((NPVariant*)&args[1]) : NULL);
				NPObjectAutoRef failureCallback(argCount > 2 ? Utils::VariantToObject((NPVariant*)&args[2]) : NULL);
				ret_val = This->m_Peer->SetRemoteDescription(
					sdp->GetSdp().get(),
					[successCallback, This]() {
					if (successCallback) {
						BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_SUCCESS, successCallback);
						if (_cb) {
							This->RaiseCallback(_cb);
							SafeReleaseObject(&_cb);
						}
					}
				},
					[failureCallback, This](cpp11::shared_ptr<std::string> error) {
					if (failureCallback) {
						BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_CREATEOFFER_ERROR, failureCallback);
						if (_cb) {
							_cb->AddString((void*)error->c_str(), error->length());
							This->RaiseCallback(_cb);
							SafeReleaseObject(&_cb);
						}
					}
				}
				);
			}
		}
	}
	else if (!strcmp(name, kFuncUpdateIce)) {
		if (This->m_Peer) {
			NPObject* RTCConfiguration = argCount > 0 ? Utils::VariantToObject((NPVariant*)&args[0]) : NULL;
			NPObject* mediaConstraints = argCount > 1 ? Utils::VariantToObject((NPVariant*)&args[1]) : NULL;
			cpp11::shared_ptr<_RTCConfiguration> _rtcConf;
			NPError err = Utils::BuildRTCConfiguration(This->m_npp, RTCConfiguration, _rtcConf);
			if (err == NPERR_NO_ERROR) {
				cpp11::shared_ptr<_MediaConstraintsObj> _mediaConstraints;
				err = Utils::BuildMediaConstraintsObjs(This->m_npp, mediaConstraints, _mediaConstraints);
				if (err == NPERR_NO_ERROR) {
					ret_val = This->m_Peer->UpdateIce(_rtcConf.get(), _mediaConstraints.get());
				}
			}
		}
	}
	else if (!strcmp(name, kFuncAddIceCandidate)) {
		if (This->m_Peer && argCount > 0) {
			NPObject* npObj = Utils::VariantToObject((NPVariant*)&args[0]);
			RTCIceCandidate* candidate = (RTCIceCandidate*)(RTCIceCandidate::IsInstanceOf(npObj) ? npObj : Utils::NPObjectUpCast(npObj));
			if (candidate) {
				NPObjectAutoRef successCallback(argCount > 1 ? Utils::VariantToObject((NPVariant*)&args[1]) : NULL);
				NPObjectAutoRef failureCallback(argCount > 2 ? Utils::VariantToObject((NPVariant*)&args[2]) : NULL);
				ret_val = This->m_Peer->AddIceCandidate(
					candidate->GetCandidate().get(),
					[successCallback, This]() {
					if (successCallback) {
						BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_SUCCESS, successCallback);
						if (_cb) {
							This->RaiseCallback(_cb);
							SafeReleaseObject(&_cb);
						}
					}
				},
					[failureCallback, This](cpp11::shared_ptr<std::string> error) {
					if (failureCallback) {
						BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_CREATEOFFER_ERROR, failureCallback);
						if (_cb) {
							_cb->AddString((void*)error->c_str(), error->length());
							This->RaiseCallback(_cb);
							SafeReleaseObject(&_cb);
						}
					}
				}
				);
			}
		}
	}
	else if (!strcmp(name, kFuncGetLocalStreams)) {
		ret_val = (This->getStreams(false/*local*/, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kFuncGetRemoteStreams)) {
		ret_val = (This->getStreams(true/*remote*/, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kFuncGetStreamById)) {
		if (This->m_Peer && argCount > 0) {
			std::string streamId = Utils::VariantToString((NPVariant*)&args[0]);
			if (!streamId.empty()) {
				cpp11::shared_ptr<_MediaStream> stream = This->m_Peer->GetStreamById(streamId.c_str());
				if (stream) {
					MediaStream* _stream;
					NPError err = MediaStream::CreateInstanceWithRef(This->m_npp, &_stream);
					if (err == NPERR_NO_ERROR) {
						_stream->SetDispatcher(const_cast<_AsyncEventDispatcher*>(This->GetDispatcher()));
						_stream->SetStream(stream);
						ret_val = true;
						OBJECT_TO_NPVARIANT(_stream, *result);
					}
				}
				else {
					ret_val = true;
					VOID_TO_NPVARIANT(*result);
				}
			}
		}
	}
	else if (!strcmp(name, kFuncAddStream)) {
		if (This->m_Peer) {
			NPObject* stream = argCount > 0 ? Utils::VariantToObject((NPVariant*)&args[0]) : NULL;
			MediaStream* _stream = (MediaStream*)(MediaStream::IsInstanceOf(stream) ? stream : Utils::NPObjectUpCast(stream));
			NPObject* mediaConstraints = argCount > 1 ? Utils::VariantToObject((NPVariant*)&args[1]) : NULL;
			if (_stream) {
				cpp11::shared_ptr<_MediaConstraintsObj> _mediaConstraints;
				NPError err = Utils::BuildMediaConstraintsObjs(This->m_npp, mediaConstraints, _mediaConstraints);
				if (err == NPERR_NO_ERROR) {
					ret_val = This->m_Peer->AddStream(_stream->GetStream().get(), _mediaConstraints.get());
				}
			}
		}
	}
	else if (!strcmp(name, kFuncRemoveStream)) {
		if (This->m_Peer && argCount > 0) {
			NPObject* stream = Utils::VariantToObject((NPVariant*)&args[0]);
			MediaStream* _stream = (MediaStream*)(MediaStream::IsInstanceOf(stream) ? stream : Utils::NPObjectUpCast(stream));
			if (_stream) {
				ret_val = This->m_Peer->RemoveStream(_stream->GetStream().get());
			}
		}
	}
	else if (!strcmp(name, kFuncClose)) {
		if (This->m_Peer) {
			ret_val = This->m_Peer->Close();
		}
	}
	else if (!strcmp(name, kFuncGetStats)) {
		if (This->m_Peer) {
			// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-getStats-void-MediaStreamTrack-selector-RTCStatsCallback-successCallback-RTCPeerConnectionErrorCallback-failureCallback
			// Standard: void getStats (MediaStreamTrack? selector, RTCStatsCallback successCallback, RTCPeerConnectionErrorCallback failureCallback);
			// Chrome: void getStats (RTCStatsCallback successCallback, RTCPeerConnectionErrorCallback failureCallback);
			// Chrome issue: "selector" is nullable and not optional

			NPObject* _selector = Utils::VariantToObject((NPVariant*)&args[0]);
			NPObjectAutoRef _successCallback(argCount > 1 ? Utils::VariantToObject((NPVariant*)&args[1]) : NULL);
			NPObjectAutoRef _failureCallback(argCount > 2 ? Utils::VariantToObject((NPVariant*)&args[2]) : NULL);

			if (_selector || _successCallback || _failureCallback) {
				MediaStreamTrack* _mediaStreamTrack = (MediaStreamTrack*)(MediaStreamTrack::IsInstanceOf(_selector) ? _selector : Utils::NPObjectUpCast(_selector));
				if (!MediaStreamTrack::IsInstanceOf(_selector)) {
					_failureCallback = _successCallback;
					_successCallback = _selector;
					_selector = NULL;
					_mediaStreamTrack = NULL;
				}
				_MediaStreamTrackBase* pSelector = NULL;
				if (_mediaStreamTrack){
					pSelector = dynamic_cast<_MediaStreamTrackBase*>(_mediaStreamTrack->GetTrack().get());
				}
				ret_val = This->m_Peer->GetStats(
					pSelector,
					[_successCallback, This](cpp11::shared_ptr<_RTCStatsReport> report) {
					if (_successCallback){
						RTCStatsReport* _report;
						NPError err = RTCStatsReport::CreateInstanceWithRef(This->m_npp, &_report);
						if (err == NPERR_NO_ERROR) {
							BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_SUCCESS, _successCallback);
							if (_cb) {
								_report->SetStats(report);
								_report->SetDispatcher(const_cast<_AsyncEventDispatcher*>(This->GetDispatcher()));
								_cb->AddObject(_report);
								This->RaiseCallback(_cb);
								SafeReleaseObject(&_cb);
							}
							RTCStatsReport::ReleaseInstance(&_report);
						}
					}
				},
					[_failureCallback, This](cpp11::shared_ptr<std::string> error) {
					if (_failureCallback){
						BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_ERROR, _failureCallback);
						if (_cb) {
							_cb->AddString((void*)error->c_str(), error->length());
							This->RaiseCallback(_cb);
							SafeReleaseObject(&_cb);
						}
					}
				});
				if (!ret_val && _failureCallback) {
					BrowserCallback* _cb = new BrowserCallback(This->m_npp, WM_ERROR, _failureCallback);
					if (_cb) {
						std::string err("Global error");
						_cb->AddString((void*)err.c_str(), err.length());
						This->RaiseCallback(_cb);
						SafeReleaseObject(&_cb);
					}
				}
				ret_val = true;
			}
			else {
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kFuncCreateDTMFSender)) {
		if (This->m_Peer && argCount > 0) {
			NPObject* _MediaStreamTrack = Utils::VariantToObject((NPVariant*)&args[0]);
			MediaStreamTrack* _mediaStreamTrack = (MediaStreamTrack*)(MediaStreamTrack::IsInstanceOf(_MediaStreamTrack) ? _MediaStreamTrack : Utils::NPObjectUpCast(_MediaStreamTrack));
			if (_mediaStreamTrack) {
				cpp11::shared_ptr<_RTCDTMFSender>sender = This->m_Peer->CreateDtmfSender(_mediaStreamTrack->GetTrack().get());
				if (sender) {
					RTCDTMFSender* _sender = NULL;
					NPError err = RTCDTMFSender::CreateInstanceWithRef(This->m_npp, &_sender);
					if (err == NPERR_NO_ERROR) {
						_sender->SetSender(sender);
						_sender->SetDispatcher(const_cast<_AsyncEventDispatcher*>(This->GetDispatcher()));
						OBJECT_TO_NPVARIANT(_sender, *result); _sender = NULL;
						RTCDTMFSender::ReleaseInstance(&_sender);
						ret_val = true;
					}
				}
			}
		}
	}
	else if (!strcmp(name, kFuncCreateDataChannel)) {
		if (This->m_Peer) {
			std::string label = "";
			if (argCount > 0 && args[0].type == NPVariantType_String) {
				label = std::string(args[0].value.stringValue.UTF8Characters, args[0].value.stringValue.UTF8Length);
			}
			NPObject* dataChannelDict = argCount > 1 ? Utils::VariantToObject((NPVariant*)&args[1]) : NULL;

			cpp11::shared_ptr<_RTCDataChannelInit> _dataChannelDict;
			NPError err = Utils::BuildRTCDataChannelInit(This->m_npp, dataChannelDict, _dataChannelDict);
			cpp11::shared_ptr<_RTCDataChannel> dataChannel = This->m_Peer->CreateDataChannel(label.c_str(), _dataChannelDict);
			if (err == NPERR_NO_ERROR) {
				RTCDataChannel* _dataChannel = NULL;
				err = RTCDataChannel::CreateInstanceWithRef(This->m_npp, &_dataChannel);
				if (err == NPERR_NO_ERROR) {
					_dataChannel->SetChannel(dataChannel);
					_dataChannel->SetDispatcher(const_cast<_AsyncEventDispatcher*>(This->GetDispatcher()));
					OBJECT_TO_NPVARIANT(_dataChannel, *result); _dataChannel = NULL;
					RTCDataChannel::ReleaseInstance(&_dataChannel);
					ret_val = true;
				}
			}
		}
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool PeerConnection::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val = !strcmp(name, kPropUniqueId) ||
		!strcmp(name, kPropLocalDescription) ||
		!strcmp(name, kPropRemoteDescription) ||
		!strcmp(name, kPropSignalingState) ||
		!strcmp(name, kPropIceGatheringState) ||
		!strcmp(name, kPropIceConnectionState) ||
		!strcmp(name, kPropOnnegotiationneeded) ||
		!strcmp(name, kPropOnicecandidate) ||
		!strcmp(name, kPropOnsignalingstatechange) ||
		!strcmp(name, kPropOnaddstream) ||
		!strcmp(name, kPropOnremovestream) ||
		!strcmp(name, kPropOniceconnectionstatechange) ||
		!strcmp(name, kPropOndatachannel)
		;

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool PeerConnection::SetProperty(NPObject *npobj, NPIdentifier propertyName, const NPVariant *value)
{
	PeerConnection *This = static_cast<PeerConnection*>(npobj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropLocalDescription)) {
		// readonly
	}
	else if (!strcmp(name, kPropRemoteDescription)) {
		// readonly
	}
	else if (!strcmp(name, kPropSignalingState)) {
		// readonly
	}
	else if (!strcmp(name, kPropIceGatheringState)) {
		// readonly
	}
	else if (!strcmp(name, kPropIceConnectionState)) {
		// readonly
	}
	else if (!strcmp(name, kPropOnnegotiationneeded)) {
		Utils::NPObjectSet(&This->m_callback_onnegotiationneeded, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}
	else if (!strcmp(name, kPropOnicecandidate)) {
		Utils::NPObjectSet(&This->m_callback_onicecandidate, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}
	else if (!strcmp(name, kPropOnsignalingstatechange)) {
		Utils::NPObjectSet(&This->m_callback_onsignalingstatechange, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}
	else if (!strcmp(name, kPropOnaddstream)) {
		Utils::NPObjectSet(&This->m_callback_onaddstream, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}
	else if (!strcmp(name, kPropOnremovestream)) {
		Utils::NPObjectSet(&This->m_callback_onremovestream, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}
	else if (!strcmp(name, kPropOniceconnectionstatechange)) {
		Utils::NPObjectSet(&This->m_callback_oniceconnectionstatechange, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}
	else if (!strcmp(name, kPropOndatachannel)) {
		Utils::NPObjectSet(&This->m_callback_ondatachannel, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}

	

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool PeerConnection::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	PeerConnection *This = static_cast<PeerConnection*>(obj);
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropUniqueId)) {
		DOUBLE_TO_NPVARIANT(This->UniqueId(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropLocalDescription)) {
		if (This->m_Peer) {
			cpp11::shared_ptr<_SessionDescription>sdp = This->m_Peer->LocalDescription();
			if (sdp) {
				SessionDescription* _sdp;
				NPError err = SessionDescription::CreateInstanceWithRef(This->m_npp, &_sdp);
				if (err == NPERR_NO_ERROR) {
					_sdp->SetSdp(sdp);
					OBJECT_TO_NPVARIANT(_sdp, *result);
					ret_val = true;
				}
			}
			else {
				NULL_TO_NPVARIANT(*result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropRemoteDescription)) {
		if (This->m_Peer) {
			cpp11::shared_ptr<_SessionDescription>sdp = This->m_Peer->RemoteDescription();
			if (sdp) {
				SessionDescription* _sdp;
				NPError err = SessionDescription::CreateInstanceWithRef(This->m_npp, &_sdp);
				if (err == NPERR_NO_ERROR) {
					_sdp->SetSdp(sdp);
					OBJECT_TO_NPVARIANT(_sdp, *result);
					ret_val = true;
				}
			}
			else {
				NULL_TO_NPVARIANT(*result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropSignalingState)) {
		if (This->m_Peer) {
			NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Peer->SignalingState(), we_strlen(This->m_Peer->SignalingState()));
			if (npStr) {
				STRINGZ_TO_NPVARIANT(npStr, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropIceGatheringState)) {
		if (This->m_Peer) {
			NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Peer->IceGatheringState(), we_strlen(This->m_Peer->IceGatheringState()));
			if (npStr) {
				STRINGZ_TO_NPVARIANT(npStr, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropIceConnectionState)) {
		if (This->m_Peer) {
			NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Peer->IceConnectionState(), we_strlen(This->m_Peer->IceConnectionState()));
			if (npStr) {
				STRINGZ_TO_NPVARIANT(npStr, *result);
				ret_val = true;
			}
		}
	}
	else if (!strcmp(name, kPropOnnegotiationneeded)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onnegotiationneeded, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropOnicecandidate)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onicecandidate, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropOnsignalingstatechange)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onsignalingstatechange, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropOnaddstream)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onaddstream, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropOnremovestream)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onremovestream, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropOniceconnectionstatechange)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_oniceconnectionstatechange, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropOndatachannel)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_ondatachannel, result) == NPERR_NO_ERROR);
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool PeerConnection::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
	return false;
}

void PeerConnection::onnegotiationneeded()
{
	if (m_callback_onnegotiationneeded) {
		BrowserCallback* _cb = new BrowserCallback(m_npp, WM_ONNEGOTIATIONNEEDED, m_callback_onnegotiationneeded);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void PeerConnection::onicecandidate(cpp11::shared_ptr<_RTCPeerConnectionIceEvent> e)
{
	if (m_callback_onicecandidate) {
		RTCPeerConnectionIceEvent* candidateEvent;
		NPError err = RTCPeerConnectionIceEvent::CreateInstanceWithRef(m_npp, &candidateEvent);
		if (err == NPERR_NO_ERROR) {
			candidateEvent->SetEvent(e);
			BrowserCallback* _cb = new BrowserCallback(m_npp, WM_ONICECANDIDATE, m_callback_onicecandidate);
			if (_cb) {
				_cb->AddObject(candidateEvent);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
			RTCPeerConnectionIceEvent::ReleaseInstance(&candidateEvent);
		}
	}
}

void PeerConnection::onsignalingstatechange()
{
	if (m_callback_onsignalingstatechange) {
		BrowserCallback* _cb = new BrowserCallback(m_npp, WM_ONSIGNALINGSTATECHANGE, m_callback_onsignalingstatechange);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void PeerConnection::onaddstream(cpp11::shared_ptr<_MediaStreamEvent> e)
{
	if (m_callback_onaddstream) {
		MediaStreamEvent* _event;
		NPError err = MediaStreamEvent::CreateInstanceWithRef(m_npp, &_event);
		if (err == NPERR_NO_ERROR) {
			_event->SetEvent(e);
			BrowserCallback* _cb = new BrowserCallback(m_npp, WM_ONADDSTREAM, m_callback_onaddstream);
			if (_cb) {
				_event->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
				_cb->AddObject(_event);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
			MediaStreamEvent::ReleaseInstance(&_event);
		}
	}
}

void PeerConnection::onremovestream(cpp11::shared_ptr<_MediaStreamEvent> e)
{
	if (m_callback_onremovestream) {
		MediaStreamEvent* _event;
		NPError err = MediaStreamEvent::CreateInstanceWithRef(m_npp, &_event);
		if (err == NPERR_NO_ERROR) {
			_event->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
			_event->SetEvent(e);
			BrowserCallback* _cb = new BrowserCallback(m_npp, WM_ONREMOVESTREAM, m_callback_onremovestream);
			if (_cb) {
				_cb->AddObject(_event);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
			MediaStreamEvent::ReleaseInstance(&_event);
		}
	}
}

void PeerConnection::oniceconnectionstatechange()
{
	if (m_callback_oniceconnectionstatechange) {
		BrowserCallback* _cb = new BrowserCallback(m_npp, WM_ONICECONNECTIONSTATECHANGE, m_callback_oniceconnectionstatechange);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void PeerConnection::ondatachannel(cpp11::shared_ptr<_RTCDataChannelEvent> e)
{
	if (m_callback_ondatachannel) {
		RTCDataChannelEvent* _event;
		NPError err = RTCDataChannelEvent::CreateInstanceWithRef(m_npp, &_event);
		if (err == NPERR_NO_ERROR) {
			_event->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
			_event->SetEvent(e);
			BrowserCallback* _cb = new BrowserCallback(m_npp, WM_SUCCESS, m_callback_ondatachannel);
			if (_cb) {
				_cb->AddObject(_event);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
			RTCDataChannelEvent::ReleaseInstance(&_event);
		}
	}
}

NPError PeerConnection::getStreams(bool remote, NPVariant* MediaStreams)
{
	if (!m_Peer) {
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
	_AsyncEventDispatcher* dispatcher = dynamic_cast<_AsyncEventDispatcher*>(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
	if (!dispatcher) {
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}

	NPError err;
	std::vector<NPVariant> vect;
	cpp11::shared_ptr<_Sequence<_MediaStream> > streams = remote ? m_Peer->GetRemoteStreams() : m_Peer->GetLocalStreams();
	if (streams) {
		for (size_t i = 0; i < streams->values.size(); ++i) {
			if (!streams->values[i]) {
				continue;
			}
			MediaStream* _stream;
			err = MediaStream::CreateInstanceWithRef(m_npp, &_stream);
			if (err == NPERR_NO_ERROR) {
				_stream->SetDispatcher(dispatcher);
				_stream->SetStream(streams->values[i]);

				NPVariant var;
				OBJECT_TO_NPVARIANT(_stream, var);
				BrowserFuncs->retainobject(var.value.objectValue); // will be release by "NPVecClear()" 
				vect.push_back(var);
				MediaStream::ReleaseInstance(&_stream);
			}
		}
	}

	NPObject* arrayObj = NULL;
	err = Utils::CreateJsArray(m_npp, vect, &arrayObj);
	if (err == NPERR_NO_ERROR) {
		OBJECT_TO_NPVARIANT(arrayObj, *MediaStreams);
	}

	Utils::NPVecClear(vect);

	return err;
}