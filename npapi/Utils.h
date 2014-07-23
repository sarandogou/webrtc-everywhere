/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
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

	static NPError CreateInstanceWithRef(NPP npp, NPClass *aClass, NPObject** obj);
	static NPError CreateJsArray(NPP npp, std::vector<NPVariant> &vecValues, NPObject** arrayObj);
    static NPError CreateDocumentElementObject(NPP npp, NPObject** jsObj);
	static void NPVecClear(std::vector<NPVariant>& vecVars);

	static NPObject* VariantToObject(NPVariant* var);
	static NPError NPObjectToVariant(NPObject* obj, NPVariant* var);
	static NPError NPObjectToVariantAndRetain(NPObject* obj, NPVariant* var);
	static std::string VariantToString(NPVariant* var);
	static NPError NPObjectToArray(NPP npp, NPObject* obj, std::vector<NPVariant>& vecVars);

	static NPError NPObjectGetProp(NPP npp, NPObject* obj, const NPUTF8* name, NPVariant* var);
	static NPError NPObjectGetPropString(NPP npp, NPObject* obj, const NPUTF8* name, std::string& str);
	static NPError NPObjectGetPropNumber(NPP npp, NPObject* obj, const NPUTF8* name, double& number);

	static NPError BuildMediaConstraints(NPP npp, NPObject* varConstraints, cpp11::shared_ptr<_MediaConstraints>& constraints);
	static NPError BuildMediaStreamConstraints(NPP npp, NPObject* varConstraints, cpp11::shared_ptr<_MediaStreamConstraints> &constraints);
	static NPError BuildMediaConstraintsObjs(NPP npp, NPObject* varConstraints, cpp11::shared_ptr<_MediaConstraintsObj> &constraints);
	static NPError BuildRTCConfiguration(NPP npp, NPObject* varConfiguration, cpp11::shared_ptr<_RTCConfiguration> &configuration);
    
    static NPObject* NPObjectUpCast(NPObject* pObj);
    
	static void* MemAlloc(size_t n);
	static void* MemDup(const void* mem, size_t n);
	static void MemFree(void** mem);
};

#endif /* _WEBRTC_EVERYWHERE_NPAPI_UTILS_H_ */
