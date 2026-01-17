/*
     File:       CoreAudio/CoreAudioTypes.h

     Contains:   definitions of basic types used in the Core Audio APIs

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 1985-2001 by Apple Computer, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

*/
#if !defined(__CoreAudioTypes_h__)
#define __CoreAudioTypes_h__

#if defined(__cplusplus)
extern "C"
{
#endif

//=============================================================================
//	Basic Types
//
//	The basic integer and floating point types are repeated here for
//	platform independance and to allow this file to be used in both
//	the open and closed source APIs without modification or polluting
//	either project.
//=============================================================================

//	from MacTypes.h
#if !defined(__MACTYPES__)

//	unsigned integer types
typedef unsigned char		UInt8;
typedef unsigned short		UInt16;
typedef unsigned long		UInt32;
typedef unsigned long long	UInt64;

//	signed integer types
typedef signed char			SInt8;
typedef signed short		SInt16;
typedef signed long			SInt32;
typedef signed long long	SInt64;

//	floating point types
typedef	float				Float32;
#if !TARGET_API_MAC_OS8
typedef double				Float64;
#else
typedef short double		Float64;
#endif

//	miscellaneous types
typedef SInt32				OSStatus;
typedef UInt8				Boolean;
typedef UInt8				Byte;
typedef SInt8				SignedByte;

#endif

#if !defined(NULL)
#define	NULL				0
#endif

//=============================================================================
//	Core Audio Types
//
//	These types are used in the various CoreAudio APIs.
//=============================================================================

//	This structure holds a pair of numbers representing a coninuous range
//	of some value.
struct AudioValueRange
{
	Float64	mMinimum;
	Float64	mMaximum;
};
typedef struct AudioValueRange	AudioValueRange;

//	This structure holds the buffers necessary for translation operations
struct AudioValueTranslation
{
	void*	mInputData;
	UInt32	mInputDataSize;
	void*	mOutputData;
	UInt32	mOutputDataSize;
};
typedef struct AudioValueTranslation	AudioValueTranslation;

//	The following two structures are used to wrap up buffers of audio data
//	when passing them around in API calls.
struct AudioBuffer
{
	UInt32	mNumberChannels;	//	number of interleaved channels in the buffer
	UInt32	mDataByteSize;		//	the size of the buffer pointed to by mData
	void*	mData;				//	the pointer to the buffer
};
typedef struct AudioBuffer	AudioBuffer;

struct AudioBufferList
{
	UInt32		mNumberBuffers;
	AudioBuffer	mBuffers[1];
};
typedef struct AudioBufferList	AudioBufferList;

//	This structure encapsulates all the information for describing
//	the basic properties of a stream of audio data. This structure
//	is sufficient to describe any constant bit rate format that 
//	has chanels that are the same size. Extensions are required
//	for variable bit rate data and for constant bit rate data where
//	the channels have unequal sizes. However, where applicable,
//	the appropriate fields will be filled out correctly for these
//	kinds of formats (the extra data is provided via separate
//	properties). In all fields, a value of 0 indicates that the
//	field is either unknown, not applicable or otherwise is
//	inapproprate for the format and should be ignored.
//
//	The extended description data, if applicable, is avaiable via
//	a property with the same ID as the format ID. The contents of
//	the data is specific to the format.
struct AudioStreamBasicDescription
{
	Float64	mSampleRate;		//	the native sample rate of the audio stream
	UInt32	mFormatID;			//	the specific encoding type of audio stream
	UInt32	mFormatFlags;		//	flags specific to each format
	UInt32	mBytesPerPacket;	//	the number of bytes in a packet
	UInt32	mFramesPerPacket;	//	the number of frames in each packet
	UInt32	mBytesPerFrame;		//	the number of bytes in a frame
	UInt32	mChannelsPerFrame;	//	the number of channels in each frame
	UInt32	mBitsPerChannel;	//	the number of bits in each channel
};
typedef struct AudioStreamBasicDescription	AudioStreamBasicDescription;

//	constants for use in AudioStreamBasicDescriptions
enum
{
	kAudioStreamAnyRate = 0
		//	the format can use any sample rate (usually because it does
		//	its own rate conversion). Note that this constant can only
		//	appear in listings of supported descriptions. It should never
		//	appear in the current description as a device must always
		//	have a "current" nominal sample rate.
};

//	Format IDs
enum
{
	kAudioFormatLinearPCM	= 'lpcm'
};

//	This flags are used in the mFormatFlags field of AudioStreamBasicDescription
//	for describing linear PCM data.
enum
{
	kLinearPCMFormatFlagIsFloat			= (1L << 0),	//	set for floating point, clear for integer
	kLinearPCMFormatFlagIsBigEndian		= (1L << 1),	//	set for big endian, clear for little
	kLinearPCMFormatFlagIsSignedInteger	= (1L << 2),	//	set for signed integer, clear for unsigned integer, only valid if kLinearPCMFormatFlagIsFloat is clear
	kLinearPCMFormatFlagIsPacked		= (1L << 3),	//	set if the sample bits are packed as closely together as possible, clear if they are high or low aligned within the channel
	kLinearPCMFormatFlagIsAlignedHigh	= (1L << 4)		//	set if the sample bits are placed into the high bits of the channel, clear for low bit placement, only valid if kLinearPCMFormatFlagIsPacked is clear
};

//	A struct for encapsulating a SMPTE time. The running rate should
//	be expressed in the AudioTimeStamp's mRateScalar field.
struct SMPTETime
{
	UInt64	mCounter;			//	total number of messages received
	UInt32	mType;				//	the SMPTE type (see constants)
	UInt32	mFlags;				//	flags indicating state (see constants
	SInt16	mHours;				//	number of hours in the full message
	SInt16	mMinutes;			//	number of minutes in the full message
	SInt16	mSeconds;			//	number of seconds in the full message
	SInt16	mFrames;			//	number of frames in the full message
};
typedef struct SMPTETime	SMPTETime;

//	constants describing SMPTE types (taken from the MTC spec)
enum
{
	kSMPTETimeType24		= 0,
	kSMPTETimeType25		= 1,
	kSMPTETimeType30Drop	= 2,
	kSMPTETimeType30		= 3,
	kSMPTETimeType2997		= 4,
	kSMPTETimeType2997Drop	= 5
};

//	flags describing a SMPTE time stamp
enum
{
	kSMPTETimeValid		= (1L << 0),	//	the full time is valid
	kSMPTETimeRunning	= (1L << 1)		//	time is running
};

//	A struct for encapsulating the parts of a time stamp. The flags
//	say which fields are valid.
struct AudioTimeStamp
{
	Float64			mSampleTime;	//	the absolute sample time
	UInt64			mHostTime;		//	the host's root timebase's time
	Float64			mRateScalar;	//	the system rate scalar
	UInt64			mWordClockTime;	//	the word clock time
	SMPTETime		mSMPTETime;		//	the SMPTE time
	UInt32			mFlags;			//	the flags indicate which fields are valid
};
typedef struct AudioTimeStamp	AudioTimeStamp;

//	flags for the AudioTimeStamp sturcture
enum
{
	kAudioTimeStampSampleTimeValid		= (1L << 0),
	kAudioTimeStampHostTimeValid		= (1L << 1),
	kAudioTimeStampRateScalarValid		= (1L << 2),
	kAudioTimeStampWordClockTimeValid	= (1L << 3),
	kAudioTimeStampSMPTETimeValid		= (1L << 4)
};

#if defined(__cplusplus)
}
#endif

#endif
