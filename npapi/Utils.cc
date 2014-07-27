/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#include "Utils.h"
#include "NPCommon.h"

#include "../common/_Debug.h"

extern NPNetscapeFuncs* BrowserFuncs;

void Utils::NPObjectSet(NPObject** dst, NPObject* src)
{
	Utils::NPObjectRelease(dst);
	if (src) {
		BrowserFuncs->retainobject(src);
		*dst = src;
	}
}

NPError Utils::NPObjectRelease(NPObject** obj)
{
	if (obj && *obj) {
		if ((*obj)->_class->structVersion != NP_CLASS_STRUCT_VERSION) {
			// FIXME: Safari: fails to free JS callback when browser is refreshed (referenceCount = 1).
			WE_DEBUG_ERROR("Trying to free invalid NPObject. structVersion=%d", (*obj)->_class->structVersion);
			*obj = NULL;
			return NPERR_INVALID_PLUGIN_ERROR;
		}
		SafeReleaseNPObject(obj);
	}
	return NPERR_NO_ERROR;
}

NPError Utils::CreateInstanceWithRef(NPP npp, NPClass *aClass, NPObject** obj)
{
	if (!obj || !aClass) {
		CHECK_NPERR_RETURN(NPERR_INVALID_PARAM);
	}
	if (!(*obj = BrowserFuncs->createobject(npp, aClass))) {
		CHECK_NPERR_RETURN(NPERR_OUT_OF_MEMORY_ERROR);
	}
	return NPERR_NO_ERROR;
}

NPError Utils::CreateJsArray(NPP npp, std::vector<NPVariant> &vecValues, NPObject** arrayObj)
{
	if (!arrayObj || *arrayObj) {
		CHECK_NPERR_RETURN(NPERR_INVALID_PARAM);
	}
	NPObject* npWindow = NULL;
	NPError err;
	
	CHECK_NPERR_RETURN(err = BrowserFuncs->getvalue(npp, NPNVWindowNPObject, &npWindow));

	NPVariant var;
	bool bRet = BrowserFuncs->invoke(npp, npWindow, BrowserFuncs->getstringidentifier("Array"), NULL, 0, &var);
	BrowserFuncs->releaseobject(npWindow);
	if (!bRet || var.type != NPVariantType_Object || !var.value.objectValue) {
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
	*arrayObj = var.value.objectValue;

	NPIdentifier idPush = BrowserFuncs->getstringidentifier("push");
	VOID_TO_NPVARIANT(var);
	for (size_t i = 0; i < vecValues.size(); ++i) {
		BrowserFuncs->invoke(npp, *arrayObj, idPush, &vecValues[i], 1, &var);
		BrowserFuncs->releasevariantvalue(&var);
	}
	return NPERR_NO_ERROR;
}

NPError Utils::CreateDocumentElementObject(NPP npp, NPObject** jsObj)
{
    if (!jsObj || *jsObj) {
		CHECK_NPERR_RETURN(NPERR_INVALID_PARAM);
	}
	NPObject* npWindow = NULL;
	NPError err;
    NPVariant var;
	
	CHECK_NPERR_RETURN(err = BrowserFuncs->getvalue(npp, NPNVWindowNPObject, &npWindow));
    
    
    if (!BrowserFuncs->getproperty(npp,npWindow, BrowserFuncs->getstringidentifier("document"), &var) || !NPVARIANT_IS_OBJECT(var)) {
        Utils::NPObjectRelease(&npWindow);
        CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
    }
    Utils::NPObjectRelease(&npWindow);
    
    NPObject* npDoc = var.value.objectValue;
    NPVariant varObjectString;
    STRINGZ_TO_NPVARIANT("object", varObjectString);
    bool ret = BrowserFuncs->invoke(npp, npDoc, BrowserFuncs->getstringidentifier("createElement"), &varObjectString, 1, &var);
    Utils::NPObjectRelease(&npDoc);
    
    if (ret && NPVARIANT_IS_OBJECT(var)) {
        *jsObj = var.value.objectValue;
    }
    else {
        BrowserFuncs->releasevariantvalue(&var);
        CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
    }
    
	return NPERR_NO_ERROR;
}

void Utils::NPVecClear(std::vector<NPVariant>& vecVars)
{
	for (size_t i = 0; i < vecVars.size(); ++i) {
		BrowserFuncs->releasevariantvalue(&vecVars[i]);
	}
	vecVars.clear();
}

// No retain()
NPObject* Utils::VariantToObject(NPVariant* var)
{
	if (var && var->type == NPVariantType_Object) {
		return NPVARIANT_TO_OBJECT(*var);
	}
	return NULL;
}

// No retain()
NPError Utils::NPObjectToVariant(NPObject* obj, NPVariant* var)
{
	if (!var) {
		CHECK_NPERR_RETURN(NPERR_INVALID_PARAM);
	}
	if (obj) {
		OBJECT_TO_NPVARIANT(obj, *var);
	}
	else {
		NULL_TO_NPVARIANT(*var);
	}
	return NPERR_NO_ERROR;
}

NPError Utils::NPObjectToVariantAndRetain(NPObject* obj, NPVariant* var)
{
	NPError err = Utils::NPObjectToVariant(obj, var);
	if (err == NPERR_NO_ERROR) {
		if (NPVARIANT_IS_OBJECT(*var) && var->value.objectValue) {
			BrowserFuncs->retainobject(var->value.objectValue);
		}
	}
	return err;
}

std::string Utils::VariantToString(NPVariant* var)
{
	if (var && var->type == NPVariantType_String && var->value.stringValue.UTF8Characters && var->value.stringValue.UTF8Length) {
		return std::string(var->value.stringValue.UTF8Characters, var->value.stringValue.UTF8Length);
	}
	return std::string("");
}

// Up to the caller to call releasevariantvalue(vecVars[i=0...n]).
NPError Utils::NPObjectToArray(NPP npp, NPObject* obj, std::vector<NPVariant>& vecVars)
{
	if (!obj) {
		CHECK_NPERR_RETURN(NPERR_INVALID_PARAM);
	}

	NPVariant var;
	NPError err;

	double length = 0;
	CHECK_NPERR_RETURN(err = Utils::NPObjectGetPropNumber(npp, obj, "length", length));

	char s[25];
	for (double i = 0; i < length; ++i) {
		sprintf(s, "%d", (int32_t)i);
		err = Utils::NPObjectGetProp(npp, obj, s, &var);		
		if (err != NPERR_NO_ERROR) {
			Utils::NPVecClear(vecVars);
			CHECK_NPERR_RETURN(err);
		}
		vecVars.push_back(var); // "var" will be released later using NPVectClear()
	}

	return NPERR_NO_ERROR;
}

// Up to the caller to call releasevariantvalue(retVal).
NPError Utils::NPObjectGetProp(NPP npp, NPObject* obj, const NPUTF8* name, NPVariant* var)
{
	if (!npp || !name || !var) {
		CHECK_NPERR_RETURN(NPERR_INVALID_PARAM);
	}
	VOID_TO_NPVARIANT(*var);
	NPIdentifier indentifier = BrowserFuncs->getstringidentifier(name);
	if (!BrowserFuncs->getproperty(npp, obj, indentifier, var)) {
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
	return NPERR_NO_ERROR;
}

NPError Utils::NPObjectGetPropString(NPP npp, NPObject* obj, const NPUTF8* name, std::string& str)
{
	NPVariant var;
	CHECK_NPERR_RETURN(Utils::NPObjectGetProp(npp, obj, name, &var));
	if (var.type != NPVariantType_String) {
		BrowserFuncs->releasevariantvalue(&var);
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
	str = std::string(var.value.stringValue.UTF8Characters, var.value.stringValue.UTF8Length);
	BrowserFuncs->releasevariantvalue(&var);
	return NPERR_NO_ERROR;
}

NPError Utils::NPObjectGetPropNumber(NPP npp, NPObject* obj, const NPUTF8* name, double& number)
{
	NPVariant var;
	CHECK_NPERR_RETURN(Utils::NPObjectGetProp(npp, obj, name, &var));

	if (var.type == NPVariantType_Double) {
		number = var.value.doubleValue;
	}
	else if (var.type == NPVariantType_Int32) {
		number = var.value.intValue;
	}
	else {
		BrowserFuncs->releasevariantvalue(&var);
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
	BrowserFuncs->releasevariantvalue(&var);
	return NPERR_NO_ERROR;
}

NPError Utils::BuildMediaConstraints(NPP npp, NPObject* varConstraints, cpp11::shared_ptr<_MediaConstraints>& constraints)
{
	if (!varConstraints) {
		return NPERR_NO_ERROR;
	}

	if (!constraints) {
		constraints = cpp11::shared_ptr<_MediaConstraints>(new _MediaConstraints());
	}

	NPError err;
	NPVariant var;
	NPIdentifier *identifiers = NULL;
	uint32_t count = 0;
	std::string strName, strVal;

	if (BrowserFuncs->enumerate(npp, varConstraints, &identifiers, &count) != true){
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
	char s[25];
	for (uint32_t i = 0; i < count; ++i) {
		NPUTF8* propName = BrowserFuncs->utf8fromidentifier(identifiers[i]);
		if (!propName) {
			continue;
		}

		err = Utils::NPObjectGetProp(npp, varConstraints, propName, &var);
		if (err != NPERR_NO_ERROR) {
			BrowserFuncs->memfree(identifiers);
			BrowserFuncs->memfree(propName);
			CHECK_NPERR_RETURN(err);
		}
		strName = std::string(propName);

		if (var.type == NPVariantType_Bool) {
			strVal = var.value.boolValue ? "true" : "false";
		}
		else if (var.type == NPVariantType_Int32) {
			sprintf(s, "%d", var.value.intValue);
			strVal = std::string(s);
		}
		else if (var.type == NPVariantType_Double) {
			sprintf(s, "%lf", var.value.doubleValue);
			strVal = std::string(s);
		}
		else if (var.type == NPVariantType_String) {
			if (var.value.stringValue.UTF8Characters && var.value.stringValue.UTF8Length) {
				strVal = std::string(var.value.stringValue.UTF8Characters, var.value.stringValue.UTF8Length);
			}
			else {
				strVal = std::string("");
			}
		}
		else if (var.type == NPVariantType_Object && var.value.objectValue) {
			err = Utils::BuildMediaConstraints(npp, var.value.objectValue, constraints);
			goto next;
		}
		else {
			goto next;
		}

		constraints->insert(std::pair<std::string, std::string>(strName, strVal));

	next:
		BrowserFuncs->memfree(propName);
		BrowserFuncs->releasevariantvalue(&var);
	}
	
	BrowserFuncs->memfree(identifiers);

	return NPERR_NO_ERROR;
}

NPError Utils::BuildMediaStreamConstraints(NPP npp, NPObject* varConstraints, cpp11::shared_ptr<_MediaStreamConstraints> &constraints)
{
	if (!varConstraints) {
		return NPERR_NO_ERROR;
	}
	
	NPError err;
	cpp11::shared_ptr<_MediaTrackConstraints> audio;
	cpp11::shared_ptr<_MediaTrackConstraints> video;
	NPVariant var;

	err = Utils::NPObjectGetProp(npp, varConstraints, "video", &var);
	if (err == NPERR_NO_ERROR) {
		if (var.type == NPVariantType_Bool) {
			video = cpp11::shared_ptr<_MediaTrackConstraints>(new _MediaTrackConstraints(var.value.boolValue));
		}
		else if (var.type == NPVariantType_Object && var.value.objectValue) {
			cpp11::shared_ptr<_MediaConstraints> mandatory;
			cpp11::shared_ptr<_MediaConstraints> optional;
			NPObject* objVideo = var.value.objectValue;
			NPVariant varVideo;
			
			err = Utils::NPObjectGetProp(npp, objVideo, "mandatory", &varVideo);
			if (err == NPERR_NO_ERROR && varVideo.type == NPVariantType_Object) {
				err = Utils::BuildMediaConstraints(npp, varVideo.value.objectValue, mandatory);
				BrowserFuncs->releasevariantvalue(&varVideo);
			}
			if (err == NPERR_NO_ERROR) {
				err = Utils::NPObjectGetProp(npp, objVideo, "optional", &varVideo);
				if (err == NPERR_NO_ERROR && varVideo.type == NPVariantType_Object) {
					err = Utils::BuildMediaConstraints(npp, varVideo.value.objectValue, optional);
					BrowserFuncs->releasevariantvalue(&varVideo);
				}
			}
			BrowserFuncs->releasevariantvalue(&var);
			CHECK_NPERR_RETURN(err);
			video = cpp11::shared_ptr<_MediaTrackConstraints>(new _MediaTrackConstraints(mandatory, optional));
		}
	}
	err = Utils::NPObjectGetProp(npp, varConstraints, "audio", &var);
	if (err == NPERR_NO_ERROR) {
		if (var.type == NPVariantType_Bool) {
			audio = cpp11::shared_ptr<_MediaTrackConstraints>(new _MediaTrackConstraints(var.value.boolValue));
		}
		else if (var.type == NPVariantType_Object && var.value.objectValue) {
			cpp11::shared_ptr<_MediaConstraints> mandatory;
			cpp11::shared_ptr<_MediaConstraints> optional;
			NPObject* objAudio = var.value.objectValue;
			NPVariant varAudio;

			err = Utils::NPObjectGetProp(npp, objAudio, "mandatory", &varAudio);
			if (err == NPERR_NO_ERROR && varAudio.type == NPVariantType_Object) {
				err = Utils::BuildMediaConstraints(npp, varAudio.value.objectValue, mandatory);
				BrowserFuncs->releasevariantvalue(&varAudio);
			}
			if (err == NPERR_NO_ERROR) {
				err = Utils::NPObjectGetProp(npp, objAudio, "optional", &varAudio);
				if (err == NPERR_NO_ERROR && varAudio.type == NPVariantType_Object) {
					err = Utils::BuildMediaConstraints(npp, varAudio.value.objectValue, optional);
					BrowserFuncs->releasevariantvalue(&varAudio);
				}
			}
			BrowserFuncs->releasevariantvalue(&var);
			CHECK_NPERR_RETURN(err);
			audio = cpp11::shared_ptr<_MediaTrackConstraints>(new _MediaTrackConstraints(mandatory, optional));
		}
	}

	constraints = cpp11::shared_ptr<_MediaStreamConstraints>(new _MediaStreamConstraints(audio, video));
	return NPERR_NO_ERROR;
}

NPError Utils::BuildMediaConstraintsObjs(NPP npp, NPObject* varConstraints, cpp11::shared_ptr<_MediaConstraintsObj> &constraints)
{
	if (!varConstraints) {
		return NPERR_NO_ERROR;
	}
	
	NPError err;
	cpp11::shared_ptr<_MediaConstraints> mandatory;
	cpp11::shared_ptr<_MediaConstraints> optional;
	NPVariant var;
	NPObject* obj;
	err = Utils::NPObjectGetProp(npp, varConstraints, "mandatory", &var);
	if (err == NPERR_NO_ERROR && (obj = Utils::VariantToObject(&var))) {
		err = Utils::BuildMediaConstraints(npp, obj, mandatory);
		BrowserFuncs->releasevariantvalue(&var);
		CHECK_NPERR_RETURN(err);
	}
	err = Utils::NPObjectGetProp(npp, varConstraints, "optional", &var);
	if (err == NPERR_NO_ERROR && (obj = Utils::VariantToObject(&var))) {
		err = Utils::BuildMediaConstraints(npp, obj, optional);
		BrowserFuncs->releasevariantvalue(&var);
		CHECK_NPERR_RETURN(err);
	}

	constraints = cpp11::shared_ptr<_MediaConstraintsObj>(new _MediaConstraintsObj(optional, mandatory));

	return NPERR_NO_ERROR;
}

NPError Utils::BuildRTCConfiguration(NPP npp, NPObject* varConfiguration, cpp11::shared_ptr<_RTCConfiguration> &configuration)
{
	if (!varConfiguration) {
		return NPERR_NO_ERROR;
	}

	configuration = cpp11::shared_ptr<_RTCConfiguration>(new _RTCConfiguration());

	NPVariant varIceServers;
	NPError err;
	err = Utils::NPObjectGetProp(npp, varConfiguration, "iceServers", &varIceServers);
	if (err == NPERR_NO_ERROR) {
		std::vector<NPVariant>vectIceServers;
		err = Utils::NPObjectToArray(npp, Utils::VariantToObject(&varIceServers), vectIceServers);
		if (err == NPERR_NO_ERROR) {
			NPObject* objServer;
			for (unsigned i = 0; i < vectIceServers.size(); i++) {
				objServer = Utils::VariantToObject(&vectIceServers[i]);
				if (objServer) {
					std::string uri, username, password;
					err = Utils::NPObjectGetPropString(npp, objServer, "url", uri);
					err = Utils::NPObjectGetPropString(npp, objServer, "username", username);
					err = Utils::NPObjectGetPropString(npp, objServer, "credential", password);
					configuration->iceServers.push_back(__RTCIceServer(uri, username, password));
				}
			}
		}
		Utils::NPVecClear(vectIceServers);
	}

	return NPERR_NO_ERROR;
}

NPObject* Utils::NPObjectUpCast(NPObject* pObj)
{
    if (pObj) {
        NPVariant var;
        if (pObj->_class->getProperty(pObj, BrowserFuncs->getstringidentifier(kPropUniqueId), &var)) {
            long uniqueId = -1;
            if (var.type == NPVariantType_Double) {
                uniqueId = (long)var.value.doubleValue;
            }
            else if (var.type == NPVariantType_Int32) {
                uniqueId = var.value.intValue;
            }
            else return NULL;
            return dynamic_cast<NPObject*>(const_cast<_UniqueObject*>(_Utils::UniqueObjFind(uniqueId)));
        }
    }
    return NULL;
}

void* Utils::MemAlloc(size_t n)
{
	return BrowserFuncs->memalloc((uint32_t)n);
}

void* Utils::MemDup(const void* mem, size_t n)
{
	void *ret = NULL;
	if (mem && n){
		if ((ret = Utils::MemAlloc((n + 1)))){
			memcpy(ret, mem, n);
			((uint8_t*)ret)[n] = '\0';
		}
	}
	return ret;
}

void Utils::MemFree(void** mem)
{
	if (mem && *mem) {
		BrowserFuncs->memfree(*mem);
		*mem = NULL;
	}
}