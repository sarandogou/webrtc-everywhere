/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#include "_RTCDisplay.h"
#include "_Debug.h"

#include "talk/media/base/videocommon.h"
#include "talk/media/base/videoframe.h"

#include <algorithm>

#if WE_UNDER_WINDOWS
#include <Windows.h>
#endif


//
//	_VideoRenderer
//
_VideoRenderer::_VideoRenderer(int width, int height, cpp11::function<void()> fnOnStartVideoRenderer, webrtc::VideoTrackInterface* track_to_render)
    : m_fnOnStartVideoRenderer(fnOnStartVideoRenderer)
#if WE_UNDER_WINDOWS
    , m_Hwnd(NULL)
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
	m_rendered_track->AddRenderer(this);
}

_VideoRenderer::~_VideoRenderer()
{
    if (m_rendered_track) {
		m_rendered_track->RemoveRenderer(this);
	}
#if WE_UNDER_APPLE
    // wait until async video rendering finish
	dispatch_group_wait(m_group, DISPATCH_TIME_FOREVER);
#endif

	{
		_AutoLock<_VideoRenderer> lock(this);

		m_rendered_track = NULL;
		m_image.reset();

#if WE_UNDER_WINDOWS

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
    }
}

#if WE_UNDER_WINDOWS
void _VideoRenderer::SetHwnd(HWND hwnd)
{
	_AutoLock<_VideoRenderer> lock(this);

	m_Hwnd = hwnd;
}

HWND _VideoRenderer::GetHwnd()
{
    _AutoLock<_VideoRenderer> lock(this);
    
	return m_Hwnd;
}
#elif WE_UNDER_APPLE
void _VideoRenderer::SetLayer(CALayer *layer)
{
    _AutoLock<_VideoRenderer> lock(this);
    
    if (m_layer) {
        m_layer.contents = NULL;
        [m_layer release], m_layer = NULL;
    }
    if (layer) {
        m_layer = [layer retain];
    }
}

CALayer *_VideoRenderer::GetLayer()
{
    _AutoLock<_VideoRenderer> lock(this);
    
    return m_layer;
}
#endif

// On Windows, must be called inside OnPaint()
bool _VideoRenderer::PaintFrame()
{
    _AutoLock<_VideoRenderer> lock(this);

#if WE_UNDER_WINDOWS
    const uint8* image = m_image.get();
	if (m_Hwnd && image) {
		PAINTSTRUCT ps;
		HDC hdc;
		if (!(hdc = ::BeginPaint(m_Hwnd, &ps))) {
			return false;
		}

		RECT rc;
		if (!::GetClientRect(m_Hwnd, &rc)) {
			::EndPaint(m_Hwnd, &ps);
			return false;
		}

#if 1
		int height = abs(m_bmi.bmiHeader.biHeight);
		int width = m_bmi.bmiHeader.biWidth;

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
#else
		::StretchDIBits(hdc, 0, 0, (rc.right - rc.left), (rc.bottom - rc.top),
			0, 0, m_bmi.bmiHeader.biWidth, abs(m_bmi.bmiHeader.biHeight), image, &m_bmi, DIB_RGB_COLORS, SRCCOPY);
#endif

		::EndPaint(m_Hwnd, &ps);

		return true;
	}
#else
	
#endif

	return false;
}

int _VideoRenderer::GetVideoWidth()
{
	_AutoLock<_VideoRenderer> lock(this);

	return m_width;
}

int _VideoRenderer::GetVideoHeight()
{
	_AutoLock<_VideoRenderer> lock(this);

	return m_height;
}



size_t _VideoRenderer::CopyFromFrame(void* bufferPtr, size_t bufferSize)
{
	if (bufferPtr && bufferSize) {
		_AutoLock<_VideoRenderer> lock(this);
		size_t sizeToCopy = std::min((int)bufferSize, (m_width * m_height * 4));
		const uint8* image = m_image.get();
		if (image) {
			memcpy(bufferPtr, image, sizeToCopy);
			return sizeToCopy;
		}
	}
	return  0;
}

// VideoRendererInterface implementation
void _VideoRenderer::SetSize(int width, int height)
{
	_AutoLock<_VideoRenderer> lock(this);
    
    m_width = width;
	m_height = height;

#if WE_UNDER_WINDOWS
	m_bmi.bmiHeader.biWidth = width;
	m_bmi.bmiHeader.biHeight = -height;
	m_bmi.bmiHeader.biSizeImage = width * height *
		(m_bmi.bmiHeader.biBitCount >> 3);
	m_image.reset(new uint8[m_bmi.bmiHeader.biSizeImage]);
#elif WE_UNDER_APPLE
    if (m_context) {
        CGContextRelease(m_context);
        m_context = NULL;
    }
    m_context_buff_size = (m_width * m_height) << 2;
    m_context_buff = realloc(m_context_buff, m_context_buff_size);
    if (!m_context_buff) {
        WE_DEBUG_ERROR("failed to allocate buffer with size = %d", m_context_buff_size);
        m_context_buff_size = 0;
        return;
    }
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    m_context = CGBitmapContextCreate(m_context_buff, m_width, m_height, 8, m_width * 4, colorSpace,
											   kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst);
    CGColorSpaceRelease(colorSpace);
    if (!m_context) {
        WE_DEBUG_ERROR("failed to create RGB32 context");
        return; // return and do not signal "video started" event
    }
    else {
        m_image.reset(new uint8[m_context_buff_size]);
        CGContextSetInterpolationQuality(m_context, kCGInterpolationMedium);
        CGContextSetShouldAntialias(m_context, true);
    }
#endif
    
	if (m_fnOnStartVideoRenderer) {
		m_fnOnStartVideoRenderer();
	}
}

// VideoRendererInterface implementation
void _VideoRenderer::RenderFrame(const cricket::VideoFrame* frame)
{
	if (!frame) {
		return;
	}
	
	_AutoLock<_VideoRenderer> lock(this);

	if (!m_image.get()) {
        return;
    }

#if WE_UNDER_WINDOWS
	frame->ConvertToRgbBuffer(cricket::FOURCC_ARGB,
		m_image.get(),
		m_bmi.bmiHeader.biSizeImage,
		m_bmi.bmiHeader.biWidth *
		m_bmi.bmiHeader.biBitCount / 8);
	
	if (m_Hwnd) {
		InvalidateRect(m_Hwnd, NULL, FALSE);
	}
#elif WE_UNDER_APPLE
    if (m_context_buff && m_context && m_layer) {
        frame->ConvertToRgbBuffer(cricket::FOURCC_ARGB, m_image.get(), m_context_buff_size, m_width * 4);
        memcpy(m_context_buff, m_image.get(), m_context_buff_size);
        
        dispatch_group_enter(m_group);
        dispatch_group_async(m_group, dispatch_get_main_queue(), ^{
            _AutoLock<_VideoRenderer> lock(this);
            if (m_context_buff && m_context && m_layer) {
                CGImageRef image = CGBitmapContextCreateImage(m_context);
                m_layer.contentsGravity = kCAGravityResizeAspect;
                m_layer.contents = (id)image;
                CGImageRelease(image);
            }
            dispatch_group_leave(m_group);
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
			_video->SetHwnd(Handle());
			SetWindowLongPtr(_video->GetHwnd(), GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
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
		SetWindowLongPtr(m_renderer->GetHwnd(), GWLP_USERDATA, NULL);
	}
#endif

	m_renderer.reset();
	OnStopVideoRenderer();
}


// On Windows, must be called inside OnPaint()
bool _RTCDisplay::PaintFrame()
{	
	_AutoLock<_RTCDisplay> lock(this);
	
	bool ret = false;

	if (m_renderer.get()) {
		ret = m_renderer->PaintFrame();
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