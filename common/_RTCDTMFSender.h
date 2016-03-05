/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#rtcdtmfsender
#ifndef _WEBRTC_EVERYWHERE_COMMON_RTCDTMFSENDER_H_
#define _WEBRTC_EVERYWHERE_COMMON_RTCDTMFSENDER_H_

#include "_Config.h"
#include "_Common.h"
#include "_MediaStreamTrack.h"

class WEBRTC_EVERYWHERE_API _RTCDTMFSender{
public:
	_RTCDTMFSender(DtmfSenderInterfacePtr sender);
	virtual ~_RTCDTMFSender();

	bool canInsertDTMF(); // readonly    attribute boolean canInsertDTMF;
	void insertDTMF(const char* tones, long duration = 100, long interToneGap = 50); // void insertDTMF(DOMString tones, optional long duration, optional long interToneGap);
	cpp11::shared_ptr<_MediaStreamTrack> track(); // readonly attribute MediaStreamTrack track;
	void ontonechangeSet(_ontonechangeCallback ontonechange);// attribute EventHandler ontonechange;
	const char* toneBuffer(); // readonly    attribute DOMString        toneBuffer;
	long duration(); // readonly attribute long duration;
	long interToneGap(); // readonly attribute long interToneGap;

private:
	void OnToneChange(cpp11::shared_ptr<_RTCDTMFToneChangeEvent> e);

private:
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	_ontonechangeCallback m_ontonechange;
	rtc::scoped_refptr<webrtc::DtmfSenderInterface> m_sender;
	std::string m_tones;
#if _MSC_VER
#pragma warning(pop)
#endif
};

#endif /* _WEBRTC_EVERYWHERE_COMMON_RTCDTMFSENDER_H_ */
