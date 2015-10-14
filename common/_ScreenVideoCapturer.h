/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_COMMON_SCREENVIDEOCAPTURER_H_
#define _WEBRTC_EVERYWHERE_COMMON_SCREENVIDEOCAPTURER_H_

#include "_Config.h"

#include "talk/media/base/videocapturer.h"
#include "webrtc/modules/desktop_capture/window_capturer.h"

class _ScreenVideoCapturer;

class _ScreenVideoCapturerFactory : public cricket::ScreenCapturerFactory, public sigslot::has_slots < > {
public:
	_ScreenVideoCapturerFactory();

	virtual cricket::VideoCapturer* Create(const cricket::ScreencastId& window);

	_ScreenVideoCapturer* window_capturer();

	cricket::CaptureState capture_state();

	static bool GetWindowList(webrtc::WindowCapturer::WindowList* windows);

private:
	void OnWindowCapturerDestroyed(_ScreenVideoCapturer* capturer);
	void OnStateChange(cricket::VideoCapturer*, cricket::CaptureState state);

	_ScreenVideoCapturer* window_capturer_;
	cricket::CaptureState capture_state_;
};

#endif /* _WEBRTC_EVERYWHERE_COMMON_SCREENVIDEOCAPTURER_H_ */
