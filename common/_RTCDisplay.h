/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_COMMON_RTCDISPLAY_H_
#define _WEBRTC_EVERYWHERE_COMMON_RTCDISPLAY_H_

#include "_Config.h"
#include "_Common.h"

#include "talk/media/base/videorenderer.h"
#include "webrtc/system_wrappers/interface/critical_section_wrapper.h"
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
	void SetHwnd(HWND hwnd);
	HWND GetHwnd();
#elif WE_UNDER_APPLE
    void SetLayer(CALayer *layer);
    CALayer *GetLayer();
#endif
	bool PaintFrame();
	int GetVideoWidth();
	int GetVideoHeight();
	size_t CopyFromFrame(void* bufferPtr, size_t bufferSize);

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
	BITMAPINFO m_bmi;
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
	talk_base::scoped_ptr<uint8[]> m_image;
	talk_base::scoped_refptr<webrtc::VideoTrackInterface> m_rendered_track;
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
	
	void StartVideoRenderer(VideoTrackInterfacePtr video);
	void StopVideoRenderer();
	bool PaintFrame();

	int GetVideoWidth();
	int GetVideoHeight();
	size_t CopyFromFrame(void* bufferPtr, size_t bufferSize);

#if WE_UNDER_WINDOWS
	virtual HWND Handle() = 0;
#elif WE_UNDER_APPLE
    virtual CALayer *Layer() = 0;
#endif

private:
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
	talk_base::scoped_ptr<_VideoRenderer> m_renderer;
    webrtc::CriticalSectionWrapper *m_cs;
#if _MSC_VER
#pragma warning(pop)
#endif
};

#endif /* _WEBRTC_EVERYWHERE_COMMON_RTCDISPLAY_H_ */