/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "_SessionDescription.h"
#include "_Buffer.h"
#include "_Logging.h"
#include "_Debug.h"

#include "webrtc/base/json.h"

_SessionDescription::_SessionDescription()
	: m_pSdp(NULL)
	, m_pType(NULL)
{
	WE_LOG_FUNCTION_CALL();
	Init(NULL, NULL, NULL, NULL);
}

_SessionDescription::_SessionDescription(const void* sdpPtr, size_t sdpSize, const void* typePtr, size_t typeSize)
	: m_pSdp(NULL)
	, m_pType(NULL)
{
	WE_LOG_FUNCTION_CALL();
	Init(sdpPtr, sdpSize, typePtr, typeSize);
}

_SessionDescription::~_SessionDescription()
{
	WE_LOG_FUNCTION_CALL();
    SafeFree(&m_pSdp);
    SafeFree(&m_pType);
}

WeError _SessionDescription::Init(const void* sdpPtr, size_t sdpSize, const void* typePtr /*= NULL*/, size_t typeSize /*= 0*/)
{
	WE_LOG_FUNCTION_CALL();
#if 1
	WeError err = WeError_Success;
	SafeFree(&m_pSdp);
	SafeFree(&m_pType);

	if (sdpPtr && sdpSize) {
		err = _Buffer::New(sdpPtr, sdpSize, &m_pSdp);
		if (err) {
			goto bail;
		}
	}
	if (typePtr && typeSize) {
		err = _Buffer::New(typePtr, typeSize, &m_pType);
		if (err) {
			goto bail;
		}
	}

bail:
	return err;
#else
    WeError err;
    const char* _descriptionInitDictPtr;
    Json::Value root, sdp, type;
    Json::Reader reader;

	if (!sdpPtr || !sdpSize) {
        WE_DEBUG_ERROR("Invalid argument");
        err = WeError_InvalidArgument;
        goto bail;
    }

	_descriptionInitDictPtr = (const char*)sdpPtr;
	if (!(reader.parse(_descriptionInitDictPtr, (_descriptionInitDictPtr + sdpSize), root))) {
		WE_DEBUG_ERROR("Invalid JSON content:%.*s", sdpSize, _descriptionInitDictPtr);
        err = WeError_InvalidJsonContent;
        goto bail;
    }

    sdp = root["sdp"];
    type = root["type"];

    if (sdp.isNull() || !sdp.isString()) {
        WE_DEBUG_ERROR("'sdp' attribute is missing");
        err = WeError_InvalidJsonContent;
        goto bail;
    }
    if (type.isNull() || !type.isString()) {
        WE_DEBUG_ERROR("'type' attribute is missing");
        err = WeError_InvalidJsonContent;
        goto bail;
    }
    if (type.asString().compare(kRTCSdpType_offer) && type.asString().compare(kRTCSdpType_pranswer) && type.asString().compare(kRTCSdpType_answer)) {
        WE_DEBUG_ERROR("'%s' not a valid sdp type", type.asCString());
        err = WeError_InvalidJsonContent;
        goto bail;
    }

    SafeFree(&m_pSdp);
    SafeFree(&m_pType);
    err = _Buffer::New(type.asCString(), type.asString().length(), &m_pType);
    if (err) {
        goto bail;
    }
    err = _Buffer::New(sdp.asCString(), sdp.asString().length(), &m_pSdp);
    if (err) {
        goto bail;
    }

bail:
    return err;
#endif
}
