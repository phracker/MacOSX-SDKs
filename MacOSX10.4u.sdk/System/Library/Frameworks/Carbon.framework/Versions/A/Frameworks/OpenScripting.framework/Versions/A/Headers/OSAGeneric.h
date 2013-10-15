/*
     File:       OpenScripting/OSAGeneric.h
 
     Contains:   AppleScript Generic Component Interfaces.
 
     Version:    OSA-97~629
 
     Copyright:  © 1992-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __OSAGENERIC__
#define __OSAGENERIC__

#ifndef __APPLICATIONSERVICES__
#include <ApplicationServices/ApplicationServices.h>
#endif

#ifndef __OSA__
#include <OpenScripting/OSA.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*    NOTE:   This interface defines a "generic scripting component."
            The Generic Scripting Component allows automatic dispatch to a
            specific scripting component that conforms to the OSA interface.
            This component supports OSA, by calling AppleScript or some other 
            scripting component.  Additionally it provides access to the default
            and the user-prefered scripting component.
*/


enum {
                                        /* Component version this header file describes */
  kGenericComponentVersion      = 0x0100
};

enum {
  kGSSSelectGetDefaultScriptingComponent = 0x1001,
  kGSSSelectSetDefaultScriptingComponent = 0x1002,
  kGSSSelectGetScriptingComponent = 0x1003,
  kGSSSelectGetScriptingComponentFromStored = 0x1004,
  kGSSSelectGenericToRealID     = 0x1005,
  kGSSSelectRealToGenericID     = 0x1006,
  kGSSSelectOutOfRange          = 0x1007
};

typedef OSType                          ScriptingComponentSelector;
typedef OSAID                           GenericID;
/* get and set the default scripting component */
/*
 *  OSAGetDefaultScriptingComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
OSAGetDefaultScriptingComponent(
  ComponentInstance             genericScriptingComponent,
  ScriptingComponentSelector *  scriptingSubType)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OSASetDefaultScriptingComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
OSASetDefaultScriptingComponent(
  ComponentInstance            genericScriptingComponent,
  ScriptingComponentSelector   scriptingSubType)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* get a scripting component instance from its subtype code */
/*
 *  OSAGetScriptingComponent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
OSAGetScriptingComponent(
  ComponentInstance            genericScriptingComponent,
  ScriptingComponentSelector   scriptingSubType,
  ComponentInstance *          scriptingInstance)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* get a scripting component selector (subType) from a stored script */
/*
 *  OSAGetScriptingComponentFromStored()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
OSAGetScriptingComponentFromStored(
  ComponentInstance             genericScriptingComponent,
  const AEDesc *                scriptData,
  ScriptingComponentSelector *  scriptingSubType)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* get a real component instance and script id from a generic id */
/*
 *  OSAGenericToRealID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
OSAGenericToRealID(
  ComponentInstance    genericScriptingComponent,
  OSAID *              theScriptID,
  ComponentInstance *  theExactComponent)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* get a generic id from a real component instance and script id */
/*
 *  OSARealToGenericID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in AppleScriptLib 1.1 and later
 */
extern OSAError 
OSARealToGenericID(
  ComponentInstance   genericScriptingComponent,
  OSAID *             theScriptID,
  ComponentInstance   theExactComponent)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





#ifdef __cplusplus
}
#endif

#endif /* __OSAGENERIC__ */

