/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_COMMON_SESSIONDESCRIPTION_H_
#define _WEBRTC_EVERYWHERE_COMMON_SESSIONDESCRIPTION_H_

#include "_Config.h"

class _Buffer;

class WEBRTC_EVERYWHERE_API _SessionDescription
{
public:
    _SessionDescription();
    _SessionDescription(const void* sdpPtr, size_t sdpSize, const void* typePtr, size_t typeSize);
    virtual ~_SessionDescription();

	WE_INLINE const _Buffer* getSdp()const {
        return m_pSdp;
    }
    WE_INLINE const _Buffer* getType()const {
        return m_pType;
    }

	WeError Init(const void* sdpPtr, size_t sdpSize, const void* typePtr = NULL, size_t typeSize = 0);

public:
    _Buffer* m_pSdp;
    _Buffer* m_pType;
};

#endif /* _WEBRTC_EVERYWHERE_COMMON_SESSIONDESCRIPTION_H_ */
