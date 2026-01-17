/*
     File:       AudioToolbox/CAFFile.h

     Contains:   Tthe data structures contained within a CAF File

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 2004 by Apple Computer, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

*/

#ifndef _CAFFile_H_
#define _CAFFile_H_

#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreServices/CoreServices.h>
#else
	#include <MacTypes.h>
#endif

// In a CAF File all of these types' byte order is big endian.
// When reading or writing these values the program will need to flip byte order to native endian

// CAF File Header
enum {
	kCAF_FileType				= 'caff',
	kCAF_FileVersion_Initial	= 1
};

// CAF Chunk Types	
enum {
	kCAF_StreamDescriptionChunkID   = 'desc',
	kCAF_AudioDataChunkID			= 'data',
	kCAF_ChannelLayoutChunkID		= 'chan',
	kCAF_FillerChunkID				= 'free',
	kCAF_MarkerChunkID				= 'mark',
	kCAF_RegionChunkID				= 'regn',
	kCAF_InstrumentChunkID			= 'inst',
	kCAF_MagicCookieID				= 'kuki',
	kCAF_InfoStringsChunkID			= 'info',
	kCAF_EditCommentsChunkID		= 'edct',
	kCAF_PacketTableChunkID			= 'pakt',
	kCAF_StringsChunkID				= 'strg',
	kCAF_UUIDChunkID				= 'uuid',
	kCAF_PeakChunkID				= 'peak',
	kCAF_OverviewChunkID			= 'ovvw',
	kCAF_MIDIChunkID				= 'midi',
	kCAF_UMIDChunkID				= 'umid'
};


struct CAFFileHeader
{
        UInt32          mFileType;			// 'caff'
		UInt16			mFileVersion;		//initial revision set to 1
		UInt16			mFileFlags;			//initial revision set to 0
};
typedef struct CAFFileHeader CAFFileHeader;


struct CAFChunkHeader
{
        UInt32          mChunkType; // four char code
        SInt64          mChunkSize;  // size in bytes of the chunk data (not including this header).
									// mChunkSize is SInt64 not UInt64 because negative values for 
									// the data size can have a special meaning
};
typedef struct CAFChunkHeader CAFChunkHeader;

struct CAF_UUID_ChunkHeader
{
        CAFChunkHeader   mHeader;
        UInt8            mUUID[16];
};
typedef struct CAF_UUID_ChunkHeader CAF_UUID_ChunkHeader;


// Every file MUST have this chunk. It MUST be the first chunk in the file
struct CAFAudioDescription
{
        Float64 mSampleRate;
        UInt32  mFormatID;
        UInt32  mFormatFlags;
        UInt32  mBytesPerPacket;
        UInt32  mFramesPerPacket;
        UInt32  mChannelsPerFrame;
        UInt32  mBitsPerChannel;
};
typedef struct CAFAudioDescription  CAFAudioDescription;

// these are the flags if the format ID is 'lpcm'
// <CoreAudio/CoreAudioTypes.h> declares some of the format constants 
// that can be used as Data Formats in a CAF file
enum
{
    kCAFLinearPCMFormatFlagIsFloat				= (1L << 0),
    kCAFLinearPCMFormatFlagIsLittleEndian		= (1L << 1)
};


// 'chan'  Optional chunk.
// struct AudioChannelLayout  as defined in CoreAudioTypes.h.

// 'free'
// this is a padding chunk for reserving space in the file. content is meaningless.

// 'kuki'
// this is the magic cookie chunk. bag of bytes.

// 'data'    Every file MUST have this chunk.
// actual audio data can be any format as described by the 'asbd' chunk.

// if mChunkSize is < 0 then this is the last chunk in the file and the actual length 
// should be determined from the file size. 
// The motivation for this is to allow writing the files without seeking to update size fields after every 
// write in order to keep the file legal.
// The program can put a -1 in the mChunkSize field and 
// update it only once at the end of recording. 
// If the program were to crash during recording then the file is still well defined.

// 'pakt' Required if either/or mBytesPerPacket or mFramesPerPacket in the Format Description are zero
// For formats that are packetized and have variable sized packets. 
// The table is stored as an array of one or two variable length integers. 
// (a) size in bytes of the data of a given packet.
// (b) number of frames in a given packet.
// These sizes are encoded as variable length integers

// The packet description entries are either one or two values depending on the format.
// There are three possibilities
// (1)
// If the format has variable bytes per packets (desc.mBytesPerPacket == 0) and constant frames per packet
// (desc.mFramesPerPacket != 0) then the packet table contains single entries representing the bytes in a given packet
// (2)
// If the format is a constant bit rate (desc.mBytesPerPacket != 0) but variable frames per packet
// (desc.mFramesPerPacket == 0) then the packet table entries contains single entries 
// representing the number of frames in a given packet
// (3)
// If the format has variable frames per packet (asbd.mFramesPerPacket == 0) and variable bytes per packet
// (desc.mBytesPerPacket == 0) then the packet table entries are a duple of two values. The first value
// is the number of bytes in a given packet, the second value is the number of frames in a given packet

struct CAFPacketTableHeader
{
        SInt64  mNumberPackets;
        SInt64  mNumberValidFrames;
        SInt32  mPrimingFrames;
        SInt32  mRemainderFrames;
		
		UInt8   mPacketDescriptions[kVariableLengthArray];
};
typedef struct CAFPacketTableHeader CAFPacketTableHeader;

struct CAFDataChunk
{
		UInt32 mEditCount;
		UInt8 mData[kVariableLengthArray];
};
typedef struct CAFDataChunk CAFDataChunk;

// markers types
enum {
	kCAFMarkerType_Generic					= 0,
	kCAFMarkerType_ProgramStart				= 'pbeg',
	kCAFMarkerType_ProgramEnd				= 'pend',
	kCAFMarkerType_TrackStart				= 'tbeg',
	kCAFMarkerType_TrackEnd					= 'tend',
	kCAFMarkerType_Index					= 'indx',
	kCAFMarkerType_RegionStart				= 'rbeg',
	kCAFMarkerType_RegionEnd				= 'rend',
	kCAFMarkerType_RegionSyncPoint			= 'rsyc',
	kCAFMarkerType_SelectionStart			= 'sbeg',
	kCAFMarkerType_SelectionEnd				= 'send',
	kCAFMarkerType_EditSourceBegin			= 'cbeg',
	kCAFMarkerType_EditSourceEnd			= 'cend',
	kCAFMarkerType_EditDestinationBegin		= 'dbeg',
	kCAFMarkerType_EditDestinationEnd		= 'dend',
	kCAFMarkerType_SustainLoopStart			= 'slbg',
	kCAFMarkerType_SustainLoopEnd			= 'slen',
	kCAFMarkerType_ReleaseLoopStart			= 'rlbg',
	kCAFMarkerType_ReleaseLoopEnd			= 'rlen',
	kCAFMarkerType_SavedPlayPosition		= 'sply'
};

enum
{
        kCAF_SMPTE_TimeTypeNone		 = 0,
        kCAF_SMPTE_TimeType24        = 1,
        kCAF_SMPTE_TimeType25        = 2,
        kCAF_SMPTE_TimeType30Drop    = 3,
        kCAF_SMPTE_TimeType30        = 4,
        kCAF_SMPTE_TimeType2997      = 5,
        kCAF_SMPTE_TimeType2997Drop  = 6,
        kCAF_SMPTE_TimeType60        = 7,
        kCAF_SMPTE_TimeType5994      = 8
};

struct CAF_SMPTE_Time
{
	SInt8 mHours;
	SInt8 mMinutes;
	SInt8 mSeconds;
	SInt8 mFrames;
	UInt32 mSubFrameSampleOffset;
};
typedef struct CAF_SMPTE_Time CAF_SMPTE_Time;

struct CAFMarker
{
        UInt32               mType;
        Float64              mFramePosition;
        UInt32               mMarkerID;
        CAF_SMPTE_Time       mSMPTETime;
        UInt32               mChannel;
};
typedef struct CAFMarker CAFMarker;

struct CAFMarkerChunk
{
        UInt32          mSMPTE_TimeType;
        UInt32          mNumberMarkers;
        CAFMarker       mMarkers[kVariableLengthArray]; 
};
typedef struct CAFMarkerChunk CAFMarkerChunk;

#define kCAFMarkerChunkHdrSize		offsetof(CAFMarkerChunk, mMarkers)

enum {
	kCAFRegionFlag_LoopEnable = 1,
	kCAFRegionFlag_PlayForward = 2,
	kCAFRegionFlag_PlayBackward = 4
};

struct CAFRegion
{
        UInt32          mRegionID;               
        UInt32          mFlags;
        UInt32          mNumberMarkers;
        CAFMarker       mMarkers[kVariableLengthArray];
};
typedef struct CAFRegion CAFRegion;

/* because AudioFileRegions are variable length, you cannot access them as an array. Use NextAudioFileRegion to walk the list. */
#define NextCAFRegion(inCAFRegionPtr) \
        ((CAFRegion*)((char*)(inCAFRegionPtr) + offsetof(CAFRegion, mMarkers) + ((inCAFRegionPtr)->mNumberMarkers)*sizeof(CAFMarker)))


struct CAFRegionChunk
{
        UInt32          mSMPTE_TimeType;
        UInt32          mNumberRegions;
        CAFRegion       mRegions[kVariableLengthArray];  //variable sized chunk
};
typedef struct CAFRegionChunk CAFRegionChunk;

#define kCAFRegionChunkHdrSize		offsetof(CAFRegionChunk, mRegions)

struct CAFInstrumentChunk
{
        Float32         mBaseNote;
        UInt8           mMIDILowNote;
        UInt8           mMIDIHighNote;
        UInt8           mMIDILowVelocity;
        UInt8           mMIDIHighVelocity;
        Float32         mdBGain;
        UInt32          mStartRegionID;               
        UInt32          mSustainRegionID;               
        UInt32          mReleaseRegionID;               
        UInt32          mInstrumentID;
};
typedef struct CAFInstrumentChunk CAFInstrumentChunk;



struct CAFStringID {
        UInt32         mStringID;
        SInt64         mStringStartByteOffset;
};
typedef struct CAFStringID CAFStringID;

struct CAFStrings
{
        UInt32         mNumEntries;
		CAFStringID    mStringsIDs[kVariableLengthArray];
// this struct is only fictionally described due to the variable length fields
//		UInt8          mStrings[kVariableLengthArray]; // null terminated UTF8 strings
};
typedef struct CAFStrings CAFStrings;


struct CAFInfoStrings
{
        UInt32		mNumEntries;

// These are only fictionally defined in the struct due to the variable length fields.
//      struct {
//              UInt8   mKey[kVariableLengthArray];			// null terminated UTF8 string
//              UInt8   mValue[kVariableLengthArray];		// null terminated UTF8 string
//      } mStrings[kVariableLengthArray];
};
typedef struct CAFInfoStrings CAFInfoStrings;


struct CAFPositionPeak
{
        Float32       mValue;
        UInt64        mFrameNumber;
};
typedef struct CAFPositionPeak CAFPositionPeak;

struct CAFPeakChunk
{
	UInt32 mEditCount;
	CAFPositionPeak mPeaks[kVariableLengthArray];
};
typedef struct CAFPeakChunk CAFPeakChunk;


struct CAFOverviewSample
{
        SInt16       mMinValue;
        SInt16       mMaxValue;
};
typedef struct CAFOverviewSample CAFOverviewSample;

struct CAFOverviewChunk
{
        UInt32                   mEditCount;
        UInt32                   mNumFramesPerOVWSample;
        CAFOverviewSample        mData[kVariableLengthArray];
};
typedef struct CAFOverview CAFOverview;

struct CAFUMIDChunk
{
	UInt8 mBytes[64];
};
typedef struct CAFUMIDChunk CAFUMIDChunk;


////////////////////////////////////////////////////////////////////////////////////////////////

#endif
