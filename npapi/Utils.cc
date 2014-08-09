/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#include "Utils.h"
#include "NPCommon.h"

#include "../common/_Buffer.h"
#include "../common/_Debug.h"

extern NPNetscapeFuncs* BrowserFuncs;

NPIdentifier Utils::s_funcID_WE00_dataChannelSendBlob = 0;
NPIdentifier Utils::s_funcID_WE01_wrapArrayBufferIntoUint8Array = 0;

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

NPError Utils::NPVariantRelease(NPVariant** var)
{
	if (var && *var) {
		NPError err = NPERR_NO_ERROR;
		if ((*var)->type == NPVariantType_Object) {
			err = Utils::NPObjectRelease(&(*var)->value.objectValue);
		}
		else {
			BrowserFuncs->releasevariantvalue(*var);
		}
		*var = NULL;
		return err;
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

NPError Utils::CreateJsArrayEx(NPP npp, std::vector<NPVariant> &vecValues, const NPUTF8* arrayClassName, NPObject** arrayObj)
{
	if (!arrayObj || *arrayObj || !arrayClassName) {
		CHECK_NPERR_RETURN(NPERR_INVALID_PARAM);
	}
	NPObject* npWindow = NULL;
	NPError err;

	CHECK_NPERR_RETURN(err = BrowserFuncs->getvalue(npp, NPNVWindowNPObject, &npWindow));

	NPVariant var;
	bool bRet;

#if 1
	NPUTF8 createArrayEvalString[1024];
	NPString npCreateArrayEvalString = { 0 };
	sprintf(createArrayEvalString, "new %s(%zu)", arrayClassName, vecValues.size());
	npCreateArrayEvalString.UTF8Characters = createArrayEvalString;
	npCreateArrayEvalString.UTF8Length = strlen(createArrayEvalString);
	bRet = BrowserFuncs->evaluate(npp, npWindow, &npCreateArrayEvalString, &var);
#else

	NPVariant args[1];
	INT32_TO_NPVARIANT(vecValues.size(), args[0]);
	NPIdentifier classId = BrowserFuncs->getstringidentifier(arrayClassName);
	bRet = BrowserFuncs->invoke(npp, npWindow, classId, args, sizeof(args) / sizeof(args[0]), &var);
#endif

	BrowserFuncs->releaseobject(npWindow);
	if (!bRet || var.type != NPVariantType_Object || !var.value.objectValue) {
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
	*arrayObj = var.value.objectValue;

	NPUTF8 index[25];
	for (size_t i = 0; i < vecValues.size(); ++i) {
		sprintf(index, "%ld", i);
		/*bRet =*/ BrowserFuncs->setproperty(npp, *arrayObj, BrowserFuncs->getstringidentifier(index), &vecValues[i]);
	}
	return NPERR_NO_ERROR;
}

NPError Utils::CreateJsArray(NPP npp, std::vector<NPVariant> &vecValues, NPObject** arrayObj)
{
	return Utils::CreateJsArrayEx(npp, vecValues, "Array", arrayObj);
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

bool Utils::NPObjectIsJsBLOB(NPP npp, NPObject* obj)
{
    if (obj) {
        NPVariant var;
        NPError err = NPObjectCallJsFunction(npp, obj, "toString", &var);
        if (err == NPERR_NO_ERROR && NPVARIANT_IS_STRING(var)) {
            return strncmp(var.value.stringValue.UTF8Characters, "[object Blob]", var.value.stringValue.UTF8Length) == 0;
        }
    }
    return false;
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

	if (NPVARIANT_IS_DOUBLE(var)) {
		number = var.value.doubleValue;
	}
	else if (NPVARIANT_IS_INT32(var)) {
		number = var.value.intValue;
	}
	else {
		BrowserFuncs->releasevariantvalue(&var);
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
	BrowserFuncs->releasevariantvalue(&var);
	return NPERR_NO_ERROR;
}

NPError Utils::NPObjectGetPropBool(NPP npp, NPObject* obj, const NPUTF8* name, bool& _bool)
{
	NPVariant var;
	CHECK_NPERR_RETURN(Utils::NPObjectGetProp(npp, obj, name, &var));

	if (NPVARIANT_IS_BOOLEAN(var)) {
		_bool = var.value.boolValue;
	}
	else {
		BrowserFuncs->releasevariantvalue(&var);
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
	BrowserFuncs->releasevariantvalue(&var);
	return NPERR_NO_ERROR;
}

NPError Utils::NPObjectCallJsFunction(NPP npp, NPObject* obj, const NPUTF8* name, NPVariant* var)
{
	if (!npp || !name || !var) {
		CHECK_NPERR_RETURN(NPERR_INVALID_PARAM);
	}
	VOID_TO_NPVARIANT(*var);
	NPIdentifier indentifier = BrowserFuncs->getstringidentifier(name);
	if (!BrowserFuncs->invoke(npp, obj, indentifier, NULL, 0, var)) {
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
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

NPError Utils::BuildRTCDataChannelInit(NPP npp, NPObject* varRTCDataChannelInit, cpp11::shared_ptr<_RTCDataChannelInit> &configuration)
{
	if (!varRTCDataChannelInit) {
		return NPERR_NO_ERROR;
	}

	configuration = cpp11::shared_ptr<_RTCDataChannelInit>(new _RTCDataChannelInit());
	NPError err;
	std::string string;
	bool _bool;
	double _double;


	// http://www.w3.org/TR/webrtc/#idl-def-RTCDataChannel
	if ((err = Utils::NPObjectGetPropString(npp, varRTCDataChannelInit, "protocol", string)) == NPERR_NO_ERROR) {
		configuration->protocol = string;
	}
	if ((err = Utils::NPObjectGetPropBool(npp, varRTCDataChannelInit, "protocol", _bool)) == NPERR_NO_ERROR) {
		configuration->ordered = _bool;
	}	
	if ((err = Utils::NPObjectGetPropNumber(npp, varRTCDataChannelInit, "maxRetransmitTime", _double)) == NPERR_NO_ERROR) {
		configuration->maxRetransmitTime = (nullable_ushort)_double;
	}
	if ((err = Utils::NPObjectGetPropNumber(npp, varRTCDataChannelInit, "maxRetransmits", _double)) == NPERR_NO_ERROR) {
		configuration->maxRetransmits = (nullable_ushort)_double;
	}
	if ((err = Utils::NPObjectGetPropBool(npp, varRTCDataChannelInit, "negotiated", _bool)) == NPERR_NO_ERROR) {
		configuration->negotiated = _bool;
	}
	if ((err = Utils::NPObjectGetPropNumber(npp, varRTCDataChannelInit, "id", _double)) == NPERR_NO_ERROR) {
		configuration->id = (nullable_ushort)_double;
	}
	return NPERR_NO_ERROR;
}

NPError Utils::BuildData(NPP npp, const NPVariant* varData, cpp11::shared_ptr<_Buffer> &data)
{
	if (!varData) {
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
	if (NPVARIANT_IS_STRING(*varData)) {
		data = cpp11::shared_ptr<_Buffer>(new _Buffer((const void*)varData->value.stringValue.UTF8Characters, (size_t)varData->value.stringValue.UTF8Length));
		return NPERR_NO_ERROR;
	}
	else if (NPVARIANT_IS_OBJECT(*varData)) {
		NPObject* _data = Utils::VariantToObject((NPVariant*)varData);
		if (!_data) {
			CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
		}

		_ArrayType arrayType = _ArrayType_None;
		NPError err;

		NPVariant var;
		CHECK_NPERR_RETURN(err = Utils::NPObjectCallJsFunction(npp, _data, "toString", &var));
		if (!NPVARIANT_IS_STRING(var)) {
			CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
		}

		if (strncmp(var.value.stringValue.UTF8Characters, "[object Int8Array]", var.value.stringValue.UTF8Length) == 0) {
			arrayType = _ArrayType_Int8Array;
		}
		else if (strncmp(var.value.stringValue.UTF8Characters, "[object Uint8Array]", var.value.stringValue.UTF8Length) == 0) {
			arrayType = _ArrayType_Uint8Array;
		}
		else if (strncmp(var.value.stringValue.UTF8Characters, "[object Uint8ClampedArray]", var.value.stringValue.UTF8Length) == 0) {
			arrayType = _ArrayType_Uint8ClampedArray;
		}
		else if (strncmp(var.value.stringValue.UTF8Characters, "[object Int16Array]", var.value.stringValue.UTF8Length) == 0) {
			arrayType = _ArrayType_Int16Array;
		}
		else if (strncmp(var.value.stringValue.UTF8Characters, "[object Uint16Array]", var.value.stringValue.UTF8Length) == 0) {
			arrayType = _ArrayType_Uint16Array;
		}
		else if (strncmp(var.value.stringValue.UTF8Characters, "[object Int32Array]", var.value.stringValue.UTF8Length) == 0) {
			arrayType = _ArrayType_Int32Array;
		}
		else if (strncmp(var.value.stringValue.UTF8Characters, "[object Uint32Array]", var.value.stringValue.UTF8Length) == 0) {
			arrayType = _ArrayType_Uint32Array;
		}
		else if (strncmp(var.value.stringValue.UTF8Characters, "[object Float32Array]", var.value.stringValue.UTF8Length) == 0) {
			arrayType = _ArrayType_Float32Array;
		}
		else if (strncmp(var.value.stringValue.UTF8Characters, "[object Float64Array]", var.value.stringValue.UTF8Length) == 0) {
			arrayType = _ArrayType_Float64Array;
		}
        else if (strncmp(var.value.stringValue.UTF8Characters, "[object ArrayBuffer]", var.value.stringValue.UTF8Length) == 0) {
            NPObject *uint8Array = NULL;
            CHECK_NPERR_RETURN(Utils::WrapArrayBufferIntoUint8Array(npp, _data, &uint8Array));
            OBJECT_TO_NPVARIANT(uint8Array, var);
            NPError err = Utils::BuildData(npp, &var, data);
            BrowserFuncs->releasevariantvalue(&var);
            return err;
		}

		if (arrayType != _ArrayType_None) {
			return Utils::BuildDataArray(npp, _data, arrayType, data);
		}
	}

	CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);

	return NPERR_GENERIC_ERROR;
}

NPError Utils::BuildDataArray(NPP npp, NPObject* varData, _ArrayType arrayType, cpp11::shared_ptr<_Buffer> &data)
{
	if (!varData || arrayType == _ArrayType_None) {
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}

	int byteCount = _Utils::ArrayBytesCount(arrayType);
	if (byteCount <= 0) {
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}

	double length;
	NPError err;

	CHECK_NPERR_RETURN(err = Utils::NPObjectGetPropNumber(npp, varData, "length", length));

	data = cpp11::shared_ptr<_Buffer>(new _Buffer((const void*)NULL, (size_t)(length * byteCount)));
	if (!data.get() || !data->getPtr()) {
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
	uint8_t* ptr = reinterpret_cast<uint8_t*>(const_cast<void*>(data->getPtr()));

	bool isFloatingPoint = _Utils::ArrayIsFloatingPoint(arrayType);

	char s[25];
	double _double;
	for (long i = 0; i < length; ++i) {
		sprintf(s, "%ld", i);
		CHECK_NPERR_RETURN(err = Utils::NPObjectGetPropNumber(npp, varData, s, _double));
		if (isFloatingPoint) {
			switch (arrayType) {
			case _ArrayType_Float32Array: *((float*)ptr) = (float)_double; break;
			case _ArrayType_Float64Array: *((double*)ptr) = _double; break;
			default: CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
			}
		}
		else {
			switch (arrayType) {
			case _ArrayType_Int8Array: *((int8_t*)ptr) = (int8_t)_double; break;
			case _ArrayType_Uint8Array: *((uint8_t*)ptr) = (uint8_t)_double; break;
			case _ArrayType_Uint8ClampedArray: *((uint8_t*)ptr) = (uint8_t)(_double < 0 ? 0 : (_double > 255 ? 255 : _double)); break;
			case _ArrayType_Int16Array: *((int16_t*)ptr) = ((int16_t)_double); break;
			case _ArrayType_Uint16Array: *((uint16_t*)ptr) = ((uint16_t)_double); break;
			case _ArrayType_Int32Array: *((int32_t*)ptr) = (int32_t)_double; break;
			case _ArrayType_Uint32Array: *((uint32_t*)ptr) = (uint32_t)_double; break;
			default: CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
			}
		}
		ptr += byteCount;
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

NPError Utils::GetLocation(NPP npp, NPVariant* protocol, NPVariant *host)
{
	if (!protocol || !host) {
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}

	VOID_TO_NPVARIANT(*protocol);
	VOID_TO_NPVARIANT(*host);

	NPObject* npWindow = NULL;
	NPError err;
	NPVariant var;

	CHECK_NPERR_RETURN(err = BrowserFuncs->getvalue(npp, NPNVWindowNPObject, &npWindow));

	if (!BrowserFuncs->getproperty(npp, npWindow, BrowserFuncs->getstringidentifier("location"), &var) || !NPVARIANT_IS_OBJECT(var)) {
		Utils::NPObjectRelease(&npWindow);
		CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
	}
	Utils::NPObjectRelease(&npWindow);

	err = Utils::NPObjectGetProp(npp, var.value.objectValue, "protocol", protocol);
	if (err == NPERR_NO_ERROR) {
		err = Utils::NPObjectGetProp(npp, var.value.objectValue, "host", host);
	}
	BrowserFuncs->releasevariantvalue(&var);

	if (err != NPERR_NO_ERROR) {
		BrowserFuncs->releasevariantvalue(protocol);
		BrowserFuncs->releasevariantvalue(host);
	}

	return err;
}

NPError Utils::InstallScripts(NPP npp)
{
    static bool g_installed = false;
    
	if (g_installed) {
		return NPERR_NO_ERROR;
	}
    
	typedef struct script {
		const NPUTF8* funcName = NULL;
		NPIdentifier* funcID = NULL;
		const NPUTF8* code = NULL;
		script(const NPUTF8* _funcName, NPIdentifier* _funcID, const NPUTF8* _code) : funcName(_funcName), funcID(_funcID), code(_code) {}
	} script;
    
	static const NPUTF8 __script00[] = "window.WE00_dataChannelSendBlob = function(dataChannel, blob) {"
    "var reader = new FileReader();"
    "attachEventListener(reader, 'loadend', function() {"
    "dataChannel.send(reader.result);"
    "});"
    "reader.readAsArrayBuffer(blob);"
    "}";
	static const NPUTF8 __script001[] = "window.WE01_wrapArrayBufferIntoUint8Array = function(arrayBuffer) { return new Uint8Array(arrayBuffer) }";
	static script __scripts[] = { { "WE00_dataChannelSendBlob", &Utils::s_funcID_WE00_dataChannelSendBlob, __script00 }, { "WE01_wrapArrayBufferIntoUint8Array", &Utils::s_funcID_WE01_wrapArrayBufferIntoUint8Array, __script001 } };
    
    NPVariant var;
	NPError err = NPERR_NO_ERROR;
    NPObject* npWindow = NULL;
    NPString npScript = { 0 };
    
    CHECK_NPERR_BAIL(err = BrowserFuncs->getvalue(npp, NPNVWindowNPObject, &npWindow));
    
	for (size_t i = 0; i < sizeof(__scripts) / sizeof(__scripts[0]); ++i) {
        npScript.UTF8Characters = __scripts[i].code;
        npScript.UTF8Length = we_strlen(npScript.UTF8Characters);
        if (!BrowserFuncs->evaluate(npp, npWindow, &npScript, &var)) {
            CHECK_NPERR_BAIL(err = NPERR_GENERIC_ERROR);
        }
        *__scripts[i].funcID = BrowserFuncs->getstringidentifier(__scripts[i].funcName);
        BrowserFuncs->releasevariantvalue(&var);
	}
	g_installed = true;
    
bail:
    if (npWindow) {
        BrowserFuncs->releaseobject(npWindow);
    }
	return err;
}

NPError Utils::WrapArrayBufferIntoUint8Array(NPP npp, NPObject* arrayBuffer, NPObject ** uint8Array)
{
    if (!arrayBuffer || !uint8Array || *uint8Array) {
        CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
    }
    NPVariant var;
	NPError err = NPERR_NO_ERROR;
    NPObject* npWindow = NULL;
    NPVariant args[1];
    bool ret;
    
    CHECK_NPERR_BAIL(err = Utils::InstallScripts(npp));
    
    CHECK_NPERR_BAIL(err = BrowserFuncs->getvalue(npp, NPNVWindowNPObject, &npWindow));
    
    OBJECT_TO_NPVARIANT(arrayBuffer, args[0]);
    VOID_TO_NPVARIANT(var);
    ret = BrowserFuncs->invoke(npp, npWindow, Utils::s_funcID_WE01_wrapArrayBufferIntoUint8Array, args, sizeof(args)/sizeof(args[0]), &var);
    if (!ret || !NPVARIANT_IS_OBJECT(var) || !var.value.objectValue) {
        CHECK_NPERR_BAIL(err = NPERR_GENERIC_ERROR);
    }
    *uint8Array = var.value.objectValue;
                                    
bail:
    if (npWindow) {
        BrowserFuncs->releaseobject(npWindow);
    }
	return err;
}

NPError Utils::DataChannelSendBlob(NPP npp, NPObject * dataChannel, NPObject* blob)
{
    if (!dataChannel || !blob) {
        CHECK_NPERR_RETURN(NPERR_GENERIC_ERROR);
    }
    NPVariant var;
	NPError err = NPERR_NO_ERROR;
    NPObject* npWindow = NULL;
    NPVariant args[2];
    
    CHECK_NPERR_BAIL(err = Utils::InstallScripts(npp));
    
    CHECK_NPERR_BAIL(err = BrowserFuncs->getvalue(npp, NPNVWindowNPObject, &npWindow));
    
    OBJECT_TO_NPVARIANT(dataChannel, args[0]);
    OBJECT_TO_NPVARIANT(blob, args[1]);
    VOID_TO_NPVARIANT(var);
    
    if (!BrowserFuncs->invoke(npp, npWindow, Utils::s_funcID_WE00_dataChannelSendBlob, args, sizeof(args)/sizeof(args[0]), &var)) {
        CHECK_NPERR_BAIL(err = NPERR_GENERIC_ERROR);
    }
    
bail:
    if (npWindow) {
        BrowserFuncs->releaseobject(npWindow);
    }
	return err;
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