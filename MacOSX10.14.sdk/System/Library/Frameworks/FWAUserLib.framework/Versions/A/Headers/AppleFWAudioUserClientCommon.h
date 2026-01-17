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

#define CURRENT_DEVICE_STATUS_VERSION	(0x00012000)

#define kNumInputClientBuffers			1
#define kMIDIInputClientBufferSize		(2 * 32 )
#define kMIDIInputRingBufferSize		(8 * kMIDIInputClientBufferSize * kNumInputClientBuffers )

#define kNumOutputClientBuffers			1
#define kMIDIOutputClientBufferSize		(2 * 32)
#define kMIDIOutputRingBufferSize		(8 * kMIDIOutputClientBufferSize *  kNumOutputClientBuffers)

#define kFWAStreamIdentSize 			(36)
#define kFWAStreamEndpointIndentifier	"kFWAudioStreamEndpointIdentifier"
#define kAudioPlugPropertiesKey			"AudioPlugProperties"
#define kMIDIPlugPropertiesKey			"MIDIPlugProperties"

#define kMIDIPropertiesIsPrivateKey		"MIDIPropertyIsPrivate"
#define kMIDIPropertiesIsEmbeddedKey	"MIDIPropertyIsEmbedded"

#define kFWAGetCurrentClockSourcePlugKey 'clkp'

#define kFWAMaxPropertyKeyLength (256)
#define kFWAMaxPropertyValueLength (4096 - (kFWAMaxPropertyKeyLength + 8))
#define kFWAMaxPathLength (512)

#include <libkern/OSTypes.h>

enum {
	kCurrentEraseHeadMeterArrayOffset = 0,
	kNumSamplesFramesInBufferMeterArrayOffset = 1,
	kCurrentInputDMASampleFrameMeterArrayOffset = 2,
	kCurrentOutputDMASampleFrameMeterArrayOffset = 3,
	kGetBadHeaderCountMeterArrayOffset = 4,
	kGetFixedHeaderCountMeterArrayOffset = 5,
	kGetBigPacketCountMeterArrayOffset = 6,
	kLastTimeStampMeterArrayOffset = 7,
	kLastTimeStampMeterArrayOffset2 = 8,
	kInputPacketCountMeterArrayOffset = 9
	
};

enum 
{
	kMIDIStreamOut = 0,
	kMIDIStreamIn = 1,
	// OR this will the above to indicate that the MIDI buffer is a structure defined below.
	kMIDIAdvanceSchedule = 0x40000000UL,
	kMIDITimeStamp = 0x80000000UL
};

typedef struct FWAMIDIInputBufferWithTimeStamp
{
	UInt64		timeStamp;
	UInt8		midiBuffer[kMIDIInputClientBufferSize];
} FWAMIDIInputBufferWithTimeStamp;

typedef struct FWAMIDIOutputBufferWithTimeStamp
{
	UInt64		timeStamp;
	UInt8		midiBuffer[kMIDIOutputClientBufferSize];
} FWAMIDIOutputBufferWithTimeStamp;

enum FWAStreamDirection
{
	kFWAStreamOut		= 0x00000000UL,
	kFWAStreamIn		= 0x00000001UL
};

typedef enum FWAStreamDirection FWAStreamDirection;

enum FWAStreamOptions
{
	kFWAStreamOptionsDefault		= 0,
	kFWAStreamOptionsForceNuDCL 	= (1 << 16),
	kFWAStreamOptionsForceLegacyDCL = (1 << 17),
};

typedef enum FWAStreamOptions FWAStreamOptions;


typedef struct FWAMIDIReadBuffer
{
	UInt32			bufSize;
	UInt32 			mrBuf[kMIDIInputClientBufferSize];	

} FWAMIDIReadBuf;

enum FWAudioType
{
	kIEC60958		= 0x00,
	kRawAudio		= 0x40,
	kMIDI			= 0x80,
	kAncillaryData	= 0xC0,
	kAllEventTypes  = 0xFF
};
typedef enum FWAudioType FWAudioType, *FWAudioTypePtr;

enum FWAMIDIDataInfo 
{
    kFWAMIDIPlugName				= 'mnam',
	kFWAMIDIPlugIdent				= 'midn',		// Used with MIDI unique plug ID
	kFWAMIDIPlugPropertyPrivate		= 'priv',
	kFWAMIDIPlugPropertyEmbedded	= 'embd',	
	kFWAMIDIGetIndexedPlug			= 0xFFFFFFFF
};

enum FWAStreamState 
{
    kFWAStreamStopped	= 0,
    kFWAStreamRunning	= 1,
    kFWAStreamPaused	= 2,
    kFWAStreamResumed	= 3
};

enum
{
	kFWAPlugNotConnected = 0xFF,
	kFWAUnusedIsochChannelID = 0xFF
};

typedef enum FWAStreamState FWAStreamState;
typedef void (*FWAStreamNotificationProc)(UInt32 isochStreamRef, void* refCon);


// Moved to AppleFWAudioUserLib.cpp
// update this with the version of the driver in xxxx.xxxx
#define kFWADeviceStatusCurrentVersion (0x00012000)

typedef struct FWADeviceStatus
{
	UInt32			version;	
	UInt32			sampleCounter;
	UInt32			inputSampleFrame;
	UInt32			outputSampleFrame;
	UInt32			inputClipSampleFrame;
	UInt32			outputClipSampleFrame;
	UInt32			meterData[1];	//numInputChannels + numInputChannels
} FWADeviceStatusRec, *FWADeviceStatusRecPtr;

typedef struct FWACreateStreamRec
{
	UInt32			owningIsochStreamRef;
	UInt32			channelNumber;
	UInt32			direction;
	UInt32			numAudioChannels;
    char			streamName[64];
	unsigned char	streamIdent[kFWAStreamIdentSize];
	bool			streamIdentIsNull;
	
} FWACreateStreamRec, *FWACreateStreamRecPtr;

typedef struct FWACreateMIDIPlugRec
{
	UInt32			owningMIDIStreamRef;
	UInt32			mpxID;
    char			plugName[64];
	unsigned char	plugIdent[kFWAStreamIdentSize];
	bool			plugIdentIsNull;
} FWACreateMIDIPlugRec, *FWACreateMIDIPlugRecPtr;

typedef struct FWACreateFWAudioPlugRec
{
	UInt32			owningAudioStreamRef;
	UInt32			channelID;
    char			plugName[64];
	unsigned char	plugIdent[kFWAStreamIdentSize];
	bool			plugIdentIsNull;
} FWACreateFWAudioPlugRec, *FWACreateFWAudioPlugRecPtr;

typedef struct FWACreateDeviceRec
{
	UInt32			vendorID;
    char			deviceName[64];
	char			guidStr[64];

} FWACreateDeviceRec, *FWACreateDeviceRecPtr;

typedef struct FWASetPluginPathRec
{
	UInt32			owningEngineRef;
	UInt32			vendorID;
	UInt32			modelID;	
    char			pluginPath[kFWAMaxPathLength];
	bool			pluginPathIsNull;
	bool			cacheValues;
} FWASetPluginPathRec, *FWASetPluginPathRecPtr;

typedef struct FWASetPlugPropertyRec
{
	UInt32			owningPlugRef;
    char			plugPropertyKey[kFWAMaxPropertyKeyLength];
	char			plugPropertyValue[kFWAMaxPropertyValueLength];
	bool			plugPropertyValueIsNull;

} FWASetPlugPropertyRec, *FWASetPlugPropertyRecPtr;

typedef struct FWACreateMIDIDeviceNubRec
{
	UInt32			owningDevice;
	UInt32			vendorID;
	UInt32			modelID;
	char			deviceName[64];
	char			guidStr[64];
    char			iconFilePath[256];
	char			editorPath[256];
} FWACreateMIDIDeviceNubRec, *FWACreateMIDIDeviceNubRecPtr;

typedef struct FWAGetPropertyRec
{
	UInt32			key;
	UInt32			size;
    char			data[1024];
} FWAGetPropertyRec, *FWAGetPropertyRecPtr;

enum
{
	kFWAudioMaxNameSize = 64,

	kReadBlockInParamCount = 1,
	kReadBlockOutParamCount = 0xFFFFFFFF,
	
	kWriteQuadletInParamCount = 2,
	kWriteQuadletOutParamCount = 0,
	
	kWriteBlockInParamCount = 1,
	kWriteBlockOutParamCount = 0xFFFFFFFF,
	
	kReadQuadletInParamCount = 1,
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

	kGetPropertyInParamCount 						= 0xFFFFFFFF,
	kGetPropertyOutParamCount 						= 0xFFFFFFFF,	
	
	kSetPropertyInParamCount 						= 2,
	kSetPropertyOutParamCount 						= 0,
	
	kSetPluginPathInParamCount 						= 0xFFFFFFFF,
	kSetPluginPathOutParamCount 					= 0xFFFFFFFF,
	
	kCreateFWAudioPlugInParamCount					= 0xFFFFFFFF,			
	kCreateFWAudioPlugOutParamCount					= 0xFFFFFFFF,
	
	kDisposeFWAudioPlugInParamCount 				= 1,
	kDisposeFWAudioPlugOutParamCount				= 0,
	
	kSetFWAudioMIDIPlugChannelInParamCount			= 2,
	kSetFWAudioMIDIPlugChannelOutParamCount			= 0,
	
	kGetFWAudioMIDIPlugChannelInParamCount			= 1,
	kGetFWAudioMIDIPlugChannelOutParamCount			= 2,
	
	kGetFWAudioPlugChannelInParamCount				= 1,
	kGetFWAudioPlugChannelOutParamCount				= 1,
	
	kSetFWAudioPlugChannelInParamCount				= 2,
	kSetFWAudioPlugChannelOutParamCount				= 0,
	
	kAttachFWAudioStreamInParamCount 				= 2,
	kAttachFWAudioStreamOutParamCount				= 0,
	
	kAttachFWAudioMIDIStreamInParamCount 			= 2,
	kAttachFWAudioMIDIStreamOutParamCount			= 0,
	
	kSetFWAudioPlugPropertyInParamCount 			= 0xFFFFFFFF,
	kSetFWAudioPlugPropertyOutParamCount			= 0xFFFFFFFF,
	
	kSetFWAudioMIDIPlugPropertyInParamCount 		= 0xFFFFFFFF,
	kSetFWAudioMIDIPlugPropertyOutParamCount		= 0xFFFFFFFF,
	
	kOpenLocalWithInterfaceInParamCount 			= 0,
	kOpenLocalWithInterfaceOutParamCount			= 0,
	
	kOpenWithServiceInParamCount 					= 0,
	kOpenWithServiceOutParamCount					= 0,
	
	kGetMaxSpeedInParamCount						= 0,
	kGetMaxSpeedOutParamCount						= 1,	
	
	kGetSessionRefInParamCount						= 0,
	kGetSessionRefOutParamCount						= 0,
	
	kReserveIsochSequencesInParamCount				= 3,
	kReserveIsochSequencesOutParamCount				= 0,

	kCreateFWAudioMIDIDeviceNubInParamCount 		= 0xFFFFFFFF,
	kCreateFWAudioMIDIDeviceNubOutParamCount 		= 0xFFFFFFFF,
	
	kDisposeFWAudioMIDIDeviceNubInParamCount		= 1, 
	kDisposeFWAudioMIDIDeviceNubOutParamCount		= 0,
	
	kGetIndexedFWAudioPlugInParamCount				= 3, 
	kGetIndexedFWAudioPlugOutParamCount				= 1,

	kGetIndexedFWAudioMIDIPlugInParamCount			= 3, 
	kGetIndexedFWAudioMIDIPlugOutParamCount			= 1,
	
	kMIDIDeviceNubAttachMIDIPlugInParamCount		= 2,
	kMIDIDeviceNubAttachMIDIPlugOutParamCount		= 0,
	
	kMIDIDeviceNubDetachMIDIPlugInParamCount		= 1,
	kMIDIDeviceNubDetachMIDIPlugOutParamCount		= 0	
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

// V7   -----------------------

	kFWASetPluginPath,
	kFWACreateFWAudioPlug,
	kFWADisposeFWAudioPlug,
	kFWASetFWAudioMIDIPlugChannel,
	kFWASetFWAudioPlugChannel,
	kFWAGetFWAudioMIDIPlugChannel,
	kFWAGetFWAudioPlugChannel,
	kFWAAttachFWAudioStream,
	kFWAAttachFWAudioMIDIStream,
	kFWASetFWAudioPlugProperty,
	kFWASetFWAudioMIDIPlugProperty,
	kFWAOpenLocalWithInterface,
	kFWAOpenWithService,
	kFWAGetSessionRef,
	kFWAGetMaxSpeed,
	kFWAReserveIsochSequences,
	kFWACreateFWAudioMIDIDeviceNub,
	kFWADisposeFWAudioMIDIDeviceNub,
	kFWAGetIndexedFWAudioPlug, 
	kFWAGetIndexedFWAudioMIDIPlug,  
	kFWAMIDIDeviceNubAttachMIDIPlug,
	kFWAMIDIDeviceNubDetachMIDIPlug,

// Async
	
	kFWASetAsyncPort,
	kWriteMIDIAsync,
	kReadMIDIAsync,

//   ------------------------
	
	kFWANumberFWAMethods			// Keep kFWANumberFWAMethods last!! (current count )
};


#endif /*_AppleFWAudioUserClientCommon_H */
