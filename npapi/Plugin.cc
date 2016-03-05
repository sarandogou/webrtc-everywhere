/* Copyright(C) 2014-2016 Doubango Telecom <https://github.com/sarandogou/webrtc-everywhere> */
#include "../common/_Debug.h"
#include "../common/_AsyncEvent.h"
#include "../common/_Common.h"
#include "../common/_Utils.h"
#include "plugin.h"
#include "WebRTC.h"

#define kPluginName					"WebRTC plugin for Safari, Opera, Firefox and IE[" kPluginVersionString "]"
#define kPluginDescription			kPluginName " (DBG Telecom)"

NPNetscapeFuncs* BrowserFuncs = NULL;

extern NPClass WebRTCClass;

typedef struct PluginInstance {
    NPP npp;
    NPWindow window;
    NPObject* object;
#if WE_UNDER_APPLE
    CALayer *rootLayer;
#endif
} PluginInstance;

NPError OSCALL
NP_Initialize(NPNetscapeFuncs* browserFuncs)
{
    /* Save the browser function table. */
    BrowserFuncs = browserFuncs;

	_Utils::Initialize();
	TakeFakePeerConnectionFactory();

    return NPERR_NO_ERROR;
}

NPError OSCALL
NP_GetEntryPoints(NPPluginFuncs* pluginFuncs)
{
    /* Check the size of the provided structure based on the offset of the
       last member we need. */
    if (pluginFuncs->size < (offsetof(NPPluginFuncs, setvalue) + sizeof(void*))) {
        CHECK_NPERR_RETURN(NPERR_INVALID_FUNCTABLE_ERROR);
    }

    pluginFuncs->newp = NPP_New;
    pluginFuncs->destroy = NPP_Destroy;
    pluginFuncs->setwindow = NPP_SetWindow;
    pluginFuncs->newstream = NPP_NewStream;
    pluginFuncs->destroystream = NPP_DestroyStream;
    pluginFuncs->asfile = NPP_StreamAsFile;
    pluginFuncs->writeready = NPP_WriteReady;
    pluginFuncs->write = (NPP_WriteProcPtr)NPP_Write;
    pluginFuncs->print = NPP_Print;
    pluginFuncs->event = NPP_HandleEvent;
    pluginFuncs->urlnotify = NPP_URLNotify;
    pluginFuncs->getvalue = NPP_GetValue;
    pluginFuncs->setvalue = NPP_SetValue;

    return NPERR_NO_ERROR;
}

char*
NP_GetPluginVersion()
{
	return ((char*)kPluginVersionString);
}

const char*
NP_GetMIMEDescription()
{
	return (kPluginMIMEType);
}

NP_EXPORT(NPError)
NP_GetValue(void* future, NPPVariable aVariable, void* aValue)
{
    switch (aVariable) {
    case NPPVpluginNameString:
        *((char**)aValue) = (char*)(kPluginName);
        break;
    case NPPVpluginDescriptionString:
		*((char**)aValue) = (char*)(kPluginDescription);
        break;
    default:
        CHECK_NPERR_RETURN(NPERR_INVALID_PARAM);
    }
    return NPERR_NO_ERROR;
}

NP_EXPORT(NPError) OSCALL
NP_Shutdown()
{
	ReleaseFakePeerConnectionFactory();

    return NPERR_NO_ERROR;
}

NPError
NPP_New(NPMIMEType pluginType, NPP instance, uint16_t mode, int16_t argc, char* argn[], char* argv[], NPSavedData* saved)
{
	NPBool browserSupportsWindowless = false;
    if (we_stricmp(kPluginMIMEType, pluginType)) {
        WE_DEBUG_ERROR("'%s' not valid MIME type. Expected '%s'", pluginType, kPluginMIMEType);
        CHECK_NPERR_RETURN(NPERR_INCOMPATIBLE_VERSION_ERROR);
    }

    // Make sure we can render this plugin
    BrowserFuncs->getvalue(instance, NPNVSupportsWindowless, &browserSupportsWindowless);
    if (!browserSupportsWindowless) {
        printf("Windowless mode not supported by the browser\n");
    }
	
#if WE_UNDER_WINDOWS
	NPBool supportsAsyncBitmapSurface = FALSE;
	if (BrowserFuncs->getvalue(instance, NPNVsupportsAsyncBitmapSurfaceBool, &supportsAsyncBitmapSurface) != NPERR_NO_ERROR) {
		supportsAsyncBitmapSurface = FALSE;
	}
	NPBool supportsAsyncWindowsDXGISurfaceBool = FALSE;
	if (BrowserFuncs->getvalue(instance, NPNVsupportsAsyncWindowsDXGISurfaceBool, &supportsAsyncWindowsDXGISurfaceBool) != NPERR_NO_ERROR) {
		supportsAsyncWindowsDXGISurfaceBool = FALSE;
	}
#endif

#if WE_UNDER_APPLE
    // Ask the browser if it supports the Core Animation drawing model
	NPBool supportsCoreAnimation = FALSE;
    if (BrowserFuncs->getvalue(instance, NPNVsupportsCoreAnimationBool, &supportsCoreAnimation) != NPERR_NO_ERROR) {
        supportsCoreAnimation = FALSE;
    }
    
    if (!supportsCoreAnimation) {
        WE_DEBUG_ERROR("CoreAnimation not supported");
        CHECK_NPERR_RETURN(NPERR_INCOMPATIBLE_VERSION_ERROR);
    }
    
    // If the browser supports the Core Animation drawing model, enable it.
    BrowserFuncs->setvalue(instance, NPPVpluginDrawingModel, (void *)NPDrawingModelCoreAnimation);
    
    // If the browser supports the Cocoa event model, enable it.
    NPBool supportsCocoa;
    if (BrowserFuncs->getvalue(instance, NPNVsupportsCocoaBool, &supportsCocoa) != NPERR_NO_ERROR) {
        supportsCocoa = FALSE;
    }
    
    if (!supportsCocoa) {
        WE_DEBUG_ERROR("Cocoa not supported...but not required");
        // return NPERR_INCOMPATIBLE_VERSION_ERROR;
    }
    else {
        BrowserFuncs->setvalue(instance, NPPVpluginEventModel, (void *)NPEventModelCocoa);
    }
#endif

	if (browserSupportsWindowless) {
		bool bWindowed = true/*(instanceData->type == PluginType_WebRtc4npapi || instanceData->type == PluginType_Display)*/;
		BrowserFuncs->setvalue(instance, NPPVpluginWindowBool, (void*)bWindowed);
	}

    // set up our our instance data
    PluginInstance *newInstance = (PluginInstance*)malloc(sizeof(PluginInstance));
    if (!newInstance) {
        CHECK_NPERR_RETURN(NPERR_OUT_OF_MEMORY_ERROR);
    }
    memset(newInstance, 0, sizeof(PluginInstance));
    newInstance->npp = instance;
    instance->pdata = newInstance;

    return NPERR_NO_ERROR;
}

NPError
NPP_Destroy(NPP instance, NPSavedData** save)
{
    PluginInstance* pluginInstance = (PluginInstance*)(instance->pdata);
    if (pluginInstance) {
        if (pluginInstance->object) {
            SafeReleaseNPObject(&pluginInstance->object);
        }
#if WE_UNDER_APPLE
        if (pluginInstance->rootLayer) {
            [pluginInstance->rootLayer release], pluginInstance->rootLayer = NULL;
        }
#endif
        free(pluginInstance);
    }
    return NPERR_NO_ERROR;
}

NPError
NPP_SetWindow(NPP instance, NPWindow* window)
{
    PluginInstance* pluginInstance = (PluginInstance*)(instance->pdata);
    if (pluginInstance) {
        pluginInstance->window = *window;
    }
    return NPERR_NO_ERROR;
}

NPError
NPP_NewStream(NPP instance, NPMIMEType type, NPStream* stream, NPBool seekable, uint16_t* stype)
{
    return NPERR_GENERIC_ERROR;
}

NPError
NPP_DestroyStream(NPP instance, NPStream* stream, NPReason reason)
{
    return NPERR_GENERIC_ERROR;
}

int32_t
NPP_WriteReady(NPP instance, NPStream* stream)
{
    return 0;
}

int32_t
NPP_Write(NPP instance, NPStream* stream, int32_t offset, int32_t len, void* buffer)
{
    return 0;
}

void
NPP_StreamAsFile(NPP instance, NPStream* stream, const char* fname)
{

}

void
NPP_Print(NPP instance, NPPrint* platformPrint)
{

}

int16_t
NPP_HandleEvent(NPP instance, void* event)
{
    // PluginInstance* pluginInstance = (PluginInstance*)(instance->pdata);
    return 1;
}

void
NPP_URLNotify(NPP instance, const char* URL, NPReason reason, void* notifyData)
{

}

NPError
NPP_GetValue(NPP instance, NPPVariable variable, void *value)
{
    PluginInstance* pluginInstance = (PluginInstance*)(instance->pdata);

    switch (variable) {
    default: {
        return NPERR_GENERIC_ERROR;
    }
    case NPPVpluginNameString: {
        *((char **)value) = (char*)kPluginName;
        return NPERR_NO_ERROR;
    }
    case NPPVpluginDescriptionString: {
        *((char **)value) = (char*)kPluginDescription;
        return NPERR_NO_ERROR;
    }
#if WE_UNDER_APPLE
        case NPPVpluginCoreAnimationLayer: {
            if (!pluginInstance->rootLayer) {
                pluginInstance->rootLayer = [[CALayer layer] retain];
                pluginInstance->rootLayer.autoresizingMask = kCALayerWidthSizable | kCALayerHeightSizable;
            }
             *(CALayer **)value = pluginInstance->rootLayer;
            return NPERR_NO_ERROR;
        }
#endif /* WE_UNDER_APPLE */
    case NPPVpluginScriptableNPObject: {
        if (!pluginInstance->object) {
            if (!(pluginInstance->object = BrowserFuncs->createobject(pluginInstance->npp, &WebRTCClass))) {
                return NPERR_OUT_OF_MEMORY_ERROR;
			}
        }
		WebRTC* webrtc = reinterpret_cast<WebRTC*>((WebRTC*)pluginInstance->object);
#if WE_UNDER_WINDOWS
		if (webrtc) {
			if (!webrtc->SetWindow(reinterpret_cast<HWND>(pluginInstance->window.window))) {
				return NPERR_GENERIC_ERROR;
			}
		}
#endif /* WE_UNDER_WINDOWS */
        
#if WE_UNDER_APPLE
        if (webrtc) {
            webrtc->SetRootLayer(pluginInstance->rootLayer);
        }
        /*if (pluginInstance->rootLayer) {
            [pluginInstance->rootLayer setBounds: CGRectMake(pluginInstance->window.x, pluginInstance->window.y, pluginInstance->window.width, pluginInstance->window.height)];
        }*/
#endif /* WE_UNDER_APPLE */
		
        BrowserFuncs->retainobject(pluginInstance->object);
		*(NPObject **)value = pluginInstance->object;
        return NPERR_NO_ERROR;
    }
        case NPPVpluginNeedsXEmbed:
        {
            *((char *)value) = 1;
            return NPERR_NO_ERROR;
        }
    }
}

NPError
NPP_SetValue(NPP instance, NPNVariable variable, void *value)
{
    return NPERR_GENERIC_ERROR;
}

