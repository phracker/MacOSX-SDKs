/*
     File:       QuickTime/MoviesFormat.h
 
     Contains:   QuickTime Interfaces.
 
     Version:    QuickTime 7.7.3
 
     Copyright:  © 1990-2015 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

/*
  QuickTime has been deprecated in 10.9.

  AVFoundation and AVKit are the frameworks recommended for all new development 
  involving time-based audiovisual media on OS X.
*/

#ifndef __MOVIESFORMAT__
#define __MOVIESFORMAT__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __MOVIES__
#include <QuickTime/Movies.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#pragma pack(push, 2)

enum {
  kMovieVersion                 = 0     /* version number of the format here described */
};

/****************************************
*
*   General Types -
*       These types are used in more than one of the
*       directory types.
*
****************************************/
/* MoviesUserData is the type used for user data in movie and track directories */
struct MoviesUserData {
  SInt32              size;                   /* size of this user data */
  SInt32              udType;                 /* type of user data */
  char                data[1];                /* the user data */
};
typedef struct MoviesUserData           MoviesUserData;
struct UserDataAtom {
  SInt32              size;
  SInt32              atomType;
  MoviesUserData      userData[1];
};
typedef struct UserDataAtom             UserDataAtom;
/* MoviesDataDescription tells us where the data for the movie or track lives.
   The data can follow the directory, be in the datafork of the same file as the directory resource,
   be in the resource fork of the same file as the directory resource, be in another file in the
   data fork or resource fork, or require a specific bottleneck to fetch the data. */
/****************************************
*
*   MediaDirectory information -
*       The MediaDirectory is tightly coupled to the data.
*
****************************************/
/* SampleDescription is in Movies.h */
struct SampleDescriptionAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'stsd' */
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */
  SInt32              numEntries;
  SampleDescription   sampleDescTable[1];
};
typedef struct SampleDescriptionAtom    SampleDescriptionAtom;
/* TimeToSampleNum maps physical sample time to physical sample number. */
struct TimeToSampleNum {
  SInt32              sampleCount;
  TimeValue           sampleDuration;
};
typedef struct TimeToSampleNum          TimeToSampleNum;
struct TimeToSampleNumAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'stts' */
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */
  SInt32              numEntries;
  TimeToSampleNum     timeToSampleNumTable[1];
};
typedef struct TimeToSampleNumAtom      TimeToSampleNumAtom;
/* SyncSamples is a list of the physical samples which are self contained. */
struct SyncSampleAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'stss' */
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */
  SInt32              numEntries;
  SInt32              syncSampleTable[1];
};
typedef struct SyncSampleAtom           SyncSampleAtom;
/* SampleToChunk maps physical sample number to chunk number. */
/* same as SampleToChunk, but redundant first sample is removed */
struct SampleToChunk {
  SInt32              firstChunk;
  SInt32              samplesPerChunk;
  SInt32              sampleDescriptionID;
};
typedef struct SampleToChunk            SampleToChunk;
struct SampleToChunkAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'stsc' */
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */
  SInt32              numEntries;
  SampleToChunk       sampleToChunkTable[1];
};
typedef struct SampleToChunkAtom        SampleToChunkAtom;
struct ChunkOffsetAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'stco' */
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */
  SInt32              numEntries;
  SInt32              chunkOffsetTable[1];
};
typedef struct ChunkOffsetAtom          ChunkOffsetAtom;
struct SampleSizeAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'stsz' */
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */
  SInt32              sampleSize;
  SInt32              numEntries;
  SInt32              sampleSizeTable[1];
};
typedef struct SampleSizeAtom           SampleSizeAtom;
struct ShadowSync {
  SInt32              fdSampleNum;
  SInt32              syncSampleNum;
};
typedef struct ShadowSync               ShadowSync;
struct ShadowSyncAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'stsz' */
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */
  SInt32              numEntries;
  ShadowSync          shadowSyncTable[1];
};
typedef struct ShadowSyncAtom           ShadowSyncAtom;
/* CompositionOffsetEntry maps sample numbers to composition offsets. */
struct CompositionOffsetEntry {
  SInt32              sampleCount;
  TimeValue           displayOffset;
};
typedef struct CompositionOffsetEntry   CompositionOffsetEntry;
struct CompositionOffsetAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'ctts' */
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */
  SInt32              numEntries;
  CompositionOffsetEntry  compositionOffsetTable[1];
};
typedef struct CompositionOffsetAtom    CompositionOffsetAtom;
struct SampleDependencyAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'sdtp' */
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */
  UInt8               sampleDependencyTable[1];
};
typedef struct SampleDependencyAtom     SampleDependencyAtom;
/*
NOTE: The values for these flags that shipped with QuickTime 7.0 were incorrect. 
They matched neither the specification nor the implementation -- the "Yes" and "No" bits
were reversed.  The flags have been corrected but renamed to ensure that code using
the incorrect flags is reviewed by developers.
enum {
    kQTSampleDependency_DependsOnOthers = 1<<5,         // INCORRECT VALUE
    kQTSampleDependency_DoesNotDependOnOthers = 1<<4,   // INCORRECT VALUE
    kQTSampleDependency_IsDependedOnByOthers = 1<<3,    // INCORRECT VALUE
    kQTSampleDependency_IsNotDependedOnByOthers = 1<<2, // INCORRECT VALUE
    kQTSampleDependency_HasRedundantCoding = 1<<1,      // INCORRECT VALUE
    kQTSampleDependency_HasNoRedundantCoding = 1<<0     // INCORRECT VALUE
};
*/
/* Values for entries in SampleDependencyAtom.sampleDependencyTable[]*/
enum {
                                        /* bit 0x80 is reserved; bit combinations 0x30, 0xC0 and 0x03 are reserved*/
  kQTSampleDependency_EarlierDisplayTimesAllowed = 1 << 6, /* corresponds to flag mediaSampleEarlierDisplayTimesAllowed except at different bit offset*/
  kQTSampleDependency_DoesNotDependOnOthers_Corrected = 1 << 5, /* ie: an I picture*/
  kQTSampleDependency_DependsOnOthers_Corrected = 1 << 4, /* ie: not an I picture*/
  kQTSampleDependency_IsNotDependedOnByOthers_Corrected = 1 << 3, /* mediaSampleDroppable*/
  kQTSampleDependency_IsDependedOnByOthers_Corrected = 1 << 2,
  kQTSampleDependency_HasNoRedundantCoding_Corrected = 1 << 1,
  kQTSampleDependency_HasRedundantCoding_Corrected = 1 << 0
};

struct CompositionShiftLeastGreatestAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'cslg' */
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */
  SInt32              compositionOffsetToDTDDeltaShift;
  SInt32              leastDecodeToDisplayDelta;
  SInt32              greatestDecodeToDisplayDelta;
  SInt32              displayStartTime;
  SInt32              displayEndTime;
};
typedef struct CompositionShiftLeastGreatestAtom CompositionShiftLeastGreatestAtom;
struct PartialSyncSampleAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'stps' */
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */
  SInt32              numEntries;
  UInt32              partialSyncSampleTable[1];
};
typedef struct PartialSyncSampleAtom    PartialSyncSampleAtom;
struct SampleTableAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'stbl' */

  SampleDescriptionAtom  sampleDescription;
  TimeToSampleNumAtom  timeToSampleNum;
  SampleToChunkAtom   sampleToChunk;
  SyncSampleAtom      syncSample;
  SampleSizeAtom      sampleSize;
  ChunkOffsetAtom     chunkOffset;
  ShadowSyncAtom      shadowSync;
};
typedef struct SampleTableAtom          SampleTableAtom;
struct PublicHandlerInfo {
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */

  SInt32              componentType;
  SInt32              componentSubType;
  SInt32              componentManufacturer;
  SInt32              componentFlags;
  SInt32              componentFlagsMask;
  char                componentName[1];
};
typedef struct PublicHandlerInfo        PublicHandlerInfo;
struct HandlerAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'hdlr' */

  PublicHandlerInfo   hInfo;
};
typedef struct HandlerAtom              HandlerAtom;
/* a data reference is a private structure */

typedef SInt32                          DataRefAtom;
struct DataInfoAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'dinf' */

  DataRefAtom         dataRef;
};
typedef struct DataInfoAtom             DataInfoAtom;
struct RgnAtom {
  SInt32              size;
  SInt32              atomType;

  SInt16              rgnSize;
  Rect                rgnBBox;
  char                data[1];
};
typedef struct RgnAtom                  RgnAtom;
struct MatteCompressedAtom {
  SInt32              size;
  SInt32              atomType;

  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */

  ImageDescription    matteImageDescription;

  char                matteData[1];
};
typedef struct MatteCompressedAtom      MatteCompressedAtom;
struct MatteAtom {
  SInt32              size;
  SInt32              atomType;

  MatteCompressedAtom  aCompressedMatte;
};
typedef struct MatteAtom                MatteAtom;
struct ClippingAtom {
  SInt32              size;
  SInt32              atomType;

  RgnAtom             aRgnClip;
};
typedef struct ClippingAtom             ClippingAtom;
/***********************
* Media Info Example Structures
***********************/

struct VideoMediaInfoHeader {
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */

  SInt16              graphicsMode;           /* for QD - transfer mode */
  SInt16              opColorRed;             /* opcolor for transfer mode */
  SInt16              opColorGreen;
  SInt16              opColorBlue;
};
typedef struct VideoMediaInfoHeader     VideoMediaInfoHeader;
struct VideoMediaInfoHeaderAtom {
  SInt32              size;                   /* size of Media info */
  SInt32              atomType;               /* = 'vmhd' */
  VideoMediaInfoHeader  vmiHeader;
};
typedef struct VideoMediaInfoHeaderAtom VideoMediaInfoHeaderAtom;
struct VideoMediaInfo {
  SInt32              size;                   /* size of Media info */
  SInt32              atomType;               /* = 'minf' */

  VideoMediaInfoHeaderAtom  header;

  HandlerAtom         dataHandler;

  DataInfoAtom        dataInfo;

  SampleTableAtom     sampleTable;
};
typedef struct VideoMediaInfo           VideoMediaInfo;
struct SoundMediaInfoHeader {
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */

  SInt16              balance;
  SInt16              rsrvd;
};
typedef struct SoundMediaInfoHeader     SoundMediaInfoHeader;
struct SoundMediaInfoHeaderAtom {
  SInt32              size;                   /* size of Media info */
  SInt32              atomType;               /* = 'vmhd' */

  SoundMediaInfoHeader  smiHeader;
};
typedef struct SoundMediaInfoHeaderAtom SoundMediaInfoHeaderAtom;
struct SoundMediaInfo {
  SInt32              size;                   /* size of Media info */
  SInt32              atomType;               /* = 'minf' */

  SoundMediaInfoHeaderAtom  header;

  HandlerAtom         dataHandler;

  DataRefAtom         dataReference;

  SampleTableAtom     sampleTable;
};
typedef struct SoundMediaInfo           SoundMediaInfo;
/* whatever data the media handler needs goes after the atomType */
struct MediaInfo {
  SInt32              size;
  SInt32              atomType;
};
typedef struct MediaInfo                MediaInfo;
/***********************
* Media Directory Structures
***********************/
struct MediaHeader {
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */

  SInt32              creationTime;           /* seconds since Jan 1904 when directory was created */
  SInt32              modificationTime;       /* seconds since Jan 1904 when directory was appended */

  TimeValue           timeScale;              /* start time for Media (Media time) */
  TimeValue           duration;               /* length of Media (Media time) */

  SInt16              language;
  SInt16              quality;
};
typedef struct MediaHeader              MediaHeader;
struct MediaHeaderAtom {
  SInt32              size;
  SInt32              atomType;

  MediaHeader         header;
};
typedef struct MediaHeaderAtom          MediaHeaderAtom;
struct MediaDirectory {
  SInt32              size;
  SInt32              atomType;               /* = 'mdia' */

  MediaHeaderAtom     mediaHeader;            /* standard Media information */

  HandlerAtom         mediaHandler;

  MediaInfo           mediaInfo;
};
typedef struct MediaDirectory           MediaDirectory;
/***********************
* Track Structures
***********************/
enum {
  TrackEnable                   = 1 << 0,
  TrackInMovie                  = 1 << 1,
  TrackInPreview                = 1 << 2,
  TrackInPoster                 = 1 << 3
};

struct TrackHeader {
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */

  SInt32              creationTime;           /* seconds since Jan 1904 when directory was created */
  SInt32              modificationTime;       /* seconds since Jan 1904 when directory was appended */

  SInt32              trackID;

  SInt32              reserved1;

  TimeValue           duration;               /* length of track (track time) */

  SInt32              reserved2;
  SInt32              reserved3;

  SInt16              layer;
  SInt16              alternateGroup;

  SInt16              volume;
  SInt16              reserved4;

  MatrixRecord        matrix;
  Fixed               trackWidth;
  Fixed               trackHeight;
};
typedef struct TrackHeader              TrackHeader;
struct TrackHeaderAtom {
  SInt32              size;                   /* size of track header */
  SInt32              atomType;               /* = 'tkhd' */

  TrackHeader         header;
};
typedef struct TrackHeaderAtom          TrackHeaderAtom;
struct EditListType {
  TimeValue           trackDuration;
  TimeValue           mediaTime;
  Fixed               mediaRate;
};
typedef struct EditListType             EditListType;
struct EditListAtom {
  SInt32              size;
  SInt32              atomType;               /* = elst */

  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */

  SInt32              numEntries;
  EditListType        editListTable[1];
};
typedef struct EditListAtom             EditListAtom;
struct EditsAtom {
  SInt32              size;
  SInt32              atomType;               /* = edts */

  EditListAtom        editList;
};
typedef struct EditsAtom                EditsAtom;
struct TrackLoadSettings {
  TimeValue           preloadStartTime;
  TimeValue           preloadDuration;
  SInt32              preloadFlags;
  SInt32              defaultHints;
};
typedef struct TrackLoadSettings        TrackLoadSettings;
struct TrackLoadSettingsAtom {
  SInt32              size;
  SInt32              atomType;               /* = load */

  TrackLoadSettings   settings;
};
typedef struct TrackLoadSettingsAtom    TrackLoadSettingsAtom;
struct TrackCleanApertureDimensions {
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */
  FixedPoint          cleanApertureDimensions;
};
typedef struct TrackCleanApertureDimensions TrackCleanApertureDimensions;
struct TrackCleanApertureDimensionsAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'tapt' */

  TrackCleanApertureDimensions  cleanApertureDimensions;
};
typedef struct TrackCleanApertureDimensionsAtom TrackCleanApertureDimensionsAtom;
struct TrackProductionApertureDimensions {
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */
  FixedPoint          productionApertureDimensions;
};
typedef struct TrackProductionApertureDimensions TrackProductionApertureDimensions;
struct TrackProductionApertureDimensionsAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'prof' */

  TrackProductionApertureDimensions  productionApertureDimensions;
};
typedef struct TrackProductionApertureDimensionsAtom TrackProductionApertureDimensionsAtom;
struct TrackEncodedPixelsDimensions {
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */
  FixedPoint          encodedPixelsDimensions;
};
typedef struct TrackEncodedPixelsDimensions TrackEncodedPixelsDimensions;
struct TrackEncodedPixelsDimensionsAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'enof' */

  TrackEncodedPixelsDimensions  encodedPixelsDimensions;
};
typedef struct TrackEncodedPixelsDimensionsAtom TrackEncodedPixelsDimensionsAtom;
struct TrackDirectory {
  SInt32              size;
  SInt32              atomType;               /* = 'trak' */

  TrackHeaderAtom     trackHeader;            /* standard track information */

  ClippingAtom        trackClip;

  EditsAtom           edits;

  MediaDirectory      media;

  UserDataAtom        userData;               /* space for extending with new data types */
};
typedef struct TrackDirectory           TrackDirectory;
/****************************************
*
*   MovieDirectory -
*       The MovieDirectory is the top level structure which
*       holds the TrackInstance describing where the
*       TrackDirectories are.
*
****************************************/
struct MovieHeader {
  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */

  SInt32              creationTime;           /* seconds since Jan 1904 when directory was created */
  SInt32              modificationTime;       /* seconds since Jan 1904 when directory was appended */

  TimeValue           timeScale;              /* Time specifications */
  TimeValue           duration;
  Fixed               preferredRate;          /* rate at which to play this movie */

  SInt16              preferredVolume;        /* volume to play movie at */
  SInt16              reserved1;

  SInt32              preferredLong1;
  SInt32              preferredLong2;

  MatrixRecord        matrix;

  TimeValue           previewTime;            /* time in track the proxy begins (track time) */
  TimeValue           previewDuration;        /* how long the proxy lasts (track time) */

  TimeValue           posterTime;             /* time in track the proxy begins (track time) */

  TimeValue           selectionTime;          /* time in track the proxy begins (track time) */
  TimeValue           selectionDuration;      /* time in track the proxy begins (track time) */
  TimeValue           currentTime;            /* time in track the proxy begins (track time) */

  SInt32              nextTrackID;            /* next value to use for a TrackID */
};
typedef struct MovieHeader              MovieHeader;
struct MovieHeaderAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'mvhd' */

  MovieHeader         header;
};
typedef struct MovieHeaderAtom          MovieHeaderAtom;
struct TrackDirectoryEntry {
  TrackDirectory      trackDirectory;         /* Track directory information */
};
typedef struct TrackDirectoryEntry      TrackDirectoryEntry;
struct MovieDirectory {
  SInt32              size;
  SInt32              atomType;               /* = 'moov' */

  MovieHeaderAtom     header;

  ClippingAtom        movieClip;

                                              /* Track Directories */
  TrackDirectoryEntry  track[1];              /* Track directory information */

                                              /* User data for Movie */
  UserDataAtom        userData;               /* space for user extensions */
};
typedef struct MovieDirectory           MovieDirectory;
/****************************************
****************************************/

/* Movie formats and tags */
enum {
                                        /* some system defined format IDs */
  QT_MOVIE_TYPE                 = 'moov',
  QT_TRACK_TYPE                 = 'trak',
  QT_MEDIA_TYPE                 = 'mdia',
  QT_VIDEO_TYPE                 = 'vide',
  QT_SOUND_TYPE                 = 'soun'
};

enum {
  MOVIE_TYPE                    = 'moov',
  TRACK_TYPE                    = 'trak',
  VIDEO_TYPE                    = 'vide',
  SOUND_TYPE                    = 'soun'
};

#if !TARGET_OS_WIN32
/* The name "MEDIA_TYPE" has a name space collision on Win32.*/
enum {
  MEDIA_TYPE                    = 'mdia'
};

#endif  /* !TARGET_OS_WIN32 */

/* atom id's */
enum {
  MovieAID                      = 'moov',
  MovieHeaderAID                = 'mvhd',
  ClipAID                       = 'clip',
  RgnClipAID                    = 'crgn',
  MatteAID                      = 'matt',
  MatteCompAID                  = 'kmat',
  TrackAID                      = 'trak',
  UserDataAID                   = 'udta',
  TrackHeaderAID                = 'tkhd',
  EditsAID                      = 'edts',
  EditListAID                   = 'elst',
  MediaAID                      = 'mdia',
  MediaHeaderAID                = 'mdhd',
  MediaInfoAID                  = 'minf',
  VideoMediaInfoHeaderAID       = 'vmhd',
  SoundMediaInfoHeaderAID       = 'smhd',
  GenericMediaInfoHeaderAID     = 'gmhd',
  GenericMediaInfoAID           = 'gmin',
  DataInfoAID                   = 'dinf',
  DataRefAID                    = 'dref',
  SampleTableAID                = 'stbl',
  STSampleDescAID               = 'stsd',
  STTimeToSampAID               = 'stts',
  STSyncSampleAID               = 'stss',
  STSampleToChunkAID            = 'stsc',
  STShadowSyncAID               = 'stsh',
  HandlerAID                    = 'hdlr',
  STSampleSizeAID               = 'stsz',
  STChunkOffsetAID              = 'stco',
  STChunkOffset64AID            = 'co64',
  STSampleIDAID                 = 'stid',
  STCompositionOffsetAID        = 'ctts',
  STSampleDependencyAID         = 'sdtp',
  STCompositionShiftLeastGreatestAID = 'cslg',
  STPartialSyncSampleAID        = 'stps',
  DataRefContainerAID           = 'drfc',
  TrackReferenceAID             = 'tref',
  ColorTableAID                 = 'ctab',
  LoadSettingsAID               = 'load',
  PropertyAtomAID               = 'code',
  InputMapAID                   = 'imap',
  MovieBufferHintsAID           = 'mbfh',
  MovieDataRefAliasAID          = 'mdra',
  SoundLocalizationAID          = 'sloc',
  CompressedMovieAID            = 'cmov',
  CompressedMovieDataAID        = 'cmvd',
  DataCompressionAtomAID        = 'dcom',
  ReferenceMovieRecordAID       = 'rmra',
  ReferenceMovieDescriptorAID   = 'rmda',
  ReferenceMovieDataRefAID      = 'rdrf',
  ReferenceMovieVersionCheckAID = 'rmvc',
  ReferenceMovieDataRateAID     = 'rmdr',
  ReferenceMovieComponentCheckAID = 'rmcd',
  ReferenceMovieQualityAID      = 'rmqu',
  ReferenceMovieLanguageAID     = 'rmla',
  ReferenceMovieCPURatingAID    = 'rmcs',
  ReferenceMovieAlternateGroupAID = 'rmag',
  ReferenceMovieNetworkStatusAID = 'rnet',
  CloneMediaAID                 = 'clon',
  FileTypeAID                   = 'ftyp',
  SecureContentInfoAID          = 'sinf',
  SecureContentSchemeTypeAID    = 'schm',
  SecureContentSchemeInfoAID    = 'schi',
  TrackApertureModeDimensionsAID = 'tapt', /* container atom including TrackCleanApertureDimensionsAID, TrackProductionApertureDimensionsAID and TrackEncodedPixelsDimensionsAID */
  TrackCleanApertureDimensionsAID = 'clef',
  TrackProductionApertureDimensionsAID = 'prof',
  TrackEncodedPixelsDimensionsAID = 'enof'
};

/* Text ATOM definitions*/

struct TextBoxAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'tbox' */
  Rect                textBox;                /* New text box (overrides defaultTextBox)*/
};
typedef struct TextBoxAtom              TextBoxAtom;
struct HiliteAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'hlit' */
  SInt32              selStart;               /* hilite selection start character*/
  SInt32              selEnd;                 /* hilite selection end character*/
};
typedef struct HiliteAtom               HiliteAtom;
struct KaraokeRec {
  TimeValue           timeVal;
  SInt16              beginHilite;
  SInt16              endHilite;
};
typedef struct KaraokeRec               KaraokeRec;
struct KaraokeAtom {
  SInt32              numEntries;
  KaraokeRec          karaokeEntries[1];
};
typedef struct KaraokeAtom              KaraokeAtom;
/* for ReferenceMovieDataRefRecord.flags*/
enum {
  kDataRefIsSelfContained       = (1 << 0)
};

struct ReferenceMovieDataRefRecord {
  SInt32              flags;
  OSType              dataRefType;
  SInt32              dataRefSize;
  char                dataRef[1];
};
typedef struct ReferenceMovieDataRefRecord ReferenceMovieDataRefRecord;
/* for VersionCheckRecord.checkType*/
enum {
  kVersionCheckMin              = 0,    /* val1 is the min. version required*/
  kVersionCheckMask             = 1     /* (gestalt return value & val2) must == val1*/
};

struct QTAltVersionCheckRecord {
  SInt32              flags;                  /* currently always 0*/
  OSType              gestaltTag;
  UInt32              val1;
  UInt32              val2;
  SInt16              checkType;
};
typedef struct QTAltVersionCheckRecord  QTAltVersionCheckRecord;
/* some helpful constants for DataRateRecord.dataRate */
enum {
  kDataRate144ModemRate         = 1400,
  kDataRate288ModemRate         = 2800,
  kDataRateISDNRate             = 5600,
  kDataRateDualISDNRate         = 11200,
  kDataRate256kbpsRate          = 25600,
  kDataRate384kbpsRate          = 38400,
  kDataRate512kbpsRate          = 51200,
  kDataRate768kbpsRate          = 76800,
  kDataRate1MbpsRate            = 100000,
  kDataRateT1Rate               = 150000,
  kDataRateInfiniteRate         = 0x7FFFFFFF,
  kDataRateDefaultIfNotSet      = kDataRate512kbpsRate
};

struct QTAltDataRateRecord {
  SInt32              flags;                  /* currently always 0*/
  SInt32              dataRate;
};
typedef struct QTAltDataRateRecord      QTAltDataRateRecord;
struct QTAltComponentCheckRecord {
  SInt32              flags;                  /* currently always 0 */
  ComponentDescription  cd;
  UInt32              minVersion;
};
typedef struct QTAltComponentCheckRecord QTAltComponentCheckRecord;
struct QTAltLanguageRecord {
  SInt32              flags;                  /* currently always 0*/
  SInt16              language;
};
typedef struct QTAltLanguageRecord      QTAltLanguageRecord;

enum {
  kQTCPUSpeed1Rating            = 100,  /* slowest*/
  kQTCPUSpeed2Rating            = 200,
  kQTCPUSpeed3Rating            = 300,
  kQTCPUSpeed4Rating            = 400,
  kQTCPUSpeed5Rating            = 500   /* fastest*/
};

struct QTAltCPURatingRecord {
  UInt32              flags;                  /* currently always 0*/
  UInt16              speed;
};
typedef struct QTAltCPURatingRecord     QTAltCPURatingRecord;
struct ReferenceMovieNetworkStatusRecord {
  UInt32              flags;                  /* currently always 0*/
  UInt32              valueCount;             /* how many status values are in array*/
  SInt32              netStatusValues[1];     /* a value from kQTNetworkStatus... constants*/
};
typedef struct ReferenceMovieNetworkStatusRecord ReferenceMovieNetworkStatusRecord;
struct CloneRecord {
  SInt32              flags;
  SInt32              masterTrackID;          /* track ID of the track we're cloning */
};
typedef struct CloneRecord              CloneRecord;
struct CloneAtom {
  SInt32              size;
  SInt32              atomType;               /* = clon */

  CloneRecord         cloneInfo;
};
typedef struct CloneAtom                CloneAtom;
struct FileTypeAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'ftyp' */
  SInt32              majorBrand;             /* best use brand */
  SInt32              minorVersion;
  SInt32              compatibleBrands[4];    /* 1 or greater */
};
typedef struct FileTypeAtom             FileTypeAtom;
enum {
  kQTFileTypeBrandQuickTimeMovie = 'qt  ', /* QuickTime movie files*/
  kQTFileTypeBrandISOFile       = 'isom', /* ISO Base Media files*/
  kQTFileTypeBrandMPEG4v1       = 'mp41', /* MPEG-4 (ISO/IEC 14496-1) version 1 files*/
  kQTFileTypeBrandMPEG4v2       = 'mp42' /* MPEG-4 (ISO/IEC 14496-1) version 2 files*/
};

struct SecureContentInfoAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'sinf' */
};
typedef struct SecureContentInfoAtom    SecureContentInfoAtom;
struct SecureContentSchemeTypeAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'schm' */

  SInt32              flags;                  /* 1 byte of version / 3 bytes of flags */

  SInt32              schemeType;
  UInt32              schemeVersion;
                                              /* if flags & 1, C string holding URL for security component server*/
};
typedef struct SecureContentSchemeTypeAtom SecureContentSchemeTypeAtom;
struct SecureContentSchemeInfoAtom {
  SInt32              size;
  SInt32              atomType;               /* = 'schi' */
};
typedef struct SecureContentSchemeInfoAtom SecureContentSchemeInfoAtom;

#pragma pack(pop)


#endif /* __MOVIESFORMAT__ */

