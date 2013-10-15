/*
     File:       ColorSync/CMTypes.h
 
     Contains:   ColorSync types
 
     Copyright:  2000-2005 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult http://developer.apple.com/bugreporter/
 
*/


#ifndef __CMTYPES__
#define __CMTYPES__

#include <stddef.h>
#include <sys/types.h>

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#include <ColorSync/CMBase.h>

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif


/* Standard type for ColorSync and other system error codes */
typedef OSStatus                        CMError;

/* Abstract data type for memory-based Profile */
typedef struct OpaqueCMProfileRef*      CMProfileRef;

#if !__LP64__
/* Abstract data type for Profile search result */
typedef struct OpaqueCMProfileSearchRef*  CMProfileSearchRef;

/* Abstract data type for BeginMatching(É) reference */
typedef struct OpaqueCMMatchRef*        CMMatchRef;
#endif // !__LP64__

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
typedef CALLBACK_API( OSErr , CMFlattenProcPtr )(SInt32 command, long *size, void *data, void *refCon);

typedef STACK_UPP_TYPE(CMFlattenProcPtr) CMFlattenUPP;

#if TARGET_RT_MAC_CFM
  CSEXTERN CMFlattenUPP
  NewCMFlattenUPP(CMFlattenProcPtr userRoutine)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

  CSEXTERN OSErr
  InvokeCMFlattenUPP(
    SInt32        command,
    long *        size,
    void *        data,
    void *        refCon,
    CMFlattenUPP  userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

  CSEXTERN void
  DisposeCMFlattenUPP(CMFlattenUPP userUPP)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#else
  CF_INLINE CMFlattenUPP NewCMFlattenUPP(CMFlattenProcPtr userRoutine)
    { return (CMFlattenUPP)userRoutine; }

  CF_INLINE OSErr InvokeCMFlattenUPP(SInt32 command, long * size, void * data, void * refCon, CMFlattenUPP userUPP)
    { return (*((CMFlattenProcPtr)userUPP))(command, size, data, refCon); }

#ifdef __cplusplus
  CF_INLINE void DisposeCMFlattenUPP(CMFlattenUPP)
  {
  }
#else
  CF_INLINE void DisposeCMFlattenUPP(CMFlattenUPP userUPP)
  {
  #pragma unused (userUPP)
  }
#endif

#endif // TARGET_RT_MAC_CFM



/* Caller-supplied progress function for Bitmap & PixMap matching routines */
typedef CALLBACK_API( Boolean , CMBitmapCallBackProcPtr )(SInt32 progress, void *refCon);

typedef STACK_UPP_TYPE(CMBitmapCallBackProcPtr) CMBitmapCallBackUPP;

#if TARGET_RT_MAC_CFM
  CSEXTERN CMBitmapCallBackUPP
  NewCMBitmapCallBackUPP(CMBitmapCallBackProcPtr userRoutine)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

  CSEXTERN Boolean
  InvokeCMBitmapCallBackUPP(
    SInt32               progress,
    void *               refCon,
    CMBitmapCallBackUPP  userUPP)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

  CSEXTERN void
  DisposeCMBitmapCallBackUPP(CMBitmapCallBackUPP userUPP)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#else
  CF_INLINE CMBitmapCallBackUPP NewCMBitmapCallBackUPP(CMBitmapCallBackProcPtr userRoutine)
    { return (CMBitmapCallBackUPP)userRoutine; }

  CF_INLINE Boolean InvokeCMBitmapCallBackUPP(SInt32 progress, void * refCon, CMBitmapCallBackUPP userUPP)
    { return (*((CMBitmapCallBackProcPtr)userUPP))(progress, refCon); }

#ifdef __cplusplus
  CF_INLINE void DisposeCMBitmapCallBackUPP(CMBitmapCallBackUPP) 
  {
  }
#else
  CF_INLINE void DisposeCMBitmapCallBackUPP(CMBitmapCallBackUPP userUPP) 
  {
  #pragma unused (userUPP)
  }
#endif
#endif // TARGET_RT_MAC_CFM


/* Caller-supplied progress function for NCMMConcatInit & NCMMNewLinkProfile routines */
typedef CALLBACK_API( Boolean , CMConcatCallBackProcPtr )(SInt32 progress, void *refCon);

typedef STACK_UPP_TYPE(CMConcatCallBackProcPtr) CMConcatCallBackUPP;

#if TARGET_RT_MAC_CFM
  CSEXTERN CMConcatCallBackUPP
  NewCMConcatCallBackUPP(CMConcatCallBackProcPtr userRoutine)   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

  CSEXTERN Boolean
  InvokeCMConcatCallBackUPP(
    SInt32               progress,
    void *               refCon,
    CMConcatCallBackUPP  userUPP)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

  CSEXTERN void
  DisposeCMConcatCallBackUPP(CMConcatCallBackUPP userUPP)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#else
  CF_INLINE CMConcatCallBackUPP NewCMConcatCallBackUPP(CMConcatCallBackProcPtr userRoutine)
    { return (CMConcatCallBackUPP)userRoutine; }

  CF_INLINE
  Boolean InvokeCMConcatCallBackUPP(SInt32 progress, void * refCon, CMConcatCallBackUPP userUPP)
    { return (*((CMConcatCallBackProcPtr)userUPP))(progress, refCon); }

#ifdef __cplusplus
  CF_INLINE void DisposeCMConcatCallBackUPP(CMConcatCallBackUPP)
  {
  }
#else
  CF_INLINE void DisposeCMConcatCallBackUPP(CMConcatCallBackUPP userUPP)
  {
  #pragma unused (userUPP)
  }
#endif
#endif // TARGET_RT_MAC_CFM


#if !__LP64__

/* Caller-supplied filter function for Profile search*/
typedef CALLBACK_API( Boolean , CMProfileFilterProcPtr )(CMProfileRef prof, void *refCon);

typedef STACK_UPP_TYPE(CMProfileFilterProcPtr) CMProfileFilterUPP;

#if TARGET_RT_MAC_CFM
  CSEXTERN CMProfileFilterUPP
  NewCMProfileFilterUPP(CMProfileFilterProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

  CSEXTERN Boolean
  InvokeCMProfileFilterUPP(
    CMProfileRef        prof,
    void *              refCon,
    CMProfileFilterUPP  userUPP)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

  CSEXTERN void
  DisposeCMProfileFilterUPP(CMProfileFilterUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#else
  CF_INLINE CMProfileFilterUPP NewCMProfileFilterUPP(CMProfileFilterProcPtr userRoutine)
    { return (CMProfileFilterUPP)userRoutine; }

  CF_INLINE Boolean InvokeCMProfileFilterUPP(CMProfileRef prof, void * refCon, CMProfileFilterUPP userUPP)
    { return (*((CMProfileFilterProcPtr)userUPP))(prof, refCon); }

#ifdef __cplusplus
  CF_INLINE void DisposeCMProfileFilterUPP(CMProfileFilterUPP)
  {
  }
#else
  CF_INLINE void DisposeCMProfileFilterUPP(CMProfileFilterUPP userUPP)
  {
  #pragma unused (userUPP)
  }
#endif
#endif // TARGET_RT_MAC_CFM


/* Caller-supplied function for profile access*/
typedef CALLBACK_API( OSErr , CMProfileAccessProcPtr )(SInt32 command, SInt32 offset, SInt32 *size, void *data, void *refCon);

typedef STACK_UPP_TYPE(CMProfileAccessProcPtr) CMProfileAccessUPP;

#if TARGET_RT_MAC_CFM
  CSEXTERN CMProfileAccessUPP
  NewCMProfileAccessUPP(CMProfileAccessProcPtr userRoutine)     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

  CSEXTERN OSErr
  InvokeCMProfileAccessUPP(
    SInt32              command,
    SInt32              offset,
    SInt32 *            size,
    void *              data,
    void *              refCon,
    CMProfileAccessUPP  userUPP)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;

  CSEXTERN void
  DisposeCMProfileAccessUPP(CMProfileAccessUPP userUPP)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;
#else
  CF_INLINE CMProfileAccessUPP NewCMProfileAccessUPP(CMProfileAccessProcPtr userRoutine)
    { return (CMProfileAccessUPP)userRoutine; }

  CF_INLINE OSErr InvokeCMProfileAccessUPP(SInt32 command, SInt32 offset, SInt32 * size, void * data, void * refCon, CMProfileAccessUPP userUPP)
    { return (*((CMProfileAccessProcPtr)userUPP))(command, offset, size, data, refCon); }

#ifdef __cplusplus
  CF_INLINE void DisposeCMProfileAccessUPP(CMProfileAccessUPP)
  {
  }
#else
  CF_INLINE void DisposeCMProfileAccessUPP(CMProfileAccessUPP userUPP)
  {
  #pragma unused (userUPP)
  }
#endif
#endif // TARGET_RT_MAC_CFM


#endif // !__LP64__



#ifdef __cplusplus
}
#endif

#endif /* __CMTYPES__ */

