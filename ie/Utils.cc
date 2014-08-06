/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */

#include "stdafx.h"
#include "Utils.h"

#include "../common/_Debug.h"

DISPID Utils::s_funcID_WE00_dataChannelSendBlob = 0;
DISPID Utils::s_funcID_WE01_wrapArrayBufferIntoUint8Array = 0;

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

BOOL Utils::VariantIsJsBLOB(__in const VARIANT &var)
{
	CComPtr<IDispatch> disp = Utils::VariantToDispatch(var);
	if (disp) {
		CComVariant var;
		if (SUCCEEDED(Utils::DispatchCallJsFunction(disp, _T("toString"), &var))) {
			if (var.vt == VT_BSTR) {
				return (_wcsicmp(var.bstrVal, _T("[object Blob]")) == 0) ? TRUE : FALSE;
			}
		}
	}
	return FALSE;
}

HRESULT Utils::VariantToInteger(VARIANT var, long &integer)
{
	if (Utils::VariantIsBSTR(var)) {
		integer = wcstol(var.bstrVal, NULL, 10);
	}
	else {
		CComVariant _var;
		HRESULT hr = VariantChangeType(&_var, &var, 0, VT_I4);
		CHECK_HR_RETURN(hr);
		integer = _var.lVal;
	}
    return S_OK;
}

HRESULT Utils::VariantToDouble(VARIANT var, double &val)
{
	if (Utils::VariantIsBSTR(var)) {
		val = wcstod(var.bstrVal, NULL);
	}
	else {
		CComVariant _var;
		HRESULT hr = VariantChangeType(&_var, &var, 0, VT_R8);
		CHECK_HR_RETURN(hr);
		val = _var.dblVal;
	}
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
	if (FAILED(hr)) {
		return hr;
	}

    DISPPARAMS dispParams = {0};
    hr = disp->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dispParams, pVar, NULL, NULL);
	if (FAILED(hr)) {
		return hr;
	}
    return hr;
}

HRESULT Utils::DispatchGetPropBSTR(__in CComPtr<IDispatch> disp, __in LPOLESTR name, __out BSTR &bstr)
{
    VARIANT varBSTR;
    HRESULT hr = Utils::DispatchGetProp(disp, name, &varBSTR);
	if (FAILED(hr)) {
		return hr;
	}
    return Utils::VariantToBSTR(varBSTR, bstr);
}

HRESULT Utils::DispatchGetPropBOOL(__in CComPtr<IDispatch> disp, __in LPOLESTR name, __out bool &val)
{
	VARIANT var;
	HRESULT hr = Utils::DispatchGetProp(disp, name, &var);
	if (SUCCEEDED(hr) && var.vt == VT_BOOL) {
		val = (var.boolVal == VARIANT_TRUE);
		return S_OK;
	}
	return E_FAIL;
}

HRESULT Utils::DispatchGetPropInteger(__in CComPtr<IDispatch> disp, __in LPOLESTR name, __out long &_long)
{
	VARIANT varLONG;
	HRESULT hr = Utils::DispatchGetProp(disp, name, &varLONG);
	if (FAILED(hr)) {
		return hr;
	}
	return Utils::VariantToInteger(varLONG, _long);
}

HRESULT Utils::DispatchCallJsFunction(CComPtr<IDispatch> disp, LPOLESTR name, VARIANT *pVar)
{
	if (!disp || !name || !pVar) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}

	HRESULT hr;
	DISPID funcID;
	CHECK_HR_RETURN(hr = disp->GetIDsOfNames(IID_NULL, &name, 1, LOCALE_USER_DEFAULT, &funcID));

	CComVariant vtRet;
	DISPPARAMS params = { 0 };
	CHECK_HR_RETURN(hr = disp->Invoke(funcID, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &params, pVar, NULL, NULL));
	return S_OK;
}

HRESULT Utils::CreateJsObjectEx(__in CComPtr<IDispatch> spDispatch, __in LPOLESTR className, VARIANTARG *rgvarg, UINT cArgs, __out CComQIPtr<IDispatchEx>& spObject)
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
	params.cArgs = cArgs;
	params.rgvarg = rgvarg;
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

HRESULT Utils::CreateJsObject(__in CComPtr<IDispatch> spDispatch, __in LPOLESTR className, __out CComQIPtr<IDispatchEx>& spObject)
{
	return Utils::CreateJsObjectEx(spDispatch, className, NULL, 0, spObject);
}

HRESULT Utils::CreateJsArrayEx(__in CComPtr<IDispatch> spDispatch, __in std::vector<CComVariant> &vecValues, __in LPOLESTR arrayClassName, __out CComQIPtr<IDispatchEx>& spArray)
{
	HRESULT hr = S_OK;

	CComVariant rgvarg((ULONG)vecValues.size()); // length as argument for the constructor
	CHECK_HR_RETURN(hr = Utils::CreateJsObjectEx(spDispatch, arrayClassName, &rgvarg, 1, spArray));

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

#if 0
	// "length" property
	CHECK_HR_RETURN(hr = spArray->GetDispID(L"length", fdexNameEnsure, &dispID));
	CComVariant varLength(vecValues.size());
	params.rgvarg = &varLength;
	CHECK_HR_RETURN(hr = spArray->InvokeEx(dispID, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYPUT, &params, NULL, NULL, NULL));
#endif

	return hr;
}

HRESULT Utils::CreateJsArray(__in CComPtr<IDispatch> spDispatch, __in std::vector<CComVariant> &vecValues, __out CComQIPtr<IDispatchEx>& spArray)
{
	return Utils::CreateJsArrayEx(spDispatch, vecValues, L"Array", spArray);
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

HRESULT Utils::BuildRTCDataChannelInit(__in VARIANT varRTCDataChannelInit, __out std::shared_ptr<_RTCDataChannelInit> &configuration)
{
	if (varRTCDataChannelInit.vt == VT_EMPTY || varRTCDataChannelInit.vt == VT_NULL || varRTCDataChannelInit.vt == VT_ERROR /* optional parameter */) {
		return S_OK;
	}

	CComQIPtr<IDispatch> spConfiguration = CComQIPtr<IDispatch>(Utils::VariantToDispatch(varRTCDataChannelInit));
	if (!spConfiguration) {
		CHECK_HR_RETURN(E_NOINTERFACE);
	}

	configuration = std::make_shared<_RTCDataChannelInit>();
	HRESULT hr;
	BSTR bstr;
	bool _bool;
	long _long;

	// http://www.w3.org/TR/webrtc/#idl-def-RTCDataChannel
	if (SUCCEEDED((hr = Utils::DispatchGetPropBSTR(spConfiguration, L"protocol", bstr)))) {
		Utils::ToString(&bstr, configuration->protocol);
	}
	if (SUCCEEDED((hr = Utils::DispatchGetPropBOOL(spConfiguration, L"ordered", _bool)))) {
		configuration->ordered = _bool;
	}
	if (SUCCEEDED((hr = Utils::DispatchGetPropInteger(spConfiguration, L"maxRetransmitTime", _long)))) {
		configuration->maxRetransmitTime = _long;
	}
	if (SUCCEEDED((hr = Utils::DispatchGetPropInteger(spConfiguration, L"maxRetransmits", _long)))) {
		configuration->maxRetransmits = _long;
	}
	if (SUCCEEDED((hr = Utils::DispatchGetPropBOOL(spConfiguration, L"negotiated", _bool)))) {
		configuration->negotiated = _bool;
	}
	if (SUCCEEDED((hr = Utils::DispatchGetPropInteger(spConfiguration, L"id", _long)))) {
		configuration->id = _long;
	}
	return S_OK;
}

HRESULT Utils::BuildData(__in CComPtr<IDispatch> spDispatch, __in VARIANT varData, __out std::shared_ptr<_Buffer> &data)
{
	if (varData.vt == VT_BSTR) {
		char *_str = _com_util::ConvertBSTRToString(varData.bstrVal);
		if (!_str) {
			CHECK_HR_RETURN(E_OUTOFMEMORY);
		}
		data = std::make_shared<_Buffer>(_str, we_strlen(_str));
		delete[]_str;
		return S_OK;
	}
	else if (varData.vt == VT_DISPATCH) {
		CComQIPtr<IDispatchEx> spData = CComQIPtr<IDispatchEx>(Utils::VariantToDispatch(varData));
		if (!spData) {
			CHECK_HR_RETURN(E_NOINTERFACE);
		}

		_ArrayType arrayType = _ArrayType_None;
		HRESULT hr;

		CComVariant var;
		CHECK_HR_RETURN(hr = Utils::DispatchCallJsFunction(spData.p, _T("toString"), &var));
		if (var.vt != VT_BSTR) {
			CHECK_HR_RETURN(E_FAIL);
		}

		if (_wcsicmp(var.bstrVal, _T("[object Int8Array]")) == 0) {
			arrayType = _ArrayType_Int8Array;
		}
		else if (_wcsicmp(var.bstrVal, _T("[object Uint8Array]")) == 0) {
			arrayType = _ArrayType_Uint8Array;
		}
		else if (_wcsicmp(var.bstrVal, _T("[object Uint8ClampedArray]")) == 0) {
			arrayType = _ArrayType_Uint8ClampedArray;
		}
		else if (_wcsicmp(var.bstrVal, _T("[object Int16Array]")) == 0) {
			arrayType = _ArrayType_Int16Array;
		}
		else if (_wcsicmp(var.bstrVal, _T("[object Uint16Array]")) == 0) {
			arrayType = _ArrayType_Uint16Array;
		}
		else if (_wcsicmp(var.bstrVal, _T("[object Int32Array]")) == 0) {
			arrayType = _ArrayType_Int32Array;
		}
		else if (_wcsicmp(var.bstrVal, _T("[object Uint32Array]")) == 0) {
			arrayType = _ArrayType_Uint32Array;
		}
		else if (_wcsicmp(var.bstrVal, _T("[object Float32Array]")) == 0) {
			arrayType = _ArrayType_Float32Array;
		}
		else if (_wcsicmp(var.bstrVal, _T("[object Float64Array]")) == 0) {
			arrayType = _ArrayType_Float64Array;
		}
		else if (_wcsicmp(var.bstrVal, _T("[object ArrayBuffer]")) == 0) {
			CComPtr<IDispatch> spUint8Array;
			CHECK_HR_RETURN(Utils::WrapArrayBufferIntoUint8Array(spDispatch, spData.p, spUint8Array));
			return Utils::BuildData(spDispatch, CComVariant(spUint8Array), data);
		}

		if (arrayType != _ArrayType_None) {
			return Utils::BuildDataArray(spData.p, arrayType, data);
		}
	}

	return E_FAIL;
}

HRESULT Utils::BuildDataArray(__in CComPtr<IDispatch> spData, __in _ArrayType arrayType, __out std::shared_ptr<_Buffer> &data)
{
	if (!spData || arrayType == _ArrayType_None) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}

	int byteCount = _Utils::ArrayBytesCount(arrayType);
	if (byteCount <= 0) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}

	CComVariant var;
	long length;
	HRESULT hr;
	
	CHECK_HR_RETURN(hr = Utils::DispatchGetPropInteger(spData, L"length", length));

	data = std::make_shared<_Buffer>((const void*)NULL, (size_t)(length * byteCount));
	if (!data.get() || !data->getPtr()) {
		CHECK_HR_RETURN(E_OUTOFMEMORY);
	}
	uint8_t* ptr = reinterpret_cast<uint8_t*>(const_cast<void*>(data->getPtr()));

	bool isFloatingPoint = _Utils::ArrayIsFloatingPoint(arrayType);

	TCHAR s[25];
	double _double;
	long _long;
	for (long i = 0; i < length; ++i) {
		wsprintf(s, _T("%ld"), i);
		CHECK_HR_RETURN(hr = Utils::DispatchGetProp(spData.p, s, &var));
		if (isFloatingPoint) {
			CHECK_HR_RETURN(hr = Utils::VariantToDouble(var, _double));
			switch (arrayType) {
			case _ArrayType_Float32Array: *((float*)ptr) = (float)_double; break;
			case _ArrayType_Float64Array: *((double*)ptr) = _double; break;
			default: CHECK_HR_RETURN(E_INVALIDARG);
			}
		}
		else {
			CHECK_HR_RETURN(hr = Utils::VariantToInteger(var, _long));
			switch (arrayType) {
			case _ArrayType_Int8Array: *((int8_t*)ptr) = (int8_t)_long; break;
			case _ArrayType_Uint8Array: *((uint8_t*)ptr) = (uint8_t)_long; break;
			case _ArrayType_Uint8ClampedArray: *((uint8_t*)ptr) = (uint8_t)(_long < 0 ? 0 : (_long > 255 ? 255 : _long)); break;
			case _ArrayType_Int16Array: *((int16_t*)ptr) = ((int16_t)_long); break;
			case _ArrayType_Uint16Array: *((uint16_t*)ptr) = ((uint16_t)_long); break;
			case _ArrayType_Int32Array: *((int32_t*)ptr) = (int32_t)_long; break;
			case _ArrayType_Uint32Array: *((uint32_t*)ptr) = (uint32_t)_long; break;
			default: CHECK_HR_RETURN(E_INVALIDARG);
			}
		}
		ptr += byteCount;
	}

	return S_OK;
}

HRESULT Utils::WrapArrayBufferIntoUint8Array(__in CComPtr<IDispatch> spDispatch, __in CComPtr<IDispatch> spArrayBuffer, __out CComPtr<IDispatch> &spUint8Array)
{
	if (!spArrayBuffer) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}

	HRESULT hr;

	CComVariant vtRet;
	DISPPARAMS params = { 0 };
	VARIANTARG args[1] = { CComVariant(spArrayBuffer) }; //!\ parameters swapped
	params.cArgs = sizeof(args) / sizeof(args[0]);
	params.rgvarg = args;
	CHECK_HR_RETURN(hr = spDispatch->Invoke(Utils::s_funcID_WE01_wrapArrayBufferIntoUint8Array, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &params, &vtRet, NULL, NULL));
	if (vtRet.vt != VT_DISPATCH || !vtRet.pdispVal) {
		CHECK_HR_RETURN(E_FAIL);
	}
	spUint8Array = vtRet.pdispVal;
	vtRet.Clear();

	return S_OK;	
}

HRESULT Utils::DataChannelSendBlob(__in CComPtr<IDispatch> spDispatch, __in CComPtr<IDispatch> dataChannel, __in CComPtr<IDispatch> blob)
{
	if (!dataChannel || !blob) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}

	HRESULT hr;

	CComVariant vtRet;
	DISPPARAMS params = { 0 };
	VARIANTARG args[2] = { CComVariant(blob), CComVariant(dataChannel) }; //!\ parameters swapped
	params.cArgs = sizeof(args) / sizeof(args[0]);
	params.rgvarg = args;
	CHECK_HR_RETURN(hr = spDispatch->Invoke(Utils::s_funcID_WE00_dataChannelSendBlob, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &params, &vtRet, NULL, NULL));
	
	return S_OK;
}

HRESULT Utils::InstallScripts(__in CComPtr<IHTMLWindow2> spWindow)
{
	static bool g_installed = false;

	if (g_installed) {
		return S_OK;
	}

	if (!spWindow) {
		CHECK_HR_RETURN(E_INVALIDARG);
	}

	typedef struct script {
		const char* funcName = NULL;
		DISPID* funcID = NULL;
		const char* code = NULL;
		script(const char* _funcName, DISPID* _funcID, const char* _code) : funcName(_funcName), funcID(_funcID), code(_code) {}
	} script;

	static const char __script00[] = "window.WE00_dataChannelSendBlob = function(dataChannel, blob) {"
			"var reader = new FileReader();"
			"attachEventListener(reader, 'loadend', function() {"
			"dataChannel.send(reader.result);"
			"});"
			"reader.readAsArrayBuffer(blob);"
		"}";
	static const char __script001[] = "window.WE01_wrapArrayBufferIntoUint8Array = function(arrayBuffer) { return new Uint8Array(arrayBuffer) }";
	static script __scripts[] = { { "WE00_dataChannelSendBlob", &Utils::s_funcID_WE00_dataChannelSendBlob, __script00 }, { "WE01_wrapArrayBufferIntoUint8Array", &Utils::s_funcID_WE01_wrapArrayBufferIntoUint8Array, __script001 } };

	CComVariant ret;
	HRESULT hr = S_OK;

	CComPtr<IDispatch> spDispatch;
	CHECK_HR_RETURN(hr = spWindow->QueryInterface(IID_PPV_ARGS(&spDispatch)));

	for (size_t i = 0; i < sizeof(__scripts) / sizeof(__scripts[0]); ++i) {
		CHECK_HR_RETURN(hr = spWindow->execScript(CComBSTR(__scripts[i].code), _T("javascript"), &ret));
		LPOLESTR funcName = CComBSTR(__scripts[i].funcName);
		CHECK_HR_RETURN(hr = spDispatch->GetIDsOfNames(IID_NULL, &funcName, 1, LOCALE_USER_DEFAULT, __scripts[i].funcID));
	}
	g_installed = true;

	return S_OK;
}