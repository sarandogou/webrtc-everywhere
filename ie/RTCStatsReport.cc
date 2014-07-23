/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */

// http://www.w3.org/TR/webrtc/#idl-def-RTCStatsReport

#include "stdafx.h"
#include "RTCStatsReport.h"
#include "RTCStats.h"
#include "Utils.h"
#include "WebRTC.h"

#include "../common/_Debug.h"

CRTCStatsReport::CRTCStatsReport()
	: m_Stats(nullptr)
{
}

HRESULT CRTCStatsReport::FinalConstruct()
{
	return S_OK;
}

void CRTCStatsReport::FinalRelease()
{
	m_Stats = nullptr;
}

STDMETHODIMP CRTCStatsReport::result(__out VARIANT* RTCStatsList)
{
	if (!m_Stats) {
		return CComVariant(NULL).Detach(RTCStatsList);
	}

	HRESULT hr;
	CComPtr<CWebRTC> pluginInstance = dynamic_cast<CWebRTC*>(const_cast<_AsyncEventDispatcher*>(GetDispatcher()));
	if (!pluginInstance) {
		CHECK_HR_RETURN(E_POINTER);
	}

	CComPtr<IDispatch> spDispatch;
	CHECK_HR_RETURN(hr = pluginInstance->GetDispatch(spDispatch));

	std::vector<CComVariant> vect;
	std::map<std::string, std::shared_ptr<_RTCStats> >::iterator it = m_Stats->values.begin();
	for (; it != m_Stats->values.end(); ++it) {
		CComObject<CRTCStats>* _stats;
		hr = Utils::CreateInstanceWithRef(&_stats);
		if (SUCCEEDED(hr)) {
			_stats->SetStats((*it).second);
			_stats->SetDispatcher(pluginInstance);
			vect.push_back(CComVariant(_stats));
			SafeRelease(&_stats);
		}
	}

	CComQIPtr<IDispatchEx> spArray;
	CHECK_HR_RETURN(hr = Utils::CreateJsArray(spDispatch, vect, spArray));
	*RTCStatsList = CComVariant(spArray.Detach());

	return hr;
}