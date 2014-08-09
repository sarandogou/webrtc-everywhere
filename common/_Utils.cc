/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#include "_Utils.h"
#include "_RTCDisplay.h"
#include "_AsyncEvent.h"
#include "_Buffer.h"
#include "_Debug.h"
#include "_EncryptCtx.h"
#include "_Common.h"

#if WE_UNDER_WINDOWS
#	include <windows.h>
#	include <comutil.h>
#	include <shlwapi.h>
#	include <shlobj.h>
#	include <AtlConv.h>
#	include "talk/base/win32socketinit.h"
#	include "resource.h"
# elif WE_UNDER_MAC
#	include "talk/base/maccocoasocketserver.h"
#   import <CoreFoundation/CoreFoundation.h>
#endif

#ifdef _MSC_VER
#pragma comment(lib,"shlwapi.lib")
#endif

#include "talk/base/ssladapter.h"
#include "talk/base/thread.h"
#include "talk/base/json.h"

static bool g_bInitialized = false;
#if WE_UNDER_WINDOWS
static bool g_winCoInitialize = false;
#endif

webrtc::CriticalSectionWrapper* _Utils::s_unique_objs_cs = webrtc::CriticalSectionWrapper::CreateCriticalSection();
std::map<long, const _UniqueObject*> _Utils::s_unique_objs;
_FTIME _Utils::s_time_config_modif = { 0 };
cpp11::shared_ptr<_EncryptCtx> _Utils::s_encrypt_ctx = nullPtr;


_Utils::_Utils()
{

}

_Utils::~_Utils()
{

}

WeError _Utils::Initialize(WeError(*InitializeAdditionals) (void) /*= NULL*/)
{
    if(!g_bInitialized) {
#if 0
        StartDebug();
#endif

#if WE_UNDER_WINDOWS
		HRESULT hr = E_FAIL; // CoInitializeEx(NULL, COINIT_MULTITHREADED);
		g_winCoInitialize = SUCCEEDED(hr);
		talk_base::EnsureWinsockInit();
#if 0
		static talk_base::Thread w32_thread;
		talk_base::ThreadManager::Instance()->SetCurrentThread(&w32_thread);
#endif
#endif
        
#if WE_UNDER_MAC
#if 0 // NOT_USING_MAC_SERVER
        static talk_base::MacCocoaSocketServer ss;
        static talk_base::SocketServerScope ss_scope(&ss);
#endif
#endif
        
		talk_base::InitializeSSL();
		talk_base::InitializeSSLThread();
        
        s_encrypt_ctx = cpp11::shared_ptr<_EncryptCtx>(new _EncryptCtx());

        g_bInitialized = true;
    }
	if (InitializeAdditionals) {
		return InitializeAdditionals();
	}
    return WeError_Success;
}

WeError _Utils::DeInitialize(void)
{
	if (g_bInitialized) {
		talk_base::CleanupSSL();
		g_bInitialized = false;
#if WE_UNDER_WINDOWS
		if (g_winCoInitialize) {
			CoUninitialize();
		}
#endif
	}
	return WeError_Success;
}

WeError _Utils::StartDebug(void)
{
#if WE_UNDER_WINDOWS
    if (AllocConsole()) {
        freopen("CONIN$", "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
        SetConsoleTitleA("WebRTC extension for Safari, Opera, FireFox and IE");
        return WeError_Success;
    }
    return WeError_OutOfMemory;
#else
    return WeError_Success;
#endif
}

WeError _Utils::StopDebug(void)
{
#if WE_UNDER_WINDOWS
    return (FreeConsole() == TRUE) ? WeError_Success : WeError_System;
#else
    return WeError_Success;
#endif
}

std::string _Utils::ToString(long val)
{
	char str[22];
	sprintf(str, "%ld", val);
	return std::string(str);
}

class _NPAsyncData {
public:
	_NPAsyncData(HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
		: hWnd(_hWnd)
		, uMsg(_uMsg)
		, wParam(_wParam)
		, lParam(_lParam)
	{}
	HWND hWnd;
	UINT uMsg;
	WPARAM wParam;
	LPARAM lParam;
};
static void _NPWndProc(void *npdata)
{
	_NPAsyncData* _npdata = reinterpret_cast<_NPAsyncData*>(npdata);
	_Utils::WndProc(_npdata->hWnd, _npdata->uMsg, _npdata->wParam, _npdata->lParam);
	delete _npdata;
}

bool _Utils::RaiseCallback(LONGLONG handle, _BrowserCallback* cb)
{
	if (!cb) {
		return false;
	}
	HWND hWnd = reinterpret_cast<HWND>(handle);
	bool ret = false;
	
	// retain() callback object
	cb->RetainObject();

#if WE_UNDER_WINDOWS
	if (hWnd) {
		ret = (PostMessage(hWnd, cb->GetMsgId(), reinterpret_cast<WPARAM>(cb), NULL) == TRUE);
	}
	else {
		WE_DEBUG_WARN("Not handle associated to the window yet");
		_Utils::WndProc(hWnd, cb->GetMsgId(), reinterpret_cast<WPARAM>(cb), NULL);
		ret = true;
	}
#elif WE_UNDER_APPLE
	_NPAsyncData* _npdata = new _NPAsyncData(hWnd, cb->GetMsgId(), reinterpret_cast<WPARAM>(cb), NULL);
	if (_npdata) {
		dispatch_async(dispatch_get_main_queue(), ^{
			_NPWndProc(_npdata);
		});
		ret = true;
	}
#else
#error "Not implemented"
#endif

	// release() callback object
	if (ret) {
		// all is ok -> object will be freed by the async functin
	}
	else {
		cb->ReleaseObject();
	}
	return ret;
}

LRESULT CALLBACK _Utils::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
#if		WE_UNDER_WINDOWS
		case WM_ERASEBKGND:
		{
			return TRUE; // avoid background erasing.
		}
		case WM_PAINT:
		{
			_RTCDisplay* display = dynamic_cast<_RTCDisplay*>(reinterpret_cast<_RTCDisplay*>(GetWindowLongPtr(hWnd, GWLP_USERDATA)));
			if (display && display->PaintFrame()) {
				return 0;
			}
			else {
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);

				RECT rc;
				GetClientRect(hWnd, &rc);
				// Set Clip region to the rectangle specified by di.prcBounds
				HRGN hRgnOld = NULL;
				if (GetClipRgn(hdc, hRgnOld) != 1) {
					hRgnOld = NULL;
				}
				bool bSelectOldRgn = false;

				HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

				if (hRgnNew != NULL) {
					bSelectOldRgn = (SelectClipRgn(hdc, hRgnNew) != ERROR);
				}

				Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
				SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
				LPCTSTR pszText = TEXT("ATL 8.0 : WebRTC Plugin");
#ifndef _WIN32_WCE
				TextOut(hdc,
					(rc.left + rc.right) / 2,
					(rc.top + rc.bottom) / 2,
					pszText,
					lstrlen(pszText));
#else
				ExtTextOut(hdc,
					(rc.left + rc.right) / 2,
					(rc.top + rc.bottom) / 2,
					ETO_OPAQUE,
					NULL,
					pszText,
					ATL::lstrlen(pszText),
					NULL);
#endif

				if (bSelectOldRgn) {
					SelectClipRgn(hdc, hRgnOld);
				}

				EndPaint(hWnd, &ps);
			}
			break;
		}
#endif /* WE_UNDER_WINDOWS */

		case WM_SUCCESS:
		case WM_ERROR:
		case WM_GETUSERMEDIA_SUCESS:
		case WM_GETUSERMEDIA_ERROR:
		case WM_CREATEOFFER_SUCCESS:
		case WM_CREATEOFFER_ERROR:
		case WM_ONNEGOTIATIONNEEDED:
		case WM_ONICECANDIDATE:
		case WM_ONSIGNALINGSTATECHANGE:
		case WM_ONADDSTREAM:
		case WM_ONREMOVESTREAM:
		case WM_ONICECONNECTIONSTATECHANGE:
		{
			_BrowserCallback* _cb = reinterpret_cast<_BrowserCallback*>(wParam);
			if (_cb) {
				_cb->Invoke();
				_cb->ReleaseObject();
			}
			break;
		}
	}

#if WE_UNDER_WINDOWS
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
#else
	return 0;
#endif /* WE_UNDER_WINDOWS */
}

long _Utils::UniqueId()
{
    static long __unique_id = 1;
    
    _Utils::s_unique_objs_cs->Enter();
    long _id = __unique_id++;
    _Utils::s_unique_objs_cs->Leave();
    
    return _id;
}

const _UniqueObject* _Utils::UniqueObjFind(long id)
{
    const _UniqueObject* obj = NULL;
    _Utils::s_unique_objs_cs->Enter();
    std::map<long, const _UniqueObject*>::iterator it = _Utils::s_unique_objs.find(id);
    if (it != _Utils::s_unique_objs.end()) {
        obj = (*it).second;
    }
    _Utils::s_unique_objs_cs->Leave();
    return obj;
}

void _Utils::UniqueObjAdd(const _UniqueObject* obj)
{
    _Utils::s_unique_objs_cs->Enter();
    if (obj) {
        _Utils::s_unique_objs[obj->UniqueId()] = obj;
    }
    _Utils::s_unique_objs_cs->Leave();
}

void _Utils::UniqueObjRemove(long id)
{
    _Utils::s_unique_objs_cs->Enter();
    _Utils::s_unique_objs.erase(id);
    _Utils::s_unique_objs_cs->Leave();
}

int _Utils::ArrayBytesCount(_ArrayType arrayType)
{
	switch (arrayType) {
	case _ArrayType_Int8Array:
	case _ArrayType_Uint8Array:
	case _ArrayType_Uint8ClampedArray:
		return 1;
	case _ArrayType_Int16Array:
	case _ArrayType_Uint16Array:
		return 2;
	case _ArrayType_Int32Array:
	case _ArrayType_Uint32Array:
	case _ArrayType_Float32Array:
		return 4;
	case _ArrayType_Float64Array:
		return 8;
	default:
		return -1;
	}
}

bool _Utils::ArrayIsFloatingPoint(_ArrayType arrayType)
{
	switch (arrayType) {
	case _ArrayType_Int8Array:
	case _ArrayType_Uint8Array:
	case _ArrayType_Uint8ClampedArray:
	case _ArrayType_Int16Array:
	case _ArrayType_Uint16Array:
	case _ArrayType_Int32Array:
	case _ArrayType_Uint32Array:
	default:
		return false;
	case _ArrayType_Float32Array:
	case _ArrayType_Float64Array:
		return true;
	}
}

cpp11::shared_ptr<_File> _Utils::FileConfigGet(bool write /*= false*/)
{
	cpp11::shared_ptr<_File> file_config;
#if WE_UNDER_WINDOWS
	// http ://support.microsoft.com/kb/310294
	TCHAR szPath[MAX_PATH];
	// Get path for each computer, non-user specific and non-roaming data.
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, szPath))) {
		// Append product-specific path - this path needs to already exist
		// for GetTempFileName to succeed.
		PathAppend(szPath, _T("\\Doubango Telecom\\webrtc-everywhere\\"));
		if (SUCCEEDED(SHCreateDirectoryEx(NULL, szPath, NULL))) {
			PathAppend(szPath, _T("\\config.json"));
			file_config = cpp11::shared_ptr<_File>(new _File(szPath, write));
		}
	}
#elif WE_UNDER_APPLE
    NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
	NSString *documentsDir = [[documentPaths objectAtIndex:0] stringByAppendingPathComponent:@"webrtc-everywhere"];
    NSString *configPath = [documentsDir stringByAppendingPathComponent:@"config.json"];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    BOOL isDirectory = NO;
	BOOL exists = [fileManager fileExistsAtPath:documentsDir isDirectory:&isDirectory];
	if(!exists){
        NSError* error = nil;
		BOOL created = [fileManager createDirectoryAtPath:documentsDir withIntermediateDirectories:YES attributes:nil error:&error];
		if(!created){
			NSLog(@"Failed to create folder (%@) to the file system: %@", documentsDir, error);
			return nullPtr;
		}
	}
    
    file_config = cpp11::shared_ptr<_File>(new _File((const char*)[configPath UTF8String], write));
#else
#error "Not implemented"
#endif

	return file_config;
}

WeError _Utils::FileConfigGetKeyAndIV(const unsigned char* &key_ptr, size_t &key_size, const unsigned char* &iv_ptr, size_t &iv_size)
{
#if defined(WE_CONFIG_CRYPT_KEY) && defined(WE_CONFIG_CRYPT_IV)
	static unsigned char *__key = NULL;
	static size_t __key_size = 0;
	static unsigned char *__iv = NULL;
	static size_t __iv_size = 0;
	if (!__key || !__iv) {
		size_t key_len = we_strlen((const char*)WE_CONFIG_CRYPT_KEY);
		size_t iv_len = we_strlen((const char*)WE_CONFIG_CRYPT_IV);
		if (!key_len || (key_len & 1) || !iv_len || (iv_len & 1)) {
			WE_DEBUG_ERROR("Crypto:key:iv not length (%zu:%zu)", key_len, iv_len);
			return WeError_System;
		}
		if (!__key) {
			__key_size = key_len >> 1;
			__key = (unsigned char *)malloc(__key_size);
			if (!__key) {
				WE_DEBUG_ERROR("failed to alloc memory with size = %zu", __key_size);
				return WeError_OutOfMemory;
			}
			const char* ptr = (const char*)WE_CONFIG_CRYPT_KEY;
            unsigned int u;
			for (size_t i = 0; i < key_len; i+=2) {
                u = __key[i >> 1];
				sscanf(&ptr[i], "%2x", &u);
			}
		}
		if (!__iv) {
			__iv_size = iv_len >> 1;
			__iv = (unsigned char *)malloc(__iv_size);
			if (!__iv) {
				WE_DEBUG_ERROR("failed to alloc memory with size = %zu", __iv_size);
				return WeError_OutOfMemory;
			}
			const char* ptr = (const char*)WE_CONFIG_CRYPT_KEY;
            unsigned int u;
			for (size_t i = 0; i < iv_len; i += 2) {
                u = __key[i >> 1];
				sscanf(&ptr[i], "%2x", &u);
			}
		}
	}
	key_ptr = __key;
	key_size = __key_size;
	iv_ptr = __iv;
	iv_size = __iv_size;
	return WeError_Success;
#else
    static const unsigned char g_Key[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	static const unsigned char g_IV[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    
	key_ptr = g_Key;
	key_size = sizeof(g_Key);
	iv_ptr = g_IV;
	iv_size = sizeof(g_IV);
	return WeError_Success;
#endif
}

WeError _Utils::FileConfigChanged(cpp11::shared_ptr<_File> file, bool &changed)
{
	changed = true;
	if (file) {
		_FTIME time;
		if (file->GetModificationTime(&time)) {
			changed = (time.dwHighDateTime != s_time_config_modif.dwHighDateTime || time.dwLowDateTime != s_time_config_modif.dwLowDateTime);
			return WeError_Success;
		}
	}
	return WeError_System;
} 

WeError _Utils::FileConfigTrustedWebsiteAdd(const char* protocol, const char* host)
{
	WeError err;
	if (!protocol || !host || (we_stricmp(protocol, "https:") && we_stricmp(protocol, "https"))) {
		WE_DEBUG_ERROR("Invalid parameter");
		return WeError_InvalidArgument;
	}

	cpp11::shared_ptr<_File> file = _Utils::FileConfigGet(true);
	if (!file) {
		WE_DEBUG_ERROR("Failed to get configuration file");
		return  WeError_System;
	}

	// inter-process lock file for writing
	_FileInterProcessLock interProcessLock(file, true);

	cpp11::shared_ptr<_Buffer> enc_data = file->Read();
	cpp11::shared_ptr<_Buffer> dec_data;
	Json::Reader reader;
	Json::Value configuration;

	if (enc_data && enc_data->getPtr() && enc_data->getSize()) {
		err = s_encrypt_ctx->Decrypt(enc_data, dec_data);
		if (err == WeError_Success) {
			if (!(reader.parse((const char*)dec_data->getPtr(), ((const char*)dec_data->getPtr() + dec_data->getSize()), configuration))) {
				WE_DEBUG_ERROR("Invalid JSON content:%.*s", (int)dec_data->getSize(), (const char*)dec_data->getPtr());
				// return WeError_InvalidJsonContent; /* do not exit -> override the content */
			}
		}
		else; // probably trying to use wrong key -> overwrite the existing content
	}

	Json::Value trustedWebsites = configuration["trusted_websites"];
	if (!trustedWebsites.isNull() && !trustedWebsites.isArray()) {
		WE_DEBUG_ERROR("Unexpected JSON content");
		assert(0);
		return WeError_InvalidJsonContent; // must never happen
	}
	Json::Value entry;

	Json::ArrayIndex size = trustedWebsites.size();
	for (Json::ArrayIndex i = 0; i < size; ++i) {
		entry = trustedWebsites[i];
		if (entry.isObject() && entry["protocol"].isString() && entry["host"].isString()) {
			if (!we_stricmp(entry["protocol"].asString().c_str(), protocol) && !we_stricmp(entry["host"].asString().c_str(), host)) {
				return WeError_Success;
			}
		}
	}
	
	entry["protocol"] = std::string(protocol);
	entry["host"] = std::string(host);
	trustedWebsites.append(entry);
	configuration["trusted_websites"] = trustedWebsites;

	Json::StyledWriter writer;
	std::string output = writer.write(configuration);
	if (!output.empty()) {
		dec_data = cpp11::shared_ptr<_Buffer>(new _Buffer(output.c_str(), output.length()));
		err = s_encrypt_ctx->Encrypt(dec_data, enc_data);
		if (err) {
			return err;
		}
		if (!file->Write(enc_data, false/*overwrite existing content*/)) {
			return  WeError_System;
		}
	}
	file->GetModificationTime(&s_time_config_modif);

	return WeError_Success;
}

WeError _Utils::FileConfigTrustedWebsiteExist(const char* protocol, const char* host, bool &exists)
{
	exists = false;
	if (!protocol || !host) {
		WE_DEBUG_ERROR("Invalid parameter");
		return WeError_InvalidArgument;
	}

	cpp11::shared_ptr<_File> file = _Utils::FileConfigGet(false);
	if (!file) {
		WE_DEBUG_ERROR("Failed to get configuration file");
		return  WeError_System;
	}

	// inter-process lock file for reading
	_FileInterProcessLock interProcessLock(file, false);

	cpp11::shared_ptr<_Buffer> enc_data = file->Read();
	Json::Reader reader;
	Json::Value configuration;

	if (enc_data && enc_data->getPtr() && enc_data->getSize()) {
		cpp11::shared_ptr<_Buffer> dec_data;
		WeError err = s_encrypt_ctx->Decrypt(enc_data, dec_data);
		if (err) {
			return err;
		}
        std::string json_data = std::string((const char*)dec_data->getPtr(), dec_data->getSize());
		if ((reader.parse(json_data, configuration))) {
			Json::Value trustedWebsites = configuration["trusted_websites"];
			if (trustedWebsites.isArray()) {
				Json::Value entry;
				Json::ArrayIndex size = trustedWebsites.size();
				for (Json::ArrayIndex i = 0; i < size && !exists; ++i) {
					entry = trustedWebsites[i];
					if (entry.isObject() && entry["protocol"].isString() && entry["host"].isString()) {
						if (!we_stricmp(entry["protocol"].asString().c_str(), protocol) && !we_stricmp(entry["host"].asString().c_str(), host)) {
							exists = true;
						}
					}
				}
			}
		}
	}
	return WeError_Success;
}

//!\ Up to the caller to free the returned buffer ("out_pptr")
WeError _Utils::ConvertToBase64(const void* _in_ptr, size_t in_size, void **out_pptr, size_t *out_size_ptr, void* (*MemAllocFn)(size_t n) /*= NULL*/)
{
	if (!_in_ptr || !in_size || !out_pptr || *out_pptr || !out_size_ptr) {
		WE_DEBUG_ERROR("Invalid parameter");
		return WeError_InvalidArgument;
	}
	// Copyright(C) Doubango Telecom - tinySAK project
	static const char* kBase64EncodeAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
#define TSK_BASE64_ENCODE_LEN(IN_LEN)		((2 + (IN_LEN) - (((IN_LEN) + 2) % 3)) * 4 / 3)
#define TSK_BASE64_DECODE_LEN(IN_LEN)		(((IN_LEN * 3)/4) + 2)
	/** Pad char.*/
#define TSK_BASE64_PAD '='

	/** Encoding block size. */
#define TSK_BASE64_ENCODE_BLOCK_SIZE	3 /* 24-bit input group */
	/** Decoding block size. */
#define TSK_BASE64_DECODE_BLOCK_SIZE	4

	/*==================================================================
	Value Encoding  Value Encoding  Value Encoding  Value Encoding
	0 A            17 R            34 i            51 z
	1 B            18 S            35 j            52 0
	2 C            19 T            36 k            53 1
	3 D            20 U            37 l            54 2
	4 E            21 V            38 m            55 3
	5 F            22 W            39 n            56 4
	6 G            23 X            40 o            57 5
	7 H            24 Y            41 p            58 6
	8 I            25 Z            42 q            59 7
	9 J            26 a            43 r            60 8
	10 K            27 b            44 s            61 9
	11 L            28 c            45 t            62 +
	12 M            29 d            46 u            63 /
	13 N            30 e            47 v
	14 O            31 f            48 w         (pad) =
	15 P            32 g            49 x
	16 Q            33 h            50 y

	RFC 4548 - Table 1: The Base 64 Alphabet
	*/

	/*=================================================================================
	content					T					S					K
	ASCII					0x54				0x53				0x4B
	Binary					0101 0100			0101 0011			0100 1011
	------------------------------------------------------------------------------
	------------------------------------------------------------------------------
	Packs of 6bits			010101			000101			001101			001011
	Indexes					21				5				13				11
	Base64 encoded			V				F				N				L			<=== HERE IS THE RESULT OF tsk_base64_encode("TSK")
	*/

	size_t i = 0;
	size_t output_size = 0;

	*out_size_ptr = TSK_BASE64_ENCODE_LEN(in_size);
	if (MemAllocFn) {
		*out_pptr = MemAllocFn((*out_size_ptr) + 1);
		memset(*out_pptr, 0, (*out_size_ptr) + 1);
	}
	else {
		*out_pptr = calloc((*out_size_ptr) + 1, sizeof(uint8_t));
	}
	if (!*out_pptr) {
		WE_DEBUG_ERROR("failed to malloc buffer");
		return WeError_OutOfMemory;
	}
	uint8_t* out_ptr = (uint8_t*)*out_pptr;
	const uint8_t* in_ptr = (const uint8_t*)_in_ptr;

	/* Too short? */
	if (in_size < TSK_BASE64_ENCODE_BLOCK_SIZE) {
		goto quantum;
	}

	do {
		out_ptr[output_size++] = kBase64EncodeAlphabet[(in_ptr[i] >> 2) & 0x3F];
		out_ptr[output_size++] = kBase64EncodeAlphabet[((in_ptr[i] << 4) | (in_ptr[i + 1] >> 4)) & 0x3F];
		out_ptr[output_size++] = kBase64EncodeAlphabet[((in_ptr[i + 1] << 2) | (in_ptr[i + 2] >> 6)) & 0x3F];
		out_ptr[output_size++] = kBase64EncodeAlphabet[in_ptr[i + 2] & 0x3F];

		i += TSK_BASE64_ENCODE_BLOCK_SIZE;
	} while ((i + TSK_BASE64_ENCODE_BLOCK_SIZE) <= in_size);

quantum:

	if ((in_size - i) == 1) {
		/* The final quantum of encoding input is exactly 8 bits; here, the
		final unit of encoded output will be two characters followed by
		two "=" padding characters.
		*/
		out_ptr[output_size++] = kBase64EncodeAlphabet[(in_ptr[i] >> 2) & 0x3F];
		out_ptr[output_size++] = kBase64EncodeAlphabet[(in_ptr[i] << 4) & 0x3F];
		out_ptr[output_size++] = TSK_BASE64_PAD, *(out_ptr + output_size++) = TSK_BASE64_PAD;
	}
	else if ((in_size - i) == 2) {
		/*	The final quantum of encoding input is exactly 16 bits; here, the
		final unit of encoded output will be three characters followed by
		one "=" padding character.
		*/
		out_ptr[output_size++] = kBase64EncodeAlphabet[(in_ptr[i] >> 2) & 0x3F];
		out_ptr[output_size++] = kBase64EncodeAlphabet[((in_ptr[i] << 4) | (in_ptr[i + 1] >> 4)) & 0x3F];
		out_ptr[output_size++] = kBase64EncodeAlphabet[((in_ptr[i + 1] << 2) | (in_ptr[i + 2] >> 6)) & 0x3F];
		out_ptr[output_size++] = TSK_BASE64_PAD;
	}

	*out_size_ptr = output_size;
	return WeError_Success; 
}



//!\ Up to the caller to free the returned buffer ("bmp_ptr")
WeError _Utils::ConvertToBMP(const void* _rgb32_ptr, size_t width, size_t height, void** bmp_pptr, size_t *bmp_size_ptr)
{
	// http://en.wikipedia.org/wiki/BMP_file_format
#if WE_UNDER_WINDOWS
	typedef BITMAPFILEHEADER BMPFILEHEADER;
	typedef BITMAPINFOHEADER BMPINFOHEADER;
#else
#if defined (__GNUC__)
#	define WE_PACKED __attribute__((__packed__))
#else
#	define WE_PACKED
#endif
#if defined(_MSC_VER)
#pragma pack( push )
#pragma pack( 2 )
#endif
	typedef struct WE_PACKED tagBMPINFOHEADER{
		uint32_t      biSize;
		long       biWidth;
		long       biHeight;
		uint16_t       biPlanes;
		uint16_t       biBitCount;
		uint32_t      biCompression;
		uint32_t      biSizeImage;
		long       biXPelsPerMeter;
		long       biYPelsPerMeter;
		uint32_t      biClrUsed;
		uint32_t      biClrImportant;
	} BMPINFOHEADER;

	typedef struct WE_PACKED tagBMPFILEHEADER {
		uint16_t    bfType;
		uint32_t   bfSize;
		uint16_t    bfReserved1;
		uint16_t    bfReserved2;
		uint32_t   bfOffBits;
	} BMPFILEHEADER;
#if defined(_MSC_VER)
#pragma pack( pop )
#endif
#endif
	if (!_rgb32_ptr || !width || !height || !bmp_pptr || *bmp_pptr || !bmp_size_ptr) {
		WE_DEBUG_ERROR("Invalid parameter");
		return WeError_InvalidArgument;
	}

	BMPFILEHEADER hdr_file;
	BMPINFOHEADER hdr_info;

	size_t align = (((width << 2) ^ 0x03) + 1) & 0x03;
	size_t stride = (width << 2) + align;

	*bmp_size_ptr = sizeof(BMPFILEHEADER) + sizeof(BMPINFOHEADER) + (stride * height);
	*bmp_pptr = calloc(*bmp_size_ptr, sizeof(uint8_t));
	if (!*bmp_pptr) {
		WE_DEBUG_ERROR("failed to malloc buffer");
		return WeError_OutOfMemory;
	}
	uint8_t* bmp_ptr = (uint8_t*)*bmp_pptr;
	const uint8_t* rgb32_ptr = (const uint8_t*)_rgb32_ptr;

	memset(&hdr_info, 0, sizeof(hdr_info));
	memset(&hdr_file, 0, sizeof(hdr_file));

	
#if !defined (BI_RGB)
#	define BI_RGB 0L
#endif
	
	hdr_file.bfSize = *bmp_size_ptr;
	hdr_file.bfOffBits = sizeof(BMPFILEHEADER) + sizeof(BMPINFOHEADER);

	hdr_info.biSize = sizeof(BMPINFOHEADER);
	hdr_file.bfType = 0x4D42;
	hdr_info.biWidth = width;
	hdr_info.biHeight = height;
	hdr_info.biXPelsPerMeter = 0;
	hdr_info.biYPelsPerMeter = 0;
	hdr_info.biPlanes = 1;
	hdr_info.biBitCount = 32;
	hdr_info.biCompression = BI_RGB;
	hdr_info.biSizeImage = stride * height;
	hdr_info.biClrImportant = 0;
	hdr_info.biClrUsed = 0;
#if WE_UNDER_WINDOWS || WE_UNDER_APPLE
	hdr_info.biHeight *= -1;
#endif

	memcpy(bmp_ptr, &hdr_file, sizeof(BMPFILEHEADER)), bmp_ptr += sizeof(BMPFILEHEADER);
	memcpy(bmp_ptr, &hdr_info, sizeof(BMPINFOHEADER)), bmp_ptr += sizeof(BMPINFOHEADER);

	if (align == 0) {
		memcpy(bmp_ptr, rgb32_ptr, (width << 2) * height);
	}
	else {
		for (size_t y = 0; y < height; ++y) {
			memcpy(bmp_ptr, rgb32_ptr, (width << 2));
			bmp_ptr += (width << 2) + align;
			rgb32_ptr += (width << 2);
		}
	}

#if 0
	FILE* file = fopen("C:\\Projects\\webrtc-everywhere\\screenshot.png", "wb");
	if (file) {
		fwrite(*bmp_pptr, 1, *bmp_size_ptr, file);
		fclose(file);
	}
#endif

	return WeError_Success;
}

#if WE_UNDER_WINDOWS
static INT_PTR CALLBACK GUMDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
		case WM_INITDIALOG:
		{
			return TRUE;
		}
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDOK:
				{
					EndDialog(hwnd, IDOK);
					break;
				}
				case IDCANCEL:
				{
					EndDialog(hwnd, IDCANCEL);
					break;
				}
			}
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

HRESULT _Utils::MsgBoxGUMA(bool &accepted, const char* protocol, const char* host, HWND hwndParent /*= NULL*/)
{
	USES_CONVERSION;
	return _Utils::MsgBoxGUM(accepted, A2T(protocol), A2T(host), hwndParent);
}

HRESULT _Utils::MsgBoxGUM(bool &accepted, const TCHAR* protocol, const TCHAR* host, HWND hwndParent /*= NULL*/)
{
	static const TCHAR __title_ptr[] = _T("Media permission");
	static const TCHAR __msg_ptr[] = _T(" would like to access your microphone and/or camera.");
	static const size_t __msg_size = sizeof(__msg_ptr) + 1;
	static const TCHAR __location_ptr[] = _T("This website");
	static const size_t __location_size = sizeof(__location_ptr) + 1;
	static const size_t __TCHAR_size = sizeof(TCHAR);
	static const TCHAR __protocol_ptr[] = _T("http:");
	static const TCHAR __host_ptr[] = _T("local");

	if (!host || !wcslen(host)) { // local file -> host = null
		host = __host_ptr;
	}
	if (!protocol || !wcslen(protocol)) { // local file -> protocol = null
		protocol = __protocol_ptr;
	}


	if (!protocol || !host || !wcslen(protocol) || !wcslen(host)) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}

#if 0
	if (!location || !wcslen(location)) {
		location = __location_ptr;
	}
#endif

	char *_protocol = _com_util::ConvertBSTRToString(CComBSTR(protocol));
	char *_host = _com_util::ConvertBSTRToString(CComBSTR(host));

	accepted = false;
	_Utils::FileConfigTrustedWebsiteExist(_protocol, _host, accepted);

	if (!accepted) {
		size_t msg_len = __msg_size + (wcslen(host) * __TCHAR_size) + 1;
		TCHAR* msg = new TCHAR[msg_len];
		if (!msg) {
			CHECK_HR_RETURN(E_OUTOFMEMORY);
		}
		memset(msg, 0, msg_len);
		wcscpy(msg, host);
		wcscpy(&msg[wcslen(host)], __msg_ptr);
		int msgboxID = MessageBox(
			hwndParent,
			msg,
			__title_ptr,
			MB_ICONEXCLAMATION | MB_YESNO
			);
		accepted = (msgboxID == IDYES);
		delete[]msg;

		if (accepted && !wcscmp(protocol, _T("https:"))) {
			_Utils::FileConfigTrustedWebsiteAdd(_protocol, _host);
		}
	}

	if (_protocol) delete[]_protocol;
	if (_host) delete[]_host;

	return S_OK;
}
#endif // WE_UNDER_WINDOWS


#if WE_UNDER_APPLE

WeError _Utils::MsgBoxGUM(bool &accepted, const char* protocol, const char* host)
{
    accepted = false;
    
    static const char __protocol_ptr[] = "http:";
	static const char __host_ptr[] = "local";
    
	if (!we_strlen(host)) { // local file -> host = null
		host = __host_ptr;
	}
	if (!we_strlen(protocol)) { // local file -> protocol = null
		protocol = __protocol_ptr;
	}
    
    _Utils::FileConfigTrustedWebsiteExist(protocol, host, accepted);
    if (!accepted) {
        CFOptionFlags cfRes;
        CFUserNotificationDisplayAlert(0, 0/*kCFUserNotificationNoDefaultButtonFlag*/, NULL, NULL, NULL,
                                       CFSTR("Media permission"), CFStringCreateWithFormat(NULL, NULL, CFSTR("[%s] would like to access your microphone and/or camera."), host),
                                       CFSTR("Deny"), CFSTR("Allow"), NULL,
                                       &cfRes);
        switch (cfRes) {
            case kCFUserNotificationDefaultResponse:
                // Denny
                break;
            case kCFUserNotificationAlternateResponse:
                // Allow
                accepted = true;
                if (!we_stricmp(protocol, "https:")) {
                    _Utils::FileConfigTrustedWebsiteAdd(protocol, host);
                }
                break;
        }
    }
    return WeError_Success;
}

#endif // WE_UNDER_APPLE



