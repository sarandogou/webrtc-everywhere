/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#rtcdtmfsender
#include "_RTCDTMFSender.h"
#include "_MediaStreamTrack.h"

//
//	DummySetSessionDescriptionObserver
//
class DummyDtmfSenderObserver
	: public webrtc::DtmfSenderObserverInterface {
public:
	static DummyDtmfSenderObserver* Create(_ontonechangeCallback ontonechange = nullPtr) {
		return
			new rtc::RefCountedObject<DummyDtmfSenderObserver>(ontonechange);
	}
	virtual void OnToneChange(const std::string& tone) {
		if (m_ontonechange) {
			cpp11::shared_ptr<_RTCDTMFToneChangeEvent> e(new _RTCDTMFToneChangeEvent(tone));
			m_ontonechange(e);
		}
	}
	DummyDtmfSenderObserver(_ontonechangeCallback ontonechange) : m_ontonechange(ontonechange) {}
	virtual ~DummyDtmfSenderObserver() {}
private:
	_ontonechangeCallback m_ontonechange;
};

//
//	_RTCDTMFSender
//
_RTCDTMFSender::_RTCDTMFSender(DtmfSenderInterfacePtr sender)
{
	assert(sender);
	m_sender = static_cast<webrtc::DtmfSenderInterface*>(sender);
	m_sender->RegisterObserver(DummyDtmfSenderObserver::Create(cpp11::bind(&_RTCDTMFSender::OnToneChange, this, cpp11::placeholders::_1)));
}

_RTCDTMFSender::~_RTCDTMFSender()
{
	m_sender->UnregisterObserver();
	m_sender = NULL;
}

void _RTCDTMFSender::OnToneChange(cpp11::shared_ptr<_RTCDTMFToneChangeEvent> e)
{
	if (m_ontonechange) {
		m_ontonechange(e);
	}
}

bool _RTCDTMFSender::canInsertDTMF()
{
	return m_sender->CanInsertDtmf();
}

void _RTCDTMFSender::insertDTMF(const char* tones, long duration /*= 100*/, long interToneGap /*= 50*/)
{
	m_sender->InsertDtmf(std::string(tones), (int)duration, (int)interToneGap);
}

cpp11::shared_ptr<_MediaStreamTrack> _RTCDTMFSender::track()
{
	const webrtc::AudioTrackInterface* _audioTrack = m_sender->track();
	if (_audioTrack) {
		cpp11::shared_ptr<_MediaStreamTrack>_track(new _MediaStreamTrackAudio(const_cast<webrtc::AudioTrackInterface*>(_audioTrack)));
		return _track;
	}
	return nullPtr;
}

void _RTCDTMFSender::ontonechangeSet(_ontonechangeCallback ontonechange)
{
	m_ontonechange = ontonechange;
}

const char* _RTCDTMFSender::toneBuffer()
{
	m_tones = m_sender->tones();
	return m_tones.c_str();
}

long _RTCDTMFSender::duration()
{
	return m_sender->duration();
}

long _RTCDTMFSender::interToneGap()
{
	return m_sender->inter_tone_gap();
}