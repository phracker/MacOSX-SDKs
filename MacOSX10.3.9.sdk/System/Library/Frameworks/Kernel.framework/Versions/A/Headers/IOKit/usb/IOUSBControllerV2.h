/*
 * Copyright (c) 1998-2003 Apple Computer, Inc. All rights reserved.
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

#ifndef __OPEN_SOURCE__
/*
 *
 *
 *	$Log: IOUSBControllerV2.h,v $
 *	Revision 1.12.36.1  2004/10/25 15:37:38  nano
 *	HS Isoch fixes to PantherUpdate.
 *	
 *	Revision 1.12.100.1  2004/10/20 15:27:38  nano
 *	Potential submissions to Sandbox -- create their own branch
 *	
 *	Bug #:
 *	<rdar://problem/3826068> USB devices on a P30 attached to Q88 do not function after restart
 *	<rdar://problem/3779852> Q16B EVT Build run in fail Checkconfig Bluetooth *2
 *	<rdar://problem/3816739>IOUSBFamily needs to support polling interval for High Speed devices
 *	<rdar://problem/3816743> Low latency for hi-speed API do not fill frTimeStamp.hi and low in completion.
 *	<rdar://problem/3816749> Low latency for hi-speed API incorrectly treats buffer striding across mem-page
 *	
 *	Submitted by:
 *	Reviewed by:
 *	
 *	Revision 1.14.42.1  2004/09/21 18:08:29  rhoads
 *	checking preliminary stuff in for safe keeping
 *	
 *	Revision 1.14.50.1  2004/10/08 17:13:39  nano
 *	Branch for fixes for:
 *	Bug #:
 *	3791223: IOUSBFamily needs to support polling interval for High Speed devices
 *	3809181: Low latency for hi-speed API do not fill frTimeStamp.hi and low in completion.
 *	3809184: Low latency for hi-speed API incorrectly treats buffer striding across mem-page
 *	
 *	Submitted by:
 *	Reviewed by:
 *	
 *	Revision 1.15  2004/09/23 02:19:50  rhoads
 *	changes for hisgh speed isoch
 *	
 *	Revision 1.14.42.1  2004/09/21 18:08:29  rhoads
 *	checking preliminary stuff in for safe keeping
 *	
 *	Revision 1.14  2004/05/17 21:52:50  nano
 *	Add timeStamp and useTimeStamp to our commands.
 *	
 *	Revision 1.13.16.1  2004/05/17 15:57:27  nano
 *	API Changes for Tiger
 *	
 *	Revision 1.13  2004/02/03 22:09:49  nano
 *	Fix <rdar://problem/3548194>: Remove $ Id $ from source files to prevent conflicts
 *	
 *	Revision 1.12.48.2  2004/04/28 17:26:09  nano
 *	Remove $ ID $ so that we don't get conflicts on merge
 *	
 *	Revision 1.12.48.1  2003/11/04 22:27:37  nano
 *	Work in progress to add time stamping to interrupt handler
 *	
 *	Revision 1.12  2003/08/20 19:41:40  nano
 *	
 *	Bug #:
 *	New version's of Nima's USB Prober (2.2b17)
 *	3382540  Panther: Ejecting a USB CardBus card can freeze a machine
 *	3358482  Device Busy message with Modems and IOUSBFamily 201.2.14 after sleep
 *	3385948  Need to implement device recovery on High Speed Transaction errors to full speed devices
 *	3377037  USB EHCI: returnTransactions can cause unstable queue if transactions are aborted
 *	
 *	Also, updated most files to use the id/log functions of cvs
 *	
 *	Submitted by: nano
 *	Reviewed by: rhoads/barryt/nano
 *	
 */
#endif
#ifndef _IOKIT_IOUSBCONTROLLERV2_H
#define _IOKIT_IOUSBCONTROLLERV2_H

#include <IOKit/usb/IOUSBController.h>

enum
{
    kUSBHSHubCommandAddHub	= 1,
    kUSBHSHubCommandRemoveHub	= 2,
    
    kUSBHSHubFlagsMultiTT	= 1
};


/*!
    @class IOUSBControllerV2
    @abstract subclass of the IOUSBController to provide support for high speed 
                devices and split transactions.
    @discussion The IOUSBController class provide sufficient functionality to 
                work with full (12Mb/s) and low (1.5Mb/s) devices. IOUSBControllerV2
                introduces the support for high (480Mb/s) speed devices from the
                USB 2.0 spec. In particular IOUSBControllerV2 indicates the high
                speed hub a full or low speed device is attached to so that split
                transactions can be directed to the hub at high speed to be forwarded
                to the full or low speed device by the hub.
                It also gives support for bulk endoints of greater than 256 bytes.
*/

class IOUSBControllerV2 : public IOUSBController
{
    OSDeclareAbstractStructors(IOUSBControllerV2)

protected:
    
    // These for keeping track of high speed ancestor to allow controller to do splits.
    //
    UInt8 _highSpeedHub[128];
    UInt8 _highSpeedPort[128];

    struct V2ExpansionData { 
	UInt8 _multiTT[128];
	IOUSBCommand 	*ClearTTCommand;
	};
    V2ExpansionData * _v2ExpansionData;

    // Super's expansion data
    #define _freeUSBCommandPool		_expansionData->freeUSBCommandPool
    #define _freeUSBIsocCommandPool	_expansionData->freeUSBIsocCommandPool
    #define _watchdogUSBTimer		_expansionData->watchdogUSBTimer
    #define _controllerTerminating	_expansionData->_terminating
    #define _watchdogTimerActive	_expansionData->_watchdogTimerActive
    #define _pcCardEjected		_expansionData->_pcCardEjected
    #define _busNumber			_expansionData->_busNumber
    #define _currentSizeOfCommandPool	_expansionData->_currentSizeOfCommandPool
    #define _currentSizeOfIsocCommandPool	_expansionData->_currentSizeOfIsocCommandPool
    #define _controllerSpeed		_expansionData->_controllerSpeed

    virtual bool 		init( OSDictionary *  propTable );

    /*!
	@function openPipe
        Open a pipe to the specified device endpoint
        @param address Address of the device on the USB bus
        @param speed of the device: kUSBDeviceSpeedLow, kUSBDeviceSpeedFull or kUSBDeviceSpeedHigh
        @param endpoint description of endpoint to connect to
    */
    virtual IOReturn 		OpenPipe(   USBDeviceAddress 	address, 
                                            UInt8 		speed,
                                            Endpoint *		endpoint );
    
    static IOReturn  DoCreateEP(OSObject *owner,
                           void *arg0, void *arg1,
                           void *arg2, void *arg3);

    static void		clearTTHandler( 
			    OSObject *	target,
                            void *	parameter,
                            IOReturn	status,
                            UInt32	bufferSizeRemaining );

public:

/*!
    @function CreateDevice
    @abstract Create a new device as IOUSBController, making a note of the
                high speed hub device ID and port number the full/low speed
                device is attached to.
    @param newDevice       new device object to work with
    @param deviceAddress   USB device ID
    @param maxPacketSize   max packet size of endpoint zero
    @param speed           speed of the device kUSBDeviceSpeedLow, kUSBDeviceSpeedFull, kUSBDeviceSpeedHigh
    @param powerAvailable  power available to the device 
    @param hub             USB ID of hub the device is immediatly attached to. (Not necessarily high speed)
    @param port            port number of port the device is attached to.
*/
    virtual  IOReturn CreateDevice(	IOUSBDevice 		*newDevice,
                                    USBDeviceAddress	deviceAddress,
                                    UInt8		 	maxPacketSize,
                                    UInt8			speed,
                                    UInt32			powerAvailable,
                                    USBDeviceAddress		hub,
                                    int      port);

/*!
	@function ConfigureDeviceZero
    @abstract configure pipe zero of device zero, as IOUSBController, but also keeping 
                 note of high speed hub device is attached to.
    @param maxPacketSize  max packet size for the pipe
    @param speed           speed of the device kUSBDeviceSpeedLow, kUSBDeviceSpeedFull, kUSBDeviceSpeedHigh
    @param hub            USB ID of hub the device is immediatly attached to.  (Not necessarily high speed)
    @param port           port number of port the device is attached to.
*/
    virtual  IOReturn ConfigureDeviceZero(UInt8 maxPacketSize, UInt8 speed, USBDeviceAddress hub, int port);

/*!
	@function UIMCreateControlEndpoint
    @abstract Create an endpoint in the controller to do control transactions.
    @param functionNumber  USB device ID of device
    @param endpointNumber  endpoint address of the endpoint in the device
    @param maxPacketSize   maximum packet size of this endpoint
    @param speed           speed of the device kUSBDeviceSpeedLow, kUSBDeviceSpeedFull, kUSBDeviceSpeedHigh
    @param highSpeedHub    If speed is not kUSBDeviceSpeedHigh, the address of the high speed hub to
                           address split transactions to.
    @param highSpeedPort   If speed is not kUSBDeviceSpeedHigh, the hub port to address split transactions to
*/
    virtual IOReturn 		UIMCreateControlEndpoint(
                                                            UInt8	functionNumber,
                                                            UInt8	endpointNumber,
                                                            UInt16	maxPacketSize,
                                                            UInt8	speed,
                                                            USBDeviceAddress highSpeedHub,
                                                            int      highSpeedPort) = 0;

/*!
	@function UIMCreateBulkEndpoint
    @abstract Create an endpoint in the controller to do bulk transactions.
    @param functionNumber  USB device ID of device
    @param endpointNumber  endpoint address of the endpoint in the device
    @param direction       Direction of data flow. kUSBIn or kUSBOut
    @param maxPacketSize   maximum packet size of this endpoint
    @param speed           speed of the device kUSBDeviceSpeedFull, kUSBDeviceSpeedHigh
    @param highSpeedHub    If speed is not kUSBDeviceSpeedHigh, the address of the high speed hub to
                           address split transactions to.
    @param highSpeedPort   If speed is not kUSBDeviceSpeedHigh, the hub port to address split transactions to
*/
    virtual IOReturn 		UIMCreateBulkEndpoint(
                                                        UInt8		functionNumber,
                                                        UInt8		endpointNumber,
                                                        UInt8		direction,
                                                        UInt8		speed,
                                                        UInt16		maxPacketSize,
                                                        USBDeviceAddress highSpeedHub,
                                                        int      highSpeedPort) = 0;

/*!
	@function UIMCreateInterruptEndpoint
    @abstract Create an endpoint in the controller to do interrupt transactions.
    @param functionAddress USB device ID of device
    @param endpointNumber  endpoint address of the endpoint in the device
    @param direction       Direction of data flow. kUSBIn or kUSBOut
    @param speed           speed of the device kUSBDeviceSpeedLow, kUSBDeviceSpeedFull, kUSBDeviceSpeedHigh
    @param maxPacketSize   maximum packet size of this endpoint
    @param pollingRate     The maximum polling interval from the endpoint descriptor.
    @param highSpeedHub    If speed is not kUSBDeviceSpeedHigh, the address of the high speed hub to
                           address split transactions to.
    @param highSpeedPort   If speed is not kUSBDeviceSpeedHigh, the hub port to address split transactions to
*/
    virtual IOReturn		UIMCreateInterruptEndpoint(
                                                                short		functionAddress,
                                                                short		endpointNumber,
                                                                UInt8		direction,
                                                                short		speed,
                                                                UInt16		maxPacketSize,
                                                                short		pollingRate,
                                                                USBDeviceAddress highSpeedHub,
                                                                int      highSpeedPort) = 0;

/*!
	@function UIMCreateIsochEndpoint
    @abstract Create an endpoint in the controller to do Isochronous transactions.
    @param functionAddress USB device ID of device
    @param endpointNumber  endpoint address of the endpoint in the device
    @param maxPacketSize   maximum packet size of this endpoint
    @param highSpeedHub    If non zero, this is a full speed device, the address of the high speed hub to
                           address split transactions to.
    @param highSpeedPort   If highSpeedHub is non zero, the hub port to address split transactions to
*/
    virtual IOReturn 		UIMCreateIsochEndpoint(
                                                        short				functionAddress,
                                                        short				endpointNumber,
                                                        UInt32				maxPacketSize,
                                                        UInt8				direction,
                                                        USBDeviceAddress	highSpeedHub,
                                                        int					highSpeedPort) = 0;

    OSMetaClassDeclareReservedUsed(IOUSBControllerV2,  0);
    virtual IOReturn		AddHSHub(USBDeviceAddress highSpeedHub, UInt32 flags);
    
    static IOReturn DOHSHubMaintenance(OSObject *owner, void *arg0, void *arg1, void *arg2, void *arg3);
    
    OSMetaClassDeclareReservedUsed(IOUSBControllerV2,  1);
    virtual IOReturn 		UIMHubMaintenance(USBDeviceAddress highSpeedHub, UInt32 highSpeedPort, UInt32 command, UInt32 flags);
    
    OSMetaClassDeclareReservedUsed(IOUSBControllerV2,  2);
    virtual IOReturn		RemoveHSHub(USBDeviceAddress highSpeedHub);
    
    static IOReturn DOSetTestMode(OSObject *owner, void *arg0, void *arg1, void *arg2, void *arg3);

    OSMetaClassDeclareReservedUsed(IOUSBControllerV2,  3);
    virtual IOReturn		SetTestMode(UInt32 mode, UInt32 port);
    
    OSMetaClassDeclareReservedUsed(IOUSBControllerV2,  4);
    virtual IOReturn		UIMSetTestMode(UInt32 mode, UInt32 port);
    
    OSMetaClassDeclareReservedUsed(IOUSBControllerV2,  5);
    virtual UInt64		GetMicroFrameNumber( void );
    
    OSMetaClassDeclareReservedUsed(IOUSBControllerV2,  6);
    virtual void ClearTT(USBDeviceAddress addr, UInt8 endpt, Boolean IN);

    
    OSMetaClassDeclareReservedUsed(IOUSBControllerV2,  7);
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
    virtual IOReturn ReadV2( IOMemoryDescriptor *			buffer,
                           USBDeviceAddress					address,
                           Endpoint *						endpoint,
                           IOUSBCompletionWithTimeStamp *	completion,
                           UInt32							noDataTimeout,
                           UInt32							completionTimeout,
                           IOByteCount						reqCount );
    
    OSMetaClassDeclareReservedUsed(IOUSBControllerV2,  8);
/*!
	@function UIMCreateIsochEndpoint
    @abstract Create an endpoint in the controller to do Isochronous transactions.
    @param functionAddress USB device ID of device
    @param endpointNumber  endpoint address of the endpoint in the device
    @param maxPacketSize   maximum packet size of this endpoint
    @param highSpeedHub    If non zero, this is a full speed device, the address of the high speed hub to
                           address split transactions to.
    @param highSpeedPort   If highSpeedHub is non zero, the hub port to address split transactions to
*/
    virtual IOReturn 		UIMCreateIsochEndpoint(
                                                        short				functionAddress,
                                                        short				endpointNumber,
                                                        UInt32				maxPacketSize,
                                                        UInt8				direction,
                                                        USBDeviceAddress	highSpeedHub,
                                                        int					highSpeedPort,
														UInt8				interval);


    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  9);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  10);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  11);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  12);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  13);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  14);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  15);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  16);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  17);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  18);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  19);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  20);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  21);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  22);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  23);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  24);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  25);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  26);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  27);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  28);
    OSMetaClassDeclareReservedUnused(IOUSBControllerV2,  29);
    
};


#endif /* ! _IOKIT_IOUSBCONTROLLERV2_H */
