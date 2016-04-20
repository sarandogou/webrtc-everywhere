/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "_Logging.h"
#include "_Buffer.h"

#include "webrtc/system_wrappers/interface/tick_util.h"
#include "webrtc/base/common.h"

#if WE_UNDER_WINDOWS
#	include <windows.h>
#	include <comutil.h>
#	include <shlwapi.h>
#	include <shlobj.h>
#	include <AtlConv.h>
# elif WE_UNDER_MAC
#   import <Foundation/Foundation.h>
#   import <CoreFoundation/CoreFoundation.h>
#	include <dirent.h>
#endif

#include <sys/stat.h>

#include <string.h>
#include <iostream>
#include <ctime>

#define kFileMaxLength 15 * (1024 *1024)

//
//	_LoggingTime
//

class _LoggingTime
{
public:
	static std::string GetNowTimeStamp(bool bForFileName = true)
	{
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		if (bForFileName) {
			strftime(buffer, 80, "%d-%m-%Y__%H-%M-%S", timeinfo);
		}
		else {
			strftime(buffer, 80, "%d-%m-%Y %H:%M:%S", timeinfo);
		}
		return std::string(buffer);
	}
	static bool GetModificationTime(const char* path, time_t *time)
	{
		if (path && time) {
			struct stat _stat;
			if (stat(path, &_stat) == 0) {
				*time = _stat.st_mtime;
				return true;
			}
		}
		return false;
	}

	static bool TimeIsOneDayOld(const time_t *now, const time_t *time)
	{
		if (now && time && *now > *time) {
			// struct tm * timeinfo = localtime(time);
			static const time_t kOneDayInSeconds = 86400;
			time_t diff = (*now - *time);
			return diff > kOneDayInSeconds;
		}
		return false;
	}
};

//
//	_LoggingFiles
//

class _LoggingFiles
{
public:
	static std::string GetDir()
	{
#if WE_UNDER_WINDOWS 
		// http ://support.microsoft.com/kb/310294
		TCHAR szPath[MAX_PATH];
		// Get path for each computer, non-user specific and non-roaming data.
		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, szPath))) {
			// Append product-specific path - this path needs to already exist
			// for GetTempFileName to succeed.
			PathAppend(szPath, TEXT("\\Doubango Telecom\\webrtc-everywhere\\"));
			if (SUCCEEDED(SHCreateDirectoryEx(NULL, szPath, NULL))) {
				int pathSize = WideCharToMultiByte(CP_ACP, 0, szPath, int(wcslen(szPath) + 0), 0, 0, 0, 0);
				std::string path(pathSize, 0);
				WideCharToMultiByte(CP_ACP, 0, szPath, int(wcslen(szPath) + 0), &path[0], pathSize, 0, 0);
				return path;
			}
		}
# elif WE_UNDER_MAC
		NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
		NSString *documentsDir = [[documentPaths objectAtIndex : 0] stringByAppendingPathComponent:@"webrtc-everywhere"];
		NSFileManager *fileManager = [NSFileManager defaultManager];
		BOOL isDirectory = NO;
		BOOL exists = [fileManager fileExistsAtPath : documentsDir isDirectory : &isDirectory];
		if (!exists){
			NSError* error = nil;
			BOOL created = [fileManager createDirectoryAtPath : documentsDir withIntermediateDirectories : YES attributes : nil error : &error];
			if (!created){
				NSLog(@"Failed to create folder (%@) to the file system: %@", documentsDir, error);
				return "";
			}
		}
        return std::string((const char*)[documentsDir UTF8String]) + std::string("/");
#else
#error "Not implemented"
#endif
		return "";
	}

	static std::string GetFullPath(std::string filename)
	{
		if (!filename.empty()) {
			std::string dir = _LoggingFiles::GetDir();
			if (!dir.empty()) {
				char micsecond[64];
#if defined(_MSC_VER)
				sprintf_s(micsecond, sizeof(micsecond), "%I64d", webrtc::TickTime::Now().MicrosecondTimestamp());
#else
                sprintf(micsecond, "%lld", webrtc::TickTime::Now().MicrosecondTimestamp());
#endif
				return dir + filename;
			}
		}
		return "";
	}

	static std::string GetUniqueFileName()
	{
		char micsecond[64];
#if defined(_MSC_VER)
		sprintf_s(micsecond, sizeof(micsecond), "%I64d", webrtc::TickTime::Now().MicrosecondTimestamp());
#else
        sprintf(micsecond, "%lld", webrtc::TickTime::Now().MicrosecondTimestamp());
#endif
		return _LoggingTime::GetNowTimeStamp() + std::string("_") + std::string(micsecond) + std::string(".log");
	}

	static std::string GetUniqueFilePath()
	{
		return GetFullPath(GetUniqueFileName());
	}

	static bool RemoveOldLogFiles()
	{
		static std::string kLogExtension = ".log";
		std::string dirPath = _LoggingFiles::GetDir();
		if (!dirPath.empty())
		{
			std::string filePath, fileName;
			time_t now, ftime;
			time(&now);

#if WE_UNDER_WINDOWS
			WIN32_FIND_DATAA FindFileData;
			HANDLE hFind;
			if ((hFind = ::FindFirstFileA((dirPath + std::string("*") + kLogExtension).c_str(), &FindFileData)) != INVALID_HANDLE_VALUE)
			{
				do
				{
					if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
					{
						filePath = dirPath + std::string(FindFileData.cFileName);
						if (_LoggingTime::GetModificationTime(filePath.c_str(), &ftime))
						{
							if (_LoggingTime::TimeIsOneDayOld(&now, &ftime))
							{
								if (DeleteFileA(filePath.c_str()) != TRUE)
								{
									_Logging::shared()->logError((std::string("Failed to remove file: ") + filePath).c_str());
								}
							}
						}
					}
				}
				while (::FindNextFileA(hFind, &FindFileData));
				::FindClose(hFind);

				return true;
			}
			else
			{
				_Logging::shared()->logError((std::string("FindFirstFileA(") + dirPath + std::string(") failed")).c_str());
			}
#else // using <dirent.h> (OSX)
			DIR *dir;
			struct dirent *ent;
			if ((dir = opendir(dirPath.c_str())) != NULL)
			{
				while ((ent = readdir(dir)) != NULL)
				{
					fileName = std::string(ent->d_name, ent->d_namlen);
					if (fileName.length() > 4 && std::equal(kLogExtension.rbegin(), kLogExtension.rend(), fileName.rbegin()))
					{
						filePath = dirPath + fileName;
						if (_LoggingTime::GetModificationTime(filePath.c_str(), &ftime))
						{
							if (_LoggingTime::TimeIsOneDayOld(&now, &ftime))
							{
								if (remove(filePath.c_str()) != 0)
								{
									_Logging::shared()->logError((std::string("Failed to remove file: ") + filePath).c_str());
								}
							}
						}
					}
				}
				closedir(dir);
				return true;
			}
			else
			{
				_Logging::shared()->logError((std::string("opendir(") + dirPath + std::string(") failed")).c_str());
			}
#endif
		}
		return false;
	}
};


//
//	_LogSink
//

class _LogSink : public rtc::LogSink {
public:
	_LogSink() 
		: m_file(NULL)
		, m_file_length(0)
	{
		std::string filePath = _LoggingFiles::GetUniqueFilePath();
		ASSERT(!filePath.empty());
		if (!filePath.empty()) {
			m_file = fopen(filePath.c_str(), "w+");
			ASSERT(m_file != NULL);
		}
	}
	virtual ~_LogSink() {
		if (m_file) {
			fclose(m_file);
		}
	}
	bool logMessage(const std::string& message) {
		if (m_file && !message.empty()) {
			const std::string messageWithTimestamp = std::string("[") + _LoggingTime::GetNowTimeStamp(false) + std::string("] ") + message;
			m_file_length += fwrite(messageWithTimestamp.c_str(), 1, messageWithTimestamp.length(), m_file);
			return true;
		}
		return false;
	}
	virtual void OnLogMessage(const std::string& message) {
		logMessage(message);
	}
	
private:
	FILE* m_file;
	size_t m_file_length;
};

//
//	_Logging
//

bool _Logging::g_bInitialized = false;
cpp11::shared_ptr<_Logging> _Logging::g_shared = nullPtr;

#if (defined(_DEBUG) || defined(DEBUG)) && !defined(NDEBUG)
static const char* kDefaultLoggingSeverity = kRTCLoggingSeverityInfo;
#else
static const char* kDefaultLoggingSeverity = kRTCLoggingSeverityError;
#endif

_Logging::_Logging()
{
	m_sink = cpp11::shared_ptr<_LogSink>(new _LogSink());
	setSeverity(kDefaultLoggingSeverity);
}

_Logging::~_Logging()
{
	rtc::LogMessage::RemoveLogToStream(m_sink.get());
	m_sink = nullPtr;
}

bool _Logging::initialize()
{
	if (!g_bInitialized) {
		// Create shared logging object
		g_shared = cpp11::shared_ptr<_Logging>(new _Logging());

		// Remove old logging files
		_LoggingFiles::RemoveOldLogFiles();

		g_bInitialized = (g_shared != NULL);
	}
	return g_bInitialized;
}

bool _Logging::deInitialize()
{
	g_shared = nullPtr;
	g_bInitialized = false;
	return true;
}

bool _Logging::setSeverity(const char* severity)
{
	rtc::LogMessage::RemoveLogToStream(m_sink.get());

	if (std::string(kRTCLoggingSeverityError) == severity) {
		rtc::LogMessage::AddLogToStream(m_sink.get(), rtc::LoggingSeverity::LS_ERROR);
		m_Severity = (int)rtc::LoggingSeverity::LS_ERROR;
	}
	else if (std::string(kRTCLoggingSeverityWarning) == severity) {
		rtc::LogMessage::AddLogToStream(m_sink.get(), rtc::LoggingSeverity::LS_WARNING);
		m_Severity = (int)rtc::LoggingSeverity::LS_WARNING;
	}
	else if (std::string(kRTCLoggingSeverityInfo) == severity) {
		rtc::LogMessage::AddLogToStream(m_sink.get(), rtc::LoggingSeverity::LS_INFO);
		m_Severity = (int)rtc::LoggingSeverity::LS_INFO;
	}
	else {
		return false;
	}
	return true;
}

const char* _Logging::getSeverity()
{
	switch (m_Severity)
	{
	case (int)rtc::LoggingSeverity::LS_ERROR: return kRTCLoggingSeverityError;
	case (int)rtc::LoggingSeverity::LS_WARNING: return kRTCLoggingSeverityWarning;
	case (int)rtc::LoggingSeverity::LS_INFO: return kRTCLoggingSeverityInfo;
	default: return NULL;
	}
}

bool _Logging::logFunctionCall(const char* functionName)
{
	if (functionName) {
		if (m_Severity <= (int)rtc::LoggingSeverity::LS_INFO) {
			std::string message = std::string("FCall: ") + std::string(functionName);
			return logInfo(message.c_str());
		}
		return true;
	}
	return false;
}

bool _Logging::logInfo(const char* message)
{
	if (message) {
		if (m_Severity <= (int)rtc::LoggingSeverity::LS_INFO) {
			return m_sink->logMessage(std::string(message) + std::string("\n"));
		}
		return true;
	}
	return false;
}

bool _Logging::logWarn(const char* message)
{
	if (message) {
		if (m_Severity <= (int)rtc::LoggingSeverity::LS_WARNING) {
			return m_sink->logMessage(std::string(message) + std::string("\n"));
		}
		return true;
	}
	return false;
}

bool _Logging::logError(const char* message)
{
	if (message) {
		if (m_Severity <= (int)rtc::LoggingSeverity::LS_ERROR) {
			return m_sink->logMessage(std::string(message) + std::string("\n"));
		}
		return true;
	}
	return false;
}
