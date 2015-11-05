/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_NPAPI_MEDIASTREAM_H_
#define _WEBRTC_EVERYWHERE_NPAPI_MEDIASTREAM_H_

#include "../common/_Config.h"
#include "../common/_Common.h"
#include "../common/_MediaStream.h"
#include "../common/_AsyncEvent.h"

#include "npapi-includes.h"

class MediaStream
	: public NPObject
	, public _AsyncEventRaiser
    , public _UniqueObject
{
public:
	MediaStream(NPP instance);
	virtual ~MediaStream();

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

	NPObjectImpl_CreateInstanceWithRef(MediaStream);
	NPObjectImpl_NPObjectRelease(MediaStream);
	NPObjectImpl_IsInstanceOf(MediaStream);

	void SetStream(cpp11::shared_ptr<_MediaStream> & stream);
	cpp11::shared_ptr<_MediaStream> GetStream();

private:
	NPError getTracks(_TrackType type, NPVariant* Tracks);

	// callbacks
	void onended();
	void onaddtrack();
	void onremovetrack();	

private:
	cpp11::shared_ptr<_MediaStream> m_Stream;
	NPP m_npp;

	// callbacks
	NPObject* m_callback_onended;
	NPObject* m_callback_onaddtrack;
	NPObject* m_callback_onremovetrack;
};

#endif /* _WEBRTC_EVERYWHERE_NPAPI_MEDIASTREAM_H_ */
