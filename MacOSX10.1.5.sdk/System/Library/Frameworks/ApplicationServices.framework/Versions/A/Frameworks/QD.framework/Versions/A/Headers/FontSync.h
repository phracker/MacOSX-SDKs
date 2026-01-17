/*
     File:       QD/FontSync.h
 
     Contains:   Public interface for FontSync
 
     Version:    Quickdraw-64.6.15~3
 
     Copyright:  © 1999-2001 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __FONTSYNC__
#define __FONTSYNC__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif

#ifndef __FILES__
#include <CarbonCore/Files.h>
#endif

#ifndef __FONTS__
#include <QD/Fonts.h>
#endif

#ifndef __SFNTTYPES__
#include <ATS/SFNTTypes.h>
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
    #pragma options align=power
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif


/* Matching Options */
typedef UInt32 FNSMatchOptions;
enum {
  kFNSMatchNames                = 0x00000001, /* font names must match */
  kFNSMatchTechnology           = 0x00000002, /* scaler technology must match */
  kFNSMatchGlyphs               = 0x00000004, /* glyph data must match */
  kFNSMatchEncodings            = 0x00000008, /* cmaps must match */
  kFNSMatchQDMetrics            = 0x00000010, /* QuickDraw Text metrics must match */
  kFNSMatchATSUMetrics          = 0x00000020, /* ATSUI metrics (incl. vertical) must match */
  kFNSMatchKerning              = 0x00000040, /* kerning data must match */
  kFNSMatchWSLayout             = 0x00000080, /* WorldScript layout tables must match */
  kFNSMatchAATLayout            = 0x00000100, /* AAT (incl. OpenType) layout tables must match */
  kFNSMatchPrintEncoding        = 0x00000200, /* PostScript font and glyph names and re-encoding vector must match */
  kFNSMissingDataNoMatch        = (unsigned long)0x80000000, /* treat missing data as mismatch */
  kFNSMatchAll                  = (unsigned long)0xFFFFFFFF, /* everything must match */
  kFNSMatchDefaults             = 0     /* use global default match options */
};

/*
 *  FNSMatchDefaultsGet()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern FNSMatchOptions 
FNSMatchDefaultsGet(void);



/* Version control */
typedef UInt32 FNSObjectVersion;
enum {
  kFNSVersionDontCare           = 0,
  kFNSCurSysInfoVersion         = 1
};

/* No features defined yet.*/
typedef UInt32                          FNSFeatureFlags;
/*
   The FontSync library version number is binary-coded decimal:
   8 bits of major version, 4 minor version and 4 bits revision.
*/
struct FNSSysInfo {
  FNSObjectVersion    iSysInfoVersion;        /* fill this in before calling FNSSysInfoGet*/
  FNSFeatureFlags     oFeatures;
  FNSObjectVersion    oCurRefVersion;
  FNSObjectVersion    oMinRefVersion;
  FNSObjectVersion    oCurProfileVersion;
  FNSObjectVersion    oMinProfileVersion;
  UInt16              oFontSyncVersion;
};
typedef struct FNSSysInfo               FNSSysInfo;
/*
 *  FNSSysInfoGet()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern void 
FNSSysInfoGet(FNSSysInfo * ioInfo);



/* FontSync References */
typedef struct OpaqueFNSFontReference*  FNSFontReference;
/*
 *  FNSReferenceGetVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceGetVersion(
  FNSFontReference    iReference,
  FNSObjectVersion *  oVersion);


/*
 *  FNSReferenceDispose()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceDispose(FNSFontReference iReference);


/*
 *  FNSReferenceMatch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceMatch(
  FNSFontReference   iReference1,
  FNSFontReference   iReference2,
  FNSMatchOptions    iOptions,
  FNSMatchOptions *  oFailedMatchOptions);      /* can be NULL */


/*
 *  FNSReferenceFlattenedSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceFlattenedSize(
  FNSFontReference   iReference,
  ByteCount *        oFlattenedSize);


/*
 *  FNSReferenceFlatten()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceFlatten(
  FNSFontReference   iReference,
  void *             oFlatReference,       /* can be NULL */
  ByteCount *        oFlattenedSize);      /* can be NULL */


/*
 *  FNSReferenceUnflatten()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceUnflatten(
  const void *        iFlatReference,
  ByteCount           iFlattenedSize,
  FNSFontReference *  oReference);



/* FontSync Profiles */
enum {
  kFNSCreatorDefault            = 0,
  kFNSProfileFileType           = 'fnsp'
};

typedef struct OpaqueFNSFontProfile*    FNSFontProfile;
/*
 *  FNSProfileCreate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileCreate(
  const FSSpec *     iFile,
  FourCharCode       iCreator,
  ItemCount          iEstNumRefs,
  FNSObjectVersion   iDesiredVersion,
  FNSFontProfile *   oProfile);


/*
 *  FNSProfileOpen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileOpen(
  const FSSpec *    iFile,
  Boolean           iOpenForWrite,
  FNSFontProfile *  oProfile);



/*
 *  FNSProfileCreateWithFSRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FNSProfileCreateWithFSRef(
  const FSRef *      iParentDirectory,
  UniCharCount       iNameLength,
  const UniChar *    iName,
  FourCharCode       iCreator,
  ItemCount          iEstNumRefs,
  FNSObjectVersion   iDesiredVersion,
  FNSFontProfile *   oProfile);


/*
 *  FNSProfileOpenWithFSRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FNSProfileOpenWithFSRef(
  const FSRef *     iFile,
  Boolean           iOpenForWrite,
  FNSFontProfile *  oProfile);


/*
 *  FNSProfileGetVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileGetVersion(
  FNSFontProfile      iProfile,
  FNSObjectVersion *  oVersion);


/*
 *  FNSProfileCompact()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileCompact(FNSFontProfile iProfile);


/*
 *  FNSProfileClose()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileClose(FNSFontProfile iProfile);


/*
 *  FNSProfileAddReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileAddReference(
  FNSFontProfile     iProfile,
  FNSFontReference   iReference);


/*
 *  FNSProfileRemoveReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileRemoveReference(
  FNSFontProfile     iProfile,
  FNSFontReference   iReference);


/*
 *  FNSProfileRemoveIndReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileRemoveIndReference(
  FNSFontProfile   iProfile,
  UInt32           iIndex);


/*
 *  FNSProfileClear()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileClear(FNSFontProfile iProfile);


/*
 *  FNSProfileCountReferences()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileCountReferences(
  FNSFontProfile   iProfile,
  ItemCount *      oCount);


/*
 *  FNSProfileGetIndReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileGetIndReference(
  FNSFontProfile      iProfile,
  UInt32              iWhichReference,
  FNSFontReference *  oReference);


/*
 *  FNSProfileMatchReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileMatchReference(
  FNSFontProfile     iProfile,
  FNSFontReference   iReference,
  FNSMatchOptions    iMatchOptions,
  ItemCount          iOutputSize,
  UInt32             oIndices[],          /* can be NULL */
  ItemCount *        oNumMatches);        /* can be NULL */



/* Mapping to and from Font Objects */
/*
 *  FNSReferenceCreate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceCreate(
  FMFont              iFont,
  FNSObjectVersion    iDesiredVersion,
  FNSFontReference *  oReference);


/*
 *  FNSReferenceMatchFonts()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceMatchFonts(
  FNSFontReference   iReference,
  FNSMatchOptions    iMatchOptions,
  ItemCount          iOutputSize,
  FMFont             oFonts[],            /* can be NULL */
  ItemCount *        oNumMatches);        /* can be NULL */



/* Mapping to and from Font Families */
/*
 *  FNSReferenceCreateFromFamily()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceCreateFromFamily(
  FMFontFamily        iFamily,
  FMFontStyle         iStyle,
  FNSObjectVersion    iDesiredVersion,
  FNSFontReference *  oReference,            /* can be NULL */
  FMFontStyle *       oActualStyle);         /* can be NULL */


/*
 *  FNSReferenceMatchFamilies()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceMatchFamilies(
  FNSFontReference       iReference,
  FNSMatchOptions        iMatchOptions,
  ItemCount              iOutputSize,
  FMFontFamilyInstance   oFonts[],            /* can be NULL */
  ItemCount *            oNumMatches);        /* can be NULL */



/* UI Support */
/*
 *  FNSReferenceGetFamilyInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceGetFamilyInfo(
  FNSFontReference   iReference,
  Str255             oFamilyName,             /* can be NULL */
  ScriptCode *       oFamilyNameScript,       /* can be NULL */
  FMFontStyle *      oActualStyle);           /* can be NULL */


/*
 *  FNSReferenceCountNames()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceCountNames(
  FNSFontReference   iReference,
  ItemCount *        oNameCount);


/*
 *  FNSReferenceGetIndName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceGetIndName(
  FNSFontReference    iReference,
  ItemCount           iFontNameIndex,
  ByteCount           iMaximumNameLength,
  Ptr                 oName,                    /* can be NULL */
  ByteCount *         oActualNameLength,        /* can be NULL */
  FontNameCode *      oFontNameCode,            /* can be NULL */
  FontPlatformCode *  oFontNamePlatform,        /* can be NULL */
  FontScriptCode *    oFontNameScript,          /* can be NULL */
  FontLanguageCode *  oFontNameLanguage);       /* can be NULL */


/*
 *  FNSReferenceFindName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceFindName(
  FNSFontReference   iReference,
  FontNameCode       iFontNameCode,
  FontPlatformCode   iFontNamePlatform,
  FontScriptCode     iFontNameScript,
  FontLanguageCode   iFontNameLanguage,
  ByteCount          iMaximumNameLength,
  Ptr                oName,                    /* can be NULL */
  ByteCount *        oActualNameLength,        /* can be NULL */
  ItemCount *        oFontNameIndex);          /* can be NULL */


/* Miscellany */
/*
 *  FNSEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern Boolean 
FNSEnabled(void);



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

#endif /* __FONTSYNC__ */

