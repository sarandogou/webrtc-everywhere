/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#include "_Common.h"
#include "_Utils.h"
#include "_MediaStream.h"

#include "webrtc/system_wrappers/interface/critical_section_wrapper.h"

#if !defined(PEERCONN_MODE)
#define PEERCONN_MODE 1
#endif

#if PEERCONN_MODE == 1
static talk_base::scoped_refptr<webrtc::PeerConnectionFactoryInterface> _fake_peer_connection = NULL; // TODO: "getUserMedia" fails if no PeerconnectionFactory instance exists. Why?
static webrtc::CriticalSectionWrapper* _fake_peer_connection_cs = webrtc::CriticalSectionWrapper::CreateCriticalSection();
#else
talk_base::scoped_refptr<webrtc::PeerConnectionFactoryInterface> _fake_peer_connection(webrtc::CreatePeerConnectionFactory());
#endif

WEBRTC_EVERYWHERE_API talk_base::scoped_refptr<webrtc::PeerConnectionFactoryInterface> GetPeerConnectionFactory()
{
#if PEERCONN_MODE == 1
	_fake_peer_connection_cs->Enter();
	talk_base::scoped_refptr<webrtc::PeerConnectionFactoryInterface> _peer = _fake_peer_connection;
	_fake_peer_connection_cs->Leave();
	return _peer;
#else
	return _fake_peer_connection;
#endif
}

WEBRTC_EVERYWHERE_API void TakeFakePeerConnectionFactory()
{
#if PEERCONN_MODE == 1
	_fake_peer_connection_cs->Enter();
	if (!_fake_peer_connection) {
		_fake_peer_connection = webrtc::CreatePeerConnectionFactory();
	}
	else {
		_fake_peer_connection->AddRef();
	}
	_fake_peer_connection_cs->Leave();
#endif
}

WEBRTC_EVERYWHERE_API void ReleaseFakePeerConnectionFactory()
{
#if PEERCONN_MODE == 1
	_fake_peer_connection_cs->Enter();
	if (_fake_peer_connection) {
		// hack because no function to retrieve the refCount value;
		webrtc::PeerConnectionFactoryInterface* tmp = _fake_peer_connection.get();
		tmp->AddRef();
		if (tmp->Release() == 1) {
			_fake_peer_connection = NULL;
		}
		else {
			_fake_peer_connection->Release();
		}
	}
	_fake_peer_connection_cs->Leave();
#endif
}

talk_base::scoped_refptr<_RTCMediaConstraints> BuildConstraints(const _MediaConstraintsObj* _constraints /*= NULL*/)
{
	talk_base::scoped_refptr<_RTCMediaConstraints> contraints = new talk_base::RefCountedObject<_RTCMediaConstraints>();

	_MediaConstraints::const_iterator it;

	if (_constraints) {
		if (_constraints->optional) {
			for (it = _constraints->optional->begin(); it != _constraints->optional->end(); ++it) {
				contraints->AddOptional(it->first, it->second);
			}
		}
		if (_constraints->mandatory) {
			for (it = _constraints->mandatory->begin(); it != _constraints->mandatory->end(); ++it) {
				contraints->AddMandatory(it->first, it->second);
			}
		}
	}

	return contraints;
}

webrtc::MediaStreamInterface* BuildMediaStream(const _MediaStream* stream)
{
	if (!stream) {
		return NULL;
	}
	return dynamic_cast<webrtc::MediaStreamInterface*>((webrtc::MediaStreamInterface*)stream->GetWrappedStream());
}

_UniqueObject::_UniqueObject()
: m_id(_Utils::UniqueId())
{
    _Utils::UniqueObjAdd(this);
}

_UniqueObject::~_UniqueObject()
{
    _Utils::UniqueObjRemove(this->UniqueId());
}



