//--------------------------------------------------------------------------------
//
//	File:		AppleFWAudioUserClientCommon.h
//
//	Contains:	A common file to keep the API in sync with the User and Kernel side of the code
//
//	Technology:	OS X
//
//	DRI:		Matthew Xavier Mora	mxmora@apple.com
//	ALTERNATE:	
//
//--------------------------------------------------------------------------------

#ifndef _AppleFWAudioUserClientCommon_H
#define _AppleFWAudioUserClientCommon_H

#define kMIDIInputClientBufferSize 		(4 * 32)
#define kMIDIOutputClientBufferSize 	(4 * 32)
#define kMIDIInputRingBufferSize 		(1 * 1024)
#define kMIDIOutputRingBufferSize		(1 * 1024) 

#define NOTIFYON 1

enum 
{
	kMIDIStreamOut = 0,
	kMIDIStreamIn = 1
};

typedef struct FWAMIDIReadBuffer
{
	unsigned long			bufSize;
	unsigned long 			mrBuf[kMIDIInputClientBufferSize];	

} FWAMIDIReadBuf;


const unsigned long kFWADeviceStatusCurrentVersion = 0x00010000;

typedef struct FWADeviceStatus
{
	unsigned long				version;	
	unsigned long				sampleCounter;
	unsigned long				inputSampleFrame;
	unsigned long				outputSampleFrame;
	unsigned long				inputClipSampleFrame;
	unsigned long				outputClipSampleFrame;
	unsigned long 			meterData[1];	//numInputChannels + numInputChannels
} FWADeviceStatusRec, *FWADeviceStatusRecPtr;

enum
{
	kFWAudioMaxNameSize = 64,

	kReadBlockInParamCount = 3,
	kReadBlockOutParamCount = 0xFFFFFFFF,
	
	kWriteQuadletInParamCount = 3,
	kWriteQuadletOutParamCount = 0,
	
	kWriteBlockInParamCount = 4,
	kWriteBlockOutParamCount = 0,
	
	kReadQuadletInParamCount = 2,
	kReadQuadletOutParamCount = 1,
	
	kGetCycleTimeOffsetInParamCount = 0,
	kGetCycleTimeOffsetOutParamCount = 1,

	kSetCycleTimeOffsetInParamCount = 1,
	kSetCycleTimeOffsetOutParamCount = 0,
	
	kGetDeviceNameInParamCount	= 0,
	kGetDeviceNameOutParamCount = 0xFFFFFFFF,

	kGetVendorNameInParamCount = 0,
	kGetVendorNameOutParamCount = 0xFFFFFFFF,
	
	kIsMIDICapableInParamCount = 0,
	kIsMIDICapableOutParamCount = 1,
	
	kGetNumMIDIInputPlugsInParamCount = 0,
	kGetNumMIDIInputPlugsOutParamCount = 1,

	kGetNumMIDIOutputPlugsInParamCount = 0,
	kGetNumMIDIOutputPlugsOutParamCount = 1,

	kSetNumMIDIInputPlugsInParamCount = 1,
	kSetNumMIDIInputPlugsOutParamCount = 0,

	kSetNumMIDIOutputPlugsInParamCount = 1,
	kSetNumMIDIOutputPlugsOutParamCount = 0,

	kGetNumAudioInputPlugsInParamCount = 0,
	kGetNumAudioInputPlugsOutParamCount = 1,

	kGetNumAudioOutputPlugsInParamCount = 0,
	kGetNumAudioOutputPlugsOutParamCount = 1,

	kCreateAudioStreamInParamCount = 1,
	kCreateAudioStreamOutParamCount = 2,	
	
	kDisposeAudioStreamInParamCount = 1,
	kDisposeAudioStreamOutParamCount = 0,	
		
	kGetDeviceSampleRateInParamCount = 0,
	kGetDeviceSampleRateOutParamCount = 1,
	
	kGetDeviceSendModeInParamCount = 0,
	kGetDeviceSendModeOutParamCount = 1,

	kGetDeviceStatusInParamCount = 1,
	kGetDeviceStatusOutParamCount = 0xFFFFFFFF,
	
	kGetDeviceStreamInfoInParamCount = 1,
	kGetDeviceStreamInfoOutParamCount = 4,
	
	kSetDeviceStreamInfoInParamCount = 6,
	kSetDeviceStreamInfoOutParamCount = 0,
};

// Index into our API
enum
{
	kFWAOpenIndex 			= 0, 
	kFWACloseIndex, 
	kFWAGetCycleTimeOffset,
	kFWASetCycleTimeOffset,
	kFWAGetNodeID,
	kFWAGetGUID,
	kFWAReadQuadlet,
	kFWAReadBlock,
	kFWAExecuteAVC,
	kFWAWriteQuadlet,
	kFWAWriteBlock,
	kFWAGetMacGUID,
	kFWACreateMIDIStream,
	kFWADisposeMIDIStream,
	kFWAWriteMIDIData,
	kFWAReadMIDIData,
	kFWAIsMIDICapable,
	kFWAGetVendorID,
	kFWAGetDeviceName,
	kFWAGetVendorName,
	kFWAGetNumMIDIInputPlugs,
	kFWAGetNumMIDIOutputPlugs,
	kFWASetNumMIDIInputPlugs,
	kFWASetNumMIDIOutputPlugs,
	kFWAGetNumAudioInputPlugs,
	kFWAGetNumAudioOutputPlugs,
	kFWACreateAudioStream,
	kFWADisposeAudioStream,
	kFWAGetDeviceSampleRate,
	kFWAGetDeviceSendMode,
	kFWAGetDeviceStatus,
	kFWAGetDeviceStreamInfo,
// V4   -----------------------

	kFWASetDeviceStreamInfo,

	//  -----------------------
	kFWANumberFWAMethods			// Keep kFWANumberFWAMethods last!!
};

// Index into our Async API
enum
{
	kFWASetAsyncPort			= 0,
	kWriteMIDIAsync,
	kReadMIDIAsync,
	//  -----------------------
	kFWANumberAsyncFWAMethods		// Keep kFWANumberAsyncFWAMethods last!!
};
		
#endif /*_AppleFWAudioUserClientCommon_H */
