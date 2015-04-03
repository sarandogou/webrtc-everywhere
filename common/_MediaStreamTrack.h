/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/mediacapture-streams/#mediastreamtrack
#ifndef _WEBRTC_EVERYWHERE_COMMON_MEDIASTREAMTRACK_H_
#define _WEBRTC_EVERYWHERE_COMMON_MEDIASTREAMTRACK_H_

#include "_Config.h"
#include "_MediaTrackConstraints.h"
#include "_Common.h"

#include "talk/app/webrtc/mediastreaminterface.h"

class _Buffer;
class _MediaTrackConstraints;

typedef enum __MediaStreamTrackType
{
	_MediaStreamTrackTypeUnknown,
	_MediaStreamTrackTypeAudio,
	_MediaStreamTrackTypeVideo
}
_MediaStreamTrackType;


//
//	_MediaStreamTrack
//
class WEBRTC_EVERYWHERE_API _MediaStreamTrack
{
protected:
	_MediaStreamTrack(_MediaStreamTrackType eType, MediaStreamTrackInterfacePtr track = NULL, const _MediaTrackConstraints* constrains = NULL);
public:
	virtual ~_MediaStreamTrack();
	WE_INLINE _MediaStreamTrackType type() { return m_eType; }
	WE_INLINE virtual bool IsValid() = 0;

	virtual const char* kind() { return m_kind.c_str(); }; // readonly attribute DOMString kind;
	virtual const char* id() { return m_id.c_str(); }; // readonly attribute DOMString id;
	virtual const char* label() { return m_label.c_str(); }; // readonly attribute DOMString id;
	virtual bool enabledSet(bool enabled) = 0; // attribute boolean enabled;
	virtual bool enabled() = 0; // attribute boolean enabled;
	virtual bool muted() = 0; // readonly attribute boolean muted;

	void onmuteSet(_VoidFunctionCallback onmute) { m_onmute = onmute; }; // attribute EventHandler onmute;
	void onunmuteSet(_VoidFunctionCallback onunmute) { m_onunmute = onunmute; }; // attribute EventHandler onunmute;

	virtual bool readonly() = 0; // readonly attribute boolean _readonly;
	virtual bool remote() { return  m_bRemote; } // readonly attribute boolean remote;
	virtual const char* readyState() = 0; // readonly attribute MediaStreamTrackState readyState;

	void onstartedSet(_VoidFunctionCallback onstarted) { m_onstarted = onstarted; } // attribute EventHandler onstarted;
	void onendedSet(_VoidFunctionCallback onended) { m_onended = onended; } // attribute EventHandler onended;

	static cpp11::shared_ptr<_Sequence<_SourceInfo> > getSourceInfos();// static sequence<SourceInfo> getSourceInfos ();
	cpp11::shared_ptr<_MediaTrackConstraints> constraints() { return m_pConstraints; } // MediaTrackConstraints? constraints ();

	virtual cpp11::shared_ptr<_MediaSourceStates> states() = 0; // MediaSourceStates states ();

	virtual cpp11::shared_ptr<_AllCapabilities> capabilities() = 0; // (AllVideoCapabilities or AllAudioCapabilities) capabilities ();
	virtual void applyConstraints(const _MediaTrackConstraints* constrains) = 0; // void applyConstraints(MediaTrackConstraints constraints);
	
	void onoverconstrainedSet(_VoidFunctionCallback onoverconstrained) { m_onoverconstrained = onoverconstrained; }; // attribute EventHandler onoverconstrained;

	virtual cpp11::shared_ptr<_MediaStreamTrack> clone() = 0; // MediaStreamTrack clone ();
	virtual void stop() = 0; // void stop ();
	

protected:
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	_MediaStreamTrackType m_eType;
	// loacl strings to avoid "dangling pointer" issue
	std::string m_label;
	std::string m_id;
	std::string m_kind;

	bool m_bRemote;
	cpp11::shared_ptr<_MediaTrackConstraints> m_pConstraints;

	_VoidFunctionCallback m_onmute;
	_VoidFunctionCallback m_onunmute;
	_VoidFunctionCallback m_onstarted;
	_VoidFunctionCallback m_onended;
	_VoidFunctionCallback m_onoverconstrained;
#if _MSC_VER
#pragma warning(pop)
#endif
};

//
//	_MediaStreamTrackBase
//
class _MediaStreamTrackBase : public _MediaStreamTrack
{
protected:
	_MediaStreamTrackBase(_MediaStreamTrackType eType, MediaStreamTrackInterfacePtr track = NULL, const _MediaTrackConstraints* constrains = NULL);
public:
	virtual ~_MediaStreamTrackBase();

	// "_MediaStreamTrack" interface implementation
	virtual bool enabledSet(bool enabled);
	virtual bool enabled();
	virtual bool muted() { return false; } // override in "_MediaStreamTrackAudio"
	virtual bool readonly();
	virtual const char* readyState();
	virtual cpp11::shared_ptr<_MediaSourceStates> states();
	virtual cpp11::shared_ptr<_AllCapabilities> capabilities();
	virtual void applyConstraints(const _MediaTrackConstraints* constrains);
	virtual cpp11::shared_ptr<_MediaStreamTrack> clone();
	virtual void stop();

public:
	virtual webrtc::MediaStreamTrackInterface* _track() = 0;

protected:
	void InitLocalVarsToAvoidDanglingPointerIssue();

protected:
	
};

//
//	_MediaStreamTrackAudio
//
class _MediaStreamTrackAudio
	: public _MediaStreamTrackBase
{
public:
	_MediaStreamTrackAudio(rtc::scoped_refptr<webrtc::AudioTrackInterface> track = NULL, const _MediaTrackConstraints* constrains = NULL);
	virtual ~_MediaStreamTrackAudio();

	WE_INLINE virtual bool IsValid() { return !!m_track; }
	virtual rtc::scoped_refptr<webrtc::AudioTrackInterface> track() { return m_track; };

	// _MediaStreamTrackBase Interface
	virtual webrtc::MediaStreamTrackInterface* _track() { return track(); }

	// "_MediaStreamTrack" interface implementation
	virtual bool muted();

private:
	rtc::scoped_refptr<webrtc::AudioTrackInterface> m_track;
};

//
//	_MediaStreamTrackVideo
//
class _MediaStreamTrackVideo
	: public _MediaStreamTrackBase
{
public:
	_MediaStreamTrackVideo(rtc::scoped_refptr<webrtc::VideoTrackInterface> track = NULL, const _MediaTrackConstraints* constrains = NULL);
	virtual ~_MediaStreamTrackVideo();

	WE_INLINE virtual bool IsValid() { return !!m_track; }
	virtual rtc::scoped_refptr<webrtc::VideoTrackInterface> track() { return m_track; };

	// _MediaStreamTrackBase Interface
	virtual webrtc::MediaStreamTrackInterface* _track() { return track(); }

private:
	rtc::scoped_refptr<webrtc::VideoTrackInterface> m_track;
};

#endif /* _WEBRTC_EVERYWHERE_COMMON_MEDIASTREAMTRACK_H_ */
