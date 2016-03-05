/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_COMMON_PEERCONNECTION_H_
#define _WEBRTC_EVERYWHERE_COMMON_PEERCONNECTION_H_

#include "_Config.h"
#include "_Common.h"

#include "talk/app/webrtc/mediastreaminterface.h"
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "webrtc/base/scoped_ptr.h"

class _Buffer;
class _MediaStream;
class _PeerConnection;
class _SessionDescription;
class _MediaStreamTrackBase;
class _MediaStreamTrack;
class _RTCDTMFSender;
class _RTCDataChannel;

namespace webrtc {
class VideoCaptureModule;
}  // namespace webrtc

namespace cricket {
class VideoRenderer;
}  // namespace cricket

//
//	_RTCPeerConnection
//
class _RTCPeerConnection
	: public webrtc::PeerConnectionObserver
	, public rtc::RefCountInterface
{
public:
	_RTCPeerConnection(const _PeerConnection* pcBase, const webrtc::PeerConnectionInterface::RTCConfiguration& configuration, const webrtc::MediaConstraintsInterface* constraints = NULL);
	bool IsValid() { return m_bValid; }

	bool createOffer(_RTCSessionDescriptionCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr, const webrtc::MediaConstraintsInterface* constraints = NULL);
	bool createAnswer(_RTCSessionDescriptionCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr, const webrtc::MediaConstraintsInterface* constraints = NULL);
	bool setLocalDescription(webrtc::SessionDescriptionInterface* description, _VoidFunctionCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr);
	const webrtc::SessionDescriptionInterface* localDescription();
	bool setRemoteDescription(webrtc::SessionDescriptionInterface* description, _VoidFunctionCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr);
	const webrtc::SessionDescriptionInterface* remoteDescription();
	const char* signalingState();
	bool updateIce(const webrtc::PeerConnectionInterface::RTCConfiguration& configuration, const webrtc::MediaConstraintsInterface* constraints = NULL);
	bool addIceCandidate(const webrtc::IceCandidateInterface* candidate, _VoidFunctionCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr);
	const char* iceGatheringState();
	const char* iceConnectionState();
	rtc::scoped_refptr<webrtc::StreamCollectionInterface> getLocalStreams();
	rtc::scoped_refptr<webrtc::StreamCollectionInterface> getRemoteStreams();
	webrtc::MediaStreamInterface* getStreamById(std::string streamId);
	bool addStream(webrtc::MediaStreamInterface* stream, const webrtc::MediaConstraintsInterface* constraints);
	bool removeStream(webrtc::MediaStreamInterface* stream);
	bool close();
	bool getStats(webrtc::MediaStreamTrackInterface* selector = NULL, _RTCStatsCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr);
	cpp11::shared_ptr<_RTCDTMFSender> createDTMFSender(webrtc::AudioTrackInterface *track);
	cpp11::shared_ptr<_RTCDataChannel> CreateDataChannel(const std::string& label, const webrtc::DataChannelInit* config);

protected:
	virtual ~_RTCPeerConnection();

	//
	// PeerConnectionObserver implementation.
	//
	virtual void OnError();
	virtual void OnStateChange(webrtc::PeerConnectionObserver::StateType state_changed);
	virtual void OnAddStream(webrtc::MediaStreamInterface* stream);
	virtual void OnRemoveStream(webrtc::MediaStreamInterface* stream);
	virtual void OnRenegotiationNeeded();
	virtual void OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state);
	virtual void OnIceCandidate(const webrtc::IceCandidateInterface* candidate);
	virtual void OnIceComplete();
	virtual void OnDataChannel(webrtc::DataChannelInterface* data_channel);

private:
	rtc::scoped_refptr<webrtc::PeerConnectionInterface> m_peer_connection;
	rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> m_peer_connection_factory;
	const _PeerConnection* m_pcBase;
	
	bool m_bValid;
};

//
//	_PeerConnection
//
class WEBRTC_EVERYWHERE_API _PeerConnection
{
	friend class _RTCPeerConnection;
public:
    _PeerConnection();
    virtual ~_PeerConnection();

	bool Init(const _RTCConfiguration* configuration = NULL, const _MediaConstraintsObj* constraints = NULL);
	bool IsInitialized() { return m_bInitialized; }

	bool CreateOffer(_RTCSessionDescriptionCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr, const _MediaConstraintsObj* constraints = NULL);
	bool CreateAnswer(_RTCSessionDescriptionCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr, const _MediaConstraintsObj* constraints = NULL);
	bool SetLocalDescription(const _SessionDescription* description, _VoidFunctionCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr);
	cpp11::shared_ptr<_SessionDescription> LocalDescription();
	bool SetRemoteDescription(const _SessionDescription* description, _VoidFunctionCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr);
	cpp11::shared_ptr<_SessionDescription> RemoteDescription();
	const char* SignalingState();
	bool UpdateIce(const _RTCConfiguration* configuration = NULL, const _MediaConstraintsObj* constraints = NULL);
	bool AddIceCandidate(const _RTCIceCandidate* candidate, _VoidFunctionCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr);
	const char* IceGatheringState();
	const char* IceConnectionState();
	cpp11::shared_ptr<_Sequence<_MediaStream> > GetLocalStreams();
	cpp11::shared_ptr<_Sequence<_MediaStream> > GetRemoteStreams();
	cpp11::shared_ptr<_MediaStream> GetStreamById(const char* streamId);
	bool AddStream(_MediaStream* stream, const _MediaConstraintsObj* constraints = NULL);
	bool RemoveStream(_MediaStream* stream);
	bool Close();
	bool GetStats(_MediaStreamTrackBase* selector = NULL, _RTCStatsCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr);
	cpp11::shared_ptr<_RTCDTMFSender> CreateDtmfSender(_MediaStreamTrack *track);
	cpp11::shared_ptr<_RTCDataChannel> CreateDataChannel(const char* label, cpp11::shared_ptr<_RTCDataChannelInit> dataChannelDict = nullPtr);

	// callbacks
	WE_INLINE void SetCallback_onnegotiationneeded(_onnegotiationneededCallback _onnegotiationneeded) { onnegotiationneeded = _onnegotiationneeded; }
	WE_INLINE void SetCallback_onicecandidate(_onicecandidateCallback _onicecandidate) { onicecandidate = _onicecandidate; }
	WE_INLINE void SetCallback_onsignalingstatechange(_onsignalingstatechangeCallback _onsignalingstatechange) { onsignalingstatechange = _onsignalingstatechange; }
	WE_INLINE void SetCallback_onaddstream(_onaddstreamCallback _onaddstream) { onaddstream = _onaddstream; }
	WE_INLINE void SetCallback_onremovestream(_onremovestreamCallback _onremovestream) { onremovestream = _onremovestream; }
	WE_INLINE void SetCallback_oniceconnectionstatechange(_oniceconnectionstatechangeCallback _oniceconnectionstatechange) { oniceconnectionstatechange = _oniceconnectionstatechange; }
	WE_INLINE void SetCallback_ondatachannel(_ondatachannelCallback _ondatachannel) { ondatachannel = _ondatachannel; }

private:
	bool DeInit();

private:
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	rtc::scoped_refptr<_RTCPeerConnection> m_peer_connection;
	cpp11::shared_ptr<_SessionDescription> m_sdp_local;
	cpp11::shared_ptr<_SessionDescription> m_sdp_remote;
	bool m_bInitialized;

	// callbacks
	_onnegotiationneededCallback onnegotiationneeded;
	_onicecandidateCallback onicecandidate;
	_onsignalingstatechangeCallback onsignalingstatechange;
	_onaddstreamCallback onaddstream;
	_onremovestreamCallback onremovestream;
	_oniceconnectionstatechangeCallback oniceconnectionstatechange;
	_ondatachannelCallback ondatachannel;

#if _MSC_VER
#pragma warning(pop)
#endif
};



#endif /* _WEBRTC_EVERYWHERE_COMMON_PEERCONNECTION_H_ */
