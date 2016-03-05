/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */

// http://www.w3.org/TR/mediacapture-streams/#idl-def-SourceInfo

#include "stdafx.h"
#include "SourceInfo.h"
#include "Utils.h"

#include "../common/_Debug.h"

CSourceInfo::CSourceInfo()
	: m_Info(nullptr)
{
}

HRESULT CSourceInfo::FinalConstruct()
{
	return S_OK;
}

void CSourceInfo::FinalRelease()
{
	m_Info = nullptr;
}

void CSourceInfo::SetInfo(std::shared_ptr<_SourceInfo> & info)
{
	m_Info = info;
}

std::shared_ptr<_SourceInfo> CSourceInfo::GetInfo()
{
	return m_Info;
}

STDMETHODIMP CSourceInfo::get_sourceId(__out BSTR* pVal)
{
	if (!m_Info) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiString(m_Info->sourceId, pVal);
}

STDMETHODIMP CSourceInfo::get_id(__out BSTR* pVal)
{
	return get_sourceId(pVal);
}

STDMETHODIMP CSourceInfo::get_kind(__out BSTR* pVal)
{
	if (!m_Info) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiString(m_Info->kind, pVal);
}

STDMETHODIMP CSourceInfo::get_label(__out BSTR* pVal)
{
	if (!m_Info) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiString(m_Info->label, pVal);
}

STDMETHODIMP CSourceInfo::get_facing(__out BSTR* pVal)
{
	if (!m_Info) {
		CHECK_HR_RETURN(E_POINTER);
	}
	return Utils::CopyAnsiString(m_Info->facing, pVal);
}
