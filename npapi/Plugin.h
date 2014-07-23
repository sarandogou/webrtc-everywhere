/* Copyright(C) 2014 Sarandogou <https://github.com/sarandogou/webrtc-everywhere> */
#ifndef _WEBRTC_EVERYWHERE_NPAPI_PLUGIN_H_
#define _WEBRTC_EVERYWHERE_NPAPI_PLUGIN_H_

#include "../common/_Config.h"
#if WE_UNDER_WINDOWS
#include <Windows.h>
#endif
#include "npapi-includes.h"

#if !defined(NP_EXPORT)
#define NP_EXPORT(__type) __type
#endif

#if !defined(OSCALL)
#	if WE_UNDER_WINDOWS
#       define OSCALL WINAPI
#   else
#       define OSCALL
#   endif
#endif

#if defined(__GNUC__)
#pragma GCC visibility push(default)
#endif

#ifdef __cplusplus
extern "C" {
#endif

NPError OSCALL NP_Initialize(NPNetscapeFuncs* aNPNFuncs);
NPError OSCALL NP_GetEntryPoints(NPPluginFuncs* pluginFuncs);
NPError OSCALL NP_Shutdown();

NPError NPP_New(NPMIMEType pluginType, NPP instance, uint16_t mode, int16_t argc, char* argn[], char* argv[], NPSavedData* saved);
NPError NPP_Destroy(NPP instance, NPSavedData** save);
NPError NPP_SetWindow(NPP instance, NPWindow* window);
NPError NPP_NewStream(NPP instance, NPMIMEType type, NPStream* stream, NPBool seekable, uint16_t* stype);
NPError NPP_DestroyStream(NPP instance, NPStream* stream, NPReason reason);
int32_t NPP_WriteReady(NPP instance, NPStream* stream);
int32_t NPP_Write(NPP instance, NPStream* stream, int32_t offset, int32_t len, void* buffer);
void    NPP_StreamAsFile(NPP instance, NPStream* stream, const char* fname);
void    NPP_Print(NPP instance, NPPrint* platformPrint);
int16_t NPP_HandleEvent(NPP instance, void* event);
void    NPP_URLNotify(NPP instance, const char* URL, NPReason reason, void* notifyData);
NPError NPP_GetValue(NPP instance, NPPVariable variable, void *value);
NPError NPP_SetValue(NPP instance, NPNVariable variable, void *value);
    
#ifdef __cplusplus
}
#endif

#if defined(__GNUC__)
#pragma GCC visibility pop
#endif

#endif /* _WEBRTC_EVERYWHERE_NPAPI_PLUGIN_H_ */
