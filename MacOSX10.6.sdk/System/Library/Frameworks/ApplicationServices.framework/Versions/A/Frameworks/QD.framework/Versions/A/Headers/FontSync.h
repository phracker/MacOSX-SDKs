/*
     File:       QD/FontSync.h
 
     Contains:   Public interface for FontSync
 
     Version:    Quickdraw-264.3~1
 
     Copyright:  © 1999-2008 by Apple Inc. all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __FONTSYNC__
#define __FONTSYNC__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __FONTS__
#include <QD/Fonts.h>
#endif

#ifndef __SFNTTYPES__
#include <ATS/SFNTTypes.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=power


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
  kFNSMissingDataNoMatch        = (UInt32)0x80000000, /* treat missing data as mismatch */
  kFNSMatchAll                  = (UInt32)0xFFFFFFFF, /* everything must match */
  kFNSMatchDefaults             = 0     /* use global default match options */
};

#if !__LP64__
/*
 *  FNSMatchDefaultsGet()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern FNSMatchOptions 
FNSMatchDefaultsGet(void)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;



/* Version control */
#endif  /* !__LP64__ */

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
#if !__LP64__
/*
 *  FNSSysInfoGet()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern void 
FNSSysInfoGet(FNSSysInfo * ioInfo)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;



/* FontSync References */
#endif  /* !__LP64__ */

typedef struct OpaqueFNSFontReference*  FNSFontReference;
#if !__LP64__
/*
 *  FNSReferenceGetVersion()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceGetVersion(
  FNSFontReference    iReference,
  FNSObjectVersion *  oVersion)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSReferenceDispose()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceDispose(FNSFontReference iReference)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSReferenceMatch()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceMatch(
  FNSFontReference   iReference1,
  FNSFontReference   iReference2,
  FNSMatchOptions    iOptions,
  FNSMatchOptions *  oFailedMatchOptions)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSReferenceFlattenedSize()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceFlattenedSize(
  FNSFontReference   iReference,
  ByteCount *        oFlattenedSize)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSReferenceFlatten()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceFlatten(
  FNSFontReference   iReference,
  void *             oFlatReference,       /* can be NULL */
  ByteCount *        oFlattenedSize)       /* can be NULL */  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSReferenceUnflatten()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceUnflatten(
  const void *        iFlatReference,
  ByteCount           iFlattenedSize,
  FNSFontReference *  oReference)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;



/* FontSync Profiles */
#endif  /* !__LP64__ */

enum {
  kFNSCreatorDefault            = 0,
  kFNSProfileFileType           = 'fnsp'
};

typedef struct OpaqueFNSFontProfile*    FNSFontProfile;
#if !__LP64__
/*
 *  FNSProfileCreate()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileCreate(
  const FSSpec *     iFile,
  FourCharCode       iCreator,
  ItemCount          iEstNumRefs,
  FNSObjectVersion   iDesiredVersion,
  FNSFontProfile *   oProfile)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSProfileOpen()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileOpen(
  const FSSpec *    iFile,
  Boolean           iOpenForWrite,
  FNSFontProfile *  oProfile)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;



/*
 *  FNSProfileCreateWithFSRef()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  FNSFontProfile *   oProfile)                                AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSProfileOpenWithFSRef()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.1 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
FNSProfileOpenWithFSRef(
  const FSRef *     iFile,
  Boolean           iOpenForWrite,
  FNSFontProfile *  oProfile)                                 AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSProfileGetVersion()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileGetVersion(
  FNSFontProfile      iProfile,
  FNSObjectVersion *  oVersion)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSProfileCompact()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in  in ApplicationServices.framework [32-bit only] but deprecated in LeopardX
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileCompact(FNSFontProfile iProfile);


/*
 *  FNSProfileClose()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileClose(FNSFontProfile iProfile)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSProfileAddReference()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileAddReference(
  FNSFontProfile     iProfile,
  FNSFontReference   iReference)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSProfileRemoveReference()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileRemoveReference(
  FNSFontProfile     iProfile,
  FNSFontReference   iReference)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSProfileRemoveIndReference()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileRemoveIndReference(
  FNSFontProfile   iProfile,
  UInt32           iIndex)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSProfileClear()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileClear(FNSFontProfile iProfile)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSProfileCountReferences()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileCountReferences(
  FNSFontProfile   iProfile,
  ItemCount *      oCount)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSProfileGetIndReference()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileGetIndReference(
  FNSFontProfile      iProfile,
  UInt32              iWhichReference,
  FNSFontReference *  oReference)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSProfileMatchReference()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  ItemCount *        oNumMatches)         /* can be NULL */   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;



/* Mapping to and from Font Objects */
/*
 *  FNSReferenceCreate()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceCreate(
  FMFont              iFont,
  FNSObjectVersion    iDesiredVersion,
  FNSFontReference *  oReference)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSReferenceMatchFonts()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceMatchFonts(
  FNSFontReference   iReference,
  FNSMatchOptions    iMatchOptions,
  ItemCount          iOutputSize,
  FMFont             oFonts[],            /* can be NULL */
  ItemCount *        oNumMatches)         /* can be NULL */   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;



/* Mapping to and from Font Families */
/*
 *  FNSReferenceCreateFromFamily()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceCreateFromFamily(
  FMFontFamily        iFamily,
  FMFontStyle         iStyle,
  FNSObjectVersion    iDesiredVersion,
  FNSFontReference *  oReference,            /* can be NULL */
  FMFontStyle *       oActualStyle)          /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSReferenceMatchFamilies()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceMatchFamilies(
  FNSFontReference       iReference,
  FNSMatchOptions        iMatchOptions,
  ItemCount              iOutputSize,
  FMFontFamilyInstance   oFonts[],            /* can be NULL */
  ItemCount *            oNumMatches)         /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;



/* UI Support */
/*
 *  FNSReferenceGetFamilyInfo()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceGetFamilyInfo(
  FNSFontReference   iReference,
  Str255             oFamilyName,             /* can be NULL */
  ScriptCode *       oFamilyNameScript,       /* can be NULL */
  FMFontStyle *      oActualStyle)            /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSReferenceCountNames()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceCountNames(
  FNSFontReference   iReference,
  ItemCount *        oNameCount)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSReferenceGetIndName()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  FontLanguageCode *  oFontNameLanguage)        /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/*
 *  FNSReferenceFindName()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
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
  ItemCount *        oFontNameIndex)           /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


/* Miscellany */
/*
 *  FNSEnabled()   *** DEPRECATED ***
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework [32-bit only] but deprecated in 10.5
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern Boolean 
FNSEnabled(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_5;


#endif  /* !__LP64__ */


#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __FONTSYNC__ */

