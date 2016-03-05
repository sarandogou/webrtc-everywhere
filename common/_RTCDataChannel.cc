/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#idl-def-RTCDataChannel
#include "_RTCDataChannel.h"
#include "_Buffer.h"
//
//	DummyDataChannelObserver
//
class DummyDataChannelObserver
	: public webrtc::DataChannelObserver {
public:
	static DummyDataChannelObserver* Create(cpp11::function<void()> fnOnStateChange = nullPtr, cpp11::function<void(const webrtc::DataBuffer& buffe)> fnOnMessage = nullPtr) {
		return
			new rtc::RefCountedObject<DummyDataChannelObserver>(fnOnStateChange, fnOnMessage);
	}
	virtual void OnStateChange()
	{
		if (m_fnOnStateChange) {
			m_fnOnStateChange();
		}
	}
	virtual void OnMessage(const webrtc::DataBuffer& buffer)
	{
		if (m_fnOnMessage) {
			m_fnOnMessage(buffer);
		}
	}
	DummyDataChannelObserver(cpp11::function<void()> fnOnStateChange = nullPtr, cpp11::function<void(const webrtc::DataBuffer& buffe)> fnOnMessage = nullPtr)
		: m_fnOnStateChange(fnOnStateChange), m_fnOnMessage(fnOnMessage) {}
	virtual ~DummyDataChannelObserver() {}
private:
	cpp11::function<void()> m_fnOnStateChange;
	cpp11::function<void(const webrtc::DataBuffer& buffe)> m_fnOnMessage;
};


//
//	_RTCDataChannel
//
_RTCDataChannel::_RTCDataChannel(DataChannelInterfacePtr dataChannel)
{
	assert(dataChannel);
	m_dataChannel = static_cast<webrtc::DataChannelInterface*>(dataChannel);
	m_dataChannel->RegisterObserver(DummyDataChannelObserver::Create(cpp11::bind(&_RTCDataChannel::OnStateChange, this), cpp11::bind(&_RTCDataChannel::OnMessage, this, cpp11::placeholders::_1)));
	// http://www.w3.org/TR/webrtc/#widl-RTCDataChannel-binaryType
	// http://www.w3.org/TR/websockets/#dom-websocket-binarytype
	// supported values: "blob" and "arraybuffer"
	// default value: "blob"
	m_binaryType = "blob";
}

_RTCDataChannel::~_RTCDataChannel()
{
	m_dataChannel->UnregisterObserver();
	m_dataChannel = NULL;
}

const char* _RTCDataChannel::label()const
{
	const_cast<_RTCDataChannel*>(this)->m_label = m_dataChannel->label();
	return m_label.c_str();
}

bool _RTCDataChannel::ordered()const
{
	return m_dataChannel->ordered();
}

nullable_ushort _RTCDataChannel::maxRetransmitTime()const
{
	return m_dataChannel->maxRetransmitTime();
}

nullable_ushort _RTCDataChannel::maxRetransmits()const
{
	return m_dataChannel->maxRetransmits();
}

const char* _RTCDataChannel::protocol()const
{
	const_cast<_RTCDataChannel*>(this)->m_protocol = m_dataChannel->protocol();
	return m_protocol.c_str();
}

bool _RTCDataChannel::negotiated()const
{
	return m_dataChannel->negotiated();
}

nullable_ushort _RTCDataChannel::id()const
{
	return m_dataChannel->id();
}

const char* _RTCDataChannel::readyState()const
{
	switch (m_dataChannel->state()) {
	case webrtc::DataChannelInterface::kConnecting:
		return kRTCDataChannelStateConnecting;
	case webrtc::DataChannelInterface::kOpen:
		return kRTCDataChannelStateOpen;
	case webrtc::DataChannelInterface::kClosing:
		return kRTCDataChannelStateClosing;
	case webrtc::DataChannelInterface::kClosed:
		return kRTCDataChannelStateClosed;
	}
	return NULL;
}

unsigned long _RTCDataChannel::bufferedAmount()const
{
	return (unsigned long)m_dataChannel->buffered_amount();
}

const char* _RTCDataChannel::binaryType()const
{
	return m_binaryType.c_str();
}

// http://www.w3.org/TR/webrtc/#widl-RTCDataChannel-binaryType
// http://www.w3.org/TR/websockets/#dom-websocket-binarytype
// supported values: "blob" and "arraybuffer"
// default value: "blob"
bool _RTCDataChannel::binaryTypeSet(const char* _binaryType)
{
	if (_binaryType && (stricmp(_binaryType, "blob") == 0 || stricmp(_binaryType, "arraybuffer") == 0)) {
		m_binaryType = std::string(_binaryType);
		return true;
	}
	return false;
}

void _RTCDataChannel::close()
{
	m_dataChannel->Close();
}

bool _RTCDataChannel::send(const _Buffer* data, bool binary /*= true*/)
{
	if (data && data->getPtr() && data->getSize()) {
		rtc::Buffer _data((const uint8_t *)data->getPtr(), data->getSize());
		webrtc::DataBuffer buffer(_data, binary);
		return m_dataChannel->Send(buffer);
	}
	return false;
}

void _RTCDataChannel::onopenSet(_VoidFunctionCallback onopen)
{
	m_onopen = onopen;
}

void _RTCDataChannel::onerrorSet(_StringFunctionCallback onerror)
{
	m_onerror = onerror;
}

void _RTCDataChannel::oncloseSet(_VoidFunctionCallback onclose)
{
	m_onclose = onclose;
}

void _RTCDataChannel::onmessageSet(_onmessageCallback onmessage)
{
	m_onmessage = onmessage;
}

void _RTCDataChannel::OnStateChange()
{
	switch (m_dataChannel->state()) {
	case webrtc::DataChannelInterface::kConnecting :
		break;
	case webrtc::DataChannelInterface::kOpen: 
		if (m_onopen) {
			m_onopen();
		}
			break;
	case webrtc::DataChannelInterface::kClosing: 
		break;
	case webrtc::DataChannelInterface::kClosed: 
		if (m_onclose) {
			m_onclose();
		}
		break;
	}
}

void _RTCDataChannel::OnMessage(const webrtc::DataBuffer& buffer)
{
	if (m_onmessage) {
		cpp11::shared_ptr<_MessageEvent>e(new _MessageEvent());
		e->binary = buffer.binary;
		if (buffer.data.data() && buffer.size()) {
			e->data = cpp11::shared_ptr<_Buffer>(new _Buffer(buffer.data.data(), buffer.size()));
		}
		m_onmessage(e);
	}
}
