/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/mediacapture-streams/#mediastream
#ifndef _WEBRTC_EVERYWHERE_COMMON_MEDIASTREAM_H_
#define _WEBRTC_EVERYWHERE_COMMON_MEDIASTREAM_H_

#include "_Config.h"
#include "_Common.h"
#include "_MediaStreamTrack.h"

#include "talk/app/webrtc/mediastreaminterface.h"
#include "webrtc/base/scoped_ptr.h"

class _MediaStreamTrack;

class WEBRTC_EVERYWHERE_API _MediaStream
{
public:
	_MediaStream(MediaStreamInterfacePtr stream = NULL);
	virtual ~_MediaStream();

public:
	// readonly    attribute DOMString    id;
	const char* id() { return m_id.c_str(); }
	// sequence<MediaStreamTrack> getAudioTracks ();
	cpp11::shared_ptr<_Sequence<_MediaStreamTrack> > getAudioTracks();
	// sequence<MediaStreamTrack> getVideoTracks ();
	cpp11::shared_ptr<_Sequence<_MediaStreamTrack> > getVideoTracks();
	// http://www.w3.org/TR/mediacapture-streams/#widl-MediaStream-addTrack-void-MediaStreamTrack-track
	// void addTrack (MediaStreamTrack track); 
	void addTrack(_MediaStreamTrack* p_track);
	// http://www.w3.org/TR/mediacapture-streams/#widl-MediaStream-removeTrack-void-MediaStreamTrack-track
	// void removeTrack (MediaStreamTrack track);
	void removeTrack(_MediaStreamTrack* p_track);
	// MediaStreamTrack?          getTrackById (DOMString trackId);
	cpp11::shared_ptr<_MediaStreamTrack> getTrackById(const char* trackId);
	// MediaStream                clone ();
	cpp11::shared_ptr<_MediaStream> clone();
	// readonly    attribute boolean      ended;
	bool ended();
	// not part of the standard but implemented in Chrome
	void stop();

	void onendedSet(_VoidFunctionCallback onended) { m_onended = onended; } // attribute EventHandler onended;
	void onaddtrackSet(_VoidFunctionCallback onaddtrack) { m_onaddtrack = onaddtrack; } // attribute EventHandler onaddtrack;
	void onremovetrackSet(_VoidFunctionCallback onremovetrack) { m_onremovetrack = onremovetrack; } // attribute EventHandler onremovetrack;

	bool IsValid()const { return m_stream != NULL; }
	MediaStreamInterfacePtr GetWrappedStream()const { return m_stream; }
	VideoTrackInterfacePtr GetVideoTrack(int index = 0)const;
	static void SetAllocator(_MediaStreamAllocateFn allocator) { s_Allocator = allocator; }
	static _MediaStream* Allocate() { return s_Allocator ? s_Allocator() : NULL; }

private:
	static _MediaStream* AllocateDefault();

private:
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	std::string m_id;
	rtc::scoped_refptr<webrtc::MediaStreamInterface> m_stream;
	static _MediaStreamAllocateFn s_Allocator;
	_VoidFunctionCallback m_onended;
	_VoidFunctionCallback m_onaddtrack;
	_VoidFunctionCallback m_onremovetrack;
#if _MSC_VER
#pragma warning(pop)
#endif
};

#endif /* _WEBRTC_EVERYWHERE_COMMON_MEDIASTREAM_H_ */
