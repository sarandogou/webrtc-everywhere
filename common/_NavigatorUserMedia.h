/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/mediacapture-streams/#navigatorusermedia
#ifndef _WEBRTC_EVERYWHERE_COMMON_NAVIGATORUSERMEDIA_H_
#define _WEBRTC_EVERYWHERE_COMMON_NAVIGATORUSERMEDIA_H_

#include "_Config.h"
#include "_Common.h"

class _Buffer;
class _MediaStreamConstraints;

class WEBRTC_EVERYWHERE_API _NavigatorUserMedia
{
public:
	// void getUserMedia (MediaStreamConstraints? constraints, NavigatorUserMediaSuccessCallback successCallback, NavigatorUserMediaErrorCallback errorCallback);
	static void getUserMedia(const _MediaStreamConstraints* constraints = NULL, _NavigatorUserMediaSuccessCallback successCallback = nullPtr, _NavigatorUserMediaErrorCallback errorCallback = nullPtr);
};

#endif /* _WEBRTC_EVERYWHERE_COMMON_NAVIGATORUSERMEDIA_H_ */
