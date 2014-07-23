#ifndef _WEBRTC_EVERYWHERE_NPAPI_INCLUDES_H_
#define _WEBRTC_EVERYWHERE_NPAPI_INCLUDES_H_

#include "../common/_Config.h"

#if WE_UNDER_APPLE
#include <WebKit/npapi.h>
#include <WebKit/npfunctions.h>
#include <WebKit/npruntime.h>
#else
#include "npapi-sdk/headers/npapi.h"
#include "npapi-sdk/headers/npfunctions.h"
#endif

#endif /* _WEBRTC_EVERYWHERE_NPAPI_INCLUDES_H_ */