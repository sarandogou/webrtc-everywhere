/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#pragma once
#include "../common/_Config.h"
#include "../common/_Utils.h"
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
    static HRESULT VariantToInteger(VARIANT var, long &integer);
	static HRESULT VariantToDouble(VARIANT var, double &val);
    static HRESULT VariantToBSTR(VARIANT var, BSTR &bstr);
    static HRESULT VariantToArray(__in const CComVariant& var, __out std::vector<CComVariant>& vecVars);
    static HRESULT DispatchGetProp(CComPtr<IDispatch> disp, LPOLESTR name, VARIANT *pVar);
    static HRESULT DispatchGetPropBSTR(__in CComPtr<IDispatch> disp, __in LPOLESTR name, __out BSTR &bstr);
	static HRESULT DispatchGetPropInteger(__in CComPtr<IDispatch> disp, __in LPOLESTR name, __out long &_long);
	static HRESULT CreateJsObject(__in CComPtr<IDispatch> spDispatch, __in LPOLESTR className, __out CComQIPtr<IDispatchEx>& spObject);
	static HRESULT CreateJsArray(__in CComPtr<IDispatch> spDispatch, __in std::vector<CComVariant> &vecValues, __out CComQIPtr<IDispatchEx>& spArray);
	static HRESULT BuildMediaConstraints(__in VARIANT varConstraints, __out std::shared_ptr<_MediaConstraints>& constraints);
	static HRESULT BuildMediaStreamConstraints(__in VARIANT varConstraints, __out std::shared_ptr<_MediaStreamConstraints> &constraints);
	static HRESULT BuildMediaConstraintsObjs(__in VARIANT varConstraints, __out std::shared_ptr<_MediaConstraintsObj> &constraints);
	static HRESULT BuildRTCConfiguration(__in VARIANT varConfiguration, __out std::shared_ptr<_RTCConfiguration> &configuration);

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
};
