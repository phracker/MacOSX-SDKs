/*=============================================================================
     File:       CoreAudio/CoreAudioTypes.h

     Contains:   definitions of basic types used in the Core Audio APIs

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 1985-2003 by Apple Computer, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

=============================================================================*/
#if !defined(__CoreAudioTypes_h__)
#define __CoreAudioTypes_h__

//	TargetConditionals.h has the definitions of some basic platform constants
#include <TargetConditionals.h>

//	MacTypes.h has the definitions of basic types like UInt32 and Float64
#if	TARGET_OS_MAC && TARGET_RT_MAC_MACHO
	#include <CoreServices/../Frameworks/CarbonCore.framework/Headers/MacTypes.h>
#else
	#include <MacTypes.h>
#endif

#if PRAGMA_ENUM_ALWAYSINT
	#pragma enumsalwaysint off
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

//	This structure holds a pair of numbers representing a continuous range of values
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
//	inapproprate for the format and should be ignored. Note that
//	0 is still a valid value for most formats the mFormatFlags field.

// 	a Frame is one sample across all channels.
// 	in non-interleaved audio, the per frame fields identify one channel.
// 	in interleaved audio, the per frame fields identify the set of n channels.
// 	in uncompressed audio, a Packet is one frame, (FramesPerPacket == 1).
// 	in compressed audio, a Packet is an indivisible chunk of compressed data, 
// 	for example an AAC packet will contain 1024 sample frames
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
	UInt32	mReserved;			//	reserved, pads the structure out to force 8 byte alignment
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
	kAudioFormatLinearPCM			= 'lpcm',	//	linear PCM data, uses standard flags
	kAudioFormatAC3					= 'ac-3',	//	AC-3, has no flags
	kAudioFormat60958AC3			= 'cac3',	//	AC-3 packaged for transport over an IEC 60958 compliant digital audio interface, uses standard flags
	kAudioFormatMPEG				= 'mpeg',	//	MPEG-1 or MPEG-2, has no flags
	kAudioFormatAppleIMA4			= 'ima4',	//	Apple's implementation of IMA 4:1 ADPCM encoding, has no flags
	kAudioFormatMPEG4AAC			= 'aac ',	//	MPEG-4 AAC, the flags field contains the MPEG-4 audio object type constant indicating the specific kind of data
	kAudioFormatMPEG4CELP			= 'celp',	//	MPEG-4 CELP, the flags field contains the MPEG-4 audio object type constant indicating the specific kind of data
	kAudioFormatMPEG4HVXC			= 'hvxc',	//	MPEG-4 HVXC, the flags field contains the MPEG-4 audio object type constant indicating the specific kind of data
	kAudioFormatMPEG4TwinVQ			= 'twvq',	//	MPEG-4 TwinVQ, the flags field contains the MPEG-4 audio object type constant indicating the specific kind of data
	kAudioFormatMACE3				= 'MAC3', 	//	MACE 3:1
	kAudioFormatMACE6				= 'MAC6', 	//	MACE 6:1
	kAudioFormatULaw				= 'ulaw', 	//	µLaw 2:1
	kAudioFormatALaw				= 'alaw', 	//	aLaw 2:1
	kAudioFormatQDesign				= 'QDMC', 	//	QDesign music
	kAudioFormatQDesign2			= 'QDM2', 	//	QDesign2 music
	kAudioFormatQUALCOMM			= 'Qclp', 	//	QUALCOMM PureVoice
	kAudioFormatMPEGLayer3			= '.mp3', 	//	MPEG Layer 3, CBR & VBR (QT4.1 and later)
	kAudioFormatDVAudio				= 'dvca', 	//	DV Audio
	kAudioFormatVariableDurationDVAudio	= 'vdva', 	//	Variable Duration DV Audio

	kAudioFormatTimeCode			= 'time',	//	a stream of IOAudioTimeStamps that describe the timing of the audio data, the format flags are the same as the IOAudioTimeStamp flags, see <IOKit/audio/IOAudioTypes.h> for the definition of IOAudioTimeStamp
	kAudioFormatMIDIStream			= 'midi',	//	describes a stream that contains a MIDIPacketList. The Time Stamps associated in the MIDIPacketList are sample offsets in this stream. The Sample Rate is used to describe how time is passed in this kind of stream and an AudioUnit that receives or generates this stream can use this SampleRate, the number of frames it is rendering and the sample offsets within the MIDIPacketList to define the time for any MIDI event within this list.
	
	kAudioFormatParameterValueStream = 'apvs'	//  a format that describes a "side-chain" of Float32 data that can be fed or generated by an AudioUnit and is used to send a high density of parameter value control information. An AU will typically run a ParameterValueStream at either the sample rate of the AudioUnit's audio data, or some integer divisor of this (say a half or a third of the sample rate of the audio). The Sample Rate of the ASBD would describe this relationship
};

//	These flags are used in the mFormatFlags field of AudioStreamBasicDescription.

// Typically, when an ASBD is being used, the fields describe the complete layout of the sample data in the
// buffers that are represented by this description - where typically those buffers are represented by an
// AudioBuffer that is contained in an AudioBufferList

// However, when an ASBD has the kAudioFormatFlagIsNonInterleaved flag, the AudioBufferList has a different
// structure and semantic. In this case, the ASBD fields will describe the format of ONE of the AudioBuffers
// that are contained in the list, AND each AudioBuffer in the list is determined to have a single (mono) channel
// of audio data. Then, the ASBD's mChannelsPerFrame will indicate the total number of AudioBuffers that are 
// contained within the AudioBufferList - where each buffer contains one channel. This is used primarily with
// the AudioUnit (and AudioConverter) representation of this list - and typically won't be found in the AudioHardware usage of 
// this structure.
enum
{
	//	standard flags
	kAudioFormatFlagIsFloat						= (1L << 0),	//	set for floating point, clear for integer
	kAudioFormatFlagIsBigEndian					= (1L << 1),	//	set for big endian, clear for little
	kAudioFormatFlagIsSignedInteger				= (1L << 2),	//	set for signed integer, clear for unsigned integer, only valid if kAudioFormatFlagIsFloat is clear
	kAudioFormatFlagIsPacked					= (1L << 3),	//	set if the sample bits are packed as closely together as possible, clear if they are high or low aligned within the channel
	kAudioFormatFlagIsAlignedHigh				= (1L << 4),	//	set if the sample bits are placed into the high bits of the channel, clear for low bit placement, only valid if kAudioFormatFlagIsPacked is clear
	kAudioFormatFlagIsNonInterleaved			= (1L << 5),	//	set if the samples for each channel are located contiguously and the channels are layed out end to end, clear if the samples for each frame are layed out contiguously and the frames layed out end to end
	kAudioFormatFlagIsNonMixable				= (1L << 5),	//	set to indicate when a format is non-mixable
	kAudioFormatFlagsAreAllClear				= (1L << 31),	//	set if all the flags would be clear in order to preserve 0 as the wild card value

	//	linear PCM flags
	kLinearPCMFormatFlagIsFloat					= kAudioFormatFlagIsFloat,
	kLinearPCMFormatFlagIsBigEndian				= kAudioFormatFlagIsBigEndian,
	kLinearPCMFormatFlagIsSignedInteger			= kAudioFormatFlagIsSignedInteger,
	kLinearPCMFormatFlagIsPacked				= kAudioFormatFlagIsPacked,
	kLinearPCMFormatFlagIsAlignedHigh			= kAudioFormatFlagIsAlignedHigh,
	kLinearPCMFormatFlagIsNonInterleaved		= kAudioFormatFlagIsNonInterleaved,
	kLinearPCMFormatFlagIsNonMixable			= kAudioFormatFlagIsNonMixable,
	kLinearPCMFormatFlagsAreAllClear			= kAudioFormatFlagsAreAllClear
};

//	Some commonly used combinations of format flags
enum
{
#if	TARGET_RT_BIG_ENDIAN
	kAudioFormatFlagsNativeEndian		= kAudioFormatFlagIsBigEndian,
#else
	kAudioFormatFlagsNativeEndian		= 0,
#endif
	kAudioFormatFlagsNativeFloatPacked	= kAudioFormatFlagIsFloat | kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked
};

//	Routines for manipulating format flags
#define TestAudioFormatNativeEndian(f)	((f.mFormatID == kAudioFormatLinearPCM) && ((f.mFormatFlags & kAudioFormatFlagIsBigEndian) == kAudioFormatFlagsNativeEndian))
#if defined(__cplusplus)
	inline bool	IsAudioFormatNativeEndian(const AudioStreamBasicDescription& f) { return (f.mFormatID == kAudioFormatLinearPCM) && ((f.mFormatFlags & kAudioFormatFlagIsBigEndian) == kAudioFormatFlagsNativeEndian); }
#endif

//	This struct is used to describe the packet layout of stream data
//	where the size of each packet may not be the same or if there is
//	extraneous data between audio data packets.
struct	AudioStreamPacketDescription
{
	SInt64	mStartOffset;			// the number of bytes from the start of the buffer to the beginning of the packet
        UInt32	mVariableFramesInPacket;	// number of frames in the packet for variable frame formats. 
        // For formats with constant frames per packet such as MP3 or AAC, mVariableFramesInPacket must be set to zero.
	
        UInt32	mDataByteSize;			// the length of the packet in bytes
};
typedef struct AudioStreamPacketDescription	AudioStreamPacketDescription;

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
	UInt32			mReserved;		//	reserved, pads the structure out to force 8 byte alignment
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

//	Some commonly used combinations of timestamp flags
enum
{
	kAudioTimeStampSampleHostTimeValid	= (kAudioTimeStampSampleTimeValid | kAudioTimeStampHostTimeValid)
};


// AudioClassDescription is used to describe codecs installed on the system.
struct AudioClassDescription {
    OSType mType;
    OSType mSubType;
    OSType mManufacturer;
};
typedef struct AudioClassDescription AudioClassDescription;


//	typedefs used for describing channel layouts
typedef UInt32 AudioChannelLabel;
typedef UInt32 AudioChannelLayoutTag;

//	An AudioChannelDescription contains information describing a single channel	
struct AudioChannelDescription
{
	AudioChannelLabel   mChannelLabel;			//	see constants below
	UInt32   			mChannelFlags;			//	flags that control the interpretation of the coordinates, see constants below
	Float32  			mCoordinates[3];		//	coordinates that specify the precise location of a speaker
};
typedef struct AudioChannelDescription AudioChannelDescription;


// The AudioChannelLayout struct is used to specify channel layouts in files and hardware.
struct AudioChannelLayout
{
	AudioChannelLayoutTag		mChannelLayoutTag;			//	see constants below
	UInt32						mChannelBitmap;				//	if non zero, then represents a channel bitmap.
	UInt32  					mNumberChannelDescriptions;	//	the number of channel descriptions
	AudioChannelDescription		mChannelDescriptions[1];	//	actual dimension is mNumberChannelDescriptions
};
typedef struct AudioChannelLayout AudioChannelLayout;

// These are for use in the mChannelLabel field of struct AudioChannelDescription
enum 
{		
	// These channel labels attempt to list all labels in common use.
	// Due to the ambiguities in channel labeling by various groups, 
	// there may be some overlap or duplication in the labels below.
	// Use the label which most clearly describes what you mean.

	// WAVE files seem to follow the USB spec for the channel flags.
	// A channel map lets you put these channels in any order, however a WAVE file only supports 
	// labels 1-18 and if present, they must be in the order given below. 
	// The integer values for the labels below match the bit position of the label 
	// in the USB bitmap and thus also the WAVE file bitmap.
	
	kAudioChannelLabel_Unknown 					= 0xFFFFFFFF,	// unknown or unspecified other use
	kAudioChannelLabel_Unused 					= 0,			// channel is present, but has no intended use or destination
	kAudioChannelLabel_UseCoordinates 			= 100,			// channel is described by the mCoordinates fields.
	
	kAudioChannelLabel_Left 					= 1,
	kAudioChannelLabel_Right 					= 2,
	kAudioChannelLabel_Center 					= 3,
	kAudioChannelLabel_LFEScreen 				= 4,	
	kAudioChannelLabel_LeftSurround 			= 5,			// WAVE: "Back Left"
	kAudioChannelLabel_RightSurround 			= 6,			// WAVE: "Back Right"
	kAudioChannelLabel_LeftCenter 				= 7,
	kAudioChannelLabel_RightCenter 				= 8,
	kAudioChannelLabel_CenterSurround 			= 9,			// WAVE: "Back Center" or plain "Rear Surround"
	kAudioChannelLabel_LeftSurroundDirect 		= 10,			// WAVE: "Side Left"
	kAudioChannelLabel_RightSurroundDirect 		= 11,			// WAVE: "Side Right"
	kAudioChannelLabel_TopCenterSurround 		= 12,
	kAudioChannelLabel_VerticalHeightLeft 		= 13,			// WAVE: "Top Front Left"
	kAudioChannelLabel_VerticalHeightCenter 	= 14,			// WAVE: "Top Front Center"
	kAudioChannelLabel_VerticalHeightRight 		= 15,			// WAVE: "Top Front Right"

	kAudioChannelLabel_TopBackLeft 				= 16,		
	kAudioChannelLabel_TopBackCenter 			= 17,
	kAudioChannelLabel_TopBackRight 			= 18,

	kAudioChannelLabel_RearSurroundLeft 		= 33,
	kAudioChannelLabel_RearSurroundRight 		= 34,
	kAudioChannelLabel_LeftWide 				= 35,
	kAudioChannelLabel_RightWide 				= 36,
	kAudioChannelLabel_LFE2 					= 37,
	kAudioChannelLabel_LeftTotal			 	= 38,			// matrix encoded 4 channels
	kAudioChannelLabel_RightTotal		 		= 39,			// matrix encoded 4 channels
	kAudioChannelLabel_HearingImpaired 			= 40,
	kAudioChannelLabel_Narration 				= 41,
	kAudioChannelLabel_Mono 					= 42,		
	kAudioChannelLabel_DialogCentricMix 		= 43,
	
	kAudioChannelLabel_CenterSurroundDirect 	= 44,			// back center, non diffuse		
	
	// first order ambisonic channels
	kAudioChannelLabel_Ambisonic_W 				= 200,
	kAudioChannelLabel_Ambisonic_X 				= 201,
	kAudioChannelLabel_Ambisonic_Y 				= 202,
	kAudioChannelLabel_Ambisonic_Z 				= 203,

	// Mid/Side Recording
	kAudioChannelLabel_MS_Mid 					= 204, 
	kAudioChannelLabel_MS_Side 					= 205,

	// X-Y Recording
	kAudioChannelLabel_XY_X 					= 206, 
	kAudioChannelLabel_XY_Y 					= 207,

	// other
	kAudioChannelLabel_HeadphonesLeft 			= 301,
	kAudioChannelLabel_HeadphonesRight 			= 302,
	kAudioChannelLabel_ClickTrack 				= 304,
	kAudioChannelLabel_ForeignLanguage 			= 305,
	
	// generic discrete channel
	kAudioChannelLabel_Discrete					= 400,
	
	// numbered discrete channel
	kAudioChannelLabel_Discrete_0				= (1L<<16) | 0,
	kAudioChannelLabel_Discrete_1				= (1L<<16) | 1,
	kAudioChannelLabel_Discrete_2				= (1L<<16) | 2,
	kAudioChannelLabel_Discrete_3				= (1L<<16) | 3,
	kAudioChannelLabel_Discrete_4				= (1L<<16) | 4,
	kAudioChannelLabel_Discrete_5				= (1L<<16) | 5,
	kAudioChannelLabel_Discrete_6				= (1L<<16) | 6,
	kAudioChannelLabel_Discrete_7				= (1L<<16) | 7,
	kAudioChannelLabel_Discrete_8				= (1L<<16) | 8,
	kAudioChannelLabel_Discrete_9				= (1L<<16) | 9,
	kAudioChannelLabel_Discrete_10				= (1L<<16) | 10,
	kAudioChannelLabel_Discrete_11				= (1L<<16) | 11,
	kAudioChannelLabel_Discrete_12				= (1L<<16) | 12,
	kAudioChannelLabel_Discrete_13				= (1L<<16) | 13,
	kAudioChannelLabel_Discrete_14				= (1L<<16) | 14,
	kAudioChannelLabel_Discrete_15				= (1L<<16) | 15,
	kAudioChannelLabel_Discrete_65535			= (1L<<16) | 65535
	
};

// These are for use in the mChannelBitmap field of struct AudioChannelLayout
enum 
{
	kAudioChannelBit_Left 						= (1L<<0),
	kAudioChannelBit_Right 						= (1L<<1),
	kAudioChannelBit_Center 					= (1L<<2),
	kAudioChannelBit_LFEScreen 					= (1L<<3),	
	kAudioChannelBit_LeftSurround 				= (1L<<4),		// WAVE: "Back Left"
	kAudioChannelBit_RightSurround 				= (1L<<5),		// WAVE: "Back Right"
	kAudioChannelBit_LeftCenter 				= (1L<<6),
	kAudioChannelBit_RightCenter 				= (1L<<7),
	kAudioChannelBit_CenterSurround 			= (1L<<8),		// WAVE: "Back Center"
	kAudioChannelBit_LeftSurroundDirect			= (1L<<9),		// WAVE: "Side Left"
	kAudioChannelBit_RightSurroundDirect		= (1L<<10),		// WAVE: "Side Right"
	kAudioChannelBit_TopCenterSurround 			= (1L<<11),
	kAudioChannelBit_VerticalHeightLeft 		= (1L<<12),		// WAVE: "Top Front Left"
	kAudioChannelBit_VerticalHeightCenter 		= (1L<<13),		// WAVE: "Top Front Center"
	kAudioChannelBit_VerticalHeightRight 		= (1L<<14),		// WAVE: "Top Front Right"
	kAudioChannelBit_TopBackLeft 				= (1L<<15),		
	kAudioChannelBit_TopBackCenter 				= (1L<<16),
	kAudioChannelBit_TopBackRight 				= (1L<<17)
};

// these are used in the mChannelFlags field of struct AudioChannelDescription
enum 
{

	// Only one of the following two coordinate flags should be set. 
	// If neither is set, then there is no speaker coordinate info.
	
	kAudioChannelFlags_RectangularCoordinates 	= (1L<<0), 
		// channel is specified by cartesian coordinates of speaker position
	
	kAudioChannelFlags_SphericalCoordinates 	= (1L<<1), 
		// channel is specified by spherical coordinates of speaker position
	
	kAudioChannelFlags_Meters 					= (1L<<2)
		// If set, units are in meters. If unset, units are relative to the unit cube or sphere.
	
};

// these are indices for acessing the mCoordinates array in struct AudioChannelDescription
enum 
{
	// if kChannelFlags_RectangularCoordinates is set.
	kAudioChannelCoordinates_LeftRight 	= 0,	// negative left, positive right
	kAudioChannelCoordinates_BackFront 	= 1,	// negative back, positive front
	kAudioChannelCoordinates_DownUp    	= 2,	// negative below ground level, 0 = ground level, positive above ground level
	
	// if kChannelFlags_SphericalCoordinates is set. Coordinates specified as on a compass.
	kAudioChannelCoordinates_Azimuth   	= 0,	// in degrees. zero is front center, + is right, - is left.
	kAudioChannelCoordinates_Elevation 	= 1,	// in degrees. +90 is zenith, zero is horizontal, -90 is nadir.
	kAudioChannelCoordinates_Distance  	= 2 	// units defined by flags
};


// Some channel abbreviations used below:
// L - left 
// R - right
// C - center
// Ls - left surround
// Rs - right surround
// Cs - center surround
// Rls - rear left surround
// Rrs - rear right surround
// Lw - left wide
// Rw - right wide
// Lsd - left surround direct
// Rsd - right surround direct
// Lc - left center
// Rc - right center
// Ts - top surround
// Vhl - vertical height left
// Vhc - vertical height center
// Vhr - vertical height right
// Lt - left matrix total. for matrix encoded stereo.
// Rt - right matrix total. for matrix encoded stereo.


// The low 16 bits of the layout tag gives the number of channels. 
// AudioChannelLayoutTag_GetNumberOfChannels() is a macro to obtain the number of channels.
// EXCEPT FOR kAudioChannelLayoutTag_UseChannelDescriptions and kAudioChannelLayoutTag_UseChannelBitmap

#define AudioChannelLayoutTag_GetNumberOfChannels(layoutTag) ((UInt32)((layoutTag) & 0x0000FFFF))

// these are used in the mChannelLayoutTag field of struct AudioChannelLayout
enum 
{
	//	General layouts
	kAudioChannelLayoutTag_UseChannelDescriptions	= (0L<<16) | 0,	// use the array of AudioChannelDescriptions to define the mapping.
	kAudioChannelLayoutTag_UseChannelBitmap			= (1L<<16) | 0,	// use the bitmap to define the mapping.

	kAudioChannelLayoutTag_Mono						= (100L<<16) | 1,	// a standard mono stream
	kAudioChannelLayoutTag_Stereo					= (101L<<16) | 2,	// a standard stereo stream (L R) - implied playback
	kAudioChannelLayoutTag_StereoHeadphones			= (102L<<16) | 2,	// a standard stereo stream (L R) - implied headphone playbac
	kAudioChannelLayoutTag_MatrixStereo				= (103L<<16) | 2,	// a matrix encoded stereo stream (Lt, Rt)
	kAudioChannelLayoutTag_MidSide		 			= (104L<<16) | 2,	// mid/side recording
	kAudioChannelLayoutTag_XY			 			= (105L<<16) | 2,	// coincident mic pair (often 2 figure 8's)
	kAudioChannelLayoutTag_Binaural					= (106L<<16) | 2,	// binaural stereo (left, right)
	kAudioChannelLayoutTag_Ambisonic_B_Format 		= (107L<<16) | 4,	// W, X, Y, Z
	
	kAudioChannelLayoutTag_Quadraphonic 			= (108L<<16) | 4,	// front left, front right, back left, back right
	
	kAudioChannelLayoutTag_Pentagonal 				= (109L<<16) | 5,	// left, right, rear left, rear right, center
															
	kAudioChannelLayoutTag_Hexagonal 				= (110L<<16) | 6,	// left, right, rear left, rear right, center, rear
	
	kAudioChannelLayoutTag_Octagonal 				= (111L<<16) | 8,	// front left, front right, rear left, rear right, 
																		// front center, rear center, side left, side right
	
	kAudioChannelLayoutTag_Cube 					= (112L<<16) | 8,	// left, right, rear left, rear right
																		// top left, top right, top rear left, top rear right
	
	//	MPEG defined layouts
	kAudioChannelLayoutTag_MPEG_1_0					= kAudioChannelLayoutTag_Mono,	//	C
	kAudioChannelLayoutTag_MPEG_2_0					= kAudioChannelLayoutTag_Stereo,	//	L R
	kAudioChannelLayoutTag_MPEG_3_0_A				= (113L<<16) | 3,	//	L R C
	kAudioChannelLayoutTag_MPEG_3_0_B				= (114L<<16) | 3,	//	C L R
	kAudioChannelLayoutTag_MPEG_4_0_A				= (115L<<16) | 4,	//	L R C Cs
	kAudioChannelLayoutTag_MPEG_4_0_B				= (116L<<16) | 4,	//	C L R Cs
	kAudioChannelLayoutTag_MPEG_5_0_A				= (117L<<16) | 5,	//	L R C Ls Rs
	kAudioChannelLayoutTag_MPEG_5_0_B				= (118L<<16) | 5,	//	L R Ls Rs C
	kAudioChannelLayoutTag_MPEG_5_0_C				= (119L<<16) | 5,	//	L C R Ls Rs
	kAudioChannelLayoutTag_MPEG_5_0_D				= (120L<<16) | 5,	//	C L R Ls Rs
	kAudioChannelLayoutTag_MPEG_5_1_A				= (121L<<16) | 6,	//	L R C LFE Ls Rs
	kAudioChannelLayoutTag_MPEG_5_1_B				= (122L<<16) | 6,	//	L R Ls Rs C LFE
	kAudioChannelLayoutTag_MPEG_5_1_C				= (123L<<16) | 6,	//	L C R Ls Rs LFE
	kAudioChannelLayoutTag_MPEG_5_1_D				= (124L<<16) | 6,	//	C L R Ls Rs LFE
	kAudioChannelLayoutTag_MPEG_6_1_A				= (125L<<16) | 7,	//	L R C LFE Ls Rs Cs
	kAudioChannelLayoutTag_MPEG_7_1_A				= (126L<<16) | 8,	//	L R C LFE Ls Rs Lc Rc
	kAudioChannelLayoutTag_MPEG_7_1_B				= (127L<<16) | 8,	//	C Lc Rc L R Ls Rs LFE    (doc: IS-13818-7 MPEG2-AAC)
	kAudioChannelLayoutTag_MPEG_7_1_C				= (128L<<16) | 8,	//	L R C LFE Ls R Rls Rrs
	kAudioChannelLayoutTag_Emagic_Default_7_1		= (129L<<16) | 8,	//	L R Ls Rs C LFE Lc Rc
	kAudioChannelLayoutTag_SMPTE_DTV				= (130L<<16) | 8,	//	L R C LFE Ls Rs Lt Rt
												//		(kAudioChannelLayoutTag_ITU_5_1 plus a matrix encoded stereo mix)
															
	//	ITU defined layouts
	kAudioChannelLayoutTag_ITU_1_0					= kAudioChannelLayoutTag_Mono,		//	C 
	kAudioChannelLayoutTag_ITU_2_0					= kAudioChannelLayoutTag_Stereo,	//	L R 

	kAudioChannelLayoutTag_ITU_2_1					= (131L<<16) | 3,	//	L R Cs
	kAudioChannelLayoutTag_ITU_2_2					= (132L<<16) | 4,	//	L R Ls Rs
	kAudioChannelLayoutTag_ITU_3_0					= kAudioChannelLayoutTag_MPEG_3_0_A,	//	L R C
	kAudioChannelLayoutTag_ITU_3_1					= kAudioChannelLayoutTag_MPEG_4_0_A,	//	L R C Cs

	kAudioChannelLayoutTag_ITU_3_2					= kAudioChannelLayoutTag_MPEG_5_0_A,	//	L R C Ls Rs
	kAudioChannelLayoutTag_ITU_3_2_1				= kAudioChannelLayoutTag_MPEG_5_1_A,	//	L R C LFE Ls Rs
	kAudioChannelLayoutTag_ITU_3_4_1				= kAudioChannelLayoutTag_MPEG_7_1_C,	//	L R C LFE Ls Rs Rls Rrs
	
	// DVD defined layouts
	kAudioChannelLayoutTag_DVD_0					= kAudioChannelLayoutTag_Mono,		// C (mono)
	kAudioChannelLayoutTag_DVD_1					= kAudioChannelLayoutTag_Stereo,	// L R
	kAudioChannelLayoutTag_DVD_2					= kAudioChannelLayoutTag_ITU_2_1,	// L R Cs
	kAudioChannelLayoutTag_DVD_3					= kAudioChannelLayoutTag_ITU_2_2,	// L R Ls Rs
	kAudioChannelLayoutTag_DVD_4					= (133L<<16) | 3,	// L R LFE
	kAudioChannelLayoutTag_DVD_5					= (134L<<16) | 4,	// L R LFE Cs
	kAudioChannelLayoutTag_DVD_6					= (135L<<16) | 5,	// L R LFE Ls Rs
	kAudioChannelLayoutTag_DVD_7					= kAudioChannelLayoutTag_MPEG_3_0_A,	// L R C
	kAudioChannelLayoutTag_DVD_8					= kAudioChannelLayoutTag_MPEG_4_0_A,	// L R C Cs
	kAudioChannelLayoutTag_DVD_9					= kAudioChannelLayoutTag_MPEG_5_0_A,	// L R C Ls Rs
	kAudioChannelLayoutTag_DVD_10					= (136L<<16) | 4,	// L R C LFE
	kAudioChannelLayoutTag_DVD_11					= (137L<<16) | 5,	// L R C LFE Cs
	kAudioChannelLayoutTag_DVD_12					= kAudioChannelLayoutTag_MPEG_5_1_A,	// L R C LFE Ls Rs
	// 13 through 17 are duplicates of 8 through 12. 
	kAudioChannelLayoutTag_DVD_13					= kAudioChannelLayoutTag_DVD_8,		// L R C Cs
	kAudioChannelLayoutTag_DVD_14					= kAudioChannelLayoutTag_DVD_9,		// L R C Ls Rs
	kAudioChannelLayoutTag_DVD_15					= kAudioChannelLayoutTag_DVD_10,	// L R C LFE
	kAudioChannelLayoutTag_DVD_16					= kAudioChannelLayoutTag_DVD_11,	// L R C LFE Cs
	kAudioChannelLayoutTag_DVD_17					= kAudioChannelLayoutTag_DVD_12,	// L R C LFE Ls Rs
	kAudioChannelLayoutTag_DVD_18					= (138L<<16) | 5,	// L R Ls Rs LFE
	kAudioChannelLayoutTag_DVD_19					= kAudioChannelLayoutTag_MPEG_5_0_B,	// L R Ls Rs C
	kAudioChannelLayoutTag_DVD_20					= kAudioChannelLayoutTag_MPEG_5_1_B,	// L R Ls Rs C LFE
    
    // These layouts are recommended for AudioUnit usage
        // These are the symmetrical layouts
	kAudioChannelLayoutTag_AudioUnit_4				= kAudioChannelLayoutTag_Quadraphonic,
    kAudioChannelLayoutTag_AudioUnit_5				= kAudioChannelLayoutTag_Pentagonal,
    kAudioChannelLayoutTag_AudioUnit_6				= kAudioChannelLayoutTag_Hexagonal,
    kAudioChannelLayoutTag_AudioUnit_8				= kAudioChannelLayoutTag_Octagonal,
        // These are the surround-based layouts
    kAudioChannelLayoutTag_AudioUnit_5_0			= kAudioChannelLayoutTag_MPEG_5_0_B,	// L R Ls Rs C
	kAudioChannelLayoutTag_AudioUnit_6_0			= (139L<<16) | 6,	// L R Ls Rs C Cs
	kAudioChannelLayoutTag_AudioUnit_7_0			= (140L<<16) | 7,	// L R Ls Rs C Rls Rrs
	kAudioChannelLayoutTag_AudioUnit_5_1			= kAudioChannelLayoutTag_MPEG_5_1_A,	// L R C LFE Ls Rs 
	kAudioChannelLayoutTag_AudioUnit_6_1			= kAudioChannelLayoutTag_MPEG_6_1_A,	// L R C LFE Ls Rs Cs
	kAudioChannelLayoutTag_AudioUnit_7_1			= kAudioChannelLayoutTag_MPEG_7_1_C,		// L R C LFE Ls Rs Rls Rrs

	kAudioChannelLayoutTag_AAC_Quadraphonic 		= kAudioChannelLayoutTag_Quadraphonic,	// L R Ls Rs
	kAudioChannelLayoutTag_AAC_4_0 					= kAudioChannelLayoutTag_MPEG_4_0_B,	// C L R Cs	
	kAudioChannelLayoutTag_AAC_5_0					= kAudioChannelLayoutTag_MPEG_5_0_D, 	// C L R Ls Rs
	kAudioChannelLayoutTag_AAC_5_1  		 		= kAudioChannelLayoutTag_MPEG_5_1_D,	// C L R Ls Rs Lfe
	kAudioChannelLayoutTag_AAC_6_0 					= (141L<<16) | 6,						// C L R Ls Rs Cs				
	kAudioChannelLayoutTag_AAC_6_1					= (142L<<16) | 7,						// C L R Ls Rs Cs Lfe
	kAudioChannelLayoutTag_AAC_7_0 					= (143L<<16) | 7,						// C L R Ls Rs Rls Rrs			
	kAudioChannelLayoutTag_AAC_7_1  				= kAudioChannelLayoutTag_MPEG_7_1_B,	// C Lc Rc L R Ls Rs Lfe
	kAudioChannelLayoutTag_AAC_Octagonal  			= (144L<<16) | 8,						// C L R Ls Rs Rls Rrs Cs                            

	kAudioChannelLayoutTag_TMH_10_2_std  			= (145L<<16) | 16,	// L R C Vhc Lsd Rsd Ls Rs Vhl Vhr Lw Rw Csd Cs LFE1 LFE2                           
	kAudioChannelLayoutTag_TMH_10_2_full  			= (146L<<16) | 21	// TMH_10_2_std plus: Lc Rc HI VI Haptic                            
};

#if defined(__cplusplus)
}
#endif

#if PRAGMA_ENUM_ALWAYSINT
	#pragma enumsalwaysint reset
#endif

#endif
