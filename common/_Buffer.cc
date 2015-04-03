/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "_Buffer.h"
#include "_Debug.h"

_Buffer::_Buffer(const void* ptr, size_t size)
	: m_pPtr(NULL)
	, m_nSize(0)
{
	m_pPtr = malloc(size + 1);
	if (!m_pPtr) {
		WE_DEBUG_ERROR("Failed to allocate buffer with size=%lu", size);
		return;
	}
	((char*)m_pPtr)[size] = '\0';
	if (size && ptr) {
		memcpy(m_pPtr, ptr, size);
	}
	m_nSize = size;
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
	(*ppObj) = new _Buffer(ptr, size);
	if (!(*ppObj) || (*ppObj)->getSize() != size) {
		SafeFree(ppObj);
        WE_DEBUG_ERROR("Failed to create new buffer");
        return WeError_OutOfMemory;
    }
    return WeError_Success;
}
