/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/mediacapture-streams/#idl-def-MediaStreamConstraints
#include "_MediaStreamConstraints.h"
#include "_Logging.h"
#include "_Debug.h"

_MediaStreamConstraints::_MediaStreamConstraints(cpp11::shared_ptr<_MediaTrackConstraints> audio /*= nullPtr*/, cpp11::shared_ptr<_MediaTrackConstraints> video /*= nullPtr*/)
	: m_audio(audio)
	, m_video(video)
{
	WE_LOG_FUNCTION_CALL();
}

_MediaStreamConstraints::~_MediaStreamConstraints()
{
	WE_LOG_FUNCTION_CALL();
	m_audio = nullPtr;
	m_video = nullPtr;
}
