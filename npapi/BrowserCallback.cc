/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Debug.h"
#include "Utils.h"
#include "BrowserCallback.h"

extern NPNetscapeFuncs* BrowserFuncs;

BrowserCallback::BrowserCallback(NPP npp, unsigned msgid, NPObject* callback)
	: _BrowserCallback(msgid)
	, m_npp(npp)
	, m_callback(NULL)
	, m_params_count(0)
{
	Utils::NPObjectSet(&m_callback, callback);
	memset(m_params, 0, sizeof(m_params));
}

BrowserCallback::~BrowserCallback()
{
	Utils::NPObjectRelease(&m_callback);
	for (size_t i = 0; i < m_params_count; ++i) {
		switch (m_params[i].type) {
			case NPParamTypeString:
				{
					Utils::MemFree(&m_params[i].value.string.ptr);
					break;
				}
			case NPParamTypeObject:
				{
					if (m_params[i].value.object) {
						BrowserFuncs->releaseobject(m_params[i].value.object), m_params[i].value.object = NULL;
					}
					break;
				}
			default:
				{
					WE_DEBUG_ERROR("%d not a valid value for NPParamType", m_params[i].type);
					break;
				}
		}
	}
}

NPError BrowserCallback::AddObject(NPObject* obj)
{
	if ((m_params_count + 1) >= kMaxParamArgs) {
		WE_DEBUG_ERROR("Too much params");
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
	NPParam* newParam = &m_params[m_params_count++];
	newParam->type = NPParamTypeObject;
	BrowserFuncs->retainobject(obj);
	newParam->value.object = obj;
	return NPERR_NO_ERROR;
}

NPError BrowserCallback::AddString(const void* ptr, size_t size)
{
	if ((m_params_count + 1) >= kMaxParamArgs) {
		WE_DEBUG_ERROR("Too much params");
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
	NPParam* newParam = &m_params[m_params_count++];
	newParam->type = NPParamTypeString;
	newParam->value.string.ptr = Utils::MemDup(ptr, size);
	newParam->value.string.size = size;
	return NPERR_NO_ERROR;
}

// _BrowserCallback implementation
bool BrowserCallback::Invoke()
{
	bool ret = false;
	if (m_callback) {
		NPVariant result;
		VOID_TO_NPVARIANT(result);
		NPVariant args[kMaxParamArgs];
		for (size_t i = 0; i < m_params_count; ++i) {
			switch (m_params[i].type) {
			case NPParamTypeString:
			{
				STRINGN_TO_NPVARIANT((const NPUTF8 *)m_params[i].value.string.ptr, m_params[i].value.string.size, args[i]);
				break;
			}
			case NPParamTypeObject:
			{
				if (m_params[i].value.object) {
					OBJECT_TO_NPVARIANT(m_params[i].value.object, args[i]);
				}
				break;
			}
			default:
			{
				WE_DEBUG_ERROR("%d not a valid value for NPParamType", m_params[i].type);
				return false;
			}
			}
		}
		ret = BrowserFuncs->invokeDefault(m_npp, m_callback, args, (uint32_t)m_params_count, &result);
		BrowserFuncs->releasevariantvalue(&result); 
	}
	return ret;
}