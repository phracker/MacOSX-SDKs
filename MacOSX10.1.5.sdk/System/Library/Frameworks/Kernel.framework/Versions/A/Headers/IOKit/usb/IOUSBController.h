/*
 * Copyright (c) 1998-2001 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.2 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.  
 * Please see the License for the specific language governing rights and 
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
#ifndef _IOKIT_IOUSBCONTROLLER_H
#define _IOKIT_IOUSBCONTROLLER_H

#include <libkern/c++/OSArray.h>

#include <IOKit/IOService.h>
#include <IOKit/IOMemoryDescriptor.h>
#include <IOKit/IODeviceMemory.h>
#include <IOKit/IOWorkLoop.h>
#include <IOKit/IOCommandGate.h>
#include <IOKit/IOCommandPool.h>

#include <IOKit/usb/USB.h>
#include <IOKit/usb/USBHub.h>
#include <IOKit/usb/IOUSBBus.h>
#include <IOKit/usb/IOUSBNub.h>
#include <IOKit/usb/IOUSBCommand.h>
#include <IOKit/usb/IOUSBWorkLoop.h>

/*
 * Errata
 * These indicate the anomolies of the various chips sets.  Test
 * for these in errataBits.
 */
enum {
    // turn off UHCI test mode
    kErrataCMDDisableTestMode		= (1 << 0),
    // Don't cross page boundaries in a single transfer
    kErrataOnlySinglePageTransfers	= (1 << 1),
    // UIM will retry out transfers with buffer underrun errors
    kErrataRetryBufferUnderruns		= (1 << 2),
    // UIM will insert delay buffer between HS and LS transfers
    kErrataLSHSOpti			= (1 << 3),
    // Always set the NOCP bit in rhDescriptorA register
    kErrataDisableOvercurrent		= (1 << 4),
    // Don't allow port suspend at the root hub
    kErrataLucentSuspendResume		= (1 << 5)
};
/* errataBits */

/*
    This table contains the list of errata that are necessary for known problems with particular devices.
    The format is vendorID, product ID, lowest revisionID needing errata, highest rev needing errata, errataBits.
    The result of all matches is ORed together, so more than one entry may match.
    Typically for a given errata a list of revisions that this applies to is supplied.
*/

struct ErrataListEntryStruct {
    UInt16 				vendID;
    UInt16 				deviceID;
    UInt16 				revisionLo;
    UInt16 				revisionHi;
    UInt32 				errata;
};

typedef struct ErrataListEntryStruct
                    ErrataListEntry,
                    *ErrataListEntryPtr;

void IOUSBSyncCompletion(void *target, void * parameter,
                                  IOReturn	status,
                                  UInt32	bufferSizeRemaining);

void  IOUSBSyncIsoCompletion(void *target, void * parameter,
                                  IOReturn	status,
                                  IOUSBIsocFrame *pFrames);


// forward definitions
class IOUSBDevice;
class IOUSBLog;
class IOUSBRootHubDevice;
class IOMemoryDescriptor;

/*!
    @class IOUSBController
    @abstract Base class for USB hardware driver
    @discussion Not many directly useful methods for USB device driver writers,
    IOUSBDevice, IOUSBInterface and IOUSBPipe provide more useful abstractions.
    The bulk of this class interfaces between IOKit and the low-level UIM, which is
    based on the MacOS9 UIM.
*/
class IOUSBController : public IOUSBBus
{
    OSDeclareAbstractStructors(IOUSBController)

protected:

    IOUSBWorkLoop *		_workLoop;
    IOCommandGate *		_commandGate;
    IOUSBRootHubDevice *	_rootHubDevice;
    UInt32			_devZeroLock;
    static UInt32		_busNumber;
    
    struct ExpansionData 
    {
	IOCommandPool		*freeUSBCommandPool;
	IOCommandPool		*freeUSBIsocCommandPool;
        IOTimerEventSource	*watchdogUSBTimer;
        bool			_terminating;
        bool			_watchdogTimerActive;
    };
    ExpansionData *_expansionData;
    
#define _freeUSBCommandPool		_expansionData->freeUSBCommandPool
#define _freeUSBIsocCommandPool		_expansionData->freeUSBIsocCommandPool
#define _watchdogUSBTimer		_expansionData->watchdogUSBTimer
#define _controllerTerminating		_expansionData->_terminating
#define _watchdogTimerActive		_expansionData->_watchdogTimerActive

    // The following methods do not use and upper case initial letter because they are part of IOKit
    //
    virtual bool 		init( OSDictionary *  propTable );
    virtual bool 		start( IOService *  provider );
    virtual void 		stop( IOService * provider );
    virtual bool 		finalize(IOOptionBits options);
    virtual IOReturn 		message( UInt32 type, IOService * provider,  void * argument = 0 );
 
    IOReturn			getNubResources( IOService *  regEntry );

    virtual UInt32 		GetErrataBits(
                                            UInt16 vendorID, 
                                            UInt16 deviceID, 
                                            UInt16 revisionID );    
    
    static IOReturn 		DoDeleteEP( 
                                            OSObject *	owner, 
                                            void *	arg0, 
                                            void *	arg1, 
                                            void *	arg2, 
                                            void *	arg3 );
                                            
    static IOReturn 		DoAbortEP( 
                                            OSObject *	owner, 
                                            void *	arg0, 
                                            void *	arg1, 
                                            void *	arg2, 
                                            void *	arg3 );
                                            
    static IOReturn 		DoClearEPStall( 
                                            OSObject *	owner, 
                                            void *	arg0, 
                                            void *	arg1, 
                                            void *	arg2, 
                                            void *	arg3 );
                                            
    static IOReturn 		DoCreateEP( 
                                            OSObject *	owner, 
                                            void *	arg0, 
                                            void *	arg1, 
                                            void *	arg2, 
                                            void *	arg3 );
    static IOReturn 		DoControlTransfer( 
                                            OSObject *	owner, 
                                            void *	arg0, 
                                            void *	arg1, 
                                            void *	arg2, 
                                            void *	arg3 );
                                            
    static IOReturn 		DoIOTransfer( 
                                            OSObject *	owner, 
                                            void *	arg0, 
                                            void *	arg1, 
                                            void *	arg2, 
                                            void *	arg3 );
                                            
    static IOReturn 		DoIsocTransfer(	
                                            OSObject *	owner, 
                                            void *	arg0, 
                                            void *	arg1, 
                                            void *	arg2, 
                                            void *	arg3 );
                                            
    static void			ControlPacketHandler( 
                                                    OSObject *	target,
                                                    void *	parameter,
                                                    IOReturn	status,
                                                    UInt32	bufferSizeRemaining );
                                                    
    static void			InterruptPacketHandler(
                                                    OSObject *	target,
                                                    void * 	parameter,
                                                    IOReturn	status,
                                                    UInt32	bufferSizeRemaining );
                                                    
    static void			BulkPacketHandler(
                                                    OSObject *	target,
                                                    void * 	parameter,
                                                    IOReturn	status,
                                                    UInt32	bufferSizeRemaining );

    static void			IsocCompletionHandler(
                                                    OSObject *		target,
                                                    void * 		parameter,
                                                    IOReturn		status,
                                                    IOUSBIsocFrame	*pFrames );
                                                    
    static void			WatchdogTimer(OSObject *target, IOTimerEventSource *sender);
    
    static IOReturn		ProtectedDevZeroLock(OSObject *target, void* lock, void *, void *, void*);

    USBDeviceAddress		GetNewAddress( void );
    
    IOReturn    		ControlTransaction( IOUSBCommand *  command );
    
    IOReturn    		InterruptTransaction( IOUSBCommand *  command );
    
    IOReturn    		BulkTransaction( IOUSBCommand *	command );
    
    IOReturn    		IsocTransaction( IOUSBIsocCommand *  command );
    
    void 			FreeCommand( IOUSBCommand *  command );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Invokes the specified completion action of the request.  If
    // the completion action is unspecified, no action is taken.
    inline void 		Complete(
                                            IOUSBCompletion	completion,
                                            IOReturn		status,
                                            UInt32		actualByteCount = 0 );



    //
    // UIM methods
    //
    virtual IOReturn 		UIMInitialize( IOService * provider ) = 0;
    virtual IOReturn 		UIMFinalize() = 0;

    // Control
    virtual IOReturn 		UIMCreateControlEndpoint(
                                                            UInt8	functionNumber,
                                                            UInt8	endpointNumber,
                                                            UInt16	maxPacketSize,
                                                            UInt8	speed) = 0;

    virtual IOReturn 		UIMCreateControlTransfer(   short		functionNumber,
                                                            short		endpointNumber,
                                                            IOUSBCompletion	completion,
                                                            void *		CBP,
                                                            bool		bufferRounding,
                                                            UInt32		bufferSize,
                                                            short		direction) = 0;

    virtual IOReturn 		UIMCreateControlTransfer(   short			functionNumber,
                                                            short			endpointNumber,
                                                            IOUSBCompletion		completion,
                                                            IOMemoryDescriptor *	CBP,
                                                            bool			bufferRounding,
                                                            UInt32			bufferSize,
                                                            short			direction) = 0;
    
    // Bulk
    virtual IOReturn 		UIMCreateBulkEndpoint(
                                                        UInt8		functionNumber,
                                                        UInt8		endpointNumber,
                                                        UInt8		direction,
                                                        UInt8		speed,
                                                        UInt8		maxPacketSize) = 0;

    virtual IOReturn 		UIMCreateBulkTransfer(  short			functionNumber,
                                                        short			endpointNumber,
                                                        IOUSBCompletion		completion,
                                                        IOMemoryDescriptor *	CBP,
                                                        bool			bufferRounding,
                                                        UInt32			bufferSize,
                                                        short			direction) = 0;

    // Interrupt
    virtual IOReturn		UIMCreateInterruptEndpoint(
                                                                short		functionAddress,
                                                                short		endpointNumber,
                                                                UInt8		direction,
                                                                short		speed,
                                                                UInt16		maxPacketSize,
                                                                short		pollingRate) = 0;

    virtual IOReturn 		UIMCreateInterruptTransfer( short			functionNumber,
                                                            short			endpointNumber,
                                                            IOUSBCompletion		completion,
                                                            IOMemoryDescriptor *	CBP,
                                                            bool			bufferRounding,
                                                            UInt32			bufferSize,
                                                            short			direction) = 0;

    // Isoch
    virtual IOReturn 		UIMCreateIsochEndpoint(
                                                        short		functionAddress,
                                                        short		endpointNumber,
                                                        UInt32		maxPacketSize,
                                                        UInt8		direction) = 0;

    virtual IOReturn 		UIMCreateIsochTransfer(
                                                        short			functionAddress,
                                                        short			endpointNumber,
                                                        IOUSBIsocCompletion	completion,
                                                        UInt8			direction,
                                                        UInt64			frameStart,
                                                        IOMemoryDescriptor *	pBuffer,
                                                        UInt32			frameCount,
                                                        IOUSBIsocFrame		*pFrames) = 0;

    virtual IOReturn 		UIMAbortEndpoint(
                                                short		functionNumber,
                                                short		endpointNumber,
                                                short		direction) = 0;

    virtual IOReturn 		UIMDeleteEndpoint(
                                                    short	functionNumber,
                                                    short	endpointNumber,
                                                    short	direction) = 0;
    
    virtual IOReturn 		UIMClearEndpointStall(
                                                        short		functionNumber,
                                                        short		endpointNumber,
                                                        short		direction) = 0;

    virtual void 		UIMRootHubStatusChange(void) = 0;

    static const IORegistryPlane	*gIOUSBPlane;
    
public:

    static IOUSBLog		*_log;
    inline IOCommandGate *GetCommandGate(void) { return _commandGate; }

    /*!
	@struct Endpoint
        Describes an endpoint of a device.
	Simply an easier to use version of the endpoint descriptor.
        @field descriptor The raw endpoint descriptor.
        @field number Endpoint number
	@field direction Endpoint direction: kUSBOut, kUSBIn, kUSBAnyDirn
	@field transferType Type of endpoint: kUSBControl, kUSBIsoc, kUSBBulk, kUSBInterrupt
	@field maxPacketSize Maximum packet size for endpoint
	@field interval Polling interval in milliseconds (only relevent for Interrupt endpoints)
    */
    struct Endpoint {
        IOUSBEndpointDescriptor	*	descriptor;
        UInt8 				number;
        UInt8				direction;	// in, out
        UInt8				transferType;	// cntrl, bulk, isoc, int
        UInt16				maxPacketSize;
        UInt8				interval;
    };

    // Implements IOService::getWorkLoop const member function
    virtual IOWorkLoop *	getWorkLoop() const;
    
    /*
     * Root hub methods
     * Only of interest to the IOUSBRootHubDevice object
     */
    virtual IOReturn 		GetRootHubDeviceDescriptor( IOUSBDeviceDescriptor *desc ) = 0;
    virtual IOReturn 		GetRootHubDescriptor( IOUSBHubDescriptor *desc ) = 0;
    virtual IOReturn 		SetRootHubDescriptor( OSData *buffer ) = 0;
    virtual IOReturn 		GetRootHubConfDescriptor( OSData *desc ) = 0;
    virtual IOReturn 		GetRootHubStatus( IOUSBHubStatus *status ) = 0;
    virtual IOReturn 		SetRootHubFeature( UInt16 wValue ) = 0;
    virtual IOReturn		ClearRootHubFeature( UInt16 wValue ) = 0;
    virtual IOReturn 		GetRootHubPortStatus( IOUSBHubPortStatus *status, UInt16 port ) = 0;
    virtual IOReturn 		SetRootHubPortFeature( UInt16 wValue, UInt16 port ) = 0;
    virtual IOReturn 		ClearRootHubPortFeature( UInt16 wValue, UInt16 port ) = 0;
    virtual IOReturn 		GetRootHubPortState( UInt8 *state, UInt16 port ) = 0;
    virtual IOReturn 		SetHubAddress( UInt16 wValue ) = 0;

    /*!
	@function openPipe
        Open a pipe to the specified device endpoint
        @param address Address of the device on the USB bus
	@param speed of the device: kUSBHighSpeed or kUSBLowSpeed
        @param endpoint description of endpoint to connect to
    */
    virtual IOReturn 		OpenPipe(   USBDeviceAddress 	address, 
                                            UInt8 		speed,
                                            Endpoint *		endpoint );
    /*!
        @function closePipe
        Close a pipe to the specified device endpoint
        @param address Address of the device on the USB bus
	@param endpoint description of endpoint
    */
    virtual IOReturn 		ClosePipe(
                                            USBDeviceAddress 	address,
                                            Endpoint * 		endpoint );

    // Controlling pipe state
    /*!
        @function abortPipe
        Abort pending I/O to/from the specified endpoint, causing them to complete
	with return code kIOReturnAborted
        @param address Address of the device on the USB bus
        @param endpoint description of endpoint
    */
    virtual IOReturn 		AbortPipe(
                                            USBDeviceAddress 	address,
                                            Endpoint * 		endpoint );
    /*!
        @function resetPipe
        Abort pending I/O and clear stalled state - this method is a combination of
	abortPipe and clearPipeStall
        @param address Address of the device on the USB bus
        @param endpoint description of endpoint
    */
    virtual IOReturn 		ResetPipe(
                                            USBDeviceAddress 	address,
                                            Endpoint * 		endpoint );
    /*!
        @function clearPipeStall
        Clear a pipe stall.
        @param address Address of the device on the USB bus
        @param endpoint description of endpoint
    */
    virtual IOReturn 		ClearPipeStall(
                                                USBDeviceAddress 	address,
                                                Endpoint * 		endpoint );

    // Transferring Data
    /*!
        @function read
        Read from an interrupt or bulk endpoint
	@param buffer place to put the transferred data
        @param address Address of the device on the USB bus
        @param endpoint description of endpoint
	@param completion describes action to take when buffer has been filled 
    */
    virtual IOReturn 		Read(
                                        IOMemoryDescriptor * 	buffer,
                                        USBDeviceAddress 	address,
                                        Endpoint *		endpoint,
                                        IOUSBCompletion *	completion );
    /*!
        @function write
        Write to an interrupt or bulk endpoint
        @param buffer place to get the transferred data
        @param address Address of the device on the USB bus
        @param endpoint description of endpoint
        @param completion describes action to take when buffer has been emptied
    */
    virtual IOReturn 		Write(
                                        IOMemoryDescriptor *	buffer,
                                        USBDeviceAddress 	address,
                                        Endpoint *		endpoint,
                                        IOUSBCompletion *	completion );

    /*!
        @function isocIO
        Read from or write to an isochronous endpoint
        @param buffer place to put the transferred data
        @param frameStart USB frame number of the frame to start transfer
        @param numFrames Number of frames to transfer
        @param frameList Bytes to transfer and result for each frame
        @param address Address of the device on the USB bus
        @param endpoint description of endpoint
        @param completion describes action to take when buffer has been filled
    */
    virtual IOReturn 		IsocIO(
                                        IOMemoryDescriptor * 	buffer,
                                        UInt64 			frameStart,
                                        UInt32 			numFrames,
                                        IOUSBIsocFrame *	frameList,
                                        USBDeviceAddress 	address,
                                        Endpoint *		endpoint,
                                        IOUSBIsocCompletion *	completion );
    /*!
        @function deviceRequest
        Make a control request to the specified endpoint
	There are two versions of this method, one uses a simple void *
        to point to the data portion of the transfer, the other uses an
	IOMemoryDescriptor to point to the data.
	@param request parameter block for the control request
	@param completion describes action to take when the request has been executed
        @param address Address of the device on the USB bus
	@param epNum endpoint number
    */
    virtual IOReturn 		DeviceRequest(
                                                IOUSBDevRequest *	request,
                                                IOUSBCompletion *	completion,
                                                USBDeviceAddress 	address, 
                                                UInt8 			epNum );
    virtual IOReturn 		DeviceRequest(
                                                IOUSBDevRequestDesc *	request,
                                                IOUSBCompletion *	completion,
                                                USBDeviceAddress 	address, 
                                                UInt8 			epNum );

    /*
     * Methods used by the hub driver to initialize a device
     */
    /*!
	@function AcquireDeviceZero
	Get the device zero lock - call this before resetting a device, to ensure there's
	only one device with address 0
    */
    virtual IOReturn 		AcquireDeviceZero( void );
    /*!
        @function ReleaseDeviceZero
        Release the device zero lock - call this to release the device zero lock,
	when there is no longer a device at address 0
    */
    virtual void 		ReleaseDeviceZero( void );

    /*!
        @function WaitForReleaseDeviceZero
        Block until the device zero lock is released
    */
    void			WaitForReleaseDeviceZero( void );

    /*!
        @function ConfigureDeviceZero
        create a pipe to the default pipe for the device at address 0
        @param maxPacketSize max packet size for the pipe
	@param speed Device speed
    */
    IOReturn			ConfigureDeviceZero( UInt8 maxPacketSize, UInt8 speed );
    /*!
        @function GetDeviceZeroDescriptor
        read the device descriptor of the device at address 0
	@param desc pointer to descriptor
        @param size how much of the descriptor to read
    */
    IOReturn			GetDeviceZeroDescriptor( IOUSBDeviceDescriptor *  desc, UInt16 size );
    /*!
        @function SetDeviceZeroAddress
        Set the device address of the device currently at address 0.
	When this routine returns, it's safe to release the device zero lock.
	@param address New address for the device
    */
    IOReturn			SetDeviceZeroAddress(USBDeviceAddress address);
    /*!
	@function MakeDevice
	Create a new device object for the device currently at address 0.
	This routine calls SetDeviceZeroAddress() with a new, unique, address for the device
	and adds the device into the registry.
	@param address pointer to the address for the device
	@result Pointer to the newly-created device, 0 if the object coudn't be created. 
    */
    IOUSBDevice *		MakeDevice(USBDeviceAddress *	address); 

     IOReturn			CreateDevice(
                                            IOUSBDevice *	device,
                                            USBDeviceAddress	deviceAddress,
                                            UInt8		maxPacketSize,
                                            UInt8		speed,
                                            UInt32		powerAvailable );
                                            
   /*!
	@function GetBandwidthAvailable
        Returns the available bandwidth (in bytes) per frame for
	isochronous transfers.
	@result maximum number of bytes that a new iso pipe could transfer
	per frame given current allocations.
    */
    virtual UInt32 		GetBandwidthAvailable( void ) = 0;

    /*!
        @function GetFrameNumber
        Returns the full current frame number.
        @result The frame number.
    */
    virtual UInt64 		GetFrameNumber( void ) = 0;

    /*!
        @function GetFrameNumber32
        Returns the least significant 32 bits of the frame number.
        @result The lsb 32 bits of the frame number.
    */
    virtual UInt32 		GetFrameNumber32( void ) = 0;

    // Debugger polled mode
    virtual void 		PollInterrupts( IOUSBCompletionAction safeAction = 0 ) = 0;
 
    virtual IOReturn 		PolledRead(
                                            short			functionNumber,
                                            short			endpointNumber,
                                            IOUSBCompletion		completion,
                                            IOMemoryDescriptor *	CBP,
                                            bool			bufferRounding,
                                            UInt32			bufferSize);
                                            
    OSMetaClassDeclareReservedUsed(IOUSBController,  0);
    virtual void UIMCheckForTimeouts(void);
    
    OSMetaClassDeclareReservedUsed(IOUSBController,  1);
    virtual IOReturn 		UIMCreateControlTransfer(   short		functionNumber,
                                                            short		endpointNumber,
                                                            IOUSBCommand*	command,
                                                            void*		CBP,
                                                            bool		bufferRounding,
                                                            UInt32		bufferSize,
                                                            short		direction);

    OSMetaClassDeclareReservedUsed(IOUSBController,  2);
    virtual IOReturn 		UIMCreateControlTransfer(   short			functionNumber,
                                                            short			endpointNumber,
                                                            IOUSBCommand*		command,
                                                            IOMemoryDescriptor*		CBP,
                                                            bool			bufferRounding,
                                                            UInt32			bufferSize,
                                                            short			direction);

    OSMetaClassDeclareReservedUsed(IOUSBController,  3);
    virtual IOReturn 		UIMCreateBulkTransfer(IOUSBCommand* command);

    OSMetaClassDeclareReservedUsed(IOUSBController,  4);
    virtual IOReturn 		UIMCreateInterruptTransfer(IOUSBCommand* command);

    /*!
        @function deviceRequest
        Make a control request to the specified endpoint
	There are two versions of this method, one uses a simple void *
        to point to the data portion of the transfer, the other uses an
	IOMemoryDescriptor to point to the data.
	@param request parameter block for the control request
	@param completion describes action to take when the request has been executed
        @param address Address of the device on the USB bus
	@param epNum endpoint number
    */
    OSMetaClassDeclareReservedUsed(IOUSBController,  5);
    virtual IOReturn 		DeviceRequest(  IOUSBDevRequest *	request,
                                                IOUSBCompletion *	completion,
                                                USBDeviceAddress 	address, 
                                                UInt8 			epNum,
						UInt32			noDataTimeout,
						UInt32			completionTimeout );
						
    OSMetaClassDeclareReservedUsed(IOUSBController,  6);
    virtual IOReturn 		DeviceRequest(  IOUSBDevRequestDesc *	request,
                                                IOUSBCompletion *	completion,
                                                USBDeviceAddress 	address, 
                                                UInt8 			epNum,
						UInt32			noDataTimeout,
						UInt32			completionTimeout );

    
    
    OSMetaClassDeclareReservedUsed(IOUSBController,  7);
    /*!
        @function read
        Read from an interrupt or bulk endpoint
	@param buffer place to put the transferred data
        @param address Address of the device on the USB bus
        @param endpoint description of endpoint
	@param completion describes action to take when buffer has been filled 
    */
    virtual IOReturn 		Read(   IOMemoryDescriptor * 	buffer,
                                        USBDeviceAddress 	address,
                                        Endpoint *		endpoint,
                                        IOUSBCompletion *	completion,
					UInt32			noDataTimeout,
					UInt32			completionTimeout );

    OSMetaClassDeclareReservedUsed(IOUSBController,  8);
    /*!
        @function write
        Write to an interrupt or bulk endpoint
        @param buffer place to get the transferred data
        @param address Address of the device on the USB bus
        @param endpoint description of endpoint
        @param completion describes action to take when buffer has been emptied
    */
    virtual IOReturn 		Write(  IOMemoryDescriptor *	buffer,
                                        USBDeviceAddress 	address,
                                        Endpoint *		endpoint,
                                        IOUSBCompletion *	completion,
					UInt32			noDataTimeout,
					UInt32			completionTimeout );

    OSMetaClassDeclareReservedUsed(IOUSBController,  9);
    virtual void free();

protected:
    	
    OSMetaClassDeclareReservedUsed(IOUSBController,  10);
    virtual void 		UIMRootHubStatusChange( bool abort ) = 0;

public:

    OSMetaClassDeclareReservedUsed(IOUSBController,  11);
    virtual IOReturn		CreateRootHubDevice( IOService * provider, IOUSBRootHubDevice ** rootHubDevice);
    
    OSMetaClassDeclareReservedUnused(IOUSBController,  12);
    OSMetaClassDeclareReservedUnused(IOUSBController,  13);
    OSMetaClassDeclareReservedUnused(IOUSBController,  14);
    OSMetaClassDeclareReservedUnused(IOUSBController,  15);
    OSMetaClassDeclareReservedUnused(IOUSBController,  16);
    OSMetaClassDeclareReservedUnused(IOUSBController,  17);
    OSMetaClassDeclareReservedUnused(IOUSBController,  18);
    OSMetaClassDeclareReservedUnused(IOUSBController,  19);
    
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Inline Functions

inline void IOUSBController::Complete(IOUSBCompletion	completion,
                                      IOReturn		status,
                                      UInt32		actualByteCount)
{
    if (completion.action)  (*completion.action)(completion.target,
                                                 completion.parameter,
                                                 status,
                                                 actualByteCount);
}


enum
{
    kUSBWatchdogTimeoutMS = 1000
};

#endif /* ! _IOKIT_IOUSBCONTROLLER_H */

