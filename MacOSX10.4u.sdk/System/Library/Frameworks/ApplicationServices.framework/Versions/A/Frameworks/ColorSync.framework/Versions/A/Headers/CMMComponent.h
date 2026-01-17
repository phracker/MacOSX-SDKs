/*
     File:       ColorSync/CMMComponent.h
 
     Contains:   ColorSync CMM Component API
 
     Version:    ColorSync-174.3.3~45
 
     Copyright:  © 1994-2006 by Apple Computer, Inc., all rights reserved.
 
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

/*
   The following declarations specify the calling conventions for CMM entry-points on Mac OS X.
   On TARGET_API_MAC_OSX, cmmInstance is undefined
*/
/*
 *  CMMOpen()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
CMMOpen(
  UInt32 *  cmmStorage,
  void *    cmmInstance);


/*
 *  CMMClose()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
CMMClose(UInt32 * cmmStorage);


/*
 *  NCMMInit()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
NCMMInit(
  UInt32 *       cmmStorage,
  CMProfileRef   srcProfile,
  CMProfileRef   dstProfile);


/*
 *  CMMMatchColors()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
CMMMatchColors(
  UInt32 *   cmmStorage,
  CMColor *  colors,
  UInt32     count);


/*
 *  CMMCheckColors()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
CMMCheckColors(
  UInt32 *   cmmStorage,
  CMColor *  colors,
  UInt32     count,
  UInt8 *    result);


/*
 *  CMMValidateProfile()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
CMMValidateProfile(
  UInt32 *       cmmStorage,
  CMProfileRef   prof,
  Boolean *      valid);


/*
 *  CMMMatchBitmap()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
CMMMatchBitmap(
  UInt32 *              cmmStorage,
  CMBitmap *            bitmap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon,
  CMBitmap *            matchedBitmap);


/*
 *  CMMCheckBitmap()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
CMMCheckBitmap(
  UInt32 *              cmmStorage,
  const CMBitmap *      bitmap,
  CMBitmapCallBackUPP   progressProc,
  void *                refCon,
  CMBitmap *            resultBitmap);


/*
 *  CMMMatchFloatBitmap()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
CMMMatchFloatBitmap(
  UInt32 *               cmmStorage,
  const CMFloatBitmap *  bitmap,
  CMFloatBitmap *        resultBitmap);


/*
 *  CMMConcatInit()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
CMMConcatInit(
  UInt32 *              cmmStorage,
  CMConcatProfileSet *  profileSet);


/*
 *  NCMMConcatInit()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
NCMMConcatInit(
  UInt32 *               cmmStorage,
  NCMConcatProfileSet *  profileSet,
  CMConcatCallBackUPP    proc,
  void *                 refCon);


/*
 *  CMMSetProperties()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
CMMSetProperties(
  UInt32 *      cmmStorage,
  CMWorldRef    cw,
  CFStringRef   requestedKey);


/*
 *  CMMNewLinkProfile()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
CMMNewLinkProfile(
  UInt32 *                   cmmStorage,
  CMProfileRef *             prof,
  const CMProfileLocation *  targetLocation,
  CMConcatProfileSet *       profileSet);


/*
 *  NCMMNewLinkProfile()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
NCMMNewLinkProfile(
  UInt32 *               cmmStorage,
  CMProfileRef           prof,
  NCMConcatProfileSet *  profileSet,
  CMConcatCallBackUPP    proc,
  void *                 refCon);


/*
 *  CMMGetPS2ColorSpace()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
CMMGetPS2ColorSpace(
  UInt32 *       cmmStorage,
  CMProfileRef   srcProf,
  UInt32         flags,
  CMFlattenUPP   proc,
  void *         refCon);


/*
 *  CMMGetPS2ColorRenderingIntent()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
CMMGetPS2ColorRenderingIntent(
  UInt32 *       cmmStorage,
  CMProfileRef   srcProf,
  UInt32         flags,
  CMFlattenUPP   proc,
  void *         refCon);


/*
 *  CMMGetPS2ColorRendering()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
CMMGetPS2ColorRendering(
  UInt32 *       cmmStorage,
  CMProfileRef   srcProf,
  CMProfileRef   dstProf,
  UInt32         flags,
  CMFlattenUPP   proc,
  void *         refCon);


/*
 *  CMMGetPS2ColorRenderingVMSize()
 *  
 *  Availability:
 *    Implemented by client
 */
extern CMError 
CMMGetPS2ColorRenderingVMSize(
  UInt32 *       cmmStorage,
  CMProfileRef   srcProf,
  CMProfileRef   dstProf,
  UInt32 *       vmSize);



#ifdef __cplusplus
}
#endif

#endif /* __CMMCOMPONENT__ */

