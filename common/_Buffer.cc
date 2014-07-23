/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#include "_Buffer.h"
#include "_Debug.h"

_Buffer::_Buffer()
    : m_pPtr(NULL)
    , m_nSize(0)
{
}

_Buffer::~_Buffer()
{
    SafeFree(&m_pPtr);
}

WeError _Buffer::New(const void* ptr, size_t size, _Buffer** ppObj)
{
    if (!ppObj || !size) {
        WE_DEBUG_ERROR("Invalid argument");
        return WeError_InvalidArgument;
    }
    (*ppObj) = new _Buffer();
    if (!(*ppObj)) {
        WE_DEBUG_ERROR("Failed to create new buffer");
        return WeError_OutOfMemory;
    }
    (*ppObj)->m_pPtr = malloc(size + 1);
    if (!(*ppObj)) {
        WE_DEBUG_ERROR("Failed to allocate buffer with size=%lu", size);
        SafeFree(ppObj);
        return WeError_OutOfMemory;
    }
    ((char*)(*ppObj)->m_pPtr)[size] = '\0';
	if (ptr) {
		memcpy((*ppObj)->m_pPtr, ptr, size);
	}
    (*ppObj)->m_nSize = size;
    return WeError_Success;
}
