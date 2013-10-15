/*
     File:       QuickTime/Movies.h
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1990-2006 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
/*
    Important note regarding availability macros
    ============================================
    
    QuickTime APIs that were introduced in QuickTime 6.0 and later are tagged with 
    availability macros indicating the first Mac OS X version in which they were 
    *always* available.  Such APIs may also be present on systems running earlier 
    Mac OS X releases when QuickTime updates have been installed.
    
    For example, QTNewDataReferenceFromCFURL was introduced in QuickTime 6.4.
    It is always available on Mac OS X 10.3, which shipped with QuickTime 6.4.
    However, QuickTime 6.4 can also be installed as an update to Mac OS X 10.2.x,
    so QTNewDataReferenceFromCFURL is also available on some systems running 
    Mac OS X 10.2.x.
    
    QuickTime 6.0 / Mac OS X 10.2  :  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER
    QuickTime 6.4 / Mac OS X 10.3  :  AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER
    QuickTime 7.0 / Mac OS X 10.4  :  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER
    QuickTime 7.2 / Mac OS X 10.5  :  AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
    
    As described in /usr/include/AvailabilityMacros.h, you can use the
    MAC_OS_X_VERSION_MIN_REQUIRED macro to weak-link to the APIs that may not be 
    available on the Mac OS X versions your software targets.
*/
#ifndef __MOVIES__
#define __MOVIES__

#ifndef __CARBON__
#include <Carbon/Carbon.h>
#endif

#ifndef __COREAUDIO__
#include <CoreAudio/CoreAudio.h>
#endif

#ifndef __AUDIOUNIT__
#include <AudioUnit/AudioUnit.h>
#endif

#ifndef __IMAGECOMPRESSION__
#include <QuickTime/ImageCompression.h>
#endif

#ifndef __QUICKTIMEERRORS__
#include <QuickTime/QuickTimeErrors.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

/* QuickTime is not available to 64-bit clients */

#if !__LP64__

/* This sets the user defined exportset name i.e. fw_QuickTime_XManchego, available on 10.5 or later, and comment [4486184] */
/* NOTE:  Requires Interfacer-35 or later */
/* <exportset=fw_QuickTime_XManchego> */
/* <exportset=fw_QuickTime_XMaguro> */

/*  "kFix1" is defined in FixMath as "fixed1"  */
/* error codes are in Errors.[haa] */
/* gestalt codes are in Gestalt.[hpa] */
enum {
  MovieFileType                 = 'MooV',
  MovieScrapType                = 'moov'
};

enum {
  MovieResourceType             = 'moov',
  MovieForwardPointerResourceType = 'fore',
  MovieBackwardPointerResourceType = 'back'
};

enum {
  MovieResourceAtomType         = 'moov',
  MovieDataAtomType             = 'mdat',
  FreeAtomType                  = 'free',
  SkipAtomType                  = 'skip',
  WideAtomPlaceholderType       = 'wide'
};

enum {
  MediaHandlerType              = 'mhlr',
  DataHandlerType               = 'dhlr'
};

enum {
  VideoMediaType                = 'vide',
  SoundMediaType                = 'soun',
  TextMediaType                 = 'text',
  BaseMediaType                 = 'gnrc',
  MPEGMediaType                 = 'MPEG',
  MusicMediaType                = 'musi',
  TimeCodeMediaType             = 'tmcd',
  SpriteMediaType               = 'sprt',
  FlashMediaType                = 'flsh',
  MovieMediaType                = 'moov',
  TweenMediaType                = 'twen',
  ThreeDeeMediaType             = 'qd3d',
  SkinMediaType                 = 'skin',
  HandleDataHandlerSubType      = 'hndl',
  PointerDataHandlerSubType     = 'ptr ',
  NullDataHandlerSubType        = 'null',
  ResourceDataHandlerSubType    = 'rsrc',
  URLDataHandlerSubType         = 'url ',
  AliasDataHandlerSubType       = 'alis',
  WiredActionHandlerType        = 'wire',
  kQTQuartzComposerMediaType    = 'qtz ',
  TimeCode64MediaType           = 'tc64'
};

enum {
  VisualMediaCharacteristic     = 'eyes',
  AudioMediaCharacteristic      = 'ears',
  kCharacteristicCanSendVideo   = 'vsnd',
  kCharacteristicProvidesActions = 'actn',
  kCharacteristicNonLinear      = 'nonl',
  kCharacteristicCanStep        = 'step',
  kCharacteristicHasNoDuration  = 'noti',
  kCharacteristicHasSkinData    = 'skin',
  kCharacteristicProvidesKeyFocus = 'keyf',
  kCharacteristicSupportsDisplayOffsets = 'dtdd'
};

enum {
  kUserDataMovieControllerType  = 'ctyp',
  kUserDataName                 = 'name',
  kUserDataTextAlbum            = (long)0xA9616C62/*'©alb' */,
  kUserDataTextArtist           = (long)0xA9415254,
  kUserDataTextAuthor           = (long)0xA9617574/*'©aut' */,
  kUserDataTextChapter          = (long)0xA9636870/*'©chp' */,
  kUserDataTextComment          = (long)0xA9636D74/*'©cmt' */,
  kUserDataTextComposer         = (long)0xA9636F6D/*'©com' */,
  kUserDataTextCopyright        = (long)0xA9637079/*'©cpy' */,
  kUserDataTextCreationDate     = (long)0xA9646179/*'©day' */,
  kUserDataTextDescription      = (long)0xA9646573/*'©des' */,
  kUserDataTextDirector         = (long)0xA9646972/*'©dir' */,
  kUserDataTextDisclaimer       = (long)0xA9646973/*'©dis' */,
  kUserDataTextEncodedBy        = (long)0xA9656E63/*'©enc' */,
  kUserDataTextFullName         = (long)0xA96E616D/*'©nam' */,
  kUserDataTextGenre            = (long)0xA967656E/*'©gen' */,
  kUserDataTextHostComputer     = (long)0xA9687374/*'©hst' */,
  kUserDataTextInformation      = (long)0xA9696E66/*'©inf' */,
  kUserDataTextKeywords         = (long)0xA96B6579/*'©key' */,
  kUserDataTextMake             = (long)0xA96D616B/*'©mak' */,
  kUserDataTextModel            = (long)0xA96D6F64/*'©mod' */,
  kUserDataTextOriginalArtist   = (long)0xA96F7065/*'©ope' */,
  kUserDataTextOriginalFormat   = (long)0xA9666D74/*'©fmt' */,
  kUserDataTextOriginalSource   = (long)0xA9737263/*'©src' */,
  kUserDataTextPerformers       = (long)0xA9707266/*'©prf' */,
  kUserDataTextProducer         = (long)0xA9707264/*'©prd' */,
  kUserDataTextProduct          = (long)0xA9505244,
  kUserDataTextSoftware         = (long)0xA9737772/*'©swr' */,
  kUserDataTextSpecialPlaybackRequirements = (long)0xA9726571/*'©req' */,
  kUserDataTextTrack            = (long)0xA974726B/*'©trk' */,
  kUserDataTextWarning          = (long)0xA977726E/*'©wrn' */,
  kUserDataTextWriter           = (long)0xA9777274/*'©wrt' */,
  kUserDataTextURLLink          = (long)0xA975726C/*'©url' */,
  kUserDataTextEditDate1        = (long)0xA9656431/*'©ed1' */,
  kUserDataAnimatedGIFLoopCount = 'gifc', /* data is big-endian UInt16 */
  kQTAnimatedGIFLoopCountInfinite = 0,
  kUserDataAnimatedGIFBufferingSize = 'gifb' /* data is big-endian UInt32 */
};

enum {
  kUserDataUnicodeBit           = 1L << 7
};

enum {
  DoTheRightThing               = 0
};

/* property types*/
typedef OSType                          QTPropertyClass;
typedef OSType                          QTPropertyID;
typedef OSType                          QTPropertyValueType;
typedef void *                          QTPropertyValuePtr;
typedef const void *                    ConstQTPropertyValuePtr;
typedef struct MovieType**              Movie;
typedef Movie *                         PtrToMovie;
typedef struct TrackType**              Track;
typedef struct MediaType**              Media;
typedef struct UserDataRecord**         UserData;
typedef struct MovieStateRecord**       MovieEditState;
typedef struct TrackStateRecord**       TrackEditState;
typedef struct QTRestrictionSetRecord**  QTRestrictionSet;
typedef struct SpriteWorldRecord*       SpriteWorld;
typedef struct SpriteRecord*            Sprite;
typedef struct QTTweenerRecord*         QTTweener;
struct SampleDescription {
  long                descSize;
  long                dataFormat;
  long                resvd1;
  short               resvd2;
  short               dataRefIndex;
};
typedef struct SampleDescription        SampleDescription;
typedef SampleDescription *             SampleDescriptionPtr;
typedef SampleDescriptionPtr *          SampleDescriptionHandle;
enum {
  kQTNetworkStatusNoNetwork     = -2,
  kQTNetworkStatusUncertain     = -1,
  kQTNetworkStatusNotConnected  = 0,
  kQTNetworkStatusConnected     = 1
};

typedef Handle                          QTAtomContainer;
typedef long                            QTAtom;
typedef long                            QTAtomType;
typedef long                            QTAtomID;
/* QTFloatDouble is the 64-bit IEEE-754 standard*/
typedef Float64                         QTFloatDouble;
/* QTFloatSingle is the 32-bit IEEE-754 standard*/
typedef Float32                         QTFloatSingle;
/*************************
 * SoundDescription
 *************************/
struct SoundDescription {
  long                descSize;               /* total size of SoundDescription including extra data */
  long                dataFormat;             /* sound format */
  long                resvd1;                 /* reserved for apple use. set to zero */
  short               resvd2;                 /* reserved for apple use. set to zero */
  short               dataRefIndex;
  short               version;                /* which version is this data */
  short               revlevel;               /* what version of that codec did this */
  long                vendor;                 /* whose  codec compressed this data */
  short               numChannels;            /* number of channels of sound */
  short               sampleSize;             /* number of bits per sample */
  short               compressionID;          /* unused. set to zero. */
  short               packetSize;             /* unused. set to zero. */
  UnsignedFixed       sampleRate;             /* sample rate sound is captured at */
};
typedef struct SoundDescription         SoundDescription;
typedef SoundDescription *              SoundDescriptionPtr;
typedef SoundDescriptionPtr *           SoundDescriptionHandle;
/* version 1 of the SoundDescription record*/
struct SoundDescriptionV1 {
                                              /* original fields*/
  SoundDescription    desc;
                                              /* fixed compression ratio information*/
  unsigned long       samplesPerPacket;
  unsigned long       bytesPerPacket;
  unsigned long       bytesPerFrame;
  unsigned long       bytesPerSample;
                                              /* additional atom based fields ([long size, long type, some data], repeat)*/
};
typedef struct SoundDescriptionV1       SoundDescriptionV1;
typedef SoundDescriptionV1 *            SoundDescriptionV1Ptr;
typedef SoundDescriptionV1Ptr *         SoundDescriptionV1Handle;
/*
   Definitions for SoundDescriptionV2:
        LPCMFrame = one uncompressed sample in each of the channels (ie. 44100Hz audio has
                44100 LPCMFrames per second, whether it is mono, stereo, 5.1, or whatever).
                In other words, LPCMFrames/audioSampleRate is duration in seconds.
        AudioPacket = For compressed audio, an AudioPacket is the natural compressed access
                unit of that format.  For uncompressed audio, an AudioPacket is simply one
                LPCMFrame.
*/
/* version 2 of the SoundDescription record*/
struct SoundDescriptionV2 {
  SInt32              descSize;               /* total size of SoundDescription including extra data */
  OSType              dataFormat;             /* 'lpcm' for uncompressed, compression type otherwise (eg. 'ima4') */
  SInt32              resvd1;                 /* reserved for apple use. Must be set to zero */
  SInt16              resvd2;                 /* reserved for apple use. Must be set to zero */
  SInt16              dataRefIndex;
  SInt16              version;                /* which version is this data (2 in this case) */
  SInt16              revlevel;               /* what version of that codec did this */
  SInt32              vendor;                 /* whose  codec compressed this data */

  SInt16              always3;                /* Reserved, must be set to 3 */
  SInt16              always16;               /* Reserved, must be set to 16 (0x0010) */
  SInt16              alwaysMinus2;           /* Reserved, must be set to -2 (0xFFFE) */
  SInt16              always0;                /* Reserved, must be set to 0 */
  UInt32              always65536;            /* Reserved, must be set to 65536 (0x00010000) */

  UInt32              sizeOfStructOnly;       /* must be set to sizeof(SoundDescriptionV2), ie. offset to extensions */
  Float64             audioSampleRate;        /* audio frames per second, eg. 44100.0 */
  UInt32              numAudioChannels;       /* any channel assignment info will be in an extension */

  SInt32              always7F000000;         /* Reserved, must be set to 0x7F000000 */
  UInt32              constBitsPerChannel;    /* only set if constant (and only for uncompressed audio) */

  UInt32              formatSpecificFlags;    /* eg. see LPCM flag definitions in CoreAudioTypes.h */
  UInt32              constBytesPerAudioPacket; /* only set if constant */
  UInt32              constLPCMFramesPerAudioPacket; /* only set if constant */

                                              /* additional atom based extensions ([long size, long type, some data], repeat)*/
};
typedef struct SoundDescriptionV2       SoundDescriptionV2;
typedef SoundDescriptionV2 *            SoundDescriptionV2Ptr;
typedef SoundDescriptionV2Ptr *         SoundDescriptionV2Handle;
enum {
  kQTSoundDescriptionKind_Movie_Version1 = 'mvv1',
  kQTSoundDescriptionKind_Movie_Version2 = 'mvv2',
  kQTSoundDescriptionKind_Movie_LowestPossibleVersion = 'mvlo',
  kQTSoundDescriptionKind_Movie_AnyVersion = 'mvny'
};

typedef FourCharCode                    QTSoundDescriptionKind;
/*
 *  QTSoundDescriptionCreate()
 *  
 *  Summary:
 *    QTSoundDescriptionCreate creates a SoundDescription of the
 *    requested kind from an AudioStreamBasicDescription, optional
 *    AudioChannelLayout, and optional magic cookie. 
 *    QTSoundDescriptionCreate allocates the returned
 *    SoundDescriptionHandle, and the caller is responsible for
 *    disposing it.
 *  
 *  Parameters:
 *    
 *    inASBD:
 *      a description of the format
 *    
 *    inLayout:
 *      the audio channel layout (can be NULL if there isn't one)
 *    
 *    inLayoutSize:
 *      size of the audio channel layout (should be 0 if inLayout is
 *      NULL)
 *    
 *    inMagicCookie:
 *      the magic cookie for the decompressor (can be NULL if there
 *      isn't one)
 *    
 *    inMagicCookieSize:
 *      size of the magic cookie (should be 0 if inMagicCookie is NULL)
 *    
 *    inRequestedKind:
 *      the kind of SoundDescription to create
 *    
 *    outSoundDesc:
 *      the resulting SoundDescription.  Caller must dispose with
 *      DisposeHandle.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTSoundDescriptionCreate(
  AudioStreamBasicDescription *  inASBD,
  AudioChannelLayout *           inLayout,
  ByteCount                      inLayoutSize,
  void *                         inMagicCookie,
  ByteCount                      inMagicCookieSize,
  QTSoundDescriptionKind         inRequestedKind,
  SoundDescriptionHandle *       outSoundDesc)                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSoundDescriptionConvert()
 *  
 *  Summary:
 *    Converts from one kind of SoundDescription to another. Note that
 *    fromKind is reserved for future expansion.  You must set it to
 *    kSoundDescriptionKind_Movie_AnyVersion. You can specify (via
 *    toKind) that you would like a specific SoundDescription version,
 *    the lowest possible version (given the constraints of the format
 *    described by fromDescription), or any version of SoundDescription
 *    at all. QTSoundDescriptionConvert allocates the returned
 *    SoundDescriptionHandle and the caller is responsible for
 *    disposing it.
 *  
 *  Parameters:
 *    
 *    fromKind:
 *      reserved, must be set to kSoundDescriptionKind_Movie_AnyVersion
 *    
 *    fromDescription:
 *      input description to be converted
 *    
 *    toKind:
 *      kind of description toDescription will be
 *    
 *    toDescription:
 *      the resulting SoundDescription.  Caller must dispose with
 *      DisposeHandle.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTSoundDescriptionConvert(
  QTSoundDescriptionKind    fromKind,
  SoundDescriptionHandle    fromDescription,
  QTSoundDescriptionKind    toKind,
  SoundDescriptionHandle *  toDescription)                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/* SoundDescription Properties*/

/*
 */
enum {

  /*
   * Properties of a SoundDescription
   */
  kQTPropertyClass_SoundDescription = 'sdes' /* class for SoundDescription properties*/
};


/*
 */
enum {

  /*
   * kQTSoundDescriptionPropertyID_AudioChannelLayout: Value is
   * AudioChannelLayout (Get/Set) Note that this is a variable sized
   * property (since it may contain an array of ChannelDescriptions;
   * see CoreAudioTypes.h).  You must get the size first (by calling
   * QTSoundDescriptionGetPropertyInfo), allocate a struct of that
   * size, and then get the property.
   */
  kQTSoundDescriptionPropertyID_AudioChannelLayout = 'clay',

  /*
   * kQTSoundDescriptionPropertyID_MagicCookie: Value is opaque bytes
   * (Get/Set) Note that this is a variable sized property (since it is
   * completely defined by the codec in question).  You must get the
   * size first (by calling QTSoundDescriptionGetPropertyInfo),
   * allocate a struct of that size, and then get the property.
   */
  kQTSoundDescriptionPropertyID_MagicCookie = 'kuki',

  /*
   * kQTSoundDescriptionPropertyID_AudioStreamBasicDescription: Value
   * is AudioStreamBasicDescription (Get only)
   */
  kQTSoundDescriptionPropertyID_AudioStreamBasicDescription = 'asbd',

  /*
   * kQTSoundDescriptionPropertyID_BitRate: Value is UInt32 in bits per
   * second (Get only) kQTSoundDescriptionPropertyID_BitRate Note that
   * this property may not be available for formats that are inherently
   * very variable in bitrate and highly source-data dependent (such as
   * Apple Lossless).
   */
  kQTSoundDescriptionPropertyID_BitRate = 'brat',

  /*
   * kQTSoundDescriptionPropertyID_UserReadableText: Value is
   * CFStringRef (Get only) QTSoundDescriptionGetProperty does a
   * CFRetain of the returned CFString on behalf of the caller, so the
   * caller is responsible for calling CFRelease on the returned
   * CFString.
   */
  kQTSoundDescriptionPropertyID_UserReadableText = 'text'
};

/*
 *  QTSoundDescriptionGetPropertyInfo()
 *  
 *  Summary:
 *    Gets info about a particular property of a SoundDescription.
 *  
 *  Parameters:
 *    
 *    inDesc:
 *      SoundDescription being interrogated
 *    
 *    inPropClass:
 *      class of property being requested
 *    
 *    inPropID:
 *      ID of property being requested
 *    
 *    outPropType:
 *      type of property is returned here (can be NULL)
 *    
 *    outPropValueSize:
 *      size of property is returned here (can be NULL)
 *    
 *    outPropertyFlags:
 *      property flags are returned here (can be NULL)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTSoundDescriptionGetPropertyInfo(
  SoundDescriptionHandle   inDesc,
  QTPropertyClass          inPropClass,
  QTPropertyID             inPropID,
  QTPropertyValueType *    outPropType,
  ByteCount *              outPropValueSize,
  UInt32 *                 outPropertyFlags)                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSoundDescriptionGetProperty()
 *  
 *  Summary:
 *    Gets a particular property of a SoundDescription.
 *  
 *  Parameters:
 *    
 *    inDesc:
 *      SoundDescription being interrogated
 *    
 *    inPropClass:
 *      class of property being requested
 *    
 *    inPropID:
 *      ID of property being requested
 *    
 *    inPropValueSize:
 *      size of property value buffer
 *    
 *    outPropValueAddress:
 *      pointer to property value buffer
 *    
 *    outPropValueSizeUsed:
 *      actual size of returned property value (can be NULL)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTSoundDescriptionGetProperty(
  SoundDescriptionHandle   inDesc,
  QTPropertyClass          inPropClass,
  QTPropertyID             inPropID,
  ByteCount                inPropValueSize,
  QTPropertyValuePtr       outPropValueAddress,
  ByteCount *              outPropValueSizeUsed)              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSoundDescriptionSetProperty()
 *  
 *  Summary:
 *    Sets a particular property of a SoundDescription.
 *  
 *  Parameters:
 *    
 *    inDesc:
 *      SoundDescription being modified
 *    
 *    inPropClass:
 *      class of property being set
 *    
 *    inPropID:
 *      ID of property being set
 *    
 *    inPropValueSize:
 *      size of property value buffer
 *    
 *    inPropValueAddress:
 *      pointer to property value buffer
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTSoundDescriptionSetProperty(
  SoundDescriptionHandle    inDesc,
  QTPropertyClass           inPropClass,
  QTPropertyID              inPropID,
  ByteCount                 inPropValueSize,
  ConstQTPropertyValuePtr   inPropValueAddress)               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/* Sound Description Extensions*/

/*
 *  AddSoundDescriptionExtension()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
AddSoundDescriptionExtension(
  SoundDescriptionHandle   desc,
  Handle                   extension,
  OSType                   idType)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetSoundDescriptionExtension()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetSoundDescriptionExtension(
  SoundDescriptionHandle   desc,
  Handle *                 extension,
  OSType                   idType)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RemoveSoundDescriptionExtension()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
RemoveSoundDescriptionExtension(
  SoundDescriptionHandle   desc,
  OSType                   idType)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





enum {
  kTx3gSampleType               = 'tx3g',
  kTx3gFontTableAtomType        = 'ftab',
  kTx3gBlinkAtomType            = 'blnk'
};

struct Tx3gRGBAColor {
  unsigned char       red;
  unsigned char       green;
  unsigned char       blue;
  unsigned char       transparency;
};
typedef struct Tx3gRGBAColor            Tx3gRGBAColor;
struct Tx3gStyleRecord {
  unsigned short      startChar;
  unsigned short      endChar;
  unsigned short      fontID;
  unsigned char       fontFace;
  unsigned char       fontSize;
  Tx3gRGBAColor       fontColor;
};
typedef struct Tx3gStyleRecord          Tx3gStyleRecord;
typedef Tx3gStyleRecord *               Tx3gStylePtr;
typedef Tx3gStylePtr *                  Tx3gStyleHandle;
struct Tx3gStyleTableRecord {
  unsigned short      count;
  Tx3gStyleRecord     table[1];
};
typedef struct Tx3gStyleTableRecord     Tx3gStyleTableRecord;
typedef Tx3gStyleTableRecord *          Tx3gStyleTablePtr;
typedef Tx3gStyleTablePtr *             Tx3gStyleTableHandle;
struct Tx3gFontRecord {
  unsigned short      fontID;
  unsigned char       nameLength;
  unsigned char       name[1];
};
typedef struct Tx3gFontRecord           Tx3gFontRecord;
typedef Tx3gFontRecord *                Tx3gFontRecordPtr;
struct Tx3gFontTableRecord {
  unsigned short      entryCount;
  Tx3gFontRecord      fontEntries[1];
};
typedef struct Tx3gFontTableRecord      Tx3gFontTableRecord;
typedef Tx3gFontTableRecord *           Tx3gFontTablePtr;
typedef Tx3gFontTablePtr *              Tx3gFontTableHandle;
struct Tx3gDescription {
  long                descSize;
  long                dataFormat;
  long                resvd1;
  short               resvd2;
  short               dataRefIndex;

  unsigned long       displayFlags;
  char                horizontalJustification;
  char                verticalJustification;
  Tx3gRGBAColor       backgroundColor;
  Rect                defaultTextBox;
  Tx3gStyleRecord     defaultStyle;
};
typedef struct Tx3gDescription          Tx3gDescription;
typedef Tx3gDescription *               Tx3gDescriptionPtr;
typedef Tx3gDescriptionPtr *            Tx3gDescriptionHandle;
struct TextDescription {
  long                descSize;               /* Total size of TextDescription*/
  long                dataFormat;             /* 'text'*/

  long                resvd1;
  short               resvd2;
  short               dataRefIndex;

  long                displayFlags;           /* see enum below for flag values*/

  long                textJustification;      /* Can be: teCenter,teFlush -Default,-Right,-Left*/

  RGBColor            bgColor;                /* Background color*/

  Rect                defaultTextBox;         /* Location to place the text within the track bounds*/
  ScrpSTElement       defaultStyle;           /* Default style (struct defined in TextEdit.h)*/
  char                defaultFontName[1];     /* Font Name (pascal string - struct extended to fit) */
};
typedef struct TextDescription          TextDescription;
typedef TextDescription *               TextDescriptionPtr;
typedef TextDescriptionPtr *            TextDescriptionHandle;
struct SpriteDescription {
  long                descSize;               /* total size of SpriteDescription including extra data */
  long                dataFormat;             /*  */
  long                resvd1;                 /* reserved for apple use */
  short               resvd2;
  short               dataRefIndex;
  long                version;                /* which version is this data */
  OSType              decompressorType;       /* which decompressor to use, 0 for no decompression */
  long                sampleFlags;            /* how to interpret samples */
};
typedef struct SpriteDescription        SpriteDescription;
typedef SpriteDescription *             SpriteDescriptionPtr;
typedef SpriteDescriptionPtr *          SpriteDescriptionHandle;
struct FlashDescription {
  long                descSize;
  long                dataFormat;
  long                resvd1;
  short               resvd2;
  short               dataRefIndex;
  long                version;                /* which version is this data */
  OSType              decompressorType;       /* which decompressor to use, 0 for no decompression */
  long                flags;
};
typedef struct FlashDescription         FlashDescription;
typedef FlashDescription *              FlashDescriptionPtr;
typedef FlashDescriptionPtr *           FlashDescriptionHandle;
struct ThreeDeeDescription {
  long                descSize;               /* total size of ThreeDeeDescription including extra data */
  long                dataFormat;             /*  */
  long                resvd1;                 /* reserved for apple use */
  short               resvd2;
  short               dataRefIndex;
  long                version;                /* which version is this data */
  long                rendererType;           /* which renderer to use, 0 for default */
  long                decompressorType;       /* which decompressor to use, 0 for default */
};
typedef struct ThreeDeeDescription      ThreeDeeDescription;
typedef ThreeDeeDescription *           ThreeDeeDescriptionPtr;
typedef ThreeDeeDescriptionPtr *        ThreeDeeDescriptionHandle;
struct DataReferenceRecord {
  OSType              dataRefType;
  Handle              dataRef;
};
typedef struct DataReferenceRecord      DataReferenceRecord;
typedef DataReferenceRecord *           DataReferencePtr;
/*--------------------------
  Music Sample Description
--------------------------*/
struct MusicDescription {
  long                descSize;
  long                dataFormat;             /* 'musi' */

  long                resvd1;
  short               resvd2;
  short               dataRefIndex;

  long                musicFlags;
  unsigned long       headerData[1];          /* variable size! */

};
typedef struct MusicDescription         MusicDescription;
typedef MusicDescription *              MusicDescriptionPtr;
typedef MusicDescriptionPtr *           MusicDescriptionHandle;
enum {
  kMusicFlagDontPlay2Soft       = 1L << 0,
  kMusicFlagDontSlaveToMovie    = 1L << 1
};


enum {
  dfDontDisplay                 = 1 << 0, /* Don't display the text*/
  dfDontAutoScale               = 1 << 1, /* Don't scale text as track bounds grows or shrinks*/
  dfClipToTextBox               = 1 << 2, /* Clip update to the textbox*/
  dfUseMovieBGColor             = 1 << 3, /* Set text background to movie's background color*/
  dfShrinkTextBoxToFit          = 1 << 4, /* Compute minimum box to fit the sample*/
  dfScrollIn                    = 1 << 5, /* Scroll text in until last of text is in view */
  dfScrollOut                   = 1 << 6, /* Scroll text out until last of text is gone (if both set, scroll in then out)*/
  dfHorizScroll                 = 1 << 7, /* Scroll text horizontally (otherwise it's vertical)*/
  dfReverseScroll               = 1 << 8, /* vert: scroll down rather than up; horiz: scroll backwards (justfication dependent)*/
  dfContinuousScroll            = 1 << 9, /* new samples cause previous samples to scroll out */
  dfFlowHoriz                   = 1 << 10, /* horiz scroll text flows in textbox rather than extend to right */
  dfContinuousKaraoke           = 1 << 11, /* ignore begin offset, hilite everything up to the end offset(karaoke)*/
  dfDropShadow                  = 1 << 12, /* display text with a drop shadow */
  dfAntiAlias                   = 1 << 13, /* attempt to display text anti aliased*/
  dfKeyedText                   = 1 << 14, /* key the text over background*/
  dfInverseHilite               = 1 << 15, /* Use inverse hiliting rather than using hilite color*/
  dfTextColorHilite             = 1 << 16 /* changes text color in place of hiliting. */
};

enum {
  searchTextDontGoToFoundTime   = 1L << 16,
  searchTextDontHiliteFoundText = 1L << 17,
  searchTextOneTrackOnly        = 1L << 18,
  searchTextEnabledTracksOnly   = 1L << 19
};

/*use these with the text property routines*/
enum {
                                        /* set property parameter / get property parameter*/
  kTextTextHandle               = 1,    /* Handle / preallocated Handle*/
  kTextTextPtr                  = 2,    /* Pointer*/
  kTextTEStyle                  = 3,    /* TextStyle * / TextStyle **/
  kTextSelection                = 4,    /* long [2] / long [2]*/
  kTextBackColor                = 5,    /* RGBColor * / RGBColor **/
  kTextForeColor                = 6,    /* RGBColor * / RGBColor **/
  kTextFace                     = 7,    /* long / long **/
  kTextFont                     = 8,    /* long / long **/
  kTextSize                     = 9,    /* long / long **/
  kTextAlignment                = 10,   /* short * / short **/
  kTextHilite                   = 11,   /* hiliteRecord * / hiliteRecord **/
  kTextDropShadow               = 12,   /* dropShadowRecord * / dropShadowRecord **/
  kTextDisplayFlags             = 13,   /* long / long **/
  kTextScroll                   = 14,   /* TimeValue * / TimeValue **/
  kTextRelativeScroll           = 15,   /* Point **/
  kTextHyperTextFace            = 16,   /* hyperTextSetFace * / hyperTextSetFace **/
  kTextHyperTextColor           = 17,   /* hyperTextSetColor * / hyperTextSetColor **/
  kTextKeyEntry                 = 18,   /* short*/
  kTextMouseDown                = 19,   /* Point **/
  kTextTextBox                  = 20,   /* Rect * / Rect **/
  kTextEditState                = 21,   /* short / short **/
  kTextLength                   = 22    /*       / long **/
};

enum {
  k3DMediaRendererEntry         = 'rend',
  k3DMediaRendererName          = 'name',
  k3DMediaRendererCode          = 'rcod'
};

/* progress messages */
enum {
  movieProgressOpen             = 0,
  movieProgressUpdatePercent    = 1,
  movieProgressClose            = 2
};

/* progress operations */
enum {
  progressOpFlatten             = 1,
  progressOpInsertTrackSegment  = 2,
  progressOpInsertMovieSegment  = 3,
  progressOpPaste               = 4,
  progressOpAddMovieSelection   = 5,
  progressOpCopy                = 6,
  progressOpCut                 = 7,
  progressOpLoadMovieIntoRam    = 8,
  progressOpLoadTrackIntoRam    = 9,
  progressOpLoadMediaIntoRam    = 10,
  progressOpImportMovie         = 11,
  progressOpExportMovie         = 12
};

enum {
  mediaQualityDraft             = 0x0000,
  mediaQualityNormal            = 0x0040,
  mediaQualityBetter            = 0x0080,
  mediaQualityBest              = 0x00C0
};

/*****
    Interactive Sprites Support
*****/
/* QTEventRecord flags*/
enum {
  kQTEventPayloadIsQTList       = 1L << 0
};

struct QTEventRecord {
  long                version;
  OSType              eventType;
  Point               where;
  long                flags;
  long                payloadRefcon;          /* from here down only present if version >= 2*/
  long                param1;
  long                param2;
  long                param3;
};
typedef struct QTEventRecord            QTEventRecord;
typedef QTEventRecord *                 QTEventRecordPtr;
struct QTAtomSpec {
  QTAtomContainer     container;
  QTAtom              atom;
};
typedef struct QTAtomSpec               QTAtomSpec;
typedef QTAtomSpec *                    QTAtomSpecPtr;
struct ResolvedQTEventSpec {
  QTAtomSpec          actionAtom;
  Track               targetTrack;
  long                targetRefCon;
};
typedef struct ResolvedQTEventSpec      ResolvedQTEventSpec;
typedef ResolvedQTEventSpec *           ResolvedQTEventSpecPtr;

/* action constants */
enum {
  kActionMovieSetVolume         = 1024, /* (short movieVolume) */
  kActionMovieSetRate           = 1025, /* (Fixed rate) */
  kActionMovieSetLoopingFlags   = 1026, /* (long loopingFlags) */
  kActionMovieGoToTime          = 1027, /* (TimeValue time) */
  kActionMovieGoToTimeByName    = 1028, /* (Str255 timeName) */
  kActionMovieGoToBeginning     = 1029, /* no params */
  kActionMovieGoToEnd           = 1030, /* no params */
  kActionMovieStepForward       = 1031, /* no params */
  kActionMovieStepBackward      = 1032, /* no params */
  kActionMovieSetSelection      = 1033, /* (TimeValue startTime, TimeValue endTime) */
  kActionMovieSetSelectionByName = 1034, /* (Str255 startTimeName, Str255 endTimeName) */
  kActionMoviePlaySelection     = 1035, /* (Boolean selectionOnly) */
  kActionMovieSetLanguage       = 1036, /* (long language) */
  kActionMovieChanged           = 1037, /* no params */
  kActionMovieRestartAtTime     = 1038, /* (TimeValue startTime, Fixed rate) */
  kActionMovieGotoNextChapter   = 1039, /* no params */
  kActionMovieGotoPreviousChapter = 1040, /* no params */
  kActionMovieGotoFirstChapter  = 1041, /* no params */
  kActionMovieGotoLastChapter   = 1042, /* no params */
  kActionMovieGotoChapterByIndex = 1043, /* ( short index ) */
  kActionMovieSetScale          = 1044, /* (Fixed xScale, Fixed yScale) */
  kActionTrackSetVolume         = 2048, /* (short volume) */
  kActionTrackSetBalance        = 2049, /* (short balance) */
  kActionTrackSetEnabled        = 2050, /* (Boolean enabled) */
  kActionTrackSetMatrix         = 2051, /* (MatrixRecord matrix) */
  kActionTrackSetLayer          = 2052, /* (short layer) */
  kActionTrackSetClip           = 2053, /* (RgnHandle clip) */
  kActionTrackSetCursor         = 2054, /* (QTATomID cursorID) */
  kActionTrackSetGraphicsMode   = 2055, /* (ModifierTrackGraphicsModeRecord graphicsMode) */
  kActionTrackSetIdleFrequency  = 2056, /* (long frequency) */
  kActionTrackSetBassTreble     = 2057, /* (short base, short treble) */
  kActionSpriteSetMatrix        = 3072, /* (MatrixRecord matrix) */
  kActionSpriteSetImageIndex    = 3073, /* (short imageIndex) */
  kActionSpriteSetVisible       = 3074, /* (short visible) */
  kActionSpriteSetLayer         = 3075, /* (short layer) */
  kActionSpriteSetGraphicsMode  = 3076, /* (ModifierTrackGraphicsModeRecord graphicsMode) */
  kActionSpritePassMouseToCodec = 3078, /* no params */
  kActionSpriteClickOnCodec     = 3079, /* Point localLoc */
  kActionSpriteTranslate        = 3080, /* (Fixed x, Fixed y, Boolean isAbsolute) */
  kActionSpriteScale            = 3081, /* (Fixed xScale, Fixed yScale) */
  kActionSpriteRotate           = 3082, /* (Fixed degrees) */
  kActionSpriteStretch          = 3083, /* (Fixed p1x, Fixed p1y, Fixed p2x, Fixed p2y, Fixed p3x, Fixed p3y, Fixed p4x, Fixed p4y) */
  kActionSpriteSetCanBeHitTested = 3094, /* (short canBeHitTested) */
  kActionQTVRSetPanAngle        = 4096, /* (float panAngle) */
  kActionQTVRSetTiltAngle       = 4097, /* (float tiltAngle) */
  kActionQTVRSetFieldOfView     = 4098, /* (float fieldOfView) */
  kActionQTVRShowDefaultView    = 4099, /* no params */
  kActionQTVRGoToNodeID         = 4100, /* (UInt32 nodeID) */
  kActionQTVREnableHotSpot      = 4101, /* long ID, Boolean enable */
  kActionQTVRShowHotSpots       = 4102, /* Boolean show */
  kActionQTVRTranslateObject    = 4103, /* float xMove, float yMove */
  kActionQTVRSetViewState       = 4109, /* long viewStateType, short state */
  kActionMusicPlayNote          = 5120, /* (long sampleDescIndex, long partNumber, long delay, long pitch, long velocity, long duration) */
  kActionMusicSetController     = 5121, /* (long sampleDescIndex, long partNumber, long delay, long controller, long value) */
  kActionCase                   = 6144, /* [(CaseStatementActionAtoms)] */
  kActionWhile                  = 6145, /* [(WhileStatementActionAtoms)] */
  kActionGoToURL                = 6146, /* (C string urlLink) */
  kActionSendQTEventToSprite    = 6147, /* ([(SpriteTargetAtoms)], QTEventRecord theEvent) */
  kActionDebugStr               = 6148, /* (Str255 theString) */
  kActionPushCurrentTime        = 6149, /* no params */
  kActionPushCurrentTimeWithLabel = 6150, /* (Str255 theLabel) */
  kActionPopAndGotoTopTime      = 6151, /* no params */
  kActionPopAndGotoLabeledTime  = 6152, /* (Str255 theLabel) */
  kActionStatusString           = 6153, /* (C string theString, long stringTypeFlags) */
  kActionSendQTEventToTrackObject = 6154, /* ([(TrackObjectTargetAtoms)], QTEventRecord theEvent) */
  kActionAddChannelSubscription = 6155, /* (Str255 channelName, C string channelsURL, C string channelsPictureURL) */
  kActionRemoveChannelSubscription = 6156, /* (C string channelsURL) */
  kActionOpenCustomActionHandler = 6157, /* (long handlerID, ComponentDescription handlerDesc) */
  kActionDoScript               = 6158, /* (long scriptTypeFlags, CString command, CString arguments) */
  kActionDoCompressedActions    = 6159, /* (compressed QTAtomContainer prefixed with eight bytes: long compressorType, long decompressedSize) */
  kActionSendAppMessage         = 6160, /* (long appMessageID) */
  kActionLoadComponent          = 6161, /* (ComponentDescription handlerDesc) */
  kActionSetFocus               = 6162, /* [(TargetAtoms theObject)] */
  kActionDontPassKeyEvent       = 6163, /* no params */
  kActionSetRandomSeed          = 6164, /* long randomSeed */
  kActionSpriteTrackSetVariable = 7168, /* (QTAtomID variableID, float value) */
  kActionSpriteTrackNewSprite   = 7169, /* (QTAtomID spriteID, short imageIndex, MatrixRecord *matrix, short visible, short layer, ModifierTrackGraphicsModeRecord *graphicsMode, QTAtomID actionHandlingSpriteID) */
  kActionSpriteTrackDisposeSprite = 7170, /* (QTAtomID spriteID) */
  kActionSpriteTrackSetVariableToString = 7171, /* (QTAtomID variableID, C string value) */
  kActionSpriteTrackConcatVariables = 7172, /* (QTAtomID firstVariableID, QTAtomID secondVariableID, QTAtomID resultVariableID ) */
  kActionSpriteTrackSetVariableToMovieURL = 7173, /* (QTAtomID variableID, < optional: [(MovieTargetAtoms)] > ) */
  kActionSpriteTrackSetVariableToMovieBaseURL = 7174, /* (QTAtomID variableID, < optional: [(MovieTargetAtoms)] > ) */
  kActionSpriteTrackSetAllSpritesHitTestingMode = 7181,
  kActionSpriteTrackNewImage    = 7182, /* (C string imageURL, QTAtomID desiredID) */
  kActionSpriteTrackDisposeImage = 7183, /* (short imageIndex) */
  kActionApplicationNumberAndString = 8192, /* (long aNumber, Str255 aString ) */
  kActionQD3DNamedObjectTranslateTo = 9216, /* (Fixed x, Fixed y, Fixed z ) */
  kActionQD3DNamedObjectScaleTo = 9217, /* (Fixed xScale, Fixed yScale, Fixed zScale ) */
  kActionQD3DNamedObjectRotateTo = 9218, /* (Fixed xDegrees, Fixed yDegrees, Fixed zDegrees ) */
  kActionFlashTrackSetPan       = 10240, /* (short xPercent, short yPercent ) */
  kActionFlashTrackSetZoom      = 10241, /* (short zoomFactor ) */
  kActionFlashTrackSetZoomRect  = 10242, /* (long left, long top, long right, long bottom ) */
  kActionFlashTrackGotoFrameNumber = 10243, /* (long frameNumber ) */
  kActionFlashTrackGotoFrameLabel = 10244, /* (C string frameLabel ) */
  kActionFlashTrackSetFlashVariable = 10245, /* (C string path, C string name, C string value, Boolean updateFocus) */
  kActionFlashTrackDoButtonActions = 10246, /* (C string path, long buttonID, long transition) */
  kActionMovieTrackAddChildMovie = 11264, /* (QTAtomID childMovieID, C string childMovieURL) */
  kActionMovieTrackLoadChildMovie = 11265, /* (QTAtomID childMovieID) */
  kActionMovieTrackLoadChildMovieWithQTListParams = 11266, /* (QTAtomID childMovieID, C string qtlistXML) */
  kActionTextTrackPasteText     = 12288, /* (C string theText, long startSelection, long endSelection ) */
  kActionTextTrackSetTextBox    = 12291, /* (short left, short top, short right, short bottom) */
  kActionTextTrackSetTextStyle  = 12292, /* (Handle textStyle) */
  kActionTextTrackSetSelection  = 12293, /* (long startSelection, long endSelection ) */
  kActionTextTrackSetBackgroundColor = 12294, /* (ModifierTrackGraphicsModeRecord backgroundColor ) */
  kActionTextTrackSetForegroundColor = 12295, /* (ModifierTrackGraphicsModeRecord foregroundColor ) */
  kActionTextTrackSetFace       = 12296, /* (long fontFace ) */
  kActionTextTrackSetFont       = 12297, /* (long fontID ) */
  kActionTextTrackSetSize       = 12298, /* (long fontSize ) */
  kActionTextTrackSetAlignment  = 12299, /* (short alignment ) */
  kActionTextTrackSetHilite     = 12300, /* (long startHighlight, long endHighlight, ModifierTrackGraphicsModeRecord highlightColor ) */
  kActionTextTrackSetDropShadow = 12301, /* (Point dropShadow, short transparency ) */
  kActionTextTrackSetDisplayFlags = 12302, /* (long flags ) */
  kActionTextTrackSetScroll     = 12303, /* (long delay ) */
  kActionTextTrackRelativeScroll = 12304, /* (short deltaX, short deltaY ) */
  kActionTextTrackFindText      = 12305, /* (long flags, Str255 theText, ModifierTrackGraphicsModeRecord highlightColor ) */
  kActionTextTrackSetHyperTextFace = 12306, /* (short index, long fontFace ) */
  kActionTextTrackSetHyperTextColor = 12307, /* (short index, ModifierTrackGraphicsModeRecord highlightColor ) */
  kActionTextTrackKeyEntry      = 12308, /* (short character ) */
  kActionTextTrackMouseDown     = 12309, /* no params */
  kActionTextTrackSetEditable   = 12310, /* (short editState) */
  kActionListAddElement         = 13312, /* (C string parentPath, long atIndex, C string newElementName) */
  kActionListRemoveElements     = 13313, /* (C string parentPath, long startIndex, long endIndex) */
  kActionListSetElementValue    = 13314, /* (C string elementPath, C string valueString) */
  kActionListPasteFromXML       = 13315, /* (C string xml, C string targetParentPath, long startIndex) */
  kActionListSetMatchingFromXML = 13316, /* (C string xml, C string targetParentPath) */
  kActionListSetFromURL         = 13317, /* (C string url, C string targetParentPath ) */
  kActionListExchangeLists      = 13318, /* (C string url, C string parentPath) */
  kActionListServerQuery        = 13319, /* (C string url, C string keyValuePairs, long flags, C string parentPath) */
  kActionListAddAttribute       = 13320, /* (C string elementPath, long atIndex, C string newAttributeName) */
  kActionListRemoveAttributes   = 13321, /* (C string elementPath, long startIndex, long endIndex) */
  kActionListSetAttributeValue  = 13322 /* (C string elementPath, C string attributeName, C string valueString) */
};


enum {
  kOperandExpression            = 1,
  kOperandConstant              = 2,
  kOperandSubscribedToChannel   = 3,    /* C string channelsURL */
  kOperandUniqueCustomActionHandlerID = 4,
  kOperandCustomActionHandlerIDIsOpen = 5, /* long ID */
  kOperandConnectionSpeed       = 6,
  kOperandGMTDay                = 7,
  kOperandGMTMonth              = 8,
  kOperandGMTYear               = 9,
  kOperandGMTHours              = 10,
  kOperandGMTMinutes            = 11,
  kOperandGMTSeconds            = 12,
  kOperandLocalDay              = 13,
  kOperandLocalMonth            = 14,
  kOperandLocalYear             = 15,
  kOperandLocalHours            = 16,
  kOperandLocalMinutes          = 17,
  kOperandLocalSeconds          = 18,
  kOperandRegisteredForQuickTimePro = 19,
  kOperandPlatformRunningOn     = 20,
  kOperandQuickTimeVersion      = 21,
  kOperandComponentVersion      = 22,   /* C string type, C string subType, C string manufacturer */
  kOperandOriginalHandlerRefcon = 23,
  kOperandTicks                 = 24,
  kOperandMaxLoadedTimeInMovie  = 25,
  kOperandEventParameter        = 26,   /* short index */
  kOperandFreeMemory            = 27,
  kOperandNetworkStatus         = 28,
  kOperandQuickTimeVersionRegistered = 29, /* long version */
  kOperandSystemVersion         = 30,
  kOperandMovieVolume           = 1024,
  kOperandMovieRate             = 1025,
  kOperandMovieIsLooping        = 1026,
  kOperandMovieLoopIsPalindrome = 1027,
  kOperandMovieTime             = 1028,
  kOperandMovieDuration         = 1029,
  kOperandMovieTimeScale        = 1030,
  kOperandMovieWidth            = 1031,
  kOperandMovieHeight           = 1032,
  kOperandMovieLoadState        = 1033,
  kOperandMovieTrackCount       = 1034,
  kOperandMovieIsActive         = 1035,
  kOperandMovieName             = 1036,
  kOperandMovieID               = 1037,
  kOperandMovieChapterCount     = 1038,
  kOperandMovieChapterIndex     = 1039,
  kOperandMovieChapterName      = 1040,
  kOperandMovieChapterNameByIndex = 1041, /* ( short index ) */
  kOperandMovieChapterIndexByName = 1042, /* (c string name)  */
  kOperandMovieAnnotation       = 1043, /* (c string requested, long flags) */
  kOperandMovieConnectionFlags  = 1044,
  kOperandMovieConnectionString = 1045,
  kOperandTrackVolume           = 2048,
  kOperandTrackBalance          = 2049,
  kOperandTrackEnabled          = 2050,
  kOperandTrackLayer            = 2051,
  kOperandTrackWidth            = 2052,
  kOperandTrackHeight           = 2053,
  kOperandTrackDuration         = 2054,
  kOperandTrackName             = 2055,
  kOperandTrackID               = 2056,
  kOperandTrackIdleFrequency    = 2057,
  kOperandTrackBass             = 2058,
  kOperandTrackTreble           = 2059,
  kOperandSpriteBoundsLeft      = 3072,
  kOperandSpriteBoundsTop       = 3073,
  kOperandSpriteBoundsRight     = 3074,
  kOperandSpriteBoundsBottom    = 3075,
  kOperandSpriteImageIndex      = 3076,
  kOperandSpriteVisible         = 3077,
  kOperandSpriteLayer           = 3078,
  kOperandSpriteTrackVariable   = 3079, /* [QTAtomID variableID] */
  kOperandSpriteTrackNumSprites = 3080,
  kOperandSpriteTrackNumImages  = 3081,
  kOperandSpriteID              = 3082,
  kOperandSpriteIndex           = 3083,
  kOperandSpriteFirstCornerX    = 3084,
  kOperandSpriteFirstCornerY    = 3085,
  kOperandSpriteSecondCornerX   = 3086,
  kOperandSpriteSecondCornerY   = 3087,
  kOperandSpriteThirdCornerX    = 3088,
  kOperandSpriteThirdCornerY    = 3089,
  kOperandSpriteFourthCornerX   = 3090,
  kOperandSpriteFourthCornerY   = 3091,
  kOperandSpriteImageRegistrationPointX = 3092,
  kOperandSpriteImageRegistrationPointY = 3093,
  kOperandSpriteTrackSpriteIDAtPoint = 3094, /* short x, short y */
  kOperandSpriteName            = 3095,
  kOperandSpriteCanBeHitTested  = 3105, /* short */
  kOperandSpriteTrackAllSpritesHitTestingMode = 3106,
  kOperandSpriteTrackImageIDByIndex = 3107, /* short imageIndex */
  kOperandSpriteTrackImageIndexByID = 3108, /* QTAtomID */
  kOperandQTVRPanAngle          = 4096,
  kOperandQTVRTiltAngle         = 4097,
  kOperandQTVRFieldOfView       = 4098,
  kOperandQTVRNodeID            = 4099,
  kOperandQTVRHotSpotsVisible   = 4100,
  kOperandQTVRViewCenterH       = 4101,
  kOperandQTVRViewCenterV       = 4102,
  kOperandQTVRViewStateCount    = 4103,
  kOperandQTVRViewState         = 4104, /* long viewStateType */
  kOperandMouseLocalHLoc        = 5120, /* [TargetAtoms aTrack] */
  kOperandMouseLocalVLoc        = 5121, /* [TargetAtoms aTrack] */
  kOperandKeyIsDown             = 5122, /* [short modKeys, char asciiValue] */
  kOperandRandom                = 5123, /* [short min, short max] */
  kOperandCanHaveFocus          = 5124, /* [(TargetAtoms theObject)] */
  kOperandHasFocus              = 5125, /* [(TargetAtoms theObject)] */
  kOperandTextTrackEditable     = 6144,
  kOperandTextTrackCopyText     = 6145, /* long startSelection, long endSelection */
  kOperandTextTrackStartSelection = 6146,
  kOperandTextTrackEndSelection = 6147,
  kOperandTextTrackTextBoxLeft  = 6148,
  kOperandTextTrackTextBoxTop   = 6149,
  kOperandTextTrackTextBoxRight = 6150,
  kOperandTextTrackTextBoxBottom = 6151,
  kOperandTextTrackTextLength   = 6152,
  kOperandListCountElements     = 7168, /* (C string parentPath) */
  kOperandListGetElementPathByIndex = 7169, /* (C string parentPath, long index) */
  kOperandListGetElementValue   = 7170, /* (C string elementPath) */
  kOperandListCopyToXML         = 7171, /* (C string parentPath, long startIndex, long endIndex) */
  kOperandListCountAttributes   = 7172, /* (C string elementPath) */
  kOperandListGetAttributeNameByIndex = 7173, /* (C string elementPath, long index) */
  kOperandListGetAttributeValue = 7174, /* (C string elementPath, C string attributeName) */
  kOperandSin                   = 8192, /* float x    */
  kOperandCos                   = 8193, /* float x    */
  kOperandTan                   = 8194, /* float x    */
  kOperandATan                  = 8195, /* float x    */
  kOperandATan2                 = 8196, /* float y, float x   */
  kOperandDegreesToRadians      = 8197, /* float x */
  kOperandRadiansToDegrees      = 8198, /* float x */
  kOperandSquareRoot            = 8199, /* float x */
  kOperandExponent              = 8200, /* float x */
  kOperandLog                   = 8201, /* float x */
  kOperandFlashTrackVariable    = 9216, /* [CString path, CString name] */
  kOperandStringLength          = 10240, /* (C string text) */
  kOperandStringCompare         = 10241, /* (C string aText, C string bText, Boolean caseSensitive, Boolan diacSensitive) */
  kOperandStringSubString       = 10242, /* (C string text, long offset, long length) */
  kOperandStringConcat          = 10243 /* (C string aText, C string bText) */
};

enum {
  kFirstMovieAction             = kActionMovieSetVolume,
  kLastMovieAction              = kActionMovieSetScale,
  kFirstTrackAction             = kActionTrackSetVolume,
  kLastTrackAction              = kActionTrackSetBassTreble,
  kFirstSpriteAction            = kActionSpriteSetMatrix,
  kLastSpriteAction             = kActionSpriteSetCanBeHitTested,
  kFirstQTVRAction              = kActionQTVRSetPanAngle,
  kLastQTVRAction               = kActionQTVRSetViewState,
  kFirstMusicAction             = kActionMusicPlayNote,
  kLastMusicAction              = kActionMusicSetController,
  kFirstSystemAction            = kActionCase,
  kLastSystemAction             = kActionSetRandomSeed,
  kFirstSpriteTrackAction       = kActionSpriteTrackSetVariable,
  kLastSpriteTrackAction        = kActionSpriteTrackDisposeImage,
  kFirstApplicationAction       = kActionApplicationNumberAndString,
  kLastApplicationAction        = kActionApplicationNumberAndString,
  kFirstQD3DNamedObjectAction   = kActionQD3DNamedObjectTranslateTo,
  kLastQD3DNamedObjectAction    = kActionQD3DNamedObjectRotateTo,
  kFirstFlashTrackAction        = kActionFlashTrackSetPan,
  kLastFlashTrackAction         = kActionFlashTrackDoButtonActions,
  kFirstMovieTrackAction        = kActionMovieTrackAddChildMovie,
  kLastMovieTrackAction         = kActionMovieTrackLoadChildMovieWithQTListParams,
  kFirstTextTrackAction         = kActionTextTrackPasteText,
  kLastTextTrackAction          = kActionTextTrackSetEditable,
  kFirstMultiTargetAction       = kActionListAddElement,
  kLastMultiTargetAction        = kActionListSetAttributeValue,
  kFirstAction                  = kFirstMovieAction,
  kLastAction                   = kLastMultiTargetAction
};

/* target atom types*/
enum {
  kTargetMovie                  = 'moov', /* no data */
  kTargetMovieName              = 'mona', /* (PString movieName) */
  kTargetMovieID                = 'moid', /* (long movieID) */
  kTargetRootMovie              = 'moro', /* no data */
  kTargetParentMovie            = 'mopa', /* no data */
  kTargetChildMovieTrackName    = 'motn', /* (PString childMovieTrackName) */
  kTargetChildMovieTrackID      = 'moti', /* (long childMovieTrackID) */
  kTargetChildMovieTrackIndex   = 'motx', /* (long childMovieTrackIndex) */
  kTargetChildMovieMovieName    = 'momn', /* (PString childMovieName) */
  kTargetChildMovieMovieID      = 'momi', /* (long childMovieID) */
  kTargetTrackName              = 'trna', /* (PString trackName) */
  kTargetTrackID                = 'trid', /* (long trackID) */
  kTargetTrackType              = 'trty', /* (OSType trackType) */
  kTargetTrackIndex             = 'trin', /* (long trackIndex) */
  kTargetSpriteName             = 'spna', /* (PString spriteName) */
  kTargetSpriteID               = 'spid', /* (QTAtomID spriteID) */
  kTargetSpriteIndex            = 'spin', /* (short spriteIndex) */
  kTargetQD3DNamedObjectName    = 'nana', /* (CString objectName) */
  kTargetCurrentQTEventParams   = 'evpa' /* no data */
};

/* action container atom types*/
enum {
  kQTEventType                  = 'evnt',
  kAction                       = 'actn',
  kWhichAction                  = 'whic',
  kActionParameter              = 'parm',
  kActionTarget                 = 'targ',
  kActionFlags                  = 'flag',
  kActionParameterMinValue      = 'minv',
  kActionParameterMaxValue      = 'maxv',
  kActionListAtomType           = 'list',
  kExpressionContainerAtomType  = 'expr',
  kConditionalAtomType          = 'test',
  kOperatorAtomType             = 'oper',
  kOperandAtomType              = 'oprn',
  kCommentAtomType              = 'why ',
  kCustomActionHandler          = 'cust',
  kCustomHandlerID              = 'id  ',
  kCustomHandlerDesc            = 'desc',
  kQTEventRecordAtomType        = 'erec'
};

/* QTEvent types */
enum {
  kQTEventMouseClick            = 'clik',
  kQTEventMouseClickEnd         = 'cend',
  kQTEventMouseClickEndTriggerButton = 'trig',
  kQTEventMouseEnter            = 'entr',
  kQTEventMouseExit             = 'exit',
  kQTEventMouseMoved            = 'move',
  kQTEventFrameLoaded           = 'fram',
  kQTEventIdle                  = 'idle',
  kQTEventKey                   = 'key ', /* qtevent.param1 = key, qtevent.param2 = modifiers, qtEvent.param3 = scanCode */
  kQTEventMovieLoaded           = 'load',
  kQTEventRequestToModifyMovie  = 'reqm',
  kQTEventListReceived          = 'list',
  kQTEventKeyUp                 = 'keyU' /* qtevent.param1 = key, qtevent.param2 = modifiers, qtEvent.param3 = scanCode */
};

/* flags for the kActionFlags atom */
enum {
  kActionFlagActionIsDelta      = 1L << 1,
  kActionFlagParameterWrapsAround = 1L << 2,
  kActionFlagActionIsToggle     = 1L << 3
};

/* flags for stringTypeFlags field of the QTStatusStringRecord */
enum {
  kStatusStringIsURLLink        = 1L << 1,
  kStatusStringIsStreamingStatus = 1L << 2,
  kStatusHasCodeNumber          = 1L << 3, /* high 16 bits of stringTypeFlags is error code number*/
  kStatusIsError                = 1L << 4
};

/* flags for scriptTypeFlags field of the QTDoScriptRecord*/
enum {
  kScriptIsUnknownType          = 1L << 0,
  kScriptIsJavaScript           = 1L << 1,
  kScriptIsLingoEvent           = 1L << 2,
  kScriptIsVBEvent              = 1L << 3,
  kScriptIsProjectorCommand     = 1L << 4,
  kScriptIsAppleScript          = 1L << 5
};

/* flags for CheckQuickTimeRegistration routine*/
enum {
  kQTRegistrationDialogTimeOutFlag = 1 << 0,
  kQTRegistrationDialogShowDialog = 1 << 1,
  kQTRegistrationDialogForceDialog = 1 << 2
};

/* constants for kOperatorAtomType IDs (operator types)*/
enum {
  kOperatorAdd                  = 'add ',
  kOperatorSubtract             = 'sub ',
  kOperatorMultiply             = 'mult',
  kOperatorDivide               = 'div ',
  kOperatorOr                   = 'or  ',
  kOperatorAnd                  = 'and ',
  kOperatorNot                  = 'not ',
  kOperatorLessThan             = '<   ',
  kOperatorLessThanEqualTo      = '<=  ',
  kOperatorEqualTo              = '=   ',
  kOperatorNotEqualTo           = '!=  ',
  kOperatorGreaterThan          = '>   ',
  kOperatorGreaterThanEqualTo   = '>=  ',
  kOperatorModulo               = 'mod ',
  kOperatorIntegerDivide        = 'idiv',
  kOperatorAbsoluteValue        = 'abs ',
  kOperatorNegate               = 'neg '
};

/* constants for kOperandPlatformRunningOn*/
enum {
  kPlatformMacintosh            = 1,
  kPlatformWindows              = 2
};

/* flags for kOperandSystemVersion*/
enum {
  kSystemIsWindows9x            = 0x00010000,
  kSystemIsWindowsNT            = 0x00020000,
  kSystemIsClassicBlueBox       = 0x00040000
};

/* constants for MediaPropertiesAtom*/
enum {
  kMediaPropertyNonLinearAtomType = 'nonl',
  kMediaPropertyHasActions      = 105
};


/* TimeBase and TimeRecord moved to MacTypes.h */
typedef UInt32 TimeBaseFlags;
enum {
  loopTimeBase                  = 1,
  palindromeLoopTimeBase        = 2,
  maintainTimeBaseZero          = 4
};

typedef struct QTCallBackHeader*        QTCallBack;
/* CallBack equates */
typedef UInt16 QTCallBackFlags;
enum {
  triggerTimeFwd                = 0x0001, /* when curTime exceeds triggerTime going forward */
  triggerTimeBwd                = 0x0002, /* when curTime exceeds triggerTime going backwards */
  triggerTimeEither             = 0x0003, /* when curTime exceeds triggerTime going either direction */
  triggerRateLT                 = 0x0004, /* when rate changes to less than trigger value */
  triggerRateGT                 = 0x0008, /* when rate changes to greater than trigger value */
  triggerRateEqual              = 0x0010, /* when rate changes to equal trigger value */
  triggerRateLTE                = triggerRateLT | triggerRateEqual,
  triggerRateGTE                = triggerRateGT | triggerRateEqual,
  triggerRateNotEqual           = triggerRateGT | triggerRateEqual | triggerRateLT,
  triggerRateChange             = 0,
  triggerAtStart                = 0x0001,
  triggerAtStop                 = 0x0002
};

typedef UInt32 TimeBaseStatus;
enum {
  timeBaseBeforeStartTime       = 1,
  timeBaseAfterStopTime         = 2,
  timeBaseRateChanging          = 4
};


typedef UInt16 QTCallBackType;
enum {
  callBackAtTime                = 1,
  callBackAtRate                = 2,
  callBackAtTimeJump            = 3,
  callBackAtExtremes            = 4,
  callBackAtTimeBaseDisposed    = 5,
  callBackAtInterrupt           = 0x8000,
  callBackAtDeferredTask        = 0x4000
};

typedef CALLBACK_API( void , QTCallBackProcPtr )(QTCallBack cb, long refCon);
typedef STACK_UPP_TYPE(QTCallBackProcPtr)                       QTCallBackUPP;
enum {
  qtcbNeedsRateChanges          = 1,    /* wants to know about rate changes */
  qtcbNeedsTimeChanges          = 2,    /* wants to know about time changes */
  qtcbNeedsStartStopChanges     = 4     /* wants to know when TimeBase start/stop is changed*/
};

struct QTCallBackOpaqueHeader {
  long                callBackFlags;
  long                reserved1;
  SInt8               qtPrivate[52];
};
typedef struct QTCallBackOpaqueHeader   QTCallBackOpaqueHeader;
typedef CALLBACK_API( void , QTSyncTaskProcPtr )(void * task);
typedef STACK_UPP_TYPE(QTSyncTaskProcPtr)                       QTSyncTaskUPP;
struct QTSyncTaskRecord {
  void *              qLink;
  QTSyncTaskUPP       proc;
};
typedef struct QTSyncTaskRecord         QTSyncTaskRecord;
typedef QTSyncTaskRecord *              QTSyncTaskPtr;

typedef CALLBACK_API( OSErr , MovieRgnCoverProcPtr )(Movie theMovie, RgnHandle changedRgn, long refcon);
typedef CALLBACK_API( OSErr , MovieProgressProcPtr )(Movie theMovie, short message, short whatOperation, Fixed percentDone, long refcon);
typedef CALLBACK_API( OSErr , MovieDrawingCompleteProcPtr )(Movie theMovie, long refCon);
typedef CALLBACK_API( OSErr , TrackTransferProcPtr )(Track t, long refCon);
typedef CALLBACK_API( OSErr , GetMovieProcPtr )(long offset, long size, void *dataPtr, void *refCon);
typedef CALLBACK_API( Boolean , MoviePreviewCallOutProcPtr )(long refcon);
typedef CALLBACK_API( OSErr , TextMediaProcPtr )(Handle theText, Movie theMovie, short *displayFlag, long refcon);
typedef CALLBACK_API( OSErr , ActionsProcPtr )(void *refcon, Track targetTrack, long targetRefCon, QTEventRecordPtr theEvent);
typedef CALLBACK_API( OSErr , DoMCActionProcPtr )(void *refcon, short action, void *params, Boolean *handled);
typedef CALLBACK_API( OSErr , MovieExecuteWiredActionsProcPtr )(Movie theMovie, void *refcon, long flags, QTAtomContainer wiredActions);
typedef CALLBACK_API( void , MoviePrePrerollCompleteProcPtr )(Movie theMovie, OSErr prerollErr, void *refcon);
typedef CALLBACK_API( void , QTNextTaskNeededSoonerCallbackProcPtr )(TimeValue duration, unsigned long flags, void *refcon);
typedef CALLBACK_API( void , MoviesErrorProcPtr )(OSErr theErr, long refcon);
typedef STACK_UPP_TYPE(MovieRgnCoverProcPtr)                    MovieRgnCoverUPP;
typedef STACK_UPP_TYPE(MovieProgressProcPtr)                    MovieProgressUPP;
typedef STACK_UPP_TYPE(MovieDrawingCompleteProcPtr)             MovieDrawingCompleteUPP;
typedef STACK_UPP_TYPE(TrackTransferProcPtr)                    TrackTransferUPP;
typedef STACK_UPP_TYPE(GetMovieProcPtr)                         GetMovieUPP;
typedef STACK_UPP_TYPE(MoviePreviewCallOutProcPtr)              MoviePreviewCallOutUPP;
typedef STACK_UPP_TYPE(TextMediaProcPtr)                        TextMediaUPP;
typedef STACK_UPP_TYPE(ActionsProcPtr)                          ActionsUPP;
typedef STACK_UPP_TYPE(DoMCActionProcPtr)                       DoMCActionUPP;
typedef STACK_UPP_TYPE(MovieExecuteWiredActionsProcPtr)         MovieExecuteWiredActionsUPP;
typedef STACK_UPP_TYPE(MoviePrePrerollCompleteProcPtr)          MoviePrePrerollCompleteUPP;
typedef STACK_UPP_TYPE(QTNextTaskNeededSoonerCallbackProcPtr)   QTNextTaskNeededSoonerCallbackUPP;
typedef STACK_UPP_TYPE(MoviesErrorProcPtr)                      MoviesErrorUPP;
typedef ComponentInstance               MediaHandler;
typedef ComponentInstance               DataHandler;
typedef Component                       MediaHandlerComponent;
typedef Component                       DataHandlerComponent;
typedef ComponentResult                 HandlerError;
enum {
  keepInRam                     = 1 << 0, /* load and make non-purgable*/
  unkeepInRam                   = 1 << 1, /* mark as purgable*/
  flushFromRam                  = 1 << 2, /* empty those handles*/
  loadForwardTrackEdits         = 1 << 3, /*    load track edits into ram for playing forward*/
  loadBackwardTrackEdits        = 1 << 4 /*    load track edits into ram for playing in reverse*/
};

enum {
  newMovieActive                = 1 << 0,
  newMovieDontResolveDataRefs   = 1 << 1,
  newMovieDontAskUnresolvedDataRefs = 1 << 2,
  newMovieDontAutoAlternates    = 1 << 3,
  newMovieDontUpdateForeBackPointers = 1 << 4,
  newMovieDontAutoUpdateClock   = 1 << 5,
  newMovieAsyncOK               = 1 << 8,
  newMovieIdleImportOK          = 1 << 10,
  newMovieDontInteractWithUser  = 1 << 11
};

/* track usage bits */
enum {
  trackUsageInMovie             = 1 << 1,
  trackUsageInPreview           = 1 << 2,
  trackUsageInPoster            = 1 << 3
};

/* Add/GetMediaSample flags */
enum {
  mediaSampleNotSync            = 1 << 0, /* sample is not a sync sample (eg. is frame differenced */
  mediaSampleShadowSync         = 1 << 1, /* sample is a shadow sync */
  mediaSampleDroppable          = 1 << 27, /* sample is not required to be decoded for later samples to be decoded properly */
  mediaSamplePartialSync        = 1 << 16, /* sample is a partial sync (e.g., I frame after open GOP) */
  mediaSampleHasRedundantCoding = 1 << 24, /* sample is known to contain redundant coding */
  mediaSampleHasNoRedundantCoding = 1 << 25, /* sample is known not to contain redundant coding */
  mediaSampleIsDependedOnByOthers = 1 << 26, /* one or more other samples depend upon the decode of this sample */
  mediaSampleIsNotDependedOnByOthers = 1 << 27, /* synonym for mediaSampleDroppable */
  mediaSampleDependsOnOthers    = 1 << 28, /* sample's decode depends upon decode of other samples */
  mediaSampleDoesNotDependOnOthers = 1 << 29, /* sample's decode does not depend upon decode of other samples */
  mediaSampleEarlierDisplayTimesAllowed = 1 << 30 /* samples later in decode order may have earlier display times */
};

/*
MediaSampleFlags is defined in ImageCompression.h:
typedef UInt32 MediaSampleFlags;
*/
enum {
  pasteInParallel               = 1 << 0,
  showUserSettingsDialog        = 1 << 1,
  movieToFileOnlyExport         = 1 << 2,
  movieFileSpecValid            = 1 << 3
};

enum {
  nextTimeMediaSample           = 1 << 0,
  nextTimeMediaEdit             = 1 << 1,
  nextTimeTrackEdit             = 1 << 2,
  nextTimeSyncSample            = 1 << 3,
  nextTimeStep                  = 1 << 4,
  nextTimePartialSyncSample     = 1 << 5,
  nextTimeEdgeOK                = 1 << 14,
  nextTimeIgnoreActiveSegment   = 1 << 15
};

typedef unsigned short                  nextTimeFlagsEnum;
enum {
  createMovieFileDeleteCurFile  = 1L << 31,
  createMovieFileDontCreateMovie = 1L << 30,
  createMovieFileDontOpenFile   = 1L << 29,
  createMovieFileDontCreateResFile = 1L << 28
};

typedef unsigned long                   createMovieFileFlagsEnum;
enum {
  flattenAddMovieToDataFork     = 1L << 0,
  flattenActiveTracksOnly       = 1L << 2,
  flattenDontInterleaveFlatten  = 1L << 3,
  flattenFSSpecPtrIsDataRefRecordPtr = 1L << 4,
  flattenCompressMovieResource  = 1L << 5,
  flattenForceMovieResourceBeforeMovieData = 1L << 6
};

typedef unsigned long                   movieFlattenFlagsEnum;
enum {
  movieInDataForkResID          = -1    /* magic res ID */
};

enum {
  mcTopLeftMovie                = 1 << 0, /* usually centered */
  mcScaleMovieToFit             = 1 << 1, /* usually only scales down */
  mcWithBadge                   = 1 << 2, /* give me a badge */
  mcNotVisible                  = 1 << 3, /* don't show controller */
  mcWithFrame                   = 1 << 4 /* gimme a frame */
};

enum {
  movieScrapDontZeroScrap       = 1 << 0,
  movieScrapOnlyPutMovie        = 1 << 1
};

enum {
  dataRefSelfReference          = 1 << 0,
  dataRefWasNotResolved         = 1 << 1
};

typedef unsigned long                   dataRefAttributesFlags;
enum {
  kMovieAnchorDataRefIsDefault  = 1 << 0 /* data ref returned is movie default data ref */
};

enum {
  hintsScrubMode                = 1 << 0, /* mask == && (if flags == scrub on, flags != scrub off) */
  hintsLoop                     = 1 << 1,
  hintsDontPurge                = 1 << 2,
  hintsUseScreenBuffer          = 1 << 5,
  hintsAllowInterlace           = 1 << 6,
  hintsUseSoundInterp           = 1 << 7,
  hintsHighQuality              = 1 << 8, /* slooooow */
  hintsPalindrome               = 1 << 9,
  hintsInactive                 = 1 << 11,
  hintsOffscreen                = 1 << 12,
  hintsDontDraw                 = 1 << 13,
  hintsAllowBlacklining         = 1 << 14,
  hintsDontUseVideoOverlaySurface = 1 << 16,
  hintsIgnoreBandwidthRestrictions = 1 << 17,
  hintsPlayingEveryFrame        = 1 << 18,
  hintsAllowDynamicResize       = 1 << 19,
  hintsSingleField              = 1 << 20,
  hintsNoRenderingTimeOut       = 1 << 21,
  hintsFlushVideoInsteadOfDirtying = 1 << 22,
  hintsEnableSubPixelPositioning = 1L << 23,
  hintsRenderingMode            = 1L << 24,
  hintsAllowIdleSleep           = 1L << 25, /* asks media handlers not to call UpdateSystemActivity etc */
  hintsDeinterlaceFields        = 1L << 26
};

typedef unsigned long                   playHintsEnum;
enum {
  mediaHandlerFlagBaseClient    = 1
};

typedef unsigned long                   mediaHandlerFlagsEnum;
enum {
  movieTrackMediaType           = 1 << 0,
  movieTrackCharacteristic      = 1 << 1,
  movieTrackEnabledOnly         = 1 << 2
};

/*
   Opaque replacement for SampleReferenceRecord/SampleReference64Record arrays able to carry information
   not described in those arrays of those records
*/
typedef const struct OpaqueQTSampleTable*  QTSampleTableRef;
typedef struct OpaqueQTSampleTable*     QTMutableSampleTableRef;
struct SampleReferenceRecord {
  long                dataOffset;
  long                dataSize;
  TimeValue           durationPerSample;
  long                numberOfSamples;
  short               sampleFlags;
};
typedef struct SampleReferenceRecord    SampleReferenceRecord;
typedef SampleReferenceRecord *         SampleReferencePtr;
struct SampleReference64Record {
  wide                dataOffset;
  unsigned long       dataSize;
  TimeValue           durationPerSample;
  unsigned long       numberOfSamples;
  short               sampleFlags;
};
typedef struct SampleReference64Record  SampleReference64Record;
typedef SampleReference64Record *       SampleReference64Ptr;

/*************************
* Initialization Routines 
**************************/
/*
 *  CheckQuickTimeRegistration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
CheckQuickTimeRegistration(
  void *  registrationKey,
  long    flags)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  EnterMovies()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
EnterMovies(void)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ExitMovies()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
ExitMovies(void)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


enum {
  kQTEnterMoviesFlagDontSetComponentsThreadMode = 1L << 0
};

/*
 *  EnterMoviesOnThread()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
EnterMoviesOnThread(UInt32 inFlags)                           AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  ExitMoviesOnThread()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
ExitMoviesOnThread(void)                                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*************************
* Error Routines 
**************************/

/*
 *  GetMoviesError()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMoviesError(void)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ClearMoviesStickyError()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
ClearMoviesStickyError(void)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMoviesStickyError()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMoviesStickyError(void)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMoviesErrorProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMoviesErrorProc(
  MoviesErrorUPP   errProc,
  long             refcon)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*************************
* Idle Routines 
**************************/
/*
 *  MoviesTask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
MoviesTask(
  Movie   theMovie,
  long    maxMilliSecToUse)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PrerollMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
PrerollMovie(
  Movie       theMovie,
  TimeValue   time,
  Fixed       Rate)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PrePrerollMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
PrePrerollMovie(
  Movie                        m,
  TimeValue                    time,
  Fixed                        rate,
  MoviePrePrerollCompleteUPP   proc,
  void *                       refcon)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AbortPrePrerollMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern void 
AbortPrePrerollMovie(
  Movie   m,
  OSErr   err)                                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LoadMovieIntoRam()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
LoadMovieIntoRam(
  Movie       theMovie,
  TimeValue   time,
  TimeValue   duration,
  long        flags)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LoadTrackIntoRam()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
LoadTrackIntoRam(
  Track       theTrack,
  TimeValue   time,
  TimeValue   duration,
  long        flags)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  LoadMediaIntoRam()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
LoadMediaIntoRam(
  Media       theMedia,
  TimeValue   time,
  TimeValue   duration,
  long        flags)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieActive()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieActive(
  Movie     theMovie,
  Boolean   active)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieActive()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Boolean 
GetMovieActive(Movie theMovie)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTGetWallClockTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTGetWallClockTimeBase(TimeBase * wallClockTimeBase)          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*************************
* Idle Management
**************************/
typedef struct OpaqueIdleManager*       IdleManager;
/*
 *  QTIdleManagerOpen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern IdleManager 
QTIdleManagerOpen(void)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTIdleManagerClose()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTIdleManagerClose(IdleManager im)                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTIdleManagerGetNextIdleTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTIdleManagerGetNextIdleTime(
  IdleManager   im,
  TimeRecord *  nextIdle)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTIdleManagerSetNextIdleTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTIdleManagerSetNextIdleTime(
  IdleManager   im,
  TimeRecord *  nextIdle)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTIdleManagerSetNextIdleTimeNever()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTIdleManagerSetNextIdleTimeNever(IdleManager im)             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTIdleManagerSetNextIdleTimeNow()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTIdleManagerSetNextIdleTimeNow(IdleManager im)               AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTIdleManagerSetNextIdleTimeDelta()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTIdleManagerSetNextIdleTimeDelta(
  IdleManager   im,
  TimeValue     duration,
  TimeScale     scale)                                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTIdleManagerSetParent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTIdleManagerSetParent(
  IdleManager   im,
  IdleManager   parent)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTIdleManagerNeedsAnIdle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTIdleManagerNeedsAnIdle(
  IdleManager   im,
  Boolean *     needsOne)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*************************
* Carbon Movie Control
**************************/
/* Movie Control option bits*/
enum {
  kMovieControlOptionHideController = (1L << 0),
  kMovieControlOptionLocateTopLeft = (1L << 1),
  kMovieControlOptionEnableEditing = (1L << 2),
  kMovieControlOptionHandleEditingHI = (1L << 3),
  kMovieControlOptionSetKeysEnabled = (1L << 4),
  kMovieControlOptionManuallyIdled = (1L << 5)
};

/* Item tags for use in GetControlData() (some with SetControlData()) calls on Movie Controls*/
enum {
  kMovieControlDataMovieController = 'mc  ',
  kMovieControlDataMovie        = 'moov',
  kMovieControlDataManualIdling = 'manu'
};

/*
** CreateMovieControl() -   This is the public API routine that creates a Movie Control. Given a window and location
**                          plus a movie, it constructs a Movie Control with a Movie Controller in the window.
*/
/*
 *  CreateMovieControl()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
CreateMovieControl(
  WindowRef     theWindow,
  Rect *        localRect,
  Movie         theMovie,
  UInt32        options,
  ControlRef *  returnedControl)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*************************
* calls for playing movies, previews, posters
**************************/
/*
 *  StartMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
StartMovie(Movie theMovie)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  StopMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
StopMovie(Movie theMovie)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GoToBeginningOfMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GoToBeginningOfMovie(Movie theMovie)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GoToEndOfMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GoToEndOfMovie(Movie theMovie)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IsMovieDone()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Boolean 
IsMovieDone(Movie theMovie)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMoviePreviewMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Boolean 
GetMoviePreviewMode(Movie theMovie)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMoviePreviewMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMoviePreviewMode(
  Movie     theMovie,
  Boolean   usePreview)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ShowMoviePoster()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
ShowMoviePoster(Movie theMovie)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PlayMoviePreview()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
PlayMoviePreview(
  Movie                    theMovie,
  MoviePreviewCallOutUPP   callOutProc,
  long                     refcon)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*************************
* calls for controlling movies & tracks which are playing
**************************/
/*
 *  GetMovieTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeBase 
GetMovieTimeBase(Movie theMovie)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieMasterTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieMasterTimeBase(
  Movie               theMovie,
  TimeBase            tb,
  const TimeRecord *  slaveZero)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieMasterClock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieMasterClock(
  Movie               theMovie,
  Component           clockMeister,
  const TimeRecord *  slaveZero)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ChooseMovieClock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern void 
ChooseMovieClock(
  Movie   m,
  long    flags)                                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  GetMovieGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetMovieGWorld(
  Movie       theMovie,
  CGrafPtr *  port,
  GDHandle *  gdh)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieGWorld(
  Movie      theMovie,
  CGrafPtr   port,
  GDHandle   gdh)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


enum {
  movieDrawingCallWhenChanged   = 0,
  movieDrawingCallAlways        = 1
};

/*
 *  SetMovieDrawingCompleteProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieDrawingCompleteProc(
  Movie                     theMovie,
  long                      flags,
  MovieDrawingCompleteUPP   proc,
  long                      refCon)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  GetMovieNaturalBoundsRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetMovieNaturalBoundsRect(
  Movie   theMovie,
  Rect *  naturalBounds)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetNextTrackForCompositing()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Track 
GetNextTrackForCompositing(
  Movie   theMovie,
  Track   theTrack)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPrevTrackForCompositing()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Track 
GetPrevTrackForCompositing(
  Movie   theMovie,
  Track   theTrack)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTrackGWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTrackGWorld(
  Track              theTrack,
  CGrafPtr           port,
  GDHandle           gdh,
  TrackTransferUPP   proc,
  long               refCon)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMoviePict()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern PicHandle 
GetMoviePict(
  Movie       theMovie,
  TimeValue   time)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackPict()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern PicHandle 
GetTrackPict(
  Track       theTrack,
  TimeValue   time)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMoviePosterPict()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern PicHandle 
GetMoviePosterPict(Movie theMovie)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* called between Begin & EndUpdate */
/*
 *  UpdateMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
UpdateMovie(Movie theMovie)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InvalidateMovieRegion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
InvalidateMovieRegion(
  Movie       theMovie,
  RgnHandle   invalidRgn)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/**** spatial movie routines ****/
/*
 *  GetMovieBox()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetMovieBox(
  Movie   theMovie,
  Rect *  boxRect)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieBox()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieBox(
  Movie         theMovie,
  const Rect *  boxRect)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/** movie display clip */
/*
 *  GetMovieDisplayClipRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern RgnHandle 
GetMovieDisplayClipRgn(Movie theMovie)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieDisplayClipRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieDisplayClipRgn(
  Movie       theMovie,
  RgnHandle   theClip)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/** movie src clip */
/*
 *  GetMovieClipRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern RgnHandle 
GetMovieClipRgn(Movie theMovie)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieClipRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieClipRgn(
  Movie       theMovie,
  RgnHandle   theClip)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/** track src clip */
/*
 *  GetTrackClipRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern RgnHandle 
GetTrackClipRgn(Track theTrack)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTrackClipRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTrackClipRgn(
  Track       theTrack,
  RgnHandle   theClip)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/** bounds in display space (not clipped by display clip) */
/*
 *  GetMovieDisplayBoundsRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern RgnHandle 
GetMovieDisplayBoundsRgn(Movie theMovie)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackDisplayBoundsRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern RgnHandle 
GetTrackDisplayBoundsRgn(Track theTrack)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/** bounds in movie space */
/*
 *  GetMovieBoundsRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern RgnHandle 
GetMovieBoundsRgn(Movie theMovie)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackMovieBoundsRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern RgnHandle 
GetTrackMovieBoundsRgn(Track theTrack)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/** bounds in track space */
/*
 *  GetTrackBoundsRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern RgnHandle 
GetTrackBoundsRgn(Track theTrack)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/** mattes - always in track space */
/*
 *  GetTrackMatte()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern PixMapHandle 
GetTrackMatte(Track theTrack)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTrackMatte()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTrackMatte(
  Track          theTrack,
  PixMapHandle   theMatte)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeMatte()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
DisposeMatte(PixMapHandle theMatte)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/** video out */
/*
 *  SetMovieVideoOutput()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern void 
SetMovieVideoOutput(
  Movie               theMovie,
  ComponentInstance   vout)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*************************
 * Audio Context
 *************************/
/*
   The QTAudioContextRef type encapsulates a connection to an audio output device.
   It represents a destination audio rendering environment that can be used for
   playback of a movie.
*/
typedef struct QTAudioContextRefType*   QTAudioContextRef;
/*
 *  QTAudioContextRetain()
 *  
 *  Summary:
 *    Retains a QTAudioContext object by incrementing its reference
 *    count. You should retain the object when you receive it from
 *    elsewhere (that is, you did not create it) and you want it to
 *    persist. If you retain a QTAudioContext object you are
 *    responsible for releasing it. The same audio context is returned
 *    for convenience. If audioContext is NULL, nothing happens.
 *  
 *  Parameters:
 *    
 *    audioContext:
 *      [in] The audio context to retain.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern QTAudioContextRef 
QTAudioContextRetain(QTAudioContextRef audioContext)          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTAudioContextRelease()
 *  
 *  Summary:
 *    Release a QTAudioContext object by decrementing its reference
 *    count. If that count consequently becomes zero the memory
 *    allocated to the object is deallocated and the object is
 *    destroyed. If you create or explicitly retain a QTAudioContext
 *    object, you are responsible for releasing it when you no longer
 *    need it. If audioContext is NULL, nothing happens.
 *  
 *  Parameters:
 *    
 *    audioContext:
 *      [in] The audio context to release.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern void 
QTAudioContextRelease(QTAudioContextRef audioContext)         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTAudioContextCreateForAudioDevice()
 *  
 *  Summary:
 *    Creates a QTAudioContext object that encapsulates a connection to
 *    an audio output device. This object is suitable for passing to
 *    SetMovieAudioContext or NewMovieFromProperties, which targets the
 *    audio output of the movie to that device. A QTAudioContext object
 *    cannot be associated with more than one movie. Each movie needs
 *    its own connection to the device. In order to play more than one
 *    movie to a particular device, create a QTAudioContext object for
 *    each movie. You are responsible for releasing the QTAudioContext
 *    object created by this routine. After calling
 *    SetMovieAudioContext or NewMovieFromProperties, you can release
 *    the object since these APIs will retain it for their own use. On
 *    Windows, the audioDeviceUID is the GUID of a DirectSound device,
 *    stringified using such Win32 functions as StringFromCLSID() or
 *    StringFromGUID2(), then wrapped in a CFStringRef using
 *    CFStringCreateWithCharacters().  After passing the audioDeviceUID
 *    CFStringRef to QTAudioContextCreateForAudioDevice(), remember to
 *    CFRelease() the CFStringRef you created.
 *  
 *  Parameters:
 *    
 *    allocator:
 *      [in]  Allocator used to create the audio context.
 *    
 *    audioDeviceUID:
 *      [in]  Audio device UID.  NULL means the default CoreAudio
 *      device.
 *    
 *    options:
 *      [in]  Reserved.  Pass NULL.
 *    
 *    newAudioContextOut:
 *      [out] Points to a variable to receive the new audio context.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTAudioContextCreateForAudioDevice(
  CFAllocatorRef       allocator,
  CFStringRef          audioDeviceUID,
  CFDictionaryRef      options,
  QTAudioContextRef *  newAudioContextOut)                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*************************
 * Audio Context Inserts
 *************************/
/*
   Theory of operations:
    To register for a Movie Audio Context Insert during playback:
        1) Get the movie's current audio context: GetMovieAudioContext()
        2) Register the application insert: QTAudioContextRegisterInsert()
    To unregister a Movie Audio Context Insert:
        Call QTAudioContextRegisterInsert() with a NULL QTAudioContextInsertRegistryInfoRef
           If the registry ptr is non-NULL but the processDataCallback is NULL, this has the same effect.
    To register for a Track Audio Context Insert during playback:
        Set the kQTAudioPropertyID_RegisterAudioContextInsert property on the track,
            providing the same registry info structure that is used for the QTAudioContextRegisterInsert() call.
    To unregister a Track Audio Context Insert:
        Set the kQTAudioPropertyID_RegisterAudioContextInsert property on the track,
            with a NULL processDataCallback
*/


/*
 *  AudioContextInsertProcessDataCallback
 *  
 *  Summary:
 *    A client-supplied function to be called during playback to get
 *    data from the audio insert.
 *  
 *  Discussion:
 *    This routine is called by the Audio Context for each buffer of
 *    audio data it renders. The client receives a source buffer list
 *    and a destination buffer list, and it is responsible for
 *    supplying output buffers to the destination buffer list. This
 *    routine is generally called on the IOProc at high thread
 *    priority, and so should not do memory allocation or release,
 *    acquire mutex resources, nor take very long to process.
 *  
 *  Parameters:
 *    
 *    inUserData:
 *      An opaque pointer to the client's data.
 *    
 *    ioRenderFlags:
 *      A field that contains render action flags (see AUComponent.h).
 *    
 *    inTimeStamp:
 *      An AudioTimeStamp that indicates the start time of the buffer
 *      to be processed. During normal playback or audio extraction,
 *      the timestamp mSampleTime is normalized to the movie time that
 *      this particular input sample buffer represents, expressed in
 *      the sample rate being processed. During reverse playback, the
 *      first Process Data call after Reset will contain a timestamp
 *      designating the movie time, but subsequent timestamps will
 *      advance forward instead of in reverse.
 *    
 *    inNumberFrames:
 *      A UInt32 that specifies the number of frames to be rendered.
 *    
 *    inInputData:
 *      An AudioBufferList used to pass input data to the insert.
 *    
 *    outOutputData:
 *      An AudioBufferList to receive the processed data that is
 *      produced by the insert. QuickTime sets buffer pointers in the
 *      list to NULL. The client must set the buffer pointers to refer
 *      to either its own allocated buffers or to be copies of the
 *      buffer pointers received in inInputData.
 */
typedef CALLBACK_API( OSStatus , AudioContextInsertProcessDataCallback )(void *inUserData, AudioUnitRenderActionFlags *ioRenderFlags, const AudioTimeStamp *inTimeStamp, UInt32 inNumberFrames, AudioBufferList *inInputData, AudioBufferList *outOutputData);

/*
 *  AudioContextInsertResetCallback
 *  
 *  Summary:
 *    A client-supplied function to be called to initialize and reset
 *    for processing data.
 *  
 *  Discussion:
 *    This routine is called by the Audio Context to initialize for
 *    rendering. The client is told the sample rate and the maximum
 *    number of frames it will be asked to process on any single
 *    ProcessData callback (ie, inNumberFrames will always be <=
 *    inMaxFrames). On return, the client reports its processing
 *    latency and tail times. This callback is invoked whenever the
 *    rendering chain is interrupted (eg, when playback jumps to a new
 *    point or changes direction). The client should call
 *    AudioUnitReset on any audio units in use, and should be prepared
 *    to respond to changes of sample rate or maxframes.
 *  
 *  Parameters:
 *    
 *    inUserData:
 *      An opaque pointer to the client's data.
 *    
 *    inSampleRate:
 *      A Float64 that will specifies the sample rate of the data to be
 *      processed.
 *    
 *    inMaxFrames:
 *      A UInt32 that specifies the maximum number of maximum frame
 *      count that will be processed in a single call.
 *    
 *    outLatency:
 *      A pointer to a Float64 that specifies the insert's render
 *      latency, in seconds. Latency data will be pulled and discarded
 *      by QuickTime after each reset.
 *    
 *    outTailTime:
 *      A pointer to a Float64 that specifies the insert's tail render
 *      time, in seconds.
 */
typedef CALLBACK_API( OSStatus , AudioContextInsertResetCallback )(void *inUserData, Float64 inSampleRate, UInt32 inMaxFrames, Float64 *outLatency, Float64 *outTailTime);

/*
 *  AudioContextInsertFinalizeCallback
 *  
 *  Summary:
 *    A client-supplied function to be called to release any resources
 *    in use by the insert.
 *  
 *  Discussion:
 *    This routine is called when the Audio Context is being disposed
 *    (ie, the MovieAudioContext has been reset or the movie was
 *    disposed). Once this callback returns, no more calls for this
 *    registered insert will be made.
 *  
 *  Parameters:
 *    
 *    inUserData:
 *      An opaque pointer to the client's data.
 */
typedef CALLBACK_API( OSStatus , AudioContextInsertFinalizeCallback )(void * inUserData);

/*
 *  QTAudioContextInsertRegistryInfo
 *  
 *  Summary:
 *    Parameters for registering an Audio Context insert
 *  
 *  Discussion:
 *    This is used with QTAudioContextRegisterInsert() and the Movie
 *    Audio Extraction
 *    kQTMovieAudioExtractionAudioPropertyID_RegisterMovieInsert
 *    property.
 */
struct QTAudioContextInsertRegistryInfo {

  /*
   * client user data to be passed to all client-specified callbacks.
   */
  void *              userData;

  /*
   * The size of the input channel layout structure.
   */
  UInt32              inputChannelLayoutSize;

  /*
   * An AudioChannelLayout that describes the channel layout (and,
   * implicitly, channel valence) of the data that the insert expects
   * as input.
   */
  AudioChannelLayout * inputChannelLayout;

  /*
   * The size of the output channel layout structure.
   */
  UInt32              outputChannelLayoutSize;

  /*
   * An AudioChannelLayout that describes the channel layout (and,
   * implicitly, channel valence) of the processed data that the insert
   * will output.
   */
  AudioChannelLayout * outputChannelLayout;

  /*
   * Client-specified process data callback.
   */
  AudioContextInsertProcessDataCallback  processDataCallback;

  /*
   * Client-specified reset callback.
   */
  AudioContextInsertResetCallback  resetCallback;

  /*
   * Client-specified finalize callback (may be NULL). NOTE: Calls to
   * the client callbacks are interlocked with respect to each other:
   * there will never be simultaneous calls, with an identical
   * inUserData, on different threads.
   */
  AudioContextInsertFinalizeCallback  finalizeCallback;
};
typedef struct QTAudioContextInsertRegistryInfo QTAudioContextInsertRegistryInfo;
typedef QTAudioContextInsertRegistryInfo * QTAudioContextInsertRegistryInfoRef;
/*
 *  QTAudioContextRegisterInsert()
 *  
 *  Summary:
 *    Register an audio insert with QuickTime
 *  
 *  Discussion:
 *    This routine is called to register an application to tap into the
 *    audio playback stream, via callbacks during audio rendering. The
 *    inAudioContext parameter refers to a Movie Audio Context that has
 *    not yet been associated with a movie. Once the application has
 *    successfully registered its insert, it may associate a movie with
 *    this Audio Context by calling SetMovieAudioContext(). The
 *    application must then be prepared to handle callbacks, which may
 *    be executed on different threads, until the Finalize callback
 *    with a matching userData parameter, is received. The application
 *    may supply a NULL Finalize callback if it has its own logic for
 *    detecting when it may release its insert resources.
 *  
 *  Parameters:
 *    
 *    inAudioContext:
 *      A QTAudioContextRef that specifies the Audio Context to tap
 *      into.
 *    
 *    inRegistryInfoSize:
 *      Size, in bytes, of the supplied
 *      QTAudioContextInsertRegistryInfo structure.
 *    
 *    inRegistryInfo:
 *      Pointer to a QTAudioContextInsertRegistryInfo structure
 *      containing setup parameters for the Audio Context insert and
 *      callbacks.
 *  
 *  Result:
 *    readErr Cannot register an insert on a movie containing protected
 *    data.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 (or QuickTime 7.2) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTAudioContextRegisterInsert(
  QTAudioContextRef                     inAudioContext,
  UInt32                                inRegistryInfoSize,
  QTAudioContextInsertRegistryInfoRef   inRegistryInfo)       AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;



/* Track-level Audio Context Insert property (kQTPropertyClass_Audio)*/

/*
 */
enum {

  /*
   * kQTAudioPropertyID_RegisterAudioContextInsert: Value is
   * QTAudioContextInsertRegistryInfoRef  (Get/Set) Set on a Track to
   * register/unregister an Audio Context Insert for that specific
   * track.    When this property is read back (QTGetTrackProperty) the
   * channel layout pointers will will be NULL.  To unregister, supply
   * a NULL processDataCallback (in which case the rest of the registry
   * info will be ignored).
   */
  kQTAudioPropertyID_RegisterAudioContextInsert = 'regt' /* value is QTAudioContextInsertRegistryInfoRef. Get/Set.*/
};


/******************************************
 * Using Audio/Visual contexts with movies
 *****************************************/
/*
 *  SetMovieVisualContext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMovieVisualContext(
  Movie                movie,
  QTVisualContextRef   visualContext)                         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMovieVisualContext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMovieVisualContext(
  Movie                 movie,
  QTVisualContextRef *  visualContext)                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  SetMovieAudioContext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMovieAudioContext(
  Movie               movie,
  QTAudioContextRef   audioContext)                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMovieAudioContext()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMovieAudioContext(
  Movie                movie,
  QTAudioContextRef *  audioContext)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*************************
* calls for getting/saving movies
**************************/
/** Properties for NewMovieFromProperties */
enum {
  kQTPropertyClass_DataLocation = 'dloc',
  kQTDataLocationPropertyID_DataReference = 'dref', /* DataReferenceRecord (for semantics of NewMovieFromDataRef)*/
  kQTDataLocationPropertyID_CFStringNativePath = 'cfnp',
  kQTDataLocationPropertyID_CFStringPosixPath = 'cfpp',
  kQTDataLocationPropertyID_CFStringHFSPath = 'cfhp',
  kQTDataLocationPropertyID_CFStringWindowsPath = 'cfwp',
  kQTDataLocationPropertyID_CFURL = 'cfur',
  kQTDataLocationPropertyID_QTDataHandler = 'qtdh', /* for semantics of NewMovieFromStorageOffset*/
  kQTDataLocationPropertyID_Scrap = 'scrp',
  kQTDataLocationPropertyID_LegacyMovieResourceHandle = 'rezh', /* QTNewMovieUserProcInfo * (for semantics of NewMovieFromHandle)*/
  kQTDataLocationPropertyID_MovieUserProc = 'uspr', /* for semantics of NewMovieFromUserProc*/
  kQTDataLocationPropertyID_ResourceFork = 'rfrk', /* for semantics of NewMovieFromFile*/
  kQTDataLocationPropertyID_DataFork = 'dfrk', /* for semantics of NewMovieFromDataFork64*/
  kQTPropertyClass_Context      = 'ctxt', /* Media Contexts*/
  kQTContextPropertyID_AudioContext = 'audi',
  kQTContextPropertyID_VisualContext = 'visu',
  kQTPropertyClass_MovieResourceLocator = 'rloc',
  kQTMovieResourceLocatorPropertyID_LegacyResID = 'rezi', /* (input/result property)*/
  kQTMovieResourceLocatorPropertyID_LegacyResName = 'rezn', /* (result property)*/
  kQTMovieResourceLocatorPropertyID_FileOffset = 'foff', /* NewMovieFromDataFork[64]*/
  kQTMovieResourceLocatorPropertyID_Callback = 'calb', /* NewMovieFromUserProc(getProc,refcon)*/
                                        /* Uses kQTMovieDefaultDataRefPropertyID for default dataref*/
  kQTPropertyClass_MovieInstantiation = 'mins',
  kQTMovieInstantiationPropertyID_DontResolveDataRefs = 'rdrn',
  kQTMovieInstantiationPropertyID_DontAskUnresolvedDataRefs = 'aurn',
  kQTMovieInstantiationPropertyID_DontAutoAlternates = 'aaln',
  kQTMovieInstantiationPropertyID_DontUpdateForeBackPointers = 'fbpn',
  kQTMovieInstantiationPropertyID_AsyncOK = 'asok',
  kQTMovieInstantiationPropertyID_IdleImportOK = 'imok',
  kQTMovieInstantiationPropertyID_DontAutoUpdateClock = 'aucl',
  kQTMovieInstantiationPropertyID_ResultDataLocationChanged = 'dlch', /* (result property)*/
  kQTMovieInstantiationPropertyID_AllowMediaOptimization = 'amop',
  kQTPropertyClass_NewMovieProperty = 'mprp',
  kQTNewMoviePropertyID_DefaultDataRef = 'ddrf', /* DataReferenceRecord*/
  kQTNewMoviePropertyID_Active  = 'actv',
  kQTNewMoviePropertyID_DontInteractWithUser = 'intn'
};


/** Property value for kQTDataLocationPropertyID_MovieUserProc */
struct QTNewMovieUserProcRecord {
  GetMovieUPP         getMovieUserProc;
  void *              getMovieUserProcRefcon;
  DataReferenceRecord  defaultDataRef;
};
typedef struct QTNewMovieUserProcRecord QTNewMovieUserProcRecord;
/** Property structure for NewMovieFromProperties */
struct QTNewMoviePropertyElement {
  QTPropertyClass     propClass;
  QTPropertyID        propID;
  ByteCount           propValueSize;
  QTPropertyValuePtr  propValueAddress;
  OSStatus            propStatus;
};
typedef struct QTNewMoviePropertyElement QTNewMoviePropertyElement;
/*
 *  NewMovieFromProperties()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
NewMovieFromProperties(
  ItemCount                    inputPropertyCount,
  QTNewMoviePropertyElement *  inputProperties,
  ItemCount                    outputPropertyCount,
  QTNewMoviePropertyElement *  outputProperties,
  Movie *                      theMovie)                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  NewMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Movie 
NewMovie(long flags)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PutMovieIntoHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
PutMovieIntoHandle(
  Movie    theMovie,
  Handle   publicMovie)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PutMovieIntoDataFork()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
PutMovieIntoDataFork(
  Movie   theMovie,
  short   fRefNum,
  long    offset,
  long    maxSize)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PutMovieIntoDataFork64()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
PutMovieIntoDataFork64(
  Movie           theMovie,
  long            fRefNum,
  const wide *    offset,
  unsigned long   maxSize)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PutMovieIntoStorage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
PutMovieIntoStorage(
  Movie           theMovie,
  DataHandler     dh,
  const wide *    offset,
  unsigned long   maxSize)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  PutMovieForDataRefIntoHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
PutMovieForDataRefIntoHandle(
  Movie    theMovie,
  Handle   dataRef,
  OSType   dataRefType,
  Handle   publicMovie)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  DisposeMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
DisposeMovie(Movie theMovie)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*************************
* Movie State Routines
**************************/
/*
 *  GetMovieCreationTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern unsigned long 
GetMovieCreationTime(Movie theMovie)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieModificationTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern unsigned long 
GetMovieModificationTime(Movie theMovie)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieTimeScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeScale 
GetMovieTimeScale(Movie theMovie)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieTimeScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieTimeScale(
  Movie       theMovie,
  TimeScale   timeScale)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieDuration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeValue 
GetMovieDuration(Movie theMovie)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Fixed 
GetMovieRate(Movie theMovie)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieRate(
  Movie   theMovie,
  Fixed   rate)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMoviePreferredRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Fixed 
GetMoviePreferredRate(Movie theMovie)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMoviePreferredRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMoviePreferredRate(
  Movie   theMovie,
  Fixed   rate)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetMovieMatrix(
  Movie           theMovie,
  MatrixRecord *  matrix)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieMatrix(
  Movie                 theMovie,
  const MatrixRecord *  matrix)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMoviePreviewTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetMoviePreviewTime(
  Movie        theMovie,
  TimeValue *  previewTime,
  TimeValue *  previewDuration)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMoviePreviewTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMoviePreviewTime(
  Movie       theMovie,
  TimeValue   previewTime,
  TimeValue   previewDuration)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMoviePosterTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeValue 
GetMoviePosterTime(Movie theMovie)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMoviePosterTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMoviePosterTime(
  Movie       theMovie,
  TimeValue   posterTime)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieSelection()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetMovieSelection(
  Movie        theMovie,
  TimeValue *  selectionTime,
  TimeValue *  selectionDuration)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieSelection()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieSelection(
  Movie       theMovie,
  TimeValue   selectionTime,
  TimeValue   selectionDuration)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieActiveSegment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieActiveSegment(
  Movie       theMovie,
  TimeValue   startTime,
  TimeValue   duration)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieActiveSegment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetMovieActiveSegment(
  Movie        theMovie,
  TimeValue *  startTime,
  TimeValue *  duration)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeValue 
GetMovieTime(
  Movie         theMovie,
  TimeRecord *  currentTime)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieTime(
  Movie               theMovie,
  const TimeRecord *  newtime)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieTimeValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieTimeValue(
  Movie       theMovie,
  TimeValue   newtime)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  GetMovieUserData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern UserData 
GetMovieUserData(Movie theMovie)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTGetTimeUntilNextTask()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTGetTimeUntilNextTask(
  long *  duration,
  long    scale)                                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTInstallNextTaskNeededSoonerCallback()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTInstallNextTaskNeededSoonerCallback(
  QTNextTaskNeededSoonerCallbackUPP   callbackProc,
  TimeScale                           scale,
  unsigned long                       flags,
  void *                              refcon)                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTUninstallNextTaskNeededSoonerCallback()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTUninstallNextTaskNeededSoonerCallback(
  QTNextTaskNeededSoonerCallbackUPP   callbackProc,
  void *                              refcon)                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  GetMovieRateChangeConstraints()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
GetMovieRateChangeConstraints(
  Movie         theMovie,
  TimeRecord *  minimumDelay,
  TimeRecord *  maximumDelay)                                 AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*************************
* Track/Media finding routines
**************************/
/*
 *  GetMovieTrackCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetMovieTrackCount(Movie theMovie)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieTrack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Track 
GetMovieTrack(
  Movie   theMovie,
  long    trackID)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieIndTrack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Track 
GetMovieIndTrack(
  Movie   theMovie,
  long    index)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieIndTrackType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Track 
GetMovieIndTrackType(
  Movie    theMovie,
  long     index,
  OSType   trackType,
  long     flags)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetTrackID(Track theTrack)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Movie 
GetTrackMovie(Track theTrack)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*************************
* Track creation routines
**************************/
/*
 *  NewMovieTrack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Track 
NewMovieTrack(
  Movie   theMovie,
  Fixed   width,
  Fixed   height,
  short   trackVolume)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeMovieTrack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
DisposeMovieTrack(Track theTrack)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*************************
* Track State routines
**************************/
/*
 *  GetTrackCreationTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern unsigned long 
GetTrackCreationTime(Track theTrack)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackModificationTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern unsigned long 
GetTrackModificationTime(Track theTrack)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  GetTrackEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Boolean 
GetTrackEnabled(Track theTrack)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTrackEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTrackEnabled(
  Track     theTrack,
  Boolean   isEnabled)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackUsage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetTrackUsage(Track theTrack)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTrackUsage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTrackUsage(
  Track   theTrack,
  long    usage)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackDuration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeValue 
GetTrackDuration(Track theTrack)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackOffset()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeValue 
GetTrackOffset(Track theTrack)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTrackOffset()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTrackOffset(
  Track       theTrack,
  TimeValue   movieOffsetTime)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackLayer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern short 
GetTrackLayer(Track theTrack)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTrackLayer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTrackLayer(
  Track   theTrack,
  short   layer)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackAlternate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Track 
GetTrackAlternate(Track theTrack)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTrackAlternate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTrackAlternate(
  Track   theTrack,
  Track   alternateT)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetAutoTrackAlternatesEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetAutoTrackAlternatesEnabled(
  Movie     theMovie,
  Boolean   enable)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SelectMovieAlternates()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SelectMovieAlternates(Movie theMovie)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetTrackMatrix(
  Track           theTrack,
  MatrixRecord *  matrix)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTrackMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTrackMatrix(
  Track                 theTrack,
  const MatrixRecord *  matrix)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackDimensions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetTrackDimensions(
  Track    theTrack,
  Fixed *  width,
  Fixed *  height)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTrackDimensions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTrackDimensions(
  Track   theTrack,
  Fixed   width,
  Fixed   height)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackUserData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern UserData 
GetTrackUserData(Track theTrack)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackDisplayMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetTrackDisplayMatrix(
  Track           theTrack,
  MatrixRecord *  matrix)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*************************
* get Media routines
**************************/
/*
 *  NewTrackMedia()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Media 
NewTrackMedia(
  Track       theTrack,
  OSType      mediaType,
  TimeScale   timeScale,
  Handle      dataRef,
  OSType      dataRefType)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeTrackMedia()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
DisposeTrackMedia(Media theMedia)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackMedia()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Media 
GetTrackMedia(Track theTrack)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaTrack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Track 
GetMediaTrack(Media theMedia)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*************************
* Media State routines
**************************/
/*
 *  GetMediaCreationTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern unsigned long 
GetMediaCreationTime(Media theMedia)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaModificationTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern unsigned long 
GetMediaModificationTime(Media theMedia)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaTimeScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeScale 
GetMediaTimeScale(Media theMedia)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMediaTimeScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMediaTimeScale(
  Media       theMedia,
  TimeScale   timeScale)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaDecodeDuration()
 *  
 *  Summary:
 *    Returns the decode duration of a media.
 *  
 *  Discussion:
 *    A media's decode duration is the sum of the decode durations of
 *    its samples.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation. Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern TimeValue64 
GetMediaDecodeDuration(Media theMedia)                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMediaAdvanceDecodeTime()
 *  
 *  Summary:
 *    Returns the advance decode time of a media.
 *  
 *  Discussion:
 *    A media's advance decode time is the absolute value of the
 *    greatest-magnitude negative display offset of its samples, or
 *    zero if there are no samples with negative display offsets. 
 *     This is the amount that the decode time axis must be adjusted
 *    ahead of the display time axis to ensure that no sample's
 *    adjusted decode time is later than its display time. 
 *    For media without nonzero display offsets, the advance decode
 *    time is zero.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation. Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern TimeValue64 
GetMediaAdvanceDecodeTime(Media theMedia)                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMediaDisplayDuration()
 *  
 *  Summary:
 *    Returns the display duration of a media.
 *  
 *  Discussion:
 *    A media's display duration is its display end time minus its
 *    display start time. For media without nonzero display offsets,
 *    the decode duration and display duration are the same, so
 *    GetMediaDisplayDuration and GetMediaDisplayDuration are
 *    equivalent to GetMediaDuration.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation. Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern TimeValue64 
GetMediaDisplayDuration(Media theMedia)                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMediaDisplayStartTime()
 *  
 *  Summary:
 *    Returns the display start time of a media.
 *  
 *  Discussion:
 *    A media's display start time is the earliest display time of any
 *    of its samples. For media without nonzero display offsets, the
 *    display start time is always zero.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation. Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern TimeValue64 
GetMediaDisplayStartTime(Media theMedia)                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMediaDisplayEndTime()
 *  
 *  Summary:
 *    Returns the display end time of a media.
 *  
 *  Discussion:
 *    A media's display end time is the sum of the display time and
 *    decode duration of the sample with the greatest display time. For
 *    media without nonzero display offsets, the display end time is
 *    the same as the media decode duration, which is the same as the
 *    media duration.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation. Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern TimeValue64 
GetMediaDisplayEndTime(Media theMedia)                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMediaDuration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeValue 
GetMediaDuration(Media theMedia)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaLanguage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern short 
GetMediaLanguage(Media theMedia)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMediaLanguage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMediaLanguage(
  Media   theMedia,
  short   language)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaQuality()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern short 
GetMediaQuality(Media theMedia)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMediaQuality()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMediaQuality(
  Media   theMedia,
  short   quality)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaHandlerDescription()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetMediaHandlerDescription(
  Media     theMedia,
  OSType *  mediaType,
  Str255    creatorName,
  OSType *  creatorManufacturer)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaUserData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern UserData 
GetMediaUserData(Media theMedia)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaInputMap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMediaInputMap(
  Media              theMedia,
  QTAtomContainer *  inputMap)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMediaInputMap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetMediaInputMap(
  Media             theMedia,
  QTAtomContainer   inputMap)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*************************
* Media Handler routines
**************************/
/*
 *  GetMediaHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern MediaHandler 
GetMediaHandler(Media theMedia)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMediaHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetMediaHandler(
  Media                   theMedia,
  MediaHandlerComponent   mH)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*************************
* Media's Data routines
**************************/
/*
 *  BeginMediaEdits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
BeginMediaEdits(Media theMedia)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  EndMediaEdits()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
EndMediaEdits(Media theMedia)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMediaDefaultDataRefIndex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetMediaDefaultDataRefIndex(
  Media   theMedia,
  short   index)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaDataHandlerDescription()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetMediaDataHandlerDescription(
  Media     theMedia,
  short     index,
  OSType *  dhType,
  Str255    creatorName,
  OSType *  creatorManufacturer)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaDataHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern DataHandler 
GetMediaDataHandler(
  Media   theMedia,
  short   index)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMediaDataHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetMediaDataHandler(
  Media                  theMedia,
  short                  index,
  DataHandlerComponent   dataHandler)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetDataHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Component 
GetDataHandler(
  Handle   dataRef,
  OSType   dataHandlerSubType,
  long     flags)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OpenADataHandler()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern OSErr 
OpenADataHandler(
  Handle               dataRef,
  OSType               dataHandlerSubType,
  Handle               anchorDataRef,
  OSType               anchorDataRefType,
  TimeBase             tb,
  long                 flags,
  ComponentInstance *  dh)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*************************
* Media Sample Table Routines
**************************/
/*
 *  GetMediaSampleDescriptionCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetMediaSampleDescriptionCount(Media theMedia)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaSampleDescription()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetMediaSampleDescription(
  Media                     theMedia,
  long                      index,
  SampleDescriptionHandle   descH)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMediaSampleDescription()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetMediaSampleDescription(
  Media                     theMedia,
  long                      index,
  SampleDescriptionHandle   descH)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaSampleCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetMediaSampleCount(Media theMedia)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaSyncSampleCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetMediaSyncSampleCount(Media theMedia)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MediaContainsDisplayOffsets()
 *  
 *  Summary:
 *    Tests whether a media contains display offsets.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation. Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *  
 *  Result:
 *    True, if the media is valid and contains at least one sample with
 *    a nonzero display offset.  False otherwise.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern Boolean 
MediaContainsDisplayOffsets(Media theMedia)                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  SampleNumToMediaDecodeTime()
 *  
 *  Summary:
 *    Finds the decode time for a specified sample.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation. Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *    
 *    logicalSampleNum:
 *      The sample number.
 *    
 *    sampleDecodeTime:
 *      A pointer to a time value. The function updates this time value
 *      to indicate the decode time of the sample specified by the
 *      logicalSampleNum parameter. This time value is expressed in the
 *      media's time scale. Set this parameter to NULL if you do not
 *      want this information.
 *    
 *    sampleDecodeDuration:
 *      A pointer to a time value. The function updates this time value
 *      to indicate the decode duration of the sample specified by the
 *      logicalSampleNum parameter. This time value is expressed in the
 *      media's time scale. Set this parameter to NULL if you do not
 *      want this information.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern void 
SampleNumToMediaDecodeTime(
  Media          theMedia,
  SInt64         logicalSampleNum,
  TimeValue64 *  sampleDecodeTime,
  TimeValue64 *  sampleDecodeDuration)                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  MediaDecodeTimeToSampleNum()
 *  
 *  Summary:
 *    Finds the sample for a specified decode time.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation. Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *    
 *    decodeTime:
 *      The decode time for which you are retrieving sample
 *      information. You must specify this value in the media's time
 *      scale.
 *    
 *    sampleNum:
 *      Points to a variable that is to receive the sample number. The
 *      function returns the sample number that identifies the sample
 *      that contains data for the specified decode time, or zero if it
 *      is not found.
 *    
 *    sampleDecodeTime:
 *      A pointer to a time value. The function updates this time value
 *      to indicate the decode time of the sample specified by the
 *      logicalSampleNum parameter. This time value is expressed in the
 *      media's time scale. Set this parameter to NULL if you do not
 *      want this information.
 *    
 *    sampleDecodeDuration:
 *      A pointer to a time value. The function updates this time value
 *      to indicate the decode duration of the sample specified by the
 *      logicalSampleNum parameter. This time value is expressed in the
 *      media's time scale. Set this parameter to NULL if you do not
 *      want this information.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern void 
MediaDecodeTimeToSampleNum(
  Media          theMedia,
  TimeValue64    decodeTime,
  SInt64 *       sampleNum,
  TimeValue64 *  sampleDecodeTime,
  TimeValue64 *  sampleDecodeDuration)                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  SampleNumToMediaDisplayTime()
 *  
 *  Summary:
 *    Finds the display time for a specified sample.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation. Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *    
 *    logicalSampleNum:
 *      The sample number.
 *    
 *    sampleDisplayTime:
 *      A pointer to a time value. The function updates this time value
 *      to indicate the display time of the sample specified by the
 *      logicalSampleNum parameter. This time value is expressed in the
 *      media's time scale. Set this parameter to NULL if you do not
 *      want this information.
 *    
 *    sampleDisplayDuration:
 *      A pointer to a time value. The function updates this time value
 *      to indicate the display duration of the sample specified by the
 *      logicalSampleNum parameter. This time value is expressed in the
 *      media's time scale. Set this parameter to NULL if you do not
 *      want this information.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern void 
SampleNumToMediaDisplayTime(
  Media          theMedia,
  SInt64         logicalSampleNum,
  TimeValue64 *  sampleDisplayTime,
  TimeValue64 *  sampleDisplayDuration)                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  MediaDisplayTimeToSampleNum()
 *  
 *  Summary:
 *    Finds the sample number for a specified display time.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation. Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *    
 *    displayTime:
 *      The display time for which you are retrieving sample
 *      information. You must specify this value in the media's time
 *      scale.
 *    
 *    sampleNum:
 *      Points to a long integer that is to receive the sample number.
 *      The function returns the sample number that identifies the
 *      sample for the specified display time, or zero if it is not
 *      found.
 *    
 *    sampleDisplayTime:
 *      A pointer to a time value. The function updates this time value
 *      to indicate the display time of the sample specified by the
 *      logicalSampleNum parameter. This time value is expressed in the
 *      media's time scale. Set this parameter to NULL if you do not
 *      want this information.
 *    
 *    sampleDisplayDuration:
 *      A pointer to a time value. The function updates this time value
 *      to indicate the display duration of the sample specified by the
 *      logicalSampleNum parameter. This time value is expressed in the
 *      media's time scale. Set this parameter to NULL if you do not
 *      want this information.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern void 
MediaDisplayTimeToSampleNum(
  Media          theMedia,
  TimeValue64    displayTime,
  SInt64 *       sampleNum,
  TimeValue64 *  sampleDisplayTime,
  TimeValue64 *  sampleDisplayDuration)                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  SampleNumToMediaTime()
 *  
 *  Summary:
 *    Finds the media time for a specified sample.
 *  
 *  Discussion:
 *    For media with display offsets, SampleNumToMediaTime is ambiguous
 *    and will return kQTMediaHasDisplayOffsetsErr. Call
 *    SampleNumToMediaDecodeTime or SampleNumToMediaDisplayTime instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SampleNumToMediaTime(
  Media        theMedia,
  long         logicalSampleNum,
  TimeValue *  sampleTime,
  TimeValue *  sampleDuration)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MediaTimeToSampleNum()
 *  
 *  Summary:
 *    Finds the sample number for a specified media time.
 *  
 *  Discussion:
 *    For media with display offsets, MediaTimeToSampleNum is ambiguous
 *    and will return kQTMediaHasDisplayOffsetsErr. Call
 *    MediaDecodeTimeToSampleNum or MediaDisplayTimeToSampleNum instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
MediaTimeToSampleNum(
  Media        theMedia,
  TimeValue    time,
  long *       sampleNum,
  TimeValue *  sampleTime,
  TimeValue *  sampleDuration)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddMediaSample2()
 *  
 *  Summary:
 *    Adds sample data and a description to a media. AddMediaSample2
 *    extends and supercedes AddMediaSample.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation.  Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *    
 *    dataIn:
 *      Points to sample data.
 *    
 *    size:
 *      The number of bytes of sample data to be added to the media.
 *      This parameter indicates the total number of bytes in the
 *      sample data to be added to the media, not the number of bytes
 *      per sample. Use the numberOfSamples parameter to indicate the
 *      number of samples that are contained in the sample data.
 *    
 *    decodeDurationPerSample:
 *      The duration of each sample to be added. You must specify this
 *      parameter in the media time scale. For example, if you are
 *      adding sound that was sampled at 22 kHz to a media that
 *      contains a sound track with the same time scale, you would set
 *      durationPerSample to 1. Similarly, if you are adding video that
 *      was recorded at 10 frames per second to a video media that has
 *      a time scale of 600, you would set this parameter to 60 to add
 *      a single sample.
 *    
 *    displayOffset:
 *      The offset from decode time to display time of each sample to
 *      be added. You must specify this parameter in the media time
 *      scale. If the decode times and display times for the samples
 *      are identical, pass zero.
 *    
 *    sampleDescriptionH:
 *      A handle to a SampleDescription structure. Some media
 *      structures may require sample descriptions. There are different
 *      descriptions for different types of samples. For example, a
 *      media that contains compressed video requires that you supply
 *      an ImageDescription structure. A media that contains sound
 *      requires that you supply a SoundDescription structure.
 *    
 *    numberOfSamples:
 *      The number of samples contained in the sample data to be added
 *      to the media.
 *    
 *    sampleFlags:
 *      Specifies the media sample flags for the samples to be added.
 *    
 *    sampleDecodeTimeOut:
 *      A pointer to a time value. After adding the sample data to the
 *      media, the AddMediaSample function returns the decode time
 *      where the first sample was inserted in the time value referred
 *      to by this parameter. If you don't want to receive this
 *      information, set this parameter to NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSErr 
AddMediaSample2(
  Media                     theMedia,
  const UInt8 *             dataIn,
  ByteCount                 size,
  TimeValue64               decodeDurationPerSample,
  TimeValue64               displayOffset,
  SampleDescriptionHandle   sampleDescriptionH,
  ItemCount                 numberOfSamples,
  MediaSampleFlags          sampleFlags,
  TimeValue64 *             sampleDecodeTimeOut)           /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  AddMediaSampleFromEncodedFrame()
 *  
 *  Summary:
 *    Adds sample data and description from an encoded frame to a media.
 *  
 *  Discussion:
 *    This is a convenience API to make it easy to add frames emitted
 *    by ICM compression session APIs to media.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation.  Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *    
 *    encodedFrame:
 *      An encoded frame token returned by an ICMCompressionSequence.
 *    
 *    sampleDecodeTimeOut:
 *      A pointer to a time value. After adding the sample data to the
 *      media, the function returns the decode time where the first
 *      sample was inserted in the time value referred to by this
 *      parameter. If you don't want to receive this information, set
 *      this parameter to NULL.
 *  
 *  Result:
 *    An operating system result code.
 *    kQTMediaDoesNotSupportDisplayOffsetsErr if the media does not
 *    support nonzero display offsets. kQTDisplayTimeAlreadyInUseErr if
 *    there is already a sample with this display time.
 *    kQTDisplayTimeTooEarlyErr if a sample's display time would be
 *    earlier than the display time of an existing sample that does not
 *    have the mediaSampleEarlierDisplayTimesAllowed flag set.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSErr 
AddMediaSampleFromEncodedFrame(
  Media                theMedia,
  ICMEncodedFrameRef   encodedFrame,
  TimeValue64 *        sampleDecodeTimeOut)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  AddSampleTableToMedia()
 *  
 *  Summary:
 *    Adds sample references from a sample table to a media.
 *    AddSampleTableToMedia supercedes AddMediaSampleReferences and
 *    AddMediaSampleReferences64.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation.  Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *    
 *    sampleTable:
 *      The sample table containing sample references to be added to
 *      the media.
 *    
 *    startSampleNum:
 *      The sample number of the first sample reference in the sample
 *      table to be added to the media.  The first sample's number is 1.
 *    
 *    numberOfSamples:
 *      The number of sample references from the sample table to be
 *      added to the media.
 *    
 *    sampleDecodeTimeOut:
 *      A pointer to a time value. After adding the sample references
 *      to the media, the function returns the decode time where the
 *      first sample was inserted in the time value referred to by this
 *      parameter. If you don't want to receive this information, set
 *      this parameter to NULL.
 *  
 *  Result:
 *    An operating system result code.
 *    kQTMediaDoesNotSupportDisplayOffsetsErr if the media does not
 *    support nonzero display offsets. kQTDisplayTimeAlreadyInUseErr if
 *    there is already a sample with this display time.
 *    kQTDisplayTimeTooEarlyErr if a sample's display time would be
 *    earlier than the display time of an existing sample that does not
 *    have the mediaSampleEarlierDisplayTimesAllowed flag set.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSErr 
AddSampleTableToMedia(
  Media              theMedia,
  QTSampleTableRef   sampleTable,
  SInt64             startSampleNum,
  SInt64             numberOfSamples,
  TimeValue64 *      sampleDecodeTimeOut)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  AddMediaSample()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
AddMediaSample(
  Media                     theMedia,
  Handle                    dataIn,
  long                      inOffset,
  unsigned long             size,
  TimeValue                 durationPerSample,
  SampleDescriptionHandle   sampleDescriptionH,
  long                      numberOfSamples,
  short                     sampleFlags,
  TimeValue *               sampleTime)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddMediaSampleReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
AddMediaSampleReference(
  Media                     theMedia,
  long                      dataOffset,
  unsigned long             size,
  TimeValue                 durationPerSample,
  SampleDescriptionHandle   sampleDescriptionH,
  long                      numberOfSamples,
  short                     sampleFlags,
  TimeValue *               sampleTime)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddMediaSampleReferences()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
AddMediaSampleReferences(
  Media                     theMedia,
  SampleDescriptionHandle   sampleDescriptionH,
  long                      numberOfSamples,
  SampleReferencePtr        sampleRefs,
  TimeValue *               sampleTime)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddMediaSampleReferences64()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
AddMediaSampleReferences64(
  Media                     theMedia,
  SampleDescriptionHandle   sampleDescriptionH,
  long                      numberOfSamples,
  SampleReference64Ptr      sampleRefs,
  TimeValue *               sampleTime)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ExtendMediaDecodeDurationToDisplayEndTime()
 *  
 *  Summary:
 *    Prepares a media for the addition of a completely new sequence of
 *    samples by ensuring that the media display end time is not later
 *    than the media decode end time.
 *  
 *  Discussion:
 *    After adding a complete, well-formed set of samples to a media,
 *    the media's display end time should be the same as the media's
 *    decode end time (also called the media decode duration). 
 *    However, this is not necessarily the case after individual
 *    sample-adding operations, and hence it is possible for a media to
 *    be left with a display end time later than its decode end time --
 *    if adding a sequence of frames is aborted halfway, for example.
 *    
 *    This may make it difficult to add a new group of samples, because
 *    a well-formed group of samples' earliest display time should be
 *    the same as the first frame's decode time.  If such a well-formed
 *    group is added to an incompletely finished media, frames from the
 *    old and new groups frames might collide in display time. 
 *     ExtendMediaDecodeDurationToDisplayEndTime prevents any such
 *    collision or overlap by extending the last sample's decode
 *    duration as necessary.  It ensures that the next added sample
 *    will have a decode time no earlier than the media's display end
 *    time.  If this was already the case, it makes no change to the
 *    media. 
 *    You can call ExtendMediaDecodeDurationToDisplayEndTime before you
 *    begin adding samples to a media if you're not certain that the
 *    media was left in a well-finished state.  You do not need to call
 *    it before adding samples to a newly created media, nor should you
 *    call it in between samples from the same compression session.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation.  Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *    
 *    mediaChanged:
 *      Points to a variable which will be set to true if any samples
 *      in the media were adjusted, false otherwise. If you don't want
 *      to receive this information, set this parameter to NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSErr 
ExtendMediaDecodeDurationToDisplayEndTime(
  Media      theMedia,
  Boolean *  mediaChanged)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMediaSample2()
 *  
 *  Summary:
 *    Retrieves sample data from a media file. GetMediaSample2 extends
 *    and supercedes GetMediaSample.
 *  
 *  Discussion:
 *    GetMediaSample2 will only return multiple samples that all have
 *    the same decode duration per sample, the same display offset, the
 *    same sample description, and the same size per sample.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation.  Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *    
 *    dataOut:
 *      Points to a buffer to receive sample data. The buffer must be
 *      large enough to contain at least maxDataSize bytes. If you do
 *      not want to receive sample data, pass NULL.
 *    
 *    maxDataSize:
 *      The maximum number of bytes of data to receive.
 *    
 *    size:
 *      Points to a long integer to receive the number of bytes of
 *      sample data returned. Pass NULL if you are not interested this
 *      information.
 *    
 *    decodeTime:
 *      The decode time for which you are retrieving sample
 *      information. You must specify this value in the media's time
 *      scale.
 *    
 *    sampleDecodeTime:
 *      A pointer to a time value. The function updates this time value
 *      to indicate the actual decode time of the returned sample data.
 *      (The returned time may differ from the time you specified with
 *      the decodeTime parameter. This will occur if the time you
 *      specified falls in the middle of a sample.) If you are not
 *      interested in this information, set this parameter to NULL.
 *    
 *    decodeDurationPerSample:
 *      A pointer to a time value. The function updates this time value
 *      to indicate the decode duration of each of the returned
 *      samples. This time value is expressed in the media's time
 *      scale. Set this parameter to NULL if you don't want this
 *      information.
 *    
 *    displayOffset:
 *      A pointer to a time value. The function updates this time value
 *      to indicate the display offset of the returned sample.  This
 *      time value is expressed in the media's time scale. Set this
 *      parameter to NULL if you don't want this information.
 *    
 *    sampleDescriptionH:
 *      A handle to a SampleDescription structure. The function returns
 *      the sample description corresponding to the returned sample
 *      data.  The function resizes this handle as appropriate. If you
 *      don't want a SampleDescription structure, set this parameter to
 *      NULL.
 *    
 *    sampleDescriptionIndex:
 *      A pointer to a long integer. The function returns an index
 *      value to the SampleDescription structure that corresponds to
 *      the returned sample data. You can retrieve the structure by
 *      calling GetMediaSampleDescription and passing this index in the
 *      index parameter. If you don't want this information, set this
 *      parameter to NULL.
 *    
 *    maxNumberOfSamples:
 *      The maximum number of samples to be returned. The Movie Toolbox
 *      does not return more samples than you specify with this
 *      parameter. If you set this parameter to 0, the Movie Toolbox
 *      uses a value that is appropriate for the media, and returns
 *      that value in the field referenced by the numberOfSamples
 *      parameter.
 *    
 *    numberOfSamples:
 *      A pointer to a long integer. The function updates the field
 *      referred to by this parameter with the number of samples it
 *      actually returns. If you don't want this information, set this
 *      parameter to NULL.
 *    
 *    sampleFlags:
 *      A pointer to a short integer in which the function returns
 *      media sample flags for the returned samples. If you don't want
 *      this information, set this parameter to NULL.
 *  
 *  Result:
 *    An operating system result code. maxSizeToGrowTooSmall if the
 *    sample data is larger than maxDataSize.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSErr 
GetMediaSample2(
  Media                     theMedia,
  UInt8 *                   dataOut,
  ByteCount                 maxDataSize,
  ByteCount *               size,
  TimeValue64               decodeTime,
  TimeValue64 *             sampleDecodeTime,
  TimeValue64 *             decodeDurationPerSample,
  TimeValue64 *             displayOffset,
  SampleDescriptionHandle   sampleDescriptionH,
  ItemCount *               sampleDescriptionIndex,
  ItemCount                 maxNumberOfSamples,
  ItemCount *               numberOfSamples,
  MediaSampleFlags *        sampleFlags)                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMediaSample()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMediaSample(
  Media                     theMedia,
  Handle                    dataOut,
  long                      maxSizeToGrow,
  long *                    size,
  TimeValue                 time,
  TimeValue *               sampleTime,
  TimeValue *               durationPerSample,
  SampleDescriptionHandle   sampleDescriptionH,
  long *                    sampleDescriptionIndex,
  long                      maxNumberOfSample,
  long *                    numberOfSamples,
  short *                   sampleFlags)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CopyMediaMutableSampleTable()
 *  
 *  Summary:
 *    Obtains information about sample references in a media in the
 *    form of a sample table. CopyMediaMutableSampleTable supercedes
 *    GetMediaSampleReferences and GetMediaSampleReferences64.
 *  
 *  Discussion:
 *    When you are done with the returned sample table, release it with
 *    QTSampleTableRelease. 
 *    To find out how many samples were returned in the sample table,
 *    call QTSampleTableGetNumberOfSamples.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation.  Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *    
 *    startDecodeTime:
 *      The starting decode time of the sample references to be
 *      retrieved. You must specify this value in the media's time
 *      scale.
 *    
 *    sampleStartDecodeTime:
 *      A pointer to a time value. The function updates this time value
 *      to indicate the actual decode time of the first returned sample
 *      reference. (The returned time may differ from the time you
 *      specified with the startDecodeTime parameter.  This will occur
 *      if the time you specified falls in the middle of a sample.) If
 *      you are not interested in this information, set this parameter
 *      to NULL.
 *    
 *    maxNumberOfSamples:
 *      The maximum number of sample references to be returned. If you
 *      set this parameter to 0, the Movie Toolbox uses a value that is
 *      appropriate to the media.
 *    
 *    maxDecodeDuration:
 *      The maximum decode duration to be returned. The function does
 *      not return samples with greater decode duration than you
 *      specify with this parameter. If you set this parameter to 0,
 *      the Movie Toolbox uses a value that is appropriate for the
 *      media.
 *    
 *    sampleTableOut:
 *      A pointer to a sample table reference to receive the newly
 *      created mutable sample table.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSErr 
CopyMediaMutableSampleTable(
  Media                      theMedia,
  TimeValue64                startDecodeTime,
  TimeValue64 *              sampleStartDecodeTime,
  SInt64                     maxNumberOfSamples,
  TimeValue64                maxDecodeDuration,
  QTMutableSampleTableRef *  sampleTableOut)                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMediaSampleReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMediaSampleReference(
  Media                     theMedia,
  long *                    dataOffset,
  long *                    size,
  TimeValue                 time,
  TimeValue *               sampleTime,
  TimeValue *               durationPerSample,
  SampleDescriptionHandle   sampleDescriptionH,
  long *                    sampleDescriptionIndex,
  long                      maxNumberOfSamples,
  long *                    numberOfSamples,
  short *                   sampleFlags)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaSampleReferences()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMediaSampleReferences(
  Media                     theMedia,
  TimeValue                 time,
  TimeValue *               sampleTime,
  SampleDescriptionHandle   sampleDescriptionH,
  long *                    sampleDescriptionIndex,
  long                      maxNumberOfEntries,
  long *                    actualNumberofEntries,
  SampleReferencePtr        sampleRefs)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaSampleReferences64()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
GetMediaSampleReferences64(
  Media                     theMedia,
  TimeValue                 time,
  TimeValue *               sampleTime,
  SampleDescriptionHandle   sampleDescriptionH,
  long *                    sampleDescriptionIndex,
  long                      maxNumberOfEntries,
  long *                    actualNumberofEntries,
  SampleReference64Ptr      sampleRefs)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMediaPreferredChunkSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetMediaPreferredChunkSize(
  Media   theMedia,
  long    maxChunkSize)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaPreferredChunkSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMediaPreferredChunkSize(
  Media   theMedia,
  long *  maxChunkSize)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMediaShadowSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetMediaShadowSync(
  Media   theMedia,
  long    frameDiffSampleNum,
  long    syncSampleNum)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaShadowSync()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMediaShadowSync(
  Media   theMedia,
  long    frameDiffSampleNum,
  long *  syncSampleNum)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*************************
* Editing Routines
**************************/
/*
    When inserting media that might have nonzero display offsets into a track, use display time:
      InsertMediaIntoTrack( track, 
                            0,                                 // track start time
                            GetMediaDisplayStartTime( media ), // media start time
                            GetMediaDisplayDuration( media ), 
                            fixed1 );                          // normal speed
    It is safe to use these display time calls for media without display offsets.
*/
/*
 *  InsertMediaIntoTrack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
InsertMediaIntoTrack(
  Track       theTrack,
  TimeValue   trackStart,
  TimeValue   mediaTime,
  TimeValue   mediaDuration,
  Fixed       mediaRate)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InsertTrackSegment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
InsertTrackSegment(
  Track       srcTrack,
  Track       dstTrack,
  TimeValue   srcIn,
  TimeValue   srcDuration,
  TimeValue   dstIn)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InsertMovieSegment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
InsertMovieSegment(
  Movie       srcMovie,
  Movie       dstMovie,
  TimeValue   srcIn,
  TimeValue   srcDuration,
  TimeValue   dstIn)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InsertEmptyTrackSegment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
InsertEmptyTrackSegment(
  Track       dstTrack,
  TimeValue   dstIn,
  TimeValue   dstDuration)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InsertEmptyMovieSegment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
InsertEmptyMovieSegment(
  Movie       dstMovie,
  TimeValue   dstIn,
  TimeValue   dstDuration)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DeleteTrackSegment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DeleteTrackSegment(
  Track       theTrack,
  TimeValue   startTime,
  TimeValue   duration)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DeleteMovieSegment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DeleteMovieSegment(
  Movie       theMovie,
  TimeValue   startTime,
  TimeValue   duration)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ScaleTrackSegment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ScaleTrackSegment(
  Track       theTrack,
  TimeValue   startTime,
  TimeValue   oldDuration,
  TimeValue   newDuration)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ScaleMovieSegment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ScaleMovieSegment(
  Movie       theMovie,
  TimeValue   startTime,
  TimeValue   oldDuration,
  TimeValue   newDuration)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*************************
* Hi-level Editing Routines
**************************/
/*
 *  CutMovieSelection()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Movie 
CutMovieSelection(Movie theMovie)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CopyMovieSelection()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Movie 
CopyMovieSelection(Movie theMovie)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PasteMovieSelection()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
PasteMovieSelection(
  Movie   theMovie,
  Movie   src)                                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddMovieSelection()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
AddMovieSelection(
  Movie   theMovie,
  Movie   src)                                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ClearMovieSelection()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
ClearMovieSelection(Movie theMovie)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PasteHandleIntoMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
PasteHandleIntoMovie(
  Handle              h,
  OSType              handleType,
  Movie               theMovie,
  long                flags,
  ComponentInstance   userComp)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PutMovieIntoTypedHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
PutMovieIntoTypedHandle(
  Movie               theMovie,
  Track               targetTrack,
  OSType              handleType,
  Handle              publicMovie,
  TimeValue           start,
  TimeValue           dur,
  long                flags,
  ComponentInstance   userComp)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  IsScrapMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Component 
IsScrapMovie(Track targetTrack)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*************************
* Middle-level Editing Routines
**************************/
/*
 *  CopyTrackSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CopyTrackSettings(
  Track   srcTrack,
  Track   dstTrack)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CopyMovieSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CopyMovieSettings(
  Movie   srcMovie,
  Movie   dstMovie)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddEmptyTrackToMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
AddEmptyTrackToMovie(
  Track    srcTrack,
  Movie    dstMovie,
  Handle   dataRef,
  OSType   dataRefType,
  Track *  dstTrack)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


enum {
  kQTCloneShareSamples          = 1 << 0,
  kQTCloneDontCopyEdits         = 1 << 1
};

/*
 *  AddClonedTrackToMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern OSErr 
AddClonedTrackToMovie(
  Track    srcTrack,
  Movie    dstMovie,
  long     flags,
  Track *  dstTrack)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*************************
* movie & track edit state routines
**************************/
/*
 *  NewMovieEditState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern MovieEditState 
NewMovieEditState(Movie theMovie)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  UseMovieEditState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
UseMovieEditState(
  Movie            theMovie,
  MovieEditState   toState)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeMovieEditState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DisposeMovieEditState(MovieEditState state)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewTrackEditState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TrackEditState 
NewTrackEditState(Track theTrack)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  UseTrackEditState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
UseTrackEditState(
  Track            theTrack,
  TrackEditState   state)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeTrackEditState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DisposeTrackEditState(TrackEditState state)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*************************
* track reference routines
**************************/
/*
 *  AddTrackReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
AddTrackReference(
  Track    theTrack,
  Track    refTrack,
  OSType   refType,
  long *   addedIndex)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DeleteTrackReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DeleteTrackReference(
  Track    theTrack,
  OSType   refType,
  long     index)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTrackReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetTrackReference(
  Track    theTrack,
  Track    refTrack,
  OSType   refType,
  long     index)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Track 
GetTrackReference(
  Track    theTrack,
  OSType   refType,
  long     index)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetNextTrackReferenceType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSType 
GetNextTrackReferenceType(
  Track    theTrack,
  OSType   refType)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackReferenceCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetTrackReferenceCount(
  Track    theTrack,
  OSType   refType)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*************************
* high level file conversion routines
**************************/
/*
 *  ConvertFileToMovieFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ConvertFileToMovieFile(
  const FSSpec *      inputFile,
  const FSSpec *      outputFile,
  OSType              creator,
  ScriptCode          scriptTag,
  short *             resID,
  long                flags,
  ComponentInstance   userComp,
  MovieProgressUPP    proc,
  long                refCon)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ConvertMovieToFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ConvertMovieToFile(
  Movie               theMovie,
  Track               onlyTrack,
  FSSpec *            outputFile,
  OSType              fileType,
  OSType              creator,
  ScriptCode          scriptTag,
  short *             resID,
  long                flags,
  ComponentInstance   userComp)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ConvertMovieToDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
ConvertMovieToDataRef(
  Movie               m,
  Track               onlyTrack,
  Handle              dataRef,
  OSType              dataRefType,
  OSType              fileType,
  OSType              creator,
  long                flags,
  ComponentInstance   userComp)                               AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  ConvertDataRefToMovieDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
ConvertDataRefToMovieDataRef(
  Handle              inputDataRef,
  OSType              inputDataRefType,
  Handle              outputDataRef,
  OSType              outputDataRefType,
  OSType              creator,
  long                flags,
  ComponentInstance   userComp,
  MovieProgressUPP    proc,
  long                refCon)                                 AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


enum {
  kGetMovieImporterValidateToFind = 1L << 0,
  kGetMovieImporterAllowNewFile = 1L << 1,
  kGetMovieImporterDontConsiderGraphicsImporters = 1L << 2,
  kGetMovieImporterDontConsiderFileOnlyImporters = 1L << 6,
  kGetMovieImporterAutoImportOnly = 1L << 10 /* reject aggressive movie importers which have dontAutoFileMovieImport set*/
};

/*
 *  GetMovieImporterForDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMovieImporterForDataRef(
  OSType       dataRefType,
  Handle       dataRef,
  long         flags,
  Component *  importer)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



enum {
  kQTGetMIMETypeInfoIsQuickTimeMovieType = 'moov', /* info is a pointer to a Boolean*/
  kQTGetMIMETypeInfoIsUnhelpfulType = 'dumb' /* info is a pointer to a Boolean*/
};

/*
 *  QTGetMIMETypeInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern OSErr 
QTGetMIMETypeInfo(
  const char *  mimeStringStart,
  short         mimeStringLength,
  OSType        infoSelector,
  void *        infoDataPtr,
  long *        infoDataSize)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/****************************
* Movie importer properties
*****************************/

/*
 */
enum {
  kQTPropertyClass_MovieImporter = 'eat ',

  /*
   * kQTMovieImporterPropertyID_AllowMediaOptimization: Value is
   * Boolean (get/set) Allow QuickTime importers to optimize the media
   * representation during import. This may create media that is not
   * fully compatible with applications that use older low-level APIs
   * to access and manipulate media samples.  For instance, this
   * property allows the MP3 importer to create VBR sample tables,
   * which may be incompatible with applications that use
   * GetMediaSample and SoundConverter to manually decode audio samples.
   */
  kQTMovieImporterPropertyID_AllowMediaOptimization = 'amop' /* Boolean*/
};


/*************************
* Movie Timebase Conversion Routines
**************************/
/*
 *  TrackTimeToMediaDisplayTime()
 *  
 *  Summary:
 *    Converts a track's time value to a display time value that is
 *    appropriate to the track's media, using the track's edit list.
 *    This is a 64-bit replacement for TrackTimeToMediaTime.
 *  
 *  Discussion:
 *    This function maps the track time through the track's edit list
 *    to come up with the media time. This time value contains the
 *    track's time value according to the media's time coordinate
 *    system. If the time you specified lies outside of the movie's
 *    active segment or corresponds to empty space in the track, this
 *    function returns a value of -1. Hence you can use it to determine
 *    whether a specified track edit is empty.
 *  
 *  Parameters:
 *    
 *    value:
 *      The track's time value; must be expressed in the time scale of
 *      the movie that contains the track.
 *    
 *    theTrack:
 *      The track for this operation.  Your application obtains this
 *      track identifier from such functions as NewMovieTrack and
 *      GetMovieTrack.
 *  
 *  Result:
 *    The corresponding time in media display time, in the media's time
 *    coordinate system. If the track time corresponds to empty space,
 *    this function returns a value of -1.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern TimeValue64 
TrackTimeToMediaDisplayTime(
  TimeValue64   value,
  Track         theTrack)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  TrackTimeToMediaTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeValue 
TrackTimeToMediaTime(
  TimeValue   value,
  Track       theTrack)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackEditRate64()
 *  
 *  Summary:
 *    Returns the rate of the track edit of a specified track at an
 *    indicated time. This is a 64-bit replacement for GetTrackEditRate.
 *  
 *  Discussion:
 *    This function is useful if you are stepping through track edits
 *    directly in your application or if you are a client of
 *    QuickTime's base media handler.
 *  
 *  Parameters:
 *    
 *    theTrack:
 *      The track identifier for which the rate of a track edit (at the
 *      time given in the atTime parameter) is to be determined.
 *    
 *    atTime:
 *      Indicates a time value at which the rate of a track edit (of a
 *      track identified in the parameter theTrack) is to be determined.
 *  
 *  Result:
 *    The rate of the track edit of the specified track at the
 *    specified time.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern Fixed 
GetTrackEditRate64(
  Track         theTrack,
  TimeValue64   atTime)                                       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetTrackEditRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Fixed 
GetTrackEditRate(
  Track       theTrack,
  TimeValue   atTime)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*************************
* Miscellaneous Routines
**************************/

/*
 *  GetMovieDataSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetMovieDataSize(
  Movie       theMovie,
  TimeValue   startTime,
  TimeValue   duration)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieDataSize64()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
GetMovieDataSize64(
  Movie       theMovie,
  TimeValue   startTime,
  TimeValue   duration,
  wide *      dataSize)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackDataSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetTrackDataSize(
  Track       theTrack,
  TimeValue   startTime,
  TimeValue   duration)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackDataSize64()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
GetTrackDataSize64(
  Track       theTrack,
  TimeValue   startTime,
  TimeValue   duration,
  wide *      dataSize)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaDataSizeTime64()
 *  
 *  Summary:
 *    Determines the size, in bytes, of the sample data in a media
 *    segment. This function uses 64-bit time values and returns a
 *    64-bit size.
 *  
 *  Discussion:
 *    The only difference between this function and GetMediaDataSize64
 *    is that it uses 64-bit time values.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation.  Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *    
 *    startDisplayTime:
 *      A time value specifying the starting point of the segment in
 *      media display time.
 *    
 *    displayDuration:
 *      A time value that specifies the duration of the segment in
 *      media display time.
 *    
 *    dataSize:
 *      Points to a variable to receive the size, in bytes, of the
 *      sample data in the defined media segment.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSErr 
GetMediaDataSizeTime64(
  Media         theMedia,
  TimeValue64   startDisplayTime,
  TimeValue64   displayDuration,
  SInt64 *      dataSize)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMediaDataSize()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetMediaDataSize(
  Media       theMedia,
  TimeValue   startTime,
  TimeValue   duration)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaDataSize64()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
GetMediaDataSize64(
  Media       theMedia,
  TimeValue   startTime,
  TimeValue   duration,
  wide *      dataSize)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PtInMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Boolean 
PtInMovie(
  Movie   theMovie,
  Point   pt)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PtInTrack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Boolean 
PtInTrack(
  Track   theTrack,
  Point   pt)                                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*************************
* Group Selection Routines
**************************/

/*
 *  SetMovieLanguage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieLanguage(
  Movie   theMovie,
  long    language)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*************************
* User Data
**************************/

/*
 *  GetUserData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetUserData(
  UserData   theUserData,
  Handle     data,
  OSType     udType,
  long       index)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddUserData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
AddUserData(
  UserData   theUserData,
  Handle     data,
  OSType     udType)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RemoveUserData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
RemoveUserData(
  UserData   theUserData,
  OSType     udType,
  long       index)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CountUserDataType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern short 
CountUserDataType(
  UserData   theUserData,
  OSType     udType)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetNextUserDataType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetNextUserDataType(
  UserData   theUserData,
  OSType     udType)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetUserDataItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetUserDataItem(
  UserData   theUserData,
  void *     data,
  long       size,
  OSType     udType,
  long       index)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetUserDataItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetUserDataItem(
  UserData   theUserData,
  void *     data,
  long       size,
  OSType     udType,
  long       index)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddUserDataText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
AddUserDataText(
  UserData   theUserData,
  Handle     data,
  OSType     udType,
  long       index,
  short      itlRegionTag)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetUserDataText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetUserDataText(
  UserData   theUserData,
  Handle     data,
  OSType     udType,
  long       index,
  short      itlRegionTag)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RemoveUserDataText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
RemoveUserDataText(
  UserData   theUserData,
  OSType     udType,
  long       index,
  short      itlRegionTag)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewUserData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
NewUserData(UserData * theUserData)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeUserData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DisposeUserData(UserData theUserData)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewUserDataFromHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
NewUserDataFromHandle(
  Handle      h,
  UserData *  theUserData)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  PutUserDataIntoHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
PutUserDataIntoHandle(
  UserData   theUserData,
  Handle     h)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



enum {
  kQTCopyUserDataReplace        = 'rplc', /* Delete all destination user data items and then add source user data items */
  kQTCopyUserDataMerge          = 'merg' /* Add source user data items to destination user data */
};

/*
 *  CopyMovieUserData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
CopyMovieUserData(
  Movie    srcMovie,
  Movie    dstMovie,
  OSType   copyRule)                                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  CopyTrackUserData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
CopyTrackUserData(
  Track    srcTrack,
  Track    dstTrack,
  OSType   copyRule)                                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  CopyMediaUserData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
CopyMediaUserData(
  Media    srcMedia,
  Media    dstMedia,
  OSType   copyRule)                                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  CopyUserData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
CopyUserData(
  UserData   srcUserData,
  UserData   dstUserData,
  OSType     copyRule)                                        AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
 *  SetMoviePropertyAtom()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern OSErr 
SetMoviePropertyAtom(
  Movie             theMovie,
  QTAtomContainer   propertyAtom)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMoviePropertyAtom()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern OSErr 
GetMoviePropertyAtom(
  Movie              theMovie,
  QTAtomContainer *  propertyAtom)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaNextInterestingDecodeTime()
 *  
 *  Summary:
 *    Searches for decode times of interest in a media.
 *  
 *  Discussion:
 *    This function takes the same flags as GetMediaNextInterestingTime.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation.  Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *    
 *    interestingTimeFlags:
 *      Contains flags that determine the search criteria. Note that
 *      you may set only one of the nextTimeMediaSample,
 *      nextTimeMediaEdit or nextTimeSyncSample flags to 1.  Set unused
 *      flags to 0.
 *    
 *    decodeTime:
 *      Specifies a time value that establishes the starting point for
 *      the search. This time value must be expressed in the media's
 *      time scale.
 *    
 *    rate:
 *      The search direction. Negative values cause the Movie Toolbox
 *      to search backward from the starting point specified in the
 *      decodeTime parameter. Other values cause a forward search.
 *    
 *    interestingDecodeTime:
 *      A pointer to a time value. The Movie Toolbox returns the first
 *      decode time value it finds that meets the search criteria
 *      specified in the flags parameter. This time value is in the
 *      media's time scale. If there are no times that meet the search
 *      criteria you specify, the Movie Toolbox sets this value to -1.
 *      Set this parameter to NULL if you are not interested in this
 *      information.
 *    
 *    interestingDecodeDuration:
 *      A pointer to a time value. The Movie Toolbox returns the decode
 *      duration of the interesting time. This time value is in the
 *      media's time coordinate system. Set this parameter to NULL if
 *      you don't want this information; this lets the function work
 *      faster.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern void 
GetMediaNextInterestingDecodeTime(
  Media          theMedia,
  short          interestingTimeFlags,
  TimeValue64    decodeTime,
  Fixed          rate,
  TimeValue64 *  interestingDecodeTime,
  TimeValue64 *  interestingDecodeDuration)                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMediaNextInterestingDisplayTime()
 *  
 *  Summary:
 *    Searches for display times of interest in a media.
 *  
 *  Discussion:
 *    This function takes the same flags as GetMediaNextInterestingTime.
 *  
 *  Parameters:
 *    
 *    theMedia:
 *      The media for this operation.  Your application obtains this
 *      media identifier from such functions as NewTrackMedia and
 *      GetTrackMedia.
 *    
 *    interestingTimeFlags:
 *      Contains flags that determine the search criteria. Note that
 *      you may set only one of the nextTimeMediaSample,
 *      nextTimeMediaEdit or nextTimeSyncSample flags to 1. Set unused
 *      flags to 0.
 *    
 *    displayTime:
 *      Specifies a time value that establishes the starting point for
 *      the search. This time value must be expressed in the media's
 *      time scale.
 *    
 *    rate:
 *      The search direction. Negative values cause the Movie Toolbox
 *      to search backward from the starting point specified in the
 *      time parameter. Other values cause a forward search.
 *    
 *    interestingDisplayTime:
 *      A pointer to a time value. The Movie Toolbox returns the first
 *      display time value it finds that meets the search criteria
 *      specified in the flags parameter. This time value is in the
 *      media's time scale. If there are no times that meet the search
 *      criteria you specify, the Movie Toolbox sets this value to -1.
 *      Set this parameter to NULL if you are not interested in this
 *      information.
 *    
 *    interestingDisplayDuration:
 *      A pointer to a time value. The Movie Toolbox returns the
 *      display duration of the interesting time. This time value is in
 *      the media's time coordinate system. Set this parameter to NULL
 *      if you don't want this information; this lets the function work
 *      faster.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern void 
GetMediaNextInterestingDisplayTime(
  Media          theMedia,
  short          interestingTimeFlags,
  TimeValue64    displayTime,
  Fixed          rate,
  TimeValue64 *  interestingDisplayTime,
  TimeValue64 *  interestingDisplayDuration)                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMediaNextInterestingTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetMediaNextInterestingTime(
  Media        theMedia,
  short        interestingTimeFlags,
  TimeValue    time,
  Fixed        rate,
  TimeValue *  interestingTime,
  TimeValue *  interestingDuration)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackNextInterestingTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetTrackNextInterestingTime(
  Track        theTrack,
  short        interestingTimeFlags,
  TimeValue    time,
  Fixed        rate,
  TimeValue *  interestingTime,
  TimeValue *  interestingDuration)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieNextInterestingTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetMovieNextInterestingTime(
  Movie           theMovie,
  short           interestingTimeFlags,
  short           numMediaTypes,
  const OSType *  whichMediaTypes,
  TimeValue       time,
  Fixed           rate,
  TimeValue *     interestingTime,
  TimeValue *     interestingDuration)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  CreateMovieFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CreateMovieFile(
  const FSSpec *  fileSpec,
  OSType          creator,
  ScriptCode      scriptTag,
  long            createMovieFileFlags,
  short *         resRefNum,
  Movie *         newmovie)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  OpenMovieFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
OpenMovieFile(
  const FSSpec *  fileSpec,
  short *         resRefNum,
  SInt8           permission)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CloseMovieFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CloseMovieFile(short resRefNum)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DeleteMovieFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
DeleteMovieFile(const FSSpec * fileSpec)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewMovieFromFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
NewMovieFromFile(
  Movie *     theMovie,
  short       resRefNum,
  short *     resId,                   /* can be NULL */
  StringPtr   resName,
  short       newMovieFlags,
  Boolean *   dataRefWasChanged)       /* can be NULL */      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewMovieFromHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
NewMovieFromHandle(
  Movie *    theMovie,
  Handle     h,
  short      newMovieFlags,
  Boolean *  dataRefWasChanged)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewMovieFromDataFork()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
NewMovieFromDataFork(
  Movie *    theMovie,
  short      fRefNum,
  long       fileOffset,
  short      newMovieFlags,
  Boolean *  dataRefWasChanged)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewMovieFromDataFork64()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
NewMovieFromDataFork64(
  Movie *       theMovie,
  long          fRefNum,
  const wide *  fileOffset,
  short         newMovieFlags,
  Boolean *     dataRefWasChanged)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewMovieFromUserProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
NewMovieFromUserProc(
  Movie *       m,
  short         flags,
  Boolean *     dataRefWasChanged,
  GetMovieUPP   getProc,
  void *        refCon,
  Handle        defaultDataRef,
  OSType        dataRefType)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewMovieFromDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
NewMovieFromDataRef(
  Movie *  m,
  short    flags,
  short *  id,
  Handle   dataRef,
  OSType   dataRefType)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewMovieFromStorageOffset()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
NewMovieFromStorageOffset(
  Movie *       theMovie,
  DataHandler   dh,
  const wide *  fileOffset,
  short         newMovieFlags,
  Boolean *     dataRefWasChanged)                            AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  NewMovieForDataRefFromHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
NewMovieForDataRefFromHandle(
  Movie *    theMovie,
  Handle     h,
  short      newMovieFlags,
  Boolean *  dataRefWasChanged,
  Handle     dataRef,
  OSType     dataRefType)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  AddMovieResource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
AddMovieResource(
  Movie              theMovie,
  short              resRefNum,
  short *            resId,
  ConstStr255Param   resName)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  UpdateMovieResource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
UpdateMovieResource(
  Movie              theMovie,
  short              resRefNum,
  short              resId,
  ConstStr255Param   resName)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RemoveMovieResource()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
RemoveMovieResource(
  short   resRefNum,
  short   resId)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CreateMovieStorage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
CreateMovieStorage(
  Handle         dataRef,
  OSType         dataRefType,
  OSType         creator,
  ScriptCode     scriptTag,
  long           createMovieFileFlags,
  DataHandler *  outDataHandler,
  Movie *        newmovie)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  OpenMovieStorage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
OpenMovieStorage(
  Handle         dataRef,
  OSType         dataRefType,
  long           flags,
  DataHandler *  outDataHandler)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  CloseMovieStorage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
CloseMovieStorage(DataHandler dh)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  DeleteMovieStorage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
DeleteMovieStorage(
  Handle   dataRef,
  OSType   dataRefType)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  AddMovieToStorage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
AddMovieToStorage(
  Movie         theMovie,
  DataHandler   dh)                                           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  UpdateMovieInStorage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
UpdateMovieInStorage(
  Movie         theMovie,
  DataHandler   dh)                                           AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HasMovieChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Boolean 
HasMovieChanged(Movie theMovie)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ClearMovieChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
ClearMovieChanged(Movie theMovie)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieDefaultDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetMovieDefaultDataRef(
  Movie    theMovie,
  Handle   dataRef,
  OSType   dataRefType)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieDefaultDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMovieDefaultDataRef(
  Movie     theMovie,
  Handle *  dataRef,
  OSType *  dataRefType)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieAnchorDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern OSErr 
SetMovieAnchorDataRef(
  Movie    theMovie,
  Handle   dataRef,
  OSType   dataRefType)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieAnchorDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern OSErr 
GetMovieAnchorDataRef(
  Movie     theMovie,
  Handle *  dataRef,
  OSType *  dataRefType,
  long *    outFlags)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieColorTable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetMovieColorTable(
  Movie        theMovie,
  CTabHandle   ctab)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieColorTable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMovieColorTable(
  Movie         theMovie,
  CTabHandle *  ctab)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlattenMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
FlattenMovie(
  Movie              theMovie,
  long               movieFlattenFlags,
  const FSSpec *     theFile,
  OSType             creator,
  ScriptCode         scriptTag,
  long               createMovieFileFlags,
  short *            resId,
  ConstStr255Param   resName)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlattenMovieData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Movie 
FlattenMovieData(
  Movie           theMovie,
  long            movieFlattenFlags,
  const FSSpec *  theFile,
  OSType          creator,
  ScriptCode      scriptTag,
  long            createMovieFileFlags)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlattenMovieDataToDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern Movie 
FlattenMovieDataToDataRef(
  Movie        theMovie,
  long         movieFlattenFlags,
  Handle       dataRef,
  OSType       dataRefType,
  OSType       creator,
  ScriptCode   scriptTag,
  long         createMovieFileFlags)                          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  SetMovieProgressProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieProgressProc(
  Movie              theMovie,
  MovieProgressUPP   p,
  long               refcon)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieProgressProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern void 
GetMovieProgressProc(
  Movie               theMovie,
  MovieProgressUPP *  p,
  long *              refcon)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CreateShortcutMovieFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
CreateShortcutMovieFile(
  const FSSpec *  fileSpec,
  OSType          creator,
  ScriptCode      scriptTag,
  long            createMovieFileFlags,
  Handle          targetDataRef,
  OSType          targetDataRefType)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MovieSearchText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
MovieSearchText(
  Movie        theMovie,
  Ptr          text,
  long         size,
  long         searchFlags,
  Track *      searchTrack,
  TimeValue *  searchTime,
  long *       searchOffset)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetPosterBox()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetPosterBox(
  Movie   theMovie,
  Rect *  boxRect)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetPosterBox()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetPosterBox(
  Movie         theMovie,
  const Rect *  boxRect)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieSegmentDisplayBoundsRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern RgnHandle 
GetMovieSegmentDisplayBoundsRgn(
  Movie       theMovie,
  TimeValue   time,
  TimeValue   duration)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackSegmentDisplayBoundsRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern RgnHandle 
GetTrackSegmentDisplayBoundsRgn(
  Track       theTrack,
  TimeValue   time,
  TimeValue   duration)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieCoverProcs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieCoverProcs(
  Movie              theMovie,
  MovieRgnCoverUPP   uncoverProc,
  MovieRgnCoverUPP   coverProc,
  long               refcon)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieCoverProcs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMovieCoverProcs(
  Movie               theMovie,
  MovieRgnCoverUPP *  uncoverProc,
  MovieRgnCoverUPP *  coverProc,
  long *              refcon)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackStatus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GetTrackStatus(Track theTrack)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieStatus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
GetMovieStatus(
  Movie    theMovie,
  Track *  firstProblemTrack)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


enum {
  kMovieLoadStateError          = -1L,
  kMovieLoadStateLoading        = 1000,
  kMovieLoadStateLoaded         = 2000,
  kMovieLoadStatePlayable       = 10000,
  kMovieLoadStatePlaythroughOK  = 20000,
  kMovieLoadStateComplete       = 100000L
};

/*
 *  GetMovieLoadState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern long 
GetMovieLoadState(Movie theMovie)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/****
    Thread related Movie routines
****/
/*
 *  AttachMovieToCurrentThread()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
AttachMovieToCurrentThread(Movie m)                           AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  DetachMovieFromCurrentThread()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
DetachMovieFromCurrentThread(Movie m)                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  GetMovieThreadAttachState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
GetMovieThreadAttachState(
  Movie      m,
  Boolean *  outAttachedToCurrentThread,
  Boolean *  outAttachedToAnyThread)                          AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/****
    CanQuickTimeOpenFile, etc.
****/
/* Input flags for CanQuickTimeOpenFile/DataRef */
enum {
  kQTDontUseDataToFindImporter  = 1L << 0,
  kQTDontLookForMovieImporterIfGraphicsImporterFound = 1L << 1,
  kQTAllowOpeningStillImagesAsMovies = 1L << 2,
  kQTAllowImportersThatWouldCreateNewFile = 1L << 3,
  kQTAllowAggressiveImporters   = 1L << 4 /* eg, TEXT and PICT movie importers*/
};

/* Determines whether the file could be opened using a graphics importer or opened in place as a movie. */
/*
 *  CanQuickTimeOpenFile()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern OSErr 
CanQuickTimeOpenFile(
  FSSpecPtr   fileSpec,
  OSType      fileType,
  OSType      fileNameExtension,
  Boolean *   outCanOpenWithGraphicsImporter,
  Boolean *   outCanOpenAsMovie,
  Boolean *   outPreferGraphicsImporter,
  UInt32      inFlags)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* Determines whether the file could be opened using a graphics importer or opened in place as a movie. */
/*
 *  CanQuickTimeOpenDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern OSErr 
CanQuickTimeOpenDataRef(
  Handle     dataRef,
  OSType     dataRefType,
  Boolean *  outCanOpenWithGraphicsImporter,
  Boolean *  outCanOpenAsMovie,
  Boolean *  outPreferGraphicsImporter,
  UInt32     inFlags)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/****
    Data Reference Utilities
****/
enum {
  kQTNativeDefaultPathStyle     = -1,
  kQTPOSIXPathStyle             = 0,
  kQTHFSPathStyle               = 1,
  kQTWindowsPathStyle           = 2
};


typedef unsigned long                   QTPathStyle;
/*
 *  QTNewDataReferenceFromFSRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
QTNewDataReferenceFromFSRef(
  const FSRef *  fileRef,
  UInt32         flags,
  Handle *       outDataRef,
  OSType *       outDataRefType)                              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTNewDataReferenceFromFSRefCFString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
QTNewDataReferenceFromFSRefCFString(
  const FSRef *  directoryRef,
  CFStringRef    fileName,
  UInt32         flags,
  Handle *       outDataRef,
  OSType *       outDataRefType)                              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTNewDataReferenceFromFSSpec()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
QTNewDataReferenceFromFSSpec(
  const FSSpec *  fsspec,
  UInt32          flags,
  Handle *        outDataRef,
  OSType *        outDataRefType)                             AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTNewDataReferenceWithDirectoryCFString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
QTNewDataReferenceWithDirectoryCFString(
  Handle        inDataRef,
  OSType        inDataRefType,
  CFStringRef   targetName,
  UInt32        flags,
  Handle *      outDataRef,
  OSType *      outDataRefType)                               AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTNewDataReferenceFromFullPathCFString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
QTNewDataReferenceFromFullPathCFString(
  CFStringRef   filePath,
  QTPathStyle   pathStyle,
  UInt32        flags,
  Handle *      outDataRef,
  OSType *      outDataRefType)                               AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTNewDataReferenceFromCFURL()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
QTNewDataReferenceFromCFURL(
  CFURLRef   url,
  UInt32     flags,
  Handle *   outDataRef,
  OSType *   outDataRefType)                                  AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTNewDataReferenceFromURLCFString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
QTNewDataReferenceFromURLCFString(
  CFStringRef   urlString,
  UInt32        flags,
  Handle *      outDataRef,
  OSType *      outDataRefType)                               AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  QTGetDataReferenceDirectoryDataReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
QTGetDataReferenceDirectoryDataReference(
  Handle    dataRef,
  OSType    dataRefType,
  UInt32    flags,
  Handle *  outDataRef,
  OSType *  outDataRefType)                                   AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTGetDataReferenceTargetNameCFString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
QTGetDataReferenceTargetNameCFString(
  Handle         dataRef,
  OSType         dataRefType,
  CFStringRef *  name)                                        AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTGetDataReferenceFullPathCFString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
QTGetDataReferenceFullPathCFString(
  Handle         dataRef,
  OSType         dataRefType,
  QTPathStyle    style,
  CFStringRef *  outPath)                                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  QTGetDataHandlerDirectoryDataReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
QTGetDataHandlerDirectoryDataReference(
  DataHandler   dh,
  UInt32        flags,
  Handle *      outDataRef,
  OSType *      outDataRefType)                               AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTGetDataHandlerTargetNameCFString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
QTGetDataHandlerTargetNameCFString(
  DataHandler    dh,
  CFStringRef *  fileName)                                    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTGetDataHandlerFullPathCFString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
QTGetDataHandlerFullPathCFString(
  DataHandler    dh,
  QTPathStyle    style,
  CFStringRef *  outPath)                                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;




/****
    Movie Controller support routines
****/
/*
 *  NewMovieController()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentInstance 
NewMovieController(
  Movie         theMovie,
  const Rect *  movieRect,
  long          someFlags)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeMovieController()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
DisposeMovieController(ComponentInstance mc)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ShowMovieInformation()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
ShowMovieInformation(
  Movie            theMovie,
  ModalFilterUPP   filterProc,
  long             refCon)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*****
    Scrap routines
*****/
/*
 *  PutMovieOnScrap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
PutMovieOnScrap(
  Movie   theMovie,
  long    movieScrapFlags)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewMovieFromScrap()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Movie 
NewMovieFromScrap(long newMovieFlags)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*****
    DataRef routines
*****/

/*
 *  GetMediaDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMediaDataRef(
  Media     theMedia,
  short     index,
  Handle *  dataRef,
  OSType *  dataRefType,
  long *    dataRefAttributes)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMediaDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetMediaDataRef(
  Media    theMedia,
  short    index,
  Handle   dataRef,
  OSType   dataRefType)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMediaDataRefAttributes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetMediaDataRefAttributes(
  Media   theMedia,
  short   index,
  long    dataRefAttributes)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddMediaDataRef()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
AddMediaDataRef(
  Media    theMedia,
  short *  index,
  Handle   dataRef,
  OSType   dataRefType)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaDataRefCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMediaDataRefCount(
  Media    theMedia,
  short *  count)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTNewAlias()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTNewAlias(
  const FSSpec *  fss,
  AliasHandle *   alias,
  Boolean         minimal)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*****
    Playback hint routines
*****/
/*
 *  SetMoviePlayHints()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMoviePlayHints(
  Movie   theMovie,
  long    flags,
  long    flagsMask)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMediaPlayHints()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMediaPlayHints(
  Media   theMedia,
  long    flags,
  long    flagsMask)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaPlayHints()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetMediaPlayHints(
  Media   theMedia,
  long *  flags)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*****
    Load time track hints
*****/
enum {
  preloadAlways                 = 1L << 0,
  preloadOnlyIfEnabled          = 1L << 1
};

/*
 *  SetTrackLoadSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTrackLoadSettings(
  Track       theTrack,
  TimeValue   preloadTime,
  TimeValue   preloadDuration,
  long        preloadFlags,
  long        defaultHints)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackLoadSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
GetTrackLoadSettings(
  Track        theTrack,
  TimeValue *  preloadTime,
  TimeValue *  preloadDuration,
  long *       preloadFlags,
  long *       defaultHints)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*****
    Big screen TV
*****/
enum {
  fullScreenHideCursor          = 1L << 0,
  fullScreenAllowEvents         = 1L << 1,
  fullScreenDontChangeMenuBar   = 1L << 2,
  fullScreenPreflightSize       = 1L << 3,
  fullScreenDontSwitchMonitorResolution = 1L << 4,
  fullScreenCaptureDisplay      = 1 << 5L, /* capturedisplay is a mac os x specific parameter */
  fullScreenCaptureAllDisplays  = 1 << 6L /* capturealldisplays is a mac os x specific parameter */
};

/*
 *  BeginFullScreen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
BeginFullScreen(
  Ptr *        restoreState,
  GDHandle     whichGD,
  short *      desiredWidth,
  short *      desiredHeight,
  WindowRef *  newWindow,
  RGBColor *   eraseColor,
  long         flags)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  EndFullScreen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
EndFullScreen(
  Ptr    fullState,
  long   flags)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*****
    Wired Actions
*****/
/* flags for MovieExecuteWiredActions*/
enum {
  movieExecuteWiredActionDontExecute = 1L << 0
};

/*
 *  AddMovieExecuteWiredActionsProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
AddMovieExecuteWiredActionsProc(
  Movie                         theMovie,
  MovieExecuteWiredActionsUPP   proc,
  void *                        refCon)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RemoveMovieExecuteWiredActionsProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
RemoveMovieExecuteWiredActionsProc(
  Movie                         theMovie,
  MovieExecuteWiredActionsUPP   proc,
  void *                        refCon)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MovieExecuteWiredActions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
MovieExecuteWiredActions(
  Movie             theMovie,
  long              flags,
  QTAtomContainer   actions)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*****
    Keyboard Navigation/Editable Text Field Support
*****/
/*
   Navigation Direction Constants
        for MediaNavigateTargetRefCon
*/
enum {
  kRefConNavigationNext         = 0,
  kRefConNavigationPrevious     = 1
};

/*
   Refcon Properties 
        for MediaRefConGetProerty/MediaRefConSetProperty
*/
enum {
  kRefConPropertyCanHaveFocus   = 1,    /* Boolean */
  kRefConPropertyHasFocus       = 2     /* Boolean */
};

/* media properties*/
enum {
  kTrackFocusCanEditFlag        = 'kedt',
  kTrackDefaultFocusFlags       = 'kfoc',
  kTrackFocusDefaultRefcon      = 'kref'
};

/* focus flags*/
enum {
  kTrackFocusOn                 = 1,
  kTrackHandlesTabs             = 2     /* this is reserved for a future release*/
};

/*****
    Flash track properties
*****/
enum {
  kFlashTrackPropertyAcceptAllClicks = 'clik' /* type of media property atom; data is a Boolean */
};

/*****
    Sprite Toolbox
*****/
enum {
  kBackgroundSpriteLayerNum     = 32767
};


/*  Sprite Properties*/
enum {
  kSpritePropertyMatrix         = 1,
  kSpritePropertyImageDescription = 2,
  kSpritePropertyImageDataPtr   = 3,
  kSpritePropertyVisible        = 4,
  kSpritePropertyLayer          = 5,
  kSpritePropertyGraphicsMode   = 6,
  kSpritePropertyImageDataSize  = 7,
  kSpritePropertyActionHandlingSpriteID = 8,
  kSpritePropertyCanBeHitTested = 9,
  kSpritePropertyImageIndex     = 100,
  kSpriteTrackPropertyBackgroundColor = 101,
  kSpriteTrackPropertyOffscreenBitDepth = 102,
  kSpriteTrackPropertySampleFormat = 103,
  kSpriteTrackPropertyScaleSpritesToScaleWorld = 104,
  kSpriteTrackPropertyHasActions = 105,
  kSpriteTrackPropertyVisible   = 106,
  kSpriteTrackPropertyQTIdleEventsFrequency = 107,
  kSpriteTrackPropertyAllSpritesHitTestingMode = 108,
  kSpriteTrackPropertyPreferredDepthInterpretationMode = 109,
  kSpriteImagePropertyRegistrationPoint = 1000,
  kSpriteImagePropertyGroupID   = 1001
};

/* values for kSpriteTrackPropertyPreferredDepthInterpretationMode*/
enum {
  kSpriteTrackPreferredDepthCompatibilityMode = 0,
  kSpriteTrackPreferredDepthModernMode = 1
};

/* values for kSpriteTrackPropertyAllSpritesHitTestingMode*/
enum {
  kSpriteHitTestUseSpritesOwnPropertiesMode = 0,
  kSpriteHitTestTreatAllSpritesAsHitTestableMode = 1,
  kSpriteHitTestTreatAllSpritesAsNotHitTestableMode = 2
};

/* special value for kSpriteTrackPropertyQTIdleEventsFrequency (the default)*/
enum {
  kNoQTIdleEvents               = -1
};

/* GetSpriteProperties for accessing invalid SpriteWorldRegion*/
enum {
  kGetSpriteWorldInvalidRegionAndLeaveIntact = -1L,
  kGetSpriteWorldInvalidRegionAndThenSetEmpty = -2L
};

/* flagsIn for SpriteWorldIdle*/
enum {
  kOnlyDrawToSpriteWorld        = 1L << 0,
  kSpriteWorldPreflight         = 1L << 1
};

/* flagsOut for SpriteWorldIdle*/
enum {
  kSpriteWorldDidDraw           = 1L << 0,
  kSpriteWorldNeedsToDraw       = 1L << 1
};

/* flags for sprite track sample format*/
enum {
  kKeyFrameAndSingleOverride    = 1L << 1,
  kKeyFrameAndAllOverrides      = 1L << 2
};

/* sprite world flags*/
enum {
  kScaleSpritesToScaleWorld     = 1L << 1,
  kSpriteWorldHighQuality       = 1L << 2,
  kSpriteWorldDontAutoInvalidate = 1L << 3,
  kSpriteWorldInvisible         = 1L << 4,
  kSpriteWorldDirtyInsteadOfFlush = 1L << 5
};

/*
 *  NewSpriteWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
NewSpriteWorld(
  SpriteWorld *  newSpriteWorld,
  GWorldPtr      destination,
  GWorldPtr      spriteLayer,
  RGBColor *     backgroundColor,
  GWorldPtr      background)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeSpriteWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
DisposeSpriteWorld(SpriteWorld theSpriteWorld)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetSpriteWorldClip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetSpriteWorldClip(
  SpriteWorld   theSpriteWorld,
  RgnHandle     clipRgn)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetSpriteWorldMatrix()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetSpriteWorldMatrix(
  SpriteWorld           theSpriteWorld,
  const MatrixRecord *  matrix)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetSpriteWorldGraphicsMode()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetSpriteWorldGraphicsMode(
  SpriteWorld       theSpriteWorld,
  long              mode,
  const RGBColor *  opColor)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteWorldIdle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SpriteWorldIdle(
  SpriteWorld   theSpriteWorld,
  long          flagsIn,
  long *        flagsOut)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InvalidateSpriteWorld()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
InvalidateSpriteWorld(
  SpriteWorld   theSpriteWorld,
  Rect *        invalidArea)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteWorldHitTest()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SpriteWorldHitTest(
  SpriteWorld   theSpriteWorld,
  long          flags,
  Point         loc,
  Sprite *      spriteHit)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteHitTest()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SpriteHitTest(
  Sprite     theSprite,
  long       flags,
  Point      loc,
  Boolean *  wasHit)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeAllSprites()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
DisposeAllSprites(SpriteWorld theSpriteWorld)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetSpriteWorldFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetSpriteWorldFlags(
  SpriteWorld   spriteWorld,
  long          flags,
  long          flagsMask)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  NewSprite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
NewSprite(
  Sprite *                 newSprite,
  SpriteWorld              itsSpriteWorld,
  ImageDescriptionHandle   idh,
  Ptr                      imageDataPtr,
  MatrixRecord *           matrix,
  Boolean                  visible,
  short                    layer)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeSprite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
DisposeSprite(Sprite theSprite)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  InvalidateSprite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
InvalidateSprite(Sprite theSprite)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetSpriteProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetSpriteProperty(
  Sprite   theSprite,
  long     propertyType,
  void *   propertyValue)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetSpriteProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetSpriteProperty(
  Sprite   theSprite,
  long     propertyType,
  void *   propertyValue)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*****
    QT Atom Data Support
*****/
enum {
  kParentAtomIsContainer        = 0
};

/* create and dispose QTAtomContainer objects*/

/*
 *  QTNewAtomContainer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTNewAtomContainer(QTAtomContainer * atomData)                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTDisposeAtomContainer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTDisposeAtomContainer(QTAtomContainer atomData)              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* locating nested atoms within QTAtomContainer container*/

/*
 *  QTGetNextChildType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern QTAtomType 
QTGetNextChildType(
  QTAtomContainer   container,
  QTAtom            parentAtom,
  QTAtomType        currentChildType)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTCountChildrenOfType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern short 
QTCountChildrenOfType(
  QTAtomContainer   container,
  QTAtom            parentAtom,
  QTAtomType        childType)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTFindChildByIndex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern QTAtom 
QTFindChildByIndex(
  QTAtomContainer   container,
  QTAtom            parentAtom,
  QTAtomType        atomType,
  short             index,
  QTAtomID *        id)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTFindChildByID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern QTAtom 
QTFindChildByID(
  QTAtomContainer   container,
  QTAtom            parentAtom,
  QTAtomType        atomType,
  QTAtomID          id,
  short *           index)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTNextChildAnyType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTNextChildAnyType(
  QTAtomContainer   container,
  QTAtom            parentAtom,
  QTAtom            currentChild,
  QTAtom *          nextChild)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* set a leaf atom's data*/
/*
 *  QTSetAtomData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTSetAtomData(
  QTAtomContainer   container,
  QTAtom            atom,
  long              dataSize,
  void *            atomData)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* extracting data*/
/*
 *  QTCopyAtomDataToHandle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTCopyAtomDataToHandle(
  QTAtomContainer   container,
  QTAtom            atom,
  Handle            targetHandle)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTCopyAtomDataToPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTCopyAtomDataToPtr(
  QTAtomContainer   container,
  QTAtom            atom,
  Boolean           sizeOrLessOK,
  long              size,
  void *            targetPtr,
  long *            actualSize)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTGetAtomTypeAndID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTGetAtomTypeAndID(
  QTAtomContainer   container,
  QTAtom            atom,
  QTAtomType *      atomType,
  QTAtomID *        id)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* extract a copy of an atom and all of it's children, caller disposes*/
/*
 *  QTCopyAtom()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTCopyAtom(
  QTAtomContainer    container,
  QTAtom             atom,
  QTAtomContainer *  targetContainer)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* obtaining direct reference to atom data*/
/*
 *  QTLockContainer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTLockContainer(QTAtomContainer container)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTGetAtomDataPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTGetAtomDataPtr(
  QTAtomContainer   container,
  QTAtom            atom,
  long *            dataSize,
  Ptr *             atomData)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTUnlockContainer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTUnlockContainer(QTAtomContainer container)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
   building QTAtomContainer trees
   creates and inserts new atom at specified index, existing atoms at or after index are moved toward end of list
   used for Top-Down tree creation
*/
/*
 *  QTInsertChild()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTInsertChild(
  QTAtomContainer   container,
  QTAtom            parentAtom,
  QTAtomType        atomType,
  QTAtomID          id,
  short             index,
  long              dataSize,
  void *            data,
  QTAtom *          newAtom)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* inserts children from childrenContainer as children of parentAtom*/
/*
 *  QTInsertChildren()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTInsertChildren(
  QTAtomContainer   container,
  QTAtom            parentAtom,
  QTAtomContainer   childrenContainer)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* destruction*/
/*
 *  QTRemoveAtom()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTRemoveAtom(
  QTAtomContainer   container,
  QTAtom            atom)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTRemoveChildren()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTRemoveChildren(
  QTAtomContainer   container,
  QTAtom            atom)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* replacement must be same type as target*/
/*
 *  QTReplaceAtom()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTReplaceAtom(
  QTAtomContainer   targetContainer,
  QTAtom            targetAtom,
  QTAtomContainer   replacementContainer,
  QTAtom            replacementAtom)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTSwapAtoms()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTSwapAtoms(
  QTAtomContainer   container,
  QTAtom            atom1,
  QTAtom            atom2)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTSetAtomID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTSetAtomID(
  QTAtomContainer   container,
  QTAtom            atom,
  QTAtomID          newID)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTGetAtomParent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern QTAtom 
QTGetAtomParent(
  QTAtomContainer   container,
  QTAtom            childAtom)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMediaPropertyAtom()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetMediaPropertyAtom(
  Media             theMedia,
  QTAtomContainer   propertyAtom)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMediaPropertyAtom()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMediaPropertyAtom(
  Media              theMedia,
  QTAtomContainer *  propertyAtom)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*****
    Tween Support
*****/
typedef struct TweenRecord              TweenRecord;
typedef CALLBACK_API( ComponentResult , TweenerDataProcPtr )(TweenRecord *tr, void *tweenData, long tweenDataSize, long dataDescriptionSeed, Handle dataDescription, ICMCompletionProcRecordPtr asyncCompletionProc, UniversalProcPtr transferProc, void *refCon);
typedef STACK_UPP_TYPE(TweenerDataProcPtr)                      TweenerDataUPP;
struct TweenRecord {
  long                version;

  QTAtomContainer     container;
  QTAtom              tweenAtom;
  QTAtom              dataAtom;
  Fixed               percent;

  TweenerDataUPP      dataProc;

  void *              private1;
  void *              private2;
};

struct TweenV1Record {
  long                version;

  QTAtomContainer     container;
  QTAtom              tweenAtom;
  QTAtom              dataAtom;
  Fixed               percent;

  TweenerDataUPP      dataProc;

  void *              private1;
  void *              private2;

  Fract               fractPercent;
};
typedef struct TweenV1Record            TweenV1Record;
enum {
  kTweenRecordNoFlags           = 0,
  kTweenRecordIsAtInterruptTime = 0x00000001
};

struct TweenV2Record {
  long                version;

  QTAtomContainer     container;
  QTAtom              tweenAtom;
  QTAtom              dataAtom;
  Fixed               percent;

  TweenerDataUPP      dataProc;

  void *              private1;
  void *              private2;

  Fract               fractPercent;

  long                flags;
};
typedef struct TweenV2Record            TweenV2Record;
/*
 *  QTNewTween()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTNewTween(
  QTTweener *       tween,
  QTAtomContainer   container,
  QTAtom            tweenAtom,
  TimeValue         maxTime)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTDisposeTween()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTDisposeTween(QTTweener tween)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTDoTween()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTDoTween(
  QTTweener        tween,
  TimeValue        atTime,
  Handle           result,
  long *           resultSize,
  TweenerDataUPP   tweenDataProc,
  void *           tweenDataRefCon)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    QTDoTweenPtr is an interrupt-safe version of QTDoTween.  It has the following limitations:
     - not all tween types support this call (those which must allocated memory), in which case they return codecUnimpErr.
     - the QTAtomContainer used for the tween must be locked
     - the dataSize must be large enough to contain the result
     - this call is not supported for sequence tweens, use interpolation tweens instead
*/
/*
 *  QTDoTweenPtr()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTDoTweenPtr(
  QTTweener   tween,
  TimeValue   atTime,
  Ptr         result,
  long        resultSize)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*****
    Preferences
*****/
/*
 *  GetQuickTimePreference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetQuickTimePreference(
  OSType             preferenceType,
  QTAtomContainer *  preferenceAtom)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetQuickTimePreference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetQuickTimePreference(
  OSType            preferenceType,
  QTAtomContainer   preferenceAtom)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*****
    Effects and dialog Support
*****/
/* atom types for entries in the effects list*/
enum {
  kEffectNameAtom               = 'name', /* name of effect */
  kEffectTypeAtom               = 'type', /* codec sub-type for effect */
  kEffectManufacturerAtom       = 'manu' /* codec manufacturer for effect */
};

struct QTParamPreviewRecord {
  long                sourceID;               /* 1 based source identifier*/
  PicHandle           sourcePicture;          /* picture for preview, must not dispose until dialog is disposed*/
};
typedef struct QTParamPreviewRecord     QTParamPreviewRecord;
typedef QTParamPreviewRecord *          QTParamPreviewPtr;
struct QTParamDialogEventRecord {
  EventRecord *       theEvent;               /* Event received by the dialog */
  DialogRef           whichDialog;            /* dialog that event was directed towards */
  short               itemHit;                /* dialog item which was hit */
};
typedef struct QTParamDialogEventRecord QTParamDialogEventRecord;
typedef QTParamDialogEventRecord *      QTParamDialogEventPtr;
struct QTParamFetchPreviewRecord {
  GWorldPtr           theWorld;               /* the world into which to draw the preview */
  Fixed               percentage;             /* frame percentage (from 0.0 - 1.0) to be drawn */
};
typedef struct QTParamFetchPreviewRecord QTParamFetchPreviewRecord;
typedef QTParamFetchPreviewRecord *     QTParamFetchPreviewPtr;

#if TARGET_API_MAC_CARBON
/* Only available on OS X */
enum {
 kEffectParentWindowCarbon = 'carb'
};
struct QTEventLoopDescriptionRecord
  {
  long                    recordSize;     /* must be == sizeof(QTEventLoopDescriptionRecord) */
  long                    windowRefKind;  /* kind of window reference */
 void *                  parentWindow;   /* parent window (for sheets) or NIL to use Carbon FrontWindow() */
    void *                  eventTarget;    /* EventTargetRef to receive kHICommandOK and kHICommandCancel */
};

typedef struct QTEventLoopDescriptionRecord QTEventLoopDescriptionRecord, *QTEventLoopDescriptionPtr;
#endif


enum {
  pdActionConfirmDialog         = 1,    /* no param*/
  pdActionSetAppleMenu          = 2,    /* param is MenuRef*/
  pdActionSetEditMenu           = 3,    /* param is MenuRef*/
  pdActionGetDialogValues       = 4,    /* param is QTAtomContainer*/
  pdActionSetPreviewUserItem    = 5,    /* param is long*/
  pdActionSetPreviewPicture     = 6,    /* param is QTParamPreviewPtr;*/
  pdActionSetColorPickerEventProc = 7,  /* param is UserEventUPP*/
  pdActionSetDialogTitle        = 8,    /* param is StringPtr */
  pdActionGetSubPanelMenu       = 9,    /* param is MenuRef* */
  pdActionActivateSubPanel      = 10,   /* param is long */
  pdActionConductStopAlert      = 11,   /* param is StringPtr */
  pdActionModelessCallback      = 12,   /* param is QTParamDialogEventPtr */
  pdActionFetchPreview          = 13,   /* param is QTParamFetchPreviewPtr */
  pdActionSetDialogSettings     = 14,   /* param is QTAtomContainer */
  pdActionGetDialogSettings     = 15,   /* param is QTAtomContainer */
  pdActionGetNextSample         = 16,   /* param is QTAtomContainer with effect sample to change - createdDialog may be NIL */
  pdActionGetPreviousSample     = 17,   /* param is QTAtomContainer with effect sample to change - createdDialog may be NIL */
  pdActionCompactSample         = 18,   /* param is QTAtomContainer with effect sample to compact, - createdDialog may be NIL */
  pdActionSetEditCallout        = 19,   /* param is QTParamPreviewCalloutPtr, can be NIL */
  pdActionSetSampleTime         = 20,   /* param is QTParamSampleTimePtr, can be NIL */
  pdActionDoEditCommand         = 21,   /* param is long with menu command (ie, mcMenuCut etc) */
  pdActionGetSubPanelMenuValue  = 22,   /* param is long and returns current sub-panel value selected by the effect */
                                        /* Action codes and typedefs used for custom controls within effects */
  pdActionCustomNewControl      = 23,   /* param is QTCustomControlNewPtr */
  pdActionCustomDisposeControl  = 24,   /* param is QTCustomControlNewPtr */
  pdActionCustomPositionControl = 25,   /* param is QTCustomControlPositionControlPtr */
  pdActionCustomShowHideControl = 26,   /* param is QTCustomControlShowHideControlPtr */
  pdActionCustomHandleEvent     = 27,   /* param is QTCustomControlHandleEventPtr */
  pdActionCustomSetFocus        = 28,   /* param is QTCustomControlSetFocusPtr */
  pdActionCustomSetEditMenu     = 29,   /* param is QTCustomControlSetEditMenuPtr */
  pdActionCustomSetPreviewPicture = 30, /* param is QTCustomControlSetPreviewPicturePtr */
  pdActionCustomSetEditCallout  = 31,   /* param is QTCustomControlSetEditCalloutPtr */
  pdActionCustomGetEnableValue  = 32,   /* param is QTCustomControlGetEnableValuePtr */
  pdActionCustomSetSampleTime   = 33,   /* param is QTCustomControlSetSampleTimePtr */
  pdActionCustomGetValue        = 34,   /* param is QTCustomControlGetValue */
  pdActionCustomDoEditCommand   = 35,   /* param is QTCustomControlDoEditCommand */
                                        /* more actions for the dialog */
  pdActionRunInEventLoop        = 36,   /* param is QTEventLoopDescriptionPtr - OS X only*/
  pdActionConvertSettingsToXML  = 37,   /* param is QTAtomContainer* inbound, Handle* outbound contains the XML - createdDialog may be NIL */
  pdActionConvertSettingsToXMLWithComments = 38, /* param is QTAtomContainer* inbound, Handle* outbound contains the XML with comments - createdDialog may be NIL */
  pdActionConvertSettingsToText = 39,   /* param is QTAtomContainer* inbound, Handle* outbound contains human readable text - createdDialog may be NIL */
  pdActionConvertXMLToSettings  = 40,   /* param is Handle* inbound, QTAtomContainer* outbound contains parameters - createdDialog may be NIL */
  pdActionSetPropertyComponent  = 41    /* param is QTParamComponentPropertyPtr */
};

/* Sample Time information */
enum {
  pdSampleTimeDisplayOptionsNone = 0x00000000
};

struct QTParamComponentPropertyRecord {
  ComponentInstance   component;              /* component to call for get/set properties*/
  OSType              defaultClass;           /* default property class if not overriden by a given parameter*/
};
typedef struct QTParamComponentPropertyRecord QTParamComponentPropertyRecord;
typedef QTParamComponentPropertyRecord * QTParamComponentPropertyPtr;
struct QTParamSampleTimeRecord {
  long                displayOptions;
  TimeRecord          sampleStartTime;
  TimeValue           sampleDuration;
  long                framesPerSecond;        /* if 0, will cause revert to seconds display*/
};
typedef struct QTParamSampleTimeRecord  QTParamSampleTimeRecord;
typedef QTParamSampleTimeRecord *       QTParamSampleTimePtr;
/* Preview change callout information */
struct QTParamPreviewCalloutRecord {
  MoviePreviewCallOutUPP  calloutProc;        /* called when user makes editing changes to dialog.  May be NIL.  You should return true from your function. */
  long                refCon;                 /* passed to the callout procedure */
};
typedef struct QTParamPreviewCalloutRecord QTParamPreviewCalloutRecord;
typedef QTParamPreviewCalloutRecord *   QTParamPreviewCalloutPtr;
enum {
  pdOptionsCollectOneValue      = 0x00000001, /* should collect a single value only*/
  pdOptionsAllowOptionalInterpolations = 0x00000002, /* non-novice interpolation options are shown */
  pdOptionsModalDialogBox       = 0x00000004, /* dialog box should be modal */
  pdOptionsEditCurrentEffectOnly = 0x00000008, /* List of effects will not be shown */
  pdOptionsHidePreview          = 0x00000010, /* Preview item will not be shown */
  pdOptionsDisplayAsSheet       = 0x00000020 /* Dialog will be used as a sheet (on platforms that support it) */
};

typedef long                            QTParameterDialogOptions;
/* ------- CUSTOM EFFECT CONTROLS*/
/*
    Effects may choose to implement custom controls to allow the user to more easily edit complex parameters
    that are ill-served by simple sliders or type in boxes.   Effects may allow a custom control for either
    a single parameter, or for a group of parameters.
    
    Parameter(s) for a custom control must still be data types defined by the standard set, or for
    complex records of data, must be defined within a group as individual parameters made up from base
    data types (for example, a point is a group containing two Fixed point numbers).  
    This is to allow applications that do not wish to use the custom control for the effect to set values themselves.
    
    Effects should be aware that these custom controls may be deployed by the application in either a dialog or
    a window, with application defined background colors or patterns, along with application defined font
    characteristics for the window.
    
    It is recommended that effects implement custom controls only when needed, and that custom controls be used
    for specific types of parameters (ie, point, rectangle, polygon, path) rather than the entire user interface
    for the effect.  Effects may choose to implement multiple custom controls which combine with standard controls
    to present the total user interface.  For effects which have very complex user interfaces not well suited for 
    inclusion within a single window, it is recommended to use kParameterImageIsPreset -- which allows the effect to
    have an external editing application for parameters which may then be set within the standard UI via the open file 
    dialog or drag and drop.  The Lens Flare effect's "Flare Type" is an example of such a preset.

    For parameters that use a custom control to control a single parameter value, a new behavior
    flag has been added (kCustomControl), and the behavior for the parameter should be kParameterItemControl.
    
    For parameters that are groups, the same flag (kCustomControl) should be used, and the behavior
    should be kParameterItemGroupDivider.  Groups with the kCustomControl bit set will be implemented
    by calling the custom control for that group -- the parameters within that group will not be processed
    in the normal manner.
    
    In both cases, the new customType and customID fields of the behavior must be filled in.  These are 
    used in order to allow your custom control to determine which parameter is being edited in the case
    where the custom control is used for the editing of multiple parameters.  These values are passed into
    the pdActionCustomNewControl call.  Since the custom control mechanism is also used by QuickTime's
    default effect dialogs, you should be prepared to pass onto the base effect any pdActionCustomNewControl
    calls for type/id pairs that you do not handle yourself.  When  pdActionCustomNewControl is called
    for controls of types handled by QuickTime, customType is kParameterAtomTypeAndID and customID is
    the ID of the parameter atom. 
*/


/*
    pdActionCustomNewControlControl is called by application to create a new custom control or set of controls
    for an effect parameter.  When pdActionCustomNewControl is called, the effect should perform any
    basic allocation it needs for storage and return the result in storage. The options parameter tells
    the control if the application wishes to support interpolated, optionally interpolated, or a single
    value parameter.
    
    Since pdActionCustomNewControlControl may be called upon your effect for other items within the
    dialog, it is recommended that your effect have an easy way to determine which controls it implements:
     a) by having storage be a pointer with an OSType at the begining to mark controls
        implemented by your code.
     - or -
     b) keeping track in your component globals those custom controls which you have created.
    
    When pdActionCustomDisposeControl is called any allocation done by the control should be disposed. In addition, 
    pdActionCustomDisposeControl is the last chance the control has to commit any user changes into the sample.
    Controls which implement type in fields typically need to commit any final user edits at this time.
*/
struct QTCustomControlNewRecord {
  void *              storage;                /* storage allocated/disposed by the control*/
  QTParameterDialogOptions  options;          /* options used to control interpolation/not*/
  QTAtomContainer     sample;                 /* sample that holds the data to be edited*/
  long                customType;             /* custom type and ID specified by effect for creation of this control*/
  long                customID;
};
typedef struct QTCustomControlNewRecord QTCustomControlNewRecord;
typedef QTCustomControlNewRecord *      QTCustomControlNewPtr;
/*
    pdActionCustomPositionControl is called by the application to position the control within a window or dialog.

    The control should determine if it will fit in the alloted area and position itself there.  It should also
    return the space taken up by the control.   Note you are free to implement controls which are variable in size depending upon
    which parameter you are editing.  You need not scale your control to the requested size.  If the area presented to your
    control is too small, set didFit to false.  You should still return in used the size you would have liked to use for
    the control.   The application will then try again with a new size.  Note that all
    controls must be able to fit within a minimum of 300 by 250 pixels.
    
    Custom controls that draw text should make note of the text font, size, and style at this time in order
    to properly display within application windows.
    
    Note that the default state for the control is hidden.  You will receive a pdActionCustomShowHideControl
    in order to enable your control.  You should not draw your control in response to pdActionCustomPositionControl.
*/
struct QTCustomControlPositionControlRecord {
  void *              storage;                /* storage for the control*/
  WindowPtr           window;                 /* window to be used by the control*/
  Rect                location;               /* location within the window the control may use*/
  Rect                used;                   /* returned by the control to indicate size it actually used*/
  Boolean             didFit;                 /* did the control fit in the specified area?*/
  Boolean             pad[3];
};
typedef struct QTCustomControlPositionControlRecord QTCustomControlPositionControlRecord;
typedef QTCustomControlPositionControlRecord * QTCustomControlPositionControlPtr;
/*
    pdActionCustomShowHideControl is called when the application wishes to enable/disable your control, or 
    completely disable drawing of the control
    
    Your control should make note of the new state (if different from the last) and perform an InvalRect()
    on your drawing area, or you may draw your control's initial state in the case of show.  You should not
    attempt to erase your control as the result of a hide -- instead call InvalRect() and allow the application
    to process the resulting event as appropriate.
*/
struct QTCustomControlShowHideControlRecord {
  void *              storage;                /* storage for the control*/
  Boolean             show;                   /* display the control?*/
  Boolean             enable;                 /* enable the control (ie, black vs gray display)*/
  Boolean             pad[2];
};
typedef struct QTCustomControlShowHideControlRecord QTCustomControlShowHideControlRecord;
typedef QTCustomControlShowHideControlRecord * QTCustomControlShowHideControlPtr;
/*
    pdActionCustomHandleEvent is called to allow your custom control to process events.
    
    Typical controls handle the following events:
        - activate - to draw your control in normal/gray mode
        - update - to draw your control
        - mouseDown - to handle clicks
        - keyDown - to handle typing when you have focus
        - idle - to perform idle drawing (if applicable)
    If your control handles the entire event, set didProcess to true.  If
    you handled the event, but other controls still need the event, set didProcess to false.
    
    If your control supports the concept of focus for the purposes of typing (such as by having
    a type-in box for the parameter) then you set the tookFocus Boolean as part of your processing
    of the event.  It is assumed that your control will draw the appropriate focus UI as a result, and
    the calling application will disable any focus drawing within the remainder of the UI.

    By default, custom controls are not given idle time.  If you need idle time, set needIdle to true
    in response to the even that causes you to need idle (typically the taking of focus, or the first draw).
    Your control will continue to be given idle events until you set needIdle to false in response to
    a nullEvent.
*/
struct QTCustomControlHandleEventRecord {
  void *              storage;                /* storage for the control*/
  EventRecord *       pEvent;                 /* event to process*/
  Boolean             didProcess;             /* did we process entire event?*/
  Boolean             tookFocus;              /* did we take focus as a result of this event (typically mouseDowns)*/
  Boolean             needIdle;               /* does this control need idle events?*/
  Boolean             didEdit;                /* did we edit the samples?*/
};
typedef struct QTCustomControlHandleEventRecord QTCustomControlHandleEventRecord;
typedef QTCustomControlHandleEventRecord * QTCustomControlHandleEventPtr;
/*
    pdActionCustomSetFocus is called in order to set or advance the current focus of the user interface, typically
    because the user has pressed the tab or shift-tab keys, or because the user clicked within the area defined by
    your control.
    
    Your control will be called with pdActionFocusFirst,  pdActionFocusLast, or pdActionFocusOff to set or clear focus on your
    control.  Your control will be called with pdActionFocusForward or pdActionFocusBackward to cycle
    focus within your control (if your control has multiple focus).  If your control does not support focus,
    or the focus request results in focus moving beyond your supported range, return pdActionFocusOff in
    the focus parameter.  Otherwise, return the focus that you set.
    
    Controls which have no focus would always set focus to be pdActionFocusOff.
    
    Controls with a single focus would set pdActionFocusFirst when requsted to set either
    pdActionFocusFirst or pdActionFocusLast, and would set pdActionFocusOff for either
    pdActionFocusForward or pdActionFocusBackward.
*/
enum {
  pdActionFocusOff              = 0,    /* no focus */
  pdActionFocusFirst            = 1,    /* focus on first element */
  pdActionFocusLast             = 2,    /* focus on last element */
  pdActionFocusForward          = 3,    /* focus on next element */
  pdActionFocusBackward         = 4     /* focus on previous element */
};

struct QTCustomControlSetFocusRecord {
  void *              storage;                /* storage for the control*/
  long                focus;                  /* focus to set, return resulting focus*/
};
typedef struct QTCustomControlSetFocusRecord QTCustomControlSetFocusRecord;
typedef QTCustomControlSetFocusRecord * QTCustomControlSetFocusPtr;
/* 
    pdActionCustomSetEditMenu will be called to inform your custom control of the location of the edit menu.
    
    If your control has editing boxes, this is useful in order to allow the user to perform cut/copy/paste operations
    when focus is on one of these boxes.
*/
struct QTCustomControlSetEditMenuRecord {
  void *              storage;                /* storage for the control*/
  MenuHandle          editMenu;               /* edit menu, or NIL*/
};
typedef struct QTCustomControlSetEditMenuRecord QTCustomControlSetEditMenuRecord;
typedef QTCustomControlSetEditMenuRecord * QTCustomControlSetEditMenuPtr;
/*
    pdActionCustomSetPreviewPicture will be called to inform your custom control of preview information that you
    may wish to use in the drawing of your user interface.  
*/
struct QTCustomControlSetPreviewPictureRecord {
  void *              storage;                /* storage for the control*/
  QTParamPreviewPtr   preview;                /* preview to set*/
};
typedef struct QTCustomControlSetPreviewPictureRecord QTCustomControlSetPreviewPictureRecord;
typedef QTCustomControlSetPreviewPictureRecord * QTCustomControlSetPreviewPicturePtr;
/*
    pdActionCustomSetEditCallout tells your control of the need by the application to be informed of
    changes to the parameter values (typically for the purposes of updating previews).
    
    If a callout is available, your custom control should call it whenever a change has been
    made to the parameter(s) that your control is editing (as a result of user actions, most typically).
    If you choose not to implement this, live dragging or updating of values will not work.
*/
struct QTCustomControlSetEditCalloutRecord {
  void *              storage;                /* storage for the control*/
  QTParamPreviewCalloutPtr  callout;          /* requested callout, or NIL to disable*/
};
typedef struct QTCustomControlSetEditCalloutRecord QTCustomControlSetEditCalloutRecord;
typedef QTCustomControlSetEditCalloutRecord * QTCustomControlSetEditCalloutPtr;
/*
    pdActionCustomGetEnableValue allows you to return a value for the purposes of enabling/disabling
    other controls.
    Most custom controls do not need to implement this call.
    
    If your control is able to control the enabling and disabling of other parameter controls (such as is done
    by standard pop up or enumerated type controls), you need to supply a value that can be use for greater than/less than
    types of comparisons.
*/
struct QTCustomControlGetEnableValueRecord {
  void *              storage;                /* storage for the control*/
  long                currentValue;           /* value to compare against for enable/disable purposes*/
};
typedef struct QTCustomControlGetEnableValueRecord QTCustomControlGetEnableValueRecord;
typedef QTCustomControlGetEnableValueRecord * QTCustomControlGetEnableValuePtr;
/*
    pdActionCustomSetSampleTime tells your control information from the application about the duration
    and start time for the sample being edited.
    
    Most controls do not need this information, but some may choose to use it in the interface
    they present the user.  However, this call need not be made by applications, so the custom
    control should be prepared to run when the sample time information is not available.
*/
struct QTCustomControlSetSampleTimeRecord {
  void *              storage;                /* storage for the control*/
  QTParamSampleTimePtr  sampleTime;           /* sample time information or NIL*/
};
typedef struct QTCustomControlSetSampleTimeRecord QTCustomControlSetSampleTimeRecord;
typedef QTCustomControlSetSampleTimeRecord * QTCustomControlSetSampleTimePtr;
/*
    pdActionCustomGetValue tells your control to store any value(s) into the specified atom container.
    
    All custom controls must implement this call
*/
struct QTCustomControlGetValueRecord {
  void *              storage;                /* storage for the control*/
  QTAtomContainer     sample;                 /* sample to store into*/
};
typedef struct QTCustomControlGetValueRecord QTCustomControlGetValueRecord;
typedef QTCustomControlGetValueRecord * QTCustomControlGetValuePtr;
/*
    pdActionCustomDoEditCommand tells your control to handle edit commands if it allow focus and type in boxes.
    
    All custom controls must implement this call if they support edit boxes
*/
struct QTCustomControlDoEditCommandRecord {
  void *              storage;                /* storage for the control*/
  long                command;                /* command to execute, return 0 here if processed*/
};
typedef struct QTCustomControlDoEditCommandRecord QTCustomControlDoEditCommandRecord;
typedef QTCustomControlDoEditCommandRecord * QTCustomControlDoEditCommandPtr;
typedef long                            QTParameterDialog;
enum {
  elOptionsIncludeNoneInList    = 0x00000001 /* "None" effect is included in list */
};

typedef long                            QTEffectListOptions;
enum {
  effectIsRealtime              = 0     /* effect can be rendered in real time */
};

/*
    QTGetEffectsListExtended is a call that provides for 
    more advanced filtering of effects to be placed into the
    effect list.  Applications can filter on:
     1) number of input sources
     2) effect major or minor class
     3) custom filtering through a callback
    The callback will be called for each effect which passes
    the other criteria for inclusion.  If the callback
    returns a true result the effect will be included in the list.
    
    Note that your filter proc may receive multiple effects from various
    manufacturers.  If you return true for multiple effects of a given type
    only the one with the higher parameter version number will be included.
    If you wish other filtering (such as effects from a given manufacturer, you
    can do this by return false for the other effects and true for those
    that you prefer.
*/
typedef CALLBACK_API( Boolean , QTEffectListFilterProcPtr )(Component effect, long effectMinSource, long effectMaxSource, OSType majorClass, OSType minorClass, void *refcon);
typedef STACK_UPP_TYPE(QTEffectListFilterProcPtr)               QTEffectListFilterUPP;
/*
 *  QTGetEffectsList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTGetEffectsList(
  QTAtomContainer *     returnedList,
  long                  minSources,
  long                  maxSources,
  QTEffectListOptions   getOptions)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTGetEffectsListExtended()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTGetEffectsListExtended(
  QTAtomContainer *       returnedList,
  long                    minSources,
  long                    maxSources,
  QTEffectListOptions     getOptions,
  OSType                  majorClass,
  OSType                  minorClass,
  QTEffectListFilterUPP   filterProc,
  void *                  filterRefCon)                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTCreateStandardParameterDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTCreateStandardParameterDialog(
  QTAtomContainer            effectList,
  QTAtomContainer            parameters,
  QTParameterDialogOptions   dialogOptions,
  QTParameterDialog *        createdDialog)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTIsStandardParameterDialogEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTIsStandardParameterDialogEvent(
  EventRecord *       pEvent,
  QTParameterDialog   createdDialog)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTDismissStandardParameterDialog()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTDismissStandardParameterDialog(QTParameterDialog createdDialog) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTStandardParameterDialogDoAction()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTStandardParameterDialogDoAction(
  QTParameterDialog   createdDialog,
  long                action,
  void *              params)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTGetEffectSpeed()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTGetEffectSpeed(
  QTAtomContainer   parameters,
  Fixed *           pFPS)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/* Movie Audio/Sound APIs*/

/*
    SetMovieAudioGain:
    This API sets the audio gain level for the mixed audio output of a movie.  This alters the
    perceived volume of the movie's playback.  The gain level is multiplicative; eg. 0.0
    is silent, 0.5 is -6dB, 1.0 is 0dB (ie. the audio from the movie is not
    modified), 2.0 is +6dB, etc.  The gain level can be set higher than 1.0 in order
    to allow quiet movies to be boosted in volume.  Settings higher than 1.0 may result in
    audio clipping, of course.  The setting is not stored in the movie.  It is only used until
    the movie is closed, at which time it is not saved.
 */
/*
 *  SetMovieAudioGain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMovieAudioGain(
  Movie     m,
  Float32   gain,
  UInt32    flags)                                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMovieAudioGain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMovieAudioGain(
  Movie      m,
  Float32 *  gain,
  UInt32     flags)                                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
    SetTrackAudioGain:
    This API sets the audio gain level for the audio output of a track.  This alters the
    perceived volume of the track's playback.  The gain level is multiplicative; eg. 0.0
    is silent, 0.5 is -6dB, 1.0 is 0dB (ie. the audio from the track is not
    modified), 2.0 is +6dB, etc.  The gain level can be set higher than 1.0 in order
    to allow quiet tracks to be boosted in volume.  Settings higher than 1.0 may result in
    audio clipping, of course.  The setting is not stored in the movie.  It is only used until
    the movie is closed, at which time it is not saved.
 */
/*
 *  SetTrackAudioGain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetTrackAudioGain(
  Track     t,
  Float32   gain,
  UInt32    flags)                                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetTrackAudioGain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetTrackAudioGain(
  Track      t,
  Float32 *  gain,
  UInt32     flags)                                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
    SetMovieAudioBalance:
    This API sets the audio balance level for the mixed audio output of a movie.  -1.0
    means full left, 0.0 means centered, and 1.0 means full right.  The setting is not
    stored in the movie.  It is only used until the movie is closed, at which time it
    is not saved.
 */
/*
 *  SetMovieAudioBalance()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMovieAudioBalance(
  Movie     m,
  Float32   leftRight,
  UInt32    flags)                                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMovieAudioBalance()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMovieAudioBalance(
  Movie      m,
  Float32 *  leftRight,
  UInt32     flags)                                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
    SetMovieAudioMute:
    This API mutes or unmutes the mixed audio output from a movie.
 */
/*
 *  SetMovieAudioMute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMovieAudioMute(
  Movie     m,
  Boolean   muted,
  UInt32    flags)                                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMovieAudioMute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMovieAudioMute(
  Movie      m,
  Boolean *  muted,
  UInt32     flags)                                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
    SetTrackAudioMute:
    This API mutes or unmutes the audio output from a track.
 */
/*
 *  SetTrackAudioMute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetTrackAudioMute(
  Track     t,
  Boolean   muted,
  UInt32    flags)                                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetTrackAudioMute()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetTrackAudioMute(
  Track      t,
  Boolean *  muted,
  UInt32     flags)                                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;




/*
 */
enum {

  /*
   * Properties of an audio presentation (eg. a movie's audio)
   */
  kQTPropertyClass_Audio        = 'audi'
};


/*
 */
enum {

  /*
   * kQTAudioPropertyID_Gain:  Value is Float32.  Get/Set/Listenable
   * The audio gain of a movie or track.  The gain level is
   * multiplicative; eg. 0.0 is silent, 0.5 is -6dB, 1.0 is 0dB (ie.
   * the audio from the movie is not modified), 2.0 is +6dB, etc.  The
   * gain level can be set higher than 1.0 in order to allow quiet
   * movies/tracks to be boosted in volume. Settings higher than 1.0
   * may result in audio clipping, of course. The setting is not stored
   * in the movie/track.  It is only used until the movie/track is
   * disposed.
   */
  kQTAudioPropertyID_Gain       = 'gain', /* value is Float32. Gettable/Settable.*/

  /*
   * kQTAudioPropertyID_Mute:  Value is Boolean.  Get/Set/Listenable
   * The audio mute state of a movie or track.  If true, the
   * movie/track is muted.  The setting is not stored in the
   * movie/track.  It is only used until the movie/track is disposed.
   */
  kQTAudioPropertyID_Mute       = 'mute', /* value is Boolean. Gettable/Settable.*/

  /*
   * kQTAudioPropertyID_Balance:  Value is Float32.  Get/Set/Listenable
   * The audio balance of a movie.  -1.0 means full left, 0.0 means
   * centered, and 1.0 means full right.  The setting is not stored in
   * the movie.  It is only used until the movie is disposed.  This is
   * only supported for movies, not tracks.
   */
  kQTAudioPropertyID_Balance    = 'bala', /* value is Float32. Gettable/Settable.*/

  /*
   * kQTAudioPropertyID_RateChangesPreservePitch:   Value is Boolean. 
   * Get/Set When the playback rate is not unity, audio must be
   * resampled in order to play at the new rate.  The default
   * resampling affects the pitch of the audio (eg, playing at 2x speed
   * raises the pitch by an octave, 1/2x lowers an octave). If this
   * property is set on the Movie, an alternative algorithm may be
   * used, which alters the speed without changing the pitch.  As this
   * is more computationally expensive, this property may be silently
   * ignored on some slow CPUs. Media handlers may query this movie
   * property and honor it when performing Scaled Edits. This property
   * can be specified as a property to the NewMovieFromProperties()
   * API. Currently, it has no effect when set on an open movie.
   */
  kQTAudioPropertyID_RateChangesPreservePitch = 'aucp', /* value is Boolean.  Gettable/Settable.*/

  /*
   * kQTAudioPropertyID_Pitch:   Value is Float32.  Get/Set/Listenable
   * Movie pitch adjustment.  Adjusts the pitch of all audio tracks
   * that contribute to the AudioContext mix.  Pitch control takes
   * effect only if kQTAudioPropertyID_RateChangesPreservePitch is in
   * effect, otherwise returns kQTMessageNotHandledErr. The Float32
   * value is specified in cents: 0.0 == no change, 1.0 == one cent up,
   * 100.0 == one semi-tone up, -1.0 == one cent down. The most useful
   * ranges for pitch are +/- 1200. (ie, one octave)
   */
  kQTAudioPropertyID_Pitch      = 'pitc', /* value is Float32. Get/Set/Listenable.*/

  /*
   * kQTAudioPropertyID_RenderQuality:   Value is UInt32.  Get/Set
   * Movie audio render quality takes effect for movie playback. UInt32
   * values vary from 0x00 (kQTAudioRenderQuality_Min) to 0x7F
   * (kQTAudioRenderQuality_Max). We also define a special value
   * (kQTAudioRenderQuality_PlaybackDefault) which resets the quality
   * settings of the playback processing chain to values that are
   * chosen to be an optimal balance of performance and quality.
   */
  kQTAudioPropertyID_RenderQuality = 'qual', /* value is UInt32.  Gettable/Settable.*/

  /*
   * kQTAudioPropertyID_ChannelLayout:  Value is AudioChannelLayout. 
   * Get/Set The AudioChannelLayout of a track, or other audio stream. 
   * Currently only settable/gettable for tracks.  (See
   * kQTAudioPropertyID_SummaryChannelLayout if you want to get the
   * summary AudioChannelLayout of a movie.) Note that this is a
   * variable sized property (since it may contain an array of
   * ChannelDescriptions; see CoreAudioTypes.h).  You must get the size
   * first (by calling QTGetTrackPropertyInfo), allocate a struct of
   * that size, and then get the property.
   */
  kQTAudioPropertyID_ChannelLayout = 'tlay', /* value is AudioChannelLayout. Gettable/Settable.*/

  /*
   * kQTAudioPropertyID_SummaryChannelLayout:  Value is
   * AudioChannelLayout.  Get-only The summary AudioChannelLayout of a
   * movie, or other grouping of audio streams. All like-labelled
   * channels are combined, so there are no duplicates.  For example,
   * if there is a stereo (L/R) track, 5 single-channel tracks marked
   * Left, Right, Left Surround, Right Surround and Center, and a 4
   * channel track marked L/R/Ls/Rs, then the summary
   * AudioChannelLayout will be L/R/Ls/Rs/C. It will _not_ be
   * L/R/L/R/Ls/Rs/C/L/R/Ls/Rs. Note that this is a variable sized
   * property (since it may contain an array of ChannelDescriptions;
   * see CoreAudioTypes.h).  You must get the size first (by calling,
   * for example, QTGetMoviePropertyInfo) allocate a struct of that
   * size, and then get the property.
   */
  kQTAudioPropertyID_SummaryChannelLayout = 'clay', /* value is AudioChannelLayout. Gettable.*/

  /*
   * kQTAudioPropertyID_DeviceChannelLayout:  Value is
   * AudioChannelLayout.  Get-only The AudioChannelLayout of the device
   * this movie is playing to.  Note that this is a variable sized
   * property (since it may contain an array of ChannelDescriptions;
   * see CoreAudioTypes.h).  You must get the size first (by calling,
   * for example, QTGetMoviePropertyInfo) allocate a struct of that
   * size, and then get the property.
   */
  kQTAudioPropertyID_DeviceChannelLayout = 'dcly', /* value is AudioChannelLayout. Gettable.*/

  /*
   * kQTAudioPropertyID_DeviceASBD:  Value is
   * AudioStreamBasicDescription.  Get-only Returns the
   * AudioStreamBasicDescription of the device this movie is playing
   * to. The interesting fields are the sample rate, which reflects
   * device's current state, and the number of channels, which matches
   * what is reported by kQTAudioPropertyID_DeviceChannelLayout.
   */
  kQTAudioPropertyID_DeviceASBD = 'dasd', /* value is AudioStreamBasicDescription. Gettable.*/

  /*
   * kQTAudioPropertyID_SummaryASBD:  Value is
   * AudioStreamBasicDescription.  Get-only Returns the
   * AudioStreamBasicDescription corresponding to the Summary Mix of a
   * movie.  This will describe non-interleaved, Float32 linear PCM
   * data, with a sample rate equal to the highest audio sample rate
   * found among the sound tracks contributing to the AudioContext mix,
   * and a number of channels that matches what is reported by
   * kQTAudioPropertyID_SummaryChannelLayout.
   */
  kQTAudioPropertyID_SummaryASBD = 'sasd', /* value is AudioStreamBasicDescription. Gettable.*/

  /*
   * kQTAudioPropertyID_FormatString:  Value is CFStringRef.  Get-only
   * kQTAudioPropertyID_FormatString returns a localized, human
   * readable string describing the audio format as a CFStringRef, i.e.
   * "MPEG Layer 3". You may get this property from a SoundDescription
   * Handle by calling QTSoundDescriptionGetProperty(), or from a
   * StandardAudioCompression (scdi/audi) component instance by calling
   * QTGetComponentProperty().
   */
  kQTAudioPropertyID_FormatString = 'fstr', /* value is CFStringRef.  Gettable.*/

  /*
   * kQTAudioPropertyID_ChannelLayoutString:  Value is CFStringRef. 
   * Get-only kQTAudioPropertyID_ChannelLayoutString returns a
   * localized, human readable string describing the audio channel
   * layout as a CFStringRef, i.e. "5.0 (L R C Ls Rs)". You may get
   * this property from a SoundDescription Handle by calling
   * QTSoundDescriptionGetProperty(), or from a
   * StandardAudioCompression (scdi/audi) component instance by calling
   * QTGetComponentProperty().
   */
  kQTAudioPropertyID_ChannelLayoutString = 'lstr', /* value is CFStringRef.  Gettable.*/

  /*
   * kQTAudioPropertyID_SampleRateString:  Value is CFStringRef. 
   * Get-only kQTAudioPropertyID_SampleRateString returns a localized,
   * human readable string describing the audio sample rate as a
   * CFStringRef, i.e. "44.100 kHz". You may get this property from a
   * SoundDescription Handle by calling
   * QTSoundDescriptionGetProperty(), or from a
   * StandardAudioCompression (scdi/audi) component instance by calling
   * QTGetComponentProperty().
   */
  kQTAudioPropertyID_SampleRateString = 'rstr', /* value is CFStringRef.  Gettable.*/

  /*
   * kQTAudioPropertyID_SampleSizeString:  Value is CFStringRef. 
   * Get-only kQTAudioPropertyID_SampleSizeString returns a localized,
   * human readable string describing the audio sample size as a
   * CFStringRef, i.e. "24-bit". Note, this property will only return a
   * valid string if the format is uncompressed (LPCM) audio. You may
   * get this property from a SoundDescription Handle by calling
   * QTSoundDescriptionGetProperty(), or from a
   * StandardAudioCompression (scdi/audi) component instance by calling
   * QTGetComponentProperty().
   */
  kQTAudioPropertyID_SampleSizeString = 'sstr', /* value is CFStringRef.  Gettable.*/

  /*
   * kQTAudioPropertyID_BitRateString:  Value is CFStringRef.  Get-only
   * kQTAudioPropertyID_BitRateString returns a localized, human
   * readable string describing the audio bit rate as a CFStringRef,
   * i.e. "12 kbps". You may get this property from a SoundDescription
   * Handle by calling QTSoundDescriptionGetProperty(), or from a
   * StandardAudioCompression (scdi/audi) component instance by calling
   * QTGetComponentProperty().
   */
  kQTAudioPropertyID_BitRateString = 'bstr', /* value is CFStringRef.  Gettable.*/

  /*
   * kQTAudioPropertyID_SummaryString:  Value is CFStringRef.  Get-only
   * kQTAudioPropertyID_SummaryString returns a localized, human
   * readable string summarizing the audio as a CFStringRef, i.e.
   * "16-bit Integer (Big Endian), Stereo (L R), 48.000 kHz". You may
   * get this property from a SoundDescription Handle calling
   * QTSoundDescriptionGetProperty(), or from a
   * StandardAudioCompression (scdi/audi) component instance by calling
   * QTGetComponentProperty().
   */
  kQTAudioPropertyID_SummaryString = 'asum' /* value is CFStringRef.  Gettable.*/
};




/*
 *  Audio Render Quality constants
 *  
 *  Summary:
 *    Render quality is an integer that ranges from
 *    kQTAudioRenderQuality_Min to kQTAudioRenderQuality_Max.
 *    kQTAudioRenderQuality_Low, kQTAudioRenderQuality_Medium, and
 *    kQTAudioRenderQuality_High are the preferred values.
 */
enum {

  /*
   * The maximum value.
   */
  kQTAudioRenderQuality_Max     = 0x7F,

  /*
   * A value that increases quality but requires more computational
   * resources.
   */
  kQTAudioRenderQuality_High    = 0x60,

  /*
   * A value that represents a good quality/performance tradeoff.
   */
  kQTAudioRenderQuality_Medium  = 0x40,

  /*
   * A value that reduces quality for better performance.
   */
  kQTAudioRenderQuality_Low     = 0x20,

  /*
   * The minimum value.
   */
  kQTAudioRenderQuality_Min     = 0x00,

  /*
   * A QuickTime-specific value that selects optimal settings for
   * playback.
   */
  kQTAudioRenderQuality_PlaybackDefault = 0x8000
};


/* whatMixToMeter constants*/

/*
 */
enum {

  /*
   * kQTAudioMeter_DeviceMix: Meter the movie's mix to the device
   * channel layout. To determine the channel layout of this mix, call
   * QTGetMovieProperty(..., kQTAudioPropertyID_DeviceChannelLayout,
   * ...).
   */
  kQTAudioMeter_DeviceMix       = kQTAudioPropertyID_DeviceChannelLayout,

  /*
   * kQTAudioMeter_StereoMix: Meter a stereo (two-channel) mix of the
   * enabled sound tracks in the movie. This option is offered only for
   * MovieAudioFrequencyMetering.
   */
  kQTAudioMeter_StereoMix       = 'stmx',

  /*
   * kQTAudioMeter_MonoMix: Meter a monarual (one-channel) mix of the
   * enabled sound tracks in the movie. This option is offered only for
   * MovieAudioFrequencyMetering.
   */
  kQTAudioMeter_MonoMix         = 'momx'
};

/*
    SetMovieAudioVolumeMeteringEnabled:
    This API enables or disables volume metering of a particular mix of this movie.  The only possible
    mix to meter is currently kQTAudioMeter_DeviceMix.  See kQTAudioMeter_DeviceMix above to see
    how to determine the channel layout of the movie's device mix.
 */
/*
 *  SetMovieAudioVolumeMeteringEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMovieAudioVolumeMeteringEnabled(
  Movie          m,
  FourCharCode   whatMixToMeter,
  Boolean        enabled)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMovieAudioVolumeMeteringEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMovieAudioVolumeMeteringEnabled(
  Movie          m,
  FourCharCode   whatMixToMeter,
  Boolean *      enabled)                                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
    GetMovieAudioVolumeLevels:
    This API returns the current volume meter levels of the movie.  It can return both average power
    levels and peak hold levels.  whatMixToMeter must be set to kQTAudioMeter_DeviceMix.  Either
    QTAudioVolumeLevels parameter may be nil.  If non-nil, each must have its numChannels field set to
    the number of channels in the movie's device mix, and must be allocated large enough to hold levels
    for all those channels.  See kQTAudioMeter_DeviceMix above to see how to determine the channel
    layout of the device mix. The levels returned are measured in decibels, where 0.0 means full volume,
    -6.0 means half volume, -12.0 means quarter volume, and -inf means silence.
 */
struct QTAudioVolumeLevels {
  UInt32              numChannels;
  Float32             level[1];               /* numChannels entries*/
};
typedef struct QTAudioVolumeLevels      QTAudioVolumeLevels;
/*
 *  GetMovieAudioVolumeLevels()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMovieAudioVolumeLevels(
  Movie                  m,
  FourCharCode           whatMixToMeter,
  QTAudioVolumeLevels *  pAveragePowerLevels,
  QTAudioVolumeLevels *  pPeakHoldLevels)                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* 
    SetTrackAudioVolumeMeteringEnabled:
    This API enables or disables volume metering of a particular track of this movie.
    This API should be used in preference to the legacy SoundMedia interface, but
    may interfere with its operation if both are in use at the same time.
*/
/*
 *  SetTrackAudioVolumeMeteringEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetTrackAudioVolumeMeteringEnabled(
  Track     t,
  Boolean   enabled)                                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetTrackAudioVolumeMeteringEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetTrackAudioVolumeMeteringEnabled(
  Track      t,
  Boolean *  enabled)                                         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
    GetTrackAudioVolumeLevels:
    This API returns the current volume meter levels of the track.  It can return both average power
    levels and peak hold levels.  Either QTAudioVolumeLevels parameter may be nil.  If non-nil,
    each must have its numChannels field set to the number of channels of interest, and must be
    allocated large enough to hold levels for all those channels.
    The levels returned are measured in decibels, where 0.0 means full volume,
    -6.0 means half volume, -12.0 means quarter volume, and -inf means silence.
*/
/*
 *  GetTrackAudioVolumeLevels()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetTrackAudioVolumeLevels(
  Track                  t,
  QTAudioVolumeLevels *  pAveragePowerLevels,
  QTAudioVolumeLevels *  pPeakHoldLevels)                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
    SetMovieAudioFrequencyMeteringNumBands:
    This API configures and enables (or disables) frequency metering for a movie.
    Note that ioNumBands is an in/out parameter.  You specify the number of frequency bands you
    want to meter, and if that number is higher than is possible (determined by, among other things,
    the sample rate of the audio being metered), this API will return the number of bands it is
    actually going to meter.  ioNumBands can be nil or a pointer to 0 to disable metering.
    whatMixToMeter must be set to kQTAudioMeter_StereoMix, kQTAudioMeter_MonoMix, or
    kQTAudioMeter_DeviceMix.  When metering movies playing to audio devices that offer a
    large number of channels, it may be prohibitively expensive to perform spectral analysis
    on every channel; in these cases, stereo or mono mix metering may be preferable.
 */
/*
 *  SetMovieAudioFrequencyMeteringNumBands()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMovieAudioFrequencyMeteringNumBands(
  Movie          m,
  FourCharCode   whatMixToMeter,
  UInt32 *       ioNumBands)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMovieAudioFrequencyMeteringNumBands()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMovieAudioFrequencyMeteringNumBands(
  Movie          m,
  FourCharCode   whatMixToMeter,
  UInt32 *       outNumBands)                                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
    GetMovieAudioFrequencyMeteringBandFrequencies:
    This API returns the actual chosen middle frequency for each band in the configured
    frequency metering of a movie.  This is useful for labeling visual meters
    in a user interface.  Frequencies are returned in Hz.  whatMixToMeter must be set
    to the same value that was passed most recently to SetMovieAudioFrequencyMeteringNumBands().
 */
/*
 *  GetMovieAudioFrequencyMeteringBandFrequencies()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMovieAudioFrequencyMeteringBandFrequencies(
  Movie          m,
  FourCharCode   whatMixToMeter,
  UInt32         numBands,
  Float32 *      outBandFrequencies)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
    GetMovieAudioFrequencyLevels:
    This API returns the current frequency meter levels of the movie. pAveragePowerLevels should
    have its numChannels field set to the number of channels being metered, and its numBands field
    set to the number of bands being metered (as previously configured).  pAveragePowerLevels must be
    allocated large enough to hold levels for all bands in all channels.  The levels are returned with
    all the band levels for the first channel first, then all the band levels for the second channel, etc.
    whatMixToMeter must be set  to the same value that was passed most recently to
    SetMovieAudioFrequencyMeteringNumBands().
 */
struct QTAudioFrequencyLevels {
  UInt32              numChannels;
  UInt32              numFrequencyBands;
                                              /* numChannels * numFrequencyBands entries, with the frequency bands for a single channel stored contiguously.*/
  Float32             level[1];
};
typedef struct QTAudioFrequencyLevels   QTAudioFrequencyLevels;
/*
 *  GetMovieAudioFrequencyLevels()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMovieAudioFrequencyLevels(
  Movie                     m,
  FourCharCode              whatMixToMeter,
  QTAudioFrequencyLevels *  pAveragePowerLevels)              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/* Movie Audio Extraction*/

/*
    MovieAudioExtractionBegin:
    This API must be called before doing any movie audio extraction.  The returned session
    object is to be passed to the other movie audio extraction APIs.  Note that the extracted
    format defaults to the aggregate channel layout of the movie (eg. all Rights mixed together,
    all Left Surrounds mixed together, etc), 32-bit float, de-interleaved, with the sample rate
    set to the highest sample rate found in the movie.  You can get this info, and you can also
    set the format to be something else (as long as it is uncompressed, and you do it before
    the first call to MovieAudioExtractionFillBuffer). 
 */
typedef struct MovieAudioExtractionRefRecord*  MovieAudioExtractionRef;
/*
 *  MovieAudioExtractionBegin()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
MovieAudioExtractionBegin(
  Movie                      m,
  UInt32                     flags,
  MovieAudioExtractionRef *  outSession)                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
    MovieAudioExtractionEnd:
    This API must be called when movie audio extraction is complete.
 */
/*
 *  MovieAudioExtractionEnd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
MovieAudioExtractionEnd(MovieAudioExtractionRef session)      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/* Movie audio extraction property classes*/

/*
 */
enum {

  /*
   * Properties of the movie being extracted from
   */
  kQTPropertyClass_MovieAudioExtraction_Movie = 'xmov',

  /*
   * Properties of the output audio
   */
  kQTPropertyClass_MovieAudioExtraction_Audio = 'xaud'
};

/* "Movie class" property IDs*/

/*
 */
enum {

  /*
   * kQTMovieAudioExtractionMoviePropertyID_CurrentTime: Value is
   * TimeRecord (set & get) When setting, set the timescale to anything
   * you want (output audio sample rate, movie timescale) When getting,
   * the timescale will be output audio sample rate for best accuracy.
   */
  kQTMovieAudioExtractionMoviePropertyID_CurrentTime = 'time', /* value is TimeRecord. Get/Set.*/

  /*
   * kQTMovieAudioExtractionMoviePropertyID_AllChannelsDiscrete: Value
   * is Boolean (set & get) Set to implement export of all audio
   * channels without mixing. When this is set and the extraction asbd
   * or channel layout are read back, you will get information relating
   * to the re-mapped movie.
   */
  kQTMovieAudioExtractionMoviePropertyID_AllChannelsDiscrete = 'disc', /* value is Boolean. Get/Set.*/

  /*
   * kQTMovieAudioExtractionAudioPropertyID_RenderQuality: Value is
   * UInt32 (set & get) Set the render quality to be used for this
   * audio extraction session. UInt32 values vary from 0x00
   * (kQTAudioRenderQuality_Min) to 0x7F (kQTAudioRenderQuality_Max).
   * We also define a special value
   * (kQTAudioRenderQuality_PlaybackDefault) which resets the quality
   * settings to the same values that were chosen by default for
   * playback.
   */
  kQTMovieAudioExtractionAudioPropertyID_RenderQuality = 'qual' /* value is UInt32. Get/Set.*/
};


/* "Output Audio class" property IDs*/

/*
 */
enum {
                                        /* kQTPropertyClass_MovieAudioExtraction_Audio*/

  /*
   * 
   * QTMovieAudioExtractionAudioPropertyID_AudioStreamBasicDescription:
   * Value is AudioStreamBasicDescription.  Get/Set. (get any time, set
   * before first MovieAudioExtractionFillBuffer call) If you get this
   * property immediately after beginning an audio extraction session,
   * it will tell you the default extraction format for the movie. 
   * This will include the number of channels in the default movie mix.
   * If you set the output AudioStreamBasicDescription, it is
   * recommended that you also set the output channel layout.  If your
   * output ASBD has a different number of channels that the default
   * extraction mix, you _must_ set the output channel layout. You can
   * only set PCM output formats.  Setting a compressed output format
   * will fail.
   */
  kQTMovieAudioExtractionAudioPropertyID_AudioStreamBasicDescription = 'asbd', /* value is AudioStreamBasicDescription. Get/Set.*/

  /*
   * kQTMovieAudioExtractionAudioPropertyID_AudioChannelLayout: Value
   * is AudioChannelLayout.  Get/Set. (get any time, set before first
   * MovieAudioExtractionFillBuffer call) If you get this property
   * immediately after beginning an audio extraction session, it will
   * tell you what the channel layout is for the default extraction mix.
   */
  kQTMovieAudioExtractionAudioPropertyID_AudioChannelLayout = 'clay', /* value is AudioChannelLayout. Get/Set.*/

  /*
   * kQTMovieAudioExtractionAudioPropertyID_RemainingAudioDuration:
   * Value is TimeRecord. Get only. Returns the total duration of audio
   * data that can be expected from the audio extraction session as
   * currently configured.  This is computed by examining all tracks
   * that contribute to the audio mix, finding the highest end time
   * among them, adding in all relevant tail times from any Audio
   * Context Inserts that have been registered, and subtracting any
   * extraction start time that has been set.  If this property is
   * queried once extraction has started, it will return the remaining
   * duration, or zero once extraction has advanced to the end of all
   * contributing audio tracks.
   */
  kQTMovieAudioExtractionAudioPropertyID_RemainingAudioDuration = 'dura' /* value is TimeRecord. Get only.*/
};


/*
 *  MovieAudioExtractionGetPropertyInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
MovieAudioExtractionGetPropertyInfo(
  MovieAudioExtractionRef   session,
  QTPropertyClass           inPropClass,
  QTPropertyID              inPropID,
  QTPropertyValueType *     outPropType,
  ByteCount *               outPropValueSize,
  UInt32 *                  outPropertyFlags)                 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  MovieAudioExtractionGetProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
MovieAudioExtractionGetProperty(
  MovieAudioExtractionRef   session,
  QTPropertyClass           inPropClass,
  QTPropertyID              inPropID,
  ByteCount                 inPropValueSize,
  QTPropertyValuePtr        outPropValueAddress,
  ByteCount *               outPropValueSizeUsed)             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  MovieAudioExtractionSetProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
MovieAudioExtractionSetProperty(
  MovieAudioExtractionRef   session,
  QTPropertyClass           inPropClass,
  QTPropertyID              inPropID,
  ByteCount                 inPropValueSize,
  ConstQTPropertyValuePtr   inPropValueAddress)               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
    MovieAudioExtractionFillBuffer:
    Each call to MovieAudioExtractionFillBuffer will continue where the last call left off.
    It will extract as many of the requested PCM frames as it can, given the limits of the
    buffer(s) supplied, and the limits of the input movie.  ioNumFrames will be updated
    with the exact number of valid frames being returned.
    When there is no more audio to extract from the movie, MovieAudioExtractionFillBuffer
    will continue to return noErr, but no audio data will be returned.  outFlags will have
    the kQTMovieAudioExtractionComplete bit set in this case.  It is possible that the
    kQTMovieAudioExtractionComplete bit will accompany the last buffer of valid data.
 */
enum {
  kQTMovieAudioExtractionComplete = (1L << 0)
};

/*
 *  MovieAudioExtractionFillBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
MovieAudioExtractionFillBuffer(
  MovieAudioExtractionRef   session,
  UInt32 *                  ioNumFrames,
  AudioBufferList *         ioData,
  UInt32 *                  outFlags)                         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/* Audio Context Insert properties for MovieAudioExtraction*/

/*
   Theory of operations:
    To register for a Movie Audio Context Insert during Movie Audio Extraction:
        Set the kQTMovieAudioExtractionAudioPropertyID_RegisterMovieInsert
            property on the extraction session, providing the same registry info structure
            that is used for the QTAudioContextRegisterInsert call.
    To register for a Track Audio Context Insert during Movie Audio Extraction:
        Set the kQTMovieAudioExtractionAudioPropertyID_RegisterTrackInsert
            property on the extraction session, providing a QTAudioTrackInsertRegistryInfoRef,
            described below.
    Note: Once extraction has begun (ie, MovieAudioExtractionFillBuffer() has been
            called), attempts to set these properties will return qtReadOnlyErr.
            This is consistent with the behavior of most extraction properties.
*/


/*
 *  QTAudioTrackInsertRegistryInfo
 *  
 *  Summary:
 *    Parameters for registering an Audio Context Track Insert during
 *    Movie Audio Extraction
 *  
 *  Discussion:
 *    This is used with the
 *    kQTMovieAudioExtractionMoviePropertyID_RegisterTrackInsert
 *    property.
 */
struct QTAudioTrackInsertRegistryInfo {

  /*
   * The track of the source movie on which to apply the insert.
   */
  Track               track;

  /*
   * The Audio Context Insert registration info (channel layouts,
   * callbacks).
   */
  QTAudioContextInsertRegistryInfo  regInfo;
};
typedef struct QTAudioTrackInsertRegistryInfo QTAudioTrackInsertRegistryInfo;
typedef QTAudioTrackInsertRegistryInfo * QTAudioTrackInsertRegistryInfoRef;
/* Movie and Track level audio context inserts for extraction (kQTPropertyClass_MovieAudioExtraction_Audio)*/

/*
 */
enum {

  /*
   * kQTMovieAudioExtractionAudioPropertyID_RegisterMovieInsert: Value
   * is QTAudioContextInsertRegistryInfoRef  (Get/Set) Set on an
   * extraction session to register/unregister an Audio Context Insert
   * for the movie summary mix.  When this property is read back
   * (MovieAudioExtractionGetProperty) the channel layout pointers will
   * will be NULL. To unregister, supply a NULL processDataCallback (in
   * which case the rest of the registry info will be ignored).
   */
  kQTMovieAudioExtractionAudioPropertyID_RegisterMovieInsert = 'regm', /* value is QTAudioContextInsertRegistryInfoRef. Get/Set.*/

  /*
   * kQTMovieAudioExtractionAudioPropertyID_RegisterTrackInsert: Value
   * is QTAudioTrackInsertRegistryInfoRef  (Get/Set) Set on an
   * extraction session to register/unregister an Audio Context Insert
   * for a particular track of the movie.  When this property is read
   * back (MovieAudioExtractionGetProperty) the channel layout pointers
   * will will be NULL. To unregister, supply a NULL
   * processDataCallback (in which case the rest of the registry info
   * will be ignored).
   */
  kQTMovieAudioExtractionAudioPropertyID_RegisterTrackInsert = 'regt' /* value is QTAudioTrackInsertRegistryInfoRef. Get/Set.*/
};


#define kQTMovieAudioExtractionMoviePropertyID_RegisterInsert  Use kQTPropertyClass_MovieAudioExtraction_Audio / kQTMovieAudioExtractionAudioPropertyID_RegisterMovieInsert instead!

/* Legacy Audio/Sound APIs*/

/*
 *  GetMoviePreferredVolume()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern short 
GetMoviePreferredVolume(Movie theMovie)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMoviePreferredVolume()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMoviePreferredVolume(
  Movie   theMovie,
  short   volume)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMovieVolume()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern short 
GetMovieVolume(Movie theMovie)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetMovieVolume()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetMovieVolume(
  Movie   theMovie,
  short   volume)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackVolume()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern short 
GetTrackVolume(Track theTrack)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTrackVolume()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTrackVolume(
  Track   theTrack,
  short   volume)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTrackSoundLocalizationSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetTrackSoundLocalizationSettings(
  Track     theTrack,
  Handle *  settings)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTrackSoundLocalizationSettings()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
SetTrackSoundLocalizationSettings(
  Track    theTrack,
  Handle   settings)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* Performance properties*/


/*
 */
enum {
  kQTPropertyClass_Performance  = 'perf',

  /*
   * kQTPerformancePropertyID_MediaStallCount:  Value is UInt32. 
   * Get/Set/Listenable Media stalls occur when a media handler is
   * unable to provide its media data at the time required for seamless
   * playback.  The exact interpretation of a track's MediaStallCount
   * property is media-handler dependent, but may indicate conditions
   * such as a video frame not decoded in time, the sound queue runs
   * dry, etc.  When requested on a specific track, this property
   * returns the current stall count of that track.  When requested on
   * a movie, it returns the accumulated MediaStallCounts for all the
   * tracks in the movie. The track property may be set to zero to
   * reset it.  Setting the movie property to zero resets all the track
   * counts. Setting the value to anything other than zero yields
   * paramErr. The movie toolbox defers property-changed notifications
   * to any property listeners until the next time the movie is idled.
   */
  kQTPerformancePropertyID_MediaStallCount = 'stal', /* UInt32, Get/Set/Listenable */

  /*
   * kQTPerformancePropertyID_AudioIOOverloadCount:  Value is UInt32. 
   * Get/Set/Listenable Audio I/O overloads occur when the
   * high-priority audio processing thread does not provide the
   * requested buffer of data in time to ensure seamless playback. 
   * This movie property accumulates the number of Audio Device I/O
   * overloads that are detected during playback of a movie.  I/O
   * overloads that are detected when the movie is not playing (but
   * other movies may be playing), are not counted. This property may
   * be set to zero to reset the counter.  Setting the value to
   * anything other than zero yields paramErr. The movie toolbox defers
   * property-changed notifications to any property listeners until the
   * next time the movie is idled.
   */
  kQTPerformancePropertyID_AudioIOOverloadCount = 'ovct' /* UInt32, Get/Set/Listenable*/
};


/* Movie Visual Adjustment APIs*/


/*
 *  Summary:
 *    Visual movie properties.
 */
enum {

  /*
   * Class for visual properties.
   */
  kQTPropertyClass_Visual       = 'visu',

  /*
   * The hue adjustment for the movie.   The value is a Float32 between
   * -1.0 and 1.0, with 0.0 meaning no adjustment. This adjustment
   * wraps around, such that -1.0 and 1.0 yield the same result.
   */
  kQTVisualPropertyID_Hue       = 'vhue', /* Float32, Read/Write */

  /*
   * The color saturation adjustment for the movie.  The value is a
   * Float32 percentage (1.0f = 100%), such that 0.0 gives grayscale.
   */
  kQTVisualPropertyID_Saturation = 'vsat', /* Float32, Read/Write */

  /*
   * The brightness adjustment for the movie.  The value is a Float32
   * for which -1.0 means full black, 0.0 means no adjustment, and 1.0
   * means full white.
   */
  kQTVisualPropertyID_Brightness = 'vbrt', /* Float32, Read/Write */

  /*
   * The contrast adjustment for the movie.  The value is a Float32
   * percentage (1.0f = 100%), such that 0.0 gives solid grey.
   */
  kQTVisualPropertyID_Contrast  = 'vcon' /* Float32, Read/Write */
};


/*
 *  SetMovieVisualHue()
 *  
 *  Summary:
 *    This API sets the hue adjustment for the movie.
 *  
 *  Discussion:
 *    See kQTPropertyClass_Visual/kQTVisualPropertyID_Hue for details.
 *    The setting is not stored in the movie.  It is only used until
 *    the movie is closed, at which time it is not saved.
 *  
 *  Parameters:
 *    
 *    movie:
 *      [in]  The movie.
 *    
 *    hue:
 *      [in]  New hue adjustment.
 *    
 *    flags:
 *      [in]  Reserved. Pass 0.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMovieVisualHue(
  Movie     movie,
  Float32   hue,
  UInt32    flags)                                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMovieVisualHue()
 *  
 *  Summary:
 *    This API gets the hue adjustment for the movie.
 *  
 *  Discussion:
 *    See kQTPropertyClass_Visual/kQTVisualPropertyID_Hue for details.
 *  
 *  Parameters:
 *    
 *    movie:
 *      [in]  The movie.
 *    
 *    hueOut:
 *      [out] Current hue adjustment.
 *    
 *    flags:
 *      [in]  Reserved. Pass 0.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMovieVisualHue(
  Movie      movie,
  Float32 *  hueOut,
  UInt32     flags)                                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  SetMovieVisualSaturation()
 *  
 *  Summary:
 *    This API sets the color saturation adjustment for the movie.
 *  
 *  Discussion:
 *    See kQTPropertyClass_Visual/kQTVisualPropertyID_Saturation for
 *    details. The setting is not stored in the movie.  It is only used
 *    until the movie is closed, at which time it is not saved.
 *  
 *  Parameters:
 *    
 *    movie:
 *      [in]  The movie.
 *    
 *    saturation:
 *      [in]  New saturation adjustment.
 *    
 *    flags:
 *      [in]  Reserved. Pass 0.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMovieVisualSaturation(
  Movie     movie,
  Float32   saturation,
  UInt32    flags)                                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMovieVisualSaturation()
 *  
 *  Summary:
 *    This API gets the color saturation adjustment for the movie.
 *  
 *  Discussion:
 *    See kQTPropertyClass_Visual/kQTVisualPropertyID_Saturation for
 *    details.
 *  
 *  Parameters:
 *    
 *    movie:
 *      [in]  The movie.
 *    
 *    saturationOut:
 *      [out] Current saturation adjustment.
 *    
 *    flags:
 *      [in]  Reserved. Pass 0.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMovieVisualSaturation(
  Movie      movie,
  Float32 *  saturationOut,
  UInt32     flags)                                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  SetMovieVisualBrightness()
 *  
 *  Summary:
 *    This API sets the brightness adjustment for the movie.
 *  
 *  Discussion:
 *    See kQTPropertyClass_Visual/kQTVisualPropertyID_Brightness for
 *    details. The setting is not stored in the movie.  It is only used
 *    until the movie is closed, at which time it is not saved.
 *  
 *  Parameters:
 *    
 *    movie:
 *      [in]  The movie.
 *    
 *    brightness:
 *      [in]  New brightness adjustment.
 *    
 *    flags:
 *      [in]  Reserved. Pass 0.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMovieVisualBrightness(
  Movie     movie,
  Float32   brightness,
  UInt32    flags)                                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMovieVisualBrightness()
 *  
 *  Summary:
 *    This API gets the brightness adjustment for the movie.
 *  
 *  Discussion:
 *    See kQTPropertyClass_Visual/kQTVisualPropertyID_Brightness for
 *    details.
 *  
 *  Parameters:
 *    
 *    movie:
 *      [in]  The movie.
 *    
 *    brightnessOut:
 *      [out] Current brightness adjustment.
 *    
 *    flags:
 *      [in]  Reserved. Pass 0.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMovieVisualBrightness(
  Movie      movie,
  Float32 *  brightnessOut,
  UInt32     flags)                                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  SetMovieVisualContrast()
 *  
 *  Summary:
 *    This API sets the contrast adjustment for the movie.
 *  
 *  Discussion:
 *    See kQTPropertyClass_Visual/kQTVisualPropertyID_Contrast for
 *    details. The setting is not stored in the movie.  It is only used
 *    until the movie is closed, at which time it is not saved.
 *  
 *  Parameters:
 *    
 *    movie:
 *      [in]  The movie.
 *    
 *    contrast:
 *      [in]  New contrast adjustment.
 *    
 *    flags:
 *      [in]  Reserved. Pass 0.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
SetMovieVisualContrast(
  Movie     movie,
  Float32   contrast,
  UInt32    flags)                                            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  GetMovieVisualContrast()
 *  
 *  Summary:
 *    This API gets the contrast adjustment for the movie.
 *  
 *  Discussion:
 *    See kQTPropertyClass_Visual/kQTVisualPropertyID_Contrast for
 *    details.
 *  
 *  Parameters:
 *    
 *    movie:
 *      [in]  The movie.
 *    
 *    contrastOut:
 *      [out] Current contrast adjustment.
 *    
 *    flags:
 *      [in]  Reserved. Pass 0.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
GetMovieVisualContrast(
  Movie      movie,
  Float32 *  contrastOut,
  UInt32     flags)                                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/* Movie Aperture APIs*/


/*
 *  Summary:
 *    Visual properties of movies for aperture modes.
 */
enum {

  /*
   * You can set the aperture mode property on a movie to indicate
   * whether aspect ratio and clean aperture correction should be
   * performed. The values for this property have the prefix
   * kQTApertureMode_ and are in ImageCompression.h. 
   * When a movie is in clean, production or encoded pixels aperture
   * mode, each track's dimensions are overriden by special dimensions
   * for that mode. The original track dimensions are preserved and can
   * be restored by setting the movie into classic aperture mode.
   */
  kQTVisualPropertyID_ApertureMode = 'apmd' /* OSType, Read/Write/Listen */
};


/*
 *  Summary:
 *    Visual properties of tracks for aperture modes
 *  
 *  Discussion:
 *    A track's dimensions may vary depending on the movie's aperture
 *    mode. The dimensions for a given aperture mode may be accessed
 *    using these properties.
 */
enum {

  /*
   * The track dimensions used in QuickTime 7.0.x and earlier. Setting
   * this property is equivalent to calling SetTrackDimensions, except
   * that SetTrackDimensions also changes the aperture mode to
   * kQTApertureMode_Classic, and setting this property does not.
   */
  kQTVisualPropertyID_ClassicDimensions = 'cldi', /* FixedPoint, Read/Write */

  /*
   * The track dimensions to use in clean aperture mode.
   */
  kQTVisualPropertyID_CleanApertureDimensions = 'cadi', /* FixedPoint, Read/Write */

  /*
   * The track dimensions to use in production aperture mode.
   */
  kQTVisualPropertyID_ProductionApertureDimensions = 'prdi', /* FixedPoint, Read/Write */

  /*
   * The track dimensions to use in encoded pixels aperture mode.
   */
  kQTVisualPropertyID_EncodedPixelsDimensions = 'endi', /* FixedPoint, Read/Write */

  /*
   * True if aperture mode dimensions have been set on this movie, even
   * if they are all identical to the classic dimensions (as is the
   * case for content with square pixels and no edge processing
   * region). 
   * This property can also be tested on a movie, where it is true if
   * any track has aperture mode dimensions.
   */
  kQTVisualPropertyID_HasApertureModeDimensions = 'hamd' /* Boolean, Read */
};


/*
 *  Summary:
 *    Media Characteristics
 */
enum {

  /*
   * Indicates that a media handler supports aperture modes, which
   * enable video to be automatically scaled and cropped to compensate
   * for non-square pixel aspect ratios and to trim possibly-dirty edge
   * processing regions. The dimensions of such a track may change when
   * the movie's aperture mode is changed.
   */
  kCharacteristicSupportsApertureModes = 'apmd'
};

/*
 *  SetTrackApertureModeDimensionsUsingSampleDescription()
 *  
 *  Summary:
 *    Sets a track's aperture mode dimensions using values calculated
 *    using a sample description.
 *  
 *  Discussion:
 *    This function should be used to add information needed to support
 *    aperture modes to newly created tracks. This information is
 *    calculated using the given sample description. If sampleDesc is
 *    NULL, the track's first sample description is used.
 *  
 *  Parameters:
 *    
 *    track:
 *      [in] The track.
 *    
 *    sampleDesc:
 *      [in] The sample description handle.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 (or QuickTime 7.1) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
SetTrackApertureModeDimensionsUsingSampleDescription(
  Track                     track,
  SampleDescriptionHandle   sampleDesc)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  GenerateMovieApertureModeDimensions()
 *  
 *  Summary:
 *    Examines a movie and sets up track aperture mode dimensions.
 *  
 *  Discussion:
 *    This function can be used to add information needed to support
 *    aperture modes to movies created with applications and/or
 *    versions of QuickTime that did not support aperture mode
 *    dimensions. If the image descriptions in video tracks lack tags
 *    describing clean aperture and pixel aspect ratio information, the
 *    media data may be scanned to see if the correct values can be
 *    divined and attached. Then the aperture mode dimensions are
 *    calculated and set for each track. Afterwards, the
 *    kQTVisualPropertyID_HasApertureModeDimensions property will be
 *    set to true for these tracks. Tracks which do not support
 *    aperture modes are not changed.
 *  
 *  Parameters:
 *    
 *    movie:
 *      [in] The movie.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 (or QuickTime 7.1) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
GenerateMovieApertureModeDimensions(Movie movie)              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  GenerateTrackApertureModeDimensions()
 *  
 *  Summary:
 *    Examines a track and sets up aperture mode dimensions.
 *  
 *  Discussion:
 *    This function can be used to add information needed to support
 *    aperture modes to tracks created with applications and/or
 *    versions of QuickTime that did not support aperture mode
 *    dimensions. If the image descriptions in video tracks lack tags
 *    describing clean aperture and pixel aspect ratio information, the
 *    media data may be scanned to see if the correct values can be
 *    divined and attached. Then the aperture mode dimensions are
 *    calculated and set. Afterwards, the
 *    kQTVisualPropertyID_HasApertureModeDimensions property will be
 *    set to true for these tracks. Tracks which do not support
 *    aperture modes are not changed.
 *  
 *  Parameters:
 *    
 *    track:
 *      [in] The track.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 (or QuickTime 7.1) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
GenerateTrackApertureModeDimensions(Track track)              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  RemoveMovieApertureModeDimensions()
 *  
 *  Summary:
 *    Removes aperture mode dimension information from a movie.
 *  
 *  Discussion:
 *    This function removes aperture mode dimension information from a
 *    movie's tracks. It does not attempt to modify sample
 *    descriptions, so it may not completely reverse the effect of
 *    GenerateMovieApertureModeDimensions. It sets the
 *    kQTVisualPropertyID_HasApertureModeDimensions property to false.
 *  
 *  Parameters:
 *    
 *    movie:
 *      [in] The movie.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 (or QuickTime 7.1) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
RemoveMovieApertureModeDimensions(Movie movie)                AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  RemoveTrackApertureModeDimensions()
 *  
 *  Summary:
 *    Removes aperture mode dimension information from a track.
 *  
 *  Discussion:
 *    This function removes aperture mode dimension information from a
 *    track. It does not attempt to modify sample descriptions, so it
 *    may not completely reverse the effect of
 *    GenerateTrackApertureModeDimensions. It sets the
 *    kQTVisualPropertyID_HasApertureModeDimensions property to false.
 *  
 *  Parameters:
 *    
 *    track:
 *      [in] The track.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 (or QuickTime 7.1) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
RemoveTrackApertureModeDimensions(Track track)                AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;



/*****
    Error reporting
*****/
struct QTErrorReplacementRecord {
  long                numEntries;
  StringPtr           replacementString[1];   /* array of numEntries StringPtrs (each String is allocated separately).*/
};
typedef struct QTErrorReplacementRecord QTErrorReplacementRecord;
typedef QTErrorReplacementRecord *      QTErrorReplacementPtr;
/*
    QTAddMovieError is used to add orthogonal errors to a list of errors that will
    later be reported (at the end of an import or playback, for example).  Errors are stored
    in 'qter' resources within the component.
    
    QTAddMovieError(Movie       addTo,                          // in: movie to add error to
                    Component   adder,                          // in: component which is adding the error
                    long        errorCode,                      // in: error code being added
                    QTErrorReplacementPtr   stringReplacements);// in: list of strings to subsitute (in order) for "^1", "^2", etc
*/
/*
 *  QTAddMovieError()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTAddMovieError(
  Movie                   movieH,
  Component               c,
  long                    errorCode,
  QTErrorReplacementPtr   stringReplacements)                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*****
    Access Keys
*****/
enum {
  kAccessKeyAtomType            = 'acky'
};

enum {
  kAccessKeySystemFlag          = 1L << 0
};

/*
 *  QTGetAccessKeys()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTGetAccessKeys(
  Str255             accessKeyType,
  long               flags,
  QTAtomContainer *  keys)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTRegisterAccessKey()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTRegisterAccessKey(
  Str255   accessKeyType,
  long     flags,
  Handle   accessKey)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTUnregisterAccessKey()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTUnregisterAccessKey(
  Str255   accessKeyType,
  long     flags,
  Handle   accessKey)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*****
    Content Restrictions
*****/

/*
 *  QTGetMovieRestrictions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTGetMovieRestrictions(
  Movie               theMovie,
  QTRestrictionSet *  outRestrictionSet,
  UInt32 *            outSeed)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*
 *  QTRestrictionsGetInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTRestrictionsGetInfo(
  QTRestrictionSet   inRestrictionSet,
  long *             outRestrictionClassCount,
  long *             outSeed)                                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTRestrictionsGetIndClass()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTRestrictionsGetIndClass(
  QTRestrictionSet   inRestrictionSet,
  long               inIndex,
  OSType *           outClass)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTRestrictionsGetItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTRestrictionsGetItem(
  QTRestrictionSet   inRestrictionSet,
  OSType             inRestrictionClass,
  UInt32 *           outRestrictions)                         AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTGetSupportedRestrictions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTGetSupportedRestrictions(
  OSType    inRestrictionClass,
  UInt32 *  outRestrictionIDs)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTCreateUUID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern OSErr 
QTCreateUUID(
  QTUUID *  outUUID,
  long      creationFlags)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  QTEqualUUIDs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern Boolean 
QTEqualUUIDs(
  const QTUUID *  uuid1,
  const QTUUID *  uuid2)                                      AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;




/*****
    Time table
*****/
/*
 *  MakeTrackTimeTable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
MakeTrackTimeTable(
  Track       trackH,
  long **     offsets,
  TimeValue   startTime,
  TimeValue   endTime,
  TimeValue   timeIncrement,
  short       firstDataRefIndex,
  short       lastDataRefIndex,
  long *      retdataRefSkew)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MakeMediaTimeTable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
MakeMediaTimeTable(
  Media       theMedia,
  long **     offsets,
  TimeValue   startTime,
  TimeValue   endTime,
  TimeValue   timeIncrement,
  short       firstDataRefIndex,
  short       lastDataRefIndex,
  long *      retdataRefSkew)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetMaxLoadedTimeInMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
GetMaxLoadedTimeInMovie(
  Movie        theMovie,
  TimeValue *  time)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTMovieNeedsTimeTable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTMovieNeedsTimeTable(
  Movie      theMovie,
  Boolean *  needsTimeTable)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTGetDataRefMaxFileOffset()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTGetDataRefMaxFileOffset(
  Movie    movieH,
  OSType   dataRefType,
  Handle   dataRef,
  long *   offset)                                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



enum {
  kQTIdlePriority               = 10,
  kQTNonRealTimePriority        = 20,
  kQTRealTimeSharedPriority     = 25,
  kQTRealTimePriority           = 30
};


/*
 *  NewQTCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTCallBackUPP
NewQTCallBackUPP(QTCallBackProcPtr userRoutine)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQTSyncTaskUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTSyncTaskUPP
NewQTSyncTaskUPP(QTSyncTaskProcPtr userRoutine)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewMovieRgnCoverUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MovieRgnCoverUPP
NewMovieRgnCoverUPP(MovieRgnCoverProcPtr userRoutine)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewMovieProgressUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MovieProgressUPP
NewMovieProgressUPP(MovieProgressProcPtr userRoutine)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewMovieDrawingCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MovieDrawingCompleteUPP
NewMovieDrawingCompleteUPP(MovieDrawingCompleteProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewTrackTransferUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TrackTransferUPP
NewTrackTransferUPP(TrackTransferProcPtr userRoutine)         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewGetMovieUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern GetMovieUPP
NewGetMovieUPP(GetMovieProcPtr userRoutine)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewMoviePreviewCallOutUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MoviePreviewCallOutUPP
NewMoviePreviewCallOutUPP(MoviePreviewCallOutProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewTextMediaUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TextMediaUPP
NewTextMediaUPP(TextMediaProcPtr userRoutine)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewActionsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ActionsUPP
NewActionsUPP(ActionsProcPtr userRoutine)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewDoMCActionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DoMCActionUPP
NewDoMCActionUPP(DoMCActionProcPtr userRoutine)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewMovieExecuteWiredActionsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MovieExecuteWiredActionsUPP
NewMovieExecuteWiredActionsUPP(MovieExecuteWiredActionsProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewMoviePrePrerollCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MoviePrePrerollCompleteUPP
NewMoviePrePrerollCompleteUPP(MoviePrePrerollCompleteProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQTNextTaskNeededSoonerCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTNextTaskNeededSoonerCallbackUPP
NewQTNextTaskNeededSoonerCallbackUPP(QTNextTaskNeededSoonerCallbackProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*
 *  NewMoviesErrorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MoviesErrorUPP
NewMoviesErrorUPP(MoviesErrorProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewTweenerDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TweenerDataUPP
NewTweenerDataUPP(TweenerDataProcPtr userRoutine)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewQTEffectListFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTEffectListFilterUPP
NewQTEffectListFilterUPP(QTEffectListFilterProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*
 *  DisposeQTCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTCallBackUPP(QTCallBackUPP userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQTSyncTaskUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTSyncTaskUPP(QTSyncTaskUPP userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeMovieRgnCoverUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMovieRgnCoverUPP(MovieRgnCoverUPP userUPP)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeMovieProgressUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMovieProgressUPP(MovieProgressUPP userUPP)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeMovieDrawingCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMovieDrawingCompleteUPP(MovieDrawingCompleteUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeTrackTransferUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTrackTransferUPP(TrackTransferUPP userUPP)             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeGetMovieUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeGetMovieUPP(GetMovieUPP userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeMoviePreviewCallOutUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMoviePreviewCallOutUPP(MoviePreviewCallOutUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeTextMediaUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTextMediaUPP(TextMediaUPP userUPP)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeActionsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeActionsUPP(ActionsUPP userUPP)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeDoMCActionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDoMCActionUPP(DoMCActionUPP userUPP)                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeMovieExecuteWiredActionsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMovieExecuteWiredActionsUPP(MovieExecuteWiredActionsUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeMoviePrePrerollCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMoviePrePrerollCompleteUPP(MoviePrePrerollCompleteUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQTNextTaskNeededSoonerCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTNextTaskNeededSoonerCallbackUPP(QTNextTaskNeededSoonerCallbackUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*
 *  DisposeMoviesErrorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMoviesErrorUPP(MoviesErrorUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeTweenerDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTweenerDataUPP(TweenerDataUPP userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeQTEffectListFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTEffectListFilterUPP(QTEffectListFilterUPP userUPP)   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*
 *  InvokeQTCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQTCallBackUPP(
  QTCallBack     cb,
  long           refCon,
  QTCallBackUPP  userUPP)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQTSyncTaskUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQTSyncTaskUPP(
  void *         task,
  QTSyncTaskUPP  userUPP)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeMovieRgnCoverUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeMovieRgnCoverUPP(
  Movie             theMovie,
  RgnHandle         changedRgn,
  long              refcon,
  MovieRgnCoverUPP  userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeMovieProgressUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeMovieProgressUPP(
  Movie             theMovie,
  short             message,
  short             whatOperation,
  Fixed             percentDone,
  long              refcon,
  MovieProgressUPP  userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeMovieDrawingCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeMovieDrawingCompleteUPP(
  Movie                    theMovie,
  long                     refCon,
  MovieDrawingCompleteUPP  userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeTrackTransferUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeTrackTransferUPP(
  Track             t,
  long              refCon,
  TrackTransferUPP  userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeGetMovieUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeGetMovieUPP(
  long         offset,
  long         size,
  void *       dataPtr,
  void *       refCon,
  GetMovieUPP  userUPP)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeMoviePreviewCallOutUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeMoviePreviewCallOutUPP(
  long                    refcon,
  MoviePreviewCallOutUPP  userUPP)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeTextMediaUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeTextMediaUPP(
  Handle        theText,
  Movie         theMovie,
  short *       displayFlag,
  long          refcon,
  TextMediaUPP  userUPP)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeActionsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeActionsUPP(
  void *            refcon,
  Track             targetTrack,
  long              targetRefCon,
  QTEventRecordPtr  theEvent,
  ActionsUPP        userUPP)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeDoMCActionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeDoMCActionUPP(
  void *         refcon,
  short          action,
  void *         params,
  Boolean *      handled,
  DoMCActionUPP  userUPP)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeMovieExecuteWiredActionsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeMovieExecuteWiredActionsUPP(
  Movie                        theMovie,
  void *                       refcon,
  long                         flags,
  QTAtomContainer              wiredActions,
  MovieExecuteWiredActionsUPP  userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeMoviePrePrerollCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeMoviePrePrerollCompleteUPP(
  Movie                       theMovie,
  OSErr                       prerollErr,
  void *                      refcon,
  MoviePrePrerollCompleteUPP  userUPP)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQTNextTaskNeededSoonerCallbackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQTNextTaskNeededSoonerCallbackUPP(
  TimeValue                          duration,
  unsigned long                      flags,
  void *                             refcon,
  QTNextTaskNeededSoonerCallbackUPP  userUPP)                 AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

/*
 *  InvokeMoviesErrorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeMoviesErrorUPP(
  OSErr           theErr,
  long            refcon,
  MoviesErrorUPP  userUPP)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeTweenerDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ComponentResult
InvokeTweenerDataUPP(
  TweenRecord *               tr,
  void *                      tweenData,
  long                        tweenDataSize,
  long                        dataDescriptionSeed,
  Handle                      dataDescription,
  ICMCompletionProcRecordPtr  asyncCompletionProc,
  UniversalProcPtr            transferProc,
  void *                      refCon,
  TweenerDataUPP              userUPP)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeQTEffectListFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeQTEffectListFilterUPP(
  Component              effect,
  long                   effectMinSource,
  long                   effectMaxSource,
  OSType                 majorClass,
  OSType                 minorClass,
  void *                 refcon,
  QTEffectListFilterUPP  userUPP)                             AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#if __MACH__
  #ifdef __cplusplus
    inline QTCallBackUPP                                        NewQTCallBackUPP(QTCallBackProcPtr userRoutine) { return userRoutine; }
    inline QTSyncTaskUPP                                        NewQTSyncTaskUPP(QTSyncTaskProcPtr userRoutine) { return userRoutine; }
    inline MovieRgnCoverUPP                                     NewMovieRgnCoverUPP(MovieRgnCoverProcPtr userRoutine) { return userRoutine; }
    inline MovieProgressUPP                                     NewMovieProgressUPP(MovieProgressProcPtr userRoutine) { return userRoutine; }
    inline MovieDrawingCompleteUPP                              NewMovieDrawingCompleteUPP(MovieDrawingCompleteProcPtr userRoutine) { return userRoutine; }
    inline TrackTransferUPP                                     NewTrackTransferUPP(TrackTransferProcPtr userRoutine) { return userRoutine; }
    inline GetMovieUPP                                          NewGetMovieUPP(GetMovieProcPtr userRoutine) { return userRoutine; }
    inline MoviePreviewCallOutUPP                               NewMoviePreviewCallOutUPP(MoviePreviewCallOutProcPtr userRoutine) { return userRoutine; }
    inline TextMediaUPP                                         NewTextMediaUPP(TextMediaProcPtr userRoutine) { return userRoutine; }
    inline ActionsUPP                                           NewActionsUPP(ActionsProcPtr userRoutine) { return userRoutine; }
    inline DoMCActionUPP                                        NewDoMCActionUPP(DoMCActionProcPtr userRoutine) { return userRoutine; }
    inline MovieExecuteWiredActionsUPP                          NewMovieExecuteWiredActionsUPP(MovieExecuteWiredActionsProcPtr userRoutine) { return userRoutine; }
    inline MoviePrePrerollCompleteUPP                           NewMoviePrePrerollCompleteUPP(MoviePrePrerollCompleteProcPtr userRoutine) { return userRoutine; }
    inline QTNextTaskNeededSoonerCallbackUPP                    NewQTNextTaskNeededSoonerCallbackUPP(QTNextTaskNeededSoonerCallbackProcPtr userRoutine) { return userRoutine; }
    inline MoviesErrorUPP                                       NewMoviesErrorUPP(MoviesErrorProcPtr userRoutine) { return userRoutine; }
    inline TweenerDataUPP                                       NewTweenerDataUPP(TweenerDataProcPtr userRoutine) { return userRoutine; }
    inline QTEffectListFilterUPP                                NewQTEffectListFilterUPP(QTEffectListFilterProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposeQTCallBackUPP(QTCallBackUPP) { }
    inline void                                                 DisposeQTSyncTaskUPP(QTSyncTaskUPP) { }
    inline void                                                 DisposeMovieRgnCoverUPP(MovieRgnCoverUPP) { }
    inline void                                                 DisposeMovieProgressUPP(MovieProgressUPP) { }
    inline void                                                 DisposeMovieDrawingCompleteUPP(MovieDrawingCompleteUPP) { }
    inline void                                                 DisposeTrackTransferUPP(TrackTransferUPP) { }
    inline void                                                 DisposeGetMovieUPP(GetMovieUPP) { }
    inline void                                                 DisposeMoviePreviewCallOutUPP(MoviePreviewCallOutUPP) { }
    inline void                                                 DisposeTextMediaUPP(TextMediaUPP) { }
    inline void                                                 DisposeActionsUPP(ActionsUPP) { }
    inline void                                                 DisposeDoMCActionUPP(DoMCActionUPP) { }
    inline void                                                 DisposeMovieExecuteWiredActionsUPP(MovieExecuteWiredActionsUPP) { }
    inline void                                                 DisposeMoviePrePrerollCompleteUPP(MoviePrePrerollCompleteUPP) { }
    inline void                                                 DisposeQTNextTaskNeededSoonerCallbackUPP(QTNextTaskNeededSoonerCallbackUPP) { }
    inline void                                                 DisposeMoviesErrorUPP(MoviesErrorUPP) { }
    inline void                                                 DisposeTweenerDataUPP(TweenerDataUPP) { }
    inline void                                                 DisposeQTEffectListFilterUPP(QTEffectListFilterUPP) { }
    inline void                                                 InvokeQTCallBackUPP(QTCallBack cb, long refCon, QTCallBackUPP userUPP) { (*userUPP)(cb, refCon); }
    inline void                                                 InvokeQTSyncTaskUPP(void * task, QTSyncTaskUPP userUPP) { (*userUPP)(task); }
    inline OSErr                                                InvokeMovieRgnCoverUPP(Movie theMovie, RgnHandle changedRgn, long refcon, MovieRgnCoverUPP userUPP) { return (*userUPP)(theMovie, changedRgn, refcon); }
    inline OSErr                                                InvokeMovieProgressUPP(Movie theMovie, short message, short whatOperation, Fixed percentDone, long refcon, MovieProgressUPP userUPP) { return (*userUPP)(theMovie, message, whatOperation, percentDone, refcon); }
    inline OSErr                                                InvokeMovieDrawingCompleteUPP(Movie theMovie, long refCon, MovieDrawingCompleteUPP userUPP) { return (*userUPP)(theMovie, refCon); }
    inline OSErr                                                InvokeTrackTransferUPP(Track t, long refCon, TrackTransferUPP userUPP) { return (*userUPP)(t, refCon); }
    inline OSErr                                                InvokeGetMovieUPP(long offset, long size, void * dataPtr, void * refCon, GetMovieUPP userUPP) { return (*userUPP)(offset, size, dataPtr, refCon); }
    inline Boolean                                              InvokeMoviePreviewCallOutUPP(long refcon, MoviePreviewCallOutUPP userUPP) { return (*userUPP)(refcon); }
    inline OSErr                                                InvokeTextMediaUPP(Handle theText, Movie theMovie, short * displayFlag, long refcon, TextMediaUPP userUPP) { return (*userUPP)(theText, theMovie, displayFlag, refcon); }
    inline OSErr                                                InvokeActionsUPP(void * refcon, Track targetTrack, long targetRefCon, QTEventRecordPtr theEvent, ActionsUPP userUPP) { return (*userUPP)(refcon, targetTrack, targetRefCon, theEvent); }
    inline OSErr                                                InvokeDoMCActionUPP(void * refcon, short action, void * params, Boolean * handled, DoMCActionUPP userUPP) { return (*userUPP)(refcon, action, params, handled); }
    inline OSErr                                                InvokeMovieExecuteWiredActionsUPP(Movie theMovie, void * refcon, long flags, QTAtomContainer wiredActions, MovieExecuteWiredActionsUPP userUPP) { return (*userUPP)(theMovie, refcon, flags, wiredActions); }
    inline void                                                 InvokeMoviePrePrerollCompleteUPP(Movie theMovie, OSErr prerollErr, void * refcon, MoviePrePrerollCompleteUPP userUPP) { (*userUPP)(theMovie, prerollErr, refcon); }
    inline void                                                 InvokeQTNextTaskNeededSoonerCallbackUPP(TimeValue duration, unsigned long flags, void * refcon, QTNextTaskNeededSoonerCallbackUPP userUPP) { (*userUPP)(duration, flags, refcon); }
    inline void                                                 InvokeMoviesErrorUPP(OSErr theErr, long refcon, MoviesErrorUPP userUPP) { (*userUPP)(theErr, refcon); }
    inline ComponentResult                                      InvokeTweenerDataUPP(TweenRecord * tr, void * tweenData, long tweenDataSize, long dataDescriptionSeed, Handle dataDescription, ICMCompletionProcRecordPtr asyncCompletionProc, UniversalProcPtr transferProc, void * refCon, TweenerDataUPP userUPP) { return (*userUPP)(tr, tweenData, tweenDataSize, dataDescriptionSeed, dataDescription, asyncCompletionProc, transferProc, refCon); }
    inline Boolean                                              InvokeQTEffectListFilterUPP(Component effect, long effectMinSource, long effectMaxSource, OSType majorClass, OSType minorClass, void * refcon, QTEffectListFilterUPP userUPP) { return (*userUPP)(effect, effectMinSource, effectMaxSource, majorClass, minorClass, refcon); }
  #else
    #define NewQTCallBackUPP(userRoutine)                       ((QTCallBackUPP)userRoutine)
    #define NewQTSyncTaskUPP(userRoutine)                       ((QTSyncTaskUPP)userRoutine)
    #define NewMovieRgnCoverUPP(userRoutine)                    ((MovieRgnCoverUPP)userRoutine)
    #define NewMovieProgressUPP(userRoutine)                    ((MovieProgressUPP)userRoutine)
    #define NewMovieDrawingCompleteUPP(userRoutine)             ((MovieDrawingCompleteUPP)userRoutine)
    #define NewTrackTransferUPP(userRoutine)                    ((TrackTransferUPP)userRoutine)
    #define NewGetMovieUPP(userRoutine)                         ((GetMovieUPP)userRoutine)
    #define NewMoviePreviewCallOutUPP(userRoutine)              ((MoviePreviewCallOutUPP)userRoutine)
    #define NewTextMediaUPP(userRoutine)                        ((TextMediaUPP)userRoutine)
    #define NewActionsUPP(userRoutine)                          ((ActionsUPP)userRoutine)
    #define NewDoMCActionUPP(userRoutine)                       ((DoMCActionUPP)userRoutine)
    #define NewMovieExecuteWiredActionsUPP(userRoutine)         ((MovieExecuteWiredActionsUPP)userRoutine)
    #define NewMoviePrePrerollCompleteUPP(userRoutine)          ((MoviePrePrerollCompleteUPP)userRoutine)
    #define NewQTNextTaskNeededSoonerCallbackUPP(userRoutine)   ((QTNextTaskNeededSoonerCallbackUPP)userRoutine)
    #define NewMoviesErrorUPP(userRoutine)                      ((MoviesErrorUPP)userRoutine)
    #define NewTweenerDataUPP(userRoutine)                      ((TweenerDataUPP)userRoutine)
    #define NewQTEffectListFilterUPP(userRoutine)               ((QTEffectListFilterUPP)userRoutine)
    #define DisposeQTCallBackUPP(userUPP)
    #define DisposeQTSyncTaskUPP(userUPP)
    #define DisposeMovieRgnCoverUPP(userUPP)
    #define DisposeMovieProgressUPP(userUPP)
    #define DisposeMovieDrawingCompleteUPP(userUPP)
    #define DisposeTrackTransferUPP(userUPP)
    #define DisposeGetMovieUPP(userUPP)
    #define DisposeMoviePreviewCallOutUPP(userUPP)
    #define DisposeTextMediaUPP(userUPP)
    #define DisposeActionsUPP(userUPP)
    #define DisposeDoMCActionUPP(userUPP)
    #define DisposeMovieExecuteWiredActionsUPP(userUPP)
    #define DisposeMoviePrePrerollCompleteUPP(userUPP)
    #define DisposeQTNextTaskNeededSoonerCallbackUPP(userUPP)
    #define DisposeMoviesErrorUPP(userUPP)
    #define DisposeTweenerDataUPP(userUPP)
    #define DisposeQTEffectListFilterUPP(userUPP)
    #define InvokeQTCallBackUPP(cb, refCon, userUPP)            (*userUPP)(cb, refCon)
    #define InvokeQTSyncTaskUPP(task, userUPP)                  (*userUPP)(task)
    #define InvokeMovieRgnCoverUPP(theMovie, changedRgn, refcon, userUPP) (*userUPP)(theMovie, changedRgn, refcon)
    #define InvokeMovieProgressUPP(theMovie, message, whatOperation, percentDone, refcon, userUPP) (*userUPP)(theMovie, message, whatOperation, percentDone, refcon)
    #define InvokeMovieDrawingCompleteUPP(theMovie, refCon, userUPP) (*userUPP)(theMovie, refCon)
    #define InvokeTrackTransferUPP(t, refCon, userUPP)          (*userUPP)(t, refCon)
    #define InvokeGetMovieUPP(offset, size, dataPtr, refCon, userUPP) (*userUPP)(offset, size, dataPtr, refCon)
    #define InvokeMoviePreviewCallOutUPP(refcon, userUPP)       (*userUPP)(refcon)
    #define InvokeTextMediaUPP(theText, theMovie, displayFlag, refcon, userUPP) (*userUPP)(theText, theMovie, displayFlag, refcon)
    #define InvokeActionsUPP(refcon, targetTrack, targetRefCon, theEvent, userUPP) (*userUPP)(refcon, targetTrack, targetRefCon, theEvent)
    #define InvokeDoMCActionUPP(refcon, action, params, handled, userUPP) (*userUPP)(refcon, action, params, handled)
    #define InvokeMovieExecuteWiredActionsUPP(theMovie, refcon, flags, wiredActions, userUPP) (*userUPP)(theMovie, refcon, flags, wiredActions)
    #define InvokeMoviePrePrerollCompleteUPP(theMovie, prerollErr, refcon, userUPP) (*userUPP)(theMovie, prerollErr, refcon)
    #define InvokeQTNextTaskNeededSoonerCallbackUPP(duration, flags, refcon, userUPP) (*userUPP)(duration, flags, refcon)
    #define InvokeMoviesErrorUPP(theErr, refcon, userUPP)       (*userUPP)(theErr, refcon)
    #define InvokeTweenerDataUPP(tr, tweenData, tweenDataSize, dataDescriptionSeed, dataDescription, asyncCompletionProc, transferProc, refCon, userUPP) (*userUPP)(tr, tweenData, tweenDataSize, dataDescriptionSeed, dataDescription, asyncCompletionProc, transferProc, refCon)
    #define InvokeQTEffectListFilterUPP(effect, effectMinSource, effectMaxSource, majorClass, minorClass, refcon, userUPP) (*userUPP)(effect, effectMinSource, effectMaxSource, majorClass, minorClass, refcon)
  #endif
#endif

/*****
    Connection Speed
*****/
enum {
  ConnectionSpeedPrefsType      = 'cspd',
  ConnectionSpeedIsValidPrefsType = 'vspd'
};

struct ConnectionSpeedPrefsRecord {
  long                connectionSpeed;
};
typedef struct ConnectionSpeedPrefsRecord ConnectionSpeedPrefsRecord;
typedef ConnectionSpeedPrefsRecord *    ConnectionSpeedPrefsPtr;
typedef ConnectionSpeedPrefsPtr *       ConnectionSpeedPrefsHandle;
/*
 *  QTGetConnectionSpeedFromPrefs()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
QTGetConnectionSpeedFromPrefs(long * pConnectionSpeed)        AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*****
    QT International Text Atom Support
*****/
enum {
  kITextRemoveEverythingBut     = 0 << 1,
  kITextRemoveLeaveSuggestedAlternate = 1 << 1
};

enum {
  kITextAtomType                = 'itxt',
  kITextStringAtomType          = 'text'
};

/*
 *  ITextAddString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ITextAddString(
  QTAtomContainer    container,
  QTAtom             parentAtom,
  RegionCode         theRegionCode,
  ConstStr255Param   theString)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ITextRemoveString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ITextRemoveString(
  QTAtomContainer   container,
  QTAtom            parentAtom,
  RegionCode        theRegionCode,
  long              flags)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ITextGetString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
ITextGetString(
  QTAtomContainer   container,
  QTAtom            parentAtom,
  RegionCode        requestedRegion,
  RegionCode *      foundRegion,
  StringPtr         theString)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  QTTextToNativeText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
QTTextToNativeText(
  Handle   theText,
  long     encoding,
  long     flags)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* QTParseTextHREF inContainer atoms*/
enum {
  kQTParseTextHREFText          = 'text', /* string*/
  kQTParseTextHREFBaseURL       = 'burl', /* string*/
  kQTParseTextHREFClickPoint    = 'clik', /* Point; if present, QTParseTextHREF will expand URLs to support server-side image maps*/
  kQTParseTextHREFUseAltDelim   = 'altd', /* boolean; if no kQTParseTextHREFDelimiter, delim is ':'*/
  kQTParseTextHREFDelimiter     = 'delm', /* character*/
  kQTParseTextHREFRecomposeHREF = 'rhrf' /* Boolean; if true, QTParseTextHREF returns recomposed HREF with URL expanded as appropriate*/
};

/* QTParseTextHREF outContainer atoms*/
enum {
  kQTParseTextHREFURL           = 'url ', /* string*/
  kQTParseTextHREFTarget        = 'targ', /* string*/
  kQTParseTextHREFChapter       = 'chap', /* string*/
  kQTParseTextHREFIsAutoHREF    = 'auto', /* Boolean*/
  kQTParseTextHREFIsServerMap   = 'smap', /* Boolean*/
  kQTParseTextHREFHREF          = 'href', /* string; recomposed HREF with URL expanded as appropriate, suitable for mcActionLinkToURL*/
  kQTParseTextHREFEMBEDArgs     = 'mbed' /* string; text between 'E<' and '>' to be used as new movie's embed tags*/
};

/*
 *  QTParseTextHREF()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern OSErr 
QTParseTextHREF(
  char *             href,
  SInt32             hrefLen,
  QTAtomContainer    inContainer,
  QTAtomContainer *  outContainer)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*************************
* track reference types
**************************/
enum {
  kTrackReferenceChapterList    = 'chap',
  kTrackReferenceTimeCode       = 'tmcd',
  kTrackReferenceModifier       = 'ssrc'
};

/*************************
* modifier track types
**************************/
enum {
  kTrackModifierInput           = 0x696E, /* is really 'in'*/
  kTrackModifierType            = 0x7479, /* is really 'ty'*/
  kTrackModifierReference       = 'ssrc',
  kTrackModifierObjectID        = 'obid',
  kTrackModifierInputName       = 'name'
};

enum {
  kInputMapSubInputID           = 'subi'
};

enum {
  kTrackModifierTypeMatrix      = 1,
  kTrackModifierTypeClip        = 2,
  kTrackModifierTypeGraphicsMode = 5,
  kTrackModifierTypeVolume      = 3,
  kTrackModifierTypeBalance     = 4,
  kTrackModifierTypeImage       = 'vide', /* was kTrackModifierTypeSpriteImage*/
  kTrackModifierObjectMatrix    = 6,
  kTrackModifierObjectGraphicsMode = 7,
  kTrackModifierType3d4x4Matrix = 8,
  kTrackModifierCameraData      = 9,
  kTrackModifierSoundLocalizationData = 10,
  kTrackModifierObjectImageIndex = 11,
  kTrackModifierObjectLayer     = 12,
  kTrackModifierObjectVisible   = 13,
  kTrackModifierAngleAspectCamera = 14,
  kTrackModifierPanAngle        = 'pan ',
  kTrackModifierTiltAngle       = 'tilt',
  kTrackModifierVerticalFieldOfViewAngle = 'fov ',
  kTrackModifierObjectQTEventSend = 'evnt',
  kTrackModifierObjectCanBeHitTested = 15
};

struct ModifierTrackGraphicsModeRecord {
  long                graphicsMode;
  RGBColor            opColor;
};
typedef struct ModifierTrackGraphicsModeRecord ModifierTrackGraphicsModeRecord;

/*************************
* tween track types
**************************/
enum {
  kTweenTypeShort               = 1,
  kTweenTypeLong                = 2,
  kTweenTypeFixed               = 3,
  kTweenTypePoint               = 4,
  kTweenTypeQDRect              = 5,
  kTweenTypeQDRegion            = 6,
  kTweenTypeMatrix              = 7,
  kTweenTypeRGBColor            = 8,
  kTweenTypeGraphicsModeWithRGBColor = 9,
  kTweenTypeQTFloatSingle       = 10,
  kTweenTypeQTFloatDouble       = 11,
  kTweenTypeFixedPoint          = 12,
  kTweenType3dScale             = '3sca',
  kTweenType3dTranslate         = '3tra',
  kTweenType3dRotate            = '3rot',
  kTweenType3dRotateAboutPoint  = '3rap',
  kTweenType3dRotateAboutAxis   = '3rax',
  kTweenType3dRotateAboutVector = '3rvc',
  kTweenType3dQuaternion        = '3qua',
  kTweenType3dMatrix            = '3mat',
  kTweenType3dCameraData        = '3cam',
  kTweenType3dAngleAspectCameraData = '3caa',
  kTweenType3dSoundLocalizationData = '3slc',
  kTweenTypePathToMatrixTranslation = 'gxmt',
  kTweenTypePathToMatrixRotation = 'gxpr',
  kTweenTypePathToMatrixTranslationAndRotation = 'gxmr',
  kTweenTypePathToFixedPoint    = 'gxfp',
  kTweenTypePathXtoY            = 'gxxy',
  kTweenTypePathYtoX            = 'gxyx',
  kTweenTypeAtomList            = 'atom',
  kTweenTypePolygon             = 'poly',
  kTweenTypeMultiMatrix         = 'mulm',
  kTweenTypeSpin                = 'spin',
  kTweenType3dMatrixNonLinear   = '3nlr',
  kTweenType3dVRObject          = '3vro'
};

enum {
  kTweenEntry                   = 'twen',
  kTweenData                    = 'data',
  kTweenType                    = 'twnt',
  kTweenStartOffset             = 'twst',
  kTweenDuration                = 'twdu',
  kTweenFlags                   = 'flag',
  kTweenOutputMin               = 'omin',
  kTweenOutputMax               = 'omax',
  kTweenSequenceElement         = 'seqe',
  kTween3dInitialCondition      = 'icnd',
  kTweenInterpolationID         = 'intr',
  kTweenRegionData              = 'qdrg',
  kTweenPictureData             = 'PICT',
  kListElementType              = 'type',
  kListElementDataType          = 'daty',
  kNameAtom                     = 'name',
  kInitialRotationAtom          = 'inro',
  kNonLinearTweenHeader         = 'nlth'
};

/* kTweenFlags*/
enum {
  kTweenReturnDelta             = 1L << 0
};

struct TweenSequenceEntryRecord {
  Fixed               endPercent;
  QTAtomID            tweenAtomID;
  QTAtomID            dataAtomID;
};
typedef struct TweenSequenceEntryRecord TweenSequenceEntryRecord;

#ifdef __QD3D__

struct ThreeDeeVRObjectSample {
  long            rows;  
    long            columns;
   TQ3Matrix4x4    calib1;
    TQ3Matrix4x4    calib2;
    long            reserved1;
 long            reserved2;
};

typedef struct ThreeDeeVRObjectSample ThreeDeeVRObjectSample;

struct ThreeDeeNonLinearSample {
 float           DurFromLastSample;  /* 0 to 1 */
   TQ3Matrix4x4    matrix;
};
typedef struct ThreeDeeNonLinearSample ThreeDeeNonLinearSample;

struct ThreeDeeNonLinearTweenHeaderAtom {
  long    number;
    long    dataSize;
  float   tensionFactor;  /* default is 0 */
 long    reserved1;
 long    reserved2;
};
typedef struct ThreeDeeNonLinearTweenHeaderAtom ThreeDeeNonLinearTweenHeaderAtom;


#endif




#if OLDROUTINENAMES

/*************************
* Video Media routines
**************************/

#define GetVideoMediaGraphicsMode      MediaGetGraphicsMode
#define SetVideoMediaGraphicsMode      MediaSetGraphicsMode

/* use these two routines at your own peril */
#define ResetVideoMediaStatistics      VideoMediaResetStatistics
#define GetVideoMediaStatistics           VideoMediaGetStatistics

/*************************
* Sound Media routines
**************************/

#define GetSoundMediaBalance            MediaGetSoundBalance
#define SetSoundMediaBalance           MediaSetSoundBalance

/*************************
* Text Media routines
**************************/

#define SetTextProc         TextMediaSetTextProc
#define AddTextSample      TextMediaAddTextSample
#define AddTESample          TextMediaAddTESample
#define AddHiliteSample        TextMediaAddHiliteSample
#define FindNextText       TextMediaFindNextText
#define HiliteTextSample  TextMediaHiliteTextSample
#define SetTextSampleData TextMediaSetTextSampleData
#define DrawRaw              TextMediaDrawRaw
#define RawSetup           TextMediaRawSetup
#define RawIdle               TextMediaRawIdle
#define SetTextProperty        TextMediaSetTextProperty

/*************************
* Sprite Media routines
**************************/

#define SetSpriteMediaSpriteProperty  SpriteMediaSetProperty
#define GetSpriteMediaSpriteProperty SpriteMediaGetProperty
#define HitTestSpriteMedia               SpriteMediaHitTestSprites
#define CountSpriteMediaSprites           SpriteMediaCountSprites
#define CountSpriteMediaImages          SpriteMediaCountImages
#define GetSpriteMediaIndImageDescription    SpriteMediaGetIndImageDescription
#define GetDisplayedSampleNumber      SpriteMediaGetDisplayedSampleNumber
#endif /* OLDROUTINENAMES */



/*****
    Content Restrictions
*****/
enum {
  kQTRestrictionClassSave       = 'save',
  kQTRestrictionSaveDontAddMovieResource = (1L << 0),
  kQTRestrictionSaveDontFlatten = (1L << 1),
  kQTRestrictionSaveDontExport  = (1L << 2),
  kQTRestrictionSaveDontExtract = (1L << 3), /* don't allow any form of extraction of content*/
  kQTRestrictionClassEdit       = 'edit',
  kQTRestrictionEditDontCopy    = (1L << 0), /* disable copy */
  kQTRestrictionEditDontCut     = (1L << 1), /* disable cut */
  kQTRestrictionEditDontPaste   = (1L << 2), /* disable paste */
  kQTRestrictionEditDontClear   = (1L << 3), /* disable clear*/
  kQTRestrictionEditDontModify  = (1L << 4), /* don't allow modification of content*/
  kQTRestrictionEditDontExtract = (1L << 5), /* don't allow any form of extraction of content*/
  kQTRestrictionClassPlay       = 'play',
  kQTRestrictionPlayDontPlay    = (1L << 0) /* disable playback   */
};


/*************************
* Video Media routines
**************************/


enum {
  videoFlagDontLeanAhead        = 1L << 0
};




/* use these five routines at your own peril*/
/*
 *  VideoMediaResetStatistics()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
VideoMediaResetStatistics(MediaHandler mh)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  VideoMediaGetStatistics()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
VideoMediaGetStatistics(MediaHandler mh)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  VideoMediaGetStallCount()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
VideoMediaGetStallCount(
  MediaHandler     mh,
  unsigned long *  stalls)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  VideoMediaSetCodecParameter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
VideoMediaSetCodecParameter(
  MediaHandler   mh,
  CodecType      cType,
  OSType         parameterID,
  long           parameterChangeSeed,
  void *         dataPtr,
  long           dataSize)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  VideoMediaGetCodecParameter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
VideoMediaGetCodecParameter(
  MediaHandler   mh,
  CodecType      cType,
  OSType         parameterID,
  Handle         outParameterData)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





/*************************
* Text Media routines
**************************/



/* Return displayFlags for TextProc */
enum {
  txtProcDefaultDisplay         = 0,    /*    Use the media's default*/
  txtProcDontDisplay            = 1,    /*    Don't display the text*/
  txtProcDoDisplay              = 2     /*    Do display the text*/
};

/*
 *  TextMediaSetTextProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
TextMediaSetTextProc(
  MediaHandler   mh,
  TextMediaUPP   TextProc,
  long           refcon)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextMediaAddTextSample()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
TextMediaAddTextSample(
  MediaHandler    mh,
  Ptr             text,
  unsigned long   size,
  short           fontNumber,
  short           fontSize,
  Style           textFace,
  RGBColor *      textColor,
  RGBColor *      backColor,
  short           textJustification,
  Rect *          textBox,
  long            displayFlags,
  TimeValue       scrollDelay,
  short           hiliteStart,
  short           hiliteEnd,
  RGBColor *      rgbHiliteColor,
  TimeValue       duration,
  TimeValue *     sampleTime)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextMediaAddTESample()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
TextMediaAddTESample(
  MediaHandler   mh,
  TEHandle       hTE,
  RGBColor *     backColor,
  short          textJustification,
  Rect *         textBox,
  long           displayFlags,
  TimeValue      scrollDelay,
  short          hiliteStart,
  short          hiliteEnd,
  RGBColor *     rgbHiliteColor,
  TimeValue      duration,
  TimeValue *    sampleTime)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextMediaAddHiliteSample()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
TextMediaAddHiliteSample(
  MediaHandler   mh,
  short          hiliteStart,
  short          hiliteEnd,
  RGBColor *     rgbHiliteColor,
  TimeValue      duration,
  TimeValue *    sampleTime)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextMediaDrawRaw()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
TextMediaDrawRaw(
  MediaHandler            mh,
  GWorldPtr               gw,
  GDHandle                gd,
  void *                  data,
  long                    dataSize,
  TextDescriptionHandle   tdh)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextMediaSetTextProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
TextMediaSetTextProperty(
  MediaHandler   mh,
  TimeValue      atMediaTime,
  long           propertyType,
  void *         data,
  long           dataSize)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextMediaRawSetup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
TextMediaRawSetup(
  MediaHandler            mh,
  GWorldPtr               gw,
  GDHandle                gd,
  void *                  data,
  long                    dataSize,
  TextDescriptionHandle   tdh,
  TimeValue               sampleDuration)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextMediaRawIdle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
TextMediaRawIdle(
  MediaHandler   mh,
  GWorldPtr      gw,
  GDHandle       gd,
  TimeValue      sampleTime,
  long           flagsIn,
  long *         flagsOut)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextMediaGetTextProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern ComponentResult 
TextMediaGetTextProperty(
  MediaHandler   mh,
  TimeValue      atMediaTime,
  long           propertyType,
  void *         data,
  long           dataSize)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


enum {
  findTextEdgeOK                = 1 << 0, /* Okay to find text at specified sample time*/
  findTextCaseSensitive         = 1 << 1, /* Case sensitive search*/
  findTextReverseSearch         = 1 << 2, /* Search from sampleTime backwards*/
  findTextWrapAround            = 1 << 3, /* Wrap search when beginning or end of movie is hit*/
  findTextUseOffset             = 1 << 4 /* Begin search at the given character offset into sample rather than edge*/
};

/*
 *  TextMediaFindNextText()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
TextMediaFindNextText(
  MediaHandler   mh,
  Ptr            text,
  long           size,
  short          findFlags,
  TimeValue      startTime,
  TimeValue *    foundTime,
  TimeValue *    foundDuration,
  long *         offset)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  TextMediaHiliteTextSample()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
TextMediaHiliteTextSample(
  MediaHandler   mh,
  TimeValue      sampleTime,
  short          hiliteStart,
  short          hiliteEnd,
  RGBColor *     rgbHiliteColor)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


enum {
  dropShadowOffsetType          = 'drpo',
  dropShadowTranslucencyType    = 'drpt'
};

/*
 *  TextMediaSetTextSampleData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
TextMediaSetTextSampleData(
  MediaHandler   mh,
  void *         data,
  OSType         dataType)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;






/*************************
* Sprite Media routines
**************************/
/* flags for sprite hit test routines */
enum {
  spriteHitTestBounds           = 1L << 0, /*    point must only be within sprite's bounding box*/
  spriteHitTestImage            = 1L << 1, /*  point must be within the shape of the sprite's image*/
  spriteHitTestInvisibleSprites = 1L << 2, /*  invisible sprites may be hit tested*/
  spriteHitTestIsClick          = 1L << 3, /*  for codecs that want mouse events*/
  spriteHitTestLocInDisplayCoordinates = 1L << 4, /*    set if you want to pass a display coordiate point to SpriteHitTest*/
  spriteHitTestTreatAllSpritesAsHitTestable = 1L << 5 /* set if you want to override each sprites hittestable property as true*/
};

/* atom types for sprite media */
enum {
  kSpriteAtomType               = 'sprt',
  kSpriteImagesContainerAtomType = 'imct',
  kSpriteImageAtomType          = 'imag',
  kSpriteImageDataAtomType      = 'imda',
  kSpriteImageDataRefAtomType   = 'imre',
  kSpriteImageDataRefTypeAtomType = 'imrt',
  kSpriteImageGroupIDAtomType   = 'imgr',
  kSpriteImageRegistrationAtomType = 'imrg',
  kSpriteImageDefaultImageIndexAtomType = 'defi',
  kSpriteSharedDataAtomType     = 'dflt',
  kSpriteNameAtomType           = 'name',
  kSpriteImageNameAtomType      = 'name',
  kSpriteUsesImageIDsAtomType   = 'uses', /* leaf data is an array of QTAtomID's, one per image used*/
  kSpriteBehaviorsAtomType      = 'beha',
  kSpriteImageBehaviorAtomType  = 'imag',
  kSpriteCursorBehaviorAtomType = 'crsr',
  kSpriteStatusStringsBehaviorAtomType = 'sstr',
  kSpriteVariablesContainerAtomType = 'vars',
  kSpriteStringVariableAtomType = 'strv',
  kSpriteFloatingPointVariableAtomType = 'flov'
};

struct QTRuntimeSpriteDescStruct {
  long                version;                /* set to zero*/
  QTAtomID            spriteID;
  short               imageIndex;
  MatrixRecord        matrix;
  short               visible;
  short               layer;
  ModifierTrackGraphicsModeRecord  graphicsMode;
  QTAtomID            actionHandlingSpriteID;
};
typedef struct QTRuntimeSpriteDescStruct QTRuntimeSpriteDescStruct;
typedef QTRuntimeSpriteDescStruct *     QTRuntimeSpriteDescPtr;
/*
   when filling in QTSpriteButtonBehaviorStruct values -1 may be used to indicate that
   the state transition does not change the property
*/
struct QTSpriteButtonBehaviorStruct {
  QTAtomID            notOverNotPressedStateID;
  QTAtomID            overNotPressedStateID;
  QTAtomID            overPressedStateID;
  QTAtomID            notOverPressedStateID;
};
typedef struct QTSpriteButtonBehaviorStruct QTSpriteButtonBehaviorStruct;
typedef QTSpriteButtonBehaviorStruct *  QTSpriteButtonBehaviorPtr;
/*
 *  SpriteMediaSetProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaSetProperty(
  MediaHandler   mh,
  short          spriteIndex,
  long           propertyType,
  void *         propertyValue)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaGetProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaGetProperty(
  MediaHandler   mh,
  short          spriteIndex,
  long           propertyType,
  void *         propertyValue)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaHitTestSprites()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaHitTestSprites(
  MediaHandler   mh,
  long           flags,
  Point          loc,
  short *        spriteHitIndex)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaCountSprites()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaCountSprites(
  MediaHandler   mh,
  short *        numSprites)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaCountImages()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaCountImages(
  MediaHandler   mh,
  short *        numImages)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaGetIndImageDescription()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaGetIndImageDescription(
  MediaHandler             mh,
  short                    imageIndex,
  ImageDescriptionHandle   imageDescription)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaGetDisplayedSampleNumber()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaGetDisplayedSampleNumber(
  MediaHandler   mh,
  long *         sampleNum)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaGetSpriteName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaGetSpriteName(
  MediaHandler   mh,
  QTAtomID       spriteID,
  Str255         spriteName)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaGetImageName()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaGetImageName(
  MediaHandler   mh,
  short          imageIndex,
  Str255         imageName)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaSetSpriteProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaSetSpriteProperty(
  MediaHandler   mh,
  QTAtomID       spriteID,
  long           propertyType,
  void *         propertyValue)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaGetSpriteProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaGetSpriteProperty(
  MediaHandler   mh,
  QTAtomID       spriteID,
  long           propertyType,
  void *         propertyValue)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaHitTestAllSprites()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaHitTestAllSprites(
  MediaHandler   mh,
  long           flags,
  Point          loc,
  QTAtomID *     spriteHitID)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaHitTestOneSprite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaHitTestOneSprite(
  MediaHandler   mh,
  QTAtomID       spriteID,
  long           flags,
  Point          loc,
  Boolean *      wasHit)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaSpriteIndexToID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaSpriteIndexToID(
  MediaHandler   mh,
  short          spriteIndex,
  QTAtomID *     spriteID)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaSpriteIDToIndex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaSpriteIDToIndex(
  MediaHandler   mh,
  QTAtomID       spriteID,
  short *        spriteIndex)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaGetSpriteActionsForQTEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaGetSpriteActionsForQTEvent(
  MediaHandler       mh,
  QTEventRecordPtr   event,
  QTAtomID           spriteID,
  QTAtomContainer *  container,
  QTAtom *           atom)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaSetActionVariable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaSetActionVariable(
  MediaHandler   mh,
  QTAtomID       variableID,
  const float *  value)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaGetActionVariable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaGetActionVariable(
  MediaHandler   mh,
  QTAtomID       variableID,
  float *        value)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaGetIndImageProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
SpriteMediaGetIndImageProperty(
  MediaHandler   mh,
  short          imageIndex,
  long           imagePropertyType,
  void *         imagePropertyValue)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaNewSprite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
SpriteMediaNewSprite(
  MediaHandler             mh,
  QTRuntimeSpriteDescPtr   newSpriteDesc)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaDisposeSprite()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
SpriteMediaDisposeSprite(
  MediaHandler   mh,
  QTAtomID       spriteID)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaSetActionVariableToString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
SpriteMediaSetActionVariableToString(
  MediaHandler   mh,
  QTAtomID       variableID,
  Ptr            theCString)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SpriteMediaGetActionVariableAsString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
SpriteMediaGetActionVariableAsString(
  MediaHandler   mh,
  QTAtomID       variableID,
  Handle *       theCString)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  SpriteMediaNewImage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern ComponentResult 
SpriteMediaNewImage(
  MediaHandler   mh,
  Handle         dataRef,
  OSType         dataRefType,
  QTAtomID       desiredID)                                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  SpriteMediaDisposeImage()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern ComponentResult 
SpriteMediaDisposeImage(
  MediaHandler   mh,
  short          imageIndex)                                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  SpriteMediaImageIndexToID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern ComponentResult 
SpriteMediaImageIndexToID(
  MediaHandler   mh,
  short          imageIndex,
  QTAtomID *     imageID)                                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  SpriteMediaImageIDToIndex()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern ComponentResult 
SpriteMediaImageIDToIndex(
  MediaHandler   mh,
  QTAtomID       imageID,
  short *        imageIndex)                                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;



/*************************
* Flash Media routines
**************************/

/*
 *  FlashMediaSetPan()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
FlashMediaSetPan(
  MediaHandler   mh,
  short          xPercent,
  short          yPercent)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlashMediaSetZoom()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
FlashMediaSetZoom(
  MediaHandler   mh,
  short          factor)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlashMediaSetZoomRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
FlashMediaSetZoomRect(
  MediaHandler   mh,
  long           left,
  long           top,
  long           right,
  long           bottom)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlashMediaGetRefConBounds()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
FlashMediaGetRefConBounds(
  MediaHandler   mh,
  long           refCon,
  long *         left,
  long *         top,
  long *         right,
  long *         bottom)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlashMediaGetRefConID()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
FlashMediaGetRefConID(
  MediaHandler   mh,
  long           refCon,
  long *         refConID)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlashMediaIDToRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
FlashMediaIDToRefCon(
  MediaHandler   mh,
  long           refConID,
  long *         refCon)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlashMediaGetDisplayedFrameNumber()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
FlashMediaGetDisplayedFrameNumber(
  MediaHandler   mh,
  long *         flashFrameNumber)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlashMediaFrameNumberToMovieTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
FlashMediaFrameNumberToMovieTime(
  MediaHandler   mh,
  long           flashFrameNumber,
  TimeValue *    movieTime)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlashMediaFrameLabelToMovieTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
FlashMediaFrameLabelToMovieTime(
  MediaHandler   mh,
  Ptr            theLabel,
  TimeValue *    movieTime)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlashMediaGetFlashVariable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern ComponentResult 
FlashMediaGetFlashVariable(
  MediaHandler   mh,
  char *         path,
  char *         name,
  Handle *       theVariableCStringOut)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlashMediaSetFlashVariable()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern ComponentResult 
FlashMediaSetFlashVariable(
  MediaHandler   mh,
  char *         path,
  char *         name,
  char *         value,
  Boolean        updateFocus)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlashMediaDoButtonActions()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern ComponentResult 
FlashMediaDoButtonActions(
  MediaHandler   mh,
  char *         path,
  long           buttonID,
  long           transition)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  FlashMediaGetSupportedSwfVersion()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern ComponentResult 
FlashMediaGetSupportedSwfVersion(
  MediaHandler     mh,
  unsigned char *  swfVersion)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/* sample format atoms*/
enum {
  kMovieMediaDataReference      = 'mmdr', /* data reference*/
  kMovieMediaDefaultDataReferenceID = 'ddri', /* atom id*/
  kMovieMediaSlaveTime          = 'slti', /* boolean*/
  kMovieMediaSlaveAudio         = 'slau', /* boolean*/
  kMovieMediaSlaveGraphicsMode  = 'slgr', /* boolean*/
  kMovieMediaAutoPlay           = 'play', /* boolean*/
  kMovieMediaLoop               = 'loop', /* UInt8 (0=no loop, 1=loop, 2=palindrome loop)*/
  kMovieMediaUseMIMEType        = 'mime', /* string indicating the MIME type to use for the dataref (usually not required)*/
  kMovieMediaTitle              = 'titl', /* string of the media's title (tooltips)*/
  kMovieMediaAltText            = 'altt', /* string of alternate text if media isn't loaded*/
  kMovieMediaClipBegin          = 'clpb', /* MovieMediaTimeRecord of start time of embedded media*/
  kMovieMediaClipDuration       = 'clpd', /* MovieMediaTimeRecord of duration of embedded media*/
  kMovieMediaRegionAtom         = 'regi', /* contains subatoms that describe layout*/
  kMovieMediaSlaveTrackDuration = 'sltr', /* Boolean indicating that media handler should adjust track and media based on actual embedded movie duration*/
  kMovieMediaEnableFrameStepping = 'enfs', /* boolean. if true stepping on external movie steps frames within embedded movie.*/
  kMovieMediaBackgroundColor    = 'bkcl', /* RGBColor.*/
  kMovieMediaPrerollTime        = 'prer' /* SInt32 indicating preroll time*/
};

/* fit types*/
enum {
  kMovieMediaFitNone            = 0,
  kMovieMediaFitScroll          = 'scro',
  kMovieMediaFitClipIfNecessary = 'hidd',
  kMovieMediaFitFill            = 'fill',
  kMovieMediaFitMeet            = 'meet',
  kMovieMediaFitSlice           = 'slic'
};

/* sub atoms for region atom*/
enum {
  kMovieMediaSpatialAdjustment  = 'fit ', /* OSType from kMovieMediaFit**/
  kMovieMediaRectangleAtom      = 'rect',
  kMovieMediaTop                = 'top ',
  kMovieMediaLeft               = 'left',
  kMovieMediaWidth              = 'wd  ',
  kMovieMediaHeight             = 'ht  '
};

/* contained movie properties*/
enum {
  kMoviePropertyDuration        = 'dura', /* TimeValue **/
  kMoviePropertyTimeScale       = 'tims', /* TimeValue **/
  kMoviePropertyTime            = 'timv', /* TimeValue **/
  kMoviePropertyNaturalBounds   = 'natb', /* Rect **/
  kMoviePropertyMatrix          = 'mtrx', /* Matrix **/
  kMoviePropertyTrackList       = 'tlst' /* long ****/
};


enum {
  kTrackPropertyMediaType       = 'mtyp', /* OSType*/
  kTrackPropertyInstantiation   = 'inst' /* MovieMediaInstantiationInfoRecord*/
};

struct MovieMediaTimeRecord {
  wide                time;
  TimeScale           scale;
};
typedef struct MovieMediaTimeRecord     MovieMediaTimeRecord;
struct MovieMediaInstantiationInfoRecord {
  Boolean             immediately;
  Boolean             pad;
  SInt32              bitRate;
};
typedef struct MovieMediaInstantiationInfoRecord MovieMediaInstantiationInfoRecord;
/*************************
* Movie Media routines
**************************/


/*
 *  MovieMediaGetChildDoMCActionCallback()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern ComponentResult 
MovieMediaGetChildDoMCActionCallback(
  MediaHandler     mh,
  DoMCActionUPP *  doMCActionCallbackProc,
  long *           refcon)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MovieMediaGetDoMCActionCallback()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern ComponentResult 
MovieMediaGetDoMCActionCallback(
  MediaHandler     mh,
  DoMCActionUPP *  doMCActionCallbackProc,
  long *           refcon)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MovieMediaGetCurrentMovieProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern ComponentResult 
MovieMediaGetCurrentMovieProperty(
  MediaHandler   mh,
  OSType         whichProperty,
  void *         value)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MovieMediaGetCurrentTrackProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern ComponentResult 
MovieMediaGetCurrentTrackProperty(
  MediaHandler   mh,
  long           trackID,
  OSType         whichProperty,
  void *         value)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MovieMediaGetChildMovieDataReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern ComponentResult 
MovieMediaGetChildMovieDataReference(
  MediaHandler   mh,
  QTAtomID       dataRefID,
  short          dataRefIndex,
  OSType *       dataRefType,
  Handle *       dataRef,
  QTAtomID *     dataRefIDOut,
  short *        dataRefIndexOut)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MovieMediaSetChildMovieDataReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern ComponentResult 
MovieMediaSetChildMovieDataReference(
  MediaHandler   mh,
  QTAtomID       dataRefID,
  OSType         dataRefType,
  Handle         dataRef)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MovieMediaLoadChildMovieFromDataReference()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern ComponentResult 
MovieMediaLoadChildMovieFromDataReference(
  MediaHandler   mh,
  QTAtomID       dataRefID)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*************************
* 3D Media routines
**************************/
/*
 *  Media3DGetNamedObjectList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
Media3DGetNamedObjectList(
  MediaHandler       mh,
  QTAtomContainer *  objectList)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Media3DGetRendererList()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
Media3DGetRendererList(
  MediaHandler       mh,
  QTAtomContainer *  rendererList)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Media3DGetCurrentGroup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
Media3DGetCurrentGroup(
  MediaHandler   mh,
  void *         group)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Media3DTranslateNamedObjectTo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
Media3DTranslateNamedObjectTo(
  MediaHandler   mh,
  char *         objectName,
  Fixed          x,
  Fixed          y,
  Fixed          z)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Media3DScaleNamedObjectTo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
Media3DScaleNamedObjectTo(
  MediaHandler   mh,
  char *         objectName,
  Fixed          xScale,
  Fixed          yScale,
  Fixed          zScale)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Media3DRotateNamedObjectTo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
Media3DRotateNamedObjectTo(
  MediaHandler   mh,
  char *         objectName,
  Fixed          xDegrees,
  Fixed          yDegrees,
  Fixed          zDegrees)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Media3DSetCameraData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
Media3DSetCameraData(
  MediaHandler   mh,
  void *         cameraData)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Media3DGetCameraData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
Media3DGetCameraData(
  MediaHandler   mh,
  void *         cameraData)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Media3DSetCameraAngleAspect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
Media3DSetCameraAngleAspect(
  MediaHandler    mh,
  QTFloatSingle   fov,
  QTFloatSingle   aspectRatioXToY)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Media3DGetCameraAngleAspect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
Media3DGetCameraAngleAspect(
  MediaHandler     mh,
  QTFloatSingle *  fov,
  QTFloatSingle *  aspectRatioXToY)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  Media3DSetCameraRange()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
Media3DSetCameraRange(
  MediaHandler   mh,
  void *         tQ3CameraRange)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Media3DGetCameraRange()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
Media3DGetCameraRange(
  MediaHandler   mh,
  void *         tQ3CameraRange)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  Media3DGetViewObject()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern ComponentResult 
Media3DGetViewObject(
  MediaHandler   mh,
  void *         tq3viewObject)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/****************************************
*                                       *
*   M O V I E   C O N T R O L L E R     *
*                                       *
****************************************/
enum {
  MovieControllerComponentType  = 'play'
};


enum {
  kMovieControllerQTVRFlag      = 1 << 0,
  kMovieControllerDontDisplayToUser = 1 << 1
};


typedef ComponentInstance               MovieController;
typedef MovieController *               MovieControllerPtr;
enum {
  mcActionIdle                  = 1,    /* no param*/
  mcActionDraw                  = 2,    /* param is WindowRef*/
  mcActionActivate              = 3,    /* no param*/
  mcActionDeactivate            = 4,    /* no param*/
  mcActionMouseDown             = 5,    /* param is pointer to EventRecord*/
  mcActionKey                   = 6,    /* param is pointer to EventRecord*/
  mcActionPlay                  = 8,    /* param is Fixed, play rate*/
  mcActionGoToTime              = 12,   /* param is TimeRecord*/
  mcActionSetVolume             = 14,   /* param is a short*/
  mcActionGetVolume             = 15,   /* param is pointer to a short*/
  mcActionStep                  = 18,   /* param is number of steps (short)*/
  mcActionSetLooping            = 21,   /* param is Boolean*/
  mcActionGetLooping            = 22,   /* param is pointer to a Boolean*/
  mcActionSetLoopIsPalindrome   = 23,   /* param is Boolean*/
  mcActionGetLoopIsPalindrome   = 24,   /* param is pointer to a Boolean*/
  mcActionSetGrowBoxBounds      = 25,   /* param is a Rect*/
  mcActionControllerSizeChanged = 26,   /* no param*/
  mcActionSetSelectionBegin     = 29,   /* param is TimeRecord*/
  mcActionSetSelectionDuration  = 30,   /* param is TimeRecord, action only taken on set-duration*/
  mcActionSetKeysEnabled        = 32,   /* param is Boolean*/
  mcActionGetKeysEnabled        = 33,   /* param is pointer to Boolean*/
  mcActionSetPlaySelection      = 34,   /* param is Boolean*/
  mcActionGetPlaySelection      = 35,   /* param is pointer to Boolean*/
  mcActionSetUseBadge           = 36,   /* param is Boolean*/
  mcActionGetUseBadge           = 37,   /* param is pointer to Boolean*/
  mcActionSetFlags              = 38,   /* param is long of flags*/
  mcActionGetFlags              = 39,   /* param is pointer to a long of flags*/
  mcActionSetPlayEveryFrame     = 40,   /* param is Boolean*/
  mcActionGetPlayEveryFrame     = 41,   /* param is pointer to Boolean*/
  mcActionGetPlayRate           = 42,   /* param is pointer to Fixed*/
  mcActionShowBalloon           = 43,   /* param is a pointer to a boolean. set to false to stop balloon*/
  mcActionBadgeClick            = 44,   /* param is pointer to Boolean. set to false to ignore click*/
  mcActionMovieClick            = 45,   /* param is pointer to event record. change "what" to nullEvt to kill click*/
  mcActionSuspend               = 46,   /* no param*/
  mcActionResume                = 47,   /* no param*/
  mcActionSetControllerKeysEnabled = 48, /* param is Boolean*/
  mcActionGetTimeSliderRect     = 49,   /* param is pointer to rect*/
  mcActionMovieEdited           = 50,   /* no param*/
  mcActionGetDragEnabled        = 51,   /* param is pointer to Boolean*/
  mcActionSetDragEnabled        = 52,   /* param is Boolean*/
  mcActionGetSelectionBegin     = 53,   /* param is TimeRecord*/
  mcActionGetSelectionDuration  = 54,   /* param is TimeRecord*/
  mcActionPrerollAndPlay        = 55,   /* param is Fixed, play rate*/
  mcActionGetCursorSettingEnabled = 56, /* param is pointer to Boolean*/
  mcActionSetCursorSettingEnabled = 57, /* param is Boolean*/
  mcActionSetColorTable         = 58,   /* param is CTabHandle*/
  mcActionLinkToURL             = 59,   /* param is Handle to URL*/
  mcActionCustomButtonClick     = 60,   /* param is pointer to EventRecord*/
  mcActionForceTimeTableUpdate  = 61,   /* no param*/
  mcActionSetControllerTimeLimits = 62, /* param is pointer to 2 time values min/max. do no send this message to controller. used internally only.*/
  mcActionExecuteAllActionsForQTEvent = 63, /* param is ResolvedQTEventSpecPtr*/
  mcActionExecuteOneActionForQTEvent = 64, /* param is ResolvedQTEventSpecPtr*/
  mcActionAdjustCursor          = 65,   /* param is pointer to EventRecord (WindowRef is in message parameter)*/
  mcActionUseTrackForTimeTable  = 66,   /* param is pointer to {long trackID; Boolean useIt}. do not send this message to controller. */
  mcActionClickAndHoldPoint     = 67,   /* param is point (local coordinates). return true if point has click & hold action (e.g., VR object movie autorotate spot)*/
  mcActionShowMessageString     = 68,   /* param is a StringPtr*/
  mcActionShowStatusString      = 69,   /* param is a QTStatusStringPtr*/
  mcActionGetExternalMovie      = 70,   /* param is a QTGetExternalMoviePtr*/
  mcActionGetChapterTime        = 71,   /* param is a QTGetChapterTimePtr*/
  mcActionPerformActionList     = 72,   /* param is a QTAtomSpecPtr*/
  mcActionEvaluateExpression    = 73,   /* param is a QTEvaluateExpressionPtr*/
  mcActionFetchParameterAs      = 74,   /* param is a QTFetchParameterAsPtr*/
  mcActionGetCursorByID         = 75,   /* param is a QTGetCursorByIDPtr*/
  mcActionGetNextURL            = 76,   /* param is a Handle to URL*/
  mcActionMovieChanged          = 77,
  mcActionDoScript              = 78,   /* param is QTDoScriptPtr*/
  mcActionRestartAtTime         = 79,   /* param is QTResartAtTimePtr*/
  mcActionGetIndChapter         = 80,   /* param is QTChapterInfoPtr*/
  mcActionLinkToURLExtended     = 81,   /* param is QTAtomContainer as used by QTParseHREF*/
  mcActionSetVolumeStep         = 82,   /* param is short containing amount to step volume via arrow keys - default = 64*/
  mcActionAutoPlay              = 83,   /* param is Fixed, play rate*/
  mcActionPauseToBuffer         = 84,   /* param is Fixed, play rate on restart*/
  mcActionAppMessageReceived    = 85,   /* param is a long, application message*/
  mcActionMovieFinished         = 86,   /* no param*/
  mcActionEvaluateExpressionWithType = 89, /* param is a QTEvaluateExpressionWithTypePtr*/
  mcActionGetMovieName          = 90,   /* param is a p String Handle*/
  mcActionGetMovieID            = 91,   /* param is pointer to long*/
  mcActionGetMovieActive        = 92,   /* param is pointer to Boolean*/
  mcActionGetKeyboardFocus      = 93,   /* param is QTKeyboardFocusPtr*/
  mcActionSetKeyboardFocus      = 94,   /* param is QTKeyboardFocusPtr*/
  mcActionAddActionNotification = 95,   /* param is QTMCActionNotificationPtr*/
  mcActionRemoveActionNotification = 96, /* param is QTMCActionNotificationPtr*/
  mcActionKeyUp                 = 97,   /* param is pointer to EventRecord */
  mcActionGetConnectionStatus   = 98,   /* param is QTConnectionStatusPtr*/
  mcActionChapterListChanged    = 99,   /* no param */
  mcActionMovieLoadStateChanged = 100,  /* param is SInt32, new load state*/
  mcActionEditStateChanged      = 101,  /* param is a Boolean, editing enabled?*/
  mcActionCurrentChapterChanged = 102   /* param is a UInt32, new chapter index */
};

typedef short                           mcAction;
enum {
  mcFlagSuppressMovieFrame      = 1 << 0,
  mcFlagSuppressStepButtons     = 1 << 1,
  mcFlagSuppressSpeakerButton   = 1 << 2,
  mcFlagsUseWindowPalette       = 1 << 3,
  mcFlagsDontInvalidate         = 1 << 4,
  mcFlagsUseCustomButton        = 1 << 5
};


enum {
  mcPositionDontInvalidate      = 1 << 5
};

typedef unsigned long                   mcFlags;
enum {
  kMCIEEnabledButtonPicture     = 1,
  kMCIEDisabledButtonPicture    = 2,
  kMCIEDepressedButtonPicture   = 3,
  kMCIEEnabledSizeBoxPicture    = 4,
  kMCIEDisabledSizeBoxPicture   = 5,
  kMCIEEnabledUnavailableButtonPicture = 6,
  kMCIEDisabledUnavailableButtonPicture = 7,
  kMCIESoundSlider              = 128,
  kMCIESoundThumb               = 129,
  kMCIEColorTable               = 256,
  kMCIEIsFlatAppearance         = 257,
  kMCIEDoButtonIconsDropOnDepress = 258
};

typedef unsigned long                   MCInterfaceElement;
typedef CALLBACK_API( Boolean , MCActionFilterProcPtr )(MovieController mc, short *action, void *params);
typedef CALLBACK_API( Boolean , MCActionFilterWithRefConProcPtr )(MovieController mc, short action, void *params, long refCon);
typedef CALLBACK_API( Boolean , MCActionNotificationProcPtr )(MovieController mc, short action, void *params, UInt32 inFlags, UInt32 *outFlags, void *refCon);
typedef STACK_UPP_TYPE(MCActionFilterProcPtr)                   MCActionFilterUPP;
typedef STACK_UPP_TYPE(MCActionFilterWithRefConProcPtr)         MCActionFilterWithRefConUPP;
typedef STACK_UPP_TYPE(MCActionNotificationProcPtr)             MCActionNotificationUPP;
/*
    menu related stuff
*/
enum {
  mcInfoUndoAvailable           = 1 << 0,
  mcInfoCutAvailable            = 1 << 1,
  mcInfoCopyAvailable           = 1 << 2,
  mcInfoPasteAvailable          = 1 << 3,
  mcInfoClearAvailable          = 1 << 4,
  mcInfoHasSound                = 1 << 5,
  mcInfoIsPlaying               = 1 << 6,
  mcInfoIsLooping               = 1 << 7,
  mcInfoIsInPalindrome          = 1 << 8,
  mcInfoEditingEnabled          = 1 << 9,
  mcInfoMovieIsInteractive      = 1 << 10
};

/* menu item codes*/
enum {
  mcMenuUndo                    = 1,
  mcMenuCut                     = 3,
  mcMenuCopy                    = 4,
  mcMenuPaste                   = 5,
  mcMenuClear                   = 6
};

/* messages to the application via mcActionAppMessageReceived*/
enum {
  kQTAppMessageSoftwareChanged  = 1,    /* notification to app that installed QuickTime software has been updated*/
  kQTAppMessageWindowCloseRequested = 3, /* request for app to close window containing movie controller*/
  kQTAppMessageExitFullScreenRequested = 4, /* request for app to turn off full screen mode if active*/
  kQTAppMessageDisplayChannels  = 5,    /* request for app to display the channel UI*/
  kQTAppMessageEnterFullScreenRequested = 6 /* request for app to turn on full screen mode*/
};

/* structures used as mcActionFilterProc params*/
struct QTStatusStringRecord {
  long                stringTypeFlags;
  char *              statusString;
};
typedef struct QTStatusStringRecord     QTStatusStringRecord;
typedef QTStatusStringRecord *          QTStatusStringPtr;
struct QTGetExternalMovieRecord {
  long                targetType;             /* set to kTargetMovieName or kTargetMovieID*/
  StringPtr           movieName;
  long                movieID;
  PtrToMovie          theMovie;
  MovieControllerPtr  theController;
};
typedef struct QTGetExternalMovieRecord QTGetExternalMovieRecord;
typedef QTGetExternalMovieRecord *      QTGetExternalMoviePtr;
struct QTGetChapterTimeRecord {
  StringPtr           chapterName;
  TimeRecord          chapterTime;
};
typedef struct QTGetChapterTimeRecord   QTGetChapterTimeRecord;
typedef QTGetChapterTimeRecord *        QTGetChapterTimePtr;
struct QTChapterInfoRecord {
  long                index;                  /* first chapter has index of 1*/
  TimeValue           time;                   /* -1 if no more chapters available*/
  Str255              name;
};
typedef struct QTChapterInfoRecord      QTChapterInfoRecord;
typedef QTChapterInfoRecord *           QTChapterInfoPtr;
struct QTEvaluateExpressionRecord {
  QTAtomSpec          expressionSpec;
  float *             expressionResult;
};
typedef struct QTEvaluateExpressionRecord QTEvaluateExpressionRecord;
typedef QTEvaluateExpressionRecord *    QTEvaluateExpressionPtr;
struct QTEvaluateExpressionWithTypeRecord {
  long                recordSize;             /* Size of structure (fill in at allocation) */
  QTAtomSpec          expressionSpec;
  float *             expressionResult;
  long                fetchAsType;
  Handle              nonNumericResult;
                                              /* Current size is 24 */
};
typedef struct QTEvaluateExpressionWithTypeRecord QTEvaluateExpressionWithTypeRecord;
typedef QTEvaluateExpressionWithTypeRecord * QTEvaluateExpressionWithTypePtr;
struct QTFetchParameterAsRecord {
  QTAtomSpec          paramListSpec;
  long                paramIndex;
  long                paramType;
  long                allowedFlags;
  void *              min;
  void *              max;
  void *              currentValue;
  void *              newValue;
  Boolean             isUnsignedValue;
};
typedef struct QTFetchParameterAsRecord QTFetchParameterAsRecord;
typedef QTFetchParameterAsRecord *      QTFetchParameterAsPtr;
struct QTGetCursorByIDRecord {
  short               cursorID;
  Handle              colorCursorData;
  long                reserved1;
};
typedef struct QTGetCursorByIDRecord    QTGetCursorByIDRecord;
typedef QTGetCursorByIDRecord *         QTGetCursorByIDPtr;
struct QTDoScriptRecord {
  long                scriptTypeFlags;
  char *              command;
  char *              arguments;
};
typedef struct QTDoScriptRecord         QTDoScriptRecord;
typedef QTDoScriptRecord *              QTDoScriptPtr;
struct QTRestartAtTimeRecord {
  TimeValue           startTime;              /* time scale is the movie timescale*/
  Fixed               rate;                   /* if rate is zero, the movie's current rate is maintained*/
};
typedef struct QTRestartAtTimeRecord    QTRestartAtTimeRecord;
typedef QTRestartAtTimeRecord *         QTRestartAtTimePtr;
/* values for paramType field of QTFetchParameterAsRecord*/
enum {
  kFetchAsBooleanPtr            = 1,
  kFetchAsShortPtr              = 2,
  kFetchAsLongPtr               = 3,
  kFetchAsMatrixRecordPtr       = 4,
  kFetchAsModifierTrackGraphicsModeRecord = 5,
  kFetchAsHandle                = 6,
  kFetchAsStr255                = 7,
  kFetchAsFloatPtr              = 8,
  kFetchAsPointPtr              = 9,
  kFetchAsNewAtomContainer      = 10,
  kFetchAsQTEventRecordPtr      = 11,
  kFetchAsFixedPtr              = 12,
  kFetchAsSetControllerValuePtr = 13,
  kFetchAsRgnHandle             = 14,   /* flipped to native*/
  kFetchAsComponentDescriptionPtr = 15,
  kFetchAsCString               = 16
};

enum {
  kQTCursorOpenHand             = -19183,
  kQTCursorClosedHand           = -19182,
  kQTCursorPointingHand         = -19181,
  kQTCursorRightArrow           = -19180,
  kQTCursorLeftArrow            = -19179,
  kQTCursorDownArrow            = -19178,
  kQTCursorUpArrow              = -19177,
  kQTCursorIBeam                = -19176
};



/* keyboard focus items*/

enum {
  kKeyboardAllowFocus           = 1,
  kKeyboardHaveFocus            = 2,
  kKeyboardValidate             = 4
};


enum {
  kRefConNavigateClick          = 'clik'
};


struct QTKeyboardFocusRecord {
  long                recordSize;             /* -> size of structure*/
  long                navigation;             /* -> same as in MediaNavigateTargetRefCon*/
  long                focusRefCon;            /* <-> refcon*/
  short               focusFlags;             /* <-> flags from kKeyboard... enum */
};
typedef struct QTKeyboardFocusRecord    QTKeyboardFocusRecord;
typedef QTKeyboardFocusRecord *         QTKeyboardFocusPtr;
enum {
  kQTMCActionNotifyBefore       = (1L << 0),
  kQTMCActionNotifyAfter        = (1L << 1),
  kQTMCActionNotifyParamChanged = (1L << 8),
  kQTMCActionNotifyCancelled    = (1L << 9),
  kQTMCActionNotifyUserFilterCancelled = (1L << 10),
  kQTMCActionNotifySignature    = 'noti'
};

struct QTMCActionNotificationRecord {
  OSType              returnSignature;        /* Set to zero when passed to movieController, set to 'noti' if mcActionAddActionNotification is implemented*/
  MCActionNotificationUPP  notifyAction;      /* Function to be called at action time*/
  void *              refcon;                 /* Something to pass to the action function*/
  UInt32              flags;                  /* Option flags*/
};
typedef struct QTMCActionNotificationRecord QTMCActionNotificationRecord;
typedef QTMCActionNotificationRecord *  QTMCActionNotificationPtr;
struct QTConnectionStatusRecord {

  short               flags;
  short               error;

  Handle              message;
};
typedef struct QTConnectionStatusRecord QTConnectionStatusRecord;
typedef QTConnectionStatusRecord *      QTConnectionStatusPtr;

/* target management */
/*
 *  MCSetMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCSetMovie(
  MovieController   mc,
  Movie             theMovie,
  WindowRef         movieWindow,
  Point             where)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCGetIndMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Movie 
MCGetIndMovie(
  MovieController   mc,
  short             index)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



#define MCGetMovie(mc) MCGetIndMovie(mc, 0)
/*
 *  MCRemoveAllMovies()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCRemoveAllMovies(MovieController mc)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCRemoveAMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCRemoveAMovie(
  MovieController   mc,
  Movie             m)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCRemoveMovie()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCRemoveMovie(MovieController mc)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* event handling etc. */
/*
 *  MCIsPlayerEvent()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCIsPlayerEvent(
  MovieController      mc,
  const EventRecord *  e)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* obsolete. use MCSetActionFilterWithRefCon instead. */
/*
 *  MCSetActionFilter()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCSetActionFilter(
  MovieController     mc,
  MCActionFilterUPP   blob)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    proc is of the form:
        Boolean userPlayerFilter(MovieController mc, short *action, void *params) =
    proc returns TRUE if it handles the action, FALSE if not
    action is passed as a VAR so that it could be changed by filter
    this is consistent with the current dialog manager stuff
    params is any potential parameters that go with the action
        such as set playback rate to xxx.
*/
/*
 *  MCDoAction()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCDoAction(
  MovieController   mc,
  short             action,
  void *            params)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/* state type things */
/*
 *  MCSetControllerAttached()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCSetControllerAttached(
  MovieController   mc,
  Boolean           attach)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCIsControllerAttached()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCIsControllerAttached(MovieController mc)                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCSetControllerPort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCSetControllerPort(
  MovieController   mc,
  CGrafPtr          gp)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCGetControllerPort()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern CGrafPtr 
MCGetControllerPort(MovieController mc)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCSetVisible()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCSetVisible(
  MovieController   mc,
  Boolean           visible)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCGetVisible()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCGetVisible(MovieController mc)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCGetControllerBoundsRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCGetControllerBoundsRect(
  MovieController   mc,
  Rect *            bounds)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCSetControllerBoundsRect()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCSetControllerBoundsRect(
  MovieController   mc,
  const Rect *      bounds)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCGetControllerBoundsRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern RgnHandle 
MCGetControllerBoundsRgn(MovieController mc)                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCGetWindowRgn()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern RgnHandle 
MCGetWindowRgn(
  MovieController   mc,
  WindowRef         w)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/* other stuff */
/*
 *  MCMovieChanged()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCMovieChanged(
  MovieController   mc,
  Movie             m)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
    called when the app has changed thing about the movie (like bounding rect) or rate. So that we
        can update our graphical (and internal) state accordingly.
*/
/*
 *  MCSetDuration()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCSetDuration(
  MovieController   mc,
  TimeValue         duration)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    duration to use for time slider -- will be reset next time MCMovieChanged is called
        or MCSetMovie is called
*/
/*
 *  MCGetCurrentTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeValue 
MCGetCurrentTime(
  MovieController   mc,
  TimeScale *       scale)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    returns the time value and the time scale it is on. if there are no movies, the
        time scale is passed back as 0. scale is an optional parameter

*/
/*
 *  MCNewAttachedController()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCNewAttachedController(
  MovieController   mc,
  Movie             theMovie,
  WindowRef         w,
  Point             where)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
    makes theMovie the only movie attached to the controller. makes the controller visible.
    the window and where parameters are passed a long to MCSetMovie and behave as
    described there
*/
/*
 *  MCDraw()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCDraw(
  MovieController   mc,
  WindowRef         w)                                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCActivate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCActivate(
  MovieController   mc,
  WindowRef         w,
  Boolean           activate)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCIdle()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCIdle(MovieController mc)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCKey()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCKey(
  MovieController   mc,
  SInt8             key,
  long              modifiers)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCClick()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCClick(
  MovieController   mc,
  WindowRef         w,
  Point             where,
  long              when,
  long              modifiers)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
    calls for editing
*/
/*
 *  MCEnableEditing()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCEnableEditing(
  MovieController   mc,
  Boolean           enabled)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCIsEditingEnabled()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
MCIsEditingEnabled(MovieController mc)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCCopy()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Movie 
MCCopy(MovieController mc)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCCut()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Movie 
MCCut(MovieController mc)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCPaste()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCPaste(
  MovieController   mc,
  Movie             srcMovie)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCClear()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCClear(MovieController mc)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCUndo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCUndo(MovieController mc)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  somewhat special stuff
 */
/*
 *  MCPositionController()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCPositionController(
  MovieController   mc,
  const Rect *      movieRect,
  const Rect *      controllerRect,
  long              someFlags)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  MCGetControllerInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCGetControllerInfo(
  MovieController   mc,
  long *            someFlags)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
 *  MCSetClip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCSetClip(
  MovieController   mc,
  RgnHandle         theClip,
  RgnHandle         movieClip)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCGetClip()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCGetClip(
  MovieController   mc,
  RgnHandle *       theClip,
  RgnHandle *       movieClip)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
 *  MCDrawBadge()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCDrawBadge(
  MovieController   mc,
  RgnHandle         movieRgn,
  RgnHandle *       badgeRgn)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCSetUpEditMenu()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCSetUpEditMenu(
  MovieController   mc,
  long              modifiers,
  MenuRef           mh)                                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCGetMenuString()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCGetMenuString(
  MovieController   mc,
  long              modifiers,
  short             item,
  Str255            aString)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCSetActionFilterWithRefCon()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCSetActionFilterWithRefCon(
  MovieController               mc,
  MCActionFilterWithRefConUPP   blob,
  long                          refCon)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCPtInController()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCPtInController(
  MovieController   mc,
  Point             thePt,
  Boolean *         inController)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCInvalidate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCInvalidate(
  MovieController   mc,
  WindowRef         w,
  RgnHandle         invalidRgn)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCAdjustCursor()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCAdjustCursor(
  MovieController   mc,
  WindowRef         w,
  Point             where,
  long              modifiers)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCGetInterfaceElement()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MCGetInterfaceElement(
  MovieController      mc,
  MCInterfaceElement   whichElement,
  void *               element)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCGetDoActionsProc()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern ComponentResult 
MCGetDoActionsProc(
  MovieController   mc,
  DoMCActionUPP *   doMCActionProc,
  long *            doMCActionRefCon)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCAddMovieSegment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern ComponentResult 
MCAddMovieSegment(
  MovieController   mc,
  Movie             srcMovie,
  Boolean           scaled)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCTrimMovieSegment()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.3 and later
 *    Non-Carbon CFM:   in QuickTimeLib 5.0 and later
 *    Windows:          in qtmlClient.lib 5.0 and later
 */
extern ComponentResult 
MCTrimMovieSegment(MovieController mc)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  MCSetIdleManager()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern ComponentResult 
MCSetIdleManager(
  MovieController   mc,
  IdleManager       im)                                       AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/* Called (but not implemented) by controllers that derive from the standard movie controller.
   All controllers except standard movie controller must delegate this call. */
enum {
  kControllerUnderstandsIdleManagers = 1 << 0
};

/*
 *  MCSetControllerCapabilities()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.6 and later
 *    Non-Carbon CFM:   in QuickTimeLib 6.0 and later
 *    Windows:          in qtmlClient.lib 6.0 and later
 */
extern ComponentResult 
MCSetControllerCapabilities(
  MovieController   mc,
  long              flags,
  long              flagsMask)                                AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;






/****************************************
*                                       *
*       T  I  M  E  B  A  S  E          *
*                                       *
****************************************/
/*
 *  NewTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeBase 
NewTimeBase(void)                                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
DisposeTimeBase(TimeBase tb)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTimeBaseTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeValue 
GetTimeBaseTime(
  TimeBase      tb,
  TimeScale     s,
  TimeRecord *  tr)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTimeBaseTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTimeBaseTime(
  TimeBase            tb,
  const TimeRecord *  tr)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTimeBaseValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTimeBaseValue(
  TimeBase    tb,
  TimeValue   t,
  TimeScale   s)                                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTimeBaseRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Fixed 
GetTimeBaseRate(TimeBase tb)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTimeBaseRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTimeBaseRate(
  TimeBase   tb,
  Fixed      r)                                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTimeBaseStartTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeValue 
GetTimeBaseStartTime(
  TimeBase      tb,
  TimeScale     s,
  TimeRecord *  tr)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTimeBaseStartTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTimeBaseStartTime(
  TimeBase            tb,
  const TimeRecord *  tr)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTimeBaseStopTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeValue 
GetTimeBaseStopTime(
  TimeBase      tb,
  TimeScale     s,
  TimeRecord *  tr)                                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTimeBaseStopTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTimeBaseStopTime(
  TimeBase            tb,
  const TimeRecord *  tr)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTimeBaseFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetTimeBaseFlags(TimeBase tb)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTimeBaseFlags()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTimeBaseFlags(
  TimeBase   tb,
  long       timeBaseFlags)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTimeBaseMasterTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTimeBaseMasterTimeBase(
  TimeBase            slave,
  TimeBase            master,
  const TimeRecord *  slaveZero)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTimeBaseMasterTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeBase 
GetTimeBaseMasterTimeBase(TimeBase tb)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTimeBaseMasterClock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTimeBaseMasterClock(
  TimeBase            slave,
  Component           clockMeister,
  const TimeRecord *  slaveZero)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTimeBaseMasterClock()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentInstance 
GetTimeBaseMasterClock(TimeBase tb)                           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ConvertTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
ConvertTime(
  TimeRecord *  theTime,
  TimeBase      newBase)                                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ConvertTimeScale()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
ConvertTimeScale(
  TimeRecord *  theTime,
  TimeScale     newScale)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  AddTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
AddTime(
  TimeRecord *        dst,
  const TimeRecord *  src)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SubtractTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SubtractTime(
  TimeRecord *        dst,
  const TimeRecord *  src)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTimeBaseStatus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern long 
GetTimeBaseStatus(
  TimeBase      tb,
  TimeRecord *  unpinnedTime)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  SetTimeBaseZero()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
SetTimeBaseZero(
  TimeBase      tb,
  TimeRecord *  zero)                                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTimeBaseEffectiveRate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern Fixed 
GetTimeBaseEffectiveRate(TimeBase tb)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetTimeBaseRateChangeStatus()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
GetTimeBaseRateChangeStatus(
  TimeBase          tb,
  TimeScale         scale,
  Fixed *           ratedChangedTo,
  TimeBaseStatus *  flags,
  TimeRecord *      rateChangeTimeBaseTime,
  TimeRecord *      rateChangeClockTime,
  TimeRecord *      currentClockTime)                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  ConvertTimeToClockTime()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern void 
ConvertTimeToClockTime(TimeRecord * time)                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  GetTimeBaseMasterOffsetTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern TimeBase 
GetTimeBaseMasterOffsetTimeBase(TimeBase tb)                  AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  SetTimeBaseOffsetTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib 6.5 and later
 */
extern OSErr 
SetTimeBaseOffsetTimeBase(
  TimeBase            tb,
  TimeBase            offsettb,
  const TimeRecord *  offsetZero)                             AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  AttachTimeBaseToCurrentThread()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
AttachTimeBaseToCurrentThread(TimeBase tb)                    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  DetachTimeBaseFromCurrentThread()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
DetachTimeBaseFromCurrentThread(TimeBase tb)                  AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  GetTimeBaseThreadAttachState()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
GetTimeBaseThreadAttachState(
  TimeBase   inTimeBase,
  Boolean *  outAttachedToCurrentThread,
  Boolean *  outAttachedToAnyThread)                          AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/****************************************
*                                       *
*       C  A  L  L  B  A  C  K          *
*                                       *
****************************************/
/*
 *  NewCallBack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern QTCallBack 
NewCallBack(
  TimeBase   tb,
  short      cbType)                                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  DisposeCallBack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
DisposeCallBack(QTCallBack cb)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetCallBackType()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern short 
GetCallBackType(QTCallBack cb)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetCallBackTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern TimeBase 
GetCallBackTimeBase(QTCallBack cb)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CallMeWhen()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
CallMeWhen(
  QTCallBack      cb,
  QTCallBackUPP   callBackProc,
  long            refCon,
  long            param1,
  long            param2,
  long            param3)                                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  CancelCallBack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
CancelCallBack(QTCallBack cb)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/****************************************
*                                       *
*       C L O C K   C A L L B A C K     *
*             S U P P O R T             *
*                                       *
****************************************/
/*
 *  AddCallBackToTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
AddCallBackToTimeBase(QTCallBack cb)                          AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  RemoveCallBackFromTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern OSErr 
RemoveCallBackFromTimeBase(QTCallBack cb)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetFirstCallBack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern QTCallBack 
GetFirstCallBack(TimeBase tb)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  GetNextCallBack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern QTCallBack 
GetNextCallBack(QTCallBack cb)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  ExecuteCallBack()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 2.5 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern void 
ExecuteCallBack(QTCallBack cb)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/****************************************
*                                       *
*   M O V I E  P R O P E R T I E S      *
*                                       *
****************************************/

typedef CALLBACK_API( void , QTMoviePropertyListenerProcPtr )(Movie inMovie, QTPropertyClass inPropClass, QTPropertyID inPropID, void *inUserData);
typedef STACK_UPP_TYPE(QTMoviePropertyListenerProcPtr)          QTMoviePropertyListenerUPP;
/*
 *  QTGetMoviePropertyInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
QTGetMoviePropertyInfo(
  Movie                  inMovie,
  QTPropertyClass        inPropClass,
  QTPropertyID           inPropID,
  QTPropertyValueType *  outPropType,
  ByteCount *            outPropValueSize,
  UInt32 *               outPropertyFlags)                    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTGetMovieProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
QTGetMovieProperty(
  Movie                inMovie,
  QTPropertyClass      inPropClass,
  QTPropertyID         inPropID,
  ByteCount            inPropValueSize,
  QTPropertyValuePtr   outPropValueAddress,
  ByteCount *          outPropValueSizeUsed)                  AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTSetMovieProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
QTSetMovieProperty(
  Movie                     inMovie,
  QTPropertyClass           inPropClass,
  QTPropertyID              inPropID,
  ByteCount                 inPropValueSize,
  ConstQTPropertyValuePtr   inPropValueAddress)               AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTAddMoviePropertyListener()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
QTAddMoviePropertyListener(
  Movie                        inMovie,
  QTPropertyClass              inPropClass,
  QTPropertyID                 inPropID,
  QTMoviePropertyListenerUPP   inListenerProc,
  void *                       inUserData)                    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
 *  QTRemoveMoviePropertyListener()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
QTRemoveMoviePropertyListener(
  Movie                        inMovie,
  QTPropertyClass              inPropClass,
  QTPropertyID                 inPropID,
  QTMoviePropertyListenerUPP   inListenerProc,
  void *                       inUserData)                    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;




/****************************************
*                                       *
*   T R A C K  P R O P E R T I E S      *
*                                       *
****************************************/

typedef CALLBACK_API( void , QTTrackPropertyListenerProcPtr )(Track inTrack, QTPropertyClass inPropClass, QTPropertyID inPropID, void *inUserData);
typedef STACK_UPP_TYPE(QTTrackPropertyListenerProcPtr)          QTTrackPropertyListenerUPP;
/*
 *  QTGetTrackPropertyInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
QTGetTrackPropertyInfo(
  Track                  inTrack,
  QTPropertyClass        inPropClass,
  QTPropertyID           inPropID,
  QTPropertyValueType *  outPropType,
  ByteCount *            outPropValueSize,
  UInt32 *               outPropertyFlags)                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTGetTrackProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
QTGetTrackProperty(
  Track                inTrack,
  QTPropertyClass      inPropClass,
  QTPropertyID         inPropID,
  ByteCount            inPropValueSize,
  QTPropertyValuePtr   outPropValueAddress,
  ByteCount *          outPropValueSizeUsed)                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSetTrackProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
QTSetTrackProperty(
  Track                     inTrack,
  QTPropertyClass           inPropClass,
  QTPropertyID              inPropID,
  ByteCount                 inPropValueSize,
  ConstQTPropertyValuePtr   inPropValueAddress)               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTAddTrackPropertyListener()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
QTAddTrackPropertyListener(
  Track                        inTrack,
  QTPropertyClass              inPropClass,
  QTPropertyID                 inPropID,
  QTTrackPropertyListenerUPP   inListenerProc,
  void *                       inUserData)                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTRemoveTrackPropertyListener()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSErr 
QTRemoveTrackPropertyListener(
  Track                        inTrack,
  QTPropertyClass              inPropClass,
  QTPropertyID                 inPropID,
  QTTrackPropertyListenerUPP   inListenerProc,
  void *                       inUserData)                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/****************************************
*                                       *
*     Q T S A M P L E T A B L E         *
*                                       *
****************************************/

typedef long                            QTSampleDescriptionID;
/*
 *  QTSampleTableCreateMutable()
 *  
 *  Summary:
 *    Creates a new empty sample table.
 *  
 *  Discussion:
 *    The newly created sample table will contain no sample references.
 *    When sample references are added, their durations and display
 *    offsets will be interpreted according to the sample table's
 *    current timescale.
 *  
 *  Parameters:
 *    
 *    allocator:
 *      The allocator to use for the new sample table.
 *    
 *    timescale:
 *      The timescale to use for durations and display offsets.
 *    
 *    hints:
 *      Reserved.  Pass NULL.
 *    
 *    newSampleTable:
 *      Points to a variable to receive the new sample table.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTSampleTableCreateMutable(
  CFAllocatorRef             allocator,
  TimeScale                  timescale,
  void *                     hints,
  QTMutableSampleTableRef *  newSampleTable)                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableRetain()
 *  
 *  Summary:
 *    Increments the retain count of a sample table.
 *  
 *  Discussion:
 *    The same sample table is returned for convenience. If sampleTable
 *    is NULL, nothing happens.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern QTSampleTableRef 
QTSampleTableRetain(QTSampleTableRef sampleTable)             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableRelease()
 *  
 *  Summary:
 *    Decrements the retain count of a sample table.
 *  
 *  Discussion:
 *    If the retain count decreases to zero, the sample table is
 *    disposed. If sampleTable is NULL, nothing happens.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern void 
QTSampleTableRelease(QTSampleTableRef sampleTable)            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableCreateMutableCopy()
 *  
 *  Summary:
 *    Copies a sample table.
 *  
 *  Discussion:
 *    All the sample references and sample descriptions in the sample
 *    table are copied.
 *  
 *  Parameters:
 *    
 *    allocator:
 *      The allocator to use for the new sample table.
 *    
 *    sampleTable:
 *      The sample table to copy.
 *    
 *    hints:
 *      Reserved, set to NULL.
 *    
 *    newSampleTable:
 *      Points to a variable to receive the new sample table.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTSampleTableCreateMutableCopy(
  CFAllocatorRef             allocator,
  QTSampleTableRef           sampleTable,
  void *                     hints,
  QTMutableSampleTableRef *  newSampleTable)                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableGetTypeID()
 *  
 *  Summary:
 *    Returns the CFTypeID for QTSampleTableRef.
 *  
 *  Discussion:
 *    You could use this to test whether a CFTypeRef that extracted
 *    from a CF container such as a CFArray was a QTSampleTableRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern CFTypeID 
QTSampleTableGetTypeID(void)                                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableSetTimeScale()
 *  
 *  Summary:
 *    Changes the timescale of a sample table.
 *  
 *  Discussion:
 *    The durations and display offsets of all the sample references in
 *    the sample table are scaled from the old timescale to the new
 *    timescale. No durations will be scaled to a value less than 1.
 *    Display offsets will be adjusted to avoid display time collisions.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *    
 *    newTimeScale:
 *      The new timescale.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTSampleTableSetTimeScale(
  QTMutableSampleTableRef   sampleTable,
  TimeScale                 newTimeScale)                     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableGetTimeScale()
 *  
 *  Summary:
 *    Returns the timescale of a sample table.
 *  
 *  Discussion:
 *    Returns 0 if sampleTable is NULL.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern TimeScale 
QTSampleTableGetTimeScale(QTSampleTableRef sampleTable)       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  Summary:
 *    Attribute flags for QTSampleTableGetNextAttributeChange
 */
enum {

  /*
   * Set this flag to find first num such that samples num-1 and num
   * are not adjacent, ie, dataOffset of num-1 + dataSize of num-1 !=
   * dataOffset of num
   */
  kQTSampleTableAttribute_DiscontiguousData = 1L << 0,

  /*
   * Set this flag to find the first sample with data size per sample
   * different from that of the starting sample.
   */
  kQTSampleTableAttribute_DataSizePerSampleChange = 1L << 1,

  /*
   * Set this flag to find the first sample with decode duration
   * different from that of the starting sample.
   */
  kQTSampleTableAttribute_DecodeDurationChange = 1L << 2,

  /*
   * Set this flag to find the first sample with display offset
   * different from that of the starting sample.
   */
  kQTSampleTableAttribute_DisplayOffsetChange = 1L << 3,

  /*
   * Set this flag to find the first sample with sample description ID
   * different from that of the starting sample.
   */
  kQTSampleTableAttribute_SampleDescriptionIDChange = 1L << 4,

  /*
   * Set this flag to find the first sample with any media sample flags
   * different from those of the starting sample.
   */
  kQTSampleTableAttribute_SampleFlagsChange = 1L << 5,

  /*
   * If no flags are set, find the first sample with any attribute
   * different from the starting sample.
   */
  kQTSampleTableAnyAttributeChange = 0
};

typedef UInt32                          QTSampleTableAttribute;
/*
 *  QTSampleTableGetNextAttributeChange()
 *  
 *  Summary:
 *    Finds the next sample number at which one or more of given sample
 *    attributes change.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *    
 *    startSampleNum:
 *      A sample number.
 *    
 *    attributeMask:
 *      A collection of flags that indicates which kinds of attribute
 *      changes to search for.
 *    
 *    sampleNumOut:
 *      Points to a variable to receive the next sample number after
 *      startSampleNum at which any of the requested attributes
 *      changes. If no attribute changes are found, this variable is
 *      set to zero.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTSampleTableGetNextAttributeChange(
  QTSampleTableRef         sampleTable,
  SInt64                   startSampleNum,
  QTSampleTableAttribute   attributeMask,
  SInt64 *                 sampleNumOut)                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  QTSampleTableAddSampleDescription()
 *  
 *  Summary:
 *    Adds a sample description to a sample table, returning a sample
 *    description ID that can be used to refer to it.
 *  
 *  Discussion:
 *    You can use the returned sample description ID when adding
 *    samples to the sample table. 
 *    Note: Sample description IDs are local to each sample table. The
 *    same sample description handle may have different IDs when
 *    referenced in different sample tables.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *    
 *    sampleDescriptionH:
 *      The sample description handle. The QTSampleTable will make its
 *      own copy of this handle.
 *    
 *    mediaSampleDescriptionIndex:
 *      Indicates the sample description index of this sample
 *      description in a media. Pass zero for sample descriptions you
 *      add to sample tables, to indicate that this was not retrieved
 *      from a media.
 *    
 *    sampleDescriptionIDOut:
 *      Points to a variable to receive a sample description ID.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTSampleTableAddSampleDescription(
  QTMutableSampleTableRef   sampleTable,
  SampleDescriptionHandle   sampleDescriptionH,
  long                      mediaSampleDescriptionIndex,
  QTSampleDescriptionID *   sampleDescriptionIDOut)           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableCopySampleDescription()
 *  
 *  Summary:
 *    Retrieves a sample description from a sample table.
 *  
 *  Discussion:
 *    The caller is responsible for disposing the returned sampled
 *    description handle with DisposeHandle.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *    
 *    sampleDescriptionID:
 *      The sample description ID.
 *    
 *    mediaSampleDescriptionIndexOut:
 *      Points to a variable to receive a media sample description
 *      index. If the sample description came from a media, this is the
 *      index that could be passed to GetMediaSampleDescription to
 *      retrieve the same sample description handle. The index will be
 *      zero if the sample description did not come directly from a
 *      media. Pass NULL if you do not want to receive this information.
 *    
 *    sampleDescriptionHOut:
 *      Points to a variable to receive a newly allocated sample
 *      description handle. Pass NULL if you do not want one.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTSampleTableCopySampleDescription(
  QTSampleTableRef           sampleTable,
  QTSampleDescriptionID      sampleDescriptionID,
  long *                     mediaSampleDescriptionIndexOut,
  SampleDescriptionHandle *  sampleDescriptionHOut)           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableAddSampleReferences()
 *  
 *  Summary:
 *    Adds sample references to a sample table.
 *  
 *  Discussion:
 *    Note that you must pass the data size per sample, not the total
 *    size of all the samples as with some other APIs.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *    
 *    dataOffset:
 *      Specifies the offset at which the first sample begins.
 *    
 *    dataSizePerSample:
 *      Specifies the number of bytes of data per sample.
 *    
 *    decodeDurationPerSample:
 *      Specifies the decode duration of each sample.
 *    
 *    displayOffset:
 *      Specifies the offset from decode time to display time of each
 *      sample. If the decode times and display times will be the same,
 *      pass 0.
 *    
 *    numberOfSamples:
 *      Specifies the number of samples.  Must be greater than zero.
 *    
 *    sampleFlags:
 *      Specifies the media sample flags for all samples.
 *    
 *    sampleDescriptionID:
 *      Specifies the ID of a sample description that has been added to
 *      the sample table with QTSampleTableAddSampleDescription.
 *    
 *    newSampleNumOut:
 *      Points to a variable to receive the sample number of the first
 *      sample that was added.  Pass NULL if you don't want this
 *      information.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTSampleTableAddSampleReferences(
  QTMutableSampleTableRef   sampleTable,
  SInt64                    dataOffset,
  ByteCount                 dataSizePerSample,
  TimeValue64               decodeDurationPerSample,
  TimeValue64               displayOffset,
  SInt64                    numberOfSamples,
  MediaSampleFlags          sampleFlags,
  QTSampleDescriptionID     sampleDescriptionID,
  SInt64 *                  newSampleNumOut)                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableGetNumberOfSamples()
 *  
 *  Summary:
 *    Returns the number of samples in a sample table.
 *  
 *  Discussion:
 *    Returns 0 if sampleTable is NULL.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern SInt64 
QTSampleTableGetNumberOfSamples(QTSampleTableRef sampleTable) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableReplaceRange()
 *  
 *  Summary:
 *    Replaces a range of samples in a sample table with a range of
 *    samples from another sample table. Can also be used to delete a
 *    range of samples, or to insert samples without removing any.
 *  
 *  Discussion:
 *    This function removes destSampleCount samples from
 *    destSampleTable starting with destStartingSampleNum, and then
 *    inserts sourceSampleCount samples from sourceSampleTable starting
 *    with sourceStartingSampleNum where the removed samples were.
 *    Sample descriptions will be copied if necessary and new sample
 *    description IDs defined.
 *  
 *  Parameters:
 *    
 *    destSampleTable:
 *      The sample table to be modified.
 *    
 *    destStartingSampleNum:
 *      The first sample number in destSampleTable to be replaced or
 *      deleted, or the sample number at which samples should be
 *      inserted.
 *    
 *    destSampleCount:
 *      The number of samples to be removed from destSampleTable. Pass
 *      0 to insert without removing samples.
 *    
 *    sourceSampleTable:
 *      The sample table from which samples should be copied, or NULL
 *      to delete samples.
 *    
 *    sourceStartingSampleNum:
 *      The first sample number to be copied. Ignored when deleting
 *      samples.
 *    
 *    sourceSampleCount:
 *      The number of samples which should be copied. Pass 0 to delete
 *      samples.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTSampleTableReplaceRange(
  QTMutableSampleTableRef   destSampleTable,
  SInt64                    destStartingSampleNum,
  SInt64                    destSampleCount,
  QTSampleTableRef          sourceSampleTable,
  SInt64                    sourceStartingSampleNum,
  SInt64                    sourceSampleCount)                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  QTSampleTableGetDataOffset()
 *  
 *  Summary:
 *    Returns the data offset of a sample.
 *  
 *  Discussion:
 *    Returns 0 if the sample table is NULL, or if the sample number is
 *    out of range.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *    
 *    sampleNum:
 *      The sample number.  The first sample's number is 1.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern SInt64 
QTSampleTableGetDataOffset(
  QTSampleTableRef   sampleTable,
  SInt64             sampleNum)                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableGetDataSizePerSample()
 *  
 *  Summary:
 *    Returns the data size of a sample.
 *  
 *  Discussion:
 *    Returns 0 if the sample table is NULL, or if the sample number is
 *    out of range.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *    
 *    sampleNum:
 *      The sample number.  The first sample's number is 1.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern ByteCount 
QTSampleTableGetDataSizePerSample(
  QTSampleTableRef   sampleTable,
  SInt64             sampleNum)                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableGetDecodeDuration()
 *  
 *  Summary:
 *    Returns the decode duration of a sample.
 *  
 *  Discussion:
 *    Returns 0 if the sample table is NULL, or if the sample number is
 *    out of range.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *    
 *    sampleNum:
 *      The sample number.  The first sample's number is 1.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern TimeValue64 
QTSampleTableGetDecodeDuration(
  QTSampleTableRef   sampleTable,
  SInt64             sampleNum)                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableGetDisplayOffset()
 *  
 *  Summary:
 *    Returns the offset from decode time to display time of a sample.
 *  
 *  Discussion:
 *    Returns 0 if the sample table is NULL, or if the sample number is
 *    out of range.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *    
 *    sampleNum:
 *      The sample number.  The first sample's number is 1.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern TimeValue64 
QTSampleTableGetDisplayOffset(
  QTSampleTableRef   sampleTable,
  SInt64             sampleNum)                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableGetSampleDescriptionID()
 *  
 *  Summary:
 *    Returns the sample description ID of a sample.
 *  
 *  Discussion:
 *    Returns 0 if the sample table is NULL, or if the sample number is
 *    out of range.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *    
 *    sampleNum:
 *      The sample number.  The first sample's number is 1.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern QTSampleDescriptionID 
QTSampleTableGetSampleDescriptionID(
  QTSampleTableRef   sampleTable,
  SInt64             sampleNum)                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableGetSampleFlags()
 *  
 *  Summary:
 *    Returns the media sample flags of a sample.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *    
 *    sampleNum:
 *      The sample number.  The first sample's number is 1.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern MediaSampleFlags 
QTSampleTableGetSampleFlags(
  QTSampleTableRef   sampleTable,
  SInt64             sampleNum)                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  Summary:
 *    Properties of sample tables
 */
enum {

  /*
   * Property class for sample tables.
   */
  kQTPropertyClass_SampleTable  = 'qtst',

  /*
   * The total decode duration of all samples in the sample table. 
   * Read-only.
   */
  kQTSampleTablePropertyID_TotalDecodeDuration = 'tded', /* TimeValue64, Read */

  /*
   * The least display offset in the table. (-50 is a lesser offset
   * than 20.)  Read-only.
   */
  kQTSampleTablePropertyID_MinDisplayOffset = '<ddd', /* TimeValue64, Read */

  /*
   * The greatest display offset in the table. (20 is a greater offset
   * than -50.)  Read-only.
   */
  kQTSampleTablePropertyID_MaxDisplayOffset = '>ddd', /* TimeValue64, Read */

  /*
   * The least display time of all samples in the table, relative to
   * the decode time of the first sample in the table.  Read-only.
   */
  kQTSampleTablePropertyID_MinRelativeDisplayTime = '<dis', /* TimeValue64, Read */

  /*
   * The greatest display time of all samples in the table, relative to
   * the decode time of the first sample in the table.  Read-only.
   */
  kQTSampleTablePropertyID_MaxRelativeDisplayTime = '>dis' /* TimeValue64, Read */
};


/*
 *  QTSampleTableGetPropertyInfo()
 *  
 *  Summary:
 *    Returns information about the properties of a sample table.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *    
 *    inPropClass:
 *      A property class.
 *    
 *    inPropID:
 *      A property ID.
 *    
 *    outPropType:
 *      A pointer to memory allocated to hold the property type on
 *      return. Pass NULL if you do not want this information.
 *    
 *    outPropValueSize:
 *      A pointer to memory allocated to hold the size of the property
 *      value on return. Pass NULL if you do not want this information.
 *    
 *    outPropertyFlags:
 *      A pointer to memory allocated to hold property flags on return.
 *      Pass NULL if you do not want this information.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTSampleTableGetPropertyInfo(
  QTSampleTableRef       sampleTable,
  QTPropertyClass        inPropClass,
  QTPropertyID           inPropID,
  QTPropertyValueType *  outPropType,            /* can be NULL */
  ByteCount *            outPropValueSize,       /* can be NULL */
  UInt32 *               outPropertyFlags)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableGetProperty()
 *  
 *  Summary:
 *    Returns the value of a specific sample table property.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *    
 *    inPropClass:
 *      A property class.
 *    
 *    inPropID:
 *      A property ID.
 *    
 *    inPropValueSize:
 *      The size of the buffer allocated to hold the property value.
 *    
 *    outPropValueAddress:
 *      A pointer to the buffer allocated to hold the property value.
 *    
 *    outPropValueSizeUsed:
 *      On return, the actual size of the value written to the buffer.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTSampleTableGetProperty(
  QTSampleTableRef     sampleTable,
  QTPropertyClass      inPropClass,
  QTPropertyID         inPropID,
  ByteCount            inPropValueSize,
  QTPropertyValuePtr   outPropValueAddress,
  ByteCount *          outPropValueSizeUsed)       /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTSampleTableSetProperty()
 *  
 *  Summary:
 *    Sets the value of a specific sample table property.
 *  
 *  Parameters:
 *    
 *    sampleTable:
 *      The sample table.
 *    
 *    inPropClass:
 *      A property class.
 *    
 *    inPropID:
 *      A property ID.
 *    
 *    inPropValueSize:
 *      The size of the property value.
 *    
 *    inPropValueAddress:
 *      A pointer to the property value.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTSampleTableSetProperty(
  QTSampleTableRef          sampleTable,
  QTPropertyClass           inPropClass,
  QTPropertyID              inPropID,
  ByteCount                 inPropValueSize,
  ConstQTPropertyValuePtr   inPropValueAddress)               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;





/****************************************************************************
*                                                                           *
*           M E T A  D A T A                                                *
*                                                                           *
* QUICKTIME METADATA API OVERVIEW                                           *
*                                                                           *
* A QTMetaDataRef represents a metadata repository consisting of one or     *
* more native metadata containers. The QuickTime MetaData API supports      *
* unified access to and management of these containers.                     *
*                                                                           *
* Each container may be addressed by its storage format                     *
* (kQTMetaDataStorageFormat). Initially, there is support for classic       *
* QuickTime UserData, iTunes metadata, and a richer QuickTime metadata      *
* container format. A QTMetaDataRef may have one or all of these. No        *
* direct access to the native storage containers is provided.               *
*                                                                           *
* Each container consists of some number of metadata items. Metadata items  *
* correspond to individually labeled values with characteristics such as    *
* keys, data types, locale information, etc. What are called items here     *
* are sometimes referred to as attributes or properties in other metadata   *
* systems. Here, the focus is on the management of the pieces of metadata   *
* instead of the associations with objects. This parallels existing         *
* management of the classic QuickTime UserData construct.                   *
*                                                                           *
* QTMetaDataRefs may be associated with the Movie, Track and Media levels.  *
* This parallels UserData placement today but provides access to other      *
* kinds of metadata storage at those levels.                                *
*                                                                           *
* A metadata item is assigned a runtime identifier (QTMetaDataItem) that    *
* along with the QTMetaDataRef identifies the particular item (and value)   *
* across all native containers managed by the QTMetaDataRef.                *
*                                                                           *
* Each item is addressed by a key (or label). The key is not necessarily    *
* unique within its container as it is possible to have multiple items      *
* with the same key (e.g., multiple author items). Operations exist to      *
* enumerate all items or only items with a particular key.                  *
*                                                                           *
* Because a QTMetaDataRef may provide access to different native metadata   *
* containers with differing key structures (a four-char-code for one, a     *
* string for another, etc.), the key structure is also specified. A         *
* QTMetaDataKeyFormat indicates the key structure in APIs accepting keys.   *
* This is also done because some container formats allow multiple key       *
* structures or multiple versions of key structures.                        *
*                                                                           *
* To allow unified access across disparate containers, a wildcard storage   *
* format can be specified. This will direct operations like searches        *
* across container formats. A special key format called                     *
* kQTMetaDataKeyFormatCommon indicates one of a set of common keys that     *
* can be handled by native containers (e.g., copyright).                    *
*                                                                           *
* So, both of these modes of operation are possible: - access metadata      *
* regardless of native container format through the use a common key -      *
* access metadata natively using a native key format                        *
*                                                                           *
****************************************************************************/
/* Opaque reference to a metadata object*/
typedef struct OpaqueQTMetaDataRef*     QTMetaDataRef;
/* Opaque identifier for metadata item*/
typedef UInt64                          QTMetaDataItem;
enum {
  kQTMetaDataItemUninitialized  = 0     /* Uninitialized metadata item identifier*/
};

/*
    Metadata Storage Format.
*/
typedef OSType                          QTMetaDataStorageFormat;
enum {
  kQTMetaDataStorageFormatWildcard = 0  /* Wildcard storage format*/
};

/*
    Metadata Key Format.
*/
typedef OSType                          QTMetaDataKeyFormat;
enum {
  kQTMetaDataKeyFormatWildcard  = 0     /* Match any key regardless of key format*/
};

/****************************************
 *  Common Key Format                   *
 ***************************************/
enum {
  kQTMetaDataKeyFormatCommon    = 'comn'
};

/* Pre-defined meta keys*/
enum {
  kQTMetaDataCommonKeyAuthor    = 'auth',
  kQTMetaDataCommonKeyComment   = 'cmmt',
  kQTMetaDataCommonKeyCopyright = 'cprt',
  kQTMetaDataCommonKeyDirector  = 'dtor',
  kQTMetaDataCommonKeyDisplayName = 'name',
  kQTMetaDataCommonKeyInformation = 'info',
  kQTMetaDataCommonKeyKeywords  = 'keyw',
  kQTMetaDataCommonKeyProducer  = 'prod',
  kQTMetaDataCommonKeyAlbum     = 'albm',
  kQTMetaDataCommonKeyArtist    = 'arts',
  kQTMetaDataCommonKeyArtwork   = 'artw',
  kQTMetaDataCommonKeyChapterName = 'chap',
  kQTMetaDataCommonKeyComposer  = 'comp',
  kQTMetaDataCommonKeyDescription = 'desc',
  kQTMetaDataCommonKeyGenre     = 'genr',
  kQTMetaDataCommonKeyOriginalFormat = 'orif',
  kQTMetaDataCommonKeyOriginalSource = 'oris',
  kQTMetaDataCommonKeyPerformers = 'perf',
  kQTMetaDataCommonKeySoftware  = 'soft',
  kQTMetaDataCommonKeyWriter    = 'wrtr'
};


/****************************************
 *  QuickTime Native Metadata Format    *
 ***************************************/
/* QTMetaDataStorageFormat type*/
enum {
  kQTMetaDataStorageFormatQuickTime = 'mdta' /* QuickTime metadata storage format*/
};

/* QTMetaDataKeyFormat type*/
enum {
  kQTMetaDataKeyFormatQuickTime = 'mdta' /* Reverse DNS format*/
};

/****************************************
 *  iTunes Native Metadata Format       *
 ***************************************/
/* QTMetaDataStorageFormat type*/
enum {
  kQTMetaDataStorageFormatiTunes = 'itms' /* iTunes metadata storage format*/
};

/* QTMetaDataKeyFormat type*/
enum {
  kQTMetaDataKeyFormatiTunesShortForm = 'itsk', /* FourCharCode*/
  kQTMetaDataKeyFormatiTunesLongForm = 'itlk' /* Reverse DNS format*/
};

/* The list of keys for iTunes metadata is TBA.*/

/****************************************
 *  UserData Native Format              *
 ***************************************/
/* QTMetaDataStorageFormat type*/
enum {
  kQTMetaDataStorageFormatUserData = 'udta' /* UserData storage format*/
};

/* QTMetaDataKeyFormat type*/
enum {
  kQTMetaDataKeyFormatUserData  = 'udta' /* FourCharCode*/
};

/* The list of keys are the User Data Identifiers (e.g. kUserDataTextAuthor, kUserDataTextCopyright, etc.)*/

/*
    Mapping from common keys to user data identifiers:
    
    kQTMetaDataCommonKeyAuthor                  -> kUserDataTextAuthor
    kQTMetaDataCommonKeyComment                 -> kUserDataTextComment
    kQTMetaDataCommonKeyCopyright               -> kUserDataTextCopyright
    kQTMetaDataCommonKeyDirector                -> kUserDataTextDirector
    kQTMetaDataCommonKeyDisplayName             -> kUserDataTextFullName
    kQTMetaDataCommonKeyInformation             -> kUserDataTextInformation
    kQTMetaDataCommonKeyKeywords                -> kUserDataTextKeywords
    kQTMetaDataCommonKeyProducer                -> kUserDataTextProducer
    kQTMetaDataCommonKeyAlbum                   -> kUserDataTextAlbum
    kQTMetaDataCommonKeyArtist                  -> kUserDataTextArtist
    kQTMetaDataCommonKeyChapterName             -> kUserDataTextChapter
    kQTMetaDataCommonKeyComposer                -> kUserDataTextComposer
    kQTMetaDataCommonKeyDescription             -> kUserDataTextDescription
    kQTMetaDataCommonKeyGenre                   -> kUserDataTextGenre
    kQTMetaDataCommonKeyOriginalFormat          -> kUserDataTextOriginalFormat
    kQTMetaDataCommonKeyOriginalSource          -> kUserDataTextOriginalSource
    kQTMetaDataCommonKeyPerformers              -> kUserDataTextPerformers
    kQTMetaDataCommonKeySoftware                -> kUserDataTextSoftware
    kQTMetaDataCommonKeyWriter                  -> kUserDataTextWriter
*/
/****************************************
 *  Metadata Property Class ID          *
 ***************************************/
enum {
  kPropertyClass_MetaData       = 'meta'
};

/* Metadata Property ID */

/*
 */
enum {

  /*
   * kQTMetaDataPropertyID_StorageFormats: The list of storage formats
   * (QTMetaDataStorageFormat) associated with this QTMetaDataRef
   * object. Return - C-style array of OSTypes, Read
   */
  kQTMetaDataPropertyID_StorageFormats = 'fmts',

  /*
   * kQTMetaDataPropertyID_OwnerType: The owner type associated with
   * this QTMetaDataRef object. Return - OSType (QT_MOVIE_TYPE,
   * QT_TRACK_TYPE, QT_MEDIA_TYPE), Read
   */
  kQTMetaDataPropertyID_OwnerType = 'ownt',

  /*
   * kQTMetaDataPropertyID_Owner: The owner associated with this
   * QTMetaDataRef object. The QTMetaDataRef object does not
   * necessarily need to have an owner. Return - Movie, Track, or
   * Media, Read
   */
  kQTMetaDataPropertyID_Owner   = 'ownr'
};

/* 
    Metadata Item Property Class ID 
*/
enum {
  kPropertyClass_MetaDataItem   = 'mdit'
};

/* Metadata Item Property ID */

/*
 */
enum {

  /*
   * kQTMetaDataItemPropertyID_Value: The value of the metadata item.
   * Return - C-style array of UInt8, Read
   */
  kQTMetaDataItemPropertyID_Value = 'valu',

  /*
   * kQTMetaDataItemPropertyID_DataType: The value type of the metadata
   * item. Return - UInt32, Read/Write
   */
  kQTMetaDataItemPropertyID_DataType = 'dtyp',

  /*
   * kQTMetaDataItemPropertyID_StorageFormat: The storage format
   * (QTMetaDataStorageFormat). Return - QTMetaDataStorageFormat, Read
   */
  kQTMetaDataItemPropertyID_StorageFormat = 'sfmt',

  /*
   * kQTMetaDataItemPropertyID_Key: The key associated with the
   * metadata item. Return - C-style array of UInt8, Read/Write
   */
  kQTMetaDataItemPropertyID_Key = 'key ',

  /*
   * kQTMetaDataItemPropertyID_KeyFormat: The format of the key used.
   * Return - OSType, Read/Write
   */
  kQTMetaDataItemPropertyID_KeyFormat = 'keyf',

  /*
   * kQTMetaDataItemPropertyID_Locale: The locale identifier based on
   * the naming convention defined by the International Components for
   * Unicode (ICU). The identifier consists of two pieces of ordered
   * information: a language code and a region code. The language code
   * is based on the ISO 639-1 standard, which defines two-character
   * codes, such as "en" and "fr", for the world's most commonly used
   * languages. If a two-letter code is not available, then ISO 639-2
   * three-letter identifiers are accepted as well, for example "haw"
   * for Hawaiian. The region code is defined by ISO 3166-1. The region
   * code is in all caps and appended, after an underscore, after the
   * language code, for example "en_US", "en_GB", and "fr_FR". Return -
   * C-string, Read/Write
   */
  kQTMetaDataItemPropertyID_Locale = 'loc '
};

/* Well-known data type code*/
enum {
  kQTMetaDataTypeBinary         = 0,
  kQTMetaDataTypeUTF8           = 1,
  kQTMetaDataTypeUTF16BE        = 2,
  kQTMetaDataTypeMacEncodedText = 3,
  kQTMetaDataTypeJPEGImage      = 13,
  kQTMetaDataTypePNGImage       = 14,
  kQTMetaDataTypeSignedIntegerBE = 21,  /* The size of the integer is defined by the value size*/
  kQTMetaDataTypeUnsignedIntegerBE = 22, /* The size of the integer is defined by the value size*/
  kQTMetaDataTypeFloat32BE      = 23,
  kQTMetaDataTypeFloat64BE      = 24,
  kQTMetaDataTypeBMPImage       = 27,
  kQTMetaDataTypeQuickTimeMetaData = 28
};


/****************************************
 *  QTMetaDataRef Access                *
 ***************************************/
/*
 *  QTCopyMovieMetaData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTCopyMovieMetaData(
  Movie            inMovie,
  QTMetaDataRef *  outMetaData)                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTCopyTrackMetaData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTCopyTrackMetaData(
  Track            inTrack,
  QTMetaDataRef *  outMetaData)                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTCopyMediaMetaData()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTCopyMediaMetaData(
  Media            inMedia,
  QTMetaDataRef *  outMetaData)                               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTMetaDataRetain()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern QTMetaDataRef 
QTMetaDataRetain(QTMetaDataRef inMetaData)                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTMetaDataRelease()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern void 
QTMetaDataRelease(QTMetaDataRef inMetaData)                   AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTMetaDataCreateFromBuffer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 (or QuickTime 7.2) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTMetaDataCreateFromBuffer(
  const UInt8 *    inBufferPtr,
  ByteCount        inBufferSize,
  QTMetaDataRef *  outMetaData)                               AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  QTMetaDataGetBytes()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 (or QuickTime 7.2) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
QTMetaDataGetBytes(
  QTMetaDataRef   inMetaData,
  ByteCount       inBufferSize,
  UInt8 *         inBufferPtr,
  ByteCount *     outBufferSizeNeeded)                        AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;



/****************************************
 *  Metadata Item Routines              *
 ***************************************/
/*
 *  QTMetaDataGetPropertyInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTMetaDataGetPropertyInfo(
  QTMetaDataRef          inMetaData,
  QTPropertyClass        inPropClass,
  QTPropertyID           inPropID,
  QTPropertyValueType *  outPropType,
  ByteCount *            outPropValueSize,
  UInt32 *               outPropFlags)                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTMetaDataGetProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTMetaDataGetProperty(
  QTMetaDataRef        inMetaData,
  QTPropertyClass      inPropClass,
  QTPropertyID         inPropID,
  ByteCount            inPropValueSize,
  QTPropertyValuePtr   outPropValueAddress,
  ByteCount *          outPropValueSizeUsed)                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTMetaDataSetProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTMetaDataSetProperty(
  QTMetaDataRef             inMetaData,
  QTPropertyClass           inPropClass,
  QTPropertyID              inPropID,
  ByteCount                 inPropValueSize,
  ConstQTPropertyValuePtr   inPropValueAddress)               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTMetaDataGetItemValue()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTMetaDataGetItemValue(
  QTMetaDataRef    inMetaData,
  QTMetaDataItem   inItem,
  UInt8 *          outValuePtr,
  ByteCount        inValueSize,
  ByteCount *      outActualSize)                             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTMetaDataGetNextItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTMetaDataGetNextItem(
  QTMetaDataRef             inMetaData,
  QTMetaDataStorageFormat   inMetaDataFormat,
  QTMetaDataItem            inCurrentItem,
  QTMetaDataKeyFormat       inKeyFormat,
  const UInt8 *             inKeyPtr,
  ByteCount                 inKeySize,
  QTMetaDataItem *          outNextItem)                      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTMetaDataGetItemPropertyInfo()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTMetaDataGetItemPropertyInfo(
  QTMetaDataRef          inMetaData,
  QTMetaDataItem         inItem,
  QTPropertyClass        inPropClass,
  QTPropertyID           inPropID,
  QTPropertyValueType *  outPropType,
  ByteCount *            outPropValueSize,
  UInt32 *               outPropFlags)                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTMetaDataGetItemProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTMetaDataGetItemProperty(
  QTMetaDataRef        inMetaData,
  QTMetaDataItem       inItem,
  QTPropertyClass      inPropClass,
  QTPropertyID         inPropID,
  ByteCount            inPropValueSize,
  QTPropertyValuePtr   outPropValueAddress,
  ByteCount *          outPropValueSizeUsed)                  AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTMetaDataSetItemProperty()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTMetaDataSetItemProperty(
  QTMetaDataRef             inMetaData,
  QTMetaDataItem            inItem,
  QTPropertyClass           inPropClass,
  QTPropertyID              inPropID,
  ByteCount                 inPropValueSize,
  ConstQTPropertyValuePtr   inPropValueAddress)               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTMetaDataGetItemCountWithKey()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTMetaDataGetItemCountWithKey(
  QTMetaDataRef             inMetaData,
  QTMetaDataStorageFormat   inMetaDataFormat,
  QTMetaDataKeyFormat       inKeyFormat,
  const UInt8 *             inKeyPtr,
  ByteCount                 inKeySize,
  ItemCount *               outCount)                         AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTMetaDataAddItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTMetaDataAddItem(
  QTMetaDataRef             inMetaData,
  QTMetaDataStorageFormat   inMetaDataFormat,
  QTMetaDataKeyFormat       inKeyFormat,
  const UInt8 *             inKeyPtr,
  ByteCount                 inKeySize,
  const UInt8 *             inValuePtr,
  ByteCount                 inValueSize,
  UInt32                    inDataType,
  QTMetaDataItem *          outItem)                          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTMetaDataSetItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTMetaDataSetItem(
  QTMetaDataRef    inMetaData,
  QTMetaDataItem   inItem,
  UInt8 *          inValuePtr,
  ByteCount        inValueSize,
  UInt32           inDataType)                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTMetaDataRemoveItem()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTMetaDataRemoveItem(
  QTMetaDataRef    inMetaData,
  QTMetaDataItem   inItem)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  QTMetaDataRemoveItemsWithKey()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 *    Windows:          in qtmlClient.lib version 10.4 (or QuickTime 7.0) and later
 */
extern OSStatus 
QTMetaDataRemoveItemsWithKey(
  QTMetaDataRef             inMetaData,
  QTMetaDataStorageFormat   inMetaDataFormat,
  QTMetaDataKeyFormat       inKeyFormat,
  const UInt8 *             inKeyPtr,
  ByteCount                 inKeySize)                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
 *  MusicMediaGetIndexedTunePlayer()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   in QuickTimeLib 3.0 and later
 *    Windows:          in qtmlClient.lib 3.0 and later
 */
extern ComponentResult 
MusicMediaGetIndexedTunePlayer(
  ComponentInstance    ti,
  long                 sampleDescIndex,
  ComponentInstance *  tp)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;





typedef struct QTBandwidthUsageRecord**  QTBandwidthReference;
typedef struct QTScheduledBandwidthUsageRecord**  QTScheduledBandwidthReference;
enum {
  BandwidthManagementPrefsType  = 'bwmg'
};


struct BandwidthManagementPrefsRecord {
  Boolean             overrideConnectionSpeedForBandwidth;
};
typedef struct BandwidthManagementPrefsRecord BandwidthManagementPrefsRecord;
typedef BandwidthManagementPrefsRecord * BandwidthManagementPrefsPtr;
typedef BandwidthManagementPrefsPtr *   BandwidthManagementPrefsHandle;
enum {
  kQTBandwidthNotifyNeedToStop  = 1L << 0,
  kQTBandwidthNotifyGoodToGo    = 1L << 1,
  kQTBandwidthChangeRequest     = 1L << 2,
  kQTBandwidthQueueRequest      = 1L << 3,
  kQTBandwidthScheduledRequest  = 1L << 4,
  kQTBandwidthVoluntaryRelease  = 1L << 5
};

typedef CALLBACK_API( OSErr , QTBandwidthNotificationProcPtr )(long flags, void *reserved, void *refcon);
struct QTScheduledBandwidthRecord {
  long                recordSize;             /* total number of bytes in QTScheduledBandwidthRecord*/

  long                priority;
  long                dataRate;
  CompTimeValue       startTime;              /* bandwidth usage start time*/
  CompTimeValue       duration;               /* duration of bandwidth usage (0 if unknown)*/
  CompTimeValue       prerollDuration;        /* time for negotiation before startTime (0 if unknown)*/
  TimeScale           scale;                  /* timescale of value/duration/prerollDuration fields*/
  TimeBase            base;                   /* timebase*/
};
typedef struct QTScheduledBandwidthRecord QTScheduledBandwidthRecord;
typedef QTScheduledBandwidthRecord *    QTScheduledBandwidthPtr;
typedef QTScheduledBandwidthPtr *       QTScheduledBandwidthHandle;
typedef STACK_UPP_TYPE(QTBandwidthNotificationProcPtr)          QTBandwidthNotificationUPP;
/*
 *  QTBandwidthRequest()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    No longer need to call bandwidth management functions.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
QTBandwidthRequest(
  long                         priority,
  QTBandwidthNotificationUPP   callback,
  const void *                 refcon,
  QTBandwidthReference *       bwRef,
  long                         flags)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  QTBandwidthRequestForTimeBase()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    No longer need to call bandwidth management functions.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern OSErr 
QTBandwidthRequestForTimeBase(
  TimeBase                     tb,
  long                         priority,
  QTBandwidthNotificationUPP   callback,
  const void *                 refcon,
  QTBandwidthReference *       bwRef,
  long                         flags)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  QTBandwidthRelease()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    No longer need to call bandwidth management functions.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
QTBandwidthRelease(
  QTBandwidthReference   bwRef,
  long                   flags)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  QTScheduledBandwidthRequest()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    No longer need to call bandwidth management functions.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern OSErr 
QTScheduledBandwidthRequest(
  QTScheduledBandwidthPtr          scheduleRec,
  QTBandwidthNotificationUPP       notificationCallback,
  void *                           refcon,
  QTScheduledBandwidthReference *  sbwRef,
  long                             flags)                     AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  QTScheduledBandwidthRelease()   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    No longer need to call bandwidth management functions.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework but deprecated in 10.4
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern OSErr 
QTScheduledBandwidthRelease(
  QTScheduledBandwidthReference   sbwRef,
  long                            flags)                      AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;


/*
 *  NewMCActionFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MCActionFilterUPP
NewMCActionFilterUPP(MCActionFilterProcPtr userRoutine)       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewMCActionFilterWithRefConUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MCActionFilterWithRefConUPP
NewMCActionFilterWithRefConUPP(MCActionFilterWithRefConProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  NewMCActionNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MCActionNotificationUPP
NewMCActionNotificationUPP(MCActionNotificationProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  NewQTMoviePropertyListenerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 9.9 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTMoviePropertyListenerUPP
NewQTMoviePropertyListenerUPP(QTMoviePropertyListenerProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  NewQTTrackPropertyListenerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 9.9 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTTrackPropertyListenerUPP
NewQTTrackPropertyListenerUPP(QTTrackPropertyListenerProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  NewQTBandwidthNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTBandwidthNotificationUPP
NewQTBandwidthNotificationUPP(QTBandwidthNotificationProcPtr userRoutine) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  DisposeMCActionFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMCActionFilterUPP(MCActionFilterUPP userUPP)           AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeMCActionFilterWithRefConUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMCActionFilterWithRefConUPP(MCActionFilterWithRefConUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  DisposeMCActionNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMCActionNotificationUPP(MCActionNotificationUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  DisposeQTMoviePropertyListenerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 9.9 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTMoviePropertyListenerUPP(QTMoviePropertyListenerUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  DisposeQTTrackPropertyListenerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 9.9 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTTrackPropertyListenerUPP(QTTrackPropertyListenerUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  DisposeQTBandwidthNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTBandwidthNotificationUPP(QTBandwidthNotificationUPP userUPP) AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

/*
 *  InvokeMCActionFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeMCActionFilterUPP(
  MovieController    mc,
  short *            action,
  void *             params,
  MCActionFilterUPP  userUPP)                                 AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeMCActionFilterWithRefConUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeMCActionFilterWithRefConUPP(
  MovieController              mc,
  short                        action,
  void *                       params,
  long                         refCon,
  MCActionFilterWithRefConUPP  userUPP)                       AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  InvokeMCActionNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   available as macro/inline
 */
extern Boolean
InvokeMCActionNotificationUPP(
  MovieController          mc,
  short                    action,
  void *                   params,
  UInt32                   inFlags,
  UInt32 *                 outFlags,
  void *                   refCon,
  MCActionNotificationUPP  userUPP)                           AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  InvokeQTMoviePropertyListenerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 (or QuickTime 6.4) and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 9.9 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQTMoviePropertyListenerUPP(
  Movie                       inMovie,
  QTPropertyClass             inPropClass,
  QTPropertyID                inPropID,
  void *                      inUserData,
  QTMoviePropertyListenerUPP  userUPP)                        AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  InvokeQTTrackPropertyListenerUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 (or QuickTime 7.0) and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 9.9 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
InvokeQTTrackPropertyListenerUPP(
  Track                       inTrack,
  QTPropertyClass             inPropClass,
  QTPropertyID                inPropID,
  void *                      inUserData,
  QTTrackPropertyListenerUPP  userUPP)                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  InvokeQTBandwidthNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern OSErr
InvokeQTBandwidthNotificationUPP(
  long                        flags,
  void *                      reserved,
  void *                      refcon,
  QTBandwidthNotificationUPP  userUPP)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED_IN_MAC_OS_X_VERSION_10_4;

#if __MACH__
  #ifdef __cplusplus
    inline MCActionFilterUPP                                    NewMCActionFilterUPP(MCActionFilterProcPtr userRoutine) { return userRoutine; }
    inline MCActionFilterWithRefConUPP                          NewMCActionFilterWithRefConUPP(MCActionFilterWithRefConProcPtr userRoutine) { return userRoutine; }
    inline MCActionNotificationUPP                              NewMCActionNotificationUPP(MCActionNotificationProcPtr userRoutine) { return userRoutine; }
    inline QTMoviePropertyListenerUPP                           NewQTMoviePropertyListenerUPP(QTMoviePropertyListenerProcPtr userRoutine) { return userRoutine; }
    inline QTTrackPropertyListenerUPP                           NewQTTrackPropertyListenerUPP(QTTrackPropertyListenerProcPtr userRoutine) { return userRoutine; }
    inline QTBandwidthNotificationUPP                           NewQTBandwidthNotificationUPP(QTBandwidthNotificationProcPtr userRoutine) { return userRoutine; }
    inline void                                                 DisposeMCActionFilterUPP(MCActionFilterUPP) { }
    inline void                                                 DisposeMCActionFilterWithRefConUPP(MCActionFilterWithRefConUPP) { }
    inline void                                                 DisposeMCActionNotificationUPP(MCActionNotificationUPP) { }
    inline void                                                 DisposeQTMoviePropertyListenerUPP(QTMoviePropertyListenerUPP) { }
    inline void                                                 DisposeQTTrackPropertyListenerUPP(QTTrackPropertyListenerUPP) { }
    inline void                                                 DisposeQTBandwidthNotificationUPP(QTBandwidthNotificationUPP) { }
    inline Boolean                                              InvokeMCActionFilterUPP(MovieController mc, short * action, void * params, MCActionFilterUPP userUPP) { return (*userUPP)(mc, action, params); }
    inline Boolean                                              InvokeMCActionFilterWithRefConUPP(MovieController mc, short action, void * params, long refCon, MCActionFilterWithRefConUPP userUPP) { return (*userUPP)(mc, action, params, refCon); }
    inline Boolean                                              InvokeMCActionNotificationUPP(MovieController mc, short action, void * params, UInt32 inFlags, UInt32 * outFlags, void * refCon, MCActionNotificationUPP userUPP) { return (*userUPP)(mc, action, params, inFlags, outFlags, refCon); }
    inline void                                                 InvokeQTMoviePropertyListenerUPP(Movie inMovie, QTPropertyClass inPropClass, QTPropertyID inPropID, void * inUserData, QTMoviePropertyListenerUPP userUPP) { (*userUPP)(inMovie, inPropClass, inPropID, inUserData); }
    inline void                                                 InvokeQTTrackPropertyListenerUPP(Track inTrack, QTPropertyClass inPropClass, QTPropertyID inPropID, void * inUserData, QTTrackPropertyListenerUPP userUPP) { (*userUPP)(inTrack, inPropClass, inPropID, inUserData); }
    inline OSErr                                                InvokeQTBandwidthNotificationUPP(long flags, void * reserved, void * refcon, QTBandwidthNotificationUPP userUPP) { return (*userUPP)(flags, reserved, refcon); }
  #else
    #define NewMCActionFilterUPP(userRoutine)                   ((MCActionFilterUPP)userRoutine)
    #define NewMCActionFilterWithRefConUPP(userRoutine)         ((MCActionFilterWithRefConUPP)userRoutine)
    #define NewMCActionNotificationUPP(userRoutine)             ((MCActionNotificationUPP)userRoutine)
    #define NewQTMoviePropertyListenerUPP(userRoutine)          ((QTMoviePropertyListenerUPP)userRoutine)
    #define NewQTTrackPropertyListenerUPP(userRoutine)          ((QTTrackPropertyListenerUPP)userRoutine)
    #define NewQTBandwidthNotificationUPP(userRoutine)          ((QTBandwidthNotificationUPP)userRoutine)
    #define DisposeMCActionFilterUPP(userUPP)
    #define DisposeMCActionFilterWithRefConUPP(userUPP)
    #define DisposeMCActionNotificationUPP(userUPP)
    #define DisposeQTMoviePropertyListenerUPP(userUPP)
    #define DisposeQTTrackPropertyListenerUPP(userUPP)
    #define DisposeQTBandwidthNotificationUPP(userUPP)
    #define InvokeMCActionFilterUPP(mc, action, params, userUPP) (*userUPP)(mc, action, params)
    #define InvokeMCActionFilterWithRefConUPP(mc, action, params, refCon, userUPP) (*userUPP)(mc, action, params, refCon)
    #define InvokeMCActionNotificationUPP(mc, action, params, inFlags, outFlags, refCon, userUPP) (*userUPP)(mc, action, params, inFlags, outFlags, refCon)
    #define InvokeQTMoviePropertyListenerUPP(inMovie, inPropClass, inPropID, inUserData, userUPP) (*userUPP)(inMovie, inPropClass, inPropID, inUserData)
    #define InvokeQTTrackPropertyListenerUPP(inTrack, inPropClass, inPropID, inUserData, userUPP) (*userUPP)(inTrack, inPropClass, inPropID, inUserData)
    #define InvokeQTBandwidthNotificationUPP(flags, reserved, refcon, userUPP) (*userUPP)(flags, reserved, refcon)
  #endif
#endif



/* UPP call backs */

/* selectors for component calls */
enum {
    kVideoMediaResetStatisticsSelect           = 0x0105,
    kVideoMediaGetStatisticsSelect             = 0x0106,
    kVideoMediaGetStallCountSelect             = 0x010E,
    kVideoMediaSetCodecParameterSelect         = 0x010F,
    kVideoMediaGetCodecParameterSelect         = 0x0110,
    kTextMediaSetTextProcSelect                = 0x0101,
    kTextMediaAddTextSampleSelect              = 0x0102,
    kTextMediaAddTESampleSelect                = 0x0103,
    kTextMediaAddHiliteSampleSelect            = 0x0104,
    kTextMediaDrawRawSelect                    = 0x0109,
    kTextMediaSetTextPropertySelect            = 0x010A,
    kTextMediaRawSetupSelect                   = 0x010B,
    kTextMediaRawIdleSelect                    = 0x010C,
    kTextMediaGetTextPropertySelect            = 0x010D,
    kTextMediaFindNextTextSelect               = 0x0105,
    kTextMediaHiliteTextSampleSelect           = 0x0106,
    kTextMediaSetTextSampleDataSelect          = 0x0107,
    kSpriteMediaSetPropertySelect              = 0x0101,
    kSpriteMediaGetPropertySelect              = 0x0102,
    kSpriteMediaHitTestSpritesSelect           = 0x0103,
    kSpriteMediaCountSpritesSelect             = 0x0104,
    kSpriteMediaCountImagesSelect              = 0x0105,
    kSpriteMediaGetIndImageDescriptionSelect   = 0x0106,
    kSpriteMediaGetDisplayedSampleNumberSelect = 0x0107,
    kSpriteMediaGetSpriteNameSelect            = 0x0108,
    kSpriteMediaGetImageNameSelect             = 0x0109,
    kSpriteMediaSetSpritePropertySelect        = 0x010A,
    kSpriteMediaGetSpritePropertySelect        = 0x010B,
    kSpriteMediaHitTestAllSpritesSelect        = 0x010C,
    kSpriteMediaHitTestOneSpriteSelect         = 0x010D,
    kSpriteMediaSpriteIndexToIDSelect          = 0x010E,
    kSpriteMediaSpriteIDToIndexSelect          = 0x010F,
    kSpriteMediaGetSpriteActionsForQTEventSelect = 0x0110,
    kSpriteMediaSetActionVariableSelect        = 0x0111,
    kSpriteMediaGetActionVariableSelect        = 0x0112,
    kSpriteMediaGetIndImagePropertySelect      = 0x0113,
    kSpriteMediaNewSpriteSelect                = 0x0114,
    kSpriteMediaDisposeSpriteSelect            = 0x0115,
    kSpriteMediaSetActionVariableToStringSelect = 0x0116,
    kSpriteMediaGetActionVariableAsStringSelect = 0x0117,
    kSpriteMediaNewImageSelect                 = 0x011B,
    kSpriteMediaDisposeImageSelect             = 0x011C,
    kSpriteMediaImageIndexToIDSelect           = 0x011D,
    kSpriteMediaImageIDToIndexSelect           = 0x011E,
    kFlashMediaSetPanSelect                    = 0x0101,
    kFlashMediaSetZoomSelect                   = 0x0102,
    kFlashMediaSetZoomRectSelect               = 0x0103,
    kFlashMediaGetRefConBoundsSelect           = 0x0104,
    kFlashMediaGetRefConIDSelect               = 0x0105,
    kFlashMediaIDToRefConSelect                = 0x0106,
    kFlashMediaGetDisplayedFrameNumberSelect   = 0x0107,
    kFlashMediaFrameNumberToMovieTimeSelect    = 0x0108,
    kFlashMediaFrameLabelToMovieTimeSelect     = 0x0109,
    kFlashMediaGetFlashVariableSelect          = 0x010A,
    kFlashMediaSetFlashVariableSelect          = 0x010B,
    kFlashMediaDoButtonActionsSelect           = 0x010C,
    kFlashMediaGetSupportedSwfVersionSelect    = 0x010D,
    kMovieMediaGetChildDoMCActionCallbackSelect = 0x0102,
    kMovieMediaGetDoMCActionCallbackSelect     = 0x0103,
    kMovieMediaGetCurrentMoviePropertySelect   = 0x0104,
    kMovieMediaGetCurrentTrackPropertySelect   = 0x0105,
    kMovieMediaGetChildMovieDataReferenceSelect = 0x0106,
    kMovieMediaSetChildMovieDataReferenceSelect = 0x0107,
    kMovieMediaLoadChildMovieFromDataReferenceSelect = 0x0108,
    kMedia3DGetNamedObjectListSelect           = 0x0101,
    kMedia3DGetRendererListSelect              = 0x0102,
    kMedia3DGetCurrentGroupSelect              = 0x0103,
    kMedia3DTranslateNamedObjectToSelect       = 0x0104,
    kMedia3DScaleNamedObjectToSelect           = 0x0105,
    kMedia3DRotateNamedObjectToSelect          = 0x0106,
    kMedia3DSetCameraDataSelect                = 0x0107,
    kMedia3DGetCameraDataSelect                = 0x0108,
    kMedia3DSetCameraAngleAspectSelect         = 0x0109,
    kMedia3DGetCameraAngleAspectSelect         = 0x010A,
    kMedia3DSetCameraRangeSelect               = 0x010D,
    kMedia3DGetCameraRangeSelect               = 0x010E,
    kMedia3DGetViewObjectSelect                = 0x010F,
    kMCSetMovieSelect                          = 0x0002,
    kMCGetIndMovieSelect                       = 0x0005,
    kMCRemoveAllMoviesSelect                   = 0x0006,
    kMCRemoveAMovieSelect                      = 0x0003,
    kMCRemoveMovieSelect                       = 0x0006,
    kMCIsPlayerEventSelect                     = 0x0007,
    kMCSetActionFilterSelect                   = 0x0008,
    kMCDoActionSelect                          = 0x0009,
    kMCSetControllerAttachedSelect             = 0x000A,
    kMCIsControllerAttachedSelect              = 0x000B,
    kMCSetControllerPortSelect                 = 0x000C,
    kMCGetControllerPortSelect                 = 0x000D,
    kMCSetVisibleSelect                        = 0x000E,
    kMCGetVisibleSelect                        = 0x000F,
    kMCGetControllerBoundsRectSelect           = 0x0010,
    kMCSetControllerBoundsRectSelect           = 0x0011,
    kMCGetControllerBoundsRgnSelect            = 0x0012,
    kMCGetWindowRgnSelect                      = 0x0013,
    kMCMovieChangedSelect                      = 0x0014,
    kMCSetDurationSelect                       = 0x0015,
    kMCGetCurrentTimeSelect                    = 0x0016,
    kMCNewAttachedControllerSelect             = 0x0017,
    kMCDrawSelect                              = 0x0018,
    kMCActivateSelect                          = 0x0019,
    kMCIdleSelect                              = 0x001A,
    kMCKeySelect                               = 0x001B,
    kMCClickSelect                             = 0x001C,
    kMCEnableEditingSelect                     = 0x001D,
    kMCIsEditingEnabledSelect                  = 0x001E,
    kMCCopySelect                              = 0x001F,
    kMCCutSelect                               = 0x0020,
    kMCPasteSelect                             = 0x0021,
    kMCClearSelect                             = 0x0022,
    kMCUndoSelect                              = 0x0023,
    kMCPositionControllerSelect                = 0x0024,
    kMCGetControllerInfoSelect                 = 0x0025,
    kMCSetClipSelect                           = 0x0028,
    kMCGetClipSelect                           = 0x0029,
    kMCDrawBadgeSelect                         = 0x002A,
    kMCSetUpEditMenuSelect                     = 0x002B,
    kMCGetMenuStringSelect                     = 0x002C,
    kMCSetActionFilterWithRefConSelect         = 0x002D,
    kMCPtInControllerSelect                    = 0x002E,
    kMCInvalidateSelect                        = 0x002F,
    kMCAdjustCursorSelect                      = 0x0030,
    kMCGetInterfaceElementSelect               = 0x0031,
    kMCGetDoActionsProcSelect                  = 0x0032,
    kMCAddMovieSegmentSelect                   = 0x0033,
    kMCTrimMovieSegmentSelect                  = 0x0034,
    kMCSetIdleManagerSelect                    = 0x0035,
    kMCSetControllerCapabilitiesSelect         = 0x0036,
    kMusicMediaGetIndexedTunePlayerSelect      = 0x0101
};

#endif // !__LP64__



#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __MOVIES__ */

