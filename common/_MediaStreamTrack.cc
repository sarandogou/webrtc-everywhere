/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/mediacapture-streams/#mediastreamtrack
#include "_MediaStreamTrack.h"
#include "_Common.h"
#include "_Utils.h"
#include "_Debug.h"

#include "talk/app/webrtc/videosourceinterface.h"
#include "talk/app/webrtc/mediastreaminterface.h"
#include "talk/app/webrtc/peerconnectioninterface.h"
#include "talk/media/devices/devicemanager.h"
#include "webrtc/base/scoped_ptr.h"
#include "webrtc/base/logging.h"

#if WE_UNDER_WINDOWS
#	include <Windows.h>
#endif

//
//	_MediaStreamTrack
//

_MediaStreamTrack::_MediaStreamTrack(_MediaStreamTrackType eType, MediaStreamTrackInterfacePtr track /*= NULL*/, const _MediaTrackConstraints* constrains /*= NULL*/)
	: m_eType(eType)
	, m_bRemote(!!track)
	, m_pConstraints(nullPtr)
{
	static long __label = 1;
	
	m_label = _Utils::ToString(we_atomic_inc(&__label));
}

_MediaStreamTrack::~_MediaStreamTrack()
{
	WE_DEBUG_INFO("_MediaStreamTrack::~_MediaStreamTrack");
}

cpp11::shared_ptr<_Sequence<_SourceInfo> > _MediaStreamTrack::getSourceInfos()
{
	cpp11::shared_ptr<_Sequence<_SourceInfo> > infos(new _Sequence<_SourceInfo>());
	cpp11::shared_ptr<_SourceInfo> info;

	rtc::scoped_ptr<cricket::DeviceManagerInterface> dev_manager(
		cricket::DeviceManagerFactory::Create());
	if (!dev_manager->Init()) {
		LOG(LS_ERROR) << "Can't create device manager";
		return infos;
	}

	// VideoCapture
	std::vector<cricket::Device> devs;
    std::string video("video");
	if (dev_manager->GetVideoCaptureDevices(&devs)) {
		std::vector<cricket::Device>::iterator dev_it = devs.begin();
		for (; dev_it != devs.end(); ++dev_it) {
			info = cpp11::shared_ptr<_SourceInfo>(new _SourceInfo(dev_it->id, video, dev_it->name));
			if (info.get()) {
				infos->Add(info);
			}
		}
	}
	else {
		LOG(LS_ERROR) << "Can't enumerate video devices";
	}
#if 0
	// AudioOut
	if (dev_manager->GetAudioOutputDevices(&devs)) {
		std::vector<cricket::Device>::iterator dev_it = devs.begin();
        std::string audio("audio");
		for (; dev_it != devs.end(); ++dev_it) {
			info = cpp11::shared_ptr<_SourceInfo>(new _SourceInfo(dev_it->id, audio, dev_it->name));
			if (info.get()) {
				infos->Add(info);
			}
		}
	}
	else {
		LOG(LS_ERROR) << "Can't enumerate audioOut devices";
	}
#endif

	// AudioIn
	if (dev_manager->GetAudioInputDevices(&devs)) {
		std::vector<cricket::Device>::iterator dev_it = devs.begin();
        std::string audio("audio");
		for (; dev_it != devs.end(); ++dev_it) {
			info = cpp11::shared_ptr<_SourceInfo>(new _SourceInfo(dev_it->id, audio, dev_it->name));
			if (info.get()) {
				infos->Add(info);
			}
		}
	}
	else {
		LOG(LS_ERROR) << "Can't enumerate audioIn devices";
		return infos;
	}	

	return infos;
}


//
//	_MediaStreamTrackBase
//

_MediaStreamTrackBase::_MediaStreamTrackBase(_MediaStreamTrackType eType, MediaStreamTrackInterfacePtr track /*= NULL*/, const _MediaTrackConstraints* constrains /*= NULL*/)
	: _MediaStreamTrack(eType, track, constrains)
{
}

_MediaStreamTrackBase::~_MediaStreamTrackBase()
{

}

void _MediaStreamTrackBase::InitLocalVarsToAvoidDanglingPointerIssue()
{
	if (_track()) {
		m_id = _track()->id();
		m_kind = _track()->kind();
	}
}

// "_MediaStreamTrack" interface implementation

bool _MediaStreamTrackBase::enabledSet(bool enabled)
{
	if (_track()) {
		return _track()->set_enabled(enabled);
	}
	return false;
}
bool _MediaStreamTrackBase::enabled()
{
	if (_track()) {
		return _track()->enabled();
	}
	return false;
}

bool _MediaStreamTrackBase::readonly()
{
	if (_track()) {
		return false;
	}
	return true;
}

const char* _MediaStreamTrackBase::readyState()
{
	if (_track()) {
		switch (_track()->state()) {
		case webrtc::MediaStreamTrackInterface::kEnded:
			return kMediaStreamTrackStateEnded;
		case webrtc::MediaStreamTrackInterface::kFailed:
			return kMediaStreamTrackStateFailed;
		case webrtc::MediaStreamTrackInterface::kInitializing:
			return kMediaStreamTrackStateNew;
		case webrtc::MediaStreamTrackInterface::kLive:
			return kMediaStreamTrackStateLive;
		}
	}
	return kMediaStreamTrackStateFailed;
}

cpp11::shared_ptr<_MediaSourceStates> _MediaStreamTrackBase::states()
{
	cpp11::shared_ptr<_MediaSourceStates> _states;

	// FIXME: not implemented yet
	WE_DEBUG_ERROR("Not implemented yet");

	return _states;
}

cpp11::shared_ptr<_AllCapabilities> _MediaStreamTrackBase::capabilities()
{
	cpp11::shared_ptr<_AllCapabilities> _capabilities;

	// FIXME: not implemented yet
	WE_DEBUG_ERROR("Not implemented yet");

	return _capabilities;
}

void _MediaStreamTrackBase::applyConstraints(const _MediaTrackConstraints* constrains)
{
	if (_track()) {
		
	}

	// http://www.w3.org/TR/mediacapture-streams/#widl-MediaStreamTrack-applyConstraints-void-MediaTrackConstraints-constraints
	// FIXME: not implemented yet
	WE_DEBUG_ERROR("Not implemented yet");
}

cpp11::shared_ptr<_MediaStreamTrack> _MediaStreamTrackBase::clone()
{
	// http://www.w3.org/TR/mediacapture-streams/#widl-MediaStreamTrack-clone-MediaStreamTrack
	// FIXME: not implemented yet
	WE_DEBUG_ERROR("Not implemented yet");

	return nullPtr;
}

void _MediaStreamTrackBase::stop()
{
	if (_track()) {
		
	}

	// http://www.w3.org/TR/mediacapture-streams/#widl-MediaStreamTrack-stop-void
	// FIXME: not implemented yet
	WE_DEBUG_ERROR("Not implemented yet");
}

//
//	_MediaStreamTrackAudio
//

_MediaStreamTrackAudio::_MediaStreamTrackAudio(rtc::scoped_refptr<webrtc::AudioTrackInterface> track /*= NULL*/, const _MediaTrackConstraints* constrains /*= NULL*/)
	: _MediaStreamTrackBase(_MediaStreamTrackTypeAudio, track, constrains)
	, m_track(track)
{
	if (!m_track) {
		rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory = GetPeerConnectionFactory();
		if (peer_connection_factory) {
			m_label += "_audio_track";
			__MediaConstraintsObj _constrainsObject(constrains ? constrains->optional() : nullPtr, constrains ? constrains->mandatory() : nullPtr);
			m_track = peer_connection_factory->CreateAudioTrack(m_label, peer_connection_factory->CreateAudioSource(BuildConstraints(&_constrainsObject)));
		}
	}
	InitLocalVarsToAvoidDanglingPointerIssue();
}

_MediaStreamTrackAudio::~_MediaStreamTrackAudio()
{
	m_track = NULL;

	WE_DEBUG_INFO("_MediaStreamTrackAudio::~_MediaStreamTrackAudio");
}

// "_MediaStreamTrack" interface implementation
bool _MediaStreamTrackAudio::muted()
{
	// TODO: no "muted()" function in "AudioTrackInterface"
	if (m_track) {
		return !enabled();
	}
	return true;
}

//
//	_MediaStreamTrackVideo
//
static cricket::VideoCapturer* OpenVideoCaptureDevice(std::string id);

_MediaStreamTrackVideo::_MediaStreamTrackVideo(rtc::scoped_refptr<webrtc::VideoTrackInterface> track /*= NULL*/, const _MediaTrackConstraints* constrains /*= NULL*/)
	: _MediaStreamTrackBase(_MediaStreamTrackTypeVideo, track, constrains)
	, m_track(track)
{
	if (!m_track) {
		rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory = GetPeerConnectionFactory();
		if (peer_connection_factory) {
			__MediaConstraintsObj _constrainsObject(constrains ? constrains->optional() : nullPtr, constrains ? constrains->mandatory() : nullPtr);
			rtc::scoped_refptr<_RTCMediaConstraints> _constrains = BuildConstraints(&_constrainsObject);
			std::string sourceId;
			if (_constrains) {
				if (!_constrains->GetMandatory().FindFirst("sourceId", &sourceId)) {
					_constrains->GetOptional().FindFirst("sourceId", &sourceId);
				}
			}
			cricket::VideoCapturer* capturer = OpenVideoCaptureDevice(sourceId);
			if (!capturer) {
				WE_DEBUG_ERROR("Failed to open video capture device");
				return;
			}
			m_label += "_video_track";
			m_track = peer_connection_factory->CreateVideoTrack(m_label, peer_connection_factory->CreateVideoSource(capturer, _constrains));
		}
	}
	InitLocalVarsToAvoidDanglingPointerIssue();
}


_MediaStreamTrackVideo:: ~_MediaStreamTrackVideo()
{
	m_track = NULL;

	WE_DEBUG_INFO("_MediaStreamTrackVideo::~_MediaStreamTrackVideo");
}

// ISSUE: https://groups.google.com/forum/#!topic/discuss-webrtc/RV6oKhY2qEM
#if WE_UNDER_APPLE
#include "mac/_webrtcvideocapturer.h"
#include "webrtc/modules/video_capture/include/video_capture_factory.h"
class _VideoCapturerFactory : public cricket::VideoDeviceCapturerFactory {
public:
    _VideoCapturerFactory() {}
    virtual ~_VideoCapturerFactory() {}
    
    cricket::VideoCapturer* Create(const cricket::Device& device) {
        cricket::WebRtcVideoCapturer* return_value = new cricket::WebRtcVideoCapturer();
        if (!return_value->Init(device)) {
            delete return_value;
            return NULL;
        }
        return return_value;
    }
};
#endif /* WE_UNDER_APPLE */

static cricket::VideoCapturer* OpenVideoCaptureDevice(std::string id) {
	rtc::scoped_ptr<cricket::DeviceManagerInterface> dev_manager(
		cricket::DeviceManagerFactory::Create());
	if (!dev_manager->Init()) {
		LOG(LS_ERROR) << "Can't create device manager";
		return NULL;
	}
    
    // ISSUE: https://groups.google.com/forum/#!topic/discuss-webrtc/RV6oKhY2qEM
#if WE_UNDER_APPLE
    cricket::DeviceManager* device_manager = static_cast<cricket::DeviceManager*>(dev_manager.get());
    device_manager->SetVideoDeviceCapturerFactory(new _VideoCapturerFactory());
#endif /* WE_UNDER_APPLE  */
    
	std::vector<cricket::Device> devs;
	if (!dev_manager->GetVideoCaptureDevices(&devs)) {
		LOG(LS_ERROR) << "Can't enumerate video devices";
		return NULL;
	}
	std::vector<cricket::Device>::iterator dev_it;
	cricket::VideoCapturer* capturer = NULL;

	if (!id.empty()) {
		for (dev_it = devs.begin(); dev_it != devs.end(); ++dev_it) {
			if ((*dev_it).id == id) {
				capturer = dev_manager->CreateVideoCapturer(*dev_it);
				if (capturer) {
					return capturer;
				}
			}
		}
	}
    
#if 0
    webrtc::VideoCaptureModule::DeviceInfo *info = webrtc::VideoCaptureFactory::CreateDeviceInfo(0);
    if (info) {
        // Find the desired camera, by name.
        // In the future, comparing IDs will be more robust.
        // TODO(juberti): Figure what's needed to allow this.
        int num_cams = info->NumberOfDevices();
        char vcm_id[256] = "";
        bool found = false;
        for (int index = 0; index < num_cams; ++index) {
            char vcm_name[256];
            if (info->GetDeviceName(index, vcm_name, ARRAY_SIZE(vcm_name),
                                    vcm_id, ARRAY_SIZE(vcm_id)) != -1) {
                if ((*devs.begin()).name == reinterpret_cast<char*>(vcm_name)) {
                    found = true;
                    break;
                }
            }
        }
        if (found) {
            //std::vector<VideoFormat> supported;
            int32_t num_caps = info->NumberOfCapabilities(vcm_id);
            for (int32_t i = 0; i < num_caps; ++i) {
                webrtc::VideoCaptureCapability cap;
                if (info->GetCapability(vcm_id, i, cap) != -1) {
                    printf("");
                }
            }
        }
    }
#endif

	for (dev_it = devs.begin(); dev_it != devs.end(); ++dev_it) {
		capturer = dev_manager->CreateVideoCapturer(*dev_it);
		if (capturer != NULL)
			break;
	}
	return capturer;
}
