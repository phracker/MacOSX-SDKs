/*
	File:  VTErrors.h
	
	Framework:  VideoToolbox
 
    Copyright 2006-2012 Apple Inc. All rights reserved.
  
*/

#ifndef VTERRORS_H
#define VTERRORS_H

#include <CoreMedia/CMBase.h>

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)

// Error codes
enum {
	kVTPropertyNotSupportedErr				= -12900,
	kVTPropertyReadOnlyErr					= -12901,
	kVTParameterErr							= -12902,
	kVTInvalidSessionErr					= -12903,
	kVTAllocationFailedErr					= -12904,
	kVTPixelTransferNotSupportedErr			= -12905, // c.f. -8961
	kVTCouldNotFindVideoDecoderErr			= -12906,
	kVTCouldNotCreateInstanceErr			= -12907,
	kVTCouldNotFindVideoEncoderErr			= -12908,
	kVTVideoDecoderBadDataErr				= -12909, // c.f. -8969
	kVTVideoDecoderUnsupportedDataFormatErr	= -12910, // c.f. -8970
	kVTVideoDecoderMalfunctionErr			= -12911, // c.f. -8960
	kVTVideoEncoderMalfunctionErr			= -12912,
	kVTVideoDecoderNotAvailableNowErr		= -12913,
	kVTImageRotationNotSupportedErr			= -12914,
	kVTVideoEncoderNotAvailableNowErr		= -12915,
	kVTFormatDescriptionChangeNotSupportedErr	= -12916,
	kVTInsufficientSourceColorDataErr		= -12917,
	kVTCouldNotCreateColorCorrectionDataErr	= -12918,
	kVTColorSyncTransformConvertFailedErr	= -12919,
	kVTVideoDecoderAuthorizationErr			= -12210,
	kVTVideoEncoderAuthorizationErr			= -12211,
	kVTColorCorrectionPixelTransferFailedErr	= -12212,
};

// Directives to decompression session and decoder
typedef uint32_t VTDecodeFrameFlags;
enum {
	kVTDecodeFrame_EnableAsynchronousDecompression = 1<<0,
	kVTDecodeFrame_DoNotOutputFrame = 1<<1,
	kVTDecodeFrame_1xRealTimePlayback = 1<<2, // A hint to the video decoder that it would be OK to use a low-power mode that can not decode faster than 1x realtime.
	kVTDecodeFrame_EnableTemporalProcessing = 1<<3, // allows video decoder to delay output of decoded frames so as to enable postprocessing of frames in temporal order; may be necessary to call VTDecompressionSessionFinishDelayedFrames to get them all out
};

// Informational status for decoding -- non-error flags 
typedef UInt32 VTDecodeInfoFlags;
enum {
	kVTDecodeInfo_Asynchronous = 1UL << 0,
	kVTDecodeInfo_FrameDropped = 1UL << 1,
};

// Informational status for encoding -- non-error flags 
typedef UInt32 VTEncodeInfoFlags;
enum {
	kVTEncodeInfo_Asynchronous = 1UL << 0,
	kVTEncodeInfo_FrameDropped = 1UL << 1,
};

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // VTERRORS_H
