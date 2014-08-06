/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */

// http://www.w3.org/TR/mediacapture-streams/#idl-def-MediaSourceStates

#include "stdafx.h"
#include "MediaSourceStates.h"
#include "Utils.h"

#include "../common/_Debug.h"

CMediaSourceStates::CMediaSourceStates()
	: m_States(nullptr)
{
}

HRESULT CMediaSourceStates::FinalConstruct()
{
	return S_OK;
}

void CMediaSourceStates::FinalRelease()
{
	m_States = nullptr;
}

void CMediaSourceStates::SetStates(std::shared_ptr<_MediaSourceStates> & states)
{
	m_States = states;
}

std::shared_ptr<_MediaSourceStates> CMediaSourceStates::GetStates()
{
	return m_States;
}

STDMETHODIMP CMediaSourceStates::get_sourceType(__out BSTR* pVal)
{
	if (!m_States) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiString(m_States->sourceType, pVal);
}

STDMETHODIMP CMediaSourceStates::get_sourceId(__out BSTR* pVal)
{
	if (!m_States) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiString(m_States->sourceId, pVal);
}

STDMETHODIMP CMediaSourceStates::get_width(__out VARIANT* pVal)
{
	if (!m_States) {
		CHECK_HR_RETURN(E_POINTER);
	}
	// nullable
	if (m_States->width <= 0) {
		CComVariant(NULL).Detach(pVal);
	}
	else {
		*pVal = CComVariant(m_States->width);
	}
	return S_OK;
}

STDMETHODIMP CMediaSourceStates::get_height(__out VARIANT* pVal)
{
	if (!m_States) {
		CHECK_HR_RETURN(E_POINTER);
	}
	// nullable
	if (m_States->height <= 0) {
		CComVariant(NULL).Detach(pVal);
	}
	else {
		*pVal = CComVariant(m_States->height);
	}
	return S_OK;
}

STDMETHODIMP CMediaSourceStates::get_frameRate(__out VARIANT* pVal)
{
	if (!m_States) {
		CHECK_HR_RETURN(E_POINTER);
	}
	// nullable
	if (m_States->frameRate <= 0) {
		CComVariant(NULL).Detach(pVal);
	}
	else {
		*pVal = CComVariant(m_States->frameRate);
	}
	return S_OK;
}

STDMETHODIMP CMediaSourceStates::get_aspectRatio(__out VARIANT* pVal)
{
	if (!m_States) {
		CHECK_HR_RETURN(E_POINTER);
	}
	// nullable
	if (m_States->aspectRatio <= 0) {
		CComVariant(NULL).Detach(pVal);
	}
	else {
		*pVal = CComVariant(m_States->aspectRatio);
	}
	return S_OK;
}

STDMETHODIMP CMediaSourceStates::get_facingMode(__out VARIANT* pVal)
{
	if (!m_States) {
		CHECK_HR_RETURN(E_POINTER);
	}
	// nullable
	if (m_States->facingMode.empty()) {
		*pVal = CComVariant(NULL);
	}
	else {
		*pVal = CComVariant(CComBSTR(m_States->facingMode.c_str()));
	}
	return S_OK;
}

STDMETHODIMP CMediaSourceStates::get_volume(__out VARIANT* pVal)
{
	if (!m_States) {
		CHECK_HR_RETURN(E_POINTER);
	}
	// nullable
	if (m_States->volume < 0) {
		*pVal = CComVariant(NULL);
	}
	else {
		*pVal = CComVariant(m_States->volume);
	}
	return S_OK;
}