/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_Debug.h"
#include "NPCommon.h"
#include "MessageEvent.h"
#include "RTCDataChannel.h"
#include "BrowserCallback.h"
#include "Utils.h"

extern NPNetscapeFuncs* BrowserFuncs;
extern const char* kPluginVersion;

#define kPropLabel					"label"
#define kPropOrdered				"ordered"
#define kPropMaxRetransmitTime		"maxRetransmitTime"
#define kPropMaxRetransmits			"maxRetransmits"
#define kPropProtocol				"protocol"
#define kPropNegotiated				"negotiated"
#define kPropId						"id"
#define kPropReadyState				"readyState"
#define kPropBufferedAmount			"bufferedAmount"
#define kPropBinaryType				"binaryType"
#define kPropOnopen					"onopen"
#define kPropOnerror				"onerror"
#define kPropOnclose				"onclose"
#define kPropOnmessage				"onmessage"

#define kFuncClose					"close"
#define kFuncSend					"send"

NPClass RTCDataChannelClass = {
	NP_CLASS_STRUCT_VERSION,
	RTCDataChannel::Allocate,
	RTCDataChannel::Deallocate,
	RTCDataChannel::Invalidate,
	RTCDataChannel::HasMethod,
	RTCDataChannel::Invoke,
	RTCDataChannel::InvokeDefault,
	RTCDataChannel::HasProperty,
	RTCDataChannel::GetProperty,
	RTCDataChannel::SetProperty,
	RTCDataChannel::RemoveProperty,
	RTCDataChannel::NPEnumeration,
	RTCDataChannel::Construct,
};

void RTCDataChannel::Invalidate(NPObject *npobj)
{
}

bool RTCDataChannel::RemoveProperty(NPObject *npobj, NPIdentifier name)
{
	return false;
}

bool RTCDataChannel::Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return false;
}

RTCDataChannel::RTCDataChannel(NPP instance)
	: m_npp(instance)
	, m_callback_onopen(NULL)
	, m_callback_onerror(NULL)
	, m_callback_onclose(NULL)
	, m_callback_onmessage(NULL)
{
	WE_DEBUG_INFO("RTCDataChannel::NewInstance()");
}

RTCDataChannel::~RTCDataChannel()
{
	if (m_Channel) {
#if !WE_UNDER_APPLE // FIXME
		m_Channel->onopenSet(nullPtr);
		m_Channel->onerrorSet(nullPtr);
		m_Channel->oncloseSet(nullPtr);
		m_Channel->onmessageSet(nullPtr);
#endif
	}
	m_Channel = nullPtr;

	Utils::NPObjectRelease(&m_callback_onopen);
	Utils::NPObjectRelease(&m_callback_onerror);
	Utils::NPObjectRelease(&m_callback_onclose);
	Utils::NPObjectRelease(&m_callback_onmessage);

	SetDispatcher(NULL);
}

void RTCDataChannel::SetChannel(cpp11::shared_ptr<_RTCDataChannel> & channel)
{
	if ((m_Channel = channel)) {
		m_Channel->onopenSet(cpp11::bind(&RTCDataChannel::onopen, this));
		m_Channel->onerrorSet(cpp11::bind(&RTCDataChannel::onerror, this, cpp11::placeholders::_1));
		m_Channel->oncloseSet(cpp11::bind(&RTCDataChannel::onclose, this));
		m_Channel->onmessageSet(cpp11::bind(&RTCDataChannel::onmessage, this, cpp11::placeholders::_1));
	}
}

cpp11::shared_ptr<_RTCDataChannel> RTCDataChannel::GetChannel()
{
	return m_Channel;
}

NPObject* RTCDataChannel::Allocate(NPP instance, NPClass* npclass)
{
	return (NPObject*)(new RTCDataChannel(instance));
}

void RTCDataChannel::Deallocate(NPObject* obj)
{
	delete (RTCDataChannel*)obj;
}

bool RTCDataChannel::HasMethod(NPObject* obj, NPIdentifier methodName)
{
	char* name = BrowserFuncs->utf8fromidentifier(methodName);

	bool ret_val = !strcmp(name, kFuncClose) || !strcmp(name, kFuncSend);

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDataChannel::InvokeDefault(NPObject* obj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}

bool RTCDataChannel::Invoke(NPObject* obj, NPIdentifier methodName,
	const NPVariant* args, uint32_t argCount,
	NPVariant* result)
{
	RTCDataChannel *This = static_cast<RTCDataChannel*>(obj);
	if (!This->m_Channel) {
		return false;
	}
	char* name = BrowserFuncs->utf8fromidentifier(methodName);
	bool ret_val = false;
	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kFuncClose)) {
		This->m_Channel->close();
		ret_val = true;
	}
	else if (!strcmp(name, kFuncSend)) {
		if (argCount > 0) {
            if (Utils::NPObjectIsJsBLOB(This->m_npp, Utils::VariantToObject((NPVariant*)&args[0]))) {
                ret_val = (Utils::DataChannelSendBlob(This->m_npp, obj, Utils::VariantToObject((NPVariant*)&args[0])) == NPERR_NO_ERROR);
            }
            else {
                cpp11::shared_ptr<_Buffer> _data;
                NPError err = Utils::BuildData(This->m_npp, &args[0], _data);
                if (err == NPERR_NO_ERROR) {
                    ret_val = This->m_Channel->send(_data.get(), !NPVARIANT_IS_STRING(args[0]));
                }
            }
		}
	}


	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDataChannel::HasProperty(NPObject* obj, NPIdentifier propertyName)
{
	RTCDataChannel *This = static_cast<RTCDataChannel*>(obj);
	if (!This->m_Channel) {
		return false;
	}
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);

	bool ret_val =
		!strcmp(name, kPropLabel) ||
		!strcmp(name, kPropOrdered) ||
		!strcmp(name, kPropMaxRetransmitTime) ||
		!strcmp(name, kPropMaxRetransmits) ||
		!strcmp(name, kPropProtocol) ||
		!strcmp(name, kPropNegotiated) ||
		!strcmp(name, kPropId) ||
		!strcmp(name, kPropReadyState) ||
		!strcmp(name, kPropBufferedAmount) ||
		!strcmp(name, kPropBinaryType) ||
		!strcmp(name, kPropOnopen) ||
		!strcmp(name, kPropOnerror) ||
		!strcmp(name, kPropOnclose) ||
		!strcmp(name, kPropOnmessage);

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDataChannel::SetProperty(NPObject* obj, NPIdentifier propertyName, const NPVariant *value)
{
	RTCDataChannel *This = static_cast<RTCDataChannel*>(obj);
	if (!This->m_Channel) {
		return false;
	}
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropLabel)) {
		// readonly
	}
	else if (!strcmp(name, kPropOrdered)) {
		// readonly
	}
	else if (!strcmp(name, kPropMaxRetransmitTime)) {
		// readonly
	}
	else if (!strcmp(name, kPropMaxRetransmits)) {
		// readonly
	}
	else if (!strcmp(name, kPropProtocol)) {
		// readonly
	}
	else if (!strcmp(name, kPropNegotiated)) {
		// readonly
	}
	else if (!strcmp(name, kPropId)) {
		// readonly
	}
	else if (!strcmp(name, kPropReadyState)) {
		// readonly
	}
	else if (!strcmp(name, kPropBufferedAmount)) {
		// readonly
	}
	else if (!strcmp(name, kPropBinaryType)) {
		// readonly
	}
	else if (!strcmp(name, kPropOnopen)) {
		Utils::NPObjectSet(&This->m_callback_onopen, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}
	else if (!strcmp(name, kPropOnerror)) {
		Utils::NPObjectSet(&This->m_callback_onerror, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}
	else if (!strcmp(name, kPropOnclose)) {
		Utils::NPObjectSet(&This->m_callback_onclose, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}
	else if (!strcmp(name, kPropOnmessage)) {
		Utils::NPObjectSet(&This->m_callback_onmessage, Utils::VariantToObject((NPVariant*)value));
		ret_val = true;
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDataChannel::GetProperty(NPObject* obj, NPIdentifier propertyName, NPVariant* result)
{
	RTCDataChannel *This = static_cast<RTCDataChannel*>(obj);
	if (!This->m_Channel) {
		return false;
	}
	char* name = BrowserFuncs->utf8fromidentifier(propertyName);
	bool ret_val = false;

	if (!name) {
		return ret_val;
	}

	if (!strcmp(name, kPropLabel)) {
		NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Channel->label(), we_strlen(This->m_Channel->label()));
		if (npStr) {
			STRINGZ_TO_NPVARIANT(npStr, *result);
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropOrdered)) {
		BOOLEAN_TO_NPVARIANT(This->m_Channel->ordered(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropMaxRetransmitTime)) {
		if (This->m_Channel->maxRetransmitTime() == nullable_ushort_null) {
			NULL_TO_NPVARIANT(*result);
		}
		else {
			INT32_TO_NPVARIANT(This->m_Channel->maxRetransmitTime(), *result);
		}
		ret_val = true;
	}
	else if (!strcmp(name, kPropMaxRetransmits)) {
		if (This->m_Channel->maxRetransmits() == nullable_ushort_null) {
			NULL_TO_NPVARIANT(*result);
		}
		else {
			INT32_TO_NPVARIANT(This->m_Channel->maxRetransmits(), *result);
		}
		ret_val = true;
	}
	else if (!strcmp(name, kPropProtocol)) {
		NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Channel->protocol(), we_strlen(This->m_Channel->protocol()));
		if (npStr) {
			STRINGZ_TO_NPVARIANT(npStr, *result);
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropNegotiated)) {
		BOOLEAN_TO_NPVARIANT(This->m_Channel->negotiated(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropId)) {
		if (This->m_Channel->id() == nullable_ushort_null) {
			NULL_TO_NPVARIANT(*result);
		}
		else {
			INT32_TO_NPVARIANT(This->m_Channel->id(), *result);
		}
		ret_val = true;
	}
	else if (!strcmp(name, kPropReadyState)) {
		NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Channel->readyState(), we_strlen(This->m_Channel->readyState()));
		if (npStr) {
			STRINGZ_TO_NPVARIANT(npStr, *result);
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropBufferedAmount)) {
		DOUBLE_TO_NPVARIANT(This->m_Channel->bufferedAmount(), *result);
		ret_val = true;
	}
	else if (!strcmp(name, kPropBinaryType)) {
		NPUTF8* npStr = (NPUTF8*)Utils::MemDup(This->m_Channel->binaryType(), we_strlen(This->m_Channel->binaryType()));
		if (npStr) {
			STRINGZ_TO_NPVARIANT(npStr, *result);
			ret_val = true;
		}
	}
	else if (!strcmp(name, kPropOnopen)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onopen, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropOnerror)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onerror, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropOnclose)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onclose, result) == NPERR_NO_ERROR);
	}
	else if (!strcmp(name, kPropOnmessage)) {
		ret_val = (Utils::NPObjectToVariantAndRetain(This->m_callback_onmessage, result) == NPERR_NO_ERROR);
	}

	BrowserFuncs->memfree(name);
	return ret_val;
}

bool RTCDataChannel::NPEnumeration(NPObject *npobj, NPIdentifier **value, uint32_t *count)
{
	return false;
}

void RTCDataChannel::onopen()
{
	if (m_callback_onopen) {
		BrowserCallback* _cb = new BrowserCallback(m_npp, WM_SUCCESS, m_callback_onopen);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void RTCDataChannel::onerror(cpp11::shared_ptr<std::string> string)
{
	if (m_callback_onerror) {
		BrowserCallback* _cb = new BrowserCallback(m_npp, WM_SUCCESS, m_callback_onerror);
		if (_cb) {
			_cb->AddString(string->c_str(), string->length());
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void RTCDataChannel::onclose()
{
	if (m_callback_onclose) {
		BrowserCallback* _cb = new BrowserCallback(m_npp, WM_SUCCESS, m_callback_onclose);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void RTCDataChannel::onmessage(cpp11::shared_ptr<_MessageEvent> e)
{
	if (m_callback_onmessage) {
		MessageEvent* _event = NULL;
		NPError err = MessageEvent::CreateInstanceWithRef(m_npp, &_event);
		if (err == NPERR_NO_ERROR) {
			_event->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
			_event->SetEvent(e);
			BrowserCallback* _cb = new BrowserCallback(m_npp, WM_SUCCESS, m_callback_onmessage);
			if (_cb) {
				_cb->AddObject(_event);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
		}
		MessageEvent::ReleaseInstance(&_event);
	}
}