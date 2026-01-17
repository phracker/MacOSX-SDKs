/*
     File:       LangAnalysis/LanguageAnalysis.h
 
     Contains:   Language Analysis Manager Interfaces
 
     Version:    LanguageAnalysis-164.2.17~316
 
     Copyright:  © 1996-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __LANGUAGEANALYSIS__
#define __LANGUAGEANALYSIS__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __AE__
#include <AE/AE.h>
#endif

#ifndef __DICTIONARY__
#include <LangAnalysis/Dictionary.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=power

typedef struct OpaqueLAEnvironmentRef*  LAEnvironmentRef;
typedef struct OpaqueLAContextRef*      LAContextRef;
typedef AEKeyword                       LAPropertyKey;
typedef DescType                        LAPropertyType;
/*
    Data structure for high level API
*/
struct LAMorphemeRec {
  ByteCount           sourceTextLength;
  LogicalAddress      sourceTextPtr;
  ByteCount           morphemeTextLength;
  LogicalAddress      morphemeTextPtr;
  UInt32              partOfSpeech;
};
typedef struct LAMorphemeRec            LAMorphemeRec;
struct LAMorphemesArray {
  ItemCount           morphemesCount;
  ByteCount           processedTextLength;
  ByteCount           morphemesTextLength;
  LAMorphemeRec       morphemes[1];
};
typedef struct LAMorphemesArray         LAMorphemesArray;
typedef LAMorphemesArray *              LAMorphemesArrayPtr;
enum {
  kLAMorphemesArrayVersion      = 0
};

/*
    Definitions for result path/bundle structure
*/
typedef AERecord                        LAMorphemeBundle;
typedef AERecord                        LAMorphemePath;
typedef AERecord                        LAMorpheme;
typedef AERecord                        LAHomograph;
enum {
  keyAELAMorphemeBundle         = 'lmfb',
  keyAELAMorphemePath           = 'lmfp',
  keyAELAMorpheme               = 'lmfn',
  keyAELAHomograph              = 'lmfh'
};

enum {
  typeLAMorphemeBundle          = typeAERecord,
  typeLAMorphemePath            = typeAERecord,
  typeLAMorpheme                = typeAEList,
  typeLAHomograph               = typeAEList
};

/*
    Definitions for morpheme/homograph information
*/
enum {
  keyAEMorphemePartOfSpeechCode = 'lamc',
  keyAEMorphemeTextRange        = 'lamt'
};

enum {
  typeAEMorphemePartOfSpeechCode = 'lamc',
  typeAEMorphemeTextRange       = 'lamt'
};

typedef UInt32                          MorphemePartOfSpeech;
struct MorphemeTextRange {
  UInt32              sourceOffset;
  UInt32              length;
};
typedef struct MorphemeTextRange        MorphemeTextRange;
/*
    Mask for High level API convert flags 
*/
enum {
  kLAEndOfSourceTextMask        = 0x00000001
};

/*
    Constants for leading/trailing path of analysis function
*/
enum {
  kLADefaultEdge                = 0,
  kLAFreeEdge                   = 1,
  kLAIncompleteEdge             = 2
};

/*
    Constants for confirm and shift function
*/
enum {
  kLAAllMorphemes               = 0
};


/*
    Library version
*/
/*
 *  LALibraryVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern UInt32 
LALibraryVersion(void)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    High level API
*/
/*
 *  LATextToMorphemes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LATextToMorphemes(
  LAContextRef          context,
  TextEncoding          preferedEncoding,
  ByteCount             textLength,
  ConstLogicalAddress   sourceText,
  ByteCount             bufferSize,
  OptionBits            convertFlags,
  UInt32                structureVersion,
  ByteCount *           acceptedLength,
  LAMorphemesArrayPtr   resultBuffer)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Handling Context
*/
/*
 *  LAOpenAnalysisContext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LAOpenAnalysisContext(
  LAEnvironmentRef   environ,
  LAContextRef *     context)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LACloseAnalysisContext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LACloseAnalysisContext(LAContextRef context)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Handling Environment
*/
/*
 *  LAGetEnvironmentList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LAGetEnvironmentList(
  UInt32             maxCount,
  UInt32 *           actualCount,
  LAEnvironmentRef   environmentList[])                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LAGetEnvironmentName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LAGetEnvironmentName(
  LAEnvironmentRef   environment,
  Str63              environmentName)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LAGetEnvironmentRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LAGetEnvironmentRef(
  ConstStr63Param     targetEnvironmentName,
  LAEnvironmentRef *  environment)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LACreateCustomEnvironment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LACreateCustomEnvironment(
  LAEnvironmentRef    baseEnvironment,
  ConstStr63Param     newEnvironmentName,
  Boolean             persistent,
  LAEnvironmentRef *  newEnvironment)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LADeleteCustomEnvironment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LADeleteCustomEnvironment(LAEnvironmentRef environment)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Handling dictionries
*/
/*
 *  LAOpenDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LAOpenDictionary(
  LAEnvironmentRef   environ,
  const FSSpec *     dictionary)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LACloseDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LACloseDictionary(
  LAEnvironmentRef   environ,
  const FSSpec *     dictionary)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LAListAvailableDictionaries()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LAListAvailableDictionaries(
  LAEnvironmentRef   environ,
  ItemCount          maxCount,
  ItemCount *        actualCount,
  FSSpec             dictionaryList[],
  Boolean            opened[])                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LAAddNewWord()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LAAddNewWord(
  LAEnvironmentRef   environ,
  const FSSpec *     dictionary,
  const AEDesc *     dataList)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Analyzing text
*/
/*
 *  LAMorphemeAnalysis()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LAMorphemeAnalysis(
  LAContextRef           context,
  ConstUniCharArrayPtr   text,
  UniCharCount           textLength,
  LAMorphemePath *       leadingPath,
  LAMorphemePath *       trailingPath,
  ItemCount              pathCount,
  LAMorphemeBundle *     result)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LAContinuousMorphemeAnalysis()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LAContinuousMorphemeAnalysis(
  LAContextRef           context,
  ConstUniCharArrayPtr   text,
  UniCharCount           textLength,
  Boolean                incrementalText,
  LAMorphemePath *       leadingPath,
  LAMorphemePath *       trailingPath,
  Boolean *              modified)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LAGetMorphemes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LAGetMorphemes(
  LAContextRef      context,
  LAMorphemePath *  result)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LAShiftMorphemes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LAShiftMorphemes(
  LAContextRef      context,
  ItemCount         morphemeCount,
  LAMorphemePath *  path,
  UniCharCount *    shiftedLength)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LAResetAnalysis()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in LanguageAnalysisLib 1.0 and later
 */
extern OSStatus 
LAResetAnalysis(LAContextRef context)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    Check Language Analysis Manager availability
*/
#if TARGET_RT_MAC_CFM
#ifdef __cplusplus
    inline pascal Boolean LALanguageAnalysisAvailable() { return (LALibraryVersion != (void*)kUnresolvedCFragSymbolAddress); }
#else
    #define LALanguageAnalysisAvailable()   ((LALibraryVersion != (void*)kUnresolvedCFragSymbolAddress)
#endif
#elif TARGET_RT_MAC_MACHO
/* Language Analysis Manager is always available on OS X */
#ifdef __cplusplus
    inline pascal Boolean LALanguageAnalysisAvailable() { return true; }
#else
    #define LALanguageAnalysisAvailable()   (true)
#endif
#endif  /*  */

/*
=============================================================================================
    Definitions for Japanese Analysis Module
=============================================================================================
*/
/*
    Names for default environments for Japanese analysis
*/
#define kLAJapaneseKanaKanjiEnvironment             "\pKanaKanjiConversion"
#define kLAJapaneseMorphemeAnalysisEnvironment      "\pJapaneseMorphemeAnalysis"
#define kLAJapaneseTTSEnvironment                   "\pJapaneseTextToSpeech"
/*
    File cretor for dictionary of Apple Japanese access method
*/
enum {
  kAppleJapaneseDictionarySignature = 'jlan'
};

/*
    Engine limitations
*/
enum {
  kMaxInputLengthOfAppleJapaneseEngine = 200
};

/*
    Definitions of information in the path/bundle
*/

typedef MorphemePartOfSpeech            JapanesePartOfSpeech;
typedef UInt16                          HomographWeight;
typedef UInt8                           HomographAccent;
/*
    AE keywords and type definitions for morpheme/homograph information
*/
enum {
  keyAEHomographDicInfo         = 'lahd',
  keyAEHomographWeight          = 'lahw',
  keyAEHomographAccent          = 'laha'
};

enum {
  typeAEHomographDicInfo        = 'lahd',
  typeAEHomographWeight         = typeShortInteger,
  typeAEHomographAccent         = 'laha'
};

/*
    Structure for dictionary information of homograph
*/
struct HomographDicInfoRec {
  DCMDictionaryID     dictionaryID;
  DCMUniqueID         uniqueID;
};
typedef struct HomographDicInfoRec      HomographDicInfoRec;
/*
=============================================================================================
    Definitions for Japanese part of speeches
=============================================================================================
*/
/*
    Masks for part of speeches
*/
enum {
  kLASpeechRoughClassMask       = 0x0000F000,
  kLASpeechMediumClassMask      = 0x0000FF00,
  kLASpeechStrictClassMask      = 0x0000FFF0,
  kLASpeechKatsuyouMask         = 0x0000000F
};


/*
    Part of speeches
*/
enum {
  kLASpeechMeishi               = 0x00000000, /* noun */
  kLASpeechFutsuuMeishi         = 0x00000000, /* general noun */
  kLASpeechJinmei               = 0x00000100, /* person name */
  kLASpeechJinmeiSei            = 0x00000110, /* family name */
  kLASpeechJinmeiMei            = 0x00000120, /* first name */
  kLASpeechChimei               = 0x00000200, /* place name */
  kLASpeechSetsubiChimei        = 0x00000210, /* place name with suffix */
  kLASpeechSoshikimei           = 0x00000300, /* organization name */
  kLASpeechKoyuuMeishi          = 0x00000400, /* proper noun */
  kLASpeechSahenMeishi          = 0x00000500, /* special noun */
  kLASpeechKeidouMeishi         = 0x00000600, /* special noun */
  kLASpeechRentaishi            = 0x00001000,
  kLASpeechFukushi              = 0x00002000, /* adverb */
  kLASpeechSetsuzokushi         = 0x00003000, /* conjunction */
  kLASpeechKandoushi            = 0x00004000,
  kLASpeechDoushi               = 0x00005000, /* verb */
  kLASpeechGodanDoushi          = 0x00005000,
  kLASpeechKagyouGodan          = 0x00005000,
  kLASpeechSagyouGodan          = 0x00005010,
  kLASpeechTagyouGodan          = 0x00005020,
  kLASpeechNagyouGodan          = 0x00005030,
  kLASpeechMagyouGodan          = 0x00005040,
  kLASpeechRagyouGodan          = 0x00005050,
  kLASpeechWagyouGodan          = 0x00005060,
  kLASpeechGagyouGodan          = 0x00005070,
  kLASpeechBagyouGodan          = 0x00005080,
  kLASpeechIchidanDoushi        = 0x00005100,
  kLASpeechKahenDoushi          = 0x00005200,
  kLASpeechSahenDoushi          = 0x00005300,
  kLASpeechZahenDoushi          = 0x00005400,
  kLASpeechKeiyoushi            = 0x00006000, /* adjective */
  kLASpeechKeiyoudoushi         = 0x00007000,
  kLASpeechSettougo             = 0x00008000, /* prefix*/
  kLASpeechSuujiSettougo        = 0x00008100, /* prefix for numbers */
  kLASpeechSetsubigo            = 0x00009000, /* suffix */
  kLASpeechJinmeiSetsubigo      = 0x00009100, /* suffix for person name */
  kLASpeechChimeiSetsubigo      = 0x00009200, /* suffix for place name */
  kLASpeechSoshikimeiSetsubigo  = 0x00009300, /* suffix for organization name */
  kLASpeechSuujiSetsubigo       = 0x00009400, /* suffix for numbers */
  kLASpeechMuhinshi             = 0x0000A000, /* no category */
  kLASpeechTankanji             = 0x0000A000, /* character */
  kLASpeechKigou                = 0x0000A100, /* symbol */
  kLASpeechKuten                = 0x0000A110,
  kLASpeechTouten               = 0x0000A120,
  kLASpeechSuushi               = 0x0000A200, /* numbers */
  kLASpeechDokuritsugo          = 0x0000A300,
  kLASpeechSeiku                = 0x0000A400,
  kLASpeechJodoushi             = 0x0000B000, /* auxiliary verb */
  kLASpeechJoshi                = 0x0000C000 /* postpositional particle */
};


/*
    Conjugations
 */
enum {
  kLASpeechKatsuyouGokan        = 0x00000001, /* stem */
  kLASpeechKatsuyouMizen        = 0x00000002,
  kLASpeechKatsuyouRenyou       = 0x00000003,
  kLASpeechKatsuyouSyuushi      = 0x00000004,
  kLASpeechKatsuyouRentai       = 0x00000005,
  kLASpeechKatsuyouKatei        = 0x00000006,
  kLASpeechKatsuyouMeirei       = 0x00000007
};



#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __LANGUAGEANALYSIS__ */

