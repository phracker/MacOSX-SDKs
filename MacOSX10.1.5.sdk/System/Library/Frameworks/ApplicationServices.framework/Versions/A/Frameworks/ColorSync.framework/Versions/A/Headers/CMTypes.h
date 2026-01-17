/*
     File:       ColorSync/CMTypes.h
 
     Contains:   ColorSync types
 
     Version:    ColorSync-81~8
 
     Copyright:  © 2000-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/


#ifndef __CMTYPES__
#define __CMTYPES__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __MIXEDMODE__
#include <CarbonCore/MixedMode.h>
#endif





/* Standard type for ColorSync and other system error codes */


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
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CMFlattenUPP
NewCMFlattenUPP(CMFlattenProcPtr userRoutine);

/*
 *  NewCMBitmapCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CMBitmapCallBackUPP
NewCMBitmapCallBackUPP(CMBitmapCallBackProcPtr userRoutine);

/*
 *  NewCMConcatCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CMConcatCallBackUPP
NewCMConcatCallBackUPP(CMConcatCallBackProcPtr userRoutine);

/*
 *  NewCMProfileFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CMProfileFilterUPP
NewCMProfileFilterUPP(CMProfileFilterProcPtr userRoutine);

/*
 *  NewCMProfileAccessUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern CMProfileAccessUPP
NewCMProfileAccessUPP(CMProfileAccessProcPtr userRoutine);

/*
 *  DisposeCMFlattenUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCMFlattenUPP(CMFlattenUPP userUPP);

/*
 *  DisposeCMBitmapCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCMBitmapCallBackUPP(CMBitmapCallBackUPP userUPP);

/*
 *  DisposeCMConcatCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCMConcatCallBackUPP(CMConcatCallBackUPP userUPP);

/*
 *  DisposeCMProfileFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCMProfileFilterUPP(CMProfileFilterUPP userUPP);

/*
 *  DisposeCMProfileAccessUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeCMProfileAccessUPP(CMProfileAccessUPP userUPP);

/*
 *  InvokeCMFlattenUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeCMFlattenUPP(
  long          command,
  long *        size,
  void *        data,
  void *        refCon,
  CMFlattenUPP  userUPP);

/*
 *  InvokeCMBitmapCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeCMBitmapCallBackUPP(
  long                 progress,
  void *               refCon,
  CMBitmapCallBackUPP  userUPP);

/*
 *  InvokeCMConcatCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeCMConcatCallBackUPP(
  long                 progress,
  void *               refCon,
  CMConcatCallBackUPP  userUPP);

/*
 *  InvokeCMProfileFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeCMProfileFilterUPP(
  CMProfileRef        prof,
  void *              refCon,
  CMProfileFilterUPP  userUPP);

/*
 *  InvokeCMProfileAccessUPP()
 *  
 *  Availability:
 *    Mac OS X:         in 3.0 and later in ApplicationServices.framework
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
  CMProfileAccessUPP  userUPP);


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

#endif /* __CMTYPES__ */

