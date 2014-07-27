/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */

#include "stdafx.h"
#include "Utils.h"

#include "../common/_Debug.h"

Utils::Utils()
    : _Utils()
{
}

Utils::~Utils()
{

}

HRESULT Utils::ToString(__in BSTR* bstr, __out std::string & str)
{
	if (!bstr || !*bstr) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}
	char* lpszStr = _com_util::ConvertBSTRToString(*bstr);
	if (!lpszStr) {
		CHECK_HR_RETURN(E_OUTOFMEMORY);
	}
	str = std::string(lpszStr);

	delete[]lpszStr;
	return S_OK;
}

HRESULT Utils::CopyAnsiStr(__in LPCSTR psz, __out BSTR* bstr)
{
	*bstr = NULL;
	if (psz) {
		CComBSTR _bstr(psz);
		return _bstr.CopyTo(bstr);
	}
	return S_OK;
}


HRESULT Utils::CopyAnsiString(__in std::string str, __out BSTR* bstr)
{
	return Utils::CopyAnsiStr(str.c_str(), bstr);
}

CComPtr<IDispatch> Utils::VariantToDispatch(VARIANT var)
{
    CComPtr<IDispatch> disp = (var.vt == VT_DISPATCH && var.pdispVal) ? var.pdispVal : NULL;
    return disp;
}

BOOL Utils::VariantIsBool(__in const VARIANT &var)
{
	return var.vt == VT_BOOL;
}

BOOL Utils::VariantIsInteger(__in const VARIANT &var)
{
	switch (var.vt) {
	case VT_I2: case VT_I4: case VT_I1: case VT_UI1: case VT_UI2: case VT_UI4: case VT_I8: case VT_UI8: case VT_INT: case VT_UINT: return TRUE;
	default: return FALSE;
	}
}

BOOL Utils::VariantIsFloat(__in const VARIANT &var)
{
	switch (var.vt) {
	case VT_R4: case VT_R8: return TRUE;
	default: return FALSE;
	}
}

BOOL Utils::VariantIsBSTR(__in const VARIANT &var)
{
	return var.vt == VT_BSTR;
}

HRESULT Utils::VariantToInteger(VARIANT var, long &integer)
{
    CComVariant _var;
    HRESULT hr = VariantChangeType(&_var, &var, 0, VT_I4);
	CHECK_HR_RETURN(hr);
    integer = _var.lVal;
    return S_OK;
}

HRESULT Utils::VariantToDouble(VARIANT var, double &val)
{
	CComVariant _var;
	HRESULT hr = VariantChangeType(&_var, &var, 0, VT_R8);
	CHECK_HR_RETURN(hr);
	val = _var.dblVal;
	return S_OK;
}

HRESULT Utils::VariantToBSTR(VARIANT var, BSTR &bstr)
{
    if (var.vt != VT_BSTR) {
		CHECK_HR_RETURN(E_INVALIDARG);
    }
    bstr = var.bstrVal;
    return S_OK;
}

HRESULT Utils::VariantToArray(__in const CComVariant& var, __out std::vector<CComVariant>& vecVars)
{
    HRESULT hr = S_OK;
    CComPtr<IDispatch> disp = Utils::VariantToDispatch(var);
    if (!disp) {
		CHECK_HR_RETURN(E_INVALIDARG);
    }

    CComVariant varLength;
    hr = Utils::DispatchGetProp(disp, L"length", &varLength);
	CHECK_HR_RETURN(hr);

    long intLength;
    hr = Utils::VariantToInteger(varLength, intLength);
	CHECK_HR_RETURN(hr);

	// Arrays are essentially handled as objects that implement the IDispatch interface pointer, and have a property named "length", 
	// which describes the length of the array, and the property "0" will be the first element, property "1" the second element, and so on.
    WCHAR wcharIndex[25];
    CComVariant varItem;
    for (long index = 0 ; index < intLength ; ++index) {
        wsprintf(wcharIndex, _T("%ld\0"), index);
		hr = Utils::DispatchGetProp(disp, CComBSTR(wcharIndex), &varItem);
		CHECK_HR_RETURN(hr);
        vecVars.push_back(varItem);
    }

    return hr;
}

HRESULT Utils::DispatchGetProp(CComPtr<IDispatch> disp, LPOLESTR name, VARIANT *pVar)
{
    HRESULT hr = S_OK;

    if (!pVar) {
		CHECK_HR_RETURN(E_INVALIDARG);
    }

    DISPID dispid = 0;
    hr = disp->GetIDsOfNames(IID_NULL, &name, 1, LOCALE_USER_DEFAULT, &dispid);
	CHECK_HR_RETURN(hr);

    DISPPARAMS dispParams = {0};
    hr = disp->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dispParams, pVar, NULL, NULL);
	CHECK_HR_RETURN(hr);
    return hr;
}

HRESULT Utils::DispatchGetPropBSTR(__in CComPtr<IDispatch> disp, __in LPOLESTR name, __out BSTR &bstr)
{
    VARIANT varBSTR;
    HRESULT hr = Utils::DispatchGetProp(disp, name, &varBSTR);
	CHECK_HR_RETURN(hr);
    return Utils::VariantToBSTR(varBSTR, bstr);
}

HRESULT Utils::DispatchGetPropInteger(__in CComPtr<IDispatch> disp, __in LPOLESTR name, __out long &_long)
{
	VARIANT varLONG;
	HRESULT hr = Utils::DispatchGetProp(disp, name, &varLONG);
	CHECK_HR_RETURN(hr);
	return Utils::VariantToInteger(varLONG, _long);
}

HRESULT Utils::CreateJsObject(__in CComPtr<IDispatch> spDispatch, __in LPOLESTR className, __out CComQIPtr<IDispatchEx>& spObject)
{
	HRESULT hr = S_OK;

	DISPID classID;
	CHECK_HR_RETURN(hr = spDispatch->GetIDsOfNames(IID_NULL, &className, 1, LOCALE_USER_DEFAULT, &classID));

	CComVariant vtRet;
	DISPPARAMS params = { 0 };
	CComVariant vtResult;
	CHECK_HR_RETURN(hr = spDispatch->Invoke(classID, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &params, &vtResult, NULL, NULL));
	if (!vtResult.pdispVal || (vtResult.vt != VT_DISPATCH)) {
		CHECK_HR_RETURN(DISP_E_TYPEMISMATCH);
	}
	
	CComQIPtr<IDispatchEx> spPrototype(vtResult.pdispVal);
	if (!spPrototype) {
		CHECK_HR_RETURN(E_NOINTERFACE);
	}
	
	vtResult.Clear();
	CHECK_HR_RETURN(hr = spPrototype->InvokeEx(DISPID_VALUE, LOCALE_USER_DEFAULT, DISPATCH_CONSTRUCT, &params, &vtResult, NULL, NULL));
	
	if (!vtResult.pdispVal || (vtResult.vt != VT_DISPATCH)) {
		CHECK_HR_RETURN(DISP_E_TYPEMISMATCH);
	}

	spObject = CComQIPtr<IDispatchEx>(vtResult.pdispVal);
	if (!spObject) {
		CHECK_HR_RETURN(E_NOINTERFACE);
	}

	return hr;
}

HRESULT Utils::CreateJsArray(__in CComPtr<IDispatch> spDispatch, __in std::vector<CComVariant> &vecValues, __out CComQIPtr<IDispatchEx>& spArray)
{
	HRESULT hr = S_OK;
	static LPOLESTR __ArrayClassName = L"Array";

	CHECK_HR_RETURN(hr = Utils::CreateJsObject(spDispatch, __ArrayClassName, spArray));

	// Values
	WCHAR wcharIndex[25];
	DISPID dispID;
	DISPID indexNamedArgs[] = { DISPID_PROPERTYPUT };
	DISPPARAMS params = { NULL, indexNamedArgs, 1, 1 };
	for (size_t index = 0; index < vecValues.size(); ++index) {
		wsprintf(wcharIndex, _T("%ld\0"), index);
		CHECK_HR_RETURN(hr = spArray->GetDispID(CComBSTR(wcharIndex), fdexNameEnsure, &dispID));
		params.rgvarg = &vecValues[index];
		CHECK_HR_RETURN(hr = spArray->InvokeEx(dispID, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUT, &params, NULL, NULL, NULL));
	}

	// "length" property
	CHECK_HR_RETURN(hr = spArray->GetDispID(L"length", fdexNameEnsure, &dispID));
	CComVariant varLength(vecValues.size());
	params.rgvarg = &varLength;
	CHECK_HR_RETURN(hr = spArray->InvokeEx(dispID, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUT, &params, NULL, NULL, NULL));

	return hr;
}

// e.g. varConstraints =  "{ maxWidth: 320, maxHeight : 180 }"
HRESULT Utils::BuildMediaConstraints(__in VARIANT varConstraints, __out std::shared_ptr<_MediaConstraints>& constraints)
{
	if (varConstraints.vt == VT_EMPTY || varConstraints.vt == VT_NULL || varConstraints.vt == VT_ERROR /* optional parameter */) {
		return S_OK;
	}

	CComQIPtr<IDispatchEx> spConstraints = CComQIPtr<IDispatchEx>(Utils::VariantToDispatch(varConstraints));
	if (!spConstraints) {
		CHECK_HR_RETURN(E_NOINTERFACE);
	}

	if (!constraints) {
		constraints = std::make_shared<_MediaConstraints>();
	}
	
	CComVariant var;
	CComBSTR bstrName;
	std::string strName, strVal;
	DISPID dispid;
	HRESULT hr;
	char s[25];
	hr = spConstraints->GetNextDispID(fdexEnumAll, DISPID_STARTENUM, &dispid);
	while (hr != S_FALSE) {
		CHECK_HR_RETURN(hr = spConstraints->GetMemberName(dispid, &bstrName));
		CHECK_HR_RETURN(hr = Utils::DispatchGetProp(spConstraints.p, bstrName, &var));
		CHECK_HR_RETURN(hr = Utils::ToString(&bstrName, strName));
		if (Utils::VariantIsBool(var)) {
			strVal = (var.boolVal != VARIANT_FALSE) ? "true" : "false";
		}
		else if (Utils::VariantIsInteger(var)) {
			long v;
			CHECK_HR_RETURN(hr = Utils::VariantToInteger(var, v));
			sprintf(s, "%ld", v);
			strVal = std::string(s);
		}
		else if (Utils::VariantIsFloat(var)) {
			double v;
			CHECK_HR_RETURN(hr = Utils::VariantToDouble(var, v));
			sprintf(s, "%f", v);
			strVal = std::string(s);
		}
		else if (Utils::VariantIsBSTR(var)) {
			CHECK_HR_RETURN(hr = Utils::ToString(&var.bstrVal, strVal));
		}
		else if (var.vt == VT_DISPATCH && var.pdispVal) {
			CHECK_HR_RETURN(hr = Utils::BuildMediaConstraints(var, constraints));
			goto next;
		}
		else {
			goto next;
		}
		
		constraints->insert(std::pair<std::string, std::string>(strName, strVal));

		next:
		hr = spConstraints->GetNextDispID(fdexEnumAll, dispid, &dispid);
	}

	return S_OK;
}

HRESULT Utils::BuildMediaStreamConstraints(__in VARIANT varConstraints, __out std::shared_ptr<_MediaStreamConstraints> &constraints)
{
	if (varConstraints.vt == VT_EMPTY || varConstraints.vt == VT_NULL || varConstraints.vt == VT_ERROR /* optional parameter */) {
		return S_OK;
	}

	HRESULT hr = S_OK;
	CComQIPtr<IDispatchEx> spConstraints = CComQIPtr<IDispatchEx>(Utils::VariantToDispatch(varConstraints));
	if (!spConstraints) {
		CHECK_HR_RETURN(E_NOINTERFACE);
	}

	std::shared_ptr<_MediaTrackConstraints> audio;
	std::shared_ptr<_MediaTrackConstraints> video;
	CComVariant var;

	hr = Utils::DispatchGetProp(spConstraints.p, L"video", &var);
	if (SUCCEEDED(hr)) {
		if (Utils::VariantIsBool(var)) {
			video = std::make_shared<_MediaTrackConstraints>(var.boolVal != VARIANT_FALSE);
		}
		else {
			std::shared_ptr<_MediaConstraints> mandatory;
			std::shared_ptr<_MediaConstraints> optional;
			CComQIPtr<IDispatchEx> spVideo = CComQIPtr<IDispatchEx>(Utils::VariantToDispatch(var));
			if (!spVideo) {
				CHECK_HR_RETURN(E_NOINTERFACE);
			}
			hr = Utils::DispatchGetProp(spVideo.p, L"mandatory", &var);
			if (SUCCEEDED(hr)) {
				CHECK_HR_RETURN(hr = Utils::BuildMediaConstraints(var, mandatory));
			}
			hr = Utils::DispatchGetProp(spVideo.p, L"optional", &var);
			if (SUCCEEDED(hr)) {
				CHECK_HR_RETURN(hr = Utils::BuildMediaConstraints(var, optional));
			}
			video = std::make_shared<_MediaTrackConstraints>(mandatory, optional);
		}
	}
	hr = Utils::DispatchGetProp(spConstraints.p, L"audio", &var);
	if (SUCCEEDED(hr)) {
		if (Utils::VariantIsBool(var)) {
			audio = std::make_shared<_MediaTrackConstraints>(var.boolVal != VARIANT_FALSE);
		}
		else {
			std::shared_ptr<_MediaConstraints> mandatory;
			std::shared_ptr<_MediaConstraints> optional;
			CComQIPtr<IDispatchEx> spAudio = CComQIPtr<IDispatchEx>(Utils::VariantToDispatch(var));
			if (!spAudio) {
				CHECK_HR_RETURN(E_NOINTERFACE);
			}
			hr = Utils::DispatchGetProp(spAudio.p, L"mandatory", &var);
			if (SUCCEEDED(hr)) {
				CHECK_HR_RETURN(hr = Utils::BuildMediaConstraints(var, mandatory));
			}
			hr = Utils::DispatchGetProp(spAudio.p, L"optional", &var);
			if (SUCCEEDED(hr)) {
				CHECK_HR_RETURN(hr = Utils::BuildMediaConstraints(var, optional));
			}
			audio = std::make_shared<_MediaTrackConstraints>(mandatory, optional);
		}
	}

	constraints = std::make_shared<_MediaStreamConstraints>(audio, video);
	return S_OK;
}

HRESULT Utils::BuildMediaConstraintsObjs(__in VARIANT varConstraints, __out std::shared_ptr<_MediaConstraintsObj> &constraints)
{
	HRESULT hr;

	if (varConstraints.vt == VT_EMPTY || varConstraints.vt == VT_NULL || varConstraints.vt == VT_ERROR /* optional parameter */) {
		return S_OK;
	}

	CComQIPtr<IDispatchEx> spConstraints = CComQIPtr<IDispatchEx>(Utils::VariantToDispatch(varConstraints));
	if (!spConstraints) {
		CHECK_HR_RETURN(E_NOINTERFACE);
	}
	
	std::shared_ptr<_MediaConstraints> mandatory;
	std::shared_ptr<_MediaConstraints> optional;
	VARIANT var;
	hr = Utils::DispatchGetProp(spConstraints.p, L"mandatory", &var);
	if (SUCCEEDED(hr)) {
		CHECK_HR_RETURN(hr = Utils::BuildMediaConstraints(var, mandatory));
	}
	hr = Utils::DispatchGetProp(spConstraints.p, L"optional", &var);
	if (SUCCEEDED(hr)) {
		CHECK_HR_RETURN(hr = Utils::BuildMediaConstraints(var, optional));
	}

	constraints = std::make_shared<_MediaConstraintsObj>(optional, mandatory);
	return S_OK;
}

HRESULT Utils::BuildRTCConfiguration(__in VARIANT varConfiguration, __out std::shared_ptr<_RTCConfiguration> &configuration)
{
	if (varConfiguration.vt == VT_EMPTY || varConfiguration.vt == VT_NULL || varConfiguration.vt == VT_ERROR /* optional parameter */) {
		return S_OK;
	}

	CComQIPtr<IDispatchEx> spConfiguration = CComQIPtr<IDispatchEx>(Utils::VariantToDispatch(varConfiguration));
	if (!spConfiguration) {
		CHECK_HR_RETURN(E_NOINTERFACE);
	}

	configuration = std::make_shared<_RTCConfiguration>();

	VARIANT varIceServers;
	HRESULT hr;
	hr = Utils::DispatchGetProp(spConfiguration.p, L"iceServers", &varIceServers);
	if (SUCCEEDED(hr)) {
		std::vector<CComVariant>vectIceServers;
		hr = Utils::VariantToArray(varIceServers, vectIceServers);
		if (SUCCEEDED(hr)) {
			CComPtr<IDispatch>dispServer;
			for (unsigned i = 0; i < vectIceServers.size(); i++) {
				dispServer = Utils::VariantToDispatch(vectIceServers[i]);
				if (dispServer) {
					BSTR bstr;
					std::string uri, username, password;
					hr = Utils::DispatchGetPropBSTR(dispServer, L"url", bstr);
					if (SUCCEEDED(hr)) {
						CHECK_HR_RETURN(hr = Utils::ToString(&bstr, uri));
					}
					hr = Utils::DispatchGetPropBSTR(dispServer, L"username", bstr);
					if (SUCCEEDED(hr)) {
						CHECK_HR_RETURN(hr = Utils::ToString(&bstr, username));
					}
					hr = Utils::DispatchGetPropBSTR(dispServer, L"credential", bstr);
					if (SUCCEEDED(hr)) {
						CHECK_HR_RETURN(hr = Utils::ToString(&bstr, password));
					}
					configuration->iceServers.push_back(__RTCIceServer(uri, username, password));
				}
			}
		}
	}

	return S_OK;
}