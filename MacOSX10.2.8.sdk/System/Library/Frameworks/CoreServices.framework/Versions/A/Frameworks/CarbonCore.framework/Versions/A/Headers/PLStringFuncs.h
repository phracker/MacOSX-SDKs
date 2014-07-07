/*
     File:       CarbonCore/PLStringFuncs.h
 
     Contains:   Pascal string manipulation routines that parallel ANSI C string.h
 
     Version:    CarbonCore-472~1
 
     Copyright:  © 1999-2002 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PLSTRINGFUNCS__
#define __PLSTRINGFUNCS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  PLstrcmp()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern short 
PLstrcmp(
  ConstStr255Param   str1,
  ConstStr255Param   str2)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PLstrncmp()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern short 
PLstrncmp(
  ConstStr255Param   str1,
  ConstStr255Param   str2,
  short              num)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PLstrcpy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern StringPtr 
PLstrcpy(
  StringPtr          str1,
  ConstStr255Param   str2)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PLstrncpy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern StringPtr 
PLstrncpy(
  StringPtr          str1,
  ConstStr255Param   str2,
  short              num)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PLstrcat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern StringPtr 
PLstrcat(
  StringPtr          str1,
  ConstStr255Param   str2)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PLstrncat()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern StringPtr 
PLstrncat(
  StringPtr          str1,
  ConstStr255Param   str2,
  short              num)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PLstrchr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Ptr 
PLstrchr(
  ConstStr255Param   str1,
  short              ch1)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PLstrrchr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Ptr 
PLstrrchr(
  ConstStr255Param   str1,
  short              ch1)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PLstrpbrk()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Ptr 
PLstrpbrk(
  ConstStr255Param   str1,
  ConstStr255Param   str2)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PLstrspn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern short 
PLstrspn(
  ConstStr255Param   str1,
  ConstStr255Param   str2)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PLstrstr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern Ptr 
PLstrstr(
  ConstStr255Param   str1,
  ConstStr255Param   str2)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PLstrlen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern short 
PLstrlen(ConstStr255Param str)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PLpos()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern short 
PLpos(
  ConstStr255Param   str1,
  ConstStr255Param   str2)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




#ifdef __cplusplus
}
#endif

#endif /* __PLSTRINGFUNCS__ */

