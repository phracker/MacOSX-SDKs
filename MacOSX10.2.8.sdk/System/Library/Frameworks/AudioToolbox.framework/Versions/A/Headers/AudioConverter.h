/*
     File:       AudioToolbox/AudioConverter.h

     Contains:   API for translating between audio data formats.

     Version:    Technology: Mac OS X
                 Release:    Mac OS X

     Copyright:  (c) 1985-2001 by Apple Computer, Inc., all rights reserved.

     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:

                     http://developer.apple.com/bugreporter/

*/
#if !defined(__AudioConverter_h__)
#define __AudioConverter_h__

//=============================================================================
//	Includes
//=============================================================================

#include <CoreAudio/CoreAudioTypes.h>

#if defined(__cplusplus)
extern "C"
{
#endif

//=============================================================================
//	Theory of Operation
//=============================================================================

//=============================================================================
//	Types specific to the Audio Converter API
//=============================================================================

typedef struct OpaqueAudioConverter *	AudioConverterRef;
typedef UInt32							AudioConverterPropertyID;

//=============================================================================
//	Standard Properties
//=============================================================================

enum
{
	kAudioConverterPropertyMinimumInputBufferSize		= 'mibs',
		//	a UInt32 that indicates the size in bytes of the smallest
		//	buffer of input data that can be supplied via the
		//	AudioConverterInputProc or as the input to
		//	AudioConverterConvertBuffer
		
	kAudioConverterPropertyMinimumOutputBufferSize		= 'mobs',
		//	a UInt32 that indicates the size in bytes of the smallest
		//	buffer of output data that can be supplied to
		//	AudioConverterFillBuffer or as the output to
		//	AudioConverterConvertBuffer
		
	kAudioConverterPropertyMaximumInputBufferSize		= 'xibs',
		//	a UInt32 that indicates the size in bytes of the largest
		//	buffer of input data that will be requested from the AudioConverterInputProc.
		// This is mostly useful for variable bit rate compressed data.
		// This will be equal to 0xFFFFFFFF if the maximum value depends on what 
		// is requested from the output, which is usually the case for constant bit rate formats.
		
	kAudioConverterPropertyMaximumInputPacketSize		= 'xips',
		//	a UInt32 that indicates the size in bytes of the largest
		//	single packet of data in the input format.
		// This is mostly useful for variable bit rate compressed data (decoders).
		
	kAudioConverterPropertyMaximumOutputPacketSize		= 'xops',
		//	a UInt32 that indicates the size in bytes of the largest
		//	single packet of data in the output format.
		// This is mostly useful for variable bit rate compressed data (encoders).
		
	kAudioConverterPropertyCalculateInputBufferSize		= 'cibs',
		//	a UInt32 that on input holds a size in bytes
		//	that is desired for the output data. On output,
		//	it will hold the size in bytes of the input buffer
		//	required to generate that much output data. Note
		//	that some converters cannot do this calculation.
		
	kAudioConverterPropertyCalculateOutputBufferSize	= 'cobs',
		//	a UInt32 that on input holds a size in bytes
		//	that is desired for the input data. On output,
		//	it will hold the size in bytes of the output buffer
		//	required to hold the output data that will be generated.
		//	Note that some converters cannot do this calculation.
		
	kAudioConverterPropertyInputCodecParameters			= 'icdp',
		//	The value of this property varies from format to format
		//	and is considered private to the format. It is treated
		//	as a buffer of untyped data.
		
	kAudioConverterPropertyOutputCodecParameters		= 'ocdp',
		//	The value of this property varies from format to format
		//	and is considered private to the format. It is treated
		//	as a buffer of untyped data.
		
	kAudioConverterSampleRateConverterAlgorithm			= 'srci',
		// DEPRECATED : please use kAudioConverterSampleRateConverterQuality instead
		//
		//	An OSType that specifies the sample rate converter to use
		//	(as defined in AudioUnit/AudioUnitProperties.h -- for now only Apple SRC's can be used)

	kAudioConverterSampleRateConverterQuality			= 'srcq',
		//	A UInt32 that specifies rendering quality of the sample rate converter
		//  (see enum constants below)

	kAudioConverterCodecQuality							= 'cdqu',
		//	A UInt32 that specifies rendering quality of a codec
		//  (see enum constants below)

	kAudioConverterPrimeMethod							= 'prmm',
		// a UInt32 specifying priming method (usually for sample-rate converter)
		// see explanation for struct AudioConverterPrimeInfo below
		// along with enum constants

	kAudioConverterPrimeInfo							= 'prim',
		//  A pointer to AudioConverterPrimeInfo (see explanation for struct AudioConverterPrimeInfo below)

	kAudioConverterChannelMap							= 'chmp',
		// An array of SInt32's.  The size of the array is the number of output
		// channels, and each element specifies which input channel's
		// data is routed to that output channel (using a 0-based index
		// of the input channels), or -1 if no input channel is to be
		// routed to that output channel.  The default behavior is as follows.
		// I = number of input channels, O = number of output channels.
		// When I > O, the first O inputs are routed to the first O outputs,
		// and the remaining puts discarded.  When O > I, the first I inputs are 
		// routed to the first O outputs, and the remaining outputs are zeroed.

	kAudioConverterDecompressionMagicCookie				= 'dmgc',
		// A void * pointing to memory set up by the caller. Required by some
        // formats in order to decompress the input data.

	kAudioConverterCompressionMagicCookie				= 'cmgc',
		// A void * pointing to memory set up by the caller. Returned by the 
        // converter so that it may be stored along with the output data.
        // It can then be passed back to the converter for decompression
        // at a later time.

	kAudioConverterEncodeBitRate						= 'brat',
		//	A UInt32 containing the number of bits per second to aim
		//	for when encoding data. This property is only relevant to
		//	encoders.

	kAudioConverterEncodeAdjustableSampleRate			= 'ajsr',
		//	For encoders where the AudioConverter was created with an output sample rate of zero, 
		//  and the codec can do rate conversion on its input, this provides a way to set the output sample rate.
		//	The property value is a Float64

	kAudioConverterInputChannelLayout					= 'icl ',
		//  The property value is an AudioChannelLayout.	

	kAudioConverterOutputChannelLayout					= 'ocl ',
		//  The property value is an AudioChannelLayout.	

	kAudioConverterApplicableEncodeBitRates				= 'aebr',
		//  The property value is an array of AudioValueRange describing applicable bit rates based on current settings.
	
	kAudioConverterAvailableEncodeBitRates				= 'vebr',
		//  The property value is an array of AudioValueRange describing available bit rates based on the input format.
		//  You can get all available bit rates from the AudioFormat API.
	
	kAudioConverterApplicableEncodeSampleRates			= 'aesr',
		//  The property value is an array of AudioValueRange describing applicable sample rates based on current settings.

	kAudioConverterAvailableEncodeSampleRates			= 'vesr',
		//  The property value is an array of AudioValueRange describing available sample rates based on the input format.
		//  You can get all available sample rates from the AudioFormat API.
	
	kAudioConverterAvailableEncodeChannelLayoutTags		= 'aecl',
		//  The property value is an array of AudioChannelLayoutTags for the format and number of
		//  channels specified in the input format going to the encoder. 
				
	kAudioConverterCurrentOutputStreamDescription		= 'acod',
		// Returns the current completely specified output AudioStreamBasicDescription.
		// For example when encoding to AAC, your original output stream description will not have been 
		// completely filled out.
	
	kAudioConverterCurrentInputStreamDescription		= 'acid'
		// Returns the current completely specified input AudioStreamBasicDescription.

};

// constants to be used with kAudioConverterSampleRateConverterQuality
enum {
	kAudioConverterQuality_Max								= 0x7F,
	kAudioConverterQuality_High								= 0x60,
	kAudioConverterQuality_Medium							= 0x40,
	kAudioConverterQuality_Low								= 0x20,
	kAudioConverterQuality_Min								= 0
};


		
// constants to be used with kAudioConverterPrimeMethod
enum
{
	kConverterPrimeMethod_Pre 		= 0,	// primes with leading + trailing input frames
	kConverterPrimeMethod_Normal 	= 1,	// only primes with trailing (zero latency)
											// leading frames are assumed to be silence
	kConverterPrimeMethod_None 		= 2		// acts in "latency" mode
											// both leading and trailing frames assumed to be silence
};

// Priming method and AudioConverterPrimeInfo
//
//  When using AudioConverterFillBuffer() (either single call or series of calls),
//  some conversions (particularly involving sample-rate conversion)
//  ideally require a certain number of input frames previous to the normal
//  start input frame and beyond the end of the last expected input frame
//  in order to yield high-quality results.
//
//	leadingFrames
//		specifies the number of leading (previous) input frames
//		(relative to the normal/desired start input frame) required by the converter
//		to perform a high quality conversion.
//		If using kConverterPrimeMethod_Pre the client should "pre-seek"
//		the input stream provided through the input proc by "leadingFrames"
//		If no frames are available previous to the desired input start frame
//		(because, for example, the desired start frame is at the very beginning
//		of available audio) then provide "leadingFrames" worth of initial zero frames
//		in the input proc.  Do not "pre-seek" in the default case of kConverterPrimeMethod_Normal
//		or when using kConverterPrimeMethod_None.
//		 
//
//	trailingFrames
//		specifies the number of trailing input frames
//		(past the normal/expected end input frame) required by the converter
//		to perform a high quality conversion.  The client should be prepared
//		to provide this number of additional input frames except when using
//		kConverterPrimeMethod_None.
//		If no more frames of input are available in the input stream
//		(because, for example, the desired end frame is at the end of an audio file),
//		then zero (silent) trailing frames will be synthesized for the client. 
//
//	The very first call to AudioConverterFillBuffer() or first call after AudioConverterReset()
//	will request additional input frames approximately equal to:
//			kConverterPrimeMethod_Pre		: leadingFrames + trailingFrames
//			kConverterPrimeMethod_Normal	: trailingFrames
//			kConverterPrimeMethod_None		: 0
//	beyond that normally expected in the input proc callback(s) to fullfil
//	this first AudioConverterFillBuffer() request.  Thus, in effect, the first input proc
//	callback(s) may provide not only the leading frames, but also may "read ahead"
//	by an additional number of trailing frames depending on the prime method.
//	kConverterPrimeMethod_None is useful in a real-time application processing
//	live input, in which case trailingFrames (relative to input sample rate) 
//	of through latency will be seen at the beginning of the output of the AudioConverter.  In other
//	real-time applications such as DAW systems, it may be possible to provide these initial extra
//	audio frames since they are stored on disk or in memory somewhere and kConverterPrimeMethod_Pre
//  may be preferable.  The default method is kConverterPrimeMethod_Normal, which requires no
//  pre-seeking of the input stream and generates no latency at the output.
//	
typedef struct AudioConverterPrimeInfo {
	UInt32		leadingFrames;
	UInt32		trailingFrames;
} AudioConverterPrimeInfo;

//=============================================================================
//	Errors
//=============================================================================

enum {
	kAudioConverterErr_FormatNotSupported		= 'fmt?',
	kAudioConverterErr_OperationNotSupported	= 0x6F703F3F, // 'op??', integer used because of trigraph
	kAudioConverterErr_PropertyNotSupported		= 'prop',
	kAudioConverterErr_InvalidInputSize			= 'insz',
	kAudioConverterErr_InvalidOutputSize		= 'otsz',
		// e.g. byte size is not a multiple of the frame size
	kAudioConverterErr_UnspecifiedError			= 'what',
	kAudioConverterErr_BadPropertySizeError		= '!siz',
	kAudioConverterErr_RequiresPacketDescriptionsError = '!pkd',
	kAudioConverterErr_InputSampleRateOutOfRange	= '!isr',
	kAudioConverterErr_OutputSampleRateOutOfRange	= '!osr'
};

//=============================================================================
//	Routines
//=============================================================================

//-----------------------------------------------------------------------------
//	AudioConverterNew
//
//	This routine is called to create a new AudioConverter.
//-----------------------------------------------------------------------------

extern OSStatus
AudioConverterNew(		const AudioStreamBasicDescription*	inSourceFormat,
						const AudioStreamBasicDescription*	inDestinationFormat,
						AudioConverterRef*					outAudioConverter);

//-----------------------------------------------------------------------------
//	AudioConverterDispose
//
//	This routine is called to destroy an AudioConverter.
//-----------------------------------------------------------------------------

extern OSStatus
AudioConverterDispose(AudioConverterRef	inAudioConverter);

//-----------------------------------------------------------------------------
//	AudioConverterReset
//-----------------------------------------------------------------------------

extern OSStatus
AudioConverterReset(AudioConverterRef	inAudioConverter);

//-----------------------------------------------------------------------------
//	AudioConverterGetPropertyInfo
//-----------------------------------------------------------------------------

extern OSStatus
AudioConverterGetPropertyInfo(	AudioConverterRef			inAudioConverter,
								AudioConverterPropertyID	inPropertyID,
								UInt32*						outSize,
								Boolean*					outWritable);

//-----------------------------------------------------------------------------
//	AudioConverterGetProperty
//-----------------------------------------------------------------------------

extern OSStatus
AudioConverterGetProperty(	AudioConverterRef			inAudioConverter,
							AudioConverterPropertyID	inPropertyID,
							UInt32*						ioPropertyDataSize,
							void*						outPropertyData);

//-----------------------------------------------------------------------------
//	AudioConverterSetProperty
//-----------------------------------------------------------------------------

extern OSStatus
AudioConverterSetProperty(	AudioConverterRef			inAudioConverter,
							AudioConverterPropertyID	inPropertyID,
							UInt32						inPropertyDataSize,
							const void*					inPropertyData);

//-----------------------------------------------------------------------------
//	AudioConverterDataProc
//		ioDataSize: on input, the minimum amount of data the converter would
//		like in order to fulfill its current FillBuffer request.  On output,
//		the number of bytes actually being provided for input, or 0 if there
//		is no more input.
//-----------------------------------------------------------------------------

typedef OSStatus
(*AudioConverterInputDataProc)(	AudioConverterRef			inAudioConverter,
								UInt32*						ioDataSize,
								void**						outData,
								void*						inUserData);

//-----------------------------------------------------------------------------
//	AudioConverterFillBuffer
//-----------------------------------------------------------------------------

extern OSStatus
AudioConverterFillBuffer(	AudioConverterRef				inAudioConverter,
							AudioConverterInputDataProc		inInputDataProc,
							void*							inInputDataProcUserData,
							UInt32*							ioOutputDataSize,
							void*							outOutputData);

//-----------------------------------------------------------------------------
//	AudioConverterConvertBuffer
//-----------------------------------------------------------------------------

extern OSStatus
AudioConverterConvertBuffer(	AudioConverterRef				inAudioConverter,
								UInt32							inInputDataSize,
								void*							inInputData,
								UInt32*							ioOutputDataSize,
								void*							outOutputData);

//-----------------------------------------------------------------------------
//	AudioConverterComplexInputDataProc
//
//	ioData - provided by the converter, must be filled out by the callback
//-----------------------------------------------------------------------------

typedef OSStatus
(*AudioConverterComplexInputDataProc)(	AudioConverterRef				inAudioConverter,
										UInt32*							ioNumberDataPackets,
										AudioBufferList*				ioData,
										AudioStreamPacketDescription**	outDataPacketDescription,
										void*							inUserData);

//-----------------------------------------------------------------------------
//	AudioConverterFillComplexBuffer
//-----------------------------------------------------------------------------

extern OSStatus
AudioConverterFillComplexBuffer(	AudioConverterRef					inAudioConverter,
									AudioConverterComplexInputDataProc	inInputDataProc,
									void*								inInputDataProcUserData,
									UInt32*								ioOutputDataPacketSize,
									AudioBufferList*					outOutputData,
									AudioStreamPacketDescription*		outPacketDescription);

#if defined(__cplusplus)
}
#endif

#endif
