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
		
	kAudioConverterPropertyCalculateInputBufferSize		= 'cibs',
		//	a UInt32 that on input holds a size in bytes
		//	that is desired for the output data. On output,
		//	it will hold the size in bytes of the input buffer
		//	requried to generate that much output data. Note
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
		//	An OSType that specifies the sample rate converter to use
		//	(as defined in AudioUnit/AudioUnitProperties.h -- for now only Apple SRC's can be used)

	kAudioConverterChannelMap							= 'chmp'
		// An array of SInt32's used when the number of input and output
		// channels differ.  The size of the array is the number of output
		// channels, and each element specifies which input channel's
		// data is routed to that output channel (using a 0-based index
		// of the input channels), or -1 if no input channel is to be
		// routed to that output channel.  The default behavior is as follows.
		// I = number of input channels, O = number of output channels.
		// When I > O, the first O inputs are routed to the first O outputs,
		// and the remaining puts discarded.  When O > I, the first I inputs are 
		// routed to the first O outputs, and the remaining outputs are zeroed.
};

//=============================================================================
//	Errors
//=============================================================================

enum {
	kAudioConverterErr_FormatNotSupported		= 'fmt?',
	kAudioConverterErr_OperationNotSupported	= 'op??',
	kAudioConverterErr_PropertyNotSupported		= 'prop',
	kAudioConverterErr_InvalidInputSize			= 'insz',
	kAudioConverterErr_InvalidOutputSize		= 'otsz'
		// e.g. byte size is not a multiple of the frame size
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
							void*						inPropertyData);

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

#if defined(__cplusplus)
}
#endif

#endif
