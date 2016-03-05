/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
// http://www.w3.org/TR/webrtc/#event-datachannel-message

#include "stdafx.h"
#include "MessageEvent.h"
#include "Utils.h"
#include "WebRTC.h"

#include "../common/_Buffer.h"
#include "../common/_Debug.h"



CMessageEvent::CMessageEvent()
{
}

HRESULT CMessageEvent::FinalConstruct()
{
	return S_OK;
}

void CMessageEvent::FinalRelease()
{
	m_data.Clear();
	m_Event = nullptr;

	SetDispatcher(NULL);
}

void CMessageEvent::SetEvent(std::shared_ptr<_MessageEvent> & _event)
{ 
	m_data.Clear();
	m_Event = _event; 
}

std::shared_ptr<_MessageEvent> CMessageEvent::GetEvent()
{ 
	return m_Event; 
}

STDMETHODIMP CMessageEvent::get_data(VARIANT* pVal)
{
	if (!m_Event || !m_Event->data.get()) {
		return CComVariant(NULL).Detach(pVal);
	}

	if (m_data.vt == VT_EMPTY || m_data.vt == VT_NULL || m_data.vt == VT_ERROR) {
		if (m_Event->binary) {
			HRESULT hr;
			CComPtr<CWebRTC> pluginInstance = dynamic_cast<CWebRTC*>(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
			if (!pluginInstance) {
				CHECK_HR_RETURN(E_POINTER);
			}

			CComPtr<IDispatch> spDispatch;
			CHECK_HR_RETURN(hr = pluginInstance->GetDispatch(spDispatch));

			const uint8_t* ptr = reinterpret_cast<const uint8_t*>(m_Event->data->getPtr());
			size_t size = m_Event->data->getSize();
			std::vector<CComVariant> vect;
			for (size_t i = 0; i < size; ++i) {
				vect.push_back(CComVariant(ptr[i]));
			}
			CComQIPtr<IDispatchEx> spArray;
			CComVariant varRawBuffer;
			CHECK_HR_RETURN(hr = Utils::CreateJsArrayEx(spDispatch, vect, L"Uint8Array", spArray));
			CHECK_HR_RETURN(hr = Utils::DispatchGetProp(spArray.p, L"buffer", &varRawBuffer));
			CHECK_HR_RETURN(hr = varRawBuffer.Detach(&m_data));
		}
		else {
			CHECK_HR_RETURN(CComVariant(CComBSTR((const char*)m_Event->data->getPtr())).Detach(&m_data));
		}
	}	

	return CComVariant(m_data).Detach(pVal);
}