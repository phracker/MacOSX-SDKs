/*
     File:       QuickTime/Movies.h
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime-142~1
 
     Copyright:  © 1990-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __MOVIES__
#define __MOVIES__

#ifndef __CARBON__
#include <Carbon/Carbon.h>
#endif

#ifndef __IMAGECOMPRESSION__
#include <QuickTime/ImageCompression.h>
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
  HandleDataHandlerSubType      = 'hndl',
  PointerDataHandlerSubType     = 'ptr ',
  NullDataHandlerSubType        = 'null',
  ResourceDataHandlerSubType    = 'rsrc',
  URLDataHandlerSubType         = 'url ',
  WiredActionHandlerType        = 'wire'
};

enum {
  VisualMediaCharacteristic     = 'eyes',
  AudioMediaCharacteristic      = 'ears',
  kCharacteristicCanSendVideo   = 'vsnd',
  kCharacteristicProvidesActions = 'actn',
  kCharacteristicNonLinear      = 'nonl',
  kCharacteristicCanStep        = 'step',
  kCharacteristicHasNoDuration  = 'noti'
};

enum {
  kUserDataMovieControllerType  = 'ctyp',
  kUserDataName                 = 'name',
  kUserDataTextAlbum            = '©alb',
  kUserDataTextArtist           = '©ART',
  kUserDataTextAuthor           = '©aut',
  kUserDataTextChapter          = '©chp',
  kUserDataTextComment          = '©cmt',
  kUserDataTextComposer         = '©com',
  kUserDataTextCopyright        = '©cpy',
  kUserDataTextCreationDate     = '©day',
  kUserDataTextDescription      = '©des',
  kUserDataTextDirector         = '©dir',
  kUserDataTextDisclaimer       = '©dis',
  kUserDataTextEncodedBy        = '©enc',
  kUserDataTextFullName         = '©nam',
  kUserDataTextGenre            = '©gen',
  kUserDataTextHostComputer     = '©hst',
  kUserDataTextInformation      = '©inf',
  kUserDataTextKeywords         = '©key',
  kUserDataTextMake             = '©mak',
  kUserDataTextModel            = '©mod',
  kUserDataTextOriginalArtist   = '©ope',
  kUserDataTextOriginalFormat   = '©fmt',
  kUserDataTextOriginalSource   = '©src',
  kUserDataTextPerformers       = '©prf',
  kUserDataTextProducer         = '©prd',
  kUserDataTextProduct          = '©PRD',
  kUserDataTextSoftware         = '©swr',
  kUserDataTextSpecialPlaybackRequirements = '©req',
  kUserDataTextTrack            = '©trk',
  kUserDataTextWarning          = '©wrn',
  kUserDataTextWriter           = '©wrt',
  kUserDataTextURLLink          = '©url',
  kUserDataTextEditDate1        = '©ed1'
};

enum {
  kUserDataUnicodeBit           = 1L << 7
};

enum {
  DoTheRightThing               = 0
};


struct MovieRecord {
  long                data[1];
};
typedef struct MovieRecord              MovieRecord;
typedef MovieRecord *                   Movie;
typedef Movie *                         MoviePtr;
struct TrackRecord {
  long                data[1];
};
typedef struct TrackRecord              TrackRecord;
typedef TrackRecord *                   Track;
struct MediaRecord {
  long                data[1];
};
typedef struct MediaRecord              MediaRecord;
typedef MediaRecord *                   Media;
struct UserDataRecord {
  long                data[1];
};
typedef struct UserDataRecord           UserDataRecord;
typedef UserDataRecord *                UserData;
struct TrackEditStateRecord {
  long                data[1];
};
typedef struct TrackEditStateRecord     TrackEditStateRecord;
typedef TrackEditStateRecord *          TrackEditState;
struct MovieEditStateRecord {
  long                data[1];
};
typedef struct MovieEditStateRecord     MovieEditStateRecord;
typedef MovieEditStateRecord *          MovieEditState;
struct SpriteWorldRecord {
  long                data[1];
};
typedef struct SpriteWorldRecord        SpriteWorldRecord;
typedef SpriteWorldRecord *             SpriteWorld;
struct SpriteRecord {
  long                data[1];
};
typedef struct SpriteRecord             SpriteRecord;
typedef SpriteRecord *                  Sprite;
struct QTTweenerRecord {
  long                data[1];
};
typedef struct QTTweenerRecord          QTTweenerRecord;
typedef QTTweenerRecord *               QTTweener;
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
typedef struct OpaqueQTBandwidthReference*  QTBandwidthReference;
typedef struct OpaqueQTScheduledBandwidthReference*  QTScheduledBandwidthReference;
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
  kActionQTVRSetPanAngle        = 4096, /* (float panAngle) */
  kActionQTVRSetTiltAngle       = 4097, /* (float tiltAngle) */
  kActionQTVRSetFieldOfView     = 4098, /* (float fieldOfView) */
  kActionQTVRShowDefaultView    = 4099, /* no params */
  kActionQTVRGoToNodeID         = 4100, /* (UInt32 nodeID) */
  kActionQTVREnableHotSpot      = 4101, /* long ID, Boolean enable */
  kActionQTVRShowHotSpots       = 4102, /* Boolean show */
  kActionQTVRTranslateObject    = 4103, /* float xMove, float yMove */
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
  kActionSpriteTrackSetVariable = 7168, /* (QTAtomID variableID, float value) */
  kActionSpriteTrackNewSprite   = 7169, /* (QTAtomID spriteID, short imageIndex, MatrixRecord *matrix, short visible, short layer, ModifierTrackGraphicsModeRecord *graphicsMode, QTAtomID actionHandlingSpriteID) */
  kActionSpriteTrackDisposeSprite = 7170, /* (QTAtomID spriteID) */
  kActionSpriteTrackSetVariableToString = 7171, /* (QTAtomID variableID, C string value) */
  kActionSpriteTrackConcatVariables = 7172, /* (QTAtomID firstVariableID, QTAtomID secondVariableID, QTAtomID resultVariableID ) */
  kActionSpriteTrackSetVariableToMovieURL = 7173, /* (QTAtomID variableID, < optional: [(MovieTargetAtoms)] > ) */
  kActionSpriteTrackSetVariableToMovieBaseURL = 7174, /* (QTAtomID variableID, < optional: [(MovieTargetAtoms)] > ) */
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
  kActionListServerQuery        = 13319 /* (C string url, C string keyValuePairs, long flags, C string parentPath) */
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
  kOperandQTVRPanAngle          = 4096,
  kOperandQTVRTiltAngle         = 4097,
  kOperandQTVRFieldOfView       = 4098,
  kOperandQTVRNodeID            = 4099,
  kOperandQTVRHotSpotsVisible   = 4100,
  kOperandQTVRViewCenterH       = 4101,
  kOperandQTVRViewCenterV       = 4102,
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
  kLastMovieAction              = kActionMovieRestartAtTime,
  kFirstTrackAction             = kActionTrackSetVolume,
  kLastTrackAction              = kActionTrackSetBassTreble,
  kFirstSpriteAction            = kActionSpriteSetMatrix,
  kLastSpriteAction             = kActionSpriteStretch,
  kFirstQTVRAction              = kActionQTVRSetPanAngle,
  kLastQTVRAction               = kActionQTVRTranslateObject,
  kFirstMusicAction             = kActionMusicPlayNote,
  kLastMusicAction              = kActionMusicSetController,
  kFirstSystemAction            = kActionCase,
  kLastSystemAction             = kActionDontPassKeyEvent,
  kFirstSpriteTrackAction       = kActionSpriteTrackSetVariable,
  kLastSpriteTrackAction        = kActionSpriteTrackSetVariableToMovieBaseURL,
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
  kLastMultiTargetAction        = kActionListServerQuery,
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
  kQTEventListReceived          = 'list'
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
  kSystemIsWindowsNT            = 0x00020000
};

/* constants for MediaPropertiesAtom*/
enum {
  kMediaPropertyNonLinearAtomType = 'nonl',
  kMediaPropertyHasActions      = 105
};

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
typedef STACK_UPP_TYPE(MoviesErrorProcPtr)                      MoviesErrorUPP;
typedef ComponentInstance               MediaHandler;
typedef ComponentInstance               DataHandler;
typedef Component                       MediaHandlerComponent;
typedef Component                       DataHandlerComponent;
typedef ComponentResult                 HandlerError;
/* TimeBase and TimeRecord moved to MacTypes.h */
typedef UInt32 TimeBaseFlags;
enum {
  loopTimeBase                  = 1,
  palindromeLoopTimeBase        = 2,
  maintainTimeBaseZero          = 4
};

struct CallBackRecord {
  long                data[1];
};
typedef struct CallBackRecord           CallBackRecord;
typedef CallBackRecord *                QTCallBack;
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
  timeBaseAfterStopTime         = 2
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

struct QTCallBackHeader {
  long                callBackFlags;
  long                reserved1;
  SInt8               qtPrivate[40];
};
typedef struct QTCallBackHeader         QTCallBackHeader;
typedef CALLBACK_API( void , QTSyncTaskProcPtr )(void * task);
typedef STACK_UPP_TYPE(QTSyncTaskProcPtr)                       QTSyncTaskUPP;
struct QTSyncTaskRecord {
  void *              qLink;
  QTSyncTaskUPP       proc;
};
typedef struct QTSyncTaskRecord         QTSyncTaskRecord;
typedef QTSyncTaskRecord *              QTSyncTaskPtr;
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
  newMovieIdleImportOK          = 1 << 10
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
  mediaSampleShadowSync         = 1 << 1 /* sample is a shadow sync */
};

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
  hintsNoRenderingTimeOut       = 1 << 21
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
  long    flags);


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
EnterMovies(void);


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
ExitMovies(void);


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
GetMoviesError(void);


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
ClearMoviesStickyError(void);


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
GetMoviesStickyError(void);


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
  long             refcon);



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
  long    maxMilliSecToUse);


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
  Fixed       Rate);


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
  void *                       refcon);


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
  OSErr   err);


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
  long        flags);


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
  long        flags);


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
  long        flags);


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
  Boolean   active);


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
GetMovieActive(Movie theMovie);


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
StartMovie(Movie theMovie);


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
StopMovie(Movie theMovie);


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
GoToBeginningOfMovie(Movie theMovie);


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
GoToEndOfMovie(Movie theMovie);


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
IsMovieDone(Movie theMovie);


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
GetMoviePreviewMode(Movie theMovie);


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
  Boolean   usePreview);


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
ShowMoviePoster(Movie theMovie);


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
  long                     refcon);


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
GetMovieTimeBase(Movie theMovie);


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
  const TimeRecord *  slaveZero);


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
  const TimeRecord *  slaveZero);


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
  GDHandle *  gdh);


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
  GDHandle   gdh);


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
  long                      refCon);



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
  Rect *  naturalBounds);


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
  Track   theTrack);


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
  Track   theTrack);


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
  long               refCon);


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
  TimeValue   time);


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
  TimeValue   time);


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
GetMoviePosterPict(Movie theMovie);


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
UpdateMovie(Movie theMovie);


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
  RgnHandle   invalidRgn);


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
  Rect *  boxRect);


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
  const Rect *  boxRect);


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
GetMovieDisplayClipRgn(Movie theMovie);


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
  RgnHandle   theClip);


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
GetMovieClipRgn(Movie theMovie);


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
  RgnHandle   theClip);


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
GetTrackClipRgn(Track theTrack);


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
  RgnHandle   theClip);


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
GetMovieDisplayBoundsRgn(Movie theMovie);


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
GetTrackDisplayBoundsRgn(Track theTrack);


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
GetMovieBoundsRgn(Movie theMovie);


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
GetTrackMovieBoundsRgn(Track theTrack);


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
GetTrackBoundsRgn(Track theTrack);


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
GetTrackMatte(Track theTrack);


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
  PixMapHandle   theMatte);


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
DisposeMatte(PixMapHandle theMatte);


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
  ComponentInstance   vout);


/*************************
* calls for getting/saving movies
**************************/
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
NewMovie(long flags);


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
  Handle   publicMovie);


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
  long    maxSize);


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
  unsigned long   maxSize);


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
DisposeMovie(Movie theMovie);


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
GetMovieCreationTime(Movie theMovie);


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
GetMovieModificationTime(Movie theMovie);


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
GetMovieTimeScale(Movie theMovie);


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
  TimeScale   timeScale);


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
GetMovieDuration(Movie theMovie);


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
GetMovieRate(Movie theMovie);


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
  Fixed   rate);


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
GetMoviePreferredRate(Movie theMovie);


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
  Fixed   rate);


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
GetMoviePreferredVolume(Movie theMovie);


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
  short   volume);


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
GetMovieVolume(Movie theMovie);


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
  short   volume);


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
  MatrixRecord *  matrix);


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
  const MatrixRecord *  matrix);


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
  TimeValue *  previewDuration);


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
  TimeValue   previewDuration);


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
GetMoviePosterTime(Movie theMovie);


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
  TimeValue   posterTime);


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
  TimeValue *  selectionDuration);


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
  TimeValue   selectionDuration);


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
  TimeValue   duration);


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
  TimeValue *  duration);


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
  TimeRecord *  currentTime);


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
  const TimeRecord *  newtime);


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
  TimeValue   newtime);



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
GetMovieUserData(Movie theMovie);



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
GetMovieTrackCount(Movie theMovie);


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
  long    trackID);


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
  long    index);


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
  long     flags);


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
GetTrackID(Track theTrack);


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
GetTrackMovie(Track theTrack);


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
  short   trackVolume);


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
DisposeMovieTrack(Track theTrack);


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
GetTrackCreationTime(Track theTrack);


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
GetTrackModificationTime(Track theTrack);



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
GetTrackEnabled(Track theTrack);


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
  Boolean   isEnabled);


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
GetTrackUsage(Track theTrack);


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
  long    usage);


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
GetTrackDuration(Track theTrack);


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
GetTrackOffset(Track theTrack);


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
  TimeValue   movieOffsetTime);


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
GetTrackLayer(Track theTrack);


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
  short   layer);


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
GetTrackAlternate(Track theTrack);


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
  Track   alternateT);


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
  Boolean   enable);


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
SelectMovieAlternates(Movie theMovie);


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
GetTrackVolume(Track theTrack);


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
  short   volume);


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
  MatrixRecord *  matrix);


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
  const MatrixRecord *  matrix);


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
  Fixed *  height);


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
  Fixed   height);


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
GetTrackUserData(Track theTrack);


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
  MatrixRecord *  matrix);


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
  Handle *  settings);


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
  Handle   settings);


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
  OSType      dataRefType);


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
DisposeTrackMedia(Media theMedia);


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
GetTrackMedia(Track theTrack);


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
GetMediaTrack(Media theMedia);




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
GetMediaCreationTime(Media theMedia);


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
GetMediaModificationTime(Media theMedia);


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
GetMediaTimeScale(Media theMedia);


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
  TimeScale   timeScale);


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
GetMediaDuration(Media theMedia);


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
GetMediaLanguage(Media theMedia);


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
  short   language);


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
GetMediaQuality(Media theMedia);


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
  short   quality);


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
  OSType *  creatorManufacturer);


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
GetMediaUserData(Media theMedia);


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
  QTAtomContainer *  inputMap);


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
  QTAtomContainer   inputMap);


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
GetMediaHandler(Media theMedia);


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
  MediaHandlerComponent   mH);



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
BeginMediaEdits(Media theMedia);


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
EndMediaEdits(Media theMedia);


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
  short   index);


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
  OSType *  creatorManufacturer);


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
  short   index);


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
  DataHandlerComponent   dataHandler);


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
  long     flags);


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
  ComponentInstance *  dh);


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
GetMediaSampleDescriptionCount(Media theMedia);


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
  SampleDescriptionHandle   descH);


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
  SampleDescriptionHandle   descH);


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
GetMediaSampleCount(Media theMedia);


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
GetMediaSyncSampleCount(Media theMedia);


/*
 *  SampleNumToMediaTime()
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
  TimeValue *  sampleDuration);


/*
 *  MediaTimeToSampleNum()
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
  TimeValue *  sampleDuration);



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
  TimeValue *               sampleTime);


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
  TimeValue *               sampleTime);


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
  TimeValue *               sampleTime);


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
  TimeValue *               sampleTime);


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
  long                      maxNumberOfSamples,
  long *                    numberOfSamples,
  short *                   sampleFlags);


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
  short *                   sampleFlags);


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
  SampleReferencePtr        sampleRefs);


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
  SampleReference64Ptr      sampleRefs);


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
  long    maxChunkSize);


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
  long *  maxChunkSize);


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
  long    syncSampleNum);


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
  long *  syncSampleNum);


/*************************
* Editing Routines
**************************/
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
  Fixed       mediaRate);


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
  TimeValue   dstIn);


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
  TimeValue   dstIn);


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
  TimeValue   dstDuration);


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
  TimeValue   dstDuration);


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
  TimeValue   duration);


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
  TimeValue   duration);


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
  TimeValue   newDuration);


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
  TimeValue   newDuration);



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
CutMovieSelection(Movie theMovie);


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
CopyMovieSelection(Movie theMovie);


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
  Movie   src);


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
  Movie   src);


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
ClearMovieSelection(Movie theMovie);


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
  ComponentInstance   userComp);


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
  ComponentInstance   userComp);


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
IsScrapMovie(Track targetTrack);


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
  Track   dstTrack);


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
  Movie   dstMovie);


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
  Track *  dstTrack);


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
  Track *  dstTrack);


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
NewMovieEditState(Movie theMovie);


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
  MovieEditState   toState);


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
DisposeMovieEditState(MovieEditState state);


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
NewTrackEditState(Track theTrack);


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
  TrackEditState   state);


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
DisposeTrackEditState(TrackEditState state);


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
  long *   addedIndex);


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
  long     index);


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
  long     index);


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
  long     index);


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
  OSType   refType);


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
  OSType   refType);



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
  long                refCon);


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
  ComponentInstance   userComp);


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
  Component *  importer);



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
  long *        infoDataSize);


/*************************
* Movie Timebase Conversion Routines
**************************/
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
  Track       theTrack);


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
  TimeValue   atTime);



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
  TimeValue   duration);


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
  wide *      dataSize);


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
  TimeValue   duration);


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
  wide *      dataSize);


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
  TimeValue   duration);


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
  wide *      dataSize);


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
  Point   pt);


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
  Point   pt);


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
  long    language);



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
  long       index);


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
  OSType     udType);


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
  long       index);


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
  OSType     udType);


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
  OSType     udType);


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
  long       index);


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
  long       index);


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
  short      itlRegionTag);


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
  short      itlRegionTag);


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
  short      itlRegionTag);


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
NewUserData(UserData * theUserData);


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
DisposeUserData(UserData theUserData);


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
  UserData *  theUserData);


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
  Handle     h);



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
  QTAtomContainer   propertyAtom);


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
  QTAtomContainer *  propertyAtom);



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
  TimeValue *  interestingDuration);


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
  TimeValue *  interestingDuration);


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
  TimeValue *     interestingDuration);



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
  Movie *         newmovie);


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
  SInt8           permission);


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
CloseMovieFile(short resRefNum);


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
DeleteMovieFile(const FSSpec * fileSpec);


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
  Boolean *   dataRefWasChanged);      /* can be NULL */


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
  Boolean *  dataRefWasChanged);


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
  Boolean *  dataRefWasChanged);


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
  Boolean *     dataRefWasChanged);


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
  OSType        dataRefType);


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
  OSType   dataRefType);


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
  ConstStr255Param   resName);


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
  ConstStr255Param   resName);


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
  short   resId);


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
HasMovieChanged(Movie theMovie);


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
ClearMovieChanged(Movie theMovie);


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
  OSType   dataRefType);


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
  OSType *  dataRefType);


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
  OSType   dataRefType);


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
  long *    outFlags);


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
  CTabHandle   ctab);


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
  CTabHandle *  ctab);


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
  ConstStr255Param   resName);


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
  long            createMovieFileFlags);


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
  long               refcon);


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
  long *              refcon);


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
  OSType          targetDataRefType);


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
  long *       searchOffset);


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
  Rect *  boxRect);


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
  const Rect *  boxRect);


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
  TimeValue   duration);


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
  TimeValue   duration);


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
  long               refcon);


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
  long *              refcon);


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
GetTrackStatus(Track theTrack);


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
  Track *  firstProblemTrack);


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
GetMovieLoadState(Movie theMovie);


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
  UInt32      inFlags);


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
  UInt32     inFlags);


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
  long          someFlags);


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
DisposeMovieController(ComponentInstance mc);


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
  long             refCon);



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
  long    movieScrapFlags);


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
NewMovieFromScrap(long newMovieFlags);



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
  long *    dataRefAttributes);


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
  OSType   dataRefType);


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
  long    dataRefAttributes);


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
  OSType   dataRefType);


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
  short *  count);


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
  Boolean         minimal);


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
  long    flagsMask);


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
  long    flagsMask);


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
  long *  flags);


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
  long        defaultHints);


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
  long *       defaultHints);


/*****
    Big screen TV
*****/
enum {
  fullScreenHideCursor          = 1L << 0,
  fullScreenAllowEvents         = 1L << 1,
  fullScreenDontChangeMenuBar   = 1L << 2,
  fullScreenPreflightSize       = 1L << 3
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
  long         flags);


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
  long   flags);


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
  void *                        refCon);


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
  void *                        refCon);


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
  QTAtomContainer   actions);


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
  kSpritePropertyImageIndex     = 100,
  kSpriteTrackPropertyBackgroundColor = 101,
  kSpriteTrackPropertyOffscreenBitDepth = 102,
  kSpriteTrackPropertySampleFormat = 103,
  kSpriteTrackPropertyScaleSpritesToScaleWorld = 104,
  kSpriteTrackPropertyHasActions = 105,
  kSpriteTrackPropertyVisible   = 106,
  kSpriteTrackPropertyQTIdleEventsFrequency = 107,
  kSpriteImagePropertyRegistrationPoint = 1000,
  kSpriteImagePropertyGroupID   = 1001
};

/* special value for kSpriteTrackPropertyQTIdleEventsFrequency (the default)*/
enum {
  kNoQTIdleEvents               = -1
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
  kSpriteWorldInvisible         = 1L << 4
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
  GWorldPtr      background);


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
DisposeSpriteWorld(SpriteWorld theSpriteWorld);


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
  RgnHandle     clipRgn);


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
  const MatrixRecord *  matrix);


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
  const RGBColor *  opColor);


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
  long *        flagsOut);


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
  Rect *        invalidArea);


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
  Sprite *      spriteHit);


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
  Boolean *  wasHit);


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
DisposeAllSprites(SpriteWorld theSpriteWorld);


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
  long          flagsMask);


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
  short                    layer);


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
DisposeSprite(Sprite theSprite);


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
InvalidateSprite(Sprite theSprite);


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
  void *   propertyValue);


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
  void *   propertyValue);


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
QTNewAtomContainer(QTAtomContainer * atomData);


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
QTDisposeAtomContainer(QTAtomContainer atomData);


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
  QTAtomType        currentChildType);


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
  QTAtomType        childType);


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
  QTAtomID *        id);


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
  short *           index);


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
  QTAtom *          nextChild);


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
  void *            atomData);


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
  Handle            targetHandle);


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
  long *            actualSize);


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
  QTAtomID *        id);


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
  QTAtomContainer *  targetContainer);


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
QTLockContainer(QTAtomContainer container);


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
  Ptr *             atomData);


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
QTUnlockContainer(QTAtomContainer container);


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
  QTAtom *          newAtom);


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
  QTAtomContainer   childrenContainer);


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
  QTAtom            atom);


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
  QTAtom            atom);


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
  QTAtom            replacementAtom);


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
  QTAtom            atom2);


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
  QTAtomID          newID);


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
  QTAtom            childAtom);


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
  QTAtomContainer   propertyAtom);


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
  QTAtomContainer *  propertyAtom);


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
  TimeValue         maxTime);


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
QTDisposeTween(QTTweener tween);


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
  void *           tweenDataRefCon);


/*****
    Sound Description Manipulations
*****/
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
  OSType                   idType);


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
  OSType                   idType);


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
  OSType                   idType);


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
  QTAtomContainer *  preferenceAtom);


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
  QTAtomContainer   preferenceAtom);


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
  pdActionFetchPreview          = 13    /* param is QTParamFetchPreviewPtr */
};

typedef long                            QTParameterDialog;
enum {
  elOptionsIncludeNoneInList    = 0x00000001 /* "None" effect is included in list */
};

typedef long                            QTEffectListOptions;
enum {
  pdOptionsCollectOneValue      = 0x00000001, /* should collect a single value only*/
  pdOptionsAllowOptionalInterpolations = 0x00000002, /* non-novice interpolation options are shown */
  pdOptionsModalDialogBox       = 0x00000004 /* dialog box should be modal */
};

typedef long                            QTParameterDialogOptions;
enum {
  effectIsRealtime              = 0     /* effect can be rendered in real time */
};

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
  QTEffectListOptions   getOptions);


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
  QTParameterDialog *        createdDialog);


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
  QTParameterDialog   createdDialog);


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
QTDismissStandardParameterDialog(QTParameterDialog createdDialog);


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
  void *              params);


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
  Fixed *           pFPS);


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
  QTAtomContainer *  keys);


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
  Handle   accessKey);


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
  Handle   accessKey);


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
  long *      retdataRefSkew);


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
  long *      retdataRefSkew);


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
  TimeValue *  time);


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
  Boolean *  needsTimeTable);


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
  long *   offset);



/*****
    Bandwidth management support
*****/
enum {
  ConnectionSpeedPrefsType      = 'cspd',
  BandwidthManagementPrefsType  = 'bwmg'
};


struct ConnectionSpeedPrefsRecord {
  long                connectionSpeed;
};
typedef struct ConnectionSpeedPrefsRecord ConnectionSpeedPrefsRecord;
typedef ConnectionSpeedPrefsRecord *    ConnectionSpeedPrefsPtr;
typedef ConnectionSpeedPrefsPtr *       ConnectionSpeedPrefsHandle;
struct BandwidthManagementPrefsRecord {
  Boolean             overrideConnectionSpeedForBandwidth;
};
typedef struct BandwidthManagementPrefsRecord BandwidthManagementPrefsRecord;
typedef BandwidthManagementPrefsRecord * BandwidthManagementPrefsPtr;
typedef BandwidthManagementPrefsPtr *   BandwidthManagementPrefsHandle;
enum {
  kQTIdlePriority               = 10,
  kQTNonRealTimePriority        = 20,
  kQTRealTimeSharedPriority     = 25,
  kQTRealTimePriority           = 30
};

enum {
  kQTBandwidthNotifyNeedToStop  = 1L << 0,
  kQTBandwidthNotifyGoodToGo    = 1L << 1,
  kQTBandwidthChangeRequest     = 1L << 2,
  kQTBandwidthQueueRequest      = 1L << 3,
  kQTBandwidthScheduledRequest  = 1L << 4,
  kQTBandwidthVoluntaryRelease  = 1L << 5
};

typedef CALLBACK_API( OSErr , QTBandwidthNotificationProcPtr )(long flags, void *reserved, void *refcon);
typedef STACK_UPP_TYPE(QTBandwidthNotificationProcPtr)          QTBandwidthNotificationUPP;
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
/*
 *  QTBandwidthRequest()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
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
  long                         flags);


/*
 *  QTBandwidthRequestForTimeBase()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
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
  long                         flags);


/*
 *  QTBandwidthRelease()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.0 and later
 *    Windows:          in qtmlClient.lib 4.0 and later
 */
extern OSErr 
QTBandwidthRelease(
  QTBandwidthReference   bwRef,
  long                   flags);


/*
 *  QTScheduledBandwidthRequest()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
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
  long                             flags);


/*
 *  QTScheduledBandwidthRelease()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.1 and later
 *    Non-Carbon CFM:   in QuickTimeLib 4.1 and later
 *    Windows:          in qtmlClient.lib 4.1 and later
 */
extern OSErr 
QTScheduledBandwidthRelease(
  QTScheduledBandwidthReference   sbwRef,
  long                            flags);


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
  ConstStr255Param   theString);


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
  long              flags);


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
  StringPtr         theString);


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
  long     flags);


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
  QTAtomContainer *  outContainer);


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
  kTrackModifierObjectQTEventSend = 'evnt'
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
VideoMediaResetStatistics(MediaHandler mh);


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
VideoMediaGetStatistics(MediaHandler mh);



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
  unsigned long *  stalls);



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
  long           dataSize);


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
  Handle         outParameterData);





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
  long           refcon);


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
  TimeValue *     sampleTime);


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
  TimeValue *    sampleTime);


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
  TimeValue *    sampleTime);


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
  TextDescriptionHandle   tdh);


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
  long           dataSize);


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
  TimeValue               sampleDuration);


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
  long *         flagsOut);


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
  long           dataSize);


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
  long *         offset);


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
  RGBColor *     rgbHiliteColor);


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
  OSType         dataType);






/*************************
* Sprite Media routines
**************************/
/* flags for sprite hit test routines */
enum {
  spriteHitTestBounds           = 1L << 0, /*    point must only be within sprite's bounding box*/
  spriteHitTestImage            = 1L << 1, /*  point must be within the shape of the sprite's image*/
  spriteHitTestInvisibleSprites = 1L << 2, /*  invisible sprites may be hit tested*/
  spriteHitTestIsClick          = 1L << 3, /*  for codecs that want mouse events*/
  spriteHitTestLocInDisplayCoordinates = 1L << 4 /*    set if you want to pass a display coordiate point to SpriteHitTest*/
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
  void *         propertyValue);


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
  void *         propertyValue);


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
  short *        spriteHitIndex);


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
  short *        numSprites);


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
  short *        numImages);


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
  ImageDescriptionHandle   imageDescription);


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
  long *         sampleNum);


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
  Str255         spriteName);


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
  Str255         imageName);


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
  void *         propertyValue);


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
  void *         propertyValue);


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
  QTAtomID *     spriteHitID);


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
  Boolean *      wasHit);


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
  QTAtomID *     spriteID);


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
  short *        spriteIndex);


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
  QTAtom *           atom);


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
  const float *  value);


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
  float *        value);


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
  void *         imagePropertyValue);


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
  QTRuntimeSpriteDescPtr   newSpriteDesc);


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
  QTAtomID       spriteID);


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
  Ptr            theCString);


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
  Handle *       theCString);




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
  short          yPercent);


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
  short          factor);


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
  long           bottom);


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
  long *         bottom);


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
  long *         refConID);


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
  long *         refCon);


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
  long *         flashFrameNumber);


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
  TimeValue *    movieTime);


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
  TimeValue *    movieTime);


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
  Handle *       theVariableCStringOut);


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
  Boolean        updateFocus);


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
  long           transition);


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
  unsigned char *  swfVersion);




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
  long *           refcon);


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
  long *           refcon);


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
  void *         value);


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
  void *         value);


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
  short *        dataRefIndexOut);


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
  Handle         dataRef);


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
  QTAtomID       dataRefID);




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
  QTAtomContainer *  objectList);


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
  QTAtomContainer *  rendererList);


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
  void *         group);


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
  Fixed          z);


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
  Fixed          zScale);


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
  Fixed          zDegrees);


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
  void *         cameraData);


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
  void *         cameraData);


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
  QTFloatSingle   aspectRatioXToY);


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
  QTFloatSingle *  aspectRatioXToY);



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
  void *         tQ3CameraRange);


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
  void *         tQ3CameraRange);


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
  void *         tq3viewObject);




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
  mcActionEvaluateExpressionWithType = 89, /* param is a QTEvaluateExpressionWithTypePtr*/
  mcActionGetMovieName          = 90,   /* param is a p String Handle*/
  mcActionGetMovieID            = 91,   /* param is pointer to long*/
  mcActionGetMovieActive        = 92    /* param is pointer to Boolean*/
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
typedef STACK_UPP_TYPE(MCActionFilterProcPtr)                   MCActionFilterUPP;
typedef STACK_UPP_TYPE(MCActionFilterWithRefConProcPtr)         MCActionFilterWithRefConUPP;
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
  MoviePtr            theMovie;
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
  Point             where);


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
  short             index);



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
MCRemoveAllMovies(MovieController mc);


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
  Movie             m);


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
MCRemoveMovie(MovieController mc);


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
  const EventRecord *  e);


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
  MCActionFilterUPP   blob);


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
  void *            params);


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
  Boolean           attach);


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
MCIsControllerAttached(MovieController mc);


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
  CGrafPtr          gp);


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
MCGetControllerPort(MovieController mc);


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
  Boolean           visible);


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
MCGetVisible(MovieController mc);


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
  Rect *            bounds);


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
  const Rect *      bounds);


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
MCGetControllerBoundsRgn(MovieController mc);


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
  WindowRef         w);



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
  Movie             m);



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
  TimeValue         duration);


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
  TimeScale *       scale);


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
  Point             where);


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
  WindowRef         w);


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
  Boolean           activate);


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
MCIdle(MovieController mc);


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
  long              modifiers);


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
  long              modifiers);



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
  Boolean           enabled);


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
MCIsEditingEnabled(MovieController mc);


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
MCCopy(MovieController mc);


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
MCCut(MovieController mc);


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
  Movie             srcMovie);


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
MCClear(MovieController mc);


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
MCUndo(MovieController mc);



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
  long              someFlags);



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
  long *            someFlags);




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
  RgnHandle         movieClip);


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
  RgnHandle *       movieClip);



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
  RgnHandle *       badgeRgn);


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
  MenuRef           mh);


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
  Str255            aString);


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
  long                          refCon);


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
  Boolean *         inController);


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
  RgnHandle         invalidRgn);


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
  long              modifiers);


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
  void *               element);


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
  long *            doMCActionRefCon);


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
  Boolean           scaled);


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
MCTrimMovieSegment(MovieController mc);






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
NewTimeBase(void);


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
DisposeTimeBase(TimeBase tb);


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
  TimeRecord *  tr);


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
  const TimeRecord *  tr);


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
  TimeScale   s);


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
GetTimeBaseRate(TimeBase tb);


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
  Fixed      r);


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
  TimeRecord *  tr);


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
  const TimeRecord *  tr);


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
  TimeRecord *  tr);


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
  const TimeRecord *  tr);


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
GetTimeBaseFlags(TimeBase tb);


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
  long       timeBaseFlags);


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
  const TimeRecord *  slaveZero);


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
GetTimeBaseMasterTimeBase(TimeBase tb);


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
  const TimeRecord *  slaveZero);


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
GetTimeBaseMasterClock(TimeBase tb);


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
  TimeBase      newBase);


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
  TimeScale     newScale);


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
  const TimeRecord *  src);


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
  const TimeRecord *  src);


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
  TimeRecord *  unpinnedTime);


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
  TimeRecord *  zero);


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
GetTimeBaseEffectiveRate(TimeBase tb);



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
  short      cbType);


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
DisposeCallBack(QTCallBack cb);


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
GetCallBackType(QTCallBack cb);


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
GetCallBackTimeBase(QTCallBack cb);


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
  long            param3);


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
CancelCallBack(QTCallBack cb);



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
AddCallBackToTimeBase(QTCallBack cb);


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
RemoveCallBackFromTimeBase(QTCallBack cb);


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
GetFirstCallBack(TimeBase tb);


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
GetNextCallBack(QTCallBack cb);


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
ExecuteCallBack(QTCallBack cb);






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
  ComponentInstance *  tp);



/* UPP call backs */
/*
 *  NewMovieRgnCoverUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MovieRgnCoverUPP
NewMovieRgnCoverUPP(MovieRgnCoverProcPtr userRoutine);

/*
 *  NewMovieProgressUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MovieProgressUPP
NewMovieProgressUPP(MovieProgressProcPtr userRoutine);

/*
 *  NewMovieDrawingCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MovieDrawingCompleteUPP
NewMovieDrawingCompleteUPP(MovieDrawingCompleteProcPtr userRoutine);

/*
 *  NewTrackTransferUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TrackTransferUPP
NewTrackTransferUPP(TrackTransferProcPtr userRoutine);

/*
 *  NewGetMovieUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern GetMovieUPP
NewGetMovieUPP(GetMovieProcPtr userRoutine);

/*
 *  NewMoviePreviewCallOutUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MoviePreviewCallOutUPP
NewMoviePreviewCallOutUPP(MoviePreviewCallOutProcPtr userRoutine);

/*
 *  NewTextMediaUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TextMediaUPP
NewTextMediaUPP(TextMediaProcPtr userRoutine);

/*
 *  NewActionsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern ActionsUPP
NewActionsUPP(ActionsProcPtr userRoutine);

/*
 *  NewDoMCActionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern DoMCActionUPP
NewDoMCActionUPP(DoMCActionProcPtr userRoutine);

/*
 *  NewMovieExecuteWiredActionsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MovieExecuteWiredActionsUPP
NewMovieExecuteWiredActionsUPP(MovieExecuteWiredActionsProcPtr userRoutine);

/*
 *  NewMoviePrePrerollCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MoviePrePrerollCompleteUPP
NewMoviePrePrerollCompleteUPP(MoviePrePrerollCompleteProcPtr userRoutine);

/*
 *  NewMoviesErrorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MoviesErrorUPP
NewMoviesErrorUPP(MoviesErrorProcPtr userRoutine);

/*
 *  NewQTCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTCallBackUPP
NewQTCallBackUPP(QTCallBackProcPtr userRoutine);

/*
 *  NewQTSyncTaskUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTSyncTaskUPP
NewQTSyncTaskUPP(QTSyncTaskProcPtr userRoutine);

/*
 *  NewTweenerDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern TweenerDataUPP
NewTweenerDataUPP(TweenerDataProcPtr userRoutine);

/*
 *  NewQTBandwidthNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern QTBandwidthNotificationUPP
NewQTBandwidthNotificationUPP(QTBandwidthNotificationProcPtr userRoutine);

/*
 *  NewMCActionFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MCActionFilterUPP
NewMCActionFilterUPP(MCActionFilterProcPtr userRoutine);

/*
 *  NewMCActionFilterWithRefConUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern MCActionFilterWithRefConUPP
NewMCActionFilterWithRefConUPP(MCActionFilterWithRefConProcPtr userRoutine);

/*
 *  DisposeMovieRgnCoverUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMovieRgnCoverUPP(MovieRgnCoverUPP userUPP);

/*
 *  DisposeMovieProgressUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMovieProgressUPP(MovieProgressUPP userUPP);

/*
 *  DisposeMovieDrawingCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMovieDrawingCompleteUPP(MovieDrawingCompleteUPP userUPP);

/*
 *  DisposeTrackTransferUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTrackTransferUPP(TrackTransferUPP userUPP);

/*
 *  DisposeGetMovieUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeGetMovieUPP(GetMovieUPP userUPP);

/*
 *  DisposeMoviePreviewCallOutUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMoviePreviewCallOutUPP(MoviePreviewCallOutUPP userUPP);

/*
 *  DisposeTextMediaUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTextMediaUPP(TextMediaUPP userUPP);

/*
 *  DisposeActionsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeActionsUPP(ActionsUPP userUPP);

/*
 *  DisposeDoMCActionUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeDoMCActionUPP(DoMCActionUPP userUPP);

/*
 *  DisposeMovieExecuteWiredActionsUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMovieExecuteWiredActionsUPP(MovieExecuteWiredActionsUPP userUPP);

/*
 *  DisposeMoviePrePrerollCompleteUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMoviePrePrerollCompleteUPP(MoviePrePrerollCompleteUPP userUPP);

/*
 *  DisposeMoviesErrorUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMoviesErrorUPP(MoviesErrorUPP userUPP);

/*
 *  DisposeQTCallBackUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTCallBackUPP(QTCallBackUPP userUPP);

/*
 *  DisposeQTSyncTaskUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTSyncTaskUPP(QTSyncTaskUPP userUPP);

/*
 *  DisposeTweenerDataUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeTweenerDataUPP(TweenerDataUPP userUPP);

/*
 *  DisposeQTBandwidthNotificationUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0.2 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeQTBandwidthNotificationUPP(QTBandwidthNotificationUPP userUPP);

/*
 *  DisposeMCActionFilterUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMCActionFilterUPP(MCActionFilterUPP userUPP);

/*
 *  DisposeMCActionFilterWithRefConUPP()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in QuickTime.framework
 *    CarbonLib:        in CarbonLib 1.0 and later
 *    Non-Carbon CFM:   available as macro/inline
 */
extern void
DisposeMCActionFilterWithRefConUPP(MCActionFilterWithRefConUPP userUPP);

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
  MovieRgnCoverUPP  userUPP);

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
  MovieProgressUPP  userUPP);

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
  MovieDrawingCompleteUPP  userUPP);

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
  TrackTransferUPP  userUPP);

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
  GetMovieUPP  userUPP);

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
  MoviePreviewCallOutUPP  userUPP);

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
  TextMediaUPP  userUPP);

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
  ActionsUPP        userUPP);

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
  DoMCActionUPP  userUPP);

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
  MovieExecuteWiredActionsUPP  userUPP);

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
  MoviePrePrerollCompleteUPP  userUPP);

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
  MoviesErrorUPP  userUPP);

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
  QTCallBackUPP  userUPP);

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
  QTSyncTaskUPP  userUPP);

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
  TweenerDataUPP              userUPP);

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
  QTBandwidthNotificationUPP  userUPP);

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
  MCActionFilterUPP  userUPP);

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
  MCActionFilterWithRefConUPP  userUPP);


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
    kMusicMediaGetIndexedTunePlayerSelect      = 0x0101
};


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

#endif /* __MOVIES__ */

