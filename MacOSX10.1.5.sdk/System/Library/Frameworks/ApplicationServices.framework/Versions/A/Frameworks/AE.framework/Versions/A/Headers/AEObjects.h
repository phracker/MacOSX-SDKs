/*
     File:       AE/AEObjects.h
 
     Contains:   Object Support Library Interfaces.
 
     Version:    AppleEvents-116~3
 
     Copyright:  © 1991-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __AEOBJECTS__
#define __AEOBJECTS__

#ifndef __OSUTILS__
#include <CarbonCore/OSUtils.h>
#endif

#ifndef __APPLEEVENTS__
#include <AE/AppleEvents.h>
#endif

#ifndef __MACERRORS__
#include <CarbonCore/MacErrors.h>
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
                                        /**** LOGICAL OPERATOR CONSTANTS  ****/
  kAEAND                        = 'AND ', /*  0x414e4420  */
  kAEOR                         = 'OR  ', /*  0x4f522020  */
  kAENOT                        = 'NOT ', /*  0x4e4f5420  */
                                        /**** ABSOLUTE ORDINAL CONSTANTS  ****/
  kAEFirst                      = 'firs', /*  0x66697273  */
  kAELast                       = 'last', /*  0x6c617374  */
  kAEMiddle                     = 'midd', /*  0x6d696464  */
  kAEAny                        = 'any ', /*  0x616e7920  */
  kAEAll                        = 'all ', /*  0x616c6c20  */
                                        /**** RELATIVE ORDINAL CONSTANTS  ****/
  kAENext                       = 'next', /*  0x6e657874  */
  kAEPrevious                   = 'prev', /*  0x70726576  */
                                        /**** KEYWORD CONSTANT    ****/
  keyAECompOperator             = 'relo', /*  0x72656c6f  */
  keyAELogicalTerms             = 'term', /*  0x7465726d  */
  keyAELogicalOperator          = 'logc', /*  0x6c6f6763  */
  keyAEObject1                  = 'obj1', /*  0x6f626a31  */
  keyAEObject2                  = 'obj2', /*  0x6f626a32  */
                                        /*    ... for Keywords for getting fields out of object specifier records. */
  keyAEDesiredClass             = 'want', /*  0x77616e74  */
  keyAEContainer                = 'from', /*  0x66726f6d  */
  keyAEKeyForm                  = 'form', /*  0x666f726d  */
  keyAEKeyData                  = 'seld' /*  0x73656c64  */
};

enum {
                                        /*    ... for Keywords for getting fields out of Range specifier records. */
  keyAERangeStart               = 'star', /*  0x73746172  */
  keyAERangeStop                = 'stop', /*  0x73746f70  */
                                        /*    ... special handler selectors for OSL Callbacks. */
  keyDisposeTokenProc           = 'xtok', /*  0x78746f6b  */
  keyAECompareProc              = 'cmpr', /*  0x636d7072  */
  keyAECountProc                = 'cont', /*  0x636f6e74  */
  keyAEMarkTokenProc            = 'mkid', /*  0x6d6b6964  */
  keyAEMarkProc                 = 'mark', /*  0x6d61726b  */
  keyAEAdjustMarksProc          = 'adjm', /*  0x61646a6d  */
  keyAEGetErrDescProc           = 'indc' /*  0x696e6463  */
};

/****   VALUE and TYPE CONSTANTS    ****/
enum {
                                        /*    ... possible values for the keyAEKeyForm field of an object specifier. */
  formAbsolutePosition          = 'indx', /*  0x696e6478  */
  formRelativePosition          = 'rele', /*  0x72656c65  */
  formTest                      = 'test', /*  0x74657374  */
  formRange                     = 'rang', /*  0x72616e67  */
  formPropertyID                = 'prop', /*  0x70726f70  */
  formName                      = 'name', /*  0x6e616d65  */
                                        /*    ... relevant types (some of these are often pared with forms above). */
  typeObjectSpecifier           = 'obj ', /*  0x6f626a20  */
  typeObjectBeingExamined       = 'exmn', /*  0x65786d6e  */
  typeCurrentContainer          = 'ccnt', /*  0x63636e74  */
  typeToken                     = 'toke', /*  0x746f6b65  */
  typeRelativeDescriptor        = 'rel ', /*  0x72656c20  */
  typeAbsoluteOrdinal           = 'abso', /*  0x6162736f  */
  typeIndexDescriptor           = 'inde', /*  0x696e6465  */
  typeRangeDescriptor           = 'rang', /*  0x72616e67  */
  typeLogicalDescriptor         = 'logi', /*  0x6c6f6769  */
  typeCompDescriptor            = 'cmpd', /*  0x636d7064  */
  typeOSLTokenList              = 'ostl' /*  0x6F73746C  */
};

/* Possible values for flags parameter to AEResolve.  They're additive */
enum {
  kAEIDoMinimum                 = 0x0000,
  kAEIDoWhose                   = 0x0001,
  kAEIDoMarking                 = 0x0004,
  kAEPassSubDescs               = 0x0008,
  kAEResolveNestedLists         = 0x0010,
  kAEHandleSimpleRanges         = 0x0020,
  kAEUseRelativeIterators       = 0x0040
};

/**** SPECIAL CONSTANTS FOR CUSTOM WHOSE-CLAUSE RESOLUTION */
enum {
  typeWhoseDescriptor           = 'whos', /*  0x77686f73  */
  formWhose                     = 'whos', /*  0x77686f73  */
  typeWhoseRange                = 'wrng', /*  0x77726e67  */
  keyAEWhoseRangeStart          = 'wstr', /*  0x77737472  */
  keyAEWhoseRangeStop           = 'wstp', /*  0x77737470  */
  keyAEIndex                    = 'kidx', /*  0x6b696478  */
  keyAETest                     = 'ktst' /*  0x6b747374  */
};

/*
    used for rewriting tokens in place of 'ccnt' descriptors
    This record is only of interest to those who, when they...
    ...get ranges as key data in their accessor procs, choose
    ...to resolve them manually rather than call AEResolve again.
*/
struct ccntTokenRecord {
  DescType            tokenClass;
  AEDesc              token;
};
typedef struct ccntTokenRecord          ccntTokenRecord;
typedef ccntTokenRecord *               ccntTokenRecPtr;
typedef ccntTokenRecPtr *               ccntTokenRecHandle;
#if OLDROUTINENAMES
typedef AEDesc *                        DescPtr;
typedef DescPtr *                       DescHandle;
#endif  /* OLDROUTINENAMES */

/* typedefs providing type checking for procedure pointers */
typedef CALLBACK_API( OSErr , OSLAccessorProcPtr )(DescType desiredClass, const AEDesc *container, DescType containerClass, DescType form, const AEDesc *selectionData, AEDesc *value, long accessorRefcon);
typedef CALLBACK_API( OSErr , OSLCompareProcPtr )(DescType oper, const AEDesc *obj1, const AEDesc *obj2, Boolean *result);
typedef CALLBACK_API( OSErr , OSLCountProcPtr )(DescType desiredType, DescType containerClass, const AEDesc *container, long *result);
typedef CALLBACK_API( OSErr , OSLDisposeTokenProcPtr )(AEDesc * unneededToken);
typedef CALLBACK_API( OSErr , OSLGetMarkTokenProcPtr )(const AEDesc *dContainerToken, DescType containerClass, AEDesc *result);
typedef CALLBACK_API( OSErr , OSLGetErrDescProcPtr )(AEDesc ** appDescPtr);
typedef CALLBACK_API( OSErr , OSLMarkProcPtr )(const AEDesc *dToken, const AEDesc *markToken, long index);
typedef CALLBACK_API( OSErr , OSLAdjustMarksProcPtr )(long newStart, long newStop, const AEDesc *markToken);
typedef STACK_UPP_TYPE(OSLAccessorProcPtr)                      OSLAccessorUPP;
typedef STACK_UPP_TYPE(OSLCompareProcPtr)                       OSLCompareUPP;
typedef STACK_UPP_TYPE(OSLCountProcPtr)                         OSLCountUPP;
typedef STACK_UPP_TYPE(OSLDisposeTokenProcPtr)                  OSLDisposeTokenUPP;
typedef STACK_UPP_TYPE(OSLGetMarkTokenProcPtr)                  OSLGetMarkTokenUPP;
typedef STACK_UPP_TYPE(OSLGetErrDescProcPtr)                    OSLGetErrDescUPP;
typedef STACK_UPP_TYPE(OSLMarkProcPtr)                          OSLMarkUPP;
typedef STACK_UPP_TYPE(OSLAdjustMarksProcPtr)                   OSLAdjustMarksUPP;
/*
 *  NewOSLAccessorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSLAccessorUPP
NewOSLAccessorUPP(OSLAccessorProcPtr userRoutine);

/*
 *  NewOSLCompareUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSLCompareUPP
NewOSLCompareUPP(OSLCompareProcPtr userRoutine);

/*
 *  NewOSLCountUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSLCountUPP
NewOSLCountUPP(OSLCountProcPtr userRoutine);

/*
 *  NewOSLDisposeTokenUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSLDisposeTokenUPP
NewOSLDisposeTokenUPP(OSLDisposeTokenProcPtr userRoutine);

/*
 *  NewOSLGetMarkTokenUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSLGetMarkTokenUPP
NewOSLGetMarkTokenUPP(OSLGetMarkTokenProcPtr userRoutine);

/*
 *  NewOSLGetErrDescUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSLGetErrDescUPP
NewOSLGetErrDescUPP(OSLGetErrDescProcPtr userRoutine);

/*
 *  NewOSLMarkUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSLMarkUPP
NewOSLMarkUPP(OSLMarkProcPtr userRoutine);

/*
 *  NewOSLAdjustMarksUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSLAdjustMarksUPP
NewOSLAdjustMarksUPP(OSLAdjustMarksProcPtr userRoutine);

/*
 *  DisposeOSLAccessorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeOSLAccessorUPP(OSLAccessorUPP userUPP);

/*
 *  DisposeOSLCompareUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeOSLCompareUPP(OSLCompareUPP userUPP);

/*
 *  DisposeOSLCountUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeOSLCountUPP(OSLCountUPP userUPP);

/*
 *  DisposeOSLDisposeTokenUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeOSLDisposeTokenUPP(OSLDisposeTokenUPP userUPP);

/*
 *  DisposeOSLGetMarkTokenUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeOSLGetMarkTokenUPP(OSLGetMarkTokenUPP userUPP);

/*
 *  DisposeOSLGetErrDescUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeOSLGetErrDescUPP(OSLGetErrDescUPP userUPP);

/*
 *  DisposeOSLMarkUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeOSLMarkUPP(OSLMarkUPP userUPP);

/*
 *  DisposeOSLAdjustMarksUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeOSLAdjustMarksUPP(OSLAdjustMarksUPP userUPP);

/*
 *  InvokeOSLAccessorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeOSLAccessorUPP(
  DescType        desiredClass,
  const AEDesc *  container,
  DescType        containerClass,
  DescType        form,
  const AEDesc *  selectionData,
  AEDesc *        value,
  long            accessorRefcon,
  OSLAccessorUPP  userUPP);

/*
 *  InvokeOSLCompareUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeOSLCompareUPP(
  DescType        oper,
  const AEDesc *  obj1,
  const AEDesc *  obj2,
  Boolean *       result,
  OSLCompareUPP   userUPP);

/*
 *  InvokeOSLCountUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeOSLCountUPP(
  DescType        desiredType,
  DescType        containerClass,
  const AEDesc *  container,
  long *          result,
  OSLCountUPP     userUPP);

/*
 *  InvokeOSLDisposeTokenUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeOSLDisposeTokenUPP(
  AEDesc *            unneededToken,
  OSLDisposeTokenUPP  userUPP);

/*
 *  InvokeOSLGetMarkTokenUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeOSLGetMarkTokenUPP(
  const AEDesc *      dContainerToken,
  DescType            containerClass,
  AEDesc *            result,
  OSLGetMarkTokenUPP  userUPP);

/*
 *  InvokeOSLGetErrDescUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeOSLGetErrDescUPP(
  AEDesc **         appDescPtr,
  OSLGetErrDescUPP  userUPP);

/*
 *  InvokeOSLMarkUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeOSLMarkUPP(
  const AEDesc *  dToken,
  const AEDesc *  markToken,
  long            index,
  OSLMarkUPP      userUPP);

/*
 *  InvokeOSLAdjustMarksUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeOSLAdjustMarksUPP(
  long               newStart,
  long               newStop,
  const AEDesc *     markToken,
  OSLAdjustMarksUPP  userUPP);




/*
 *  AEObjectInit()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ObjectSupportLib 1.0 and later
 */
extern OSErr 
AEObjectInit(void);


/* Not done by inline, but by direct linking into code.  It sets up the pack
  such that further calls can be via inline */
/*
 *  AESetObjectCallbacks()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ObjectSupportLib 1.0 and later
 */
extern OSErr 
AESetObjectCallbacks(
  OSLCompareUPP        myCompareProc,
  OSLCountUPP          myCountProc,
  OSLDisposeTokenUPP   myDisposeTokenProc,
  OSLGetMarkTokenUPP   myGetMarkTokenProc,
  OSLMarkUPP           myMarkProc,
  OSLAdjustMarksUPP    myAdjustMarksProc,
  OSLGetErrDescUPP     myGetErrDescProcPtr);


/*
 *  AEResolve()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ObjectSupportLib 1.0 and later
 */
extern OSErr 
AEResolve(
  const AEDesc *  objectSpecifier,
  short           callbackFlags,
  AEDesc *        theToken);


/*
 *  AEInstallObjectAccessor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ObjectSupportLib 1.0 and later
 */
extern OSErr 
AEInstallObjectAccessor(
  DescType         desiredClass,
  DescType         containerType,
  OSLAccessorUPP   theAccessor,
  long             accessorRefcon,
  Boolean          isSysHandler);


/*
 *  AERemoveObjectAccessor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ObjectSupportLib 1.0 and later
 */
extern OSErr 
AERemoveObjectAccessor(
  DescType         desiredClass,
  DescType         containerType,
  OSLAccessorUPP   theAccessor,
  Boolean          isSysHandler);


/*
 *  AEGetObjectAccessor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ObjectSupportLib 1.0 and later
 */
extern OSErr 
AEGetObjectAccessor(
  DescType          desiredClass,
  DescType          containerType,
  OSLAccessorUPP *  accessor,
  long *            accessorRefcon,
  Boolean           isSysHandler);


/*
 *  AEDisposeToken()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ObjectSupportLib 1.0 and later
 */
extern OSErr 
AEDisposeToken(AEDesc * theToken);


/*
 *  AECallObjectAccessor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in ObjectSupportLib 1.0 and later
 */
extern OSErr 
AECallObjectAccessor(
  DescType        desiredClass,
  const AEDesc *  containerToken,
  DescType        containerClass,
  DescType        keyForm,
  const AEDesc *  keyData,
  AEDesc *        token);




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

#endif /* __AEOBJECTS__ */

