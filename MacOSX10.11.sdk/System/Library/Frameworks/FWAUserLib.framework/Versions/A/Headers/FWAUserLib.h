/*
     File:      FWAUserLib/FWAUserLib.h
 
     Contains:  Public API for AppleFWAudio driver userclient
 
     Version:   Mac OS X
 
     Copyright © 2001-2013 Apple Computer, Inc. All rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/
/*!
	@header
	This header contains the C interface to the AppleFWAudio driver. The functions in this library allow applications
	to create and manage audio and MIDI streams and plugs, audio engines, and audio devices. In addition, this library
	can be used to implement mLAN support in Mac OS X.

	@attribute Path /System/Library/Frameworks/FWAUserLib.framework/Versions/A/Headers/AppleFWAudioUserLib.h
	@attribute Include Path
		&lt;FWAUserLib/AppleFWAudioUserLib.h&gt;
*/

// <rdar://problem/11755857> Apply FWAUserLib framework headerdoc patch

#include 	<IOKit/firewire/IOFireWireFamilyCommon.h>
#include 	<FWAUserLib/AppleFWAudioUserClientCommon.h>

/*! Opaque pointer to userland FWARefRec */
typedef struct OpaqueFWARef				*FWARef;

/*! Opaque kernel pointer to AM824Channel */
typedef struct OpaqueFWAIsochStreamRef	*FWAIsochStreamRef;

/*! Opaque kernel pointer to AppleLocalAudioDevice */
typedef struct OpaqueFWADeviceRef		*FWADeviceRef;

/*! Opaque kernel pointer to AppleFWAudioEngineNub */
typedef struct OpaqueFWAEngineRef		*FWAEngineRef;

/*! Opaque kernel pointer to AppleFWAudioStream. */
typedef struct OpaqueFWAAudioStreamRef	*FWAAudioStreamRef;

/*! Opaque kernel pointer to AppleFWAudioMIDIStream. */
typedef struct OpaqueFWAMIDIStreamRef	*FWAMIDIStreamRef;

/*! Opaque kernel pointer to AppleFWAudioMIDIPlug. */
typedef struct OpaqueFWAMIDIPlugRef		*FWAMIDIPlugRef;

/*! Opaque kernel pointer to AppleFWAudioStream. */
typedef struct OpaqueFWAAudioPlugRef	*FWAAudioPlugRef;

/*! Opaque kernel pointer to AppleFWAudioMIDIDeviceNub. */
typedef struct OpaqueFWAMIDIDeviceNubRef *FWAMIDIDeviceNubRef;

#if __cplusplus
extern "C" {
#endif

	// Device identification
	typedef UInt32 FWADeviceID;			
	
#pragma mark -- V1
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// API
	/*! @group Version 1 */
       
	/*!
	 * @function FWACountDevices
	 * @abstract Returns the number of AppleFWAudio devices connected to the system and their node IDs.
	 * @discussion Because node IDs are dynamic and can change, you should get the device list again after each bus reset.
	 * @availability Version 1
	 * @param deviceNodeIDArray Pointer to an array of UInt16 values representing node IDs.
	 * @param deviceCount On input, pass in the size of the array; on output, deviceCount contains the number of nodeIDs returned in the array.
	 * @result OSStatus
	 */
	OSStatus FWACountDevices( UInt16* deviceNodeIDArray,UInt16* deviceCount );

	/*!
	 * @function FWAOpen
	 * @abstract Opens a user client connection to the AppleFWAudio driver.
	 * @discussion The returned FWARef is needed for all future calls to the user library. The FWARef is unique to the node ID used to open the
	 * connection. If the node ID changes after a bus reset, you can get the device's new node ID using @link FWAGetNodeID FWAGetNodeID@/link.
	 * @availability Version 1
	 * @param nodeID The node ID of the device to open.
	 * @param outRef On return, the FWARef for the device.
	 * @result OSStatus
	 */
	OSStatus FWAOpen(UInt32 nodeID, FWARef* outRef );

	/*!
	 * @function FWAOpenLocal
	 * @abstract Opens a connection to the FireWire audio service that is attached to the Macintosh local FireWire node.
	 * @discussion The FWARef device reference returned by this function can be passed to all functions that
	 * accept an FWARef. Note that some functions in earlier versions of the AppleFWAudioUserLib API may not
	 * work with a local FireWire node reference. This reference will work with all functions in version 5
	 * and above of the API.
	 *
	 * If the outRef parameter is set to 'midi' before calling this function, an internal flag is set that
	 * indicates this is a connection to the MIDI system. Note that there can be only one connection to the
	 * MIDI system at a time. An access error will be returned if a MIDI connection is attempted while another
	 * MIDI connection is already open. The AppleFWAudioMIDIDriver uses this mode to vend its MIDI services.
	 * If this connection is open before the AppleFWAudioMIDIDriver attempts to open it, MIDI data will not
	 * be sent to and from CoreMIDI.
	 * @availability Version 5
	 * @param outRef On return, an FWARef that represents the FireWire audio service attached to the Macintosh local FireWire node.
	 * @result OSStatus
	 */
	OSStatus FWAOpenLocal( FWARef* outRef );

	/*!
	 * @function FWAClose
	 * @abstract Closes the connection that was made to the device with @link FWAOpen FWAOpen@/link.
	 * @availability Version 1 
	 * @param inRef The FWARef of the device to close.
	 * @result OSStatus
	 */     
	OSStatus FWAClose( FWARef 	inRef );

	/*!
	 * @function FWARead
	 * @abstract 
	 * @discussion 
	 * @availability Version 1
	 * @param inRef
	 * @param inAddress
	 * @param inSubAddress
	 * @param inDataSize
	 * @param inDataPtr
	 * @result OSStatus
	 */
	OSStatus FWARead( FWARef inRef, UInt8 inAddress, UInt8 inSubAddress, ByteCount	 inDataSize, void * inDataPtr );

	/*!
	 * @function FWAWrite
	 * @abstract 
	 * @discussion 
	 * @availability Version 1
	 * @param inRef
	 * @param inAddress
	 * @param inSubAddress
	 * @param inDataSize
	 * @param inDataPtr
	 * @result OSStatus
	 */
	OSStatus FWAWrite( FWARef inRef, UInt8 inAddress, UInt8	 inSubAddress, ByteCount inDataSize,  const void *	inDataPtr );

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// mLan support
	/*! @group Version 1 (mLAN support) */
	/*!
	 * @function FWAGetNodeID
	 * @abstract Returns the node ID of the passed-in FWARef device reference.
	 * @discussion Node IDs can change after the device is opened with the FWARef device reference. This function returns the current node ID.
	 * @availability Version 1 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param outNodeID The node ID of the device for the current bus generation.
	 * @param outGeneration The current bus generation.
	 * @result OSStatus
	 */
	OSStatus FWAGetNodeID(FWARef inRef, UInt32 *outNodeID, UInt32 *outGeneration);

	/*!
	 * @function FWAGetGUID
	 * @abstract Returns the device's globally unique ID (GUID).
	 * @availability Version 1
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param guid The address of a UInt64 to hold the device GUID.
	 * @result OSStatus
	 */     
	OSStatus FWAGetGUID(FWARef inRef, UInt64 *guid);

	/*!
	 * @function FWAGetMacGUID
	 * @abstract Returns the Macintosh computer's globally unique ID (GUID).
	 * @availability Version 1 
	 * @param inRef In general this parameter is ignored, but it may be needed if the device is connected to an add-in FireWire card.
	 * @param guid The address of a UInt64 to hold the Macintosh computer's GUID.
	 * @result OSStatus
	 */
	OSStatus FWAGetMacGUID(FWARef inRef, UInt64 *guid);

	/*!
	 * @function FWAReadQuadlet
	 * @abstract Reads a quadlet at the specified FireWire address.
	 * @availability Version 1 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param address A pointer to the FWAddress of the quadlet to read. 
	 * @param outData A pointer to a UInt32 to hold the quadlet that was read.
	 * @result OSStatus
	 */
	OSStatus FWAReadQuadlet(FWARef inRef, FWAddressPtr address, UInt32 *outData);

	/*!
	 * @function FWAReadBlock
	 * @abstract Reads a block of data from the specified FireWire address.
	 * @availability Version 1 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param address A pointer to the FWAddress at the start of the read.
	 * @param size A pointer to a UInt32 that holds the size of the block to read.
	 * @param outData A pointer to the data that was read.
	 * @result OSStatus
	 */
	OSStatus FWAReadBlock(FWARef inRef, 	FWAddressPtr address, UInt32* size, UInt8 *outData);

	/*!
	 * @function FWAExecuteAVC
	 * @abstract Sends an AVC command to the device and receives a response.
	 * @availability Version 1 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param cmd A pointer to the AVC command to send.
	 * @param cmdSize The size of the AVC command.
	 * @param response A pointer to the response buffer.
	 * @param responseSize A pointer to the size of the response.
	 * @result OSStatus
	 */
	OSStatus FWAExecuteAVC(FWARef inRef, UInt8* cmd,UInt32 cmdSize,UInt8* response,UInt32* responseSize);

	/*!
	 * @function FWAWriteQuadlet
	 * @abstract Writes a quadlet to the specified FireWire address.
	 * @availability Version 1 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param address A pointer to the FWAddress of the quadlet to write.
	 * @param data The data to write.
	 * @result OSStatus
	 */
	OSStatus FWAWriteQuadlet(FWARef inRef, FWAddressPtr address, UInt32 data);

	/*!
	 * @function FWAWriteBlock
	 * @abstract Writes a block of data to the specified FireWire address.
	 * @availability Version 1
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param address A pointer to the FWAddress to write to.
	 * @param size The size of the block.
	 * @param data A pointer to the data to write.
	 * @result OSStatus
	 */
	OSStatus FWAWriteBlock(FWARef inRef, FWAddressPtr address, UInt32 size, const UInt8 *data);

	/*!
	 * @function FWACreateMIDIStream
	 * @abstract Creates a MIDI stream reference which allows MIDI to be sent and received via the FireWire device.
	 * @availability Version 1
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param midiIO MIDI input or output (can be either kMIDIInput or kMIDIOutput).
	 * @param bufSizeInBytes The size of the buffer in bytes.
	 * @param buf A pointer to the buffer to hold the MIDI bytes sent to or received from the driver.
	 * @param sequenceNum The sequence number of the MIDI data in the isochronous packet.
	  * @param midiStreamRef On return, the reference to the MIDI stream to use in other MIDI functions.
	 * @result OSStatus
	 */
	OSStatus FWACreateMIDIStream(FWARef inRef, UInt32 midiIO, UInt32 bufSizeInBytes, void * buf, UInt32 sequenceNum, UInt32 *midiStreamRef);

	/*!
	 * @function FWADisposeMIDIStream
	 * @abstract Destroys a MIDI stream reference.
	 * @availability Version 1 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param midiStreamRef The MIDI stream reference created with @link FWACreateMIDIStream FWACreateMIDIStream@/link.
	 * @result OSStatus
	 */
	OSStatus FWADisposeMIDIStream(FWARef inRef, UInt32 midiStreamRef);

	/*!
	 * @function FWAWriteMIDIData
	 * @abstract This function has been deprecated. Use @link FWAWriteMIDIDataAsync FWAWriteMIDIDataAsync@/link instead.
	 */
	OSStatus FWAWriteMIDIData(FWARef inRef,  UInt32 midiStreamRef, UInt32 writeMsgLength, UInt8 * buf);

	/*!
	 * @function FWAReadMIDIData
	 * @abstract This function has been deprecated. Use @link FWAReadMIDIDataAsync FWAReadMIDIDataAsync@/link instead.
	 */
	OSStatus FWAReadMIDIData( FWARef inRef,  UInt32 midiStreamRef, FWAMIDIReadBuf *buf);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma mark -- V2

	/*! @group Version 2 */

	/*!
	 * @function FWAGetCycleTimeOffset
	 * @abstract Gets the cycle time offset the driver adds to the time stamp to compensate for delays in the packetizer.
	 * @availability Version 2
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param cycleTimeOffset The cycle time offset in nanoseconds.
	 * @result OSStatus
	 */

	OSStatus FWAGetCycleTimeOffset(FWARef inRef, UInt32* cycleTimeOffset);

	/*!
	 * @function FWASetCycleTimeOffset
	 * @abstract Sets the cycle time offset the driver should add to the time stamp to compensate for delays in the packetizer.
	 * @availability Version 2
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param cycleTimeOffset The cycle time offset in nanoseconds.
	 * @result OSStatus
	 */
	OSStatus FWASetCycleTimeOffset(FWARef inRef, UInt32 cycleTimeOffset);

	/*!
	 * @function FWAGetVendorID
	 * @abstract Gets the vendor ID of the device.
	 * @discussion This function retrieves the vendor ID that the FireWire family places in the I/O Registry when the device is enumerated.
	 * @availability Version 2
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param vendorID On return, a pointer to the vendor ID of the device.
	 * @result OSStatus
	 */     
	OSStatus FWAGetVendorID(FWARef inRef, UInt32 * vendorID);

	/*!
	 * @function FWAGetDeviceName
	 * @abstract Gets the name of the device.
	 * @discussion This function retrieves the device name that the FireWire family places in the I/O Registry when the device is enumerated.
	 * @availability Version 2
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param name On return, a pointer to the device name.
	 * @result OSStatus
	 */
	OSStatus FWAGetDeviceName(FWARef inRef, char * name);

	/*!
	 * @function FWAGetVendorName
	 * @abstract Gets the vendor name of the device.
	 * @discussion This function retrieves the vendor name that the FireWire family places in the I/O Registry when the device is enumerated.
	 * @availability Version 2
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param name On return, a pointer to the device name.
	 * @result OSStatus
	 */
	OSStatus FWAGetVendorName(FWARef inRef, char * name);

	/*!
	 * @function FWAIsMIDICapable
	 * @abstract Returns whether the device is MIDI capable.
	 * @availability Version 2
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param supportsMIDI On return, a pointer to a Boolean value (TRUE if the device supports MIDI, FALSE if it does not).
	 * @result OSStatus
	 */
	OSStatus FWAIsMIDICapable(FWARef inRef, bool* supportsMIDI);

	/*!
	 * @function FWAGetNumMIDIInputPlugs
	 * @abstract Gets the total number of MIDI input plugs of all MIDI streams attached to the device.
	 * @availability Version 2
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param plugs On return, a pointer to the number of MIDI input plugs.
	 * @result OSStatus
	 */
	OSStatus FWAGetNumMIDIInputPlugs(FWARef inRef, UInt32* plugs);

	/*!
	 * @function FWAGetNumMIDIOutputPlugs
	 * @abstract Gets the total number of MIDI output plugs of all MIDI streams attached to the device.
	 * @availability Version 2
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param plugs On return, a pointer to the number of MIDI output plugs.
	 * @result OSStatus 
	 */
	OSStatus FWAGetNumMIDIOutputPlugs(FWARef inRef, UInt32* plugs);

	/*!
	 * @function FWASetNumMIDIInputPlugs
	 * @abstract Sets the number of MIDI input plugs of all MIDI streams attached to the device.
	 * @availability Version 2
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param plugs The number of input plugs.
	 * @result OSStatus
	 */
	OSStatus FWASetNumMIDIInputPlugs(FWARef inRef, UInt32 plugs);

	/*!
	 * @function FWASetNumMIDIOutputPlugs
	 * @abstract Sets the number of MIDI output plugs of all MIDI streams attached to the device.
	 * @availability Version 2
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param plugs The number of output plugs.
	 * @result OSStatus
	 */
	OSStatus FWASetNumMIDIOutputPlugs(FWARef inRef, UInt32 plugs);

	/*!
	 * @function FWAGetNumAudioInputPlugs
	 * @abstract Gets the total number of audio input plugs to the device.
	 * @availability Version 2
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param plugs On return, a pointer to the number of audio input plugs.
	 * @result OSStatus
	 */
	OSStatus FWAGetNumAudioInputPlugs(FWARef inRef, UInt32* plugs);

	/*!
	 * @function FWAGetNumAudioOutputPlugs
	 * @abstract Gets the total number of audio output plugs to the device.
	 * @availability Version 2
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param plugs On return, a pointer to the number of audio output plugs.
	 * @result OSStatus
	 */
	OSStatus FWAGetNumAudioOutputPlugs(FWARef inRef, UInt32* plugs);

	/*!
	 * @function FWACreateAudioStream
	 * @abstract This function has been deprecated. Use @link FWACreateFWAudioStream FWACreateFWAudioStream@/link instead.
	 * @availability Version 2
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param audioIO
	 * @param audioStreamRef
	 * @param sequenceNum
	 * @result OSStatus
	 */
	OSStatus FWACreateAudioStream(FWARef inRef,UInt32 audioIO, UInt32 *audioStreamRef, UInt32 *sequenceNum);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma mark -- V3

	/*! @group Version 3 */

	/*!
	 * @function FWADisposeAudioStream
	 * @abstract This function has been deprecated. Use @link FWADisposeFWAudioStream FWADisposeFWAudioStream@/link instead.
	 * @availability Version 3
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param audioStreamRef
	 * @result OSStatus
	 */
	OSStatus FWADisposeAudioStream(FWARef inRef, UInt32 audioStreamRef);

	/*!
	 * @function FWAGetDeviceSampleRate 
	 * @abstract Gets the device's current sample rate.
	 * @availability Version 3
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param rate On return, a pointer to the current sample rate value.
	 * @result OSStatus
	 */
	OSStatus FWAGetDeviceSampleRate(FWARef inRef,UInt32* rate);

	/*!
	 * @function FWAGetDeviceSendMode
	 * @abstract Gets the device's current send mode.
	 * @availability Version 3
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param mode On return, a pointer to the send mode (can be either IEC60958 or Raw audio).
	 * @result OSStatus
	 */
	OSStatus FWAGetDeviceSendMode(FWARef inRef,UInt32* mode);

	/*!
	 * @function FWAGetDeviceStatus
	 * @abstract Returns a status structure containing device statistics (intended for diagnostic use).
	 * @availability Version 3
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param outData A pointer to a status structure.
	 * @param inSize The size of the status structure.
	 * @result OSStatus
	 */
	OSStatus FWAGetDeviceStatus( FWARef inRef, void *outData, UInt32 inSize);

	/*!
	 * @function FWAGetDeviceStreamInfo
	 * @abstract Returns private information about the driver, according to specific input parameters.
	 * @availability Version 3
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param audioStreamRef Unused.
	 * @param numInput The number of input channels of this stream.
	 * @param inputIsochChan The isochronous channel used for the input stream.
	 * @param numOutput The number of output channels of this stream.
	 * @param outputIsochChan The isochronous channel used for the output stream.
	 * @result OSStatus
	 */
	OSStatus FWAGetDeviceStreamInfo(FWARef inRef, UInt32 audioStreamRef, UInt32* numInput,UInt32* inputIsochChan, UInt32* numOutput,UInt32* outputIsochChan);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Async methods added for MIDI

	/*! @group Version 3 (asynchronous MIDI functions) */

	/*!
	 * @function FWAInitAEvntSource
	 * @abstract Initializes the event source so asynchronous commands can send a notification to the CFRunLoop source.
	 * @availability Version 3
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param source The run loop to send messages to.
	 * @param refcon User value that is returned when the event source is triggered.
	 * @result OSStatus
	 */
	OSStatus FWAInitAEvntSource(FWARef inRef, CFRunLoopSourceRef *source, void * refcon);

	/*!
	 * @function CreateAsyncWakePort
	 * @abstract Creates a port for asynchronous responses (most developers will not need to use this).
	 * @availability Version 3
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param notifyPort On return, a Mach port (mach_port_t) for notification.
	 * @result OSStatus
	 */
	OSStatus CreateAsyncWakePort(FWARef inRef, mach_port_t *notifyPort);

	/*!
	 * @function FWAGetAEvntSource
	 * @abstract Gets the event source reference.
	 * @availability Version 3
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @result The run loop to pass in @link FWAInitAEvntSource FWAInitAEvntSource@/link.
	 */
	CFRunLoopSourceRef FWAGetAEvntSource(FWARef inRef);

	/*!
	 * @function FWAWriteMIDIDataAsync
	 * @abstract Writes data to the MIDI stream asynchronously.
	 * @availability Version 3
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param midiStreamRef The FWAMIDIStreamRef returned in @link FWACreateMIDIStream FWACreateMIDIStream@/link.
	 * @param writeMsgLength Length of the data to write in bytes.
	 * @param callback
	 * @param refCon User value that is returned when the notification is sent.
	 * @result OSStatus
	 */
	OSStatus FWAWriteMIDIDataAsync(FWARef inRef, UInt32 midiStreamRef, UInt32 writeMsgLength, IOAsyncCallback1 callback, void * refCon);

	/*!
	 * @function FWAReadMIDIDataAsync
	 * @abstract Reads data from the MIDI stream asynchronously.
	 * @availability Version 3
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link.
	 * @param midiStreamRef The FWAMIDIStreamRef returned in @link FWACreateMIDIStream FWACreateMIDIStream@/link.
	 * @param readBufSize Size in bytes of the buffer in which to receive the results.
	 * @param callback
	 * @param refCon User value that is returned when the notification is sent.
	 * @result OSStatus
	 */
	OSStatus FWAReadMIDIDataAsync(FWARef inRef, UInt32 midiStreamRef, UInt32 readBufSize, IOAsyncCallback2 callback, void * refCon);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma mark -- V4

	/*! @group Version 4 */

	/*!
	 * @function FWASetDeviceStreamInfo
	 * @abstract This function is deprecated.
	 * @availability Version 4
	 * @param inRef
	 * @param audioStreamRef
	 * @param numInput
	 * @param inputIsochChan 
	 * @param numOutput 
	 * @param outputIsochChan
	 * @param update
	 * @result Because this function is deprecated, the return value indicates it is unimplemented.
	 */
	OSStatus FWASetDeviceStreamInfo(FWARef inRef, UInt32 audioStreamRef, UInt32 numInput,UInt32 inputIsochChan, UInt32 numOutput,UInt32 outputIsochChan,bool update);
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma mark -- V5
	/*! @group Version 5 */

	/*!
	 * @function FWASyncUpDevice
	 * @abstract Causes a notification to be sent to the driver that something may have changed externally and that the driver should resynchronize.  This function is currently not used.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @result OSStatus
	 */     
	OSStatus FWASyncUpDevice(FWARef inRef);

	/*!
	 * @function FWAGetMaxSpeed
	 * @availability Version 5
	 * @abstract Gets the maximum speed of the device.
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param speed On return, a pointer to an IOFWSpeed that contains the speed.
	 * @result OSStatus
	 */
	OSStatus FWAGetMaxSpeed(FWARef inRef,IOFWSpeed* speed);

	/*!
	 * @function FWAGetMaxIsochChannels
	 * @abstract Gets the maximum number of isochronous stream contexts the Macintosh can support.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param inChannels On return, a pointer to the number of isochronous input channels.
	 * @param outChannels On return, a pointer to the number of isochronous output channels.
	 * @result OSStatus
	 */
	OSStatus FWAGetMaxIsochChannels(FWARef inRef, UInt32* inChannels, UInt32* outChannels);

	/*!
	 * @function FWAGetMaxSequences
	 * @abstract Gets the maximum number of sequences the driver can support.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param numSequences On return, a pointer to the number of sequences.
	 * @result OSStatus
	 */
	OSStatus FWAGetMaxSequences(FWARef inRef, UInt32* numSequences);

	 /*!
	 * @function FWAGetSupportedSampleRates
	 * @abstract Gets the sample rates the driver supports.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param sampleRates A pointer to an array of sample rates.
	 * @param count On input, a pointer to the number of sample rates the array can hold; on return, the actual number of sample rates returned.
	 * @result OSStatus
	 */
	OSStatus FWAGetSupportedSampleRates(FWARef inRef, UInt32* sampleRates, UInt32* count);

	/*!
	 * @function FWAGetSupportedAudioTypes
	 * @abstract Gets the audio types the driver supports.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param audioTypes A pointer to an array of audio types. 
	 * @param count On input, a pointer to the number of audio types the array can hold; on return, the actual number of audio types returned.
	 * @result OSStatus
	 */
	OSStatus FWAGetSupportedAudioTypes(FWARef inRef, FWAudioType* audioTypes, UInt32* count);

	/*!
	 * @function FWAGetCurrentIsochStreamRefs
	 * @abstract Gets the isochronous stream references the driver currently supports.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef A pointer to an array of isochronous stream references.
	 * @param count On input, a pointer to the number of audio types the array can hold; on return, the actual number of audio types returned.
	 * @result OSStatus
	 */
	OSStatus FWAGetCurrentIsochStreamRefs(FWARef inRef, FWAIsochStreamRef* isochStreamRef, UInt32* count);

	/*!
	 * @function FWAGetIsochStreamState
	 * @abstract Gets the isochronous stream state of the specified isochronous stream reference.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef An isochronous stream reference.
	 * @param state A pointer to an FWAStreamState that contains the current state (can be stopped, running, paused, or resumed).
	 * @result OSStatus
	 */
	OSStatus FWAGetIsochStreamState(FWARef inRef, FWAIsochStreamRef isochStreamRef,FWAStreamState* state);

	/*!
	 * @function FWAGetIsochStreamDirection
	 * @abstract Gets the stream direction of the specified isochronous stream reference.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef An isochronous stream reference.
	 * @param direction A pointer to an FWAStreamDirection that contains the current stream direction (can be out or in).
	 * @result OSStatus
	 */
	OSStatus FWAGetIsochStreamDirection(FWARef inRef, FWAIsochStreamRef isochStreamRef,FWAStreamDirection* direction);

	/*!
	 * @function FWAGetIsochStreamChannelID
	 * @abstract Gets the current isochronous stream channel ID.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef An isochronous stream reference.
	 * @param channelID On return, a pointer to the current isochronous stream channel ID.
	 * @result OSStatus
	 */
	OSStatus FWAGetIsochStreamChannelID(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32* channelID);

	/*!
	 * @function FWASetIsochStreamChannelID
	 * @abstract Sets the isochronous stream channel ID to the given value.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef An isochronous stream reference.
	 * @param channelID The value to which the isochronous stream channel ID should be set.
	 * @result OSStatus
	 */
	OSStatus FWASetIsochStreamChannelID(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32 channelID);

	/*!
	 * @function FWAGetIsochStreamSampleRate
	 * @abstract Gets the sample rate of the specified isochronous stream.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef An isochronous stream reference.
	 * @param rate On return, a pointer to the isochronous stream sample rate.
	 * @result OSStatus 
	 */
	OSStatus FWAGetIsochStreamSampleRate(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32* rate);

	/*!
	 * @function FWASetIsochStreamSampleRate
	 * @abstract Sets the sample rate of the specified isochronous stream.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef An isochronous stream reference.
	 * @param rate The sample rate to which the isochronous stream should be set.
	 * @result OSStatus 
	 */
	OSStatus FWASetIsochStreamSampleRate(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32 rate);

	/*!
	 * @function FWAGetIsochStreamOutputSpeed
	 * @abstract Gets the speed of the specified isochronous output stream.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef An isochronous stream reference. 
	 * @param speed On return, a pointer to an IOFWSpeed that contains the speed.
	 * @result OSStatus
	 */
	OSStatus FWAGetIsochStreamOutputSpeed(FWARef inRef, FWAIsochStreamRef isochStreamRef,IOFWSpeed* speed);

	/*!
	 * @function FWASetIsochStreamOutputSpeed
	 * @abstract Sets the speed of the specified isochronous output stream.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef An isochronous stream reference. 
	 * @param speed The speed to which the isochronous output stream should be set.
	 * @result OSStatus
	 */
	OSStatus FWASetIsochStreamOutputSpeed(FWARef inRef, FWAIsochStreamRef isochStreamRef,IOFWSpeed speed);

	/*!
	 * @function FWAGetIsochStreamAudioType 
	 * @abstract Gets the audio type of the specified isochronous stream.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef An isochronous stream reference.
	 * @param type On return, a pointer to an FWAudioType that contains the type (can be IEC60598, raw audio, or MIDI).
	 * @result OSStatus
	 */
	OSStatus FWAGetIsochStreamAudioType(FWARef inRef, FWAIsochStreamRef isochStreamRef, FWAudioType* type);

	/*!
	 * @function FWASetIsochStreamAudioType 
	 * @abstract Sets the audio type of the specified isochronous stream.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef An isochronous stream reference.
	 * @param type The audio type to which the isochronous stream should be set.
	 * @result OSStatus
	 */
	OSStatus FWASetIsochStreamAudioType(FWARef inRef, FWAIsochStreamRef isochStreamRef, FWAudioType type);

	/*!
	 * @function FWACreateIsochStream
	 * @abstract Creates an isochronous stream.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param channelNumber The requested isochronous channel number to use. If this channel number is available, it will be allocated. If this channel number is in use, this routine will find
	 * the next available channel number. If there are no more channels available, it will return kIOReturnNoResources.
	 * @param direction The direction of the isochronous stream (can be kIOAudioStreamDirectionInput or kIOAudioStreamDirectionOutput).
	 * @param numAudioChannels The number of audio channels to create for this stream.
	 * @param numMIDIChannels The number of MIDI channels to create for this stream.
	 * @param isochStreamRef On return, an FWAIsochStreamRef representing this isochronous stream.
	 * @result OSStatus
	 */
	OSStatus FWACreateIsochStream(FWARef inRef, UInt32 channelNumber,FWAStreamDirection direction,UInt32 numAudioChannels,UInt32 numMIDIChannels, FWAIsochStreamRef* isochStreamRef );

	/*!
	 * @function FWADisposeIsochStream
	 * @abstract Destroys the isochronous stream reference.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef The FWAIsochStreamRef created with @link FWACreateIsochStream FWACreateIsochStream@/link.
	 * @result OSStatus
	 */
	OSStatus FWADisposeIsochStream(FWARef inRef,FWAIsochStreamRef isochStreamRef );

	/*!
	 * @function FWAStartIsochStream
	 * @abstract Starts an isochronous stream.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef The FWAIsochStreamRef created with @link FWACreateIsochStream FWACreateIsochStream@/link.
	 * @result OSStatus
	 */     
	OSStatus FWAStartIsochStream(FWARef inRef, FWAIsochStreamRef isochStreamRef);

	/*!
	 * @function FWAStopIsochStream
	 * @abstract Stops an isochronous stream.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef The FWAIsochStreamRef created with @link FWACreateIsochStream FWACreateIsochStream@/link.
	 * @result OSStatus
	 */
	OSStatus FWAStopIsochStream(FWARef inRef,FWAIsochStreamRef isochStreamRef );

	/*!
	 * @function FWAGetIsochStreamAudioSequenceCount
	 * @abstract Returns the number of audio sequences in the frame.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef The FWAIsochStreamRef created with @link FWACreateIsochStream FWACreateIsochStream@/link.
	 * @param numAudioSequence On return, a pointer to the audio sequence count.
	 * @result OSStatus
	 */
	OSStatus FWAGetIsochStreamAudioSequenceCount(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32* numAudioSequence);

	/*!
	 * @function FWASetIsochStreamAudioSequenceCount
	 * @abstract Changes the number of audio sequences in a FWAIsochStreamRef object.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef The FWAIsochStreamRef created with @link FWACreateIsochStream FWACreateIsochStream@/link.
	 * @param numAudioSequence The number to which the isochronous stream audio sequence count should be set.
	 * @result OSStatus
	 */
	OSStatus FWASetIsochStreamAudioSequenceCount(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32 numAudioSequence);

	/*!
	 * @function FWAGetIsochStreamMIDISequenceCount
	 * @abstract Returns the number of MIDI sequences in the frame.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef The FWAIsochStreamRef created with @link FWACreateIsochStream FWACreateIsochStream@/link.
	 * @param numMIDISequence On return, the sequence count of the MIDI stream.
	 * @result OSStatus
	 */
	OSStatus FWAGetIsochStreamMIDISequenceCount(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32* numMIDISequence);

	/*!
	 * @function FWASetIsochStreamMIDISequenceCount
	 * @abstract
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param isochStreamRef The FWAIsochStreamRef created with @link FWACreateIsochStream FWACreateIsochStream@/link.
	 * @param numMIDISequence The sequence count to which the MIDI stream should be set.
	 * @result OSStatus
	 */
	OSStatus FWASetIsochStreamMIDISequenceCount(FWARef inRef, FWAIsochStreamRef isochStreamRef,UInt32 numMIDISequence);
	
	/*!
	 * @function FWACreateFWAudioDevice
	 * @abstract Creates an audio device that is connected to the local node.
	 * @discussion To create a local audio device that will work with Core Audio, you must also create the following
	 * objects (in this order):<br>
	 * <ul><li>An audio engine (using @link FWACreateFWAudioEngine FWACreateFWAudioEngine@/link)</li>
	 * <li>One or more isochronous streams (using @link FWACreateIsochStream FWACreateIsochStream@/link)</li>
	 * <li>One or more audio streams (using @link FWACreateFWAudioStream FWACreateFWAudioStream@/link)</li>
	 * </ul>
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param deviceName The string representing the device name.
	 * @param vendorID The vendor ID of the device.
	 * @param guid The GUID of the device.
	 * @param device On return, the FWADeviceRef representing the audio device.
	 * @result OSStatus
	 */
	OSStatus FWACreateFWAudioDevice(FWARef inRef,const char * deviceName, UInt32 vendorID,const char* guid, FWADeviceRef* device);

	/*!
	 * @function FWADisposeFWAudioDevice
	 * @abstract Destroys an audio device object.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param device The FWADeviceRef created with @link FWACreateFWAudioDevice FWACreateFWAudioDevice@/link.
	 * @result OSStatus
	 */
	OSStatus FWADisposeFWAudioDevice(FWARef inRef,FWADeviceRef device);

	/*!
	 * @function FWAStartFWAudioDevice
	 * @abstract Starts an audio device.
	 * @discussion All streams connected to the device will be started. If there are no streams attached, this function will return a kIOReturnNoResources error.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param device The FWADeviceRef created with @link FWACreateFWAudioDevice FWACreateFWAudioDevice@/link.
	 * @result OSStatus
	 */
	OSStatus FWAStartFWAudioDevice(FWARef inRef,FWADeviceRef device);

	/*!
	 * @function FWAStopFWAudioDevice
	 * @abstract Stops an audio device.
	 * @discussion This function stops all the streams connected to the device and deallocates the resources created for the streaming.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param device The FWADeviceRef created with @link FWACreateFWAudioDevice FWACreateFWAudioDevice@/link.
	 * @result OSStatus 
	 */
	OSStatus FWAStopFWAudioDevice(FWARef inRef,FWADeviceRef device);

	/*!
	 * @function FWACreateFWAudioEngine
	 * @abstract Creates an IOAudioEngine for the specified audio device.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param owningDevice The FWADeviceRef created with @link FWACreateFWAudioDevice FWACreateFWAudioDevice@/link.
	 * @param hasInput A Boolean value that indicates whether the device has audio input channels.
	 * @param hasOutput A Boolean value that indicates whether the device has audio output channels.
	 * @param engine On return, the FWAEngineRef representing the audio engine.
	 * @result OSStatus
	 */
	OSStatus FWACreateFWAudioEngine(FWARef inRef, FWADeviceRef owningDevice, bool hasInput, bool hasOutput, FWAEngineRef* engine);

	/*!
	 * @function FWADisposeFWAudioEngine
	 * @abstract Destroys an audio engine object.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param engine The FWAEngineRef created with @link FWACreateFWAudioEngine FWACreateFWAudioEngine@/link.
	 * @result OSStatus
	 */     
	OSStatus FWADisposeFWAudioEngine(FWARef inRef, FWAEngineRef engine);

	/*!
	 * @function FWACreateFWAudioStream
	 * @abstract Creates an audio stream in the specified isochronous stream.
	 * @availability Version 5 
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param owningIsochStreamRef The FWAIsochStreamRef created with @link FWACreateIsochStream FWACreateIsochStream@/link.
	 * @param channelNumber The Core Audio channel number (channels are numbered 1 to n channels).
	 * @param direction The direction of the audio stream (can be either kIOAudioStreamDirectionInput or kIOAudioStreamDirectionOutput).
	 * @param numAudioChannels The number of audio channels this audio stream should have.
	 * @param streamName The string representing the stream name.
	 * @param streamIdent A pointer to a stream ID property used to identify the stream in the I/O Registry.
	 * @param streamRef On return, the FWAAudioStreamRef representing this audio stream.
	 * @result OSStatus
	 */
	OSStatus FWACreateFWAudioStream(FWARef inRef, FWAIsochStreamRef owningIsochStreamRef, UInt32 channelNumber,UInt32 direction,UInt32 numAudioChannels,char* streamName,UInt8* streamIdent, FWAAudioStreamRef* streamRef);

	/*!
	 * @function FWADisposeFWAudioStream
	 * @abstract Destroys an audio stream object.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param streamRef The FWAAudioStreamRef created with @link FWACreateFWAudioStream FWACreateFWAudioStream@/link.
	 * @result OSStatus
	 */

	OSStatus FWADisposeFWAudioStream(FWARef inRef, FWAAudioStreamRef streamRef );

	/*!
	 * @function FWACreateFWAudioMIDIStream
	 * @abstract Creates a MIDI stream.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param owningIsochStreamRef The FWAIsochStreamRef created with @link FWACreateIsochStream FWACreateIsochStream@/link.
	 * @param sequenceNumber The sequence number representing the slot in the packet of this MIDI stream.
	 * @param direction The direction of the MIDI stream (can be either kIOAudioStreamDirectionInput or kIOAudioStreamDirectionOutput).
	 * @param streamRef On return, the FWAMIDIStreamRef representing this MIDI stream.
	 * @result OSStatus
	 */
	OSStatus FWACreateFWAudioMIDIStream(FWARef inRef, FWAIsochStreamRef owningIsochStreamRef, UInt32 sequenceNumber,UInt32 direction, FWAMIDIStreamRef* streamRef);

	/*!
	 * @function FWADisposeFWAudioMIDIStream
	 * @abstract Destroys a MIDI stream.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param streamRef The FWAMIDIStreamRef created with @link FWACreateFWAudioMIDIStream FWACreateFWAudioMIDIStream@/link.
	 * @result OSStatus
	 */
	OSStatus FWADisposeFWAudioMIDIStream(FWARef inRef, FWAMIDIStreamRef streamRef );

	/*!
	 * @function FWACreateFWAudioMIDIPlug
	 * @abstract Creates a MIDI plug.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param owningMIDIStreamRef The FWAMIDIStreamRef created with @link FWACreateFWAudioMIDIStream FWACreateFWAudioMIDIStream@/link.
	 * @param mpxID The MIDI multiplex index ID that specifies the index to which this plug should go.
	 * @param plugName The string representing the plug name.
	 * @param plugIdent A property of the MIDI plug.
	 * @param streamRef On return, the FWAMIDIPlugRef representing this MIDI plug.
	 * @result OSStatus
	 */
	OSStatus FWACreateFWAudioMIDIPlug(FWARef inRef, FWAMIDIStreamRef owningMIDIStreamRef,UInt8 mpxID,char* plugName, UInt8* plugIdent, FWAMIDIPlugRef* streamRef);

	/*!
	 * @function FWADisposeFWAudioMIDIPlug
	 * @abstract Destroys a MIDI plug object.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param plugRef The FWAMIDIPlugRef created with @link FWACreateFWAudioMIDIPlug FWACreateFWAudioMIDIPlug @/link.
	 * @result OSStatus
	 */
	OSStatus FWADisposeFWAudioMIDIPlug(FWARef inRef, FWAMIDIPlugRef plugRef );

	/*!
	 * @function FWAGetClockSource
	 * @abstract Returns the isochronous stream providing the clock (SYT) for the audio.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param streamRef The FWAIsochStreamRef created with @link FWACreateIsochStream FWACreateIsochStream@/link.
	 * @param sequence
	 * @result OSStatus
	 */
	OSStatus FWAGetClockSource(FWARef inRef, FWAIsochStreamRef *streamRef, UInt32 *sequence);

	/*!
	 * @function FWASetClockSource
	 * @abstract Sets the isochronous stream as the clock source.
	 * @availability Version 5
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param streamRef The FWAIsochStreamRef created with @link FWACreateIsochStream FWACreateIsochStream@/link.
	 * @param sequence
	 * @result OSStatus
	 */
	OSStatus FWASetClockSource(FWARef inRef, FWAIsochStreamRef streamRef,UInt32 sequence);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma mark -- V6

	/*! @group Version 6 */

	/*!
	 * @function FWASetAutoLoad
	 * @abstract Creates or removes the AppleFWAudio_Disable property in the I/O Registry.
	 * @discussion The existence of the AppleFWAudio_Disable property in the I/O Registry tells the driver to <i>not</i> load if it matches on a device (the
	 * value of the property does not matter). Call FWASetAutoLoad with enable = TRUE to create the property. To remove the property (if it already exists), call
	 * {@link FWASetAutoLoad} with enable = FALSE.
	 * @availability Version 6
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param enable A Boolean value that indicates whether the AppleFWAudio_Disable property should be removed from or created in the I/O Registry.
	 * @result OSStatus
	 */
	OSStatus FWASetAutoLoad(FWARef inRef, bool enable);

	/* 
	 * @function FWAGetProperty
	 * @abstract 
	 * @availability Version 6
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param propertyID
	 * @param data
	 * @param size
	 * @result OSStatus
	 */
	OSStatus FWAGetProperty(FWARef inRef, UInt32 propertyID, void * data,UInt32* size);

	/*
	 * @function FWASetProperty
	 * @abstract
	 * @availability Version 6
	 * @param inRef The FWARef returned in @link FWAOpen FWAOpen@/link or in @link FWAOpenLocal FWAOpenLocal@/link.
	 * @param propertyID
	 * @param data
	 * @param size
	 * @result OSStatus
	 */
	OSStatus FWASetProperty(FWARef inRef, UInt32 propertyID, void * data,UInt32 size);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma mark -- V7
	
	/*! @group Version 7 */

	/*! Description forthcoming. */
	OSStatus FWASetPluginPath(FWARef inRef,FWAEngineRef engine,UInt32 vendorID, UInt32 modelID, const char* pluginPath);
	
	/*! Description forthcoming. */
	OSStatus FWACreateFWAudioPlug(FWARef inRef, FWAAudioStreamRef owningStream,UInt32 channelID,char* plugName, UInt8* plugIdent, FWAAudioPlugRef* streamRef);

	/*! Description forthcoming. */
	OSStatus FWADisposeFWAudioPlug(FWARef inRef, FWAAudioPlugRef plugRef );
	
	/*! Description forthcoming. */
	OSStatus FWAGetFWAudioMIDIPlugChannel(FWARef inRef, FWAMIDIPlugRef streamRef,UInt32* channelID);

	/*! Description forthcoming. */
	OSStatus FWASetFWAudioMIDIPlugChannel(FWARef inRef, FWAMIDIPlugRef streamRef,UInt32 channelID);

	/*! Description forthcoming. */
	OSStatus FWAGetFWAudioPlugChannel(FWARef inRef, FWAAudioPlugRef streamRef,UInt32* channelID);

	/*! Description forthcoming. */
	OSStatus FWASetFWAudioPlugChannel(FWARef inRef, FWAAudioPlugRef streamRef,UInt32 channelID);

	/*! Description forthcoming. */
	OSStatus FWAGetIndexedFWAudioPlug(FWARef inRef,FWADeviceRef device, UInt32 index,UInt32 dir, FWAAudioPlugRef* plugRef);

	/*! Description forthcoming. */
	OSStatus FWAGetIndexedFWAudioMIDIPlug(FWARef inRef, FWAMIDIDeviceNubRef device,UInt32 index,UInt32 dir,FWAMIDIPlugRef* plugRef);
	
	/*! Description forthcoming. */
	OSStatus FWAAttachFWAudioStream(FWARef inRef, FWAAudioStreamRef streamRef,FWAIsochStreamRef isochChannel);

	/*! Description forthcoming. */
	OSStatus FWAAttachFWAudioMIDIStream(FWARef inRef, FWAMIDIStreamRef streamRef,FWAIsochStreamRef isochChannel);

	/*! Description forthcoming. */
	OSStatus FWASetFWAudioPlugProperty(FWARef inRef, FWAAudioPlugRef plugRef,const char *keyname,const  char* keyvalue);

	/*! Description forthcoming. */
	OSStatus FWASetFWAudioMIDIPlugProperty(FWARef inRef,FWAMIDIPlugRef plugRef,const char *keyname,const  char* keyvalue);

	/*! Description forthcoming. */
	OSStatus FWAOpenLocalWithInterface(UInt64 guid,UInt32 options, FWARef* outRef);

	/*! Description forthcoming. */
	OSStatus FWAOpenWithService(io_service_t ,UInt32 options, FWARef* outRef);

	/*! Description forthcoming. */
	OSStatus FWAGetSessionRef(FWARef inRef,IOFireWireSessionRef * sessionRef);

	/*! Description forthcoming. */
	OSStatus FWAReserveIsochSequences(FWARef inRef,FWAIsochStreamRef isochStream,FWAudioType type,UInt32 count);
	
	/*! Description forthcoming. */
	OSStatus FWACreateFWAudioMIDIDeviceNub(FWARef inRef,FWADeviceRef owningDevice, const char * deviceName, UInt32 vendorID,const char* guid,const char* iconFilePath, UInt32 modelID, const char * editorPath, FWAMIDIDeviceNubRef* device);

	/*! Description forthcoming. */
	OSStatus FWADisposeFWAudioMIDIDeviceNub(FWARef inRef,FWAMIDIDeviceNubRef device);

	/*! Description forthcoming. */
	OSStatus FWAMIDIDeviceNubAttachMIDIPlug(FWARef inRef, FWAMIDIDeviceNubRef midiDeviceNub,FWAMIDIPlugRef midiPlug);

	/*! Description forthcoming. */
	OSStatus FWAMIDIDeviceNubDetachMIDIPlug(FWARef inRef, FWAMIDIPlugRef midiPlug);	

#if __cplusplus
}
#endif


