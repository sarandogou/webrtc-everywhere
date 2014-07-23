/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_DEBUG_H_
#define _WEBRTC_EVERYWHERE_DEBUG_H_

#include "_Config.h"

#if !defined(WE_DEBUG_LEVEL)
#	define WE_DEBUG_LEVEL WE_DEBUG_LEVEL_ERROR
#endif

#define WE_DEBUG_LEVEL_INFO			4
#define WE_DEBUG_LEVEL_WARN			3
#define WE_DEBUG_LEVEL_ERROR		2
#define WE_DEBUG_LEVEL_FATAL		1

/* INFO */
#if WE_DEBUG_LEVEL >= DEBUG_LEVEL_INFO
#	define WE_DEBUG_INFO(FMT, ...) fprintf(stderr, "*INFO: " FMT "\n", ##__VA_ARGS__);
#else
#	define WE_DEBUG_INFO(FMT, ...)
#endif

/* WARN */
#if WE_DEBUG_LEVEL >= DEBUG_LEVEL_WARN
#	define WE_DEBUG_WARN(FMT, ...) fprintf(stderr, "**WARN: function: \"%s()\" \nfile: \"%s\" \nline: \"%u\" \nMSG: " FMT "\n", __FUNCTION__,  __FILE__, __LINE__, ##__VA_ARGS__);
#else
#	define WE_DEBUG_WARN(FMT, ...)
#endif

/* WARN */
#if WE_DEBUG_LEVEL >= DEBUG_LEVEL_ERROR
#	define WE_DEBUG_ERROR(FMT, ...) fprintf(stderr, "**ERROR: function: \"%s()\" \nfile: \"%s\" \nline: \"%u\" \nMSG: " FMT "\n", __FUNCTION__,  __FILE__, __LINE__, ##__VA_ARGS__);
#else
#	define WE_DEBUG_ERROR(FMT, ...)
#endif

/* FATAL */
#if WE_DEBUG_LEVEL >= DEBUG_LEVEL_FATAL
#	define WE_DEBUG_FATAL(FMT, ...) fprintf(stderr, "**FATAL: function: \"%s()\" \nfile: \"%s\" \nline: \"%u\" \nMSG: " FMT "\n", __FUNCTION__,  __FILE__, __LINE__, ##__VA_ARGS__);
#else
#	define WE_DEBUG_FATAL(FMT, ...)
#endif

#endif /* _WEBRTC_EVERYWHERE_DEBUG_H_ */

