/*
     File:       CarbonCore/AIFF.h
 
     Contains:   Definition of AIFF file format components.
 
     Version:    CarbonCore-682.26~1
 
     Copyright:  © 1989-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __AIFF__
#define __AIFF__

#ifndef __MACTYPES__
#include <CarbonCore/MacTypes.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#pragma options align=mac68k

enum {
  AIFFID                        = 'AIFF',
  AIFCID                        = 'AIFC',
  FormatVersionID               = 'FVER',
  CommonID                      = 'COMM',
  FORMID                        = 'FORM',
  SoundDataID                   = 'SSND',
  MarkerID                      = 'MARK',
  InstrumentID                  = 'INST',
  MIDIDataID                    = 'MIDI',
  AudioRecordingID              = 'AESD',
  ApplicationSpecificID         = 'APPL',
  CommentID                     = 'COMT',
  NameID                        = 'NAME',
  AuthorID                      = 'AUTH',
  CopyrightID                   = '(c) ',
  AnnotationID                  = 'ANNO'
};

enum {
  NoLooping                     = 0,
  ForwardLooping                = 1,
  ForwardBackwardLooping        = 2
};

enum {
                                        /* AIFF-C Versions */
  AIFCVersion1                  = (long)0xA2805140
};

/* Compression Names */
#define NoneName                        "\pnot compressed"
#define ACE2to1Name                     "\pACE 2-to-1"
#define ACE8to3Name                     "\pACE 8-to-3"
#define MACE3to1Name                    "\pMACE 3-to-1"
#define MACE6to1Name                    "\pMACE 6-to-1"
enum {
                                        /* Compression Types */
  NoneType                      = 'NONE',
  ACE2Type                      = 'ACE2',
  ACE8Type                      = 'ACE8',
  MACE3Type                     = 'MAC3',
  MACE6Type                     = 'MAC6'
};

typedef unsigned long                   ID;
typedef short                           MarkerIdType;
struct ChunkHeader {
  ID                  ckID;
  long                ckSize;
};
typedef struct ChunkHeader              ChunkHeader;
struct ContainerChunk {
  ID                  ckID;
  long                ckSize;
  ID                  formType;
};
typedef struct ContainerChunk           ContainerChunk;
struct FormatVersionChunk {
  ID                  ckID;
  long                ckSize;
  unsigned long       timestamp;
};
typedef struct FormatVersionChunk       FormatVersionChunk;
typedef FormatVersionChunk *            FormatVersionChunkPtr;
struct CommonChunk {
  ID                  ckID;
  long                ckSize;
  short               numChannels;
  unsigned long       numSampleFrames;
  short               sampleSize;
  extended80          sampleRate;
};
typedef struct CommonChunk              CommonChunk;
typedef CommonChunk *                   CommonChunkPtr;
struct ExtCommonChunk {
  ID                  ckID;
  long                ckSize;
  short               numChannels;
  unsigned long       numSampleFrames;
  short               sampleSize;
  extended80          sampleRate;
  ID                  compressionType;
  char                compressionName[1];     /* variable length array, Pascal string */
};
typedef struct ExtCommonChunk           ExtCommonChunk;
typedef ExtCommonChunk *                ExtCommonChunkPtr;
struct SoundDataChunk {
  ID                  ckID;
  long                ckSize;
  unsigned long       offset;
  unsigned long       blockSize;
};
typedef struct SoundDataChunk           SoundDataChunk;
typedef SoundDataChunk *                SoundDataChunkPtr;
struct Marker {
  MarkerIdType        id;
  unsigned long       position;
  Str255              markerName;
};
typedef struct Marker                   Marker;
struct MarkerChunk {
  ID                  ckID;
  long                ckSize;
  unsigned short      numMarkers;
  Marker              Markers[1];             /* variable length array */
};
typedef struct MarkerChunk              MarkerChunk;
typedef MarkerChunk *                   MarkerChunkPtr;
struct AIFFLoop {
  short               playMode;
  MarkerIdType        beginLoop;
  MarkerIdType        endLoop;
};
typedef struct AIFFLoop                 AIFFLoop;
struct InstrumentChunk {
  ID                  ckID;
  long                ckSize;
  UInt8               baseFrequency;
  UInt8               detune;
  UInt8               lowFrequency;
  UInt8               highFrequency;
  UInt8               lowVelocity;
  UInt8               highVelocity;
  short               gain;
  AIFFLoop            sustainLoop;
  AIFFLoop            releaseLoop;
};
typedef struct InstrumentChunk          InstrumentChunk;
typedef InstrumentChunk *               InstrumentChunkPtr;
struct MIDIDataChunk {
  ID                  ckID;
  long                ckSize;
  UInt8               MIDIdata[1];            /* variable length array */
};
typedef struct MIDIDataChunk            MIDIDataChunk;
typedef MIDIDataChunk *                 MIDIDataChunkPtr;
struct AudioRecordingChunk {
  ID                  ckID;
  long                ckSize;
  UInt8               AESChannelStatus[24];
};
typedef struct AudioRecordingChunk      AudioRecordingChunk;
typedef AudioRecordingChunk *           AudioRecordingChunkPtr;
struct ApplicationSpecificChunk {
  ID                  ckID;
  long                ckSize;
  OSType              applicationSignature;
  UInt8               data[1];                /* variable length array */
};
typedef struct ApplicationSpecificChunk ApplicationSpecificChunk;
typedef ApplicationSpecificChunk *      ApplicationSpecificChunkPtr;
struct Comment {
  unsigned long       timeStamp;
  MarkerIdType        marker;
  unsigned short      count;
  char                text[1];                /* variable length array, Pascal string */
};
typedef struct Comment                  Comment;
struct CommentsChunk {
  ID                  ckID;
  long                ckSize;
  unsigned short      numComments;
  Comment             comments[1];            /* variable length array */
};
typedef struct CommentsChunk            CommentsChunk;
typedef CommentsChunk *                 CommentsChunkPtr;
struct TextChunk {
  ID                  ckID;
  long                ckSize;
  char                text[1];                /* variable length array, Pascal string */
};
typedef struct TextChunk                TextChunk;
typedef TextChunk *                     TextChunkPtr;

#pragma options align=reset


#endif /* __AIFF__ */

