/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "_RTCDisplay.h"
#include "_Debug.h"

#include "talk/media/base/videocommon.h"
#include "talk/media/base/videoframe.h"

#include <algorithm>

#if WE_UNDER_WINDOWS
#include <Windows.h>
#endif

///
/// _VideoRenderer
///

_VideoRendererResources::_VideoRendererResources(int width, int height, cpp11::function<void()> fnOnStartVideoRenderer, webrtc::VideoTrackInterface* track_to_render)
: m_fnOnStartVideoRenderer(fnOnStartVideoRenderer)
#if WE_UNDER_WINDOWS
, m_Hwnd(NULL)
, m_lpUsrData(NULL)
#elif WE_UNDER_APPLE
, m_layer(NULL)
, m_context(NULL)
, m_context_buff(NULL)
, m_context_buff_size(0)
, m_group(dispatch_group_create())

#endif
, m_cs(NULL)
, m_width(width)
, m_height(height)
{
    m_rendered_track = track_to_render;
    m_cs = webrtc::CriticalSectionWrapper::CreateCriticalSection();
#if WE_UNDER_WINDOWS
    ZeroMemory(&m_bmi, sizeof(m_bmi));
    m_bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    m_bmi.bmiHeader.biPlanes = 1;
    m_bmi.bmiHeader.biBitCount = 32;
    m_bmi.bmiHeader.biCompression = BI_RGB;
    m_bmi.bmiHeader.biWidth = width;
    m_bmi.bmiHeader.biHeight = -height;
    m_bmi.bmiHeader.biSizeImage = width * height *
    (m_bmi.bmiHeader.biBitCount >> 3);
#elif WE_UNDER_APPLE
#endif
}
_VideoRendererResources::~_VideoRendererResources()
{
    m_image.reset();
    m_rendered_track = NULL;
    
    {
        
#if WE_UNDER_WINDOWS
        if (m_Hwnd) {
            InvalidateRect(m_Hwnd, NULL, TRUE);
        }
#elif WE_UNDER_APPLE
        if (m_layer) {
            m_layer.contents = NULL;
            [m_layer release], m_layer = NULL;
        }
        if (m_context) {
            CGContextRelease(m_context);
            m_context = NULL;
        }
        if (m_context_buff) {
            free(m_context_buff), m_context_buff = NULL;
        }
        m_context_buff_size = 0;
        dispatch_release(m_group);
#endif
    } // ~lock
    
    
    if (m_cs) {
        delete m_cs;
        m_cs = NULL;
    }
}


//
//	_VideoRenderer
//
_VideoRenderer::_VideoRenderer(int width, int height, cpp11::function<void()> fnOnStartVideoRenderer, webrtc::VideoTrackInterface* track_to_render)
    : m_cs(NULL)
    , resources_(new _VideoRendererResources(width, height, fnOnStartVideoRenderer, track_to_render))

{
    m_cs = webrtc::CriticalSectionWrapper::CreateCriticalSection();
	resources_->m_rendered_track->AddRenderer(this);
}

_VideoRenderer::~_VideoRenderer()
{
    if (resources_->m_rendered_track) {
        resources_->m_rendered_track->RemoveRenderer(this);
    }

    if (m_cs) {
        delete m_cs;
        m_cs = NULL;
    }
    resources_ = nullPtr;
}

#if WE_UNDER_WINDOWS
void _VideoRenderer::SetHwnd(HWND hwnd, LONG_PTR lpUsrData)
{
	_AutoLock<_VideoRenderer> lock0(this);
	_AutoLock<_VideoRendererResources> lock1(resources_.get());

	resources_->m_Hwnd = hwnd;
	resources_->m_lpUsrData = lpUsrData;
	if (hwnd)
	{
		SetWindowLongPtr(hwnd, GWLP_USERDATA, lpUsrData);
	}
}

HWND _VideoRenderer::GetHwnd()
{
	return resources_->m_Hwnd;
}

static inline LONG Width(const RECT& r)
{
	return r.right - r.left;
}

static inline LONG Height(const RECT& r)
{
	return r.bottom - r.top;
}

typedef struct _WERatio {
	DWORD Numerator;
	DWORD Denominator;
} WERatio;

//-----------------------------------------------------------------------------
// CorrectAspectRatio
//
// Converts a rectangle from the source's pixel aspect ratio (PAR) to 1:1 PAR.
// Returns the corrected rectangle.
//
// For example, a 720 x 486 rect with a PAR of 9:10, when converted to 1x1 PAR,
// is stretched to 720 x 540.
// Copyright (C) Microsoft
//-----------------------------------------------------------------------------

static inline RECT CorrectAspectRatio(const RECT& src, const WERatio& srcPAR)
{
	// Start with a rectangle the same size as src, but offset to the origin (0,0).
	RECT rc = { 0, 0, src.right - src.left, src.bottom - src.top };

	if ((srcPAR.Numerator != 1) || (srcPAR.Denominator != 1))
	{
		// Correct for the source's PAR.

		if (srcPAR.Numerator > srcPAR.Denominator)
		{
			// The source has "wide" pixels, so stretch the width.
			rc.right = MulDiv(rc.right, srcPAR.Numerator, srcPAR.Denominator);
		}
		else if (srcPAR.Numerator < srcPAR.Denominator)
		{
			// The source has "tall" pixels, so stretch the height.
			rc.bottom = MulDiv(rc.bottom, srcPAR.Denominator, srcPAR.Numerator);
		}
		// else: PAR is 1:1, which is a no-op.
	}
	return rc;
}

//-------------------------------------------------------------------
// LetterBoxDstRect
//
// Takes a src rectangle and constructs the largest possible
// destination rectangle within the specifed destination rectangle
// such thatthe video maintains its current shape.
//
// This function assumes that pels are the same shape within both the
// source and destination rectangles.
// Copyright (C) Microsoft
//-------------------------------------------------------------------

static inline RECT LetterBoxRect(const RECT& rcSrc, const RECT& rcDst)
{
	// figure out src/dest scale ratios
	int iSrcWidth = Width(rcSrc);
	int iSrcHeight = Height(rcSrc);

	int iDstWidth = Width(rcDst);
	int iDstHeight = Height(rcDst);

	int iDstLBWidth;
	int iDstLBHeight;

	if (MulDiv(iSrcWidth, iDstHeight, iSrcHeight) <= iDstWidth) {

		// Column letter boxing ("pillar box")

		iDstLBWidth = MulDiv(iDstHeight, iSrcWidth, iSrcHeight);
		iDstLBHeight = iDstHeight;
	}
	else {

		// Row letter boxing.

		iDstLBWidth = iDstWidth;
		iDstLBHeight = MulDiv(iDstWidth, iSrcHeight, iSrcWidth);
	}


	// Create a centered rectangle within the current destination rect

	RECT rc;

	LONG left = rcDst.left + ((iDstWidth - iDstLBWidth) >> 1);
	LONG top = rcDst.top + ((iDstHeight - iDstLBHeight) >> 1);

	SetRect(&rc, left, top, left + iDstLBWidth, top + iDstLBHeight);

	return rc;
}

#elif WE_UNDER_APPLE
void _VideoRenderer::SetLayer(CALayer *layer)
{
    _AutoLock<_VideoRenderer> lock0(this);
    _AutoLock<_VideoRendererResources> lock1(resources_.get());
    
    if (resources_->m_layer) {
        resources_->m_layer.contents = NULL;
        [resources_->m_layer release], resources_->m_layer = NULL;
    }
    if (layer) {
        resources_->m_layer = [layer retain];
    }
}

CALayer *_VideoRenderer::GetLayer()
{
    _AutoLock<_VideoRenderer> lock(this);
    _AutoLock<_VideoRendererResources> lock1(resources_.get());
    
    return resources_->m_layer;
}
#endif

// On Windows, must be called inside OnPaint()
// Requires valid m_Hwnd
bool _VideoRenderer::PaintFrame(intptr_t layer /*= 0*/)
{
    _AutoLock<_VideoRenderer> lock0(this);
    _AutoLock<_VideoRendererResources> lock1(resources_.get());

#if WE_UNDER_WINDOWS
    const uint8* image = resources_->m_image.get();
	ATL_DRAWINFO* drawInfo  = reinterpret_cast<ATL_DRAWINFO*>(layer);
	if ((resources_->m_Hwnd || drawInfo) && image) {
		PAINTSTRUCT ps;
		HDC hdc;
		if (resources_->m_Hwnd) {
			if (!(hdc = ::BeginPaint(resources_->m_Hwnd, &ps))) {
				return false;
			}
		}
		else {
			memset(&ps, 0, sizeof(ps));
			ps.hdc = hdc = drawInfo->hdcDraw;
		}

		RECT rc;
		if (resources_->m_Hwnd) {
			if (!::GetClientRect(resources_->m_Hwnd, &rc)) {
				::EndPaint(resources_->m_Hwnd, &ps);
				return false;
			}
		}
		else {
			rc = *(RECT*)drawInfo->prcBounds;
		}

#if WE_USE_AUTORESIZE // Flickering when resizing (in windowless mode only: https://github.com/sarandogou/webrtc-everywhere/issues/44)
		int width = resources_->m_bmi.bmiHeader.biWidth;
		int height = abs(resources_->m_bmi.bmiHeader.biHeight);

		HDC dc_mem = ::CreateCompatibleDC(ps.hdc);
		::SetStretchBltMode(dc_mem, HALFTONE);

		// Set the map mode so that the ratio will be maintained for us.
		HDC all_dc[] = { ps.hdc, dc_mem };
		for (int i = 0; i < ARRAY_SIZE(all_dc); ++i) {
			SetMapMode(all_dc[i], MM_ISOTROPIC);
			SetWindowExtEx(all_dc[i], width, height, NULL);
			SetViewportExtEx(all_dc[i], rc.right, rc.bottom, NULL);
		}

		HBITMAP bmp_mem = ::CreateCompatibleBitmap(ps.hdc, rc.right, rc.bottom);
		HGDIOBJ bmp_old = ::SelectObject(dc_mem, bmp_mem);

		POINT logical_area = { rc.right, rc.bottom };
		DPtoLP(ps.hdc, &logical_area, 1);

		HBRUSH brush = ::CreateSolidBrush(RGB(0, 0, 0));
		RECT logical_rect = { 0, 0, logical_area.x, logical_area.y };
		::FillRect(dc_mem, &logical_rect, brush);
		::DeleteObject(brush);

		int x = (logical_area.x / 2) - (width / 2);
		int y = (logical_area.y / 2) - (height / 2);

		StretchDIBits(dc_mem, x, y, width, height,
			0, 0, width, height, image, &m_bmi, DIB_RGB_COLORS, SRCCOPY);

		BitBlt(ps.hdc, 0, 0, logical_area.x, logical_area.y,
			dc_mem, 0, 0, SRCCOPY);

		// Cleanup.
		::SelectObject(dc_mem, bmp_old);
		::DeleteObject(bmp_mem);
		::DeleteDC(dc_mem);
#else /* !WE_USE_AUTORESIZE */
		static const WERatio pixelAR = { 1, 1 };
		RECT rcSrc = { 0, 0, resources_->m_bmi.bmiHeader.biWidth, abs(resources_->m_bmi.bmiHeader.biHeight) };
		rcSrc = CorrectAspectRatio(rcSrc, pixelAR);
		const RECT rcDest = LetterBoxRect(rcSrc, rc);

		HDC dc_mem = ::CreateCompatibleDC(ps.hdc);
		::SetStretchBltMode(dc_mem, HALFTONE);

		// Create offscreen bmp memory
		HBITMAP bmp_mem = ::CreateCompatibleBitmap(ps.hdc, rc.right, rc.bottom);
		HGDIOBJ bmp_old = ::SelectObject(dc_mem, bmp_mem);

		POINT logical_area = { rc.right, rc.bottom };
		DPtoLP(ps.hdc, &logical_area, 1);

		HBRUSH brush = ::CreateSolidBrush(RGB(0, 0, 0));
		RECT logical_rect = { 0, 0, logical_area.x, logical_area.y };
		::FillRect(dc_mem, &logical_rect, brush);
		::DeleteObject(brush);

		StretchDIBits(dc_mem, rcDest.left, rcDest.top, Width(rcDest), Height(rcDest),
			rcSrc.left, rcSrc.top, Width(rcSrc), Height(rcSrc), image, &resources_->m_bmi, DIB_RGB_COLORS, SRCCOPY);

		BitBlt(ps.hdc, 0, 0, logical_area.x, logical_area.y, dc_mem, 0, 0, SRCCOPY);

		// Cleanup.
		::SelectObject(dc_mem, bmp_old);
		::DeleteObject(bmp_mem);
		::DeleteDC(dc_mem);
#endif /* WE_USE_AUTORESIZE */
		
		if (resources_->m_Hwnd) {
			::EndPaint(resources_->m_Hwnd, &ps);
		}

		return true;
	}
#else
	
#endif

	return false;
}

int _VideoRenderer::GetVideoWidth()
{
	_AutoLock<_VideoRenderer> lock0(this);
    _AutoLock<_VideoRendererResources> lock1(resources_.get());

	return resources_->m_width;
}

int _VideoRenderer::GetVideoHeight()
{
	_AutoLock<_VideoRenderer> lock0(this);
    _AutoLock<_VideoRendererResources> lock1(resources_.get());

	return resources_->m_height;
}



size_t _VideoRenderer::CopyFromFrame(void* bufferPtr, size_t bufferSize)
{
	if (bufferPtr && bufferSize) {
		_AutoLock<_VideoRenderer> lock0(this);
        _AutoLock<_VideoRendererResources> lock1(resources_.get());
		size_t sizeToCopy = std::min((int)bufferSize, (resources_->m_width * resources_->m_height * 4));
		const uint8* image = resources_->m_image.get();
		if (image) {
			memcpy(bufferPtr, image, sizeToCopy);
			return sizeToCopy;
		}
	}
	return  0;
}

#if WE_UNDER_WINDOWS
void _VideoRenderer::SetFnQueryHwnd(cpp11::function<HWND()> fnQueryHwnd)
{
	_AutoLock<_VideoRenderer> lock0(this);
    _AutoLock<_VideoRendererResources> lock1(resources_.get());

	resources_->m_fnQueryHwnd = fnQueryHwnd;
}

void _VideoRenderer::SetFnIsWindowless(cpp11::function<BOOL()> fnIsWindowless)
{
	_AutoLock<_VideoRenderer> lock0(this);
    _AutoLock<_VideoRendererResources> lock1(resources_.get());

	resources_->m_fnIsWindowless = fnIsWindowless;
}

void _VideoRenderer::SetFnInvalidateWindowless(cpp11::function<HRESULT(/* [unique][in] */ __RPC__in_opt LPCRECT pRect, /* [in] */ BOOL fErase)> fnInvalidateWindowless)
{
	_AutoLock<_VideoRenderer> lock0(this);
    _AutoLock<_VideoRendererResources> lock1(resources_.get());

	resources_->m_fnInvalidateWindowless = fnInvalidateWindowless;
}

#endif /* WE_UNDER_WINDOWS */

// VideoRendererInterface implementation
void _VideoRenderer::SetSize(int width, int height)
{
	_AutoLock<_VideoRenderer> lock0(this);
    _AutoLock<_VideoRendererResources> lock1(resources_.get());
    
    resources_->m_width = width;
	resources_->m_height = height;

#if WE_UNDER_WINDOWS
	resources_->m_bmi.bmiHeader.biWidth = width;
	resources_->m_bmi.bmiHeader.biHeight = -height;
	resources_->m_bmi.bmiHeader.biSizeImage = width * height *
		(resources_->m_bmi.bmiHeader.biBitCount >> 3);
	resources_->m_image.reset(new uint8[resources_->m_bmi.bmiHeader.biSizeImage]);
	if (resources_->m_Hwnd) {
	}
#elif WE_UNDER_APPLE
    if (resources_->m_context) {
        CGContextRelease(resources_->m_context);
        resources_->m_context = NULL;
    }
    resources_->m_context_buff_size = (resources_->m_width * resources_->m_height) << 2;
    resources_->m_context_buff = realloc(resources_->m_context_buff, resources_->m_context_buff_size);
    if (!resources_->m_context_buff) {
        WE_DEBUG_ERROR("failed to allocate buffer with size = %d", resources_->m_context_buff_size);
        resources_->m_context_buff_size = 0;
        return;
    }
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    resources_->m_context = CGBitmapContextCreate(resources_->m_context_buff, resources_->m_width, resources_->m_height, 8, resources_->m_width * 4, colorSpace,
											   kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst);
    CGColorSpaceRelease(colorSpace);
    if (!resources_->m_context) {
        WE_DEBUG_ERROR("failed to create RGB32 context");
        return; // return and do not signal "video started" event
    }
    else {
        resources_->m_image.reset(new uint8[resources_->m_context_buff_size]);
        CGContextSetInterpolationQuality(resources_->m_context, kCGInterpolationMedium);
        CGContextSetShouldAntialias(resources_->m_context, true);
    }
#endif
    
	if (resources_->m_fnOnStartVideoRenderer) {
		resources_->m_fnOnStartVideoRenderer();
	}
}

// VideoRendererInterface implementation
void _VideoRenderer::RenderFrame(const cricket::VideoFrame* frame)
{
	if (!frame) {
		return;
	}
	
	_AutoLock<_VideoRenderer> lock0(this);
    _AutoLock<_VideoRendererResources> lock1(resources_.get());

	if (!resources_->m_image.get() || resources_->m_width != frame->GetWidth() || resources_->m_height != frame->GetHeight()) {
		SetSize((int)frame->GetWidth(), (int)frame->GetHeight());
		if (!resources_->m_image.get()) {
			return;
		}
    }

#if WE_UNDER_WINDOWS
	frame->ConvertToRgbBuffer(cricket::FOURCC_ARGB,
		resources_->m_image.get(),
		resources_->m_bmi.bmiHeader.biSizeImage,
		resources_->m_bmi.bmiHeader.biWidth *
		resources_->m_bmi.bmiHeader.biBitCount / 8);

	if (resources_->m_fnIsWindowless && resources_->m_fnIsWindowless()) {
		// windowless
		if (resources_->m_fnInvalidateWindowless) {
			resources_->m_fnInvalidateWindowless(NULL, TRUE);
		}
	}
	else {
		// windowed
		if (!resources_->m_Hwnd && resources_->m_fnQueryHwnd) {
			SetHwnd(resources_->m_fnQueryHwnd(), resources_->m_lpUsrData);
		}
		if (resources_->m_Hwnd) {
			InvalidateRect(resources_->m_Hwnd, NULL, TRUE);
		}
	}
#elif WE_UNDER_APPLE
    __block cpp11::shared_ptr<_VideoRendererResources> rcopy = resources_;
    if (rcopy->m_context_buff && rcopy->m_context && rcopy->m_layer) {
        frame->ConvertToRgbBuffer(cricket::FOURCC_ARGB, rcopy->m_image.get(), rcopy->m_context_buff_size, rcopy->m_width * 4);
        memcpy(rcopy->m_context_buff, rcopy->m_image.get(), rcopy->m_context_buff_size);
        
        dispatch_group_enter(rcopy->m_group);
        dispatch_group_async(rcopy->m_group, dispatch_get_main_queue(), ^{
            rcopy->Enter();
            if (rcopy->m_context_buff && rcopy->m_context && rcopy->m_layer) {
                CGImageRef image = CGBitmapContextCreateImage(rcopy->m_context);
                rcopy->m_layer.contentsGravity = kCAGravityResizeAspect;
                rcopy->m_layer.contents = (id)image;
                CGImageRelease(image);
            }
            dispatch_group_leave(rcopy->m_group);
            rcopy->Leave();
            rcopy = nullPtr;
        });
    }

#endif
}


//
//	_RTCDisplay
//

_RTCDisplay::_RTCDisplay()
{
	m_cs = webrtc::CriticalSectionWrapper::CreateCriticalSection();
}

_RTCDisplay::~_RTCDisplay()
{
	StopVideoRenderer();
    
    if (m_cs) {
        delete m_cs, m_cs = NULL;
    }
}

void _RTCDisplay::StartVideoRenderer(VideoTrackInterfacePtr video)
{
	_AutoLock<_RTCDisplay> lock(this);
	if (!video) {
		StopVideoRenderer();
		return;
	}

	webrtc::VideoTrackInterface* _v = dynamic_cast<webrtc::VideoTrackInterface*>((webrtc::VideoTrackInterface*)video);
	if (_v) {
		_VideoRenderer* _video = new _VideoRenderer(1, 1, cpp11::bind(&_RTCDisplay::OnStartVideoRenderer, this), _v);
		if (_video) {
#if WE_UNDER_WINDOWS
			_video->SetFnQueryHwnd(cpp11::bind(&_RTCDisplay::QueryHwnd, this));
			_video->SetFnIsWindowless(cpp11::bind(&_RTCDisplay::IsWindowless, this));
			_video->SetFnInvalidateWindowless(cpp11::bind(&_RTCDisplay::InvalidateWindowless, this, std::placeholders::_1, std::placeholders::_2));
			_video->SetHwnd(Handle(), reinterpret_cast<LONG_PTR>(this));
#elif WE_UNDER_APPLE
            _video->SetLayer(Layer());
#endif
			m_renderer.reset(_video);
		}
	}
}

void _RTCDisplay::StopVideoRenderer()
{
	_AutoLock<_RTCDisplay> lock(this);

#if WE_UNDER_WINDOWS
	if (m_renderer) {
		m_renderer->SetHwnd(m_renderer->GetHwnd(), NULL);
	}
#elif WE_UNDER_APPLE
    
#endif

	m_renderer.reset();
	OnStopVideoRenderer();
}


// On Windows, must be called inside OnPaint()
bool _RTCDisplay::PaintFrame(intptr_t layer /*= 0*/)
{	
	_AutoLock<_RTCDisplay> lock(this);
	
	bool ret = false;

	if (m_renderer.get()) {
		ret = m_renderer->PaintFrame(layer);
	}

	return ret;
}

int _RTCDisplay::GetVideoWidth()
{
	if (m_renderer.get()) {
		return m_renderer->GetVideoWidth();
	}
	return -1;
}

int _RTCDisplay::GetVideoHeight()
{
	_AutoLock<_RTCDisplay> lock(this);

	if (m_renderer.get()) {
		return m_renderer->GetVideoHeight();
	}
	return -1;
}

size_t _RTCDisplay::CopyFromFrame(void* bufferPtr, size_t bufferSize)
{
	_AutoLock<_RTCDisplay> lock(this);

	if (m_renderer.get()) {
		return m_renderer->CopyFromFrame(bufferPtr, bufferSize);
	}
	return 0;
}