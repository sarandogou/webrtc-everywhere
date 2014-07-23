/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_NPAPI_WEBRTC_H_
#define _WEBRTC_EVERYWHERE_NPAPI_WEBRTC_H_

#include "../common/_Config.h"
#include "../common/_AsyncEvent.h"
#include "../common/_RTCDisplay.h"
#include "../common/_Common.h"
#include "../common/_Buffer.h"

#if WE_UNDER_APPLE
#include <QuartzCore/QuartzCore.h>
#include <QTKit/QTKit.h>
#endif

#include "npapi-includes.h"

class WebRTC
	: public NPObject
	, public _AsyncEventDispatcher
	, public _AsyncEventRaiser
	, public _RTCDisplay
	, public _UniqueObject
{
public:
	WebRTC(NPP instance);
	virtual ~WebRTC();

public:
	static NPObject* Allocate(NPP instance, NPClass* npclass);
	static void Deallocate(NPObject* obj);
	static bool HasMethod(NPObject* obj, NPIdentifier methodName);
	static bool InvokeDefault(NPObject* obj, const NPVariant* args,
		uint32_t argCount, NPVariant* result);
	static bool Invoke(NPObject* obj, NPIdentifier methodName,
		const NPVariant* args, uint32_t argCount,
		NPVariant* result);
	static bool HasProperty(NPObject* obj, NPIdentifier propertyName);
	static bool GetProperty(NPObject* obj, NPIdentifier propertyName,
		NPVariant* result);
	static bool SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value);
	static bool RemoveProperty(NPObject *npobj, NPIdentifier name);
	static bool NPEnumeration(NPObject *npobj, NPIdentifier **value,
		uint32_t *count);
	static void Invalidate(NPObject *npobj);
	static bool Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result);

	// _RTCDisplay implementation
#if WE_UNDER_WINDOWS
	virtual HWND Handle();
#elif WE_UNDER_APPLE
    virtual CALayer *Layer();
#endif
	virtual void OnStartVideoRenderer();
	virtual void OnStopVideoRenderer();

	// _BrowserObject implementation
	BrowserObjectImpl_NPObject();
    
#if WE_UNDER_APPLE
    CALayer * rootLayer() { return m_pRootLayer; }
    void SetRootLayer(CALayer *rootLayer) { if (m_pRootLayer) { [m_pRootLayer release], m_pRootLayer = NULL; } if (rootLayer) { m_pRootLayer = [rootLayer retain]; } }
#endif

private:
	NPP m_npp;
	_Buffer *m_pTempVideoBuff;
	std::vector<NPObject*> m_callbacks_onplay;
#if WE_UNDER_APPLE
    CALayer *m_pRootLayer;
#endif
};

#endif /* _WEBRTC_EVERYWHERE_NPAPI_WEBRTC_H_ */
