/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_UTILS_H_
#define _WEBRTC_EVERYWHERE_UTILS_H_

#include "_Config.h"
#include "_Common.h"

#include "webrtc/system_wrappers/interface/critical_section_wrapper.h"

#include <map>

class WEBRTC_EVERYWHERE_API _Utils
{
public:
    _Utils();
    virtual ~_Utils();

public:
	static WeError Initialize(WeError(*InitializeAdditionals) (void) = NULL);
	static WeError DeInitialize(void);
    static WeError StartDebug(void);
    static WeError StopDebug(void);

	static std::string ToString(long val);

	static bool RaiseCallback(LONGLONG handle, _BrowserCallback* cb);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    
    static long UniqueId();
    static const _UniqueObject* UniqueObjFind(long id);
    static void UniqueObjAdd(const _UniqueObject* obj);
    static void UniqueObjRemove(long id);

	static WeError ConvertToBase64(const void* in_ptr, size_t in_size, void **out_pptr, size_t *out_size_ptr, void* (*MemAllocFn)(size_t n) = NULL);
	static WeError ConvertToBMP(const void* rgb32_ptr, size_t width, size_t height, void** bmp_pptr, size_t *bmp_size_ptr);
    
private:
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
    static webrtc::CriticalSectionWrapper* s_unique_objs_cs;
    static std::map<long, const _UniqueObject*> s_unique_objs;
#if _MSC_VER
#pragma warning(pop)
#endif
};

#endif /* _WEBRTC_EVERYWHERE_UTILS_H_ */

