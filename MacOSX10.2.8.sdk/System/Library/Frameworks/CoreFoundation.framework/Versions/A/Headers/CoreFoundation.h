/*	CoreFoundation.h
	Copyright 1998-2002, Apple, Inc. All rights reserved.
*/

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFBag.h>
#include <CoreFoundation/CFCharacterSet.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFDate.h>
#include <CoreFoundation/CFDictionary.h>
#include <CoreFoundation/CFNumber.h>
#include <CoreFoundation/CFPropertyList.h>
#include <CoreFoundation/CFSet.h>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFTimeZone.h>
#include <CoreFoundation/CFTree.h>
#include <CoreFoundation/CFURL.h>
#include <CoreFoundation/CFXMLNode.h>
#include <CoreFoundation/CFXMLParser.h>

#if TARGET_API_MAC_OS8

#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFPlugIn.h>
#include <CoreFoundation/CFPreferences.h>
#include <CoreFoundation/CFStringEncodingExt.h>
#include <CoreFoundation/CFURLAccess.h>
#include <CoreFoundation/CFUUID.h>

#else	/* Mac OS X */

#include <stdarg.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(__STDC_VERSION__) && (199901L <= __STDC_VERSION__)

//#include <complex.h>
//#include <fenv.h>
#include <inttypes.h>
//#include <iso646.h>
#include <stdbool.h>
#include <stdint.h>
//#include <tgmath.h>
//#include <wchar.h>
//#include <wctype.h>

#endif

#include <CoreFoundation/CFBinaryHeap.h>
#include <CoreFoundation/CFBitVector.h>
#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFByteOrder.h>
#include <CoreFoundation/CFPlugIn.h>
#include <CoreFoundation/CFURLAccess.h>
#include <CoreFoundation/CFUUID.h>

#if defined(__MACH__) || defined(__WIN32__)
#include <CoreFoundation/CFMachPort.h>
#include <CoreFoundation/CFMessagePort.h>
#include <CoreFoundation/CFRunLoop.h>
#include <CoreFoundation/CFSocket.h>
#endif

#if !defined(DARWIN)

#include <CoreFoundation/CFNotificationCenter.h>
#include <CoreFoundation/CFPreferences.h>
#include <CoreFoundation/CFStream.h>
#include <CoreFoundation/CFStringEncodingExt.h>
#include <CoreFoundation/CFUserNotification.h>

#endif /* !DARWIN */

#endif

