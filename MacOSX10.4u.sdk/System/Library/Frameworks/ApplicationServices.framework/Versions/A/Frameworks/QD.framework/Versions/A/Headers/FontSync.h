/*
     File:       QD/FontSync.h
 
     Contains:   Public interface for FontSync
 
     Version:    Quickdraw-192.24~58
 
     Copyright:  © 1999-2006 by Apple Computer, Inc., all rights reserved.
 
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
FNSMatchDefaultsGet(void)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
FNSSysInfoGet(FNSSysInfo * ioInfo)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
  FNSObjectVersion *  oVersion)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FNSReferenceDispose()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSReferenceDispose(FNSFontReference iReference)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  FNSMatchOptions *  oFailedMatchOptions)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ByteCount *        oFlattenedSize)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ByteCount *        oFlattenedSize)       /* can be NULL */  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  FNSFontReference *  oReference)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
  FNSFontProfile *   oProfile)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  FNSFontProfile *  oProfile)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
  FNSFontProfile *   oProfile)                                AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


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
  FNSFontProfile *  oProfile)                                 AVAILABLE_MAC_OS_X_VERSION_10_1_AND_LATER;


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
  FNSObjectVersion *  oVersion)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FNSProfileCompact()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileCompact(FNSFontProfile iProfile)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FNSProfileClose()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileClose(FNSFontProfile iProfile)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  FNSFontReference   iReference)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  FNSFontReference   iReference)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  UInt32           iIndex)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FNSProfileClear()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in FontSyncLib 1.0 and later
 */
extern OSStatus 
FNSProfileClear(FNSFontProfile iProfile)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *      oCount)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  FNSFontReference *  oReference)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *        oNumMatches)         /* can be NULL */   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
  FNSFontReference *  oReference)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *        oNumMatches)         /* can be NULL */   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
  FMFontStyle *       oActualStyle)          /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *            oNumMatches)         /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



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
  FMFontStyle *      oActualStyle)            /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *        oNameCount)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  FontLanguageCode *  oFontNameLanguage)        /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  ItemCount *        oFontNameIndex)           /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
FNSEnabled(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __FONTSYNC__ */

