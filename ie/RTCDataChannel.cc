/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#idl-def-RTCDataChannel

#include "stdafx.h"
#include "RTCDataChannel.h"
#include "BrowserCallback.h"
#include "MessageEvent.h"
#include "WebRTC.h"
#include "Utils.h"

#include "../common/_Debug.h"
#include "../common/_Buffer.h"


CRTCDataChannel::CRTCDataChannel()
{
}

HRESULT CRTCDataChannel::FinalConstruct()
{
	return S_OK;
}

void CRTCDataChannel::FinalRelease()
{
	if (m_Channel) {
		m_Channel->onopenSet(nullptr);
		m_Channel->onerrorSet(nullptr);
		m_Channel->oncloseSet(nullptr);
		m_Channel->onmessageSet(nullptr);
	}
	m_Channel = nullptr;

	SetDispatcher(NULL);
}

void CRTCDataChannel::SetChannel(std::shared_ptr<_RTCDataChannel> & channel)
{
	if ((m_Channel = channel)) {
		m_Channel->onopenSet(std::bind(&CRTCDataChannel::onopen, this));
		m_Channel->onerrorSet(std::bind(&CRTCDataChannel::onerror, this, std::placeholders::_1));
		m_Channel->oncloseSet(std::bind(&CRTCDataChannel::onclose, this));
		m_Channel->onmessageSet(std::bind(&CRTCDataChannel::onmessage, this, std::placeholders::_1));
	}
}

std::shared_ptr<_RTCDataChannel> CRTCDataChannel::GetChannel()
{
	return m_Channel;
}


STDMETHODIMP CRTCDataChannel::get_label(__out BSTR* pVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiStr(m_Channel->label(), pVal);
}

STDMETHODIMP CRTCDataChannel::get_ordered(__out VARIANT_BOOL* pVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = m_Channel->ordered() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::get_maxRetransmitTime(__out VARIANT* pVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = (m_Channel->maxRetransmitTime() == nullable_ushort_null)
		? CComVariant(NULL)
		: CComVariant((USHORT)m_Channel->maxRetransmitTime());
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::get_maxRetransmits(__out VARIANT* pVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = (m_Channel->maxRetransmits() == nullable_ushort_null)
		? CComVariant(NULL)
		: CComVariant((USHORT)m_Channel->maxRetransmits());
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::get_protocol(__out BSTR* pVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiStr(m_Channel->protocol(), pVal);
}

STDMETHODIMP CRTCDataChannel::get_negotiated(__out VARIANT_BOOL* pVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = m_Channel->negotiated() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::get_id(__out VARIANT* pVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = (m_Channel->id() == nullable_ushort_null)
		? CComVariant(NULL)
		: CComVariant((USHORT)m_Channel->id());
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::get_readyState(__out BSTR* pVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiStr(m_Channel->readyState(), pVal);
}

STDMETHODIMP CRTCDataChannel::get_bufferedAmount(__out ULONG* pVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = m_Channel->bufferedAmount();
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::get_binaryType(__out BSTR* pVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiStr(m_Channel->binaryType(), pVal);
}

STDMETHODIMP CRTCDataChannel::put_binaryType(__in BSTR newVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	char *binaryType = _com_util::ConvertBSTRToString(newVal);
	if (!binaryType) {
		CHECK_HR_RETURN(E_OUTOFMEMORY);
	}
	m_Channel->binaryTypeSet(binaryType);
	delete[] binaryType;
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::get_onopen(__out VARIANT* pVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = CComVariant(m_callback_onopen);
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::put_onopen(__in VARIANT newVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	m_callback_onopen = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::get_onerror(__out VARIANT* pVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = CComVariant(m_callback_onerror);
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::put_onerror(__in VARIANT newVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	m_callback_onerror = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::get_onclose(__out VARIANT* pVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = CComVariant(m_callback_onclose);
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::put_onclose(__in VARIANT newVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	m_callback_onclose = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::get_onmessage(__out VARIANT* pVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	*pVal = CComVariant(m_callback_onmessage);
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::put_onmessage(__in VARIANT newVal)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	m_callback_onmessage = Utils::VariantToDispatch(newVal);
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::close()
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}
	m_Channel->close();
	return S_OK;
}

STDMETHODIMP CRTCDataChannel::send(__in VARIANT data)
{
	if (!m_Channel) {
		CHECK_HR_RETURN(E_POINTER);
	}

	CWebRTC* plugin = dynamic_cast<CWebRTC*>(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));

	CComPtr<IDispatch> spDispatch;
	CHECK_HR_RETURN(plugin->GetDispatch(spDispatch));
	
	if (Utils::VariantIsJsBLOB(data)) {
		CComPtr<IHTMLWindow2> spWindow;
		CHECK_HR_RETURN(plugin->GetHTMLWindow2(spWindow));
		CHECK_HR_RETURN(Utils::DataChannelSendBlob(spDispatch, this, Utils::VariantToDispatch(data)));
	}
	else {
		HRESULT hr;
		std::shared_ptr<_Buffer> _data;

		CHECK_HR_RETURN(hr = Utils::BuildData(spDispatch, data, _data));
		hr = m_Channel->send(_data.get(), data.vt != VT_BSTR) ? S_OK : E_FAIL;
		CHECK_HR_RETURN(hr);
	}
	return S_OK;
}

void CRTCDataChannel::onopen()
{
	if (m_callback_onopen) {
		BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, m_callback_onopen);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void CRTCDataChannel::onerror(cpp11::shared_ptr<std::string> _string)
{
	if (m_callback_onerror) {
		BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, m_callback_onerror);
		if (_cb) {
			_cb->AddBSTR(CComBSTR(_string->c_str()));
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void CRTCDataChannel::onclose()
{
	if (m_callback_onclose) {
		BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, m_callback_onclose);
		if (_cb) {
			this->RaiseCallback(_cb);
			SafeReleaseObject(&_cb);
		}
	}
}

void CRTCDataChannel::onmessage(cpp11::shared_ptr<_MessageEvent> e)
{
	if (m_callback_onmessage) {
		CComObject<CMessageEvent>* _event;
		HRESULT _hr = Utils::CreateInstanceWithRef(&_event);
		if (SUCCEEDED(_hr)) {
			_event->SetDispatcher(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
			_event->SetEvent(e);
			BrowserCallback* _cb = new BrowserCallback(WM_SUCCESS, m_callback_onmessage);
			if (_cb) {
				_cb->AddDispatch(_event);
				this->RaiseCallback(_cb);
				SafeReleaseObject(&_cb);
			}
		}
		SafeRelease(&_event);
	}
}