/*
     File:       Print/PMApplicationDeprecated.h
 
     Contains:   Deprecated Carbon Printing Manager Interfaces.
 
	 Copyright  (c) 1998-2006, 2008, 2011 Apple Inc. All Rights Reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __PMAPPLICATION_DEPRECATED__
#define __PMAPPLICATION_DEPRECATED__

#if !__LP64__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifndef __DIALOGS__
#include <HIToolbox/Dialogs.h>
#endif

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  PMSessionBeginDocument()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Instead use PMSessionBeginCGDocument.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
PMSessionBeginDocument(
  PMPrintSession    printSession,
  PMPrintSettings   printSettings,
  PMPageFormat      pageFormat)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


#ifdef __cplusplus
}
#endif

#endif  /* !__LP64__ */

#endif	/* __PMAPPLICATION_DEPRECATED__ */

