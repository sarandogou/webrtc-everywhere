// http://www.w3.org/TR/mediacapture-streams/
// http://www.w3.org/TR/webrtc/



#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <assert.h>

#include "_PeerConnection.h"
#include "_NavigatorUserMedia.h"
#include "_MediaStream.h"
#include "_MediaStreamTrack.h"
#include "_MediaTrackConstraints.h"
#include "_MediaStreamConstraints.h"
#include "_Utils.h"
#include "_Debug.h"

#ifdef WIN32
#include <Windows.h>
#endif

static std::shared_ptr<_MediaStream> mediaStream = nullptr;
static std::shared_ptr<_SessionDescription>sdpOffer = nullptr;
static std::shared_ptr<_PeerConnection>peerConnection = nullptr;

// http://www.w3.org/TR/webrtc/#idl-def-RTCSessionDescriptionCallback
static void CreateOfferSuccessCb(std::shared_ptr<_SessionDescription> sdp)
{
	sdpOffer = sdp;
}

// http://www.w3.org/TR/webrtc/#idl-def-RTCPeerConnectionErrorCallback
static void CreateOfferErrorCb(std::shared_ptr<std::string> error)
{

}

// http://www.w3.org/TR/mediacapture-streams/#idl-def-NavigatorUserMediaSuccessCallback
static void NavigatorUserMediaSuccessCb(std::shared_ptr<_MediaStream> stream)
{
	mediaStream = stream;
}

// http://www.w3.org/TR/mediacapture-streams/#idl-def-NavigatorUserMediaErrorCallback
static void NavigatorUserMediaErrorCb(std::shared_ptr<_NavigatorUserMediaError>e)
{
	WE_DEBUG_ERROR("%s", e->constraintName.c_str());
}

// http://www.w3.org/TR/webrtc/#event-negotiation
static void onnegotiationneededCallback()
{

}
// http://www.w3.org/TR/webrtc/#event-icecandidate
static void onicecandidateCallback(std::shared_ptr<_RTCPeerConnectionIceEvent> e)
{
	if (e->candidate) {
		peerConnection->AddIceCandidate(e->candidate.get());
	}
}
// http://www.w3.org/TR/webrtc/#event-signalingstatechange
static void onsignalingstatechangeCallback()
{
	if (peerConnection) {
		WE_DEBUG_INFO("New signaling state: %s", peerConnection->SignalingState());
	}
}
// http://www.w3.org/TR/webrtc/#event-mediastream-addstream
static void onaddstreamCallback(std::shared_ptr<_MediaStreamEvent> stream)
{

}

// http://www.w3.org/TR/webrtc/#event-mediastream-removestream
static void onremovestreamCallback(std::shared_ptr<_MediaStreamEvent> stream)
{

}
// http://www.w3.org/TR/webrtc/#event-iceconnectionstatechange
static void oniceconnectionstatechangeCallback()
{

}

// http://www.w3.org/TR/webrtc/#idl-def-RTCStatsCallback
static void onRTCStatsCallback(std::shared_ptr<_RTCStatsReport> report)
{

}

int _tmain(int argc, _TCHAR* argv[])
{
	_Utils::Initialize();
	TakeFakePeerConnectionFactory();

	peerConnection = std::make_shared<_PeerConnection>();
	static _RTCIceServer iceServers[] = {
			{ "stun:stun.l.google.com:19302" },
			{ "turn:numb.viagenie.ca:3478", "user", "password" },
	};
	static size_t iceServersCount = sizeof(iceServers) / sizeof(iceServers[0]);

	std::shared_ptr<_Sequence<_MediaStream> > localStreams;
	std::shared_ptr<_Sequence<_MediaStream> > remoteStreams;
	
	_RTCConfiguration peerConnectionConfiguration;
	peerConnectionConfiguration.iceServers.push_back(_RTCIceServer(iceServers[0].uri, iceServers[0].username, iceServers[0].password));
	peerConnectionConfiguration.iceServers.push_back(_RTCIceServer(iceServers[1].uri, iceServers[1].username, iceServers[1].password));

	std::shared_ptr<_MediaConstraints> optional = std::make_shared<_MediaConstraints>();
	std::shared_ptr<_MediaConstraints> mandatory = std::make_shared<_MediaConstraints>();
	_MediaConstraintsObj peerConnectionConstraints(optional, mandatory);

	std::shared_ptr<_MediaTrackConstraints> audio = std::make_shared<_MediaTrackConstraints>(true);
	std::shared_ptr<_MediaTrackConstraints> video = std::make_shared<_MediaTrackConstraints>(true);
	_MediaStreamConstraints mediaStreamConstraints(audio, video);

	_NavigatorUserMedia::getUserMedia(&mediaStreamConstraints, NavigatorUserMediaSuccessCb, NavigatorUserMediaErrorCb);

	if (!mediaStream) {
		goto bail;
	}

	peerConnection->SetCallback_onnegotiationneeded(onnegotiationneededCallback);
	peerConnection->SetCallback_onicecandidate(onicecandidateCallback);
	peerConnection->SetCallback_onsignalingstatechange(onsignalingstatechangeCallback);
	peerConnection->SetCallback_onaddstream(onaddstreamCallback);
	peerConnection->SetCallback_onremovestream(onremovestreamCallback);
	peerConnection->SetCallback_oniceconnectionstatechange(oniceconnectionstatechangeCallback);
		
	mandatory->insert(std::pair<std::string, std::string>("DtlsSrtpKeyAgreement", "true"));
	if (!peerConnection->Init(&peerConnectionConfiguration, &peerConnectionConstraints)) {
		goto bail;
	}

	if (!peerConnection->AddStream(mediaStream.get())) {
		goto bail;
	}

	if (!peerConnection->CreateOffer(CreateOfferSuccessCb, CreateOfferErrorCb)) {
		goto bail;
	}

	// FIXME: AssertBreak() at the end because not all streams are destroyed
	localStreams = peerConnection->GetLocalStreams();
	remoteStreams = peerConnection->GetRemoteStreams();

	if (localStreams->values.size() > 0) {
		std::shared_ptr<_MediaStream>localStream = localStreams->values[0]->clone();

		std::shared_ptr<_Sequence<_MediaStreamTrack> > audioTracks = localStream->getAudioTracks();
		std::shared_ptr<_Sequence<_MediaStreamTrack> > videoTracks = localStream->getVideoTracks();

		WE_DEBUG_INFO("audioTracks.size() = %ld", audioTracks->values.size());
		WE_DEBUG_INFO("videoTracks.size() = %ld", videoTracks->values.size());

		for (size_t i = 0; i < audioTracks->values.size(); ++i) {
			WE_DEBUG_INFO("AudioTrack: %s, %s, %s", audioTracks->values[i]->id(), audioTracks->values[i]->kind(), audioTracks->values[i]->label());
		}
		for (size_t i = 0; i < videoTracks->values.size(); ++i) {
			WE_DEBUG_INFO("VideoTrack: %s, %s, %s", videoTracks->values[i]->id(), videoTracks->values[i]->kind(), videoTracks->values[i]->label());
		}
	}

	getchar();

	localStreams = nullptr;
	remoteStreams = nullptr;
	peerConnection = nullptr;
	mediaStream = nullptr;
	_Utils::DeInitialize();
	ReleaseFakePeerConnectionFactory();

	return 0;

bail:
	assert(0);
	return -1;
}