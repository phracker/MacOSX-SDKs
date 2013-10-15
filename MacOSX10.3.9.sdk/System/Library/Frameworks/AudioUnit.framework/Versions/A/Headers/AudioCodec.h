/*
     File:       AudioUnit/AudioCodec.h

     Contains:   A component API for encoding/decoding audio data.

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 1985-2002 by Apple Computer, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

*/
#if !defined(__AudioCodec_h__)
#define __AudioCodec_h__

//=============================================================================
//	Includes
//=============================================================================

#include <TargetConditionals.h>
#include <AvailabilityMacros.h>

#if !defined(__COREAUDIO_USE_FLAT_INCLUDES__)
	#include <CoreServices/CoreServices.h>
	#include <CoreAudio/CoreAudioTypes.h>
#else
	#include "Components.h"
	#include "CoreAudioTypes.h"
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

//=============================================================================
//	Theory of Operation
//
//	AudioCodec components translate audio data from one format to another. There
//	are three kinds of AudioCodec components. Decoder components translate data
//	that isn't in linear PCM into linear PCM formatted data. Encoder components
//	translate linear PCM data into some other format. Unity codecs translates
//	between different flavors of the same type (for instance 16 bit signed
//	integer linear PCM into 32 bit floating point linear PCM).
//
//	<how to find AudioCodecs yet to be determined>
//
//	Once an AudioCodec is found that implements the translation in question,
//	it has to be set up to do the translation. This can be done by setting the
//	appropriate properties or by calling AudioCodecInitialize. If the translation
//	is specified by properties, AudioCodecInitialize still needs to be called
//	prior to appending input data or producing output data.
//
//	AudioCodecInitialize puts the codec into the "initialized" state. In this state,
//	the format information for the translation cannot be changed. The codec
//	has to be in the initialized state for AudioCodecAppendInputData and
//	AudioCodecProduceOutputData to work. They will return kAudioCodecStateError
//	if the codec isn't initialized.
//
//	AudioCodecUninitialize will return the codec to the uninitialized state and
//	release any allocated resources. It may then be configured freely. It is not
//	necessary to call AudioCodecUninitialize prior to closing the codec.
//
//	Once in the initialized state, the codec is ready to receive input and produce
//	output using the AudioCodecAppendInputData and AudioCodecProduceOutputData
//	routines. Input data can be fed into a codec in any size (even byte by byte),
//	but output data can only be produced in whole packet sizes. Both routines
//	will return the amount of data they consume/produce.
//
//	AudioCodecProduceOutputData also returns a status code to the caller that
//	indicates the result of the operation (success or failure) as well as the
//	state of the input buffer.
//=============================================================================

//=============================================================================
//	Issues for Discussion
//
//	-	Finding these guys hasn't been addressed yet. When it is, one must
//		keep in mind the fact that multiple codecs may perform the same
//		translation so being able to differentiate between them by something
//		other than type and subtype is important.
//
//	-	Should there be standard properties for the important configuration
//		things, like bit rate, profile, etc. that aren't covered in an
//		AudioStreamBasicDescription? If so what are they and what do they
//		look like. If there were standard properties for this stuff, then
//		it would be possible to create a standard UI for the majority of
//		the codecs out there which would greatly simplify the process of
//		creating an AudioCodec component.
//
//	-	UI for configuring a codec. Because of the way things are layered
//		on X, it is highly desirable to not include any UI code in the
//		AudioCodec component. But, it is also desirable to allow the codec
//		the opportunity to present its own UI for configuration. In fact,
//		this is how QT works with codecs now. AudioUnits have the exact same
//		problem, so likely the solution here is similar to the solution
//		being worked on for AudioUnits.
//
//	-	
//=============================================================================

//=============================================================================
//	Types specific to AudioCodecs
//=============================================================================

typedef ComponentInstance	AudioCodec;
typedef UInt32				AudioCodecPropertyID;

struct AudioStreamLoudnessStatistics
{
	Float64	mAveragePerceivedPowerCoefficient;		//	normalized from 0-1
	Float64	mMaximumPerceivedPowerCoefficient;		//	normalized from 0-1
	UInt64	mMaximumPerceivedPowerPacketOffset;		//	the packet that contains the maximum coefficient
	Float32	mPeakAmplitude;							//	the absolute peak sample value
	UInt32	mReserved;								//	padding
	UInt64	mPeakAmplitudeSampleOffset;				//	the sample number of the absolute peak sample
};
typedef struct AudioStreamLoudnessStatistics	AudioStreamLoudnessStatistics;

//=============================================================================
//	AudioCodec Component Constants
//=============================================================================

enum
{

	kAudioDecoderComponentType								= 'adec',
		//	A codec that translates data in some other format into linear PCM
		//	The component subtype specifies the format ID of the other format
	
	kAudioEncoderComponentType								= 'aenc',
		//	A codec that translates linear PCM data into some other format
		//	The component subtype specifies the format ID of the other format
	
	kAudioUnityCodecComponentType							= 'acdc'
		//	A codec that translates between different flavors of the same format
		//	The component subtype specifies the format ID of this format.

};

//=============================================================================
//	Standard Codec Properties
//
//	Used with the AudioCodecXXXXPropertyXXXX family of routines.
//=============================================================================

enum
{

	kAudioCodecPropertyNameCFString							= 'lnam',
		//	the name of the codec component as a CFStringRef. The CFStringRef
		//	retrieved via this property must be released by the caller.
		
	kAudioCodecPropertyManufacturerCFString					= 'lmak',
		//	the manufacturer of the codec as a CFStringRef. The CFStringRef 
		//	retrieved via this property must be released by the caller.
	
	kAudioCodecPropertyFormatCFString						= 'lfor',
		//	the name of the codec's format as a CFStringRef. The CFStringRef
		//	retrieved via this property must be released by the caller.
		
	kAudioCodecPropertyRequiresPacketDescription			= 'pakd',
		//	A UInt32 where a non-zero value indicates that the format the codec implements
		//	requires that an AudioStreamPacketDescription array must be supplied with any data
		//	in that format. Note that this implies that data must also be handled strictly in
		//	packets. For a decoder, this applies to input data. For an encoder, it applies to
		//	output data.
		
	kAudioCodecPropertyPacketFrameSize						= 'pakf',
		//	A UInt32 indicating the number of frames of audio data in each
		//	packet of data in the codec's format will be. For encoders, this is the
		//	input format. For decoders this is the output format.
		//	Note that this property can only be queried when the codec is initialized.
	
	kAudioCodecPropertyHasVariablePacketByteSizes			= 'vpk?',
		//	A UInt32 where 0 indicates that all packets in the codec's format
		//	have the same byte size and 1 indicates that they vary in size (up
		//	to the maximum size indicated in kAudioCodecPropertyMaximumPacketByteSize).
	
	kAudioCodecPropertyMaximumPacketByteSize				= 'pakb',
		//	A UInt32 indicating the maximum number of bytes a packet of data
		//	in the codec's format will be. If the format is constant bit rate,
		//	all packets will be this size. If it is variable bit rate, the packets
		//	won't ever be any larger than this size.
		//	This always refers to the encoded data, so for encoders it refers to the
		//	output data and for decoders the input data.
		//	Note that this property can only be queried when the codec is initialized.
	
	kAudioCodecPropertyCurrentInputFormat					= 'ifmt',
		//	An AudioStreamBasicDescription describing the format the codec
		//	expects its input data in
	
	kAudioCodecPropertySupportedInputFormats				= 'ifm#',
		//	An array of AudioStreamBasicDescription structs describing what formats 
		//	the codec supports for input data
	
	kAudioCodecPropertyCurrentOutputFormat					= 'ofmt',
		//	An AudioStreamBasicDescription describing the format the codec
		//	provides its output data in
	
	kAudioCodecPropertySupportedOutputFormats				= 'ofm#',
		//	An array of AudioStreamBasicDescription structs describing what formats 
		//	the codec supports for output data
	
	kAudioCodecPropertyMagicCookie							= 'kuki',
		//	An untyped buffer of out of band configuration data the codec
		//	requires to process the stream of data correctly. The contents
		//	of this data is private to the codec. Not all codecs have magic
		//	cookies.
	
	kAudioCodecPropertyInputBufferSize						= 'tbuf',
		//	A UInt32 indicating the maximum input buffering size for the codec
		//	in bytes
	
	kAudioCodecPropertyUsedInputBufferSize					= 'ubuf',
		//	A UInt32 indicating the number of bytes in the codec's input
		//	buffer that are already in use
	
	kAudioCodecPropertyIsInitialized						= 'init',
		//	A UInt32 where 0 means the codec is uninitialized and anything
		//	else means the codec is initialized.
	
	kAudioCodecPropertyCurrentTargetBitRate					= 'brat',
		//	A UInt32 containing the number of bits per second to aim
		//	for when encoding data. This property is only relevant to
		//	encoders.

	kAudioCodecPropertyAvailableBitRates					= 'brt#',
		//	An array of UInt32 that indicates the target bit rates
		//	supported by the encoder. This property is only relevant to
		//	encoders.
		//	Deprecated. Replaced with kAudioCodecPropertyAvailableBitRateRange

  	kAudioCodecPropertyCurrentInputSampleRate				= 'cisr',
		//	A Float64 containing current input sample rate in Hz.
		
  	kAudioCodecPropertyCurrentOutputSampleRate				= 'cosr',
		//	A Float64 containing current output sample rate in Hz.
		
	kAudioCodecPropertyAvailableInputSampleRates			= 'aisr',
		//	An array of AudioValueRange indicating the valid ranges for the
		//	input sample rate of the codec.
      
	kAudioCodecPropertyAvailableOutputSampleRates			= 'aosr',
		//	An array of AudioValueRange indicating the valid ranges for the
		//	output sample rate of the codec.

	kAudioCodecPropertyQualitySetting						= 'srcq',
		//	"Some Relative Codec Quality"
		//
		//	A UInt32 that specifies the relative quality of a codec.
		//	(see enum constants below)

	kAudioCodecPropertyCurrentLoudnessStatistics 			= 'loud',
		//	An array of AudioStreamLoudnessStatistics structs that provides statistics about
		//	the loudness of each channel in the stream of data being processed by the codec.
		//	Note that this property can only be queried when the codec is initialized
		//	and until data is actually moved through it the values will all be defaults.

	kAudioCodecPropertyAvailableBitRateRange				= 'abrt',
		//	An array of AudioValueRange that indicate the target bit rates
		//	supported by the encoder. 
		//	This property is only relevant to encoders.

	kAudioCodecPropertyApplicableBitRateRange				= 'brta',
		//	An array of AudioValueRange indicating the target bit rates
		//	supported by the encoder in its current configuration. 
		//	This property is only relevant to encoders.

	kAudioCodecPropertyApplicableInputSampleRates			= 'isra',
		//	An array of AudioValueRange indicating the valid ranges for the
		//	input sample rate of the codec for the current bit rate. 

	kAudioCodecPropertyApplicableOutputSampleRates			= 'osra',
		//	An array of AudioValueRange indicating the valid ranges for the
		//	output sample rate of the codec for the current bit rate. 

	kAudioCodecPropertyMinimumNumberInputPackets			= 'mnip',
		//	A UInt32 indicating the minimum number of input packets
		//	that need to be supplied to the codec. The actual input the
		//	codec accepts could be less than this.
		//	For most codecs this value will be 1.

	kAudioCodecPropertyMinimumNumberOutputPackets			= 'mnop',
		//	A UInt32 indicating the minimum number of output packets
		//	that need to be handled from the codec. The actual output
		//	might be less than this.
		//	For most codecs this value will be 1.

	kAudioCodecPropertyZeroFramesPadded						= 'pad0',
		//	A UInt32 indicating the number of zeroes (samples) that were appended
		//	to the last packet of input data to make a complete packet encoding.

	kAudioCodecPropertyAvailableNumberChannels				= 'cmnc',
		//	An array of UInt32 that specifies the number of channels the codec is capable of encoding to.
		//	0xFFFFFFFF means any number of channels.

	kAudioCodecPropertyPrimeMethod							= 'prmm',
		//	A UInt32 specifying priming method.
		//	see explanation for struct AudioCodecPrimeInfo below along with enum constants

	kAudioCodecPropertyPrimeInfo							= 'prim',
		//	A pointer to AudioCodecPrimeInfo

	kAudioCodecDoesSampleRateConversion						= 'lmrc',
		//	A UInt32 indicating if the codec wants to do a sample rate conversion (if 
		//	necessary) because it can do it in a way that is meaningful for quality.
		//	Value is 1 if true, 0 otherwise.
		
	kAudioCodecPropertyInputChannelLayout					= 'icl ',
		//	An AudioChannelLayout that specifies the channel layout that the codec is using for input.
		//	Settable on encoders.
	
	kAudioCodecPropertyOutputChannelLayout					= 'ocl ',
		//	An AudioChannelLayout that specifies the channel layout that the codec is using for output.
		//	If settable on a encoder, it means the encoder can re-map channels

	kAudioCodecPropertyAvailableInputChannelLayouts			= 'aicl',
		//	An array of AudioChannelLayoutTag that specifies what channel layouts the codec is
		//	capable of using on input.

	kAudioCodecPropertyAvailableOutputChannelLayouts		= 'aocl',
		//	An array of AudioChannelLayoutTag that specifies what channel layouts the codec is
		//	capable of using on output.

	kAudioCodecPropertySettings								= 'acs ',
		//	A CFDictionaryRef that lists both the settable codec settings and their values.
	
	kAudioCodecBitRateFormat								= 'acbf',
		//	A UInt32 indicating what bit rate format an encoder will target, eg Constant Bit Rate
		//	(CBR), Average Bit Rate (ABR), or Variable Bit Rate (VBR). See the enums below.
		//	Only needs to be settable if the codec supports multiple bit rate strategies.
		
	kAudioCodecExtendFrequencies							= 'acef',
		//	A UInt32 indicating whether an encoder should extend its cutoff frequency
		//	if such an option exists. 0 == extended frequencies off, 1 == extended frequencies on
		//	eg some encoders normally cut off the signal at 16 kHz but can encode up to 20 kHz if 
		//	asked to
		
	kAudioCodecInputFormatsForOutputFormat					= 'if4o',
		//	An array of AudioStreamBasicDescription indicating what the codec supports
		//  for input data given an output format that's passed in as the first member of
		//	the array (and is overwritten on the reply). Always a subset of 
		//	kAudioCodecPropertySupportedInputFormats
		
	kAudioCodecOutputFormatsForInputFormat					= 'of4i',
		//	An array of AudioStreamBasicDescription indicating what the codec supports
		//	for output data given an input format that's passed in as the first member of
		//	the array (and is overwritten on the reply). Always a subset of 
		//	kAudioCodecPropertySupportedOutputFormats

	kAudioCodecUseRecommendedSampleRate						= 'ursr',
		//	For encoders that do sample rate conversion, a UInt32 indicating whether or
		//	not the encoder is using the recommended sample rate for the given input. 
		//	A value of 0 indicates it isn't, 1 indicates it is.
		
	kAudioCodecOutputPrecedence								= 'oppr'
		//	For encoders that do sample rate conversion, a UInt32 indicating whether the
		//	bitrate, sample rate, nor either have precedence of the other.
		//	See enum below
};

// constants to be used with kAudioCodecPropertyQualitySetting
enum
{
	kAudioCodecQuality_Max								= 0x7F,
	kAudioCodecQuality_High								= 0x60,
	kAudioCodecQuality_Medium							= 0x40,
	kAudioCodecQuality_Low								= 0x20,
	kAudioCodecQuality_Min								= 0
};

// constants to be used with kAudioCodecPrimeMethod
enum
{
	kAudioCodecPrimeMethod_Pre 		= 0,	// primes with leading + trailing input frames
	kAudioCodecPrimeMethod_Normal 	= 1,	// only primes with trailing (zero latency)
											// leading frames are assumed to be silence
	kAudioCodecPrimeMethod_None 	= 2		// acts in "latency" mode
											// both leading and trailing frames assumed to be silence
};

// constants to be used with kAudioCodecBitRateFormat
enum
{
	kAudioCodecBitRateFormat_CBR 	= 0,	// Every encoded frame is the same size
											// eg IMA, MACE, old MP3, most early audio codecs
	kAudioCodecBitRateFormat_ABR 	= 1,	// Encoder attempts to keep close to the given bit rate, can vary
											// eg modern MP3 CBR, AAC (anything that has a "minimum" frame size 
											// or implements a bit pool for "CBR")
	kAudioCodecBitRateFormat_VBR 	= 2		// Encoder varies frames size attempting to maintain constant quality
											// eg MP3 VBR (Xing), AAC VBR
};

// constants to be used with kAudioCodecOutputPrecedence
enum
{
	kAudioCodecOutputPrecedenceNone			= 0,	// Change in the bit rate or the sample rate are constrained by
													// the other value.
	kAudioCodecOutputPrecedenceBitRate		= 1,	// The bit rate may be changed freely, 
													// adjusting the sample rate if necessary
	kAudioCodecOutputPrecedenceSampleRate 	= 2		// The sample rate may be changed freely, 
													// adjusting the bit rate if necessary
};

typedef struct AudioCodecPrimeInfo 
{
	UInt32		leadingFrames;
	UInt32		trailingFrames;
} AudioCodecPrimeInfo;

//=============================================================================
// Constants for kAudioCodecPropertySettings
//=============================================================================

#define kAudioSettings_TopLevelKey		"name"
#define kAudioSettings_Version			"version"
#define kAudioSettings_Parameters 		"parameters"
#define kAudioSettings_SettingKey		"key"
#define kAudioSettings_SettingName 		"name"
#define kAudioSettings_ValueType 		"value type"
#define kAudioSettings_AvailableValues	"available values"
#define kAudioSettings_LimitedValues	"limited values"
#define kAudioSettings_CurrentValue 	"current value"
#define kAudioSettings_Summary 			"summary"
#define kAudioSettings_Hint 			"hint"
#define kAudioSettings_Unit 			"unit" // kHz, kbps, etc.

// constants to be used with kAudioSettings_Hint (deprecated, use kAudioSettingsFlags_XX below)
enum
{
	kHintBasic		= 0,
	kHintAdvanced	= 1,
	kHintHidden		= 2
};

// constants to be used with kAudioSettings_Hint
enum {
	kAudioSettingsFlags_ExpertParameter = (1L << 0),
		// If set, then the parameter is an expert parameter.
	kAudioSettingsFlags_InvisibleParameter = (1L << 1),
		// If set, then the parameter should not be displayed.
	kAudioSettingsFlags_MetaParameter = (1L << 2),
		// If set, then changing this parameter may affect the values of other parameters. 
		// If not set, then this parameter can be set without affecting the values of other parameters.
	kAudioSettingsFlags_UserInterfaceParameter = (1L << 3)
		// If set, then this is only a user interface element and not reflected in the codec's bit stream.
};
	
//=============================================================================
//	Status values returned from the AudioCodecProduceOutputPacket routine
//=============================================================================

enum
{

	kAudioCodecProduceOutputPacketFailure					= 1,
		//	Couldn't complete the request due to an error. It is possible
		//	that some output data was produced. This is reflected in the value
		//	returned in ioNumberPackets.
		
	kAudioCodecProduceOutputPacketSuccess					= 2,
		//	The number of requested output packets was produced without incident
		//	and there isn't any more input data to process
	
	kAudioCodecProduceOutputPacketSuccessHasMore			= 3,
		//	The number of requested output packets was produced and there is
		//	enough input data to produce at least one more packet of output data
		
	kAudioCodecProduceOutputPacketNeedsMoreInputData		= 4,
		//	There was insufficient input data to produce the requested
		//	number of output packets, The value returned in ioNumberPackets
		//	holds the number of output packets produced.
		
	kAudioCodecProduceOutputPacketAtEOF						= 5
		//	The end-of-file marker was hit during the processing. Fewer
		//	than the requested number of output packets may have been
		//	produced. Check the value returned in ioNumberPackets for the
		//	actual number produced. Note that not all formats have EOF
		//	markers in them.
		
};

//=============================================================================
//	Selectors for the component routines (preliminary)
//=============================================================================

enum
{

	kAudioCodecGetPropertyInfoSelect						= 0x0001,
	kAudioCodecGetPropertySelect							= 0x0002,
	kAudioCodecSetPropertySelect							= 0x0003,
	kAudioCodecInitializeSelect								= 0x0004,
	kAudioCodecUninitializeSelect							= 0x0005,
	kAudioCodecAppendInputDataSelect						= 0x0006,
	kAudioCodecProduceOutputDataSelect						= 0x0007,
	kAudioCodecResetSelect									= 0x0008
	
};

//=============================================================================
//	Errors
//=============================================================================

enum
{
	kAudioCodecNoError								= 0,
	kAudioCodecUnspecifiedError						= 'what',
	kAudioCodecUnknownPropertyError					= 'who?',
	kAudioCodecBadPropertySizeError					= '!siz',
	kAudioCodecIllegalOperationError				= 'nope',
	kAudioCodecUnsupportedFormatError				= '!dat',
	kAudioCodecStateError							= '!stt',
	kAudioCodecNotEnoughBufferSpaceError			= '!buf'
};

//=============================================================================
//	Codec Property Management
//=============================================================================

//-----------------------------------------------------------------------------
//	AudioCodecGetPropertyInfo
//
//	Retrieve information about the given property. The outSize argument
//	will return the size in bytes of the current value of the property.
//	The outWritable argument will return whether or not the property
//	in question can be changed.
//-----------------------------------------------------------------------------
	
EXTERN_API(ComponentResult)
AudioCodecGetPropertyInfo(	AudioCodec				inCodec,
							AudioCodecPropertyID	inPropertyID,
							UInt32*					outSize,
							Boolean*				outWritable)		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

//-----------------------------------------------------------------------------
//	AudioCodecGetProperty
//
//	Retrieve the indicated property data. On input, ioDataSize has the size
//	of the data pointed to by outPropertyData. On output, ioDataSize will contain
//	the amount written.
//-----------------------------------------------------------------------------
	
EXTERN_API(ComponentResult)
AudioCodecGetProperty(	AudioCodec				inCodec,
						AudioCodecPropertyID	inPropertyID,
						UInt32*					ioPropertyDataSize,
						void*					outPropertyData)		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

//-----------------------------------------------------------------------------
//	AudioCodecSetProperty
//
//	Set the indicated property data.
//-----------------------------------------------------------------------------
	
EXTERN_API(ComponentResult)
AudioCodecSetProperty(	AudioCodec				inCodec,
						AudioCodecPropertyID	inPropertyID,
						UInt32					inPropertyDataSize,
						const void*				inPropertyData)			AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

//=============================================================================
//	Codec Data Handling Routines
//=============================================================================

//-----------------------------------------------------------------------------
//	AudioCodecInitialize
//
//	This call will allocate any buffers needed and otherwise set the codec
//	up to perform the indicated translation. If an argument is NULL, any
//	previously set properties will be used for preparing the codec for work.
//	Note that this routine will also validate the format information as useable.
//-----------------------------------------------------------------------------
	
EXTERN_API(ComponentResult)
AudioCodecInitialize(	AudioCodec							inCodec,
						const AudioStreamBasicDescription*	inInputFormat,
						const AudioStreamBasicDescription*	inOutputFormat,
						const void*							inMagicCookie,
						UInt32								inMagicCookieByteSize)
																		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

//-----------------------------------------------------------------------------
//	AudioCodecUninitialize
//
//	This call will move the codec from the initialized state back to the
//	uninitialized state. The codec will release any resources it allocated
//	or claimed in AudioCodecInitialize.
//-----------------------------------------------------------------------------
	
EXTERN_API(ComponentResult)
AudioCodecUninitialize(AudioCodec inCodec)								AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

//-----------------------------------------------------------------------------
//	AudioCodecAppendInputData
//
//	Append as much of the given data to the codec's input buffer as possible
//	and return in ioInputDataByteSize the amount of data used. Note that the
//	data is copied from the input buffer to the codec's internal buffers.
//	
//	The inPacketDescription argument is an array of AudioStreamPacketDescription
//	structs that describes the packet layout returned in outOutputData. The number
//	of elements in this array is indicated on input by ioNumberPackets.
//
//	Note that inPacketDescription and ioNumberPackets need only be filled out
//	if the value of kAudioCodecPropertyRequiresPacketDescription is non-zero.
//	Note also in this case that it is an error to supply less than a full packet
//	of data at a time.
//-----------------------------------------------------------------------------
	
EXTERN_API(ComponentResult)
AudioCodecAppendInputData(	AudioCodec							inCodec,
							const void*							inInputData,
							UInt32*								ioInputDataByteSize,
							UInt32*								ioNumberPackets,
							const AudioStreamPacketDescription*	inPacketDescription)
																		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

//-----------------------------------------------------------------------------
//	AudioCodecProduceOutputPackets
//
//	Produce as many output packets as requested and the amount of input data
//	allows for. The outStatus argument returns information about the codec's
//	status to allow for proper data management. See the constants above for
//	the possible values that can be returned.
//	
//	The outPacketDescription argument is an array of AudioStreamPacketDescription
//	structs that describes the packet layout returned in outOutputData. This
//	argument is optional. Pass NULL if this information is not to be returned.
//	Note that this information is only provided when the output format isn't
//	linear PCM.
//
//	Note that decoders will always only produce linear PCM data in multiples of
//	the number frames in a packet of the encoded format (as returned by
//	kAudioCodecPropertyPacketFrameSize). Encoders will consume this many frames
//	of linear PCM data to produce a packet of their format. 
//-----------------------------------------------------------------------------
	
EXTERN_API(ComponentResult)
AudioCodecProduceOutputPackets(	AudioCodec						inCodec,
								void*							outOutputData,
								UInt32*							ioOutputDataByteSize,
								UInt32*							ioNumberPackets,
								AudioStreamPacketDescription*	outPacketDescription,
								UInt32*							outStatus)
																		AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

//-----------------------------------------------------------------------------
//	AudioCodecReset
//
//	Flushes all the data in the codec and clears the input buffer. Note that
//	the formats, and magic cookie will be retained so they won't need to be
//	set up again to decode the same data.
//-----------------------------------------------------------------------------
	
EXTERN_API(ComponentResult)
AudioCodecReset(AudioCodec inCodec)										AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;

#if defined(__cplusplus)
}
#endif

#endif
