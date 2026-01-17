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

#define kNumInputClientBuffers			1
#define kMIDIInputClientBufferSize 		(2 * 32)
#define kMIDIInputRingBufferSize 		(8 * kMIDIInputClientBufferSize * kNumInputClientBuffers )

#define kNumOutputClientBuffers			1
#define kMIDIOutputClientBufferSize 	(2 * 32)
#define kMIDIOutputRingBufferSize		(8 * kMIDIOutputClientBufferSize *  kNumOutputClientBuffers)

#define kFWAStreamIdentSize 			(36)
#define kFWAStreamEndpointIndentifier "kFWAudioStreamEndpointIdentifier"

enum {
	kCurrentEraseHeadMeterArrayOffset = 0,
	kNumSamplesFramesInBufferMeterArrayOffset = 1,
	kCurrentInputDMASampleFrameMeterArrayOffset = 2,
	kCurrentOutputDMASampleFrameMeterArrayOffset = 3,
	kGetBadHeaderCountMeterArrayOffset = 4,
	kGetFixedHeaderCountMeterArrayOffset = 5,
	kGetBigPacketCountMeterArrayOffset = 6,
	kLastTimeStampMeterArrayOffset = 7,
};


enum 
{
	kMIDIStreamOut = 0,
	kMIDIStreamIn = 1
};

enum FWAStreamDirection
{
	kFWAStreamOut		= 0x00000000UL,
	kFWAStreamIn		= 0x00000001UL
};

typedef enum FWAStreamDirection FWAStreamDirection;


typedef struct FWAMIDIReadBuffer
{
	unsigned long			bufSize;
	unsigned long 			mrBuf[kMIDIInputClientBufferSize];	

} FWAMIDIReadBuf;

enum FWAudioType
{
	kIEC60958		= 0x00,
	kRawAudio		= 0x40,
	kMIDI			= 0x80
};
typedef enum FWAudioType FWAudioType, *FWAudioTypePtr;

enum FWAMIDIDataInfo 
{
    kFWAMIDIPlugName		= 'mnam',
	kFWAMIDIPlugIdent		= 'midn',
	kFWAMIDIGetIndexedPlug 	= 0xFFFFFFFF,
};

enum FWAStreamState 
{
    kFWAStreamStopped	= 0,
    kFWAStreamRunning	= 1,
    kFWAStreamPaused	= 2,
    kFWAStreamResumed	= 3
};

typedef enum FWAStreamState FWAStreamState;
typedef void (*FWAStreamNotificationProc)( unsigned long isochStreamRef, void*  refCon);


// update this with the version of the driver in xxxx.xxxx
const unsigned long kFWADeviceStatusCurrentVersion = 0x00011100;

typedef struct FWADeviceStatus
{
	unsigned long	version;	
	unsigned long	sampleCounter;
	unsigned long	inputSampleFrame;
	unsigned long	outputSampleFrame;
	unsigned long	inputClipSampleFrame;
	unsigned long	outputClipSampleFrame;
	unsigned long	meterData[1];	//numInputChannels + numInputChannels
} FWADeviceStatusRec, *FWADeviceStatusRecPtr;

typedef struct FWACreateStreamRec
{
	unsigned long 	owningIsochStreamRef;
	unsigned long 	channelNumber;
	unsigned long 	direction;
	unsigned long 	numAudioChannels;
    char			streamName[64];
	unsigned char	streamIdent[kFWAStreamIdentSize];
	bool			streamIdentIsNull;
	
} FWACreateStreamRec, *FWACreateStreamRecPtr;

typedef struct FWACreateMIDIPlugRec
{
	unsigned long 	owningMIDIStreamRef;
	unsigned long 	mpxID;
    char			plugName[64];
	unsigned char	plugIdent[kFWAStreamIdentSize];
	bool			plugIdentIsNull;
} FWACreateMIDIPlugRec, *FWACreateMIDIPlugRecPtr;


typedef struct FWACreateDeviceRec
{
	unsigned long 	vendorID;
    char			deviceName[64];
	char			guidStr[64];

} FWACreateDeviceRec, *FWACreateDeviceRecPtr;

enum
{
	kFWAudioMaxNameSize = 64,

	kReadBlockInParamCount = 3,
	kReadBlockOutParamCount = 0xFFFFFFFF,
	
	kWriteQuadletInParamCount = 3,
	kWriteQuadletOutParamCount = 0,
	
	kWriteBlockInParamCount = 3,
	kWriteBlockOutParamCount = 0xFFFFFFFF,
	
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

	kCreateAudioStreamInParamCount = 0xFFFFFFFF,
	kCreateAudioStreamOutParamCount = 0xFFFFFFFF,	
	
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

// v4	
	kSetDeviceStreamInfoInParamCount = 6,
	kSetDeviceStreamInfoOutParamCount = 0,

// v5	

	kSyncUpDeviceInParamCount 						= 0,
	kSyncUpDeviceOutParamCount 						= 0,

	kGetCurrentStreamRefsInParamCount				= 1,	 
	kGetCurrentStreamRefsOutParamCount				= 0xFFFFFFFF,

	kGetStreamStateInParamCount						= 1,
	kGetStreamStateOutParamCount					= 1,

	kGetIsochStreamDirectionInParamCount			= 1,
	kGetIsochStreamDirectionOutParamCount			= 1,

	kGetIsochStreamChannelIDInParamCount			= 1,
	kGetIsochStreamChannelIDOutParamCount			= 1,

	kSetIsochStreamChannelIDInParamCount			= 2,
	kSetIsochStreamChannelIDOutParamCount			= 0,
	
	kGetStreamSampleRateInParamCount				= 1,
	kGetStreamSampleRateOutParamCount				= 1,

	kSetStreamSampleRateInParamCount				= 2,
	kSetStreamSampleRateOutParamCount				= 0,

	kGetStreamOutputSpeedInParamCount				= 1,
	kGetStreamOutputSpeedOutParamCount				= 1,

	kSetStreamOutputSpeedInParamCount				= 2,
	kSetStreamOutputSpeedOutParamCount				= 0,	

	kGetStreamAudioTypeInParamCount					= 1,
	kGetStreamAudioTypeOutParamCount				= 1,

	kSetStreamAudioTypeInParamCount					= 2, 
	kSetStreamAudioTypeOutParamCount				= 0,

	kSetStreamCallbackFunctionInParamCount			= 3,
	kSetStreamCallbackFunctionOutParamCount			= 0,

	kCreateIsochStreamInParamCount					= 4, 
	kCreateIsochStreamOutParamCount					= 1,

	kDisposeIsochStreamInParamCount					= 1,
	kDisposeIsochStreamOutParamCount				= 0,

	kStartIsochStreamInParamCount					= 1,
	kStartIsochStreamOutParamCount					= 0,

	kStopIsochStreamInParamCount 					= 1,
	kStopIsochStreamOutParamCount  					= 0,

	kGetIsochStreamAudioChannelCountInParamCount 	= 1,
	kGetIsochStreamAudioChannelCountOutParamCount 	= 1,

	kSetIsochStreamAudioChannelCountInParamCount 	= 2,
	kSetIsochStreamAudioChannelCountOutParamCount 	= 0,

	kGetIsochStreamMIDIChannelCountInParamCount 	= 1,
	kGetIsochStreamMIDIChannelCountOutParamCount 	= 1,

	kSetIsochStreamMIDIChannelCountInParamCount 	= 2,
	kSetIsochStreamMIDIChannelCountOutParamCount 	= 0,
	
	kCreateFWAudioDeviceInParamCount 				= 0xFFFFFFFF,
	kCreateFWAudioDeviceOutParamCount 				= 0xFFFFFFFF,
											
	kStartFWAudioDeviceInParamCount					= 1, 
	kStartFWAudioDeviceOutParamCount				= 0,

	kStopFWAudioDeviceInParamCount					= 1, 
	kStopFWAudioDeviceOutParamCount					= 0,

	kDisposeFWAudioDeviceInParamCount 				= 1,
	kDisposeFWAudioDeviceOutParamCount 				= 0,

	kCreateFWAudioEngineInParamCount 				= 3,
	kCreateFWAudioEngineOutParamCount 				= 1,

	kDisposeFWAudioEngineInParamCount 				= 1,
	kDisposeFWAudioEngineOutParamCount 				= 0,

	kCreateFWAudioStreamInParamCount 				= 0xFFFFFFFF,
	kCreateFWAudioStreamOutParamCount 				= 0xFFFFFFFF,

	kDisposeFWAudioStreamInParamCount 				= 1,
	kDisposeFWAudioStreamOutParamCount 				= 0,
	
	kCreateFWAudioMIDIStreamInParamCount			= 3,
	kCreateFWAudioMIDIStreamOutParamCount			= 1,
	
	kDisposeFWAudioMIDIStreamInParamCount			= 1,
	kDisposeFWAudioMIDIStreamOutParamCount			= 0,

	kCreateFWAudioMIDIPlugInParamCount 				= 0xFFFFFFFF,
	kCreateFWAudioMIDIPlugOutParamCount 			= 0xFFFFFFFF,
	
	kDisposeFWAudioMIDIPlugInParamCount				= 1,
	kDisposeFWAudioMIDIPlugOutParamCount			= 0,

	kGetClockSourceInParamCount 					= 0,
	kGetClockSourceOutParamCount 					= 2,
	
	kSetClockSourceInParamCount 					= 2,
	kSetClockSourceOutParamCount 					= 0,
	
	kSetAutoLoadInParamCount 						= 1,
	kSetAutoLoadOutParamCount 						= 0,	

	kGetPropertyInParamCount 						= 2,
	kGetPropertyOutParamCount 						= 0,	
	
	kSetPropertyInParamCount 						= 2,
	kSetPropertyOutParamCount 						= 0	
	
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

// V5   -----------------------

	kFWASyncUpDevice,
	kFWAGetCurrentStreamRefs,	 
	kFWAGetStreamState,
	kFWAGetIsochStreamDirection,
	kFWAGetIsochStreamChannelID,
	kFWASetIsochStreamChannelID,
	kFWAGetStreamSampleRate,
	kFWASetStreamSampleRate,
	kFWAGetStreamOutputSpeed,
	kFWASetStreamOutputSpeed,
	kFWAGetStreamAudioType,
	kFWASetStreamAudioType, 
	kFWASetStreamCallbackFunction,
	kFWACreateIsochStream, 
	kFWADisposeIsochStream,
	kFWAStartIsochStream,
	kFWAStopIsochStream,
	kFWAGetIsochStreamAudioChannelCount,
	kFWASetIsochStreamAudioChannelCount,
	kFWAGetIsochStreamMIDIChannelCount,
	kFWASetIsochStreamMIDIChannelCount,
	kFWACreateFWAudioDevice,
	kFWADisposeFWAudioDevice,
	kFWAStartFWAudioDevice,
	kFWAStopFWAudioDevice, 
	kFWACreateFWAudioEngine,
	kFWADisposeFWAudioEngine,
	kFWACreateFWAudioStream,
	kFWADisposeFWAudioStream,
	kFWAGetClockSource,
	kFWASetClockSource,
	kFWACreateFWAudioMIDIStream,
	kFWADisposeFWAudioMIDIStream,
	kFWACreateFWAudioMIDIPlug,
	kFWADisposeFWAudioMIDIPlug,

// V6   -----------------------

	kFWASetAutoLoad,
	kFWAGetProperty,
	kFWASetProperty,

//  -----------------------
	
	kFWANumberFWAMethods			// Keep kFWANumberFWAMethods last!! (current count )
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
