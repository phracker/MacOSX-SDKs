/*
     File:       SpeechSynthesis/SpeechSynthesis.h
 
     Contains:   Speech Interfaces.
 
     Version:    SpeechSynthesis-3.5.19~278
 
     Copyright:  © 1989-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __SPEECHSYNTHESIS__
#define __SPEECHSYNTHESIS__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma options align=mac68k

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
  soWordCallBack                = 'wdcb',
  soSynthExtension              = 'xtnd',
  soSoundOutput                 = 'sndo',
  soOutputToFileWithCFURL       = 'opaf' /* Pass a CFURLRef to write to this file, NULL to generate sound.*/
};


/*------------------------------------------*/
/* Speaking Mode Constants                  */
/*------------------------------------------*/
enum {
  modeText                      = 'TEXT', /* input mode constants             */
  modePhonemes                  = 'PHON',
  modeNormal                    = 'NORM', /* character mode and number mode constants */
  modeLiteral                   = 'LTRL'
};


enum {
  soVoiceDescription            = 'info',
  soVoiceFile                   = 'fref'
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
  long                length;
  VoiceSpec           voice;
  long                version;
  Str63               name;
  Str255              comment;
  short               gender;
  short               age;
  short               script;
  short               language;
  short               region;
  long                reserved[4];
};
typedef struct VoiceDescription         VoiceDescription;


struct VoiceFileInfo {
  FSSpec              fileSpec;
  short               resID;
};
typedef struct VoiceFileInfo            VoiceFileInfo;
struct SpeechStatusInfo {
  Boolean             outputBusy;
  Boolean             outputPaused;
  long                inputBytesLeft;
  short               phonemeCode;
};
typedef struct SpeechStatusInfo         SpeechStatusInfo;


struct SpeechErrorInfo {
  short               count;
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
  long                synthFlags;
  NumVersion          synthVersion;
};
typedef struct SpeechVersionInfo        SpeechVersionInfo;


struct PhonemeInfo {
  short               opcode;
  Str15               phStr;
  Str31               exampleStr;
  short               hiliteStart;
  short               hiliteEnd;
};
typedef struct PhonemeInfo              PhonemeInfo;

struct PhonemeDescriptor {
  short               phonemeCount;
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

typedef CALLBACK_API( void , SpeechTextDoneProcPtr )(SpeechChannel chan, long refCon, const void **nextBuf, unsigned long *byteLen, long *controlFlags);
typedef CALLBACK_API( void , SpeechDoneProcPtr )(SpeechChannel chan, long refCon);
typedef CALLBACK_API( void , SpeechSyncProcPtr )(SpeechChannel chan, long refCon, OSType syncMessage);
typedef CALLBACK_API( void , SpeechErrorProcPtr )(SpeechChannel chan, long refCon, OSErr theError, long bytePos);
typedef CALLBACK_API( void , SpeechPhonemeProcPtr )(SpeechChannel chan, long refCon, short phonemeOpcode);
typedef CALLBACK_API( void , SpeechWordProcPtr )(SpeechChannel chan, long refCon, unsigned long wordPos, unsigned short wordLen);
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
  long               refCon,
  const void **      nextBuf,
  unsigned long *    byteLen,
  long *             controlFlags,
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
  long           refCon,
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
  long           refCon,
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
  long            refCon,
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
  long              refCon,
  short             phonemeOpcode,
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
  SpeechChannel   chan,
  long            refCon,
  unsigned long   wordPos,
  unsigned short  wordLen,
  SpeechWordUPP   userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

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
CountVoices(short * numVoices)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  short        index,
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
  long            controlFlags)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long            whereToStop)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
  long            whereToPause)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


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
extern short 
SpeechBusy(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpeechBusySystemWide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in ApplicationServices.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in SpeechLib 1.0 and later
 */
extern short 
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





#pragma options align=reset

#ifdef __cplusplus
}
#endif

#endif /* __SPEECHSYNTHESIS__ */

