/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_NPAPI_BROWSERCALLBACK_H_
#define _WEBRTC_EVERYWHERE_NPAPI_BROWSERCALLBACK_H_

#include "../common/_Config.h"
#include "../common/_Common.h"

#include "npapi-includes.h"

typedef enum NPParamType_
{
	NPParamTypeString,
	NPParamTypeObject
} NPParamType;

typedef struct NPParam_ {
	NPParamType type;
	union {
		NPObject *object;
		struct {
			void* ptr;
			size_t size;
		} string;
	} value;
} NPParam;

class BrowserCallback
	: public _BrowserCallback
{
public:
	BrowserCallback(NPP npp, unsigned msgid, NPObject* callback);
	virtual ~BrowserCallback();

	BrowserObjectImpl_Inline();

	NPError AddObject(NPObject* obj);
	NPError AddString(const void* ptr, size_t size);

	// _BrowserCallback implementation
	virtual bool Invoke();

private:
	NPP m_npp;
	NPObject* m_callback;
	size_t m_params_count;
	NPParam m_params[kMaxParamArgs];
};

#endif /* _WEBRTC_EVERYWHERE_NPAPI_BROWSERCALLBACK_H_ */
