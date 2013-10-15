/*
     File:       ColorSync/CMMComponent.h
 
     Contains:   ColorSync CMM Component API
 
     Version:    ColorSync-118.2.4~3
 
     Copyright:  © 1994-2003 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __CMMCOMPONENT__
#define __CMMCOMPONENT__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __CMAPPLICATION__
#include <ColorSync/CMApplication.h>
#endif




#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

/* Component-based CMM interface version */
enum {
  CMMInterfaceVersion           = 1
};


/* Component-based CMM function selectors */
enum {
                                        /* Required */
  kCMMOpen                      = -1,   /* kComponentOpenSelect,*/
  kCMMClose                     = -2,   /* kComponentCloseSelect,*/
  kCMMGetInfo                   = -4,   /* kComponentVersionSelect*/
  kNCMMInit                     = 6,
  kCMMMatchColors               = 1,
  kCMMCheckColors               = 2,

                                        /* Optional */
  kCMMValidateProfile           = 8,
  kCMMMatchBitmap               = 9,
  kCMMCheckBitmap               = 10,
  kCMMConcatenateProfiles       = 5,
  kCMMConcatInit                = 7,
  kCMMNewLinkProfile            = 16,
  kNCMMConcatInit               = 18,
  kNCMMNewLinkProfile           = 19,
  kCMMGetPS2ColorSpace          = 11,
  kCMMGetPS2ColorRenderingIntent = 12,
  kCMMGetPS2ColorRendering      = 13,
  kCMMGetPS2ColorRenderingVMSize = 17,

                                        /* obsolete with ColorSync 2.5 */
  kCMMFlattenProfile            = 14,
  kCMMUnflattenProfile          = 15,

                                        /* obsolete with ColorSync 2.6 */
  kCMMInit                      = 0,
  kCMMGetNamedColorInfo         = 70,
  kCMMGetNamedColorValue        = 71,
  kCMMGetIndNamedColorValue     = 72,
  kCMMGetNamedColorIndex        = 73,
  kCMMGetNamedColorName         = 74,

                                        /* obsolete with ColorSync 3.0 */
  kCMMMatchPixMap               = 3,
  kCMMCheckPixMap               = 4
};


#if !TARGET_API_MAC_OS8
/*
   The following declarations specify the calling conventions
   for non-Component-based CMM entry-points.
*/

/*
   On TARGET_API_MAC_OSX, cmmInstance is a CFBundleRef
   On TARGET_OS_WIN32, cmmInstance is a HINSTANCE
*/
/*
 *  CMMOpen()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  CMMClose()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  NCMMInit()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  CMMMatchColors()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  CMMCheckColors()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  CMMValidateProfile()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  CMMMatchBitmap()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  CMMCheckBitmap()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  CMMConcatInit()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  NCMMConcatInit()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  CMMNewLinkProfile()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  NCMMNewLinkProfile()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  CMMGetPS2ColorSpace()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  CMMGetPS2ColorRenderingIntent()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  CMMGetPS2ColorRendering()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


/*
 *  CMMGetPS2ColorRenderingVMSize()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


#endif  /* !TARGET_API_MAC_OS8 */

#if TARGET_OS_WIN32
/*
 *  CMMGetCMMInfo()
 *  
 *  Availability:
 *    Mac OS X:         not available
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */


#endif  /* TARGET_OS_WIN32 */



#endif /* __CMMCOMPONENT__ */

