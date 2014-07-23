/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/mediacapture-streams/#idl-def-MediaStreamConstraints
#include "_MediaStreamConstraints.h"
#include "_Debug.h"

_MediaStreamConstraints::_MediaStreamConstraints(cpp11::shared_ptr<_MediaTrackConstraints> audio /*= nullPtr*/, cpp11::shared_ptr<_MediaTrackConstraints> video /*= nullPtr*/)
	: m_audio(audio)
	, m_video(video)
{
}

_MediaStreamConstraints::~_MediaStreamConstraints()
{
	m_audio = nullPtr;
	m_video = nullPtr;

	WE_DEBUG_INFO("_MediaStreamConstraints::~_MediaStreamConstraints");
}
