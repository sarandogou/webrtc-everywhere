/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_CONFIG_H_
#define _WEBRTC_EVERYWHERE_CONFIG_H_

#define WE_CAT_(A, B) A ## B
#define WE_CAT(A, B) WE_CAT_(A, B)
#define WE_STRING_(A) #A
#define WE_STRING(A) WE_STRING_(A)

#if !defined(kPluginMIMEType)
#	define kPluginMIMEType "application/webrtc-everywhere"
#endif

#if !defined(kPluginVersionMajor)
#	define kPluginVersionMajor 1
#endif
#if !defined(kPluginVersionMinor)
#	define kPluginVersionMinor 3
#endif
#if !defined(kPluginVersionMicro)
#	define kPluginVersionMicro 1
#endif
#if !defined(kPluginVersionString)
#	define kPluginVersionString WE_STRING(WE_CAT(kPluginVersionMajor, .)) WE_STRING(WE_CAT(kPluginVersionMinor, .)) WE_STRING(kPluginVersionMicro)
#endif

// Windows
#if defined(WIN32)|| defined(_WIN32) || defined(_WIN32_WCE)
#	define WE_UNDER_WINDOWS	1
#else
typedef int64_t LONGLONG;
typedef unsigned int UINT;
typedef long LRESULT;
typedef void* WPARAM;
typedef void* LPARAM;
typedef void* HWND;
#define CALLBACK
#endif

// OS X or iOS
#if defined(__APPLE__)
#	define WE_UNDER_APPLE				1
#endif
#if TARGET_OS_MAC
#	define WE_UNDER_MAC					1
#endif
#if TARGET_OS_IPHONE
#	define WE_UNDER_IPHONE				1
#endif
#if TARGET_IPHONE_SIMULATOR
#	define WE_UNDER_IPHONE_SIMULATOR	1
#endif


#ifdef _MSC_VER
#	if !defined(_CRT_SECURE_NO_WARNINGS)
#		define _CRT_SECURE_NO_WARNINGS
#	endif
#	define WE_INLINE	_inline
#	define we_stricmp	_stricmp
#	ifndef __STDC_LIMIT_MACROS
#		define __STDC_LIMIT_MACROS
#	endif
#else
#	define WE_INLINE	inline
#	define we_stricmp	stricmp
#endif

#if !defined(__GNUC__) && defined(WEBRTC_EVERYWHERE_EXPORTS)
# 	define WEBRTC_EVERYWHERE_API		__declspec(dllexport)
#	define WEBRTC_EVERYWHERE_GEXTERN	extern __declspec(dllexport)
#elif !defined(__GNUC__) && !defined(WEBRTC_EVERYWHERE_IMPORTS_IGNORE)
# 	define WEBRTC_EVERYWHERE_API		__declspec(dllimport)
#	define WEBRTC_EVERYWHERE_GEXTERN	__declspec(dllimport)
#else
#	define WEBRTC_EVERYWHERE_API
#	define WEBRTC_EVERYWHERE_GEXTERN	extern
#endif

typedef enum WeError {
    WeError_Success = 0,
    WeError_InvalidArgument,
    WeError_InvalidJsonContent,
    WeError_OutOfMemory,
    WeError_System,
	WeError_NotInitialized
}
WeError;

// http://www.w3.org/TR/webrtc/#idl-def-RTCSdpType
#define kRTCSdpType_offer		"offer"
#define kRTCSdpType_pranswer	"pranswer"
#define kRTCSdpType_answer		"answer"

#define SafeRelease(ppObj) { if ((ppObj) && *(ppObj)) { (*(ppObj))->Release(); *(ppObj) = NULL; } }
#define SafeReleaseObject(ppObj) { if ((ppObj) && *(ppObj)) { (*(ppObj))->ReleaseObject(); *(ppObj) = NULL; } }
#define SafeFree(ppObj) { if ((ppObj) && *(ppObj)) { free(*(ppObj)); *(ppObj) = NULL; } }

#define SafeReleaseNPObject(ppObj) \
	if ((ppObj) && *(ppObj)) { \
		if ((*(ppObj))->referenceCount > 0) BrowserFuncs->releaseobject(*(ppObj)); \
		*(ppObj) = NULL; \
	}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#include <iostream>
#include <string>
#include <assert.h>

// C++11
#include <functional>
#include <memory>

#if __clang__
#   include <tr1/memory>
#   include <tr1/functional>

namespace cpp11 = std::tr1;
class {
public:
    template<typename T>
    operator cpp11::shared_ptr<T>() { return cpp11::shared_ptr<T>(); }
} nullPtr;
#elif _MSC_VER || __llvm__ || 1
#   include <mutex>
namespace cpp11 = std;
#   define nullPtr nullptr
#else
#	error "Not implemented"
#endif

#if 0
#include <thread>
#include <chrono>
#endif

#endif /* _WEBRTC_EVERYWHERE_CONFIG_H_ */

