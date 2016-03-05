/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_UTILS_H_
#define _WEBRTC_EVERYWHERE_UTILS_H_

#include "_Config.h"
#include "_Common.h"

#include "webrtc/system_wrappers/interface/critical_section_wrapper.h"

#include <map>

class _EncryptCtx;

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

	static int ArrayBytesCount(_ArrayType arrayType);
	static bool ArrayIsFloatingPoint(_ArrayType arrayType);

	static cpp11::shared_ptr<_File> FileConfigGet(bool write = false);
	static WeError FileConfigGetKeyAndIV(const unsigned char* &key_ptr, size_t &key_size, const unsigned char* &iv_ptr, size_t &iv_size);
	static WeError FileConfigChanged(cpp11::shared_ptr<_File> file, bool &changed);
	static WeError FileConfigTrustedWebsiteAdd(const char* protocol, const char* host);
	static WeError FileConfigTrustedWebsiteExist(const char* protocol, const char* host, bool &exists);

	static WeError ConvertToBase64(const void* in_ptr, size_t in_size, void **out_pptr, size_t *out_size_ptr, void* (*MemAllocFn)(size_t n) = NULL);
	static WeError ConvertToBMP(const void* rgb32_ptr, size_t width, size_t height, void** bmp_pptr, size_t *bmp_size_ptr);
#if WE_UNDER_WINDOWS
	static HRESULT MsgBoxGUMA(bool &accepted, const char* protocol, const char* host, HWND hwndParent /*= NULL*/);
	static HRESULT MsgBoxGUM(bool &accepted, const TCHAR* protocol, const TCHAR* host, HWND hwndParent = NULL);
#elif WE_UNDER_APPLE
    static WeError MsgBoxGUM(bool &accepted, const char* protocol, const char* host);
#endif

	static void StdMemFree(void** mem);

	static void SetUserAgent(const char* userAgent);
	static const char* GetUserAgent();
    
    static rtc::Thread* GetInitThread() { return  s_InitThread; }

private:
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
    static webrtc::CriticalSectionWrapper* s_unique_objs_cs;
    static std::map<long, const _UniqueObject*> s_unique_objs;
	static _FTIME s_time_config_modif;
	static cpp11::shared_ptr<_EncryptCtx> s_encrypt_ctx;
	static std::string s_UserAgent;
    static rtc::Thread* s_InitThread;
#if _MSC_VER
#pragma warning(pop)
#endif
};

#endif /* _WEBRTC_EVERYWHERE_UTILS_H_ */

