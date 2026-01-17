/*	CoreFoundation.h
	Copyright (c) 1998-2005, Apple, Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_COREFOUNDATION__)
#define __COREFOUNDATION_COREFOUNDATION__ 1
#define __COREFOUNDATION__ 1

#if !defined(CF_EXCLUDE_CSTD_HEADERS)

#include <sys/types.h>
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

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>

#endif

#endif

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
#include <CoreFoundation/CFStringEncodingExt.h>
#include <CoreFoundation/CFTimeZone.h>
#include <CoreFoundation/CFTree.h>
#include <CoreFoundation/CFURL.h>
#include <CoreFoundation/CFXMLNode.h>
#include <CoreFoundation/CFXMLParser.h>

#if defined(__MACH__) || defined(__WIN32__)
#include <CoreFoundation/CFMachPort.h>
#include <CoreFoundation/CFMessagePort.h>
#include <CoreFoundation/CFRunLoop.h>
#include <CoreFoundation/CFSocket.h>
#endif

#include <CoreFoundation/CFBinaryHeap.h>
#include <CoreFoundation/CFBitVector.h>
#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFByteOrder.h>
#include <CoreFoundation/CFPlugIn.h>
#include <CoreFoundation/CFPreferences.h>
#include <CoreFoundation/CFURLAccess.h>
#include <CoreFoundation/CFUUID.h>

#include <CoreFoundation/CFLocale.h>

#include <CoreFoundation/CFStream.h>

#if defined(__MACH__)

#ifndef CF_OPEN_SOURCE
#include <CoreFoundation/CFDateFormatter.h>
#include <CoreFoundation/CFNumberFormatter.h>
#include <CoreFoundation/CFCalendar.h>
#endif

#include <CoreFoundation/CFUserNotification.h>

#ifndef CF_OPEN_SOURCE
#include <CoreFoundation/CFNotificationCenter.h>
#include <CoreFoundation/CFAttributedString.h>
#endif // !CF_OPEN_SOURCE

#endif // __MACH__


#endif /* ! __COREFOUNDATION_COREFOUNDATION__ */

