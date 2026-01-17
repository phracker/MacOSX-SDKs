/*
     File:       CarbonCore/PLStringFuncs.h
 
     Contains:   Pascal string manipulation routines that parallel ANSI C string.h
 
     Version:    CarbonCore-317~6
 
     Copyright:  © 1999-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PLSTRINGFUNCS__
#define __PLSTRINGFUNCS__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif




#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
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
  ConstStr255Param   str2);


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
  short              num);


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
  ConstStr255Param   str2);


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
  short              num);


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
  ConstStr255Param   str2);


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
  short              num);


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
  short              ch1);


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
  short              ch1);


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
  ConstStr255Param   str2);


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
  ConstStr255Param   str2);


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
  ConstStr255Param   str2);


/*
 *  PLstrlen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   not available
 */
extern short 
PLstrlen(ConstStr255Param str);


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
  ConstStr255Param   str2);




#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __PLSTRINGFUNCS__ */

