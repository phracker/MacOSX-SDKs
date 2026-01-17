/*
     File:       ColorSync/CMMComponent.h
 
     Contains:   ColorSync CMM Component API
 
     Copyright:  1994-2005 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult http://developer.apple.com/bugreporter/
 
*/
#ifndef __CMMCOMPONENT__
#define __CMMCOMPONENT__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __CMAPPLICATION__
#include <ColorSync/CMApplication.h>
#endif

#ifndef __CMFLOATBITMAP__
#include <ColorSync/CMFloatBitmap.h>
#endif




#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

CSEXTERN void
CWColorWorldSetProperty(
  CMWorldRef    cw,
  CFStringRef   key,
  CFTypeRef     value) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


CSEXTERN const void* 
CWColorWorldGetProperty(
  CMWorldRef    cw,
  CFStringRef   key) AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*
   The following declarations specify the calling conventions for CMM entry-points on Mac OS X.
*/

/* Required */
extern CMError 
CMM_ConcatColorWorld(
  CMWorldRef             cw,
  NCMConcatProfileSet *  profileSet,
  CMConcatCallBackUPP    proc,
  void *                 refCon);

extern CMError 
CMM_MatchColors(
  CMWorldRef  cw,
  CMColor *   colors,
  UInt32      count);

extern CMError 
CMM_CheckColors(
  CMWorldRef  cw,
  CMColor *   colors,
  UInt32      count,
  UInt8 *     result);

/* Optional */

extern CMError 
CMM_ValidateProfile(
  CMProfileRef   prof,
  Boolean *      valid);

extern CMError 
CMM_MatchBitmap(
  CMWorldRef            cw,
  CMBitmap *            bitmap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon,
  CMBitmap *            matchedBitmap);

extern CMError 
CMM_CheckBitmap(
  CMWorldRef            cw,
  const CMBitmap *      bitmap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon,
  CMBitmap *            resultBitmap);

extern CMError 
CMM_MatchFloatBitmap(
  CMWorldRef             cw,
  const CMFloatBitmap *  bitmap,
  CMFloatBitmap *        resultBitmap);

extern CMError 
CMM_CreateLinkProfile(
  CMProfileRef           prof,
  NCMConcatProfileSet *  profileSet,
  CMConcatCallBackUPP    proc,
  void *                 refCon);

extern CFTypeRef 
CMM_GetProperty(
  CMWorldRef    cw,
  CFStringRef   requestedKey);



#ifdef __cplusplus
}
#endif

#endif /* __CMMCOMPONENT__ */

