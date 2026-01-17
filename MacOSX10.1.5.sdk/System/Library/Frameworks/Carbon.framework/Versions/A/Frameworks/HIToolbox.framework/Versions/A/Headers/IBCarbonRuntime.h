/*
     File:       HIToolbox/IBCarbonRuntime.h
 
     Contains:   Nib support for Carbon
 
     Version:    HIToolbox-79.9~1
 
     Copyright:  © 2000-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __IBCARBONRUNTIME__
#define __IBCARBONRUNTIME__

#ifndef __CARBONCORE__
#include <CarbonCore/CarbonCore.h>
#endif

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifndef __MACWINDOWS__
#include <HIToolbox/MacWindows.h>
#endif

#ifndef __MENUS__
#include <HIToolbox/Menus.h>
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

enum {
  kIBCarbonRuntimeCantFindNibFile = -10960,
  kIBCarbonRuntimeObjectNotOfRequestedType = -10961,
  kIBCarbonRuntimeCantFindObject = -10962
};

/* ----- typedef ------ */
typedef struct OpaqueIBNibRef*          IBNibRef;
/* ----- Create & Dispose NIB References ------ */
/*
 *  CreateNibReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateNibReference(
  CFStringRef   inNibName,
  IBNibRef *    outNibRef);


/*
 *  CreateNibReferenceWithCFBundle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateNibReferenceWithCFBundle(
  CFBundleRef   inBundle,
  CFStringRef   inNibName,
  IBNibRef *    outNibRef);


/*
 *  DisposeNibReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
DisposeNibReference(IBNibRef inNibRef);


/* ----- Window ------ */
/*
 *  CreateWindowFromNib()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateWindowFromNib(
  IBNibRef      inNibRef,
  CFStringRef   inName,
  WindowRef *   outWindow);


/* ----- Menu -----*/

/*
 *  CreateMenuFromNib()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateMenuFromNib(
  IBNibRef      inNibRef,
  CFStringRef   inName,
  MenuRef *     outMenuRef);


/* ----- MenuBar ------*/

/*
 *  CreateMenuBarFromNib()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
CreateMenuBarFromNib(
  IBNibRef      inNibRef,
  CFStringRef   inName,
  Handle *      outMenuBar);


/*
 *  SetMenuBarFromNib()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in Carbon.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMenuBarFromNib(
  IBNibRef      inNibRef,
  CFStringRef   inName);



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

#endif /* __IBCARBONRUNTIME__ */

