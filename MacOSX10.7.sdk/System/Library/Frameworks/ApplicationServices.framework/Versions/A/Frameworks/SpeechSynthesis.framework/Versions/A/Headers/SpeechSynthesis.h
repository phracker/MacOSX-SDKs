/*
     File:       SpeechSynthesis/SpeechSynthesis.h
 
     Contains:   Speech Interfaces.
 
     Version:    SpeechSynthesis-4.0.74~1
 
     Copyright:  © 1989-2008 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __SPEECHSYNTHESIS__
#define __SPEECHSYNTHESIS__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#include <stdint.h>


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

enum {
  kTextToSpeechSynthType        = 'ttsc',
  kTextToSpeechVoiceType        = 'ttvd',
  kTextToSpeechVoiceFileType    = 'ttvf',
  kTextToSpeechVoiceBundleType  = 'ttvb'
};

enum {
  kNoEndingProsody              = 1,
  kNoSpeechInterrupt            = 2,
  kPreflightThenPause           = 4
};

enum {
  kImmediate                    = 0,
  kEndOfWord                    = 1,
  kEndOfSentence                = 2
};


/*------------------------------------------*/
/* GetSpeechInfo & SetSpeechInfo selectors  */
/*------------------------------------------*/
enum {
  soStatus                      = 'stat',
  soErrors                      = 'erro',
  soInputMode                   = 'inpt',
  soCharacterMode               = 'char',
  soNumberMode                  = 'nmbr',
  soRate                        = 'rate',
  soPitchBase                   = 'pbas',
  soPitchMod                    = 'pmod',
  soVolume                      = 'volm',
  soSynthType                   = 'vers',
  soRecentSync                  = 'sync',
  soPhonemeSymbols              = 'phsy',
  soCurrentVoice                = 'cvox',
  soCommandDelimiter            = 'dlim',
  soReset                       = 'rset',
  soCurrentA5                   = 'myA5',
  soRefCon                      = 'refc',
  soTextDoneCallBack            = 'tdcb', /* use with SpeechTextDoneProcPtr*/
  soSpeechDoneCallBack          = 'sdcb', /* use with SpeechDoneProcPtr*/
  soSyncCallBack                = 'sycb', /* use with SpeechSyncProcPtr*/
  soErrorCallBack               = 'ercb', /* use with SpeechErrorProcPtr*/
  soPhonemeCallBack             = 'phcb', /* use with SpeechPhonemeProcPtr*/
  soWordCallBack                = 'wdcb', /* use with SpeechWordProcPtr*/
  soSynthExtension              = 'xtnd',
  soSoundOutput                 = 'sndo',
  soOutputToFileWithCFURL       = 'opaf', /* Pass a CFURLRef to write to this file, NULL to generate sound.*/
  soOutputToExtAudioFile        = 'opax', /* Pass a ExtAudioFileRef to write to this file, NULL to generate sound. Available in 10.6 and later.*/
  soOutputToAudioDevice         = 'opad', /* Pass an AudioDeviceID to play to this file, 0 to play to default output*/
  soPhonemeOptions              = 'popt' /* Available in 10.6 and later*/
};


/*------------------------------------------*/
/* Speaking Mode Constants                  */
/*------------------------------------------*/
enum {
  modeText                      = 'TEXT', /* input mode constants             */
  modePhonemes                  = 'PHON',
  modeTune                      = 'TUNE',
  modeNormal                    = 'NORM', /* character mode and number mode constants */
  modeLiteral                   = 'LTRL'
};


enum {
  soVoiceDescription            = 'info',
  soVoiceFile                   = 'fref'
};

/*------------------------------------------*/
/* Flags for phoneme generation.            */
/*------------------------------------------*/
enum {
  kSpeechGenerateTune           = 1,    /* Generate detailed "tune" instead of just phonemes  */
  kSpeechRelativePitch          = 2,    /* Pitch relative to voice baseline             */
  kSpeechRelativeDuration       = 4,    /* Duration relative to speech rate             */
  kSpeechShowSyllables          = 8     /* Show all syllable marks                              */
};

/*------------------------------------------*/
/* AudioUnit constants - new in 10.5        */
/*------------------------------------------*/
enum {
  kAudioUnitSubType_SpeechSynthesis = 'ttsp', /* kAudioUnitType_Generator */
  kAudioUnitProperty_Voice      = 3330, /* Get/Set (VoiceSpec)      */
  kAudioUnitProperty_SpeechChannel = 3331 /* Get (SpeechChannel)      */
};

/*
   The speech manager sources may or may not need SpeechChannelRecord.
   If not, the .i file should be changed to use the opaque mechanism.
*/
struct SpeechChannelRecord {
  long                data[1];
};
typedef struct SpeechChannelRecord      SpeechChannelRecord;
typedef SpeechChannelRecord *           SpeechChannel;

struct VoiceSpec {
  OSType              creator;
  OSType              id;
};
typedef struct VoiceSpec                VoiceSpec;
typedef VoiceSpec *                     VoiceSpecPtr;

enum {
  kNeuter                       = 0,
  kMale                         = 1,
  kFemale                       = 2
};




struct VoiceDescription {
  SInt32              length;
  VoiceSpec           voice;
  SInt32              version;
  Str63               name;
  Str255              comment;
  SInt16              gender;
  SInt16              age;
  SInt16              script;
  SInt16              language;
  SInt16              region;
  SInt32              reserved[4];
};
typedef struct VoiceDescription         VoiceDescription;


struct VoiceFileInfo {
  FSSpec              fileSpec;
  SInt16              resID;
};
typedef struct VoiceFileInfo            VoiceFileInfo;
struct SpeechStatusInfo {
  Boolean             outputBusy;
  Boolean             outputPaused;
  long                inputBytesLeft;
  SInt16              phonemeCode;
};
typedef struct SpeechStatusInfo         SpeechStatusInfo;


struct SpeechErrorInfo {
  SInt16              count;
  OSErr               oldest;
  long                oldPos;
  OSErr               newest;
  long                newPos;
};
typedef struct SpeechErrorInfo          SpeechErrorInfo;


struct SpeechVersionInfo {
  OSType              synthType;
  OSType              synthSubType;
  OSType              synthManufacturer;
  SInt32              synthFlags;
  NumVersion          synthVersion;
};
typedef struct SpeechVersionInfo        SpeechVersionInfo;


struct PhonemeInfo {
  SInt16              opcode;
  Str15               phStr;
  Str31               exampleStr;
  SInt16              hiliteStart;
  SInt16              hiliteEnd;
};
typedef struct PhonemeInfo              PhonemeInfo;

struct PhonemeDescriptor {
  SInt16              phonemeCount;
  PhonemeInfo         thePhonemes[1];
};
typedef struct PhonemeDescriptor        PhonemeDescriptor;
struct SpeechXtndData {
  OSType              synthCreator;
  Byte                synthData[2];
};
typedef struct SpeechXtndData           SpeechXtndData;

struct DelimiterInfo {
  Byte                startDelimiter[2];
  Byte                endDelimiter[2];
};
typedef struct DelimiterInfo            DelimiterInfo;
/* Synthesizer Properties */
/*
 *  kSpeechStatusProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechStatusProperty                             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechErrorsProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechErrorsProperty                             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechInputModeProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechInputModeProperty                          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechCharacterModeProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechCharacterModeProperty                      AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechNumberModeProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechNumberModeProperty                         AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechRateProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechRateProperty                               AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechPitchBaseProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechPitchBaseProperty                          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechPitchModProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechPitchModProperty                           AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechVolumeProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechVolumeProperty                             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechSynthesizerInfoProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechSynthesizerInfoProperty                    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechRecentSyncProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechRecentSyncProperty                         AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechPhonemeSymbolsProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechPhonemeSymbolsProperty                     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechCurrentVoiceProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechCurrentVoiceProperty                       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechCommandDelimiterProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechCommandDelimiterProperty                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechResetProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechResetProperty                              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechOutputToFileURLProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechOutputToFileURLProperty                    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechOutputToExtAudioFileProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.6 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechOutputToExtAudioFileProperty               AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
/*
 *  kSpeechOutputToAudioDeviceProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.6 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechOutputToAudioDeviceProperty                AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
/*
 *  kSpeechRefConProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechRefConProperty                             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechTextDoneCallBack
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechTextDoneCallBack                           AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechSpeechDoneCallBack
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechSpeechDoneCallBack                         AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechSyncCallBack
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechSyncCallBack                               AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechPhonemeCallBack
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechPhonemeCallBack                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechErrorCFCallBack
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechErrorCFCallBack                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechWordCFCallBack
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechWordCFCallBack                             AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechPhonemeOptionsProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.6 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechPhonemeOptionsProperty                     AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
/*
 *  kSpeechAudioUnitProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.6 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechAudioUnitProperty                          AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
/*
 *  kSpeechAudioGraphProperty
 *  
 *  Availability:
 *    Mac OS X:         in version 10.6 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechAudioGraphProperty                         AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
/* Speaking Modes*/
/*
 *  kSpeechModeText
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechModeText                                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechModePhoneme
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechModePhoneme                                AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechModeTune
 *  
 *  Availability:
 *    Mac OS X:         in version 10.6 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechModeTune                                   AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
/*
 *  kSpeechModeNormal
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechModeNormal                                 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechModeLiteral
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechModeLiteral                                AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/* Dictionary keys for options parameter in SpeakCFString*/
/*
 *  kSpeechNoEndingProsody
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechNoEndingProsody                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechNoSpeechInterrupt
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechNoSpeechInterrupt                          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechPreflightThenPause
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechPreflightThenPause                         AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/* Dictionary keys returned by kSpeechStatusProperty*/
/*
 *  kSpeechStatusOutputBusy
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechStatusOutputBusy                           AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechStatusOutputPaused
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechStatusOutputPaused                         AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechStatusNumberOfCharactersLeft
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechStatusNumberOfCharactersLeft               AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechStatusPhonemeCode
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechStatusPhonemeCode                          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/* Dictionary keys returned by kSpeechErrorProperty*/
/*
 *  kSpeechErrorCount
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechErrorCount                                 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechErrorOldest
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechErrorOldest                                AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechErrorOldestCharacterOffset
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechErrorOldestCharacterOffset                 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechErrorNewest
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechErrorNewest                                AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechErrorNewestCharacterOffset
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechErrorNewestCharacterOffset                 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/* Dictionary keys returned by kSpeechSynthesizerInfoProperty*/
/*
 *  kSpeechSynthesizerInfoIdentifier
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechSynthesizerInfoIdentifier                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechSynthesizerInfoManufacturer
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechSynthesizerInfoManufacturer                AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechSynthesizerInfoVersion
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechSynthesizerInfoVersion                     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/* Dictionary keys returned by kSpeechPhonemeSymbolsProperty*/
/*
 *  kSpeechPhonemeInfoOpcode
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechPhonemeInfoOpcode                          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechPhonemeInfoSymbol
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechPhonemeInfoSymbol                          AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechPhonemeInfoExample
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechPhonemeInfoExample                         AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechPhonemeInfoHiliteStart
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechPhonemeInfoHiliteStart                     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechPhonemeInfoHiliteEnd
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechPhonemeInfoHiliteEnd                       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/* Dictionary keys returned by kSpeechCurrentVoiceProperty*/
/*
 *  kSpeechVoiceCreator
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechVoiceCreator                               AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechVoiceID
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechVoiceID                                    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/* Dictionary keys returned by kSpeechCommandDelimiterProperty*/
/*
 *  kSpeechCommandPrefix
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechCommandPrefix                              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechCommandSuffix
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechCommandSuffix                              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/* Use with useSpeechDictionary:*/
/*
 *  kSpeechDictionaryLocaleIdentifier
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechDictionaryLocaleIdentifier                 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechDictionaryModificationDate
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechDictionaryModificationDate                 AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechDictionaryPronunciations
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechDictionaryPronunciations                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechDictionaryAbbreviations
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechDictionaryAbbreviations                    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechDictionaryEntrySpelling
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechDictionaryEntrySpelling                    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechDictionaryEntryPhonemes
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechDictionaryEntryPhonemes                    AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/* Error callback user info keys*/
/*
 *  kSpeechErrorCallbackSpokenString
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechErrorCallbackSpokenString                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
/*
 *  kSpeechErrorCallbackCharacterOffset
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef kSpeechErrorCallbackCharacterOffset               AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

typedef CALLBACK_API( void , SpeechTextDoneProcPtr )(SpeechChannel chan, SRefCon refCon, const void **nextBuf, unsigned long *byteLen, SInt32 *controlFlags);
typedef CALLBACK_API( void , SpeechDoneProcPtr )(SpeechChannel chan, SRefCon refCon);
typedef CALLBACK_API( void , SpeechSyncProcPtr )(SpeechChannel chan, SRefCon refCon, OSType syncMessage);
typedef CALLBACK_API( void , SpeechErrorProcPtr )(SpeechChannel chan, SRefCon refCon, OSErr theError, long bytePos);
typedef CALLBACK_API( void , SpeechPhonemeProcPtr )(SpeechChannel chan, SRefCon refCon, SInt16 phonemeOpcode);
typedef CALLBACK_API( void , SpeechWordProcPtr )(SpeechChannel chan, SRefCon refCon, unsigned long wordPos, UInt16 wordLen);
typedef STACK_UPP_TYPE(SpeechTextDoneProcPtr)                   SpeechTextDoneUPP;
typedef STACK_UPP_TYPE(SpeechDoneProcPtr)                       SpeechDoneUPP;
typedef STACK_UPP_TYPE(SpeechSyncProcPtr)                       SpeechSyncUPP;
typedef STACK_UPP_TYPE(SpeechErrorProcPtr)                      SpeechErrorUPP;
typedef STACK_UPP_TYPE(SpeechPhonemeProcPtr)                    SpeechPhonemeUPP;
typedef STACK_UPP_TYPE(SpeechWordProcPtr)                       SpeechWordUPP;
/*
 *  NewSpeechTextDoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SpeechTextDoneUPP
NewSpeechTextDoneUPP(SpeechTextDoneProcPtr userRoutine)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewSpeechDoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SpeechDoneUPP
NewSpeechDoneUPP(SpeechDoneProcPtr userRoutine)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewSpeechSyncUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SpeechSyncUPP
NewSpeechSyncUPP(SpeechSyncProcPtr userRoutine)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewSpeechErrorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SpeechErrorUPP
NewSpeechErrorUPP(SpeechErrorProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewSpeechPhonemeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SpeechPhonemeUPP
NewSpeechPhonemeUPP(SpeechPhonemeProcPtr userRoutine)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewSpeechWordUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern SpeechWordUPP
NewSpeechWordUPP(SpeechWordProcPtr userRoutine)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeSpeechTextDoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeSpeechTextDoneUPP(SpeechTextDoneUPP userUPP)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeSpeechDoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeSpeechDoneUPP(SpeechDoneUPP userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeSpeechSyncUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeSpeechSyncUPP(SpeechSyncUPP userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeSpeechErrorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeSpeechErrorUPP(SpeechErrorUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeSpeechPhonemeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeSpeechPhonemeUPP(SpeechPhonemeUPP userUPP)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeSpeechWordUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeSpeechWordUPP(SpeechWordUPP userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeSpeechTextDoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeSpeechTextDoneUPP(
  SpeechChannel      chan,
  SRefCon            refCon,
  const void **      nextBuf,
  unsigned long *    byteLen,
  SInt32 *           controlFlags,
  SpeechTextDoneUPP  userUPP)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeSpeechDoneUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeSpeechDoneUPP(
  SpeechChannel  chan,
  SRefCon        refCon,
  SpeechDoneUPP  userUPP)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeSpeechSyncUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeSpeechSyncUPP(
  SpeechChannel  chan,
  SRefCon        refCon,
  OSType         syncMessage,
  SpeechSyncUPP  userUPP)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeSpeechErrorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeSpeechErrorUPP(
  SpeechChannel   chan,
  SRefCon         refCon,
  OSErr           theError,
  long            bytePos,
  SpeechErrorUPP  userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeSpeechPhonemeUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeSpeechPhonemeUPP(
  SpeechChannel     chan,
  SRefCon           refCon,
  SInt16            phonemeOpcode,
  SpeechPhonemeUPP  userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeSpeechWordUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeSpeechWordUPP(
  SpeechChannel  chan,
  SRefCon        refCon,
  unsigned long  wordPos,
  UInt16         wordLen,
  SpeechWordUPP  userUPP)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

#if __MACH__
  #ifdef __cplusplus
    inline SpeechTextDoneUPP                                    NewSpeechTextDoneUPP(SpeechTextDoneProcPtr userRoutine) { return userRoutine; }
    inline SpeechDoneUPP                                        NewSpeechDoneUPP(SpeechDoneProcPtr userRoutine) { return userRoutine; }
    inline SpeechSyncUPP                                        NewSpeechSyncUPP(SpeechSyncProcPtr userRoutine) { return userRoutine; }
    inline SpeechErrorUPP                                       NewSpeechErrorUPP(SpeechErrorProcPtr userRoutine) { return userRoutine; }
    inline SpeechPhonemeUPP                                     NewSpeechPhonemeUPP(SpeechPhonemeProcPtr userRoutine) { return userRoutine; }
    inline SpeechWordUPP                                        NewSpeechWordUPP(SpeechWordProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposeSpeechTextDoneUPP(SpeechTextDoneUPP) { }
    inline void                                                 DisposeSpeechDoneUPP(SpeechDoneUPP) { }
    inline void                                                 DisposeSpeechSyncUPP(SpeechSyncUPP) { }
    inline void                                                 DisposeSpeechErrorUPP(SpeechErrorUPP) { }
    inline void                                                 DisposeSpeechPhonemeUPP(SpeechPhonemeUPP) { }
    inline void                                                 DisposeSpeechWordUPP(SpeechWordUPP) { }
    inline void                                                 InvokeSpeechTextDoneUPP(SpeechChannel chan, SRefCon refCon, const void ** nextBuf, unsigned long * byteLen, SInt32 * controlFlags, SpeechTextDoneUPP userUPP) { (*userUPP)(chan, refCon, nextBuf, byteLen, controlFlags); }
    inline void                                                 InvokeSpeechDoneUPP(SpeechChannel chan, SRefCon refCon, SpeechDoneUPP userUPP) { (*userUPP)(chan, refCon); }
    inline void                                                 InvokeSpeechSyncUPP(SpeechChannel chan, SRefCon refCon, OSType syncMessage, SpeechSyncUPP userUPP) { (*userUPP)(chan, refCon, syncMessage); }
    inline void                                                 InvokeSpeechErrorUPP(SpeechChannel chan, SRefCon refCon, OSErr theError, long bytePos, SpeechErrorUPP userUPP) { (*userUPP)(chan, refCon, theError, bytePos); }
    inline void                                                 InvokeSpeechPhonemeUPP(SpeechChannel chan, SRefCon refCon, SInt16 phonemeOpcode, SpeechPhonemeUPP userUPP) { (*userUPP)(chan, refCon, phonemeOpcode); }
    inline void                                                 InvokeSpeechWordUPP(SpeechChannel chan, SRefCon refCon, unsigned long wordPos, UInt16 wordLen, SpeechWordUPP userUPP) { (*userUPP)(chan, refCon, wordPos, wordLen); }
  #else
    #define NewSpeechTextDoneUPP(userRoutine)                   ((SpeechTextDoneUPP)userRoutine)
    #define NewSpeechDoneUPP(userRoutine)                       ((SpeechDoneUPP)userRoutine)
    #define NewSpeechSyncUPP(userRoutine)                       ((SpeechSyncUPP)userRoutine)
    #define NewSpeechErrorUPP(userRoutine)                      ((SpeechErrorUPP)userRoutine)
    #define NewSpeechPhonemeUPP(userRoutine)                    ((SpeechPhonemeUPP)userRoutine)
    #define NewSpeechWordUPP(userRoutine)                       ((SpeechWordUPP)userRoutine)
    #define DisposeSpeechTextDoneUPP(userUPP)
    #define DisposeSpeechDoneUPP(userUPP)
    #define DisposeSpeechSyncUPP(userUPP)
    #define DisposeSpeechErrorUPP(userUPP)
    #define DisposeSpeechPhonemeUPP(userUPP)
    #define DisposeSpeechWordUPP(userUPP)
    #define InvokeSpeechTextDoneUPP(chan, refCon, nextBuf, byteLen, controlFlags, userUPP) (*userUPP)(chan, refCon, nextBuf, byteLen, controlFlags)
    #define InvokeSpeechDoneUPP(chan, refCon, userUPP)          (*userUPP)(chan, refCon)
    #define InvokeSpeechSyncUPP(chan, refCon, syncMessage, userUPP) (*userUPP)(chan, refCon, syncMessage)
    #define InvokeSpeechErrorUPP(chan, refCon, theError, bytePos, userUPP) (*userUPP)(chan, refCon, theError, bytePos)
    #define InvokeSpeechPhonemeUPP(chan, refCon, phonemeOpcode, userUPP) (*userUPP)(chan, refCon, phonemeOpcode)
    #define InvokeSpeechWordUPP(chan, refCon, wordPos, wordLen, userUPP) (*userUPP)(chan, refCon, wordPos, wordLen)
  #endif
#endif

typedef CALLBACK_API( void , SpeechErrorCFProcPtr )(SpeechChannel chan, SRefCon refCon, CFErrorRef theError);
typedef CALLBACK_API( void , SpeechWordCFProcPtr )(SpeechChannel chan, SRefCon refCon, CFStringRef aString, CFRange wordRange);

/*
 *  SpeechManagerVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern NumVersion 
SpeechManagerVersion(void)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MakeVoiceSpec()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
MakeVoiceSpec(
  OSType       creator,
  OSType       id,
  VoiceSpec *  voice)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CountVoices()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
CountVoices(SInt16 * numVoices)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetIndVoice()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
GetIndVoice(
  SInt16       index,
  VoiceSpec *  voice)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetVoiceDescription()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
GetVoiceDescription(
  const VoiceSpec *   voice,
  VoiceDescription *  info,
  long                infoLength)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetVoiceInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
GetVoiceInfo(
  const VoiceSpec *  voice,
  OSType             selector,
  void *             voiceInfo)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewSpeechChannel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
NewSpeechChannel(
  VoiceSpec *      voice,       /* can be NULL */
  SpeechChannel *  chan)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeSpeechChannel()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
DisposeSpeechChannel(SpeechChannel chan)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpeakString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
SpeakString(ConstStr255Param textToBeSpoken)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpeakText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
SpeakText(
  SpeechChannel   chan,
  const void *    textBuf,
  unsigned long   textBytes)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpeakBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
SpeakBuffer(
  SpeechChannel   chan,
  const void *    textBuf,
  unsigned long   textBytes,
  SInt32          controlFlags)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StopSpeech()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
StopSpeech(SpeechChannel chan)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StopSpeechAt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
StopSpeechAt(
  SpeechChannel   chan,
  SInt32          whereToStop)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PauseSpeechAt()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
PauseSpeechAt(
  SpeechChannel   chan,
  SInt32          whereToPause)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ContinueSpeech()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
ContinueSpeech(SpeechChannel chan)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpeechBusy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern SInt16 
SpeechBusy(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpeechBusySystemWide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern SInt16 
SpeechBusySystemWide(void)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetSpeechRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
SetSpeechRate(
  SpeechChannel   chan,
  Fixed           rate)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetSpeechRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
GetSpeechRate(
  SpeechChannel   chan,
  Fixed *         rate)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetSpeechPitch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
SetSpeechPitch(
  SpeechChannel   chan,
  Fixed           pitch)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetSpeechPitch()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
GetSpeechPitch(
  SpeechChannel   chan,
  Fixed *         pitch)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetSpeechInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
SetSpeechInfo(
  SpeechChannel   chan,
  OSType          selector,
  const void *    speechInfo)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetSpeechInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
GetSpeechInfo(
  SpeechChannel   chan,
  OSType          selector,
  void *          speechInfo)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextToPhonemes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
TextToPhonemes(
  SpeechChannel   chan,
  const void *    textBuf,
  unsigned long   textBytes,
  Handle          phonemeBuf,
  long *          phonemeBytes)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  UseDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern OSErr 
UseDictionary(
  SpeechChannel   chan,
  Handle          dictionary)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Replaces SpeakBuffer*/
/*
 *  SpeakCFString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
SpeakCFString(
  SpeechChannel     chan,
  CFStringRef       aString,
  CFDictionaryRef   options)                                  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/* Replaces UseDictionary*/
/*
 *  UseSpeechDictionary()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
UseSpeechDictionary(
  SpeechChannel     chan,
  CFDictionaryRef   speechDictionary)                         AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/* Replaces TextToPhonemes*/
/*
 *  CopyPhonemesFromText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
CopyPhonemesFromText(
  SpeechChannel   chan,
  CFStringRef     text,
  CFStringRef *   phonemes)                                   AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/* Replaces GetSpeechInfo*/
/*
 *  CopySpeechProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
CopySpeechProperty(
  SpeechChannel   chan,
  CFStringRef     property,
  CFTypeRef *     object)                                     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/* Replaces SetSpeechInfo*/
/*
 *  SetSpeechProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
SetSpeechProperty(
  SpeechChannel   chan,
  CFStringRef     property,
  CFTypeRef       object)                                     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/* Support loading and unloading synthesizers and voices from locations other than the standard directories.*/
/*
 *  SpeechSynthesisRegisterModuleURL()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.6 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
SpeechSynthesisRegisterModuleURL(CFURLRef url)                AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;


/*
 *  SpeechSynthesisUnregisterModuleURL()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.6 and later in ApplicationServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
SpeechSynthesisUnregisterModuleURL(CFURLRef url)              AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;




#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __SPEECHSYNTHESIS__ */

