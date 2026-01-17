/*
 * Copyright (c) 1998-2006 Apple Computer, Inc. All rights reserved.
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

//================================================================================================
//
//   Headers
//
//================================================================================================
//
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


//================================================================================================
//
//   Types and Constants
//
//================================================================================================
//
enum
{
    kErrataCMDDisableTestMode		= (1 << 0),		// turn off UHCI test mode
    kErrataOnlySinglePageTransfers	= (1 << 1),		// Don't cross page boundaries in a single transfer
    kErrataRetryBufferUnderruns		= (1 << 2),		// Don't cross page boundaries in a single transfer
    kErrataLSHSOpti					= (1 << 3),		// Don't cross page boundaries in a single transfer
    kErrataDisableOvercurrent		= (1 << 4),		// Always set the NOCP bit in rhDescriptorA register
    kErrataLucentSuspendResume		= (1 << 5),		// Don't allow port suspend at the root hub
    kErrataNeedsWatchdogTimer		= (1 << 6),		// Use Watchdog timer to reset confused controllers
    kErrataNeedsPortPowerOff		= (1 << 7),		// Power off the ports and back on again to clear weird status.
    kErrataAgereEHCIAsyncSched		= (1 << 8),		// needs workaround for Async Sched bug
    kErrataNECOHCIIsochWraparound	= (1 << 9),		// needs workaround for NEC isoch buffer wraparound problem
	kErrataNECIncompleteWrite		= (1 << 10),	// needs workaround for NEC bits not sticking (errata IBB-2UE-00030 Jun 23 2005)
	kErrataICH6PowerSequencing		= (1 << 11),	// needs special power sequencing for early Transition machines
	kErrataICH7ISTBuffer			= (1 << 12),	// buffer for Isochronous Scheduling Threshold
	kErrataUHCISupportsOvercurrent	= (1 << 13),	// UHCI controller supports overcurrent detection
	kErrataNeedsOvercurrentDebounce = (1 << 14),	// The overcurrent indicator should be debounced by 10ms
	kErrataSupportsPortResumeEnable = (1 << 15)		// UHCI has resume enable bits at config address 0xC4
};

enum
{
    kUSBWatchdogTimeoutMS = 1000
};


/*!
    @struct
    @discussion This table contains the list of errata that are necessary for known problems with particular devices.
    The format is vendorID, product ID, lowest revisionID needing errata, highest rev needing errata, errataBits.
    The result of all matches is ORed together, so more than one entry may match.
    Typically for a given errata a list of revisions that this applies to is supplied.
     @field vendID      The Vendor ID of the device
     @field deviceID    Product ID of device
     @field revisionLo  Lowest product revsion to apply errata to
     @field revisionHi  Highest product revision to apply errata to
     @field errata      Bit field flagging which errata to apply to device.
*/

struct ErrataListEntryStruct
{
    UInt16 				vendID;
    UInt16 				deviceID;
    UInt16 				revisionLo;
    UInt16 				revisionHi;
    UInt32 				errata;
};

typedef struct ErrataListEntryStruct  ErrataListEntry, *ErrataListEntryPtr;


//================================================================================================
//
//   Routines used to implement synchronous I/O
//
//================================================================================================
//
void IOUSBSyncCompletion(void *target, void * parameter, IOReturn status, UInt32 bufferSizeRemaining);

void  IOUSBSyncIsoCompletion(void *target, void * parameter, IOReturn status, IOUSBIsocFrame *pFrames);


//================================================================================================
//
//   Forward Declarations
//
//================================================================================================
//
class IOUSBDevice;
class IOUSBLog;
class IOUSBRootHubDevice;
class IOMemoryDescriptor;


//================================================================================================
//
//   IOUSBController Class
//
//================================================================================================
//
/*!
    @class IOUSBController
    @abstract Base class for USB hardware driver
    @discussion Not many directly useful methods for USB device driver writers,
    IOUSBDevice, IOUSBInterface and IOUSBPipe provide more useful abstractions.
    The bulk of this class interfaces between IOKit and the low-level UIM, which is
    based on the MacOS9 UIM. To impliment a new controller type, subclass
    IOUSBController and impiment all the "UIM functions". AppleUSBOHCI
    is an example of this implementing all the functions necessary to drive an
    OHCI controller.
*/
class IOUSBController : public IOUSBBus
{
    OSDeclareAbstractStructors(IOUSBController)
    friend class IOUSBControllerV2;

protected:

    IOUSBWorkLoop *		_workLoop;
    IOCommandGate *		_commandGate;
    IOUSBRootHubDevice *	_rootHubDevice;
    UInt32			_devZeroLock;
    static UInt32		_busCount;
    static bool			gUsedBusIDs[256];
    
    struct ExpansionData 
    {
	IOCommandPool		*freeUSBCommandPool;
	IOCommandPool		*freeUSBIsocCommandPool;
        IOTimerEventSource	*watchdogUSBTimer;
        bool			_terminating;
        bool			_watchdogTimerActive;
        bool			_pcCardEjected;
        UInt32			_busNumber;
        UInt32			_currentSizeOfCommandPool;
        UInt32			_currentSizeOfIsocCommandPool;
        UInt8			_controllerSpeed;	// Controller speed, passed down for splits
        thread_call_t	_terminatePCCardThread;
        bool			_addressPending[128];
		SInt32			_activeIsochTransfers;				// isochronous transfers in the queue
    };
    ExpansionData *_expansionData;

    //
    #define _freeUSBCommandPool			_expansionData->freeUSBCommandPool
    #define _freeUSBIsocCommandPool		_expansionData->freeUSBIsocCommandPool
    #define _watchdogUSBTimer			_expansionData->watchdogUSBTimer
    #define _controllerTerminating		_expansionData->_terminating
    #define _watchdogTimerActive		_expansionData->_watchdogTimerActive
    #define _pcCardEjected			_expansionData->_pcCardEjected
    #define _busNumber				_expansionData->_busNumber
    #define _currentSizeOfCommandPool		_expansionData->_currentSizeOfCommandPool
    #define _currentSizeOfIsocCommandPool	_expansionData->_currentSizeOfIsocCommandPool
    #define _controllerSpeed			_expansionData->_controllerSpeed
    #define _terminatePCCardThread		_expansionData->_terminatePCCardThread
    #define _addressPending			_expansionData->_addressPending

    // The following methods do not use and upper case initial letter because they are part of IOKit
    //

public:
    virtual bool 		init( OSDictionary *  propTable );
    virtual bool 		start( IOService *  provider );
    virtual void 		stop( IOService * provider );
    virtual bool 		finalize(IOOptionBits options);
    virtual IOReturn 		message( UInt32 type, IOService * provider,  void * argument = 0 );

protected:
		
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
                                            
    static IOReturn 		DoLowLatencyIsocTransfer(	
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
                                                    
    static void			LowLatencyIsocCompletionHandler(
                                                    OSObject *		target,
                                                    void * 		parameter,
                                                    IOReturn		status,
                                                    IOUSBLowLatencyIsocFrame	*pFrames );
                                                    
    static void			WatchdogTimer(OSObject *target, IOTimerEventSource *sender);

    static void 		TerminatePCCard(OSObject *target);

    static IOReturn		ProtectedDevZeroLock(OSObject *target, void* lock, void *, void *, void*);

    USBDeviceAddress		GetNewAddress( void );
    
    IOReturn    		ControlTransaction( IOUSBCommand *  command );
    
    IOReturn    		InterruptTransaction( IOUSBCommand *  command );
    
    IOReturn    		BulkTransaction( IOUSBCommand *	command );
    
    IOReturn    		IsocTransaction( IOUSBIsocCommand *  command );
    
    IOReturn    		LowLatencyIsocTransaction( IOUSBIsocCommand *  command );
    
    void 			FreeCommand( IOUSBCommand *  command );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Invokes the specified completion action of the request.  If
    // the completion action is unspecified, no action is taken.
    void 			Complete(
                     IOUSBCompletion	completion,
                     IOReturn		status,
                     UInt32		actualByteCount = 0 );

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Invokes the specified completion action of the request.  If
    // the completion action is unspecified, no action is taken.
    void	CompleteWithTimeStamp (
                                IOUSBCompletionWithTimeStamp		completion,
                                IOReturn				status,
                                UInt32					actualByteCount,
                                AbsoluteTime				timeStamp);

    

    //
    // UIM methods
    //

/*!
    @function UIMInitialize
    @abstract UIM function, initialise the controller and UIM data structures.
*/
    virtual IOReturn 		UIMInitialize( IOService * provider ) = 0;
    
/*!
    @function UIMFinalize
    @abstract UIM function, finalise the controller and UIM data structures prior to removal.
*/
    virtual IOReturn 		UIMFinalize() = 0;

    // Control
/*!
    @function UIMCreateControlEndpoint
    @abstract UIM function, create a control endpoint for the controller.
    @param functionNumber  The USB device ID of the device for this endpoint
    @param endpointNumber  The endpoint number for this endpoint
    @param maxPacketSize   Maximum packet size of this endpoint
    @param speed           speed of the device: kUSBDeviceSpeedLow or kUSBDeviceSpeedFull 
*/
    virtual IOReturn 		UIMCreateControlEndpoint(
                                                            UInt8	functionNumber,
                                                            UInt8	endpointNumber,
                                                            UInt16	maxPacketSize,
                                                            UInt8	speed) = 0;

/* Note: this function has been superceded. */
    virtual IOReturn 		UIMCreateControlTransfer(   short		functionNumber,
                                                            short		endpointNumber,
                                                            IOUSBCompletion	completion,
                                                            void *		CBP,
                                                            bool		bufferRounding,
                                                            UInt32		bufferSize,
                                                            short		direction) = 0;

/*!
    @function UIMCreateControlTransfer
    @abstract UIM function, Do a transfer on a control endpoint.
                This method supercedes the method which takes a void * parameter.
    @param functionNumber  The USB device ID of the device to perform the transaction with
    @param endpointNumber  The endpoint number for the transaction
    @param completion      Action to perform when I/O completes
    @param CBP             Memory descriptor describing the buffer to transfer. Will never describe
                             memory which has disjoint packets.
    @param bufferRounding  If true, short packets are OK and do not cause an error
    @param bufferSize      Size of the data to transfer in the data phase. (C
    @param direction       Specifies direction and PID for transaction. kUSBIn, KUSBOut (DATA PID) or kUSBSetup (SETUP PID).
*/
    virtual IOReturn 		UIMCreateControlTransfer(   short			functionNumber,
                                                            short			endpointNumber,
                                                            IOUSBCompletion		completion,
                                                            IOMemoryDescriptor *	CBP,
                                                            bool			bufferRounding,
                                                            UInt32			bufferSize,
                                                            short			direction) = 0;
    
    // Bulk
/*!
    @function UIMCreateBulkEndpoint
    @abstract UIM function, create a bulk endpoint for the controller.
    @param functionNumber  The USB device ID of the device for this endpoint
    @param endpointNumber  The endpoint number for this endpoint
    @param direction       Specifies direction for the endpoint. kUSBIn or KUSBOut.
    @param speed           speed of the device: kUSBDeviceSpeedLow or kUSBDeviceSpeedFull 
    @param maxPacketSize   Maximum packet size of this endpoint
*/
    virtual IOReturn 		UIMCreateBulkEndpoint(
                                                        UInt8		functionNumber,
                                                        UInt8		endpointNumber,
                                                        UInt8		direction,
                                                        UInt8		speed,
                                                        UInt8		maxPacketSize) = 0;

/* Note: this function has been superceded. */
    virtual IOReturn 		UIMCreateBulkTransfer(  short			functionNumber,
                                                        short			endpointNumber,
                                                        IOUSBCompletion		completion,
                                                        IOMemoryDescriptor *	CBP,
                                                        bool			bufferRounding,
                                                        UInt32			bufferSize,
                                                        short			direction) = 0;

    // Interrupt
/*!
    @function UIMCreateInterruptEndpoint
    @abstract UIM function, create an interrupt endpoint for the controller.
    @param functionNumber  The USB device ID of the device for this endpoint
    @param endpointNumber  The endpoint number for this endpoint
    @param direction       Specifies direction for the endpoint. kUSBIn or KUSBOut.
    @param speed           speed of the device: kUSBDeviceSpeedLow or kUSBDeviceSpeedFull 
    @param maxPacketSize   Maximum packet size of this endpoint
    @param pollingRate     The maximum polling interval from the endpoint descriptor.
*/
    virtual IOReturn		UIMCreateInterruptEndpoint(
                                                                short		functionAddress,
                                                                short		endpointNumber,
                                                                UInt8		direction,
                                                                short		speed,
                                                                UInt16		maxPacketSize,
                                                                short		pollingRate) = 0;

/* Note: this function has been superceded. */
    virtual IOReturn 		UIMCreateInterruptTransfer( short			functionNumber,
                                                            short			endpointNumber,
                                                            IOUSBCompletion		completion,
                                                            IOMemoryDescriptor *	CBP,
                                                            bool			bufferRounding,
                                                            UInt32			bufferSize,
                                                            short			direction) = 0;

    // Isoch
/*!
	@function UIMCreateIsochEndpoint
    @abstract Create an Isochronous endpoint in the controller.
    @param functionNumber  The USB device ID of the device for this endpoint
    @param endpointNumber  The endpoint number for this endpoint
    @param maxPacketSize   Maximum packet size of this endpoint
    @param direction       Specifies direction for the endpoint. kUSBIn or KUSBOut.
*/
    virtual IOReturn 		UIMCreateIsochEndpoint(
                                                        short		functionAddress,
                                                        short		endpointNumber,
                                                        UInt32		maxPacketSize,
                                                        UInt8		direction) = 0;

/*!
    @function UIMCreateIsochTransfer
    @abstract UIM function, Do a transfer on an Isocchronous endpoint.
    @param functionNumber  The USB device ID of the device to perform the transaction with
    @param endpointNumber  The endpoint number for the transaction
    @param completion      Action to perform when I/O completes
    @param direction       Specifies direction for transfer. kUSBIn or KUSBOut.
    @param frameStart      The frame number in which to start the transactions
    @param pBuffer         describes memory buffer. 
    @param frameCount      number of frames to do transactions in
    @param pFrames         Describes transactions in individual frames, gives sizes and reults for transactions.
*/
    virtual IOReturn 		UIMCreateIsochTransfer(
                                                        short			functionAddress,
                                                        short			endpointNumber,
                                                        IOUSBIsocCompletion	completion,
                                                        UInt8			direction,
                                                        UInt64			frameStart,
                                                        IOMemoryDescriptor *	pBuffer,
                                                        UInt32			frameCount,
                                                        IOUSBIsocFrame		*pFrames) = 0;

/*!
    @function UIMAbortEndpoint
    @abstract UIM function  Abort the specified endpoint, return all transactions queued on it.
    @param functionNumber  The USB device ID of the device to Abort
    @param endpointNumber  The endpoint number to Abort
    @param direction       Specifies direction of the endpoint for uniqueness. kUSBIn or KUSBOut.
*/
    virtual IOReturn 		UIMAbortEndpoint(
                                                short		functionNumber,
                                                short		endpointNumber,
                                                short		direction) = 0;

/*!
    @function UIMDeleteEndpoint
    @abstract UIM function  Delete the specified endpoint, returning all transactions queued on it.
    @param functionNumber  The USB device ID of the device to Delete
    @param endpointNumber  The endpoint number to Delete
    @param direction       Specifies direction of the endpoint for uniqueness. kUSBIn or KUSBOut.
*/
    virtual IOReturn 		UIMDeleteEndpoint(
                                                    short	functionNumber,
                                                    short	endpointNumber,
                                                    short	direction) = 0;
    
/*!
    @function UIMClearEndpointStall
    @abstract UIM function  Clear stall on the specified endpoint, set data toggle to zero,
                              return all transactions queued on it.
    @param functionNumber  The USB device ID of the device to Clear
    @param endpointNumber  The endpoint number to Clear
    @param direction       Specifies direction of the endpoint for uniqueness. kUSBIn or KUSBOut.
*/
    virtual IOReturn 		UIMClearEndpointStall(
                                                        short		functionNumber,
                                                        short		endpointNumber,
                                                        short		direction) = 0;

/*!
    @function UIMClearEndpointStall
    @abstract UIM function  UIMRootHubStatusChange This method gets called when there is a 
                change in the root hub status or a change in the status of one of the ports.
*/
    virtual void 		UIMRootHubStatusChange(void) = 0;

    static const IORegistryPlane	*gIOUSBPlane;
    
public:

    static IOUSBLog		*_log;
    IOCommandGate *GetCommandGate(void);

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
/*!
    @function GetRootHubDeviceDescriptor
    @abstract UIM function, return the device descriptor of the simulated root hub device
                           As GET_DESCRIPTOR control request for device descrptor
    @param  desc   Descriptor structure to return data in
*/
    virtual IOReturn 		GetRootHubDeviceDescriptor( IOUSBDeviceDescriptor *desc ) = 0;
    
/*!
    @function GetRootHubDescriptor
    @abstract UIM function, return the hub descriptor of the simulated root hub device
                           As GET_DESCRIPTOR control request for hub descrptor
    @param  desc   Descriptor structure to return data in
*/
    virtual IOReturn 		GetRootHubDescriptor( IOUSBHubDescriptor *desc ) = 0;
    
/*!
    @function SetRootHubDescriptor
    @abstract UIM function, optional. Set the hub descriptor data.
                           As SET_DESCRIPTOR control request for hub descrptor
    @param  buffer   Descriptor data
*/
    virtual IOReturn 		SetRootHubDescriptor( OSData *buffer ) = 0;
    
/*!
    @function GetRootHubConfDescriptor
    @abstract UIM function, retrun the configuration descriptor of the simulated root hub device
                           As GET_DESCRIPTOR control request for configuration descrptor
    @param  desc   Descriptor structure to return data in
*/
    virtual IOReturn 		GetRootHubConfDescriptor( OSData *desc ) = 0;
    
/*!
    @function GetRootHubStatus
    @abstract UIM function, get the status of the root hub. As GET_STATUS control request to device.
    @param status  Status structure to return
*/
    virtual IOReturn 		GetRootHubStatus( IOUSBHubStatus *status ) = 0;
    
/*!
    @function SetRootHubFeature
    @abstract UIM function, set feature of root hub, As SET_FEATURE control request.
    @param wValue  The feature to set, as would be transferred in wValue field of SETUP packet.
*/
    virtual IOReturn 		SetRootHubFeature( UInt16 wValue ) = 0;
    
/*!
    @function ClearRootHubFeature
    @abstract UIM function, set feature of root hub, As CLEAR_FEATURE control request.
    @param wValue  The feature to clear, as would be transferred in wValue field of SETUP packet.
*/
    virtual IOReturn		ClearRootHubFeature( UInt16 wValue ) = 0;
    
/*!
    @function GetRootHubPortStatus
    @abstract UIM function, get the status of a root hub port. As GET_STATUS control request to the port.
    @param status  Status structure to return
    @param port    Port to get status for.
*/
    virtual IOReturn 		GetRootHubPortStatus( IOUSBHubPortStatus *status, UInt16 port ) = 0;
    
/*!
    @function SetRootHubPortFeature
    @abstract UIM function, set feature of a root hub port, As SET_FEATURE control request to a port.
    @param wValue  The feature to set, as would be transferred in wValue field of SETUP packet.
    @param port    Port to set feature for
*/
    virtual IOReturn 		SetRootHubPortFeature( UInt16 wValue, UInt16 port ) = 0;
    
/*!
    @function ClearRootHubPortFeature
    @abstract UIM function, clear feature of a root hub port, As CLEAR_FEATURE control request to a port.
    @param wValue  The feature to clear, as would be transferred in wValue field of SETUP packet.
    @param port    Port to clear feature for
*/
    virtual IOReturn 		ClearRootHubPortFeature( UInt16 wValue, UInt16 port ) = 0;
    
/*!
    @function ClearRootHubPortFeature
    @abstract UIM function, Impliments GET_BUS_STATE control request, now obsolete.
*/
    virtual IOReturn 		GetRootHubPortState( UInt8 *state, UInt16 port ) = 0;
    
/*!
    @function SetHubAddress
    @abstract UIM function, set the address of the simulated root hub device, as SET_ADDRESS
    @param wValue	 New address for root hub.
*/
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
/*!
    @function UIMCreateBulkTransfer
    @abstract UIM function, Do a transfer on a bulk endpoint.
                This method supercedes the method which takes multiple parameters.
    @param command  paramters for transfer.
*/
    virtual IOReturn 		UIMCreateBulkTransfer(IOUSBCommand* command);

    OSMetaClassDeclareReservedUsed(IOUSBController,  4);
/*!
    @function UIMCreateInterruptTransfer
    @abstract UIM function, Do a transfer on an interrupt endpoint.
                This method supercedes the method which takes multiple parameters.
    @param command  paramters for transfer.
*/
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

    // this should really not be using a padding slot, since free is in our superclas, but we shipped this way so now we need to leave it.
    OSMetaClassDeclareReservedUsed(IOUSBController,  9);
    virtual void free();

protected:
    	
    OSMetaClassDeclareReservedUsed(IOUSBController,  10);
    virtual void 		UIMRootHubStatusChange( bool abort ) = 0;

public:

    OSMetaClassDeclareReservedUsed(IOUSBController,  11);
    virtual IOReturn CreateRootHubDevice( IOService * provider, IOUSBRootHubDevice ** rootHubDevice);
    
    OSMetaClassDeclareReservedUsed(IOUSBController,  12);
    /*!
        @function Read
        Read from an interrupt or bulk endpoint
	@param buffer place to put the transferred data
        @param address Address of the device on the USB bus
        @param endpoint description of endpoint
	@param completion describes action to take when buffer has been filled
	@param noDataTimeout number of milliseconds of no data movement before the request is aborted
	@param completionTimeout number of milliseonds after the command is on the bus in which it must complete
	@param reqCount number of bytes requested for the transfer (must not be greater than the length of the buffer)
    */
    virtual IOReturn 		Read(   IOMemoryDescriptor * 	buffer,
                                        USBDeviceAddress 	address,
                                        Endpoint *		endpoint,
                                        IOUSBCompletion *	completion,
					UInt32			noDataTimeout,
					UInt32			completionTimeout,
					IOByteCount		reqCount );

    OSMetaClassDeclareReservedUsed(IOUSBController,  13);
    /*!
        @function Write
        Write to an interrupt or bulk endpoint
        @param buffer place to get the transferred data
        @param address Address of the device on the USB bus
        @param endpoint description of endpoint
        @param completion describes action to take when buffer has been emptied
	@param noDataTimeout number of milliseconds of no data movement before the request is aborted
	@param completionTimeout number of milliseonds after the command is on the bus in which it must complete
	@param reqCount number of bytes requested for the transfer (must not be greater than the length of the buffer)
    */
    virtual IOReturn 		Write(  IOMemoryDescriptor *	buffer,
                                        USBDeviceAddress 	address,
                                        Endpoint *		endpoint,
                                        IOUSBCompletion *	completion,
					UInt32			noDataTimeout,
					UInt32			completionTimeout,
					IOByteCount		reqCount );

    OSMetaClassDeclareReservedUsed(IOUSBController,  14);
    
    virtual IOReturn GetRootHubStringDescriptor(UInt8	index, OSData *desc) = 0;
    
    OSMetaClassDeclareReservedUsed(IOUSBController,  15);
    /*!
        @function IsocIO
        Read from or write to an isochronous endpoint
        @param buffer place to put the transferred data
        @param frameStart USB frame number of the frame to start transfer
        @param numFrames Number of frames to transfer
        @param frameList Bytes to transfer and result for each frame
        @param address Address of the device on the USB bus
        @param endpoint description of endpoint
        @param completion describes action to take when buffer has been filled
        @param updateFrequency describes how often to update the framelist once the transfer has completed (in ms)
    */
    virtual IOReturn IsocIO(  IOMemoryDescriptor * 			buffer,
                                        UInt64 				frameStart,
                                        UInt32 				numFrames,
                                        IOUSBLowLatencyIsocFrame *	frameList,
                                        USBDeviceAddress 		address,
                                        Endpoint *			endpoint,
                                        IOUSBLowLatencyIsocCompletion *	completion,
                                        UInt32				updateFrequency );

    OSMetaClassDeclareReservedUsed(IOUSBController,  16);
    
    /*!
    @function UIMCreateIsochTransfer
    @abstract UIM function, Do a transfer on an Isocchronous endpoint.
    @param functionNumber  The USB device ID of the device to perform the transaction with
    @param endpointNumber  The endpoint number for the transaction
    @param completion      Action to perform when I/O completes
    @param direction       Specifies direction for transfer. kUSBIn or KUSBOut.
    @param frameStart      The frame number in which to start the transactions
    @param pBuffer         describes memory buffer. 
    @param frameCount      number of frames to do transactions in
    @param pFrames         Describes transactions in individual frames, gives sizes and reults for transactions.
    @param updateFrequency Describes how often we update the frameList parameters (in ms)
*/
    virtual IOReturn 		UIMCreateIsochTransfer(
                                                        short			functionAddress,
                                                        short			endpointNumber,
                                                        IOUSBIsocCompletion	completion,
                                                        UInt8			direction,
                                                        UInt64			frameStart,
                                                        IOMemoryDescriptor *	pBuffer,
                                                        UInt32			frameCount,
                                                        IOUSBLowLatencyIsocFrame *pFrames,
                                                        UInt32			updateFrequency);


    OSMetaClassDeclareReservedUsed(IOUSBController,  17);
    virtual IOReturn 		CheckForDisjointDescriptor(IOUSBCommand *command, UInt16 maxPacketSize);
    
#if !(defined(__ppc__) && defined(KPI_10_4_0_PPC_COMPAT))
    /*!
		@function UIMCreateIsochTransfer
	 @abstract UIM function, Do a transfer on an Isocchronous endpoint.
	 @param command  an IOUSBIsocCommand object with all the necessary information
	 */
    OSMetaClassDeclareReservedUsed(IOUSBController,  18);
	virtual IOReturn UIMCreateIsochTransfer(IOUSBIsocCommand *command);
#else
    OSMetaClassDeclareReservedUnused(IOUSBController,  18);
#endif

    OSMetaClassDeclareReservedUnused(IOUSBController,  19);
    
protected:
    void	IncreaseIsocCommandPool();
    void 	IncreaseCommandPool();
    void	ParsePCILocation(const char *str, int *deviceNum, int *functionNum);
    int		ValueOfHexDigit(char c);
};

#endif /* ! _IOKIT_IOUSBCONTROLLER_H */

