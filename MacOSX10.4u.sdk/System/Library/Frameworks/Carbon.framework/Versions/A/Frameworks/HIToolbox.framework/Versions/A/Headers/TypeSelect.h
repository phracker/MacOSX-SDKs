/*
     File:       HIToolbox/TypeSelect.h
 
     Contains:   TypeSelect Utilties
 
     Version:    HIToolbox-227.3~63
 
     Copyright:  © 2000-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __TYPESELECT__
#define __TYPESELECT__

#ifndef __EVENTS__
#include <HIToolbox/Events.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

typedef SInt16 TSCode;
enum {
  tsPreviousSelectMode          = -1,
  tsNormalSelectMode            = 0,
  tsNextSelectMode              = 1
};

struct TypeSelectRecord {
  unsigned long       tsrLastKeyTime;
  ScriptCode          tsrScript;
  Str63               tsrKeyStrokes;
};
typedef struct TypeSelectRecord         TypeSelectRecord;
typedef CALLBACK_API( Boolean , IndexToStringProcPtr )(short item, ScriptCode *itemsScript, StringPtr *itemsStringPtr, void *yourDataPtr);
typedef STACK_UPP_TYPE(IndexToStringProcPtr)                    IndexToStringUPP;
/*
 *  TypeSelectClear()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFStringUppercase instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFStringUppercase instead.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
TypeSelectClear(TypeSelectRecord * tsr)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
        Long ago the implementation of TypeSelectNewKey had a bug that
        required the high word of D0 to be zero or the function did not work.
        Although fixed now, we are continuing to clear the high word
        just in case someone tries to run on an older system.
    */
/*
 *  TypeSelectNewKey()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use UCTypeSelect instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use UCTypeSelect
 *    instead.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
TypeSelectNewKey(
  const EventRecord *  theEvent,
  TypeSelectRecord *   tsr)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  TypeSelectFindItem()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use UCTypeSelect instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use UCTypeSelect
 *    instead.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern short 
TypeSelectFindItem(
  const TypeSelectRecord *  tsr,
  short                     listSize,
  TSCode                    selectMode,
  IndexToStringUPP          getStringProc,
  void *                    yourDataPtr)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;



/*
 *  TypeSelectCompare()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    use CFStringUppercase instead.
 *  
 *  Discussion:
 *    This function is no longer recommended. Please use
 *    CFStringUppercase instead.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern short 
TypeSelectCompare(
  const TypeSelectRecord *  tsr,
  ScriptCode                testStringScript,
  StringPtr                 testStringPtr)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  NewIndexToStringUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern IndexToStringUPP
NewIndexToStringUPP(IndexToStringProcPtr userRoutine)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeIndexToStringUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeIndexToStringUPP(IndexToStringUPP userUPP)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeIndexToStringUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeIndexToStringUPP(
  short             item,
  ScriptCode *      itemsScript,
  StringPtr *       itemsStringPtr,
  void *            yourDataPtr,
  IndexToStringUPP  userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __TYPESELECT__ */

