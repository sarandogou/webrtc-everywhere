/* Copyright(C) 2014-2015 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_NPAPI_UTILS_H_
#define _WEBRTC_EVERYWHERE_NPAPI_UTILS_H_

#include "../common/_Config.h"
#include "../common/_Utils.h"
#include "../common/_MediaStreamConstraints.h"

#include "npapi-includes.h"

class Utils : public _Utils
{
public:
	static void NPObjectSet(NPObject** dst, NPObject* src);
	static NPError NPObjectRelease(NPObject** obj);
	static NPError NPVariantRelease(NPVariant** var);

	static NPError CreateInstanceWithRef(NPP npp, NPClass *aClass, NPObject** obj);
	static NPError CreateJsArrayEx(NPP npp, std::vector<NPVariant> &vecValues, const NPUTF8* arrayClassName, NPObject** arrayObj);
	static NPError CreateJsArray(NPP npp, std::vector<NPVariant> &vecValues, NPObject** arrayObj);
    static NPError CreateDocumentElementObject(NPP npp, NPObject** jsObj);
	static void NPVecClear(std::vector<NPVariant>& vecVars);

	static NPObject* VariantToObject(NPVariant* var);
	static NPError NPObjectToVariant(NPObject* obj, NPVariant* var);
	static NPError NPObjectToVariantAndRetain(NPObject* obj, NPVariant* var);
	static std::string VariantToString(NPVariant* var);
	static NPError NPObjectToArray(NPP npp, NPObject* obj, std::vector<NPVariant>& vecVars);

    static bool NPObjectIsJsBLOB(NPP npp, NPObject* obj);
	static NPError NPObjectGetProp(NPP npp, NPObject* obj, const NPUTF8* name, NPVariant* var);
	static NPError NPObjectGetPropString(NPP npp, NPObject* obj, const NPUTF8* name, std::string& str);
	static NPError NPObjectGetPropNumber(NPP npp, NPObject* obj, const NPUTF8* name, double& number);
	static NPError NPObjectGetPropBool(NPP npp, NPObject* obj, const NPUTF8* name, bool& _bool);
	static NPError NPObjectCallJsFunction(NPP npp, NPObject* obj, const NPUTF8* name, NPVariant* var);

	static NPError BuildMediaConstraints(NPP npp, NPObject* varConstraints, cpp11::shared_ptr<_MediaConstraints>& constraints);
	static NPError BuildMediaStreamConstraints(NPP npp, NPObject* varConstraints, cpp11::shared_ptr<_MediaStreamConstraints> &constraints);
	static NPError BuildMediaConstraintsObjs(NPP npp, NPObject* varConstraints, cpp11::shared_ptr<_MediaConstraintsObj> &constraints);
	static NPError BuildRTCConfiguration(NPP npp, NPObject* varConfiguration, cpp11::shared_ptr<_RTCConfiguration> &configuration);
	static NPError BuildRTCDataChannelInit(NPP npp, NPObject* varRTCDataChannelInit, cpp11::shared_ptr<_RTCDataChannelInit> &configuration);
	static NPError BuildData(NPP npp, const NPVariant* varData, cpp11::shared_ptr<_Buffer> &data);
	static NPError BuildDataArray(NPP npp, NPObject* varData, _ArrayType type, cpp11::shared_ptr<_Buffer> &data);
    
    static NPObject* NPObjectUpCast(NPObject* pObj);

	static NPError GetLocation(NPP, NPVariant* protocol, NPVariant *host);
    
    static NPError InstallScripts(NPP npp);
    
    static NPError WrapArrayBufferIntoUint8Array(NPP npp, NPObject* arrayBuffer, NPObject ** uint8Array);
    
    static NPError DataChannelSendBlob(NPP npp, NPObject * dataChannel, NPObject* blob);
    
	static void* MemAlloc(size_t n);
	static void* MemDup(const void* mem, size_t n);
	static void MemFree(void** mem);
    
private:
    static NPIdentifier s_funcID_WE00_dataChannelSendBlob;
    static NPIdentifier s_funcID_WE01_wrapArrayBufferIntoUint8Array;
};

#endif /* _WEBRTC_EVERYWHERE_NPAPI_UTILS_H_ */
