/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "_PeerConnection.h"
#include "_Buffer.h"
#include "_SessionDescription.h"
#include "_MediaStream.h"
#include "_MediaStreamTrack.h"
#include "_MediaTrackConstraints.h"
#include "_MediaStreamConstraints.h"
#include "_RTCIceCandidate.h"
#include "_RTCDTMFSender.h"
#include "_RTCDataChannel.h"
#include "_utils.h"
#include "_Common.h"
#include "_Logging.h"
#include "_Debug.h"

#include "talk/app/webrtc/mediaconstraintsinterface.h"
#include "webrtc/base/thread.h"
#include "webrtc/base/json.h"
#include "webrtc/base/logging.h"

// http://www.w3.org/TR/webrtc/#interface-definition

//
//	DummySetSessionDescriptionObserver
//
class DummySetSessionDescriptionObserver
	: public webrtc::SetSessionDescriptionObserver {
public:
	static DummySetSessionDescriptionObserver* Create(_VoidFunctionCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr) {
		return
			new rtc::RefCountedObject<DummySetSessionDescriptionObserver>(successCallback, failureCallback);
	}
	virtual void OnSuccess() {
		LOG(INFO) << __FUNCTION__;
		if (m_successCallback) {
			m_successCallback();
		}
	}
	virtual void OnFailure(const std::string& error) {
		LOG(INFO) << __FUNCTION__ << " " << error;
		cpp11::shared_ptr<std::string> err(new std::string(error));
		if (m_failureCallback) {
			m_failureCallback(err);
		}
	}

protected:
	DummySetSessionDescriptionObserver(_VoidFunctionCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr) : m_successCallback(successCallback), m_failureCallback(failureCallback){}
	~DummySetSessionDescriptionObserver() 
	{
		WE_DEBUG_INFO("~DummySetSessionDescriptionObserver");
	}
private:
	_VoidFunctionCallback m_successCallback;
	_RTCPeerConnectionErrorCallback m_failureCallback;
};

//
//	DummyCreateSessionDescriptionObserver
//
class DummyCreateSessionDescriptionObserver
	: public webrtc::CreateSessionDescriptionObserver {
public:
	static DummyCreateSessionDescriptionObserver* Create(const _RTCPeerConnection* pc, _RTCSessionDescriptionCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr) {
		return
			new rtc::RefCountedObject<DummyCreateSessionDescriptionObserver>(pc, successCallback, failureCallback);
	}
	virtual void OnSuccess(webrtc::SessionDescriptionInterface* desc) {
		LOG(INFO) << __FUNCTION__;
		if (m_pc) {
#if 0
			const_cast<_RTCPeerConnection*>(m_pc)->setLocalDescription(desc);
#endif
		}
		if (m_successCallback) {
			std::string sdp;
			desc->ToString(&sdp);
            cpp11::shared_ptr<_SessionDescription>_sdp(new _SessionDescription((const void*)sdp.c_str(), sdp.length(), (const void*)desc->type().c_str(), desc->type().length()));
			m_successCallback(_sdp);
		}
	}
	virtual void OnFailure(const std::string& error) {
		LOG(INFO) << __FUNCTION__ << " " << error;
		cpp11::shared_ptr<std::string> err(new std::string(error));
		if (m_failureCallback) {
			m_failureCallback(err);
		}
	}

protected:
	DummyCreateSessionDescriptionObserver(const _RTCPeerConnection* pc, _RTCSessionDescriptionCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr)
		: m_pc(pc)
		, m_successCallback(successCallback)
		, m_failureCallback(failureCallback){}
	virtual ~DummyCreateSessionDescriptionObserver()
	{
		WE_DEBUG_INFO("~DummyCreateSessionDescriptionObserver");
	}
private:
	const _RTCPeerConnection* m_pc;
	_RTCSessionDescriptionCallback m_successCallback;
	_RTCPeerConnectionErrorCallback m_failureCallback;
};


//
//	DummyStatsObserver
//
class DummyStatsObserver
	: public webrtc::StatsObserver {
public:
	static DummyStatsObserver* Create(_RTCStatsCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr) {
		return
			new rtc::RefCountedObject<DummyStatsObserver>(successCallback, failureCallback);
	}
	virtual void OnComplete(const webrtc::StatsReports& reports) {
		LOG(INFO) << __FUNCTION__;
		if (m_successCallback) {
			cpp11::shared_ptr<_RTCStatsReport> _report(new _RTCStatsReport());
			if (_report) {
				for (size_t i = 0; i < reports.size(); ++i) {
					cpp11::shared_ptr<_RTCStats> stats(new _RTCStats());
					if (stats) {
						stats->id = std::string(reports[i]->id()->ToString());
						stats->type = std::string(reports[i]->TypeToString());
						stats->timestamp = reports[i]->timestamp();
						for (std::map<webrtc::StatsReport::StatsValueName, webrtc::StatsReport::ValuePtr>::const_iterator iter
							= reports[i]->values().begin(); iter != reports[i]->values().end(); ++iter) {
							stats->names.insert(std::pair<std::string, std::string>(iter->second->display_name(), iter->second->ToString()));
						}
						_report->values.insert(std::pair<std::string, cpp11::shared_ptr<_RTCStats> >(stats->id, stats));
					}
				}
				m_successCallback(_report);
			}
		}
	}
protected:
	DummyStatsObserver(_RTCStatsCallback successCallback = nullPtr, _RTCPeerConnectionErrorCallback failureCallback = nullPtr) {
		m_successCallback = successCallback;
		m_failureCallback = failureCallback;
	}
	~DummyStatsObserver() {
		WE_DEBUG_INFO("~DummyStatsObserver");
	}
private:
	_RTCStatsCallback m_successCallback;
	_RTCPeerConnectionErrorCallback m_failureCallback;
};

//
//	_RTCPeerConnection
//

_RTCPeerConnection::_RTCPeerConnection(const _PeerConnection* pcBase, const webrtc::PeerConnectionInterface::RTCConfiguration& configuration, const webrtc::MediaConstraintsInterface* constraints /*= NULL*/)
	: m_bValid(false)
	, m_pcBase(pcBase)
{
	WE_LOG_FUNCTION_CALL();
	m_peer_connection_factory = GetPeerConnectionFactory();
	if (!m_peer_connection_factory.get()) {
		WE_DEBUG_ERROR("Failed to create factory");
		return;
	}

	m_peer_connection = m_peer_connection_factory->CreatePeerConnection(
		configuration,
		constraints,
		GetPortAllocatorFactory(),
		NULL,
		this);
	if (!m_peer_connection.get()) {
		WE_DEBUG_ERROR("Failed to create peer connection");
		return;
	}

	m_bValid = true;
}

bool _RTCPeerConnection::createOffer(_RTCSessionDescriptionCallback successCallback /*= nullPtr*/, _RTCPeerConnectionErrorCallback failureCallback /*= nullPtr*/, const webrtc::MediaConstraintsInterface* constraints /*= NULL*/)
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		m_peer_connection->CreateOffer(DummyCreateSessionDescriptionObserver::Create(this, successCallback, failureCallback), constraints);
		return true;
	}
	return false;
}

bool _RTCPeerConnection::createAnswer(_RTCSessionDescriptionCallback successCallback /*= nullPtr*/, _RTCPeerConnectionErrorCallback failureCallback /*= nullPtr*/, const webrtc::MediaConstraintsInterface* constraints /*= NULL*/)
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		m_peer_connection->CreateAnswer(DummyCreateSessionDescriptionObserver::Create(this, successCallback, failureCallback), constraints);
		return true;
	}
	return false;
}

bool _RTCPeerConnection::setLocalDescription(webrtc::SessionDescriptionInterface* description, _VoidFunctionCallback successCallback /*= nullPtr*/, _RTCPeerConnectionErrorCallback failureCallback /*= nullPtr*/)
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		m_peer_connection->SetLocalDescription(DummySetSessionDescriptionObserver::Create(successCallback, failureCallback), description);
		return true;
	}
	return false;
}

const webrtc::SessionDescriptionInterface* _RTCPeerConnection::localDescription()
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		return m_peer_connection->local_description();
	}
	return NULL;
}

bool _RTCPeerConnection::setRemoteDescription(webrtc::SessionDescriptionInterface* description, _VoidFunctionCallback successCallback /*= nullPtr*/, _RTCPeerConnectionErrorCallback failureCallback /*= nullPtr*/)
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		m_peer_connection->SetRemoteDescription(DummySetSessionDescriptionObserver::Create(successCallback, failureCallback), description);
		return true;
	}
	return false;
}

const webrtc::SessionDescriptionInterface* _RTCPeerConnection::remoteDescription()
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		return m_peer_connection->remote_description();
	}
	return NULL;
}

const char* _RTCPeerConnection::signalingState()
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		switch (m_peer_connection->signaling_state()) {
		case webrtc::PeerConnectionInterface::kStable : return kSignalingStateStable;
		case webrtc::PeerConnectionInterface::kHaveLocalOffer:return kSignalingStateHaveLocalOffer;
		case webrtc::PeerConnectionInterface::kHaveLocalPrAnswer: return kSignalingStateHaveLocalPrAnswer;
		case webrtc::PeerConnectionInterface::kHaveRemoteOffer: return kSignalingStateHaveRemoteOffer;
		case webrtc::PeerConnectionInterface::kHaveRemotePrAnswer: return kSignalingStateHaveRemotePrAnswer;
		case webrtc::PeerConnectionInterface::kClosed: return kSignalingStateClosed;
		}
	}
	return kSignalingStateClosed;
}

bool _RTCPeerConnection::updateIce(const webrtc::PeerConnectionInterface::RTCConfiguration& configuration, const webrtc::MediaConstraintsInterface* constraints /*= NULL*/)
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		return m_peer_connection->UpdateIce(configuration.servers, constraints);
	}
	return false;
}

bool _RTCPeerConnection::addIceCandidate(const webrtc::IceCandidateInterface* candidate, _VoidFunctionCallback successCallback /*= nullPtr*/, _RTCPeerConnectionErrorCallback failureCallback /*= nullPtr*/)
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		bool ret = m_peer_connection->AddIceCandidate(candidate);
		if (ret) {
			if (successCallback) {
				successCallback();
			}
		}
		else {
			if (failureCallback) {
				failureCallback(cpp11::shared_ptr<std::string>(new std::string("Internal error")));
			}
		}
		return ret;
	}
	if (failureCallback) {
		failureCallback(cpp11::shared_ptr<std::string>(new std::string("Peer connection not initialized yet")));
	}
	return false;
}

const char* _RTCPeerConnection::iceGatheringState()
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		switch (m_peer_connection->ice_gathering_state()) {
		case webrtc::PeerConnectionInterface::kIceGatheringNew: return kIceGatheringStateNew;
		case webrtc::PeerConnectionInterface::kIceGatheringGathering: return kIceGatheringStateGathering;
		case webrtc::PeerConnectionInterface::kIceGatheringComplete:return kIceGatheringStateComplete;
		}
	}
	return kIceGatheringStateNew;
}

const char* _RTCPeerConnection::iceConnectionState()
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		switch (m_peer_connection->ice_connection_state()) {
		case webrtc::PeerConnectionInterface::kIceConnectionNew: return kIceConnectionStateNew;
		case webrtc::PeerConnectionInterface::kIceConnectionChecking: return kIceConnectionStatChecking;
		case webrtc::PeerConnectionInterface::kIceConnectionConnected: return kIceConnectionStatConnected;
		case webrtc::PeerConnectionInterface::kIceConnectionCompleted: return kIceConnectionStatCompleted;
		case webrtc::PeerConnectionInterface::kIceConnectionFailed: return kIceConnectionStatFailed;
		case webrtc::PeerConnectionInterface::kIceConnectionDisconnected: return kIceConnectionStatDisconnected;
		case webrtc::PeerConnectionInterface::kIceConnectionClosed: return kIceConnectionStatClosed;
		}
	}
	return kIceConnectionStateNew;
}

rtc::scoped_refptr<webrtc::StreamCollectionInterface> _RTCPeerConnection::getLocalStreams()
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		return m_peer_connection->local_streams();
	}
	return NULL;
}

rtc::scoped_refptr<webrtc::StreamCollectionInterface> _RTCPeerConnection::getRemoteStreams()
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		return m_peer_connection->remote_streams();
	}
	return NULL;
}

webrtc::MediaStreamInterface* _RTCPeerConnection::getStreamById(std::string streamId)
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		webrtc::MediaStreamInterface* stream = NULL;
		rtc::scoped_refptr<webrtc::StreamCollectionInterface> streams;
		if ((streams = m_peer_connection->local_streams()) && (stream = streams->find(streamId))) {
			return stream;
		}
		if ((streams = m_peer_connection->remote_streams()) && (stream = streams->find(streamId))) {
			return stream;
		}
	}
	return NULL;
}

bool _RTCPeerConnection::addStream(webrtc::MediaStreamInterface* stream, const webrtc::MediaConstraintsInterface* constraints)
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
#if 0 // Was an bug in Google's code, "addStream" takes a single parameter
		return m_peer_connection->AddStream(stream, constraints);
#else
		return m_peer_connection->AddStream(stream);
#endif
	}
	return false;
}

bool _RTCPeerConnection::removeStream(webrtc::MediaStreamInterface* stream)
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		m_peer_connection->RemoveStream(stream);
		return true;
	}
	return false;
}

bool _RTCPeerConnection::close()
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		m_peer_connection->Close();
		return true;
	}
	return false;
}

bool _RTCPeerConnection::getStats(webrtc::MediaStreamTrackInterface* selector /*= NULL*/, _RTCStatsCallback successCallback /*= nullPtr*/, _RTCPeerConnectionErrorCallback failureCallback /*= nullPtr*/)
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid()) {
		return m_peer_connection->GetStats(DummyStatsObserver::Create(successCallback, failureCallback), selector, webrtc::PeerConnectionInterface::kStatsOutputLevelStandard);
	}
	return false;
}

cpp11::shared_ptr<_RTCDTMFSender> _RTCPeerConnection::createDTMFSender(webrtc::AudioTrackInterface *track)
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid() && track) {
		rtc::scoped_refptr<webrtc::DtmfSenderInterface> sender = m_peer_connection->CreateDtmfSender(track);
		if (sender) {
			cpp11::shared_ptr<_RTCDTMFSender>_sender(new _RTCDTMFSender(sender));
			return _sender;
		}
	}
	return nullPtr;
}

cpp11::shared_ptr<_RTCDataChannel> _RTCPeerConnection::CreateDataChannel(const std::string& label, const webrtc::DataChannelInit* config)
{
	WE_LOG_FUNCTION_CALL();
	if (IsValid() && config) {
		rtc::scoped_refptr<webrtc::DataChannelInterface> dataChannel = m_peer_connection->CreateDataChannel(label, config);
		if (dataChannel) {
			cpp11::shared_ptr<_RTCDataChannel>_dataChannel(new _RTCDataChannel(dataChannel));
			return _dataChannel;
		}
	}
	return nullPtr;
}

_RTCPeerConnection::~_RTCPeerConnection()
{
	WE_LOG_FUNCTION_CALL();
	m_peer_connection = NULL;
	m_peer_connection_factory = NULL;

	WE_DEBUG_INFO("_RTCPeerConnection::~_RTCPeerConnection");
}


//--- PeerConnectionObserver implementation ---//
void _RTCPeerConnection::OnError()
{
	WE_LOG_FUNCTION_CALL();
	WE_DEBUG_INFO("_RTCPeerConnection::OnError");
}

void _RTCPeerConnection::OnStateChange(webrtc::PeerConnectionObserver::StateType state_changed)
{
	WE_LOG_FUNCTION_CALL();
	WE_DEBUG_INFO("_RTCPeerConnection::OnStateChange");
	if (m_pcBase) {
		if (state_changed == kSignalingState && m_pcBase->onsignalingstatechange) {
			m_pcBase->onsignalingstatechange();
		}
		else if (state_changed == kIceState && m_pcBase->oniceconnectionstatechange) {
			m_pcBase->oniceconnectionstatechange();
		}
	}
}

void _RTCPeerConnection::OnAddStream(webrtc::MediaStreamInterface* stream)
{
	WE_LOG_FUNCTION_CALL();
	WE_DEBUG_INFO("_PeerConnection::OnAddStream");
	if (m_pcBase && m_pcBase->onaddstream && stream) {
        cpp11::shared_ptr<_MediaStreamEvent>_e (new _MediaStreamEvent(cpp11::shared_ptr<_MediaStream>(new _MediaStream(stream))));
		m_pcBase->onaddstream(_e);
	}
}

void _RTCPeerConnection::OnRemoveStream(webrtc::MediaStreamInterface* stream)
{
	WE_LOG_FUNCTION_CALL();
	WE_DEBUG_INFO("_RTCPeerConnection::OnRemoveStream");
	if (m_pcBase && m_pcBase->onremovestream && stream) {
        cpp11::shared_ptr<_MediaStreamEvent>_e (new _MediaStreamEvent(cpp11::shared_ptr<_MediaStream>(new _MediaStream(stream))));
		m_pcBase->onremovestream(_e);
	}
}

void _RTCPeerConnection::OnRenegotiationNeeded()
{
	WE_LOG_FUNCTION_CALL();
	WE_DEBUG_INFO("_RTCPeerConnection::OnRenegotiationNeeded");
	if (m_pcBase && m_pcBase->onnegotiationneeded) {
		m_pcBase->onnegotiationneeded();
	}
}

void _RTCPeerConnection::OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state)
{
	WE_LOG_FUNCTION_CALL();
	WE_DEBUG_INFO("_RTCPeerConnection::OnIceConnectionChange");
	if (m_pcBase && m_pcBase->oniceconnectionstatechange) {
		m_pcBase->oniceconnectionstatechange();
	}
}

void _RTCPeerConnection::OnIceCandidate(const webrtc::IceCandidateInterface* candidate)
{
	WE_LOG_FUNCTION_CALL();
	WE_DEBUG_INFO("_RTCPeerConnection::OnIceCandidate");

	if (m_pcBase && m_pcBase->onicecandidate) {
		if (candidate) {
			std::string _str;
			candidate->ToString(&_str);
			cpp11::shared_ptr<_RTCIceCandidate>_candidate(new _RTCIceCandidate(_str.c_str(), candidate->sdp_mid().c_str(), candidate->sdp_mline_index()));
            cpp11::shared_ptr<_RTCPeerConnectionIceEvent>_e(new _RTCPeerConnectionIceEvent(_candidate));
            m_pcBase->onicecandidate(_e);
		}
        else {
            cpp11::shared_ptr<_RTCPeerConnectionIceEvent>_e(nullPtr);
            m_pcBase->onicecandidate(_e);
        }
	}
}

void _RTCPeerConnection::OnIceComplete()
{
	WE_LOG_FUNCTION_CALL();
	WE_DEBUG_INFO("_RTCPeerConnection::OnIceComplete");
	OnIceCandidate(NULL); // null candidate used as a hack to signal end of ICe gathering
}

void _RTCPeerConnection::OnDataChannel(webrtc::DataChannelInterface* data_channel)
{
	WE_LOG_FUNCTION_CALL();
	WE_DEBUG_INFO("_RTCPeerConnection::OnDataChannel");
	if (m_pcBase && m_pcBase->ondatachannel) {
		cpp11::shared_ptr<_RTCDataChannel>dataChannel(new _RTCDataChannel(data_channel));
		if (dataChannel) {
			cpp11::shared_ptr<_RTCDataChannelEvent> e(new _RTCDataChannelEvent(dataChannel));
			m_pcBase->ondatachannel(e);
		}
	}
}


//
//	_PeerConnection
//

#define CHECK_INITIALIZED() \
	if (!IsInitialized()) { \
		WE_DEBUG_ERROR("Not initialized"); \
		return false; \
	}

_PeerConnection::_PeerConnection()
: m_bInitialized(false)
, m_peer_connection(NULL)
, m_sdp_local(nullPtr)
, m_sdp_remote(nullPtr)
{
	WE_LOG_FUNCTION_CALL();
	_Utils::Initialize();
}

_PeerConnection::~_PeerConnection()
{
	WE_LOG_FUNCTION_CALL();
	DeInit();

	m_sdp_local = nullPtr;
	m_sdp_remote = nullPtr;

	WE_DEBUG_INFO("_PeerConnection::~_PeerConnection");
}

// http://www.w3.org/TR/webrtc/#widl-ctor-RTCPeerConnection--RTCConfiguration-configuration-MediaConstraints-constraints
bool _PeerConnection::Init(const _RTCConfiguration* configuration /*= NULL*/, const _MediaConstraintsObj* constraints /*= NULL*/)
{
	WE_LOG_FUNCTION_CALL();
	if (IsInitialized()) {
		WE_DEBUG_INFO("Already initialized");
		return true;
	}

	webrtc::PeerConnectionInterface::RTCConfiguration _configuration/*(webrtc::PeerConnectionInterface::IceTransportsType::kAll)*/;
	webrtc::PeerConnectionInterface::IceServers servers;
	if (configuration) {
		for (size_t i = 0; i < configuration->iceServers.size(); ++i) {
			webrtc::PeerConnectionInterface::IceServer server;
			server.uri = configuration->iceServers[i].uri;
			server.password = configuration->iceServers[i].password;
			server.username = configuration->iceServers[i].username;
			_configuration.servers.push_back(server);
		}
	}

	rtc::scoped_refptr<_RTCMediaConstraints> _constraints = BuildConstraints(constraints);

	// DTLS is required, enable it unless the end-user decided to disable it
	std::string value;
	if (!_constraints->GetMandatory().FindFirst(webrtc::MediaConstraintsInterface::kEnableDtlsSrtp, &value)) {
		_constraints->AddMandatory(webrtc::MediaConstraintsInterface::kEnableDtlsSrtp, webrtc::MediaConstraintsInterface::kValueTrue);
	}

	m_peer_connection = new rtc::RefCountedObject<_RTCPeerConnection>(this, _configuration, _constraints);
	if (!m_peer_connection.get() || !m_peer_connection->IsValid()) {
		WE_DEBUG_ERROR("Failed to create peer connection");
		return false;
	}

	m_bInitialized = true;
	return true;
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-createOffer-void-RTCSessionDescriptionCallback-successCallback-RTCPeerConnectionErrorCallback-failureCallback-MediaConstraints-constraints
// void createOffer (RTCSessionDescriptionCallback successCallback, RTCPeerConnectionErrorCallback failureCallback, optional MediaConstraints constraints);
bool _PeerConnection::CreateOffer(_RTCSessionDescriptionCallback successCallback /*= nullPtr*/, _RTCPeerConnectionErrorCallback failureCallback /*= nullPtr*/, const _MediaConstraintsObj* constraints /*= NULL*/)
{
	WE_LOG_FUNCTION_CALL();
	CHECK_INITIALIZED();
	return m_peer_connection->createOffer(successCallback, failureCallback, BuildConstraints(constraints));
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-createAnswer-void-RTCSessionDescriptionCallback-successCallback-RTCPeerConnectionErrorCallback-failureCallback-MediaConstraints-constraints
// void createAnswer (RTCSessionDescriptionCallback successCallback, RTCPeerConnectionErrorCallback failureCallback, optional MediaConstraints constraints)
bool _PeerConnection::CreateAnswer(_RTCSessionDescriptionCallback successCallback /*= nullPtr*/, _RTCPeerConnectionErrorCallback failureCallback /*= nullPtr*/, const _MediaConstraintsObj* constraints /*= NULL*/)
{
	WE_LOG_FUNCTION_CALL();
	CHECK_INITIALIZED();
	m_sdp_local = nullPtr;
	return m_peer_connection->createAnswer(successCallback, failureCallback, BuildConstraints(constraints));
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-setLocalDescription-void-RTCSessionDescription-description-VoidFunction-successCallback-RTCPeerConnectionErrorCallback-failureCallback
// void setLocalDescription (RTCSessionDescription description, VoidFunction successCallback, RTCPeerConnectionErrorCallback failureCallback);
bool _PeerConnection::SetLocalDescription(const _SessionDescription* description, _VoidFunctionCallback successCallback /*= nullPtr*/, _RTCPeerConnectionErrorCallback failureCallback /*= nullPtr*/)
{
	WE_LOG_FUNCTION_CALL();
	CHECK_INITIALIZED();
	if (!description) {
		WE_DEBUG_ERROR("Invalid argument");
		return false;
	}

	std::string type((const char*)description->getType()->getPtr(), description->getType()->getSize());
	std::string sdp((const char*)description->getSdp()->getPtr(), description->getSdp()->getSize());
	webrtc::SdpParseError err;
	webrtc::SessionDescriptionInterface* _description = webrtc::CreateSessionDescription(type, sdp, &err);
	if (!_description) {
		if (failureCallback) {
			failureCallback(cpp11::shared_ptr<std::string>(new std::string(err.description)));
			WE_DEBUG_ERROR("CreateSessionDescription eror: %s", err.description.c_str());
		}
		return false;
	}
	bool ret = m_peer_connection->setLocalDescription(_description, successCallback, failureCallback);
	if (ret) {
		m_sdp_local = nullPtr;
		_description = NULL; // now is owned by the peerconnection
	}
	if (_description) delete _description;
	return ret;
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-localDescription
// readonly    attribute RTCSessionDescription? localDescription;
cpp11::shared_ptr<_SessionDescription> _PeerConnection::LocalDescription()
{
	WE_LOG_FUNCTION_CALL();
	if (!IsInitialized()) {
		WE_DEBUG_ERROR("Not initialized");
		return nullPtr;
	}
	if (!m_sdp_local) {
		const webrtc::SessionDescriptionInterface* localDescription = m_peer_connection->localDescription();
		if (localDescription){
			std::string sdp;
			localDescription->ToString(&sdp);
			m_sdp_local = cpp11::shared_ptr<_SessionDescription>(new _SessionDescription(sdp.c_str(), sdp.length(), localDescription->type().c_str(), localDescription->type().length()));
		}
	}
	return m_sdp_local;
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-setRemoteDescription-void-RTCSessionDescription-description-VoidFunction-successCallback-RTCPeerConnectionErrorCallback-failureCallback
// void setRemoteDescription(RTCSessionDescription description, VoidFunction successCallback, RTCPeerConnectionErrorCallback failureCallback);
bool _PeerConnection::SetRemoteDescription(const _SessionDescription* description, _VoidFunctionCallback successCallback /*= nullPtr*/, _RTCPeerConnectionErrorCallback failureCallback /*= nullPtr*/)
{
	WE_LOG_FUNCTION_CALL();
	CHECK_INITIALIZED();
	if (!description) {
		WE_DEBUG_ERROR("Invalid argument");
		return false;
	}

	std::string type((const char*)description->getType()->getPtr(), description->getType()->getSize());
	std::string sdp((const char*)description->getSdp()->getPtr(), description->getSdp()->getSize());
	webrtc::SdpParseError err;
	webrtc::SessionDescriptionInterface* _description = webrtc::CreateSessionDescription(type, sdp, &err);
	if (!_description) {
		if (failureCallback) {
			failureCallback(cpp11::shared_ptr<std::string>(new std::string(err.description)));
			WE_DEBUG_ERROR("CreateSessionDescription eror: %s", err.description.c_str());
		}
		return false;
	}
	bool ret = m_peer_connection->setRemoteDescription(_description, successCallback, failureCallback);
	if (ret) {
		m_sdp_remote = nullPtr;
		_description = NULL; // now is owned by the peerconnection
	}
	if (_description) delete _description;
	return ret;
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-remoteDescription
// readonly attribute RTCSessionDescription? remoteDescription;
cpp11::shared_ptr<_SessionDescription> _PeerConnection::RemoteDescription()
{
	WE_LOG_FUNCTION_CALL();
	if (!IsInitialized()) {
		WE_DEBUG_ERROR("Not initialized");
		return nullPtr;
	}
	if (!m_sdp_remote) {
		const webrtc::SessionDescriptionInterface* remoteDescription = m_peer_connection->remoteDescription();
		if (remoteDescription){
			std::string sdp;
			remoteDescription->ToString(&sdp);
			m_sdp_remote = cpp11::shared_ptr<_SessionDescription>(new _SessionDescription(sdp.c_str(), sdp.length(), remoteDescription->type().c_str(), remoteDescription->type().length()));
		}
	}
	return m_sdp_remote;
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-signalingState
// readonly    attribute RTCSignalingState      signalingState;
const char* _PeerConnection::SignalingState()
{
	WE_LOG_FUNCTION_CALL();
	if (IsInitialized()) {
		return m_peer_connection->signalingState();
	}
	return kSignalingStateClosed;
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-updateIce-void-RTCConfiguration-configuration-MediaConstraints-constraints
// void updateIce (optional RTCConfiguration configuration, optional MediaConstraints constraints);
bool _PeerConnection::UpdateIce(const _RTCConfiguration* configuration /*= NULL*/, const _MediaConstraintsObj* constraints /*= NULL*/)
{
	WE_LOG_FUNCTION_CALL();
	CHECK_INITIALIZED();
	webrtc::PeerConnectionInterface::RTCConfiguration _configuration/*(webrtc::PeerConnectionInterface::IceTransportsType::kAll)*/;
	webrtc::PeerConnectionInterface::IceServers servers;
	if (configuration) {
		for (size_t i = 0; i < configuration->iceServers.size(); ++i) {
			webrtc::PeerConnectionInterface::IceServer server;
			server.uri = configuration->iceServers[i].uri;
			server.password = configuration->iceServers[i].password;
			server.username = configuration->iceServers[i].username;
			_configuration.servers.push_back(server);
		}
	}

	return m_peer_connection->updateIce(_configuration, BuildConstraints(constraints));
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-addIceCandidate-void-RTCIceCandidate-candidate-VoidFunction-successCallback-RTCPeerConnectionErrorCallback-failureCallback
// void addIceCandidate (RTCIceCandidate candidate, VoidFunction successCallback, RTCPeerConnectionErrorCallback failureCallback);
bool _PeerConnection::AddIceCandidate(const _RTCIceCandidate* candidate, _VoidFunctionCallback successCallback /*= nullPtr*/, _RTCPeerConnectionErrorCallback failureCallback /*= nullPtr*/)
{
	WE_LOG_FUNCTION_CALL();
	CHECK_INITIALIZED();
	if (!candidate) {
		WE_DEBUG_ERROR("Invalid argument");
		return false;
	}

	webrtc::SdpParseError error;
	webrtc::IceCandidateInterface* _candidate = webrtc::CreateIceCandidate(candidate->sdpMid(),
		candidate->sdpMLineIndex(),
		candidate->candidate(),
		&error);
	if (!_candidate) {
		if (failureCallback) {
			failureCallback(cpp11::shared_ptr<std::string>(new std::string(error.description)));
		}
		return false;
	}
	bool ret = m_peer_connection->addIceCandidate(_candidate, successCallback, failureCallback);
	if (!ret) {
		SafeDelete(&_candidate);
	}
	return ret;
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-iceGatheringState
// readonly attribute RTCIceGatheringState   iceGatheringState;
const char* _PeerConnection::IceGatheringState()
{
	WE_LOG_FUNCTION_CALL();
	if (!IsInitialized()) {
		return kIceGatheringStateNew;
	}
	return m_peer_connection->iceGatheringState();
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-iceConnectionState
// readonly attribute RTCIceConnectionState  iceConnectionState;
const char* _PeerConnection::IceConnectionState()
{
	WE_LOG_FUNCTION_CALL();
	if (!IsInitialized()) {
		return kIceConnectionStateNew;
	}
	return m_peer_connection->iceConnectionState();
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-getLocalStreams-sequence-MediaStream
// sequence<MediaStream> getLocalStreams();
cpp11::shared_ptr<_Sequence<_MediaStream> > _PeerConnection::GetLocalStreams()
{
	WE_LOG_FUNCTION_CALL();
	cpp11::shared_ptr<_Sequence<_MediaStream> > seq(new _Sequence<_MediaStream>());

	if (IsInitialized()) {
		rtc::scoped_refptr<webrtc::StreamCollectionInterface> _streams = m_peer_connection->getLocalStreams();
		if (_streams) {
			for (size_t i = 0; i < _streams->count(); ++i){
				webrtc::MediaStreamInterface* _stream = _streams->at(i);
				if (_stream) {
					seq->Add(cpp11::shared_ptr<_MediaStream>(new _MediaStream(_stream)));
				}
			}
		}
	}

	return seq;
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-getRemoteStreams-sequence-MediaStream
// sequence<MediaStream> getRemoteStreams();
cpp11::shared_ptr<_Sequence<_MediaStream> > _PeerConnection::GetRemoteStreams()
{
	WE_LOG_FUNCTION_CALL();
	cpp11::shared_ptr<_Sequence<_MediaStream> > seq(new _Sequence<_MediaStream>());

	if (IsInitialized()) {
		rtc::scoped_refptr<webrtc::StreamCollectionInterface> _streams = m_peer_connection->getRemoteStreams();
		if (_streams) {
			for (size_t i = 0; i < _streams->count(); ++i){
				webrtc::MediaStreamInterface* _stream = _streams->at(i);
				if (_stream) {
					seq->Add(cpp11::shared_ptr<_MediaStream>(new _MediaStream(_stream)));
				}
			}
		}
	}

	return seq;
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-getStreamById-MediaStream-DOMString-streamId
// MediaStream? getStreamById (DOMString streamId);
cpp11::shared_ptr<_MediaStream> _PeerConnection::GetStreamById(const char* streamId)
{
	WE_LOG_FUNCTION_CALL();
	if (IsInitialized() && streamId) {
		webrtc::MediaStreamInterface* stream = m_peer_connection->getStreamById(std::string(streamId));
		if (stream) {
			return cpp11::shared_ptr<_MediaStream>(new _MediaStream(stream));
		}
	}
	return nullPtr;
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-addStream-void-MediaStream-stream-MediaConstraints-constraints
// void addStream (MediaStream stream, optional MediaConstraints constraints);
bool _PeerConnection::AddStream(_MediaStream* stream, const _MediaConstraintsObj* constraints /*= NULL*/)
{
	WE_LOG_FUNCTION_CALL();
	CHECK_INITIALIZED();
	return m_peer_connection->addStream(BuildMediaStream(stream), BuildConstraints(constraints));
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-removeStream-void-MediaStream-stream
// void removeStream (MediaStream stream);
bool _PeerConnection::RemoveStream(_MediaStream* stream)
{
	WE_LOG_FUNCTION_CALL();
	CHECK_INITIALIZED();
	if (!stream) {
		WE_DEBUG_ERROR("Invalid argument");
		return false;
	}
	return m_peer_connection->removeStream(dynamic_cast<webrtc::MediaStreamInterface*>((webrtc::MediaStreamInterface*)stream->GetWrappedStream()));
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-close-void
// void close ();
bool _PeerConnection::Close()
{
	WE_LOG_FUNCTION_CALL();
	CHECK_INITIALIZED();
	return m_peer_connection->close();
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-getStats-void-MediaStreamTrack-selector-RTCStatsCallback-successCallback-RTCPeerConnectionErrorCallback-failureCallback
// void getStats (MediaStreamTrack? selector, RTCStatsCallback successCallback, RTCPeerConnectionErrorCallback failureCallback);

bool _PeerConnection::GetStats(_MediaStreamTrackBase* selector /*= NULL*/, _RTCStatsCallback successCallback /*= nullPtr*/, _RTCPeerConnectionErrorCallback failureCallback /*= nullPtr*/)
{
	WE_LOG_FUNCTION_CALL();
	CHECK_INITIALIZED();
	return m_peer_connection->getStats(selector ? selector->_track() : NULL, successCallback, failureCallback);
}

// http://www.w3.org/TR/webrtc/#rtcpeerconnection-interface-extensions-1
// RTCDTMFSender createDTMFSender (MediaStreamTrack track);
cpp11::shared_ptr<_RTCDTMFSender> _PeerConnection::CreateDtmfSender(_MediaStreamTrack *track)
{
	WE_LOG_FUNCTION_CALL();
	if (IsInitialized() && track && track->type() == _MediaStreamTrackTypeAudio) {
		return m_peer_connection->createDTMFSender(dynamic_cast<_MediaStreamTrackAudio*>(track)->track());
	}
	return nullPtr;
}

// http://www.w3.org/TR/webrtc/#widl-RTCPeerConnection-createDataChannel-RTCDataChannel-DOMString-label-RTCDataChannelInit-dataChannelDict
// RTCDataChannel createDataChannel ([TreatNullAs=EmptyString] DOMString label, optional RTCDataChannelInit dataChannelDict);
cpp11::shared_ptr<_RTCDataChannel> _PeerConnection::CreateDataChannel(const char* _label/*[TreatNullAs=EmptyString]*/, cpp11::shared_ptr<_RTCDataChannelInit> dataChannelDict /*= nullPtr*/)
{
	WE_LOG_FUNCTION_CALL();
	if (IsInitialized()) {
		std::string label(_label ? _label : "");
		webrtc::DataChannelInit config;
		if (dataChannelDict) {
			config.ordered = dataChannelDict->ordered;
			config.maxRetransmitTime = dataChannelDict->maxRetransmitTime;
			config.maxRetransmits = dataChannelDict->maxRetransmits;
			config.protocol = dataChannelDict->protocol;
			config.negotiated = dataChannelDict->negotiated;
			config.id = dataChannelDict->id;
		}
		cpp11::shared_ptr<_RTCDataChannel> dataChannel = m_peer_connection->CreateDataChannel(label, &config);
		return dataChannel;
	}
	return nullPtr;
}

bool _PeerConnection::DeInit()
{
	WE_LOG_FUNCTION_CALL();
	m_peer_connection = NULL;

	return true;
}

