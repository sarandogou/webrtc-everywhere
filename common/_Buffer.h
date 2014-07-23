/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_COMMON_BUFFER_H_
#define _WEBRTC_EVERYWHERE_COMMON_BUFFER_H_

#include "_Config.h"

class WEBRTC_EVERYWHERE_API _Buffer
{
public:
    virtual ~_Buffer();
    WE_INLINE const void* getPtr()const {
        return m_pPtr;
    }
    WE_INLINE size_t getSize()const {
        return m_nSize;
    }

    static WeError New(const void* ptr, size_t size, _Buffer** ppObj);

private:
    _Buffer();
    void* m_pPtr;
    size_t m_nSize;
};

#endif /* _WEBRTC_EVERYWHERE_COMMON_BUFFER_H_ */
