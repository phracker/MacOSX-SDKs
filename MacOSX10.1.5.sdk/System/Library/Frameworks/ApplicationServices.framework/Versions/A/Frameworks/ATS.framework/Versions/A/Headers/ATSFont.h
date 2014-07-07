/*
     File:       ATS/ATSFont.h
 
     Contains:   Public interface to the font access and data management functions of ATS.
 
     Version:    ATS-77.1~62
 
     Copyright:  © 2000-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __ATSFONT__
#define __ATSFONT__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __ATSTYPES__
#include <ATS/ATSTypes.h>
#endif

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif

#ifndef __TEXTCOMMON__
#include <CarbonCore/TextCommon.h>
#endif

#ifndef __SFNTTYPES__
#include <ATS/SFNTTypes.h>
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

#if PRAGMA_ENUM_ALWAYSINT
    #if defined(__fourbyteints__) && !__fourbyteints__ 
        #define __ATSFONT__RESTORE_TWOBYTEINTS
        #pragma fourbyteints on
    #endif
    #pragma enumsalwaysint on
#elif PRAGMA_ENUM_OPTIONS
    #pragma option enum=int
#elif PRAGMA_ENUM_PACK
    #if __option(pack_enums)
        #define __ATSFONT__RESTORE_PACKED_ENUMS
        #pragma options(!pack_enums)
    #endif
#endif

enum {
  kATSOptionFlagsDefault        = kNilOptions,
  kATSOptionFlagsComposeFontPostScriptName = 1 << 0, /* ATSFontGetPostScriptName */
  kATSOptionFlagsUseDataForkAsResourceFork = 1 << 8, /* ATSFontActivateFromFileSpecification */
  kATSOptionFlagsUseResourceFork = 2 << 8,
  kATSOptionFlagsUseDataFork    = 3 << 8
};

enum {
  kATSIterationCompleted        = -980L,
  kATSInvalidFontFamilyAccess   = -981L,
  kATSInvalidFontAccess         = -982L,
  kATSIterationScopeModified    = -983L,
  kATSInvalidFontTableAccess    = -984L,
  kATSInvalidFontContainerAccess = -985L
};

typedef UInt32                          ATSFontContext;
enum {
  kATSFontContextUnspecified    = 0,
  kATSFontContextGlobal         = 1,
  kATSFontContextLocal          = 2
};

enum {
  kATSOptionFlagsIterationScopeMask = 0x00000007 << 12, /* Mask option bits 12-14 for iteration scopes */
  kATSOptionFlagsDefaultScope   = 0x00000000 << 12,
  kATSOptionFlagsUnRestrictedScope = 0x00000001 << 12,
  kATSOptionFlagsRestrictedScope = 0x00000002 << 12
};

/* Iteration Option Flags */
enum {
  kATSOptionFlagsIterateByPrecedenceMask = 0x00000001 << 5
};

typedef UInt32                          ATSFontFormat;
enum {
  kATSFontFormatUnspecified     = 0
};

typedef CALLBACK_API_C( OSStatus , ATSFontFamilyApplierFunction )(ATSFontFamilyRef iFamily, void *iRefCon);
typedef CALLBACK_API_C( OSStatus , ATSFontApplierFunction )(ATSFontRef iFont, void *iRefCon);
typedef struct ATSFontFamilyIterator_*  ATSFontFamilyIterator;
typedef struct ATSFontIterator_*        ATSFontIterator;
enum {
  kATSFontFilterCurrentVersion  = 0
};


enum ATSFontFilterSelector {
  kATSFontFilterSelectorUnspecified = 0,
  kATSFontFilterSelectorGeneration = 3,
  kATSFontFilterSelectorFontFamily = 7,
  kATSFontFilterSelectorFontFamilyApplierFunction = 8,
  kATSFontFilterSelectorFontApplierFunction = 9
};
typedef enum ATSFontFilterSelector ATSFontFilterSelector;

struct ATSFontFilter {
  UInt32              version;
  ATSFontFilterSelector  filterSelector;
  union {
    ATSGeneration       generationFilter;
    ATSFontFamilyRef    fontFamilyFilter;
    ATSFontFamilyApplierFunction  fontFamilyApplierFunctionFilter;
    ATSFontApplierFunction  fontApplierFunctionFilter;
  }                       filter;
};
typedef struct ATSFontFilter            ATSFontFilter;
/* ----------------------------------------------------------------------------------------- */
/* Font container                                                                            */
/* ----------------------------------------------------------------------------------------- */
/*
 *  ATSGetGeneration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSGeneration 
ATSGetGeneration(void);


/*
 *  ATSFontActivateFromFileSpecification()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontActivateFromFileSpecification(
  const FSSpec *         iFile,
  ATSFontContext         iContext,
  ATSFontFormat          iFormat,
  void *                 iReserved,
  ATSOptionFlags         iOptions,
  ATSFontContainerRef *  oContainer);


/*
 *  ATSFontActivateFromMemory()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontActivateFromMemory(
  LogicalAddress         iData,
  ByteCount              iLength,
  ATSFontContext         iContext,
  ATSFontFormat          iFormat,
  void *                 iReserved,
  ATSOptionFlags         iOptions,
  ATSFontContainerRef *  oContainer);


/*
 *  ATSFontDeactivate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontDeactivate(
  ATSFontContainerRef   iContainer,
  void *                iRefCon,
  ATSOptionFlags        iOptions);


/* ----------------------------------------------------------------------------------------- */
/* Font family                                                                               */
/* ----------------------------------------------------------------------------------------- */
/*
 *  ATSFontFamilyApplyFunction()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFamilyApplyFunction(
  ATSFontFamilyApplierFunction   iFunction,
  void *                         iRefCon);


/*
 *  ATSFontFamilyIteratorCreate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFamilyIteratorCreate(
  ATSFontContext           iContext,
  const ATSFontFilter *    iFilter,          /* can be NULL */
  void *                   iRefCon,
  ATSOptionFlags           iOptions,
  ATSFontFamilyIterator *  ioIterator);


/*
 *  ATSFontFamilyIteratorRelease()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFamilyIteratorRelease(ATSFontFamilyIterator * ioIterator);


/*
 *  ATSFontFamilyIteratorReset()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFamilyIteratorReset(
  ATSFontContext           iContext,
  const ATSFontFilter *    iFilter,          /* can be NULL */
  void *                   iRefCon,
  ATSOptionFlags           iOptions,
  ATSFontFamilyIterator *  ioIterator);


/*
 *  ATSFontFamilyIteratorNext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFamilyIteratorNext(
  ATSFontFamilyIterator   iIterator,
  ATSFontFamilyRef *      oFamily);


/*
 *  ATSFontFamilyFindFromName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSFontFamilyRef 
ATSFontFamilyFindFromName(
  CFStringRef      iName,
  ATSOptionFlags   iOptions);


/*
 *  ATSFontFamilyGetGeneration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSGeneration 
ATSFontFamilyGetGeneration(ATSFontFamilyRef iFamily);


/*
 *  ATSFontFamilyGetName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFamilyGetName(
  ATSFontFamilyRef   iFamily,
  ATSOptionFlags     iOptions,
  CFStringRef *      oName);


/*
 *  ATSFontFamilyGetEncoding()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern TextEncoding 
ATSFontFamilyGetEncoding(ATSFontFamilyRef iFamily);


/* ----------------------------------------------------------------------------------------- */
/* Font                                                                                      */
/* ----------------------------------------------------------------------------------------- */
/*
 *  ATSFontApplyFunction()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontApplyFunction(
  ATSFontApplierFunction   iFunction,
  void *                   iRefCon);


/*
 *  ATSFontIteratorCreate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontIteratorCreate(
  ATSFontContext         iContext,
  const ATSFontFilter *  iFilter,          /* can be NULL */
  void *                 iRefCon,
  ATSOptionFlags         iOptions,
  ATSFontIterator *      ioIterator);


/*
 *  ATSFontIteratorRelease()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontIteratorRelease(ATSFontIterator * ioIterator);


/*
 *  ATSFontIteratorReset()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontIteratorReset(
  ATSFontContext         iContext,
  const ATSFontFilter *  iFilter,          /* can be NULL */
  void *                 iRefCon,
  ATSOptionFlags         iOptions,
  ATSFontIterator *      ioIterator);


/*
 *  ATSFontIteratorNext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontIteratorNext(
  ATSFontIterator   iIterator,
  ATSFontRef *      oFont);


/*
 *  ATSFontFindFromName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSFontRef 
ATSFontFindFromName(
  CFStringRef      iName,
  ATSOptionFlags   iOptions);


/*
 *  ATSFontFindFromPostScriptName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSFontRef 
ATSFontFindFromPostScriptName(
  CFStringRef      iName,
  ATSOptionFlags   iOptions);


/*
 *  ATSFontFindFromContainer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFindFromContainer(
  ATSFontContainerRef   iContainer,
  ATSOptionFlags        iOptions,
  ItemCount             iCount,
  ATSFontRef            ioArray[],
  ItemCount *           oCount);


/*
 *  ATSFontGetGeneration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSGeneration 
ATSFontGetGeneration(ATSFontRef iFont);


/*
 *  ATSFontGetName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetName(
  ATSFontRef       iFont,
  ATSOptionFlags   iOptions,
  CFStringRef *    oName);


/*
 *  ATSFontGetPostScriptName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetPostScriptName(
  ATSFontRef       iFont,
  ATSOptionFlags   iOptions,
  CFStringRef *    oName);


/*
 *  ATSFontGetTableDirectory()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetTableDirectory(
  ATSFontRef   iFont,
  ByteCount    iBufferSize,
  void *       ioBuffer,
  ByteCount *  oSize);            /* can be NULL */


/*
 *  ATSFontGetTable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetTable(
  ATSFontRef     iFont,
  FourCharCode   iTag,
  ByteOffset     iOffset,
  ByteCount      iBufferSize,
  void *         ioBuffer,
  ByteCount *    oSize);            /* can be NULL */


/*
 *  ATSFontGetHorizontalMetrics()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetHorizontalMetrics(
  ATSFontRef        iFont,
  ATSOptionFlags    iOptions,
  ATSFontMetrics *  oMetrics);


/*
 *  ATSFontGetVerticalMetrics()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetVerticalMetrics(
  ATSFontRef        iFont,
  ATSOptionFlags    iOptions,
  ATSFontMetrics *  oMetrics);


/* ----------------------------------------------------------------------------------------- */
/* Compatibiity                                                                              */
/* ----------------------------------------------------------------------------------------- */
/*
 *  ATSFontFamilyFindFromQuickDrawName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern ATSFontFamilyRef 
ATSFontFamilyFindFromQuickDrawName(ConstStr255Param iName);


/*
 *  ATSFontFamilyGetQuickDrawName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontFamilyGetQuickDrawName(
  ATSFontFamilyRef   iFamily,
  Str255             oName);


/*
 *  ATSFontGetFileSpecification()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetFileSpecification(
  ATSFontRef   iFont,
  FSSpec *     oFile);


/*
 *  ATSFontGetFontFamilyResource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.0 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
ATSFontGetFontFamilyResource(
  ATSFontRef   iFont,
  ByteCount    iBufferSize,
  void *       ioBuffer,
  ByteCount *  oSize);            /* can be NULL */




#if PRAGMA_ENUM_ALWAYSINT
    #pragma enumsalwaysint reset
    #ifdef __ATSFONT__RESTORE_TWOBYTEINTS
        #pragma fourbyteints off
    #endif
#elif PRAGMA_ENUM_OPTIONS
    #pragma option enum=reset
#elif defined(__ATSFONT__RESTORE_PACKED_ENUMS)
    #pragma options(pack_enums)
#endif

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

#endif /* __ATSFONT__ */

