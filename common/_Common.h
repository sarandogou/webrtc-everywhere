/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_COMMON_COMMON_H_
#define _WEBRTC_EVERYWHERE_COMMON_COMMON_H_

#include "_Config.h"
#include "_RTCMediaConstraints.h"

#include "talk/app/webrtc/peerconnectioninterface.h"
#include "talk/app/webrtc/mediaconstraintsinterface.h"
#include "talk/app/webrtc/mediastreaminterface.h"
#include "webrtc/base/thread.h"

#include <map>
#include <vector>

class _SessionDescription;
class _MediaStream;
class _RTCIceCandidate;
class _RTCDataChannel;
class _Buffer;

typedef void* VoidPtr;
typedef VoidPtr DtmfSenderInterfacePtr,
VideoTrackInterfacePtr,
MediaStreamInterfacePtr,
MediaStreamTrackInterfacePtr,
VideoRendererPtr,
DataChannelInterfacePtr;

#define nullable_ushort_null -1
typedef int nullable_ushort;

#if WE_UNDER_WINDOWS
typedef FILETIME _FTIME;
#else
typedef struct __FTIME {
	unsigned long dwLowDateTime;
	unsigned long dwHighDateTime;
} _FTIME;
#endif

static const char kAudioLabel[] = "audio_label";
static const char kVideoLabel[] = "video_label";
static const char kStreamLabel[] = "stream_label";

// http://www.w3.org/TR/webrtc/#idl-def-RTCSignalingState
static const char kSignalingStateStable[] = "stable";
static const char kSignalingStateHaveLocalOffer[] = "have-local-offer";
static const char kSignalingStateHaveRemoteOffer[] = "have-remote-offer";
static const char kSignalingStateHaveLocalPrAnswer[] = "have-local-pranswer";
static const char kSignalingStateHaveRemotePrAnswer[] = "have-remote-pranswer";
static const char kSignalingStateClosed[] = "closed";

// http://www.w3.org/TR/webrtc/#idl-def-RTCIceGatheringState
static const char kIceGatheringStateNew[] = "new";
static const char kIceGatheringStateGathering[] = "gathering";
static const char kIceGatheringStateComplete[] = "complete";

// http://www.w3.org/TR/webrtc/#idl-def-RTCIceConnectionState
static const char kIceConnectionStateNew[] = "new";
static const char kIceConnectionStatChecking[] = "checking";
static const char kIceConnectionStatConnected[] = "connected";
static const char kIceConnectionStatCompleted[] = "completed";
static const char kIceConnectionStatFailed[] = "failed";
static const char kIceConnectionStatDisconnected[] = "disconnected";
static const char kIceConnectionStatClosed[] = "closed";

// http://www.w3.org/TR/mediacapture-streams/#idl-def-MediaStreamTrackState
static const char kMediaStreamTrackStateNew[] = "new";
static const char kMediaStreamTrackStateLive[] = "live";
static const char kMediaStreamTrackStateEnded[] = "ended";
static const char kMediaStreamTrackStateFailed[] = "failed";

// http://www.w3.org/TR/mediacapture-streams/#idl-def-SourceTypeEnum
static const char kSourceTypeEnumNone[] = "none";
static const char kSourceTypeEnumCamera[] = "camera";
static const char kSourceTypeEnumMicrophone[] = "microphone";

// http://www.w3.org/TR/mediacapture-streams/#idl-def-VideoFacingModeEnum
static const char kVideoFacingModeEnumUser[] = "user";
static const char kVideoFacingModeEnumEnvironment[] = "environment";
static const char kVideoFacingModeEnumLeft[] = "left";
static const char kVideoFacingModeEnumRight[] = "right";

// http://www.w3.org/TR/webrtc/#rtcstats-dictionary
static const char kRTCStatsTypeInboundRtp[] = "inbound-rtp";
static const char kRTCStatsTypeOutboundRtp[] = "outbound-rtp";

// http://www.w3.org/TR/webrtc/#idl-def-RTCDataChannelState
static const char kRTCDataChannelStateConnecting[] = "connecting";
static const char kRTCDataChannelStateOpen[] = "open";
static const char kRTCDataChannelStateClosing[] = "closing";
static const char kRTCDataChannelStateClosed[] = "closed";

// ScreenShare
static const char kDoubangoScreenshareSourceId[] = "X978DoubangoTelecomScreenCapturer785";
static const char kDoubangoScreenshareLabel[] = "ScreenCapturer (Doubango Telecom)";
static const char kDoubangoScreenshareKind[] = "video";

#define kMaxParamArgs 10

// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Typed_arrays
typedef enum _ArrayType
{
	_ArrayType_None,
	_ArrayType_Int8Array,//	1	8 - bit twos complement signed integer	signed char
	_ArrayType_Uint8Array,//	1	8 - bit unsigned integer	unsigned char
	_ArrayType_Uint8ClampedArray,//	1	8 - bit unsigned integer	unsigned char
	_ArrayType_Int16Array,//	2	16 - bit twos complement signed integer	short
	_ArrayType_Uint16Array,//	2	16 - bit unsigned integer	unsigned short
	_ArrayType_Int32Array,//	4	32 - bit twos complement signed integer	int
	_ArrayType_Uint32Array,//	4	32 - bit unsigned integer	unsigned int
	_ArrayType_Float32Array,//	4	32 - bit IEEE floating point number	float
	_ArrayType_Float64Array,//	8	64 - bit IEEE floating point number	double
}
_ArrayType;

typedef struct __TrustedWebsite {
	std::string scheme;
	std::string host;
}
_TrustedWebsite;

typedef struct __BrowserObject {
	virtual struct __BrowserObject* RetainObject() = 0;
	virtual struct __BrowserObject* ReleaseObject() = 0;
} _BrowserObject;

typedef struct __BrowserCallback : _BrowserObject {
	unsigned msgid;
	__BrowserCallback(unsigned _msgid) {
		msgid = _msgid;
	}
	virtual unsigned GetMsgId() { return msgid; }
	virtual bool Invoke() = 0;
} _BrowserCallback;

typedef struct __RTCIceServer {
	std::string uri;
	std::string username;
	std::string password;
	__RTCIceServer(std::string _uri, std::string _username = std::string(""), std::string _password = std::string("")) {
		uri = _uri, username = _username, password = _password;
	}
} _RTCIceServer;

typedef struct __RTCConfiguration {
	std::vector<_RTCIceServer>iceServers;
	__RTCConfiguration() {
	}
	~__RTCConfiguration() {
		iceServers.clear();
	}
}
_RTCConfiguration;

// http://www.w3.org/TR/webrtc/#idl-def-RTCDTMFToneChangeEvent
typedef struct __RTCDTMFToneChangeEvent {
	std::string tone; // readonly attribute DOMString tone;
	__RTCDTMFToneChangeEvent(std::string _tone = "") {
		tone = _tone;
	}
}
_RTCDTMFToneChangeEvent;

// http://www.w3.org/TR/webrtc/#idl-def-RTCDataChannelEvent
typedef struct __RTCDataChannelEvent {
	cpp11::shared_ptr<_RTCDataChannel> channel; // readonly    attribute RTCDataChannel channel;
	__RTCDataChannelEvent(cpp11::shared_ptr<_RTCDataChannel>& _channel) {
		channel = _channel;
	}
}
_RTCDataChannelEvent;

// http://www.w3.org/TR/webrtc/#event-datachannel-message
typedef struct __MessageEvent {
	cpp11::shared_ptr<_Buffer>data;
	bool binary = false;
	__MessageEvent() {
	}
}
_MessageEvent;


// http://www.w3.org/TR/webrtc/#idl-def-RTCPeerConnectionIceEvent
typedef struct __RTCPeerConnectionIceEvent {
	cpp11::shared_ptr<_RTCIceCandidate> candidate;
	__RTCPeerConnectionIceEvent(cpp11::shared_ptr<_RTCIceCandidate> _candidate = nullPtr) {
		candidate = _candidate;
	}
	~__RTCPeerConnectionIceEvent() {
		candidate = nullPtr;
	}
} _RTCPeerConnectionIceEvent;

// http://www.w3.org/TR/webrtc/#idl-def-MediaStreamEvent
typedef struct __MediaStreamEvent {
	cpp11::shared_ptr<_MediaStream> stream;
	__MediaStreamEvent(cpp11::shared_ptr<_MediaStream> _stream = nullPtr) {
		stream = _stream;
	}
	~__MediaStreamEvent() {
		stream = nullPtr;
	}
}
_MediaStreamEvent;

// http://www.w3.org/TR/mediacapture-streams/#idl-def-NavigatorUserMediaError
typedef struct __NavigatorUserMediaError {
	std::string constraintName;
	__NavigatorUserMediaError(std::string _constraintName) {
		constraintName = _constraintName;
	}
} _NavigatorUserMediaError;

// http://tools.ietf.org/html/draft-burnett-rtcweb-constraints-registry-05
typedef std::pair< std::string, std::string> _MediaConstraint;
typedef std::map<std::string, std::string> _MediaConstraints;
typedef struct __MediaConstraintsObj {
	cpp11::shared_ptr<_MediaConstraints> optional;
	cpp11::shared_ptr<_MediaConstraints> mandatory;
	__MediaConstraintsObj(cpp11::shared_ptr<_MediaConstraints> _optional = nullPtr, cpp11::shared_ptr<_MediaConstraints> _mandatory = nullPtr) {
		optional = _optional;
		mandatory = _mandatory;
	}
}
_MediaConstraintsObj;

// http://www.w3.org/TR/mediacapture-streams/#idl-def-SourceInfo
typedef struct __SourceInfo {
	std::string sourceId;
	std::string kind;
	std::string label;
	std::string facing; // VideoFacingModeEnum 

	__SourceInfo(std::string _sourceId = "", std::string _kind = "", std::string _label = "") {
		sourceId = _sourceId;
		kind = _kind;
		label = _label;
	}
}
_SourceInfo;

// http://www.w3.org/TR/mediacapture-streams/#idl-def-MediaSourceStates
typedef struct __MediaSourceStates{
	std::string sourceType; // SourceTypeEnum sourceType; 
	std::string sourceId;
	unsigned long width;
	unsigned long height;
	float frameRate;
	float aspectRatio;
	std::string facingMode; // VideoFacingModeEnum ? facingMode;
	unsigned long volume;
}
_MediaSourceStates;

// http://www.w3.org/TR/webrtc/#rtcstats-dictionary
typedef struct __RTCStats {
	double timestamp; // DOMHiResTimeStamp timestamp;
	std::string type; // RTCStatsType      type;
	std::string id; // DOMString         id;
	std::map<std::string, std::string> names;
	std::string stat(std::string name) {
		std::map<std::string, std::string>::iterator it = names.find(name);
		if (it != names.end()) {
			return (*it).second;
		}
		return std::string("");
	}
}
_RTCStats;

// http://www.w3.org/TR/webrtc/#dictionary-rtcrtpstreamstats-members
typedef struct  __RTCRTPStreamStats : _RTCStats{
	std::string ssrc; // DOMString ssrc;
	std::string remoteId; // DOMString remoteId;
}
_RTCRTPStreamStats;

// http://www.w3.org/TR/webrtc/#dictionary-rtcinboundrtpstreamstats-members
typedef struct  __RTCInboundRTPStreamStats : _RTCStats{
	unsigned long bytesReceived;
	unsigned long packetsReceived;
}
_RTCInboundRTPStreamStats;

// http://www.w3.org/TR/webrtc/#dictionary-rtcoutboundrtpstreamstats-members
typedef struct  __RTCOutboundRTPStreamStats : _RTCStats{
	unsigned long bytesSent;
	unsigned long packetsSent;
}
_RTCOutboundRTPStreamStats;

// http://www.w3.org/TR/webrtc/#rtcstatsreport-object
typedef struct  __RTCStatsReport {
	std::map<std::string, cpp11::shared_ptr<_RTCStats> > values; // getter RTCStats(DOMString id);
}
_RTCStatsReport;

// http://www.w3.org/TR/webrtc/#idl-def-RTCDataChannelInit
typedef struct  __RTCDataChannelInit {
	// "nullable_ushort" is used instead of "unsigned short" to emulate nulable values: "-1 == null" (same rule is used in WebRTC internals)
	bool ordered = true; //  boolean ordered = true;
	nullable_ushort maxRetransmitTime = nullable_ushort_null; // unsigned short ? maxRetransmitTime = null;
	nullable_ushort maxRetransmits = nullable_ushort_null; // unsigned short ? maxRetransmits = null;
	std::string protocol = ""; // DOMString protocol = "";
	bool negotiated = false; // boolean negotiated = false;
	nullable_ushort id = nullable_ushort_null; // unsigned short ? id = null;
}
_RTCDataChannelInit;

// http://www.w3.org/TR/mediacapture-streams/#idl-def-CapabilityRange
typedef struct __CapabilityRange {
	enum RangeType {
		String,
		Integer
	};
	// any     max;
	// any     min;
	bool supported;
	RangeType type;
	__CapabilityRange(RangeType _type, bool _supported) {
		type = _type;
		supported = _supported;
	}
}
_CapabilityRange;
typedef struct __CapabilityRangeInteger : public _CapabilityRange {
	long max;
	long min;
	__CapabilityRangeInteger(bool _supported, long _max, long _min) : _CapabilityRange(_CapabilityRange::Integer, _supported) {
		max = _max, min = _min;
	}
}
_CapabilityRangeInteger;
typedef struct __CapabilityRangeString : public _CapabilityRange {
	std::string max;
	std::string min;
	__CapabilityRangeString(bool _supported, std::string _max, std::string _min) : _CapabilityRange(_CapabilityRange::String, _supported) {
		max = _max, min = _min;
	}
}
_CapabilityRangeString;

template <typename T>
struct _Sequence {
	std::vector<cpp11::shared_ptr<T> > values;
	_Sequence() {

	}
	void Clear() {
		values.clear();
	}
	void Add(cpp11::shared_ptr<T> v) {
		values.push_back(v);
	}
	~_Sequence() {
		Clear();
	}
};

typedef struct __AllCapabilities {
	enum CapType {
		Audio,
		Video
	};
	CapType type;
	__AllCapabilities(CapType _type) {
		type = _type;
	}
}
_AllCapabilities;

// http://www.w3.org/TR/mediacapture-streams/#idl-def-CapabilityList
typedef _Sequence<std::string> _CapabilityList; // typedef sequence<DOMString> CapabilityList;

// http://www.w3.org/TR/mediacapture-streams/#idl-def-AllVideoCapabilities
typedef struct __AllVideoCapabilities : public _AllCapabilities {
	cpp11::shared_ptr<_CapabilityList> sourceType; // CapabilityList ? sourceType;
	cpp11::shared_ptr<_CapabilityList> sourceId; // CapabilityList ? sourceId;
	cpp11::shared_ptr<_CapabilityRange> width; // CapabilityRange ? width;
	cpp11::shared_ptr<_CapabilityRange> height; // CapabilityRange ? height;
	cpp11::shared_ptr<_CapabilityRange> frameRate; // CapabilityRange ? frameRate;
	cpp11::shared_ptr<_CapabilityRange> aspectRatio; // CapabilityRange ? aspectRatio;
	cpp11::shared_ptr<_CapabilityList> facingMode; // CapabilityList ? facingMode;
	__AllVideoCapabilities() : _AllCapabilities(_AllCapabilities::Video){
	}
}
_AllVideoCapabilities;

// http://www.w3.org/TR/mediacapture-streams/#idl-def-AllAudioCapabilities
typedef struct __AllAudioCapabilities : public _AllCapabilities {
	cpp11::shared_ptr<_CapabilityRange> volume; // CapabilityRange ? volume;
	__AllAudioCapabilities() : _AllCapabilities(_AllCapabilities::Audio){
	}
}
_AllAudioCapabilities;

template <typename T>
class WEBRTC_EVERYWHERE_API _AutoLock {
public:
	explicit _AutoLock(T* obj) : obj_(obj) { obj_->Enter(); }
	virtual ~_AutoLock() { obj_->Leave(); }
protected:
	T* obj_;
};

class WEBRTC_EVERYWHERE_API _UniqueObject {
public:
    virtual ~_UniqueObject();
    WE_INLINE long UniqueId()const { return m_id; }
    operator long() const {
		return m_id;
	}
protected:
    explicit _UniqueObject();
private:
    long m_id;
};

// _Window
typedef struct __Window{
	intptr_t id;
	std::string title;
	__Window(intptr_t id_, std::string title_) {
		id = id_;
		title = title_;
	}
}
_Window;
typedef std::vector<_Window> _WindowList;

class _File {
public:
#if WE_UNDER_WINDOWS
	_File(const TCHAR* path, bool write = false);
#else
    _File(const char* path, bool write = false);
#endif
	virtual ~_File();
	virtual bool IsValid()const;
	virtual bool LockInterProcess(bool exclusive = false);
	virtual bool UnlockInterProcess();
	virtual cpp11::shared_ptr<_Buffer> Read();
	virtual bool Write(cpp11::shared_ptr<_Buffer>& buffer, bool append = false);
	virtual bool GetModificationTime(_FTIME *time);
private:
#if WE_UNDER_WINDOWS
	HANDLE m_file;
#else
    FILE* m_file;
#endif
	bool m_write;
};

class _FileInterProcessLock {
public:
	explicit _FileInterProcessLock(cpp11::shared_ptr<_File> file, bool exclusive = false) : file_(file) { file_->LockInterProcess(exclusive); }
	virtual ~_FileInterProcessLock() { file_->UnlockInterProcess(); }
protected:
	cpp11::shared_ptr<_File> file_;
};


typedef cpp11::function<void()> _VoidFunctionCallback;
typedef cpp11::function<void(cpp11::shared_ptr<std::string> string)> _StringFunctionCallback;

// http://www.w3.org/TR/webrtc/#idl-def-RTCSessionDescriptionCallback
typedef cpp11::function<void(cpp11::shared_ptr<_SessionDescription> sdp)> _RTCSessionDescriptionCallback;

// http://www.w3.org/TR/webrtc/#idl-def-RTCPeerConnectionErrorCallback
typedef cpp11::function<void(cpp11::shared_ptr<std::string> error)> _RTCPeerConnectionErrorCallback;

// http://www.w3.org/TR/mediacapture-streams/#idl-def-NavigatorUserMediaSuccessCallback
typedef cpp11::function<void(cpp11::shared_ptr<_MediaStream> stream)> _NavigatorUserMediaSuccessCallback;

// http://www.w3.org/TR/mediacapture-streams/#idl-def-NavigatorUserMediaErrorCallback
typedef cpp11::function<void(cpp11::shared_ptr<_NavigatorUserMediaError> e)> _NavigatorUserMediaErrorCallback;

// http://www.w3.org/TR/webrtc/#event-negotiation
typedef cpp11::function<void()> _onnegotiationneededCallback;
// http://www.w3.org/TR/webrtc/#event-icecandidate
typedef cpp11::function<void(cpp11::shared_ptr<_RTCPeerConnectionIceEvent> e)> _onicecandidateCallback;
// http://www.w3.org/TR/webrtc/#event-signalingstatechange
typedef cpp11::function<void()> _onsignalingstatechangeCallback;
// http://www.w3.org/TR/webrtc/#event-mediastream-addstream
typedef cpp11::function<void(cpp11::shared_ptr<_MediaStreamEvent> stream)> _onaddstreamCallback;
// http://www.w3.org/TR/webrtc/#event-mediastream-removestream
typedef cpp11::function<void(cpp11::shared_ptr<_MediaStreamEvent> stream)> _onremovestreamCallback;
// http://www.w3.org/TR/webrtc/#event-iceconnectionstatechange
typedef cpp11::function<void()> _oniceconnectionstatechangeCallback;
// http://www.w3.org/TR/webrtc/#idl-def-RTCStatsCallback
typedef cpp11::function<void(cpp11::shared_ptr<_RTCStatsReport> report)> _RTCStatsCallback;
// http://www.w3.org/TR/webrtc/#idl-def-RTCDTMFToneChangeEvent
typedef cpp11::function<void(cpp11::shared_ptr<_RTCDTMFToneChangeEvent> e)> _ontonechangeCallback;
// http://www.w3.org/TR/webrtc/#idl-def-RTCDataChannelEvent
typedef cpp11::function<void(cpp11::shared_ptr<_RTCDataChannelEvent> e)> _ondatachannelCallback;
// http://www.w3.org/TR/webrtc/#event-datachannel-message
typedef cpp11::function<void(cpp11::shared_ptr<_MessageEvent> e)> _onmessageCallback;


typedef _MediaStream*(*_MediaStreamAllocateFn)();


#if defined(__GNUC__) || (HAVE___SYNC_FETCH_AND_ADD && HAVE___SYNC_FETCH_AND_SUB)
#	define we_atomic_inc(_ptr_) __sync_fetch_and_add((_ptr_), 1)
#	define we_atomic_dec(_ptr_) __sync_fetch_and_sub((_ptr_), 1)
#elif defined(_MSC_VER)
#	define we_atomic_inc(_ptr_) InterlockedIncrement((_ptr_))
#	define we_atomic_dec(_ptr_) InterlockedDecrement((_ptr_))
#else
#	define we_atomic_inc(_ptr_) ++(*(_ptr_))
#	define we_atomic_dec(_ptr_) --(*(_ptr_))
#endif

#define SafeDelete(pptr) if(pptr && *pptr) delete *pptr, *pptr = NULL;

#define we_strlen(pStr) ((pStr) ? strlen((pStr)) : 0)

#define BrowserObjectImpl_IUnknown() \
	virtual struct __BrowserObject* RetainObject() { \
		if (AddRef()) return dynamic_cast<struct __BrowserObject*>(this); \
		return NULL; \
	} \
	virtual struct __BrowserObject* ReleaseObject() { \
	if (Release()) return dynamic_cast<struct __BrowserObject*>(this); \
	return NULL; \
}

#define BrowserObjectImpl_NPObject() \
	virtual struct __BrowserObject* RetainObject(){ \
		extern NPNetscapeFuncs* BrowserFuncs; \
		if  (BrowserFuncs->retainobject(this)) return this; \
		return NULL; \
	} \
	virtual struct __BrowserObject* ReleaseObject(){ \
		extern NPNetscapeFuncs* BrowserFuncs; \
		BrowserFuncs->releaseobject(this); \
		if (this->referenceCount == 0)  return NULL; \
		return this; \
	}

#define BrowserObjectImpl_Inline() \
	private: \
	volatile long m_nRefCount = 1; \
	public: \
	struct __BrowserObject* RetainObject() { \
		assert(m_nRefCount > 0); \
		we_atomic_inc(&m_nRefCount); return this; \
	} \
struct __BrowserObject* ReleaseObject() { \
	assert(m_nRefCount > 0); \
    we_atomic_dec(&m_nRefCount); \
	if (m_nRefCount) return this; \
	delete this; return NULL; \
}

#define NPObjectImpl_CreateInstanceWithRef(classname) \
	static NPError CreateInstanceWithRef(NPP instance, classname** ppObj) { \
		extern NPClass classname##Class; \
		extern NPNetscapeFuncs* BrowserFuncs; \
		if (!ppObj) { \
			CHECK_NPERR_RETURN(NPERR_INVALID_PARAM); \
				} \
		NPObject* pObj; \
		if (!(pObj = BrowserFuncs->createobject(instance, &classname##Class))) { \
			CHECK_NPERR_RETURN(NPERR_OUT_OF_MEMORY_ERROR); \
				} \
		*ppObj = dynamic_cast<classname*>((classname*)pObj); \
		return NPERR_NO_ERROR; \
	}

#define NPObjectImpl_NPObjectRelease(classname) \
	static void ReleaseInstance(classname** ppObj) { \
		if (ppObj && *ppObj) { \
			extern NPNetscapeFuncs* BrowserFuncs; \
			NPObject *pObj = dynamic_cast<NPObject*>(*ppObj); \
			SafeReleaseNPObject(&pObj); \
			*ppObj = NULL; \
				} \
	}
#define NPObjectImpl_IsInstanceOf(classname) \
	static bool IsInstanceOf(NPObject* pObj) { \
		extern NPClass classname##Class; \
		return (pObj && pObj->_class == &classname##Class); \
	}

#undef CHECK_HR
// In CHECK_HR(x) When (x) is a function it will be executed twice when used in "WE_DEBUG_ERROR(x)" and "If(x)"
#define CHECK_HR_BAIL(x) { HRESULT __hr__ = (x); if (FAILED(__hr__)) { WE_DEBUG_ERROR("Operation Failed (%08x)", __hr__); goto bail; } }
#define CHECK_HR_RETURN(x) { HRESULT __hr__ = (x); if (FAILED(__hr__)) { WE_DEBUG_ERROR("Operation Failed (%08x)", __hr__); return __hr__; } }
#define CHECK_NPERR_BAIL(x) { NPError __err__ = (x); if (__err__ != NPERR_NO_ERROR) { WE_DEBUG_ERROR("Operation Failed (%08x)", __err__); goto bail; } }
#define CHECK_NPERR_RETURN(x) { NPError __err__ = (x); if (__err__ != NPERR_NO_ERROR) { WE_DEBUG_ERROR("Operation Failed (%08x)", __err__); return __err__; } }

extern WEBRTC_EVERYWHERE_API rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> GetPeerConnectionFactory();
extern WEBRTC_EVERYWHERE_API rtc::Thread* GetWorkerThread();
extern WEBRTC_EVERYWHERE_API rtc::scoped_refptr<webrtc::PortAllocatorFactoryInterface> GetPortAllocatorFactory();
extern WEBRTC_EVERYWHERE_API void TakeFakePeerConnectionFactory();
extern WEBRTC_EVERYWHERE_API void ReleaseFakePeerConnectionFactory();
extern WEBRTC_EVERYWHERE_API bool GetWindowList(_WindowList* windowList);
extern rtc::scoped_refptr<_RTCMediaConstraints> BuildConstraints(const _MediaConstraintsObj* constraints = NULL);
extern webrtc::MediaStreamInterface* BuildMediaStream(const _MediaStream* stream);

#endif /* _WEBRTC_EVERYWHERE_COMMON_COMMON_H_ */

