/*
     File:       OpenScripting/OSAComp.h
 
     Contains:   AppleScript Component Implementor's Interfaces.
 
     Version:    OSA-97~629
 
     Copyright:  © 1992-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __OSACOMP__
#define __OSACOMP__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************
    Types and Constants
**************************************************************************/
/**************************************************************************
    Routines for Associating a Storage Type with a Script Data Handle 
**************************************************************************/
/*
 *  OSAGetStorageType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSErr 
OSAGetStorageType(
  AEDataStorage   scriptData,
  DescType *      dscType)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OSAAddStorageType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSErr 
OSAAddStorageType(
  AEDataStorage   scriptData,
  DescType        dscType)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OSARemoveStorageType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSErr 
OSARemoveStorageType(AEDataStorage scriptData)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#ifdef __cplusplus
}
#endif

#endif /* __OSACOMP__ */

