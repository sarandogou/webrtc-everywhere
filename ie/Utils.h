/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#pragma once
#include "../common/_Config.h"
#include "../common/_Utils.h"
#include "../common/_Buffer.h"
#include "../common/_MediaStreamConstraints.h"

#include <atlctl.h>
#include <comutil.h>
#include <stdio.h>
#include <vector>

class Utils : public _Utils
{
public:
    Utils();
    virtual ~Utils();

	static HRESULT ToString(__in BSTR* bstr, __out std::string & str);
	static HRESULT CopyAnsiStr(__in LPCSTR psz, __out BSTR* bstr);
	static HRESULT CopyAnsiString(__in std::string str, __out BSTR* bstr);
    static CComPtr<IDispatch> VariantToDispatch(VARIANT var);
	static BOOL VariantIsBool(__in const VARIANT &var);
	static BOOL VariantIsInteger(__in const VARIANT &var);
	static BOOL VariantIsFloat(__in const VARIANT &var);
	static BOOL VariantIsBSTR(__in const VARIANT &var);
	static BOOL VariantIsJsBLOB(__in const VARIANT &var);
    static HRESULT VariantToInteger(VARIANT var, long &integer);
	static HRESULT VariantToDouble(VARIANT var, double &val);
    static HRESULT VariantToBSTR(VARIANT var, BSTR &bstr);
    static HRESULT VariantToArray(__in const CComVariant& var, __out std::vector<CComVariant>& vecVars);
    static HRESULT DispatchGetProp(CComPtr<IDispatch> disp, LPOLESTR name, VARIANT *pVar);
	static HRESULT DispatchGetPropBOOL(__in CComPtr<IDispatch> disp, __in LPOLESTR name, __out bool &val);
    static HRESULT DispatchGetPropBSTR(__in CComPtr<IDispatch> disp, __in LPOLESTR name, __out BSTR &bstr);
	static HRESULT DispatchGetPropInteger(__in CComPtr<IDispatch> disp, __in LPOLESTR name, __out long &_long);
	static HRESULT DispatchCallJsFunction(CComPtr<IDispatch> disp, LPOLESTR name, VARIANT *pVar);
	static HRESULT Utils::CreateJsObjectEx(__in CComPtr<IDispatch> spDispatch, __in LPOLESTR className, VARIANTARG *rgvarg, UINT cArgs, __out CComQIPtr<IDispatchEx>& spObject);
	static HRESULT CreateJsObject(__in CComPtr<IDispatch> spDispatch, __in LPOLESTR className, __out CComQIPtr<IDispatchEx>& spObject);
	static HRESULT CreateJsArrayEx(__in CComPtr<IDispatch> spDispatch, __in std::vector<CComVariant> &vecValues, __in LPOLESTR arrayClassName, __out CComQIPtr<IDispatchEx>& spArray);
	static HRESULT CreateJsArray(__in CComPtr<IDispatch> spDispatch, __in std::vector<CComVariant> &vecValues, __out CComQIPtr<IDispatchEx>& spArray);
	static HRESULT BuildMediaConstraints(__in VARIANT varConstraints, __out std::shared_ptr<_MediaConstraints>& constraints);
	static HRESULT BuildMediaStreamConstraints(__in VARIANT varConstraints, __out std::shared_ptr<_MediaStreamConstraints> &constraints);
	static HRESULT BuildMediaConstraintsObjs(__in VARIANT varConstraints, __out std::shared_ptr<_MediaConstraintsObj> &constraints);
	static HRESULT BuildRTCConfiguration(__in VARIANT varConfiguration, __out std::shared_ptr<_RTCConfiguration> &configuration);
	static HRESULT BuildRTCDataChannelInit(__in VARIANT varRTCDataChannelInit, __out std::shared_ptr<_RTCDataChannelInit> &configuration);
	static HRESULT BuildData(__in CComPtr<IDispatch> spDispatch, __in VARIANT varData, __out std::shared_ptr<_Buffer> &data);
	static HRESULT BuildDataArray(__in CComPtr<IDispatch> spData, __in _ArrayType type, __out std::shared_ptr<_Buffer> &data);
	static HRESULT WrapArrayBufferIntoUint8Array(__in CComPtr<IDispatch> spDispatch, __in CComPtr<IDispatch> spArrayBuffer, __out CComPtr<IDispatch> &spUint8Array);

	static HRESULT DataChannelSendBlob(__in CComPtr<IDispatch> spDispatch, __in CComPtr<IDispatch> dataChannel, __in CComPtr<IDispatch> blob);

	static HRESULT InstallScripts(__in CComPtr<IHTMLWindow2> spWindow);

	template <class T>
	static HRESULT CreateInstanceWithRef(T** ppObject)
	{
		CComObject<T> *pObject;
		HRESULT hr = CComObject<T>::CreateInstance(&pObject);
		if (SUCCEEDED(hr)) {
			pObject->AddRef();
			*ppObject = pObject;
		}
		return hr;
	}

private:
	static DISPID s_funcID_WE00_dataChannelSendBlob;
	static DISPID s_funcID_WE01_wrapArrayBufferIntoUint8Array;
};
