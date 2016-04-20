/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_COMMON_LOGGING_H_
#define _WEBRTC_EVERYWHERE_COMMON_LOGGING_H_

#include "_Config.h"
#include "_Common.h"

#define WE_LOG_FUNCTION_CALL() _Logging::shared()->logFunctionCall(__FUNCTION__)
#define WE_LOG_ERROR(msg) _Logging::shared()->logError((std::string("[") + std::string(__FUNCTION__) + std::string("] ") + std::string(msg)).c_str())

class _LogSink;

class WEBRTC_EVERYWHERE_API _Logging
{
public:
	_Logging();
	virtual ~_Logging();
	bool setSeverity(const char* severity);
	const char* getSeverity();
	bool logFunctionCall(const char* functionName);
	bool logInfo(const char* message);
	bool logWarn(const char* message);
	bool logError(const char* message);
	static bool initialize();
	static bool deInitialize();
	static cpp11::shared_ptr<_Logging> shared() { return g_shared; }

private:
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	int m_Severity;
	cpp11::shared_ptr<_LogSink> m_sink;
	static bool g_bInitialized;
	static cpp11::shared_ptr<_Logging> g_shared;
#if _MSC_VER
#pragma warning(pop)
#endif
};

#endif /* _WEBRTC_EVERYWHERE_COMMON_LOGGING_H_ */
