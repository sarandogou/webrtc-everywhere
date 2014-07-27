/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#include "_Utils.h"
#include "_RTCDisplay.h"
#include "_AsyncEvent.h"
#include "_Debug.h"
#include "_Common.h"

#if WE_UNDER_WINDOWS
#	include "windows.h"
#	include <comutil.h>
#	include "talk/base/win32socketinit.h"
# elif WE_UNDER_MAC
#	include "talk/base/maccocoasocketserver.h"
#endif

#include "talk/base/ssladapter.h"
#include "talk/base/thread.h"

static bool g_bInitialized = false;
#if WE_UNDER_WINDOWS
static bool g_winCoInitialize = false;
#endif

webrtc::CriticalSectionWrapper* _Utils::s_unique_objs_cs = webrtc::CriticalSectionWrapper::CreateCriticalSection();
std::map<long, const _UniqueObject*> _Utils::s_unique_objs;

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

	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x, rgb32_ptr+=4, bmp_ptr+=4) {
#if 0
			((uint32_t*)bmp_ptr)[0] = ((uint32_t*)rgb32_ptr)[0];
#else
			bmp_ptr[0] = rgb32_ptr[0], bmp_ptr[1] = rgb32_ptr[1], bmp_ptr[2] = rgb32_ptr[2], bmp_ptr[3] = rgb32_ptr[3];
#endif
		}
#if 0
		for (size_t a = 0; a < align; ++a) {
			*bmp_ptr++ = 0;
		}
#else
		bmp_ptr += align;
#endif
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