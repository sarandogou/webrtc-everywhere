/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#idl-def-RTCDataChannel
#ifndef _WEBRTC_EVERYWHERE_COMMON__RTCDATACHANNEL_H_
#define _WEBRTC_EVERYWHERE_COMMON__RTCDATACHANNEL_H_

#include "_Config.h"
#include "_Common.h"

class WEBRTC_EVERYWHERE_API _RTCDataChannel{
public:
	_RTCDataChannel(DataChannelInterfacePtr dataChannel);
	virtual ~_RTCDataChannel();

	const char* label()const; // readonly attribute DOMString label;
	bool ordered()const;  // readonly attribute boolean ordered;
	nullable_ushort maxRetransmitTime()const; // readonly attribute unsigned short ? maxRetransmitTime;
	nullable_ushort maxRetransmits()const;// readonly attribute unsigned short ? maxRetransmits;
	const char* protocol()const; // readonly attribute DOMString protocol;
	bool negotiated()const;  // readonly attribute boolean negotiated;
	nullable_ushort id()const; // readonly attribute unsigned short ? id;
	const char* readyState()const; // readonly attribute RTCDataChannelState readyState;
	unsigned long bufferedAmount()const; // readonly attribute unsigned long bufferedAmount;
	const char* binaryType()const; // attribute DOMString binaryType;

	bool binaryTypeSet(const char* _binaryType); // attribute DOMString binaryType;
	void onopenSet(_VoidFunctionCallback onopen);
	void onerrorSet(_StringFunctionCallback onerror);
	void oncloseSet(_VoidFunctionCallback onclose);
	void onmessageSet(_onmessageCallback onmessage);
	void close(); // void close();
	bool send(const _Buffer* data, bool binary = true); // void send(DOMString data); void send(Blob data); void send(ArrayBuffer data); void send(ArrayBufferView data);

private:
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	virtual void OnStateChange();
	virtual void OnMessage(const webrtc::DataBuffer& buffer);

	std::string m_label;
	std::string m_protocol;
	std::string m_binaryType;

	_VoidFunctionCallback m_onopen;
	_StringFunctionCallback m_onerror;
	_VoidFunctionCallback m_onclose;
	_onmessageCallback m_onmessage;
	rtc::scoped_refptr<webrtc::DataChannelInterface> m_dataChannel;
#if _MSC_VER
#pragma warning(pop)
#endif
};

#endif /* _WEBRTC_EVERYWHERE_COMMON__RTCDATACHANNEL_H_ */

