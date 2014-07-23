/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/mediacapture-streams/#idl-def-MediaStreamConstraints
#ifndef _WEBRTC_EVERYWHERE_COMMON_MEDIASTREAMCONSTRAINTS_H_
#define _WEBRTC_EVERYWHERE_COMMON_MEDIASTREAMCONSTRAINTS_H_

#include "_Config.h"
#include "_Common.h"
#include "_MediaTrackConstraints.h"

#include <map>

class _Buffer;

class WEBRTC_EVERYWHERE_API _MediaStreamConstraints
{
public:
	_MediaStreamConstraints(cpp11::shared_ptr<_MediaTrackConstraints> audio = nullPtr, cpp11::shared_ptr<_MediaTrackConstraints> video = nullPtr);
	virtual ~_MediaStreamConstraints();

	WE_INLINE cpp11::shared_ptr<_MediaTrackConstraints> audio() const { return m_audio; }
	WE_INLINE cpp11::shared_ptr<_MediaTrackConstraints> video() const { return m_video; }

private:
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	cpp11::shared_ptr<_MediaTrackConstraints> m_audio;
	cpp11::shared_ptr<_MediaTrackConstraints> m_video;
#if _MSC_VER
#pragma warning(pop)
#endif
};

#endif /* _WEBRTC_EVERYWHERE_COMMON_MEDIASTREAMCONSTRAINTS_H_ */
