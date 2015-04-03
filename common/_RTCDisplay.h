/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_COMMON_RTCDISPLAY_H_
#define _WEBRTC_EVERYWHERE_COMMON_RTCDISPLAY_H_

#include "_Config.h"
#include "_Common.h"

#include "talk/media/base/videorenderer.h"
#include "webrtc/system_wrappers/interface/critical_section_wrapper.h"
#if WE_UNDER_WINDOWS
#	include <atlbase.h>
#	include <atlcom.h>
#	include <atlctl.h>
#	include <D3D10_1.h> // Requires Windows Vista or later
#	include <DXGI.h> // Requires Windows 7 or later
#endif
#if WE_UNDER_APPLE
#import <Cocoa/Cocoa.h>
#import <QuartzCore/CoreVideo.h>
#import <QuartzCore/CIContext.h>
#endif

class _VideoRenderer : public webrtc::VideoRendererInterface
{
public:
	_VideoRenderer(int width, int height, cpp11::function<void()> fnOnStartVideoRenderer, webrtc::VideoTrackInterface* track_to_render);
	virtual ~_VideoRenderer();
    
    void Enter() { m_cs->Enter(); }
    void Leave() { m_cs->Leave(); }

#if WE_UNDER_WINDOWS
	void SetHwnd(HWND hwnd, LONG_PTR lpUsrData);
	HWND GetHwnd();
#elif WE_UNDER_APPLE
    void SetLayer(CALayer *layer);
    CALayer *GetLayer();
#endif
	bool PaintFrame();
	int GetVideoWidth();
	int GetVideoHeight();
	size_t CopyFromFrame(void* bufferPtr, size_t bufferSize);
#if WE_UNDER_WINDOWS
	void SetFnQuerySurfacePresenter(cpp11::function<void(CComPtr<ISurfacePresenter> &spPtr, CComPtr<ID3D10Texture2D> &spText, int &backBuffWidth, int &backBuffHeight)> fnQuerySurfacePresenter);
	void SetFnQueryHwnd(cpp11::function<HWND()> fnQueryHwnd);
#endif

	// VideoRendererInterface implementation
	virtual void SetSize(int width, int height);
	virtual void RenderFrame(const cricket::VideoFrame* frame);

private:
	enum {
		SET_SIZE,
		RENDER_FRAME,
	};

#if WE_UNDER_WINDOWS
	HWND m_Hwnd;
	LONG_PTR m_lpUsrData;
	BITMAPINFO m_bmi;
	cpp11::function<void(CComPtr<ISurfacePresenter> &spPtr, CComPtr<ID3D10Texture2D> &spText, int &backBuffWidth, int &backBuffHeight)> m_fnQuerySurfacePresenter;
	cpp11::function<HWND()> m_fnQueryHwnd;
#elif WE_UNDER_APPLE
    CALayer *m_layer;
    CGContextRef m_context;
    void* m_context_buff;
    int m_context_buff_size;
    dispatch_group_t m_group;
#endif
    int m_width;
	int m_height;
	cpp11::function<void()> m_fnOnStartVideoRenderer;
    webrtc::CriticalSectionWrapper *m_cs;
	rtc::scoped_ptr<uint8[]> m_image;
	rtc::scoped_refptr<webrtc::VideoTrackInterface> m_rendered_track;
};

class WEBRTC_EVERYWHERE_API _RTCDisplay
{
protected:
	_RTCDisplay();
public:
	virtual ~_RTCDisplay();
    
    void Enter() { m_cs->Enter(); }
    void Leave() { m_cs->Leave(); }

	virtual void OnStartVideoRenderer() {};
	virtual void OnStopVideoRenderer() {};
	virtual void OnNewFrame(const void* rgb32_ptr, int width, int height) {}
	
	void StartVideoRenderer(VideoTrackInterfacePtr video);
	void StopVideoRenderer();
	bool PaintFrame();

	int GetVideoWidth();
	int GetVideoHeight();
	size_t CopyFromFrame(void* bufferPtr, size_t bufferSize);

#if WE_UNDER_WINDOWS
	virtual HWND Handle() = 0;
	virtual void QuerySurfacePresenter(CComPtr<ISurfacePresenter> &spPtr, CComPtr<ID3D10Texture2D> &spText, int &backBuffWidth, int &backBuffHeight)
	{
		spPtr = NULL, spText = NULL, backBuffWidth = 0, backBuffHeight = 0;
	}
	virtual HWND QueryHwnd()
	{
		return Handle();
	}
#elif WE_UNDER_APPLE
    virtual CALayer *Layer() = 0;
#endif

private:
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	rtc::scoped_ptr<_VideoRenderer> m_renderer;
    webrtc::CriticalSectionWrapper *m_cs;
#if _MSC_VER
#pragma warning(pop)
#endif
};

#endif /* _WEBRTC_EVERYWHERE_COMMON_RTCDISPLAY_H_ */