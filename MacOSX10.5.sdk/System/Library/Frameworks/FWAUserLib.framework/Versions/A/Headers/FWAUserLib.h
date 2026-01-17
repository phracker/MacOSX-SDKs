/*
     File:      FWAUserLib/FWAUserLib.h
 
     Contains:  Public API for AppleFWAudio driver userclient
 
     Version:   Mac OS X
 
     Copyright: © 2005 - 2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/


#include 	<IOKit/firewire/IOFireWireFamilyCommon.h>
#include 	<FWAUserLib/AppleFWAudioUserClientCommon.h>

typedef struct OpaqueFWARef				*FWARef;				// Opaque pointer to userland FWARefRec
typedef struct OpaqueFWAIsochStreamRef	*FWAIsochStreamRef;		// kernel pointer to AM824Channel
typedef struct OpaqueFWADeviceRef		*FWADeviceRef;			// kernel pointer to AppleLocalAudioDevice
typedef struct OpaqueFWAEngineRef		*FWAEngineRef;			// kernel pointer to AppleFWAudioEngineNub
typedef struct OpaqueFWAAudioStreamRef	*FWAAudioStreamRef;
typedef struct OpaqueFWAMIDIStreamRef	*FWAMIDIStreamRef;
typedef struct OpaqueFWAMIDIPlugRef		*FWAMIDIPlugRef;
typedef struct OpaqueFWAAudioPlugRef	*FWAAudioPlugRef;
typedef struct OpaqueFWAMIDIDeviceNubRef *FWAMIDIDeviceNubRef;

#if __cplusplus
extern "C" {
#endif

	// Device identification
	typedef UInt32 FWADeviceID;			
	
#pragma mark -- V1
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// API
	OSStatus FWACountDevices( UInt16* deviceNodeIDArray,UInt16* deviceCount );
	OSStatus FWAOpen(UInt32 nodeID, FWARef* outRef );
	OSStatus FWAOpenLocal( FWARef* outRef );

	OSStatus FWAClose( FWARef 	inRef );
	OSStatus FWARead( FWARef inRef, UInt8 inAddress, UInt8 inSubAddress, ByteCount	 inDataSize, void * inDataPtr );
	OSStatus FWAWrite( FWARef inRef, UInt8 inAddress, UInt8	 inSubAddress, ByteCount inDataSize,  const void *	inDataPtr );

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// mLan support
	OSStatus FWAGetNodeID(FWARef inRef, UInt32 *outNodeID, UInt32 *outGeneration);
	OSStatus FWAGetGUID(FWARef inRef, UInt64 *guid);
	OSStatus FWAGetMacGUID(FWARef inRef, UInt64 *guid);
	OSStatus FWAReadQuadlet(FWARef inRef, FWAddressPtr address, UInt32 *outData);
	OSStatus FWAReadBlock(FWARef inRef, 	FWAddressPtr address, UInt32* size, UInt8 *outData);
	OSStatus FWAExecuteAVC(FWARef inRef, UInt8* cmd,UInt32 cmdSize,UInt8* response,UInt32* responseSize);
	OSStatus FWAWriteQuadlet(FWARef inRef, FWAddressPtr address, UInt32 data);
	OSStatus FWAWriteBlock(FWARef inRef, FWAddressPtr address, UInt32 size, const UInt8 *data);
	OSStatus FWACreateMIDIStream(FWARef inRef, UInt32 midiIO, UInt32 bufSizeInBytes, void * buf, UInt32 sequenceNum, UInt32 *midiStreamRef);
	OSStatus FWADisposeMIDIStream(FWARef inRef, UInt32 midiStreamRef);
	OSStatus FWAWriteMIDIData(FWARef inRef,  UInt32 midiStreamRef, UInt32 writeMsgLength, UInt8 * buf);
	OSStatus FWAReadMIDIData( FWARef inRef,  UInt32 midiStreamRef, FWAMIDIReadBuf *buf);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma mark -- V2

	OSStatus FWAGetCycleTimeOffset(FWARef inRef, UInt32* cycleTimeOffset);
	OSStatus FWASetCycleTimeOffset(FWARef inRef, UInt32 cycleTimeOffset);
	OSStatus FWAGetVendorID(FWARef inRef, UInt32 * vendorID);
	OSStatus FWAGetDeviceName(FWARef inRef, char * name);
	OSStatus FWAGetVendorName(FWARef inRef, char * name);
	OSStatus FWAIsMIDICapable(FWARef inRef, bool* supportsMIDI);
	OSStatus FWAGetNumMIDIInputPlugs(FWARef inRef, UInt32* plugs);
	OSStatus FWAGetNumMIDIOutputPlugs(FWARef inRef, UInt32* plugs);
	OSStatus FWASetNumMIDIInputPlugs(FWARef inRef, UInt32 plugs);
	OSStatus FWASetNumMIDIOutputPlugs(FWARef inRef, UInt32 plugs);
	OSStatus FWAGetNumAudioInputPlugs(FWARef inRef, UInt32* plugs);
	OSStatus FWAGetNumAudioOutputPlugs(FWARef inRef, UInt32* plugs);
	OSStatus FWACreateAudioStream(FWARef inRef,UInt32 audioIO, UInt32 *audioStreamRef, UInt32 *sequenceNum);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma mark -- V3

	OSStatus FWADisposeAudioStream(FWARef inRef, UInt32 audioStreamRef);
	OSStatus FWAGetDeviceSampleRate(FWARef inRef,UInt32* rate);
	OSStatus FWAGetDeviceSendMode(FWARef inRef,UInt32* mode);
	OSStatus FWAGetDeviceStatus( FWARef inRef, void *outData, UInt32 inSize);
	OSStatus FWAGetDeviceStreamInfo(FWARef inRef, UInt32 audioStreamRef, UInt32* numInput,UInt32* inputIsochChan, UInt32* numOutput,UInt32* outputIsochChan);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Async methods added for MIDI
	OSStatus FWAInitAEvntSource(FWARef inRef, CFRunLoopSourceRef *source, void * refcon);
	OSStatus CreateAsyncWakePort(FWARef inRef, mach_port_t *notifyPort);
	CFRunLoopSourceRef FWAGetAEvntSource(FWARef inRef);
	OSStatus FWAWriteMIDIDataAsync(FWARef inRef, UInt32 midiStreamRef, UInt32 writeMsgLength, IOAsyncCallback1 callback, void * refCon);
	OSStatus FWAReadMIDIDataAsync(FWARef inRef, UInt32 midiStreamRef, UInt32 readBufSize, IOAsyncCallback2 callback, void * refCon);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma mark -- V4
	
	OSStatus FWASetDeviceStreamInfo(FWARef inRef, UInt32 audioStreamRef, UInt32 numInput,UInt32 inputIsochChan, UInt32 numOutput,UInt32 outputIsochChan,bool update);
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma mark -- V5
	
	OSStatus FWASyncUpDevice(FWARef inRef);
	
	OSStatus FWAGetMaxSpeed(FWARef inRef,IOFWSpeed* speed);
	OSStatus FWAGetMaxIsochChannels(FWARef inRef, UInt32* inChannels, UInt32* outChannels);
	OSStatus FWAGetMaxSequences(FWARef inRef, UInt32* numSequences);
	OSStatus FWAGetSupportedSampleRates(FWARef inRef, UInt32* sampleRates, UInt32* count);
	OSStatus FWAGetSupportedAudioTypes(FWARef inRef, FWAudioType* audioTypes, UInt32* count);
	
	OSStatus FWAGetCurrentIsochStreamRefs(FWARef inRef, FWAIsochStreamRef* isochStreamRef, UInt32* count);
	OSStatus FWAGetIsochStreamState(FWARef inRef, FWAIsochStreamRef isochStreamRef,FWAStreamState* state);
	OSStatus FWAGetIsochStreamDirection(FWARef inRef, FWAIsochStreamRef isochStreamRef,FWAStreamDirection* direction);
	OSStatus FWAGetIsochStreamChannelID(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32* channelID);
	OSStatus FWASetIsochStreamChannelID(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32 channelID);

	OSStatus FWAGetIsochStreamSampleRate(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32* rate);
	OSStatus FWASetIsochStreamSampleRate(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32 rate);
	
	OSStatus FWAGetIsochStreamOutputSpeed(FWARef inRef, FWAIsochStreamRef isochStreamRef,IOFWSpeed* speed);
	OSStatus FWASetIsochStreamOutputSpeed(FWARef inRef, FWAIsochStreamRef isochStreamRef,IOFWSpeed speed);
	
	OSStatus FWAGetIsochStreamAudioType(FWARef inRef, FWAIsochStreamRef isochStreamRef, FWAudioType* type);
	OSStatus FWASetIsochStreamAudioType(FWARef inRef, FWAIsochStreamRef isochStreamRef, FWAudioType type);
		
	OSStatus FWACreateIsochStream(FWARef inRef, UInt32 channelNumber,FWAStreamDirection direction,UInt32 numAudioChannels,UInt32 numMIDIChannels, FWAIsochStreamRef* isochStreamRef );
	OSStatus FWADisposeIsochStream(FWARef inRef,FWAIsochStreamRef isochStreamRef );
	
	OSStatus FWAStartIsochStream(FWARef inRef, FWAIsochStreamRef isochStreamRef);
	OSStatus FWAStopIsochStream(FWARef inRef,FWAIsochStreamRef isochStreamRef );

	OSStatus FWAGetIsochStreamAudioSequenceCount(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32* numAudioSequence);
	OSStatus FWASetIsochStreamAudioSequenceCount(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32 numAudioSequence);

	OSStatus FWAGetIsochStreamMIDISequenceCount(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32* numMIDISequence);
	OSStatus FWASetIsochStreamMIDISequenceCount(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32 numMIDISequence);
	
	OSStatus FWACreateFWAudioDevice(FWARef inRef,const char * deviceName, UInt32 vendorID,const char* guid, FWADeviceRef* device);
	OSStatus FWADisposeFWAudioDevice(FWARef inRef,FWADeviceRef device);
	OSStatus FWAStartFWAudioDevice(FWARef inRef,FWADeviceRef device);
	OSStatus FWAStopFWAudioDevice(FWARef inRef,FWADeviceRef device);
		
	OSStatus FWACreateFWAudioEngine(FWARef inRef, FWADeviceRef owningDevice, bool hasInput, bool hasOutput, FWAEngineRef* engine);
	OSStatus FWADisposeFWAudioEngine(FWARef inRef, FWAEngineRef engine);
	
	OSStatus FWACreateFWAudioStream(FWARef inRef, FWAIsochStreamRef owningIsochStreamRef, UInt32 channelNumber,UInt32 direction,UInt32 numAudioChannels,char* streamName,UInt8* streamIdent, FWAAudioStreamRef* streamRef);
	OSStatus FWADisposeFWAudioStream(FWARef inRef, FWAAudioStreamRef streamRef );

	OSStatus FWACreateFWAudioMIDIStream(FWARef inRef, FWAIsochStreamRef owningIsochStreamRef, UInt32 sequenceNumber,UInt32 direction, FWAMIDIStreamRef* streamRef);
	OSStatus FWADisposeFWAudioMIDIStream(FWARef inRef, FWAMIDIStreamRef streamRef );

	OSStatus FWACreateFWAudioMIDIPlug(FWARef inRef, FWAMIDIStreamRef owningMIDIStreamRef,UInt8 mpxID,char* plugName, UInt8* plugIdent, FWAMIDIPlugRef* streamRef);
	OSStatus FWADisposeFWAudioMIDIPlug(FWARef inRef, FWAMIDIPlugRef plugRef );

	OSStatus FWAGetClockSource(FWARef inRef, FWAIsochStreamRef *streamRef, UInt32 *sequence);
	OSStatus FWASetClockSource(FWARef inRef, FWAIsochStreamRef streamRef,UInt32 sequence);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma mark -- V6
	
	OSStatus FWASetAutoLoad(FWARef inRef, bool enable);
	OSStatus FWAGetProperty(FWARef inRef, UInt32 propertyID, void * data,UInt32* size);
	OSStatus FWASetProperty(FWARef inRef, UInt32 propertyID, void * data,UInt32 size);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma mark -- V7
	
	OSStatus FWASetPluginPath(FWARef inRef,FWAEngineRef engine,UInt32 vendorID, UInt32 modelID, const char* pluginPath);
	
	OSStatus FWACreateFWAudioPlug(FWARef inRef, FWAAudioStreamRef owningStream,UInt32 channelID,char* plugName, UInt8* plugIdent, FWAAudioPlugRef* streamRef);
	OSStatus FWADisposeFWAudioPlug(FWARef inRef, FWAAudioPlugRef plugRef );
	
	OSStatus FWAGetFWAudioMIDIPlugChannel(FWARef inRef, FWAMIDIPlugRef streamRef,UInt32* channelID);
	OSStatus FWASetFWAudioMIDIPlugChannel(FWARef inRef, FWAMIDIPlugRef streamRef,UInt32 channelID);

	OSStatus FWAGetFWAudioPlugChannel(FWARef inRef, FWAAudioPlugRef streamRef,UInt32* channelID);
	OSStatus FWASetFWAudioPlugChannel(FWARef inRef, FWAAudioPlugRef streamRef,UInt32 channelID);

	OSStatus FWAGetIndexedFWAudioPlug(FWARef inRef,FWADeviceRef device, UInt32 index,UInt32 dir, FWAAudioPlugRef* plugRef);
	OSStatus FWAGetIndexedFWAudioMIDIPlug(FWARef inRef, FWAMIDIDeviceNubRef device,UInt32 index,UInt32 dir,FWAMIDIPlugRef* plugRef);
	
	OSStatus FWAAttachFWAudioStream(FWARef inRef, FWAAudioStreamRef streamRef,FWAIsochStreamRef isochChannel);
	OSStatus FWAAttachFWAudioMIDIStream(FWARef inRef, FWAMIDIStreamRef streamRef,FWAIsochStreamRef isochChannel);

	OSStatus FWASetFWAudioPlugProperty(FWARef inRef, FWAAudioPlugRef plugRef,const char *keyname,const  char* keyvalue);
	OSStatus FWASetFWAudioMIDIPlugProperty(FWARef inRef,FWAMIDIPlugRef plugRef,const char *keyname,const  char* keyvalue);

	OSStatus FWAOpenLocalWithInterface(UInt64 guid,UInt32 options, FWARef* outRef);
	OSStatus FWAOpenWithService(io_service_t ,UInt32 options, FWARef* outRef);

	OSStatus FWAGetSessionRef(FWARef inRef,IOFireWireSessionRef * sessionRef);

	OSStatus FWAReserveIsochSequences(FWARef inRef,FWAIsochStreamRef isochStream,FWAudioType type,UInt32 count);
	
	OSStatus FWACreateFWAudioMIDIDeviceNub(FWARef inRef,FWADeviceRef owningDevice, const char * deviceName, UInt32 vendorID,const char* guid,const char* iconFilePath, UInt32 modelID, const char * editorPath, FWAMIDIDeviceNubRef* device);
	OSStatus FWADisposeFWAudioMIDIDeviceNub(FWARef inRef,FWAMIDIDeviceNubRef device);

	OSStatus FWAMIDIDeviceNubAttachMIDIPlug(FWARef inRef, FWAMIDIDeviceNubRef midiDeviceNub,FWAMIDIPlugRef midiPlug);
	OSStatus FWAMIDIDeviceNubDetachMIDIPlug(FWARef inRef, FWAMIDIPlugRef midiPlug);	

#if __cplusplus
}
#endif


