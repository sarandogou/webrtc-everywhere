/*
 *  webrtc_everywhere.cp
 *  webrtc-everywhere
 *
 *  Created by Mamadou DIOP on 7/14/14.
 *  Copyright (c) 2014 sarandogou. All rights reserved.
 *
 */

#include "webrtc_everywhere.h"
#include "webrtc_everywherePriv.h"

CFStringRef webrtc_everywhereUUID(void)
{
	Cwebrtc_everywhere* theObj = new Cwebrtc_everywhere;
	return theObj->UUID();
}

CFStringRef Cwebrtc_everywhere::UUID()
{
	return CFSTR("0001020304050607");
}
