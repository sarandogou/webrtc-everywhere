/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_NPAPI_NPCOMMON_H_
#define _WEBRTC_EVERYWHERE_NPAPI_NPCOMMON_H_

#include "../common/_Config.h"
#include "../common/_Common.h"
#include "../common/_AsyncEvent.h"

#include "Utils.h"

#include "npapi-includes.h"

#define kPropUniqueId							"uniqueId"

class NPObjectAutoRef {
public:
	NPObjectAutoRef(NPObject *obj) : m_obj(NULL){
		Utils::NPObjectSet(&m_obj, obj);
	}
	NPObjectAutoRef(const NPObjectAutoRef& other) : m_obj(NULL) {
		Utils::NPObjectSet(&m_obj, other);
	}
	virtual ~NPObjectAutoRef() {
		Utils::NPObjectRelease(&m_obj);
	}

	operator bool() const
	{
		return !!m_obj;
	}
	operator NPObject*() const
	{
		return m_obj;
	}
	NPObjectAutoRef& operator = (NPObject* obj)
	{
		Utils::NPObjectSet(&m_obj, obj);
		return *this;
	}
private:
	NPObject *m_obj;
};

#endif /* _WEBRTC_EVERYWHERE_NPAPI_NPCOMMON_H_ */