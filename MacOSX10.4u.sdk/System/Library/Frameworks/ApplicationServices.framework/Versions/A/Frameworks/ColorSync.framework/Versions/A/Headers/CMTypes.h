/*
     File:       ColorSync/CMTypes.h
 
     Contains:   ColorSync types
 
     Version:    ColorSync-174.3.3~45
 
     Copyright:  © 2000-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/


#ifndef __CMTYPES__
#define __CMTYPES__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


/* Standard type for ColorSync and other system error codes */

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef long                            CMError;
/* Abstract data type for memory-based Profile */
typedef struct OpaqueCMProfileRef*      CMProfileRef;
/* Abstract data type for Profile search result */
typedef struct OpaqueCMProfileSearchRef*  CMProfileSearchRef;
/* Abstract data type for BeginMatching(É) reference */
typedef struct OpaqueCMMatchRef*        CMMatchRef;
/* Abstract data type for ColorWorld reference */
typedef struct OpaqueCMWorldRef*        CMWorldRef;
/* Data type for ColorSync DisplayID reference */
/* On 8 & 9 this is a AVIDType */
/* On X this is a CGSDisplayID */
typedef UInt32                          CMDisplayIDType;
typedef UInt32                          CMChromaticAdaptation;
enum {
  cmUseDefaultChromaticAdaptation = 0,
  cmLinearChromaticAdaptation   = 1,
  cmVonKriesChromaticAdaptation = 2,
  cmBradfordChromaticAdaptation = 3
};



/* Caller-supplied flatten function */
typedef CALLBACK_API( OSErr , CMFlattenProcPtr )(long command, long *size, void *data, void *refCon);
/* Caller-supplied progress function for Bitmap & PixMap matching routines */
typedef CALLBACK_API( Boolean , CMBitmapCallBackProcPtr )(long progress, void *refCon);
/* Caller-supplied progress function for NCMMConcatInit & NCMMNewLinkProfile routines */
typedef CALLBACK_API( Boolean , CMConcatCallBackProcPtr )(long progress, void *refCon);
/* Caller-supplied filter function for Profile search */
typedef CALLBACK_API( Boolean , CMProfileFilterProcPtr )(CMProfileRef prof, void *refCon);
/* Caller-supplied function for profile access */
typedef CALLBACK_API( OSErr , CMProfileAccessProcPtr )(long command, long offset, long *size, void *data, void *refCon);
typedef STACK_UPP_TYPE(CMFlattenProcPtr)                        CMFlattenUPP;
typedef STACK_UPP_TYPE(CMBitmapCallBackProcPtr)                 CMBitmapCallBackUPP;
typedef STACK_UPP_TYPE(CMConcatCallBackProcPtr)                 CMConcatCallBackUPP;
typedef STACK_UPP_TYPE(CMProfileFilterProcPtr)                  CMProfileFilterUPP;
typedef STACK_UPP_TYPE(CMProfileAccessProcPtr)                  CMProfileAccessUPP;
/*
 *  NewCMFlattenUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CMFlattenUPP
NewCMFlattenUPP(CMFlattenProcPtr userRoutine)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewCMBitmapCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CMBitmapCallBackUPP
NewCMBitmapCallBackUPP(CMBitmapCallBackProcPtr userRoutine)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewCMConcatCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CMConcatCallBackUPP
NewCMConcatCallBackUPP(CMConcatCallBackProcPtr userRoutine)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewCMProfileFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CMProfileFilterUPP
NewCMProfileFilterUPP(CMProfileFilterProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewCMProfileAccessUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CMProfileAccessUPP
NewCMProfileAccessUPP(CMProfileAccessProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeCMFlattenUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCMFlattenUPP(CMFlattenUPP userUPP)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeCMBitmapCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCMBitmapCallBackUPP(CMBitmapCallBackUPP userUPP)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeCMConcatCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCMConcatCallBackUPP(CMConcatCallBackUPP userUPP)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeCMProfileFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCMProfileFilterUPP(CMProfileFilterUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeCMProfileAccessUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCMProfileAccessUPP(CMProfileAccessUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeCMFlattenUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeCMFlattenUPP(
  long          command,
  long *        size,
  void *        data,
  void *        refCon,
  CMFlattenUPP  userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeCMBitmapCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeCMBitmapCallBackUPP(
  long                 progress,
  void *               refCon,
  CMBitmapCallBackUPP  userUPP)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeCMConcatCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeCMConcatCallBackUPP(
  long                 progress,
  void *               refCon,
  CMConcatCallBackUPP  userUPP)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeCMProfileFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeCMProfileFilterUPP(
  CMProfileRef        prof,
  void *              refCon,
  CMProfileFilterUPP  userUPP)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeCMProfileAccessUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeCMProfileAccessUPP(
  long                command,
  long                offset,
  long *              size,
  void *              data,
  void *              refCon,
  CMProfileAccessUPP  userUPP)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#ifdef __cplusplus
}
#endif

#endif /* __CMTYPES__ */

