/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/mediacapture-streams/#mediastream
#include "_MediaStream.h"
#include "_MediaStreamTrack.h"
#include "_Common.h"
#include "_Utils.h"
#include "_Debug.h"

#include "talk/app/webrtc/mediastreaminterface.h"
#include "talk/base/scoped_ptr.h"
#include "talk/base/logging.h"

#if WE_UNDER_WINDOWS
#	include <Windows.h>
#endif

#define RETURN_IF_NOT_VALID() if (!IsValid()) return;

_MediaStreamAllocateFn _MediaStream::s_Allocator = _MediaStream::AllocateDefault;

_MediaStream::_MediaStream(MediaStreamInterfacePtr _stream /*= NULL*/)
{
	m_stream = dynamic_cast<webrtc::MediaStreamInterface*>((webrtc::MediaStreamInterface*)_stream);
	if (!m_stream) {
		talk_base::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory = GetPeerConnectionFactory();
		if (peer_connection_factory) {
			static long __id = 1;
			std::string _id = _Utils::ToString(we_atomic_inc(&__id));
			m_stream = peer_connection_factory->CreateLocalMediaStream(_id);			
		}
	}
	if (!m_stream) {
		WE_DEBUG_ERROR("Failed to create stream");
	}
	else {
		m_id = m_stream->label();
	}
}

_MediaStream::~_MediaStream()
{
	m_stream = NULL;
	WE_DEBUG_INFO("_MediaStream::~_MediaStream");
}

_MediaStream* _MediaStream::AllocateDefault()
{
	return new _MediaStream();
}

cpp11::shared_ptr<_Sequence<_MediaStreamTrack> > _MediaStream::getAudioTracks()
{
	cpp11::shared_ptr<_Sequence<_MediaStreamTrack> > seq(new _Sequence<_MediaStreamTrack>());

	if (IsValid()) {
		webrtc::AudioTrackVector tracks = m_stream->GetAudioTracks();		
		for (size_t i = 0; i < tracks.size(); ++i){
			if (tracks[i]) {
				seq->Add(cpp11::shared_ptr<_MediaStreamTrackAudio>(new _MediaStreamTrackAudio(tracks[i])));
			}
		}
	}

	return seq;
}

cpp11::shared_ptr<_Sequence<_MediaStreamTrack> > _MediaStream::getVideoTracks()
{
	cpp11::shared_ptr<_Sequence<_MediaStreamTrack> > seq(new _Sequence<_MediaStreamTrack>());

	if (IsValid()) {
		webrtc::VideoTrackVector tracks = m_stream->GetVideoTracks();
		for (size_t i = 0; i < tracks.size(); ++i){
			if (tracks[i]) {
				seq->Add(cpp11::shared_ptr<_MediaStreamTrackVideo>(new _MediaStreamTrackVideo(tracks[i])));
			}
		}
	}

	return seq;
}

// void addTrack (MediaStreamTrack track); 
// http://www.w3.org/TR/mediacapture-streams/#widl-MediaStream-addTrack-void-MediaStreamTrack-track
void _MediaStream::addTrack(_MediaStreamTrack* p_track)
{
	RETURN_IF_NOT_VALID();
	if (!p_track) {
		WE_DEBUG_ERROR("Invalid parameter");
		return;
	}
	
	_MediaStreamTrackBase *_pTrack = dynamic_cast<_MediaStreamTrackBase*>(p_track);
	bool added = false;
	if (_pTrack) {
		switch (p_track->type())
		{
		case _MediaStreamTrackTypeAudio:
			{
				added = m_stream->AddTrack(dynamic_cast<_MediaStreamTrackAudio*>(_pTrack)->track());
				break;
			}		
		case _MediaStreamTrackTypeVideo:
			{
				added = m_stream->AddTrack(dynamic_cast<_MediaStreamTrackVideo*>(_pTrack)->track());
				break;
			}
		default:
			WE_DEBUG_ERROR("%d not valid stream track type", p_track->type());
			break;
		}
	}
	else {
		WE_DEBUG_ERROR("Invalid stream track");
	}

	if (added && m_onaddtrack) {
		m_onaddtrack();
	}
}

// void removeTrack (MediaStreamTrack track);
// http://www.w3.org/TR/mediacapture-streams/#widl-MediaStream-removeTrack-void-MediaStreamTrack-track
void _MediaStream::removeTrack(_MediaStreamTrack* p_track)
{
	RETURN_IF_NOT_VALID();
	if (!p_track) {
		WE_DEBUG_ERROR("Invalid parameter");
		return;
	}

	_MediaStreamTrackBase *_pTrack = dynamic_cast<_MediaStreamTrackBase*>(p_track);
	bool removed = false;
	if (_pTrack) {
		switch (p_track->type())
		{
		case _MediaStreamTrackTypeAudio:
			removed = m_stream->RemoveTrack(dynamic_cast<_MediaStreamTrackAudio*>(_pTrack)->track());
			break;
		case _MediaStreamTrackTypeVideo:
			removed = m_stream->RemoveTrack(dynamic_cast<_MediaStreamTrackVideo*>(_pTrack)->track());
			break;
		default:
			WE_DEBUG_ERROR("%d not valid stream track type", p_track->type());
			break;
		}
	}
	else {
		WE_DEBUG_ERROR("Invalid stream track");
	}

	if (removed && m_onremovetrack) {
		m_onremovetrack();
	}
}

cpp11::shared_ptr<_MediaStreamTrack> _MediaStream::getTrackById(const char* trackId)
{
	cpp11::shared_ptr<_MediaStreamTrack> track = nullPtr;
	if (trackId && IsValid()) {
		talk_base::scoped_refptr<webrtc::AudioTrackInterface> track_audio = m_stream->FindAudioTrack(std::string(trackId));
		if (track_audio.get()) {
            track = cpp11::shared_ptr<_MediaStreamTrackAudio>(new _MediaStreamTrackAudio(track_audio));
		}
		else {
			talk_base::scoped_refptr<webrtc::VideoTrackInterface> track_video = m_stream->FindVideoTrack(std::string(trackId));
			if (track_video.get()) {
				track = cpp11::shared_ptr<_MediaStreamTrackVideo>(new _MediaStreamTrackVideo(track_video));
			}
		}
	}

	return track;
}

cpp11::shared_ptr<_MediaStream> _MediaStream::clone()
{
	// http://www.w3.org/TR/mediacapture-streams/#widl-MediaStream-clone-MediaStream
	cpp11::shared_ptr<_MediaStream> _clone = nullPtr;
	if (IsValid()) {
		_clone = cpp11::shared_ptr<_MediaStream>(new _MediaStream());
		if (_clone && _clone->IsValid()) {
			// audio
			cpp11::shared_ptr<_Sequence<_MediaStreamTrack> > audioTracks = getAudioTracks();
			if (audioTracks) {
				for (size_t i = 0; i < audioTracks->values.size(); ++i) {
					if (audioTracks->values[i].get()) {
						_clone->addTrack(audioTracks->values[i].get());
					}
				}
			}
			// video
			cpp11::shared_ptr<_Sequence<_MediaStreamTrack> > videoTracks = getVideoTracks();
			if (videoTracks) {
				for (size_t i = 0; i < videoTracks->values.size(); ++i) {
					if (videoTracks->values[i].get()) {
						_clone->addTrack(videoTracks->values[i].get());
					}
				}
			}
		}
	}
	return _clone;
}

bool _MediaStream::ended()
{
	if (IsValid()) {
		return m_stream == NULL;
	}
	return true;
}

void _MediaStream::stop()
{
	cpp11::shared_ptr<_Sequence<_MediaStreamTrack> > _tracks[] = { getAudioTracks(), getVideoTracks() };
	for (size_t i = 0; i < sizeof(_tracks) / sizeof(_tracks[0]); ++i) {
		if (_tracks[i]){
			for (size_t j = 0; j < _tracks[i]->values.size(); ++j) {
				if (_tracks[i]->values[j]){
					removeTrack(_tracks[i]->values[j].get());
				}
			}
		}
	}
}

VideoTrackInterfacePtr _MediaStream::GetVideoTrack(int index /*= 0*/)const
{
	if (m_stream && index >= 0 && index < (int)m_stream->GetVideoTracks().size()) {
		return m_stream->GetVideoTracks().at(index);
	}
	return NULL;
}