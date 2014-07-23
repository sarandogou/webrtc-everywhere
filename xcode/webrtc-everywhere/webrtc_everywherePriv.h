/*
 *  webrtc_everywherePriv.h
 *  webrtc-everywhere
 *
 *  Created by Mamadou DIOP on 7/14/14.
 *  Copyright (c) 2014 sarandogou. All rights reserved.
 *
 */

#include <CoreFoundation/CoreFoundation.h>

#pragma GCC visibility push(hidden)

class Cwebrtc_everywhere {
	public:
		CFStringRef UUID(void);
};

#pragma GCC visibility pop
