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
#ifndef _IOKIT_IOUSBDEVICE_H
#define _IOKIT_IOUSBDEVICE_H

#include <IOKit/usb/IOUSBNub.h>
#include <IOKit/usb/IOUSBPipe.h>
#include <IOKit/IOBufferMemoryDescriptor.h>

#include <kern/thread_call.h>

// The following are definitions for errata properties needed for different devices.  This
// should be but in the dictionary of the IOUSBDevice in question.  This can be achieved
// by using the AppleUSBMergeNub class and having an IOProviderMergeProperties dictionary
// with the required properties.

// This property allows a device to specify a configuration value of 0 in its configuration
// descriptor.  This does not follow the spec, but we will allow it in order to get the device 
// to work.  The property should be a Boolean
//
#define kAllowConfigValueOfZero		"kAllowZeroConfigValue"
#define kAllowNumConfigsOfZero		"kAllowZeroNumConfigs"


class IOUSBController;
class IOUSBInterface;

/*!
    @class IOUSBDevice
    @abstract The object representing a device on the USB bus.
    @discussion This class provides functionality to configure a device and to create
	IOUSBInterface objects to represent the interfaces of the device
*/

class IOUSBDevice : public IOUSBNub
{
    friend IOUSBController;
    friend IOUSBInterface;
   
    OSDeclareDefaultStructors(IOUSBDevice)

protected:

    USBDeviceAddress			_address;
    IOUSBController *	     		_controller;
    IOUSBPipe *				_pipeZero;
    IOUSBDeviceDescriptor 		_descriptor;
    UInt32				_busPowerAvailable;
    UInt8				_speed;
    IOUSBEndpointDescriptor		_endpointZero; 				// Fake ep for control pipe
    void *				_port;					// Obsolete, do not use
    IOBufferMemoryDescriptor**		_configList;
    IOUSBInterface**			_interfaceList;
    UInt8				_currentConfigValue;
    UInt8				_numInterfaces;
    
    struct ExpansionData 
    {
        UInt32		_portNumber;
        thread_call_t	_doPortResetThread;
        IOUSBDevice *	_usbPlaneParent;
        bool		_portResetThreadActive;
        bool		_allowConfigValueOfZero;
        thread_call_t	_doPortSuspendThread;
        bool		_portSuspendThreadActive;
        thread_call_t	_doPortReEnumerateThread;
        bool		_resetInProgress;
        bool		_portHasBeenReset;
        bool		_deviceterminating;
    
    };
    ExpansionData * _expansionData;
    #define _portNumber			_expansionData->_portNumber
    #define _doPortResetThread		_expansionData->_doPortResetThread
    #define _usbPlaneParent		_expansionData->_usbPlaneParent
    #define _portResetThreadActive	_expansionData->_portResetThreadActive
    #define _allowConfigValueOfZero	_expansionData->_allowConfigValueOfZero
    #define _doPortSuspendThread	_expansionData->_doPortSuspendThread
    #define _portSuspendThreadActive	_expansionData->_portSuspendThreadActive
    #define _doPortReEnumerateThread	_expansionData->_doPortReEnumerateThread
    #define _resetInProgress		_expansionData->_resetInProgress
    #define _portHasBeenReset		_expansionData->_portHasBeenReset
    #define _deviceterminating		_expansionData->_deviceterminating

   virtual void free();	

    const IOUSBConfigurationDescriptor *FindConfig(UInt8 configValue, UInt8 *configIndex=0);

    virtual IOUSBInterface * GetInterface(const IOUSBInterfaceDescriptor *interface);

    virtual IOReturn IOUSBDevice::SetFeature(UInt8 feature);
    
    virtual IOReturn GetConfigDescriptor(UInt8 configIndex, void *data, UInt32 len);

    virtual IOReturn GetDeviceDescriptor(IOUSBDeviceDescriptor *desc, UInt32 size);

    virtual bool init(USBDeviceAddress deviceAddress, UInt32 powerAvaiable, UInt8 speed, UInt8 maxPacketSize );

    virtual bool matchPropertyTable(OSDictionary * table, SInt32 *score);
    
public:
    virtual void SetProperties();
    
    static IOUSBDevice *NewDevice(void);
    
    // IOService methods
    virtual bool 	attach(IOService *provider);
    virtual bool 	start( IOService * provider );
    virtual void 	stop( IOService * provider );
    virtual bool 	finalize(IOOptionBits options);
    virtual IOReturn 	message( UInt32 type, IOService * provider,  void * argument = 0 );
    virtual bool 	willTerminate( IOService * provider, IOOptionBits options );
    virtual bool 	didTerminate( IOService * provider, IOOptionBits options, bool * defer );

    virtual void SetPort(void *port) { _port = port;}			// Obsolete, do NOT use

    /*!
	@function FindNextInterfaceDescriptor
	return a pointer to the next interface descriptor within the given full configuration descriptor satisfying the requirements specified, or NULL if there aren't any.
        @param configDescIn the configuration descriptor within which to search. obtained from GetFullConfigurationDescriptor(configIndex). use NULL to specify the current configuration's descriptor.
        @param intfDesc interface descriptor from which to start the search. NULL for the first interface descriptor in the given configuration descriptor
        @param request IOUSBFindInterfaceRequest specifying the desired interface. Not changed.
        @param descOut pointer to placeholder for the returned descriptor ptr
	@result returns kIOReturnBadArgument if configDesc is not correct, or if configDesc is NULL and the device is not configured, or if intfDesc is not in configDesc. Otherwise returns kIOReturnSuccess or kIOUSBInterfaceNotFound.
    */
    virtual IOReturn FindNextInterfaceDescriptor(const IOUSBConfigurationDescriptor *configDescIn, 
                                                 const IOUSBInterfaceDescriptor *intfDesc,
                                                 const IOUSBFindInterfaceRequest *request,
                                                 IOUSBInterfaceDescriptor **descOut);
    /*!
	@function FindNextInterface
	return an pointer to an instantiated interface satisfying the requirements specified in request, or NULL if there aren't any. the device
        must be configured for there to be any interfaces.
        @param current interface to start searching from, NULL to start at the beginning of the device's interface list for the current configuration.
	@param request specifies what properties an interface must have to match.
	@result Pointer to a matching interface, or NULL if none match. Note: The IOUSBInterface is NOT retained for the caller. If the caller wishes to continue to use the returned object, it should call retain() on that object.
    */
    virtual IOUSBInterface *FindNextInterface(IOUSBInterface *current,
                                              IOUSBFindInterfaceRequest *request);

    /*!
        @function CreateInterfaceIterator 
        return an OSIterator to iterate through interfaces satisfying the requirements specified in request.                        
        @param request specifies what properties an interface must have to match.
        @result Pointer to an OSIterator.
    */
    virtual OSIterator *CreateInterfaceIterator(IOUSBFindInterfaceRequest *request);

    // Get pointer to full config info (cached in device, don't free returned pointer)
    /*!
	@function GetFullConfigurationDescriptor
	return a pointer to all the descriptors for the requested configuration.
        @param configIndex The configuration index (not the configuration value)
	@result Pointer to the descriptors, which are cached in the device object.
    */
    virtual const IOUSBConfigurationDescriptor *GetFullConfigurationDescriptor(UInt8 configIndex);

    /*!
	@function GetConfigurationDescriptor
        Copy the specified amount of data for a configuration into the suppled buffer.
        @param configValue The configuration value
	@param data Buffer to copy data into
	@param len number of bytes to copy
    */
    virtual IOReturn GetConfigurationDescriptor(UInt8 configValue, void *data, UInt32 len);

    /*!
	@function ResetDevice
	Reset the device, returning it to the addressed, unconfigured state.
	This is useful if a device has got badly confused
    */
    virtual IOReturn ResetDevice();

    /*!
	@function SetConfiguration
	Do a USB SetConfiguration call to the device. The caller must have the device open() in order to 
	actually cause a configuration change. If the device is currently configured, all interfaces
	associated with the device are freed. After the new configuration has been set, all of its interfaces are
	instantiated automatically.
	@param forClient The client requesting the configuration change
	@param configValue The desired configuration value.
	@param startInterfaceMatching A boolean specifying whether IOKit should begin the process of finding
	matching drivers for the new interfaces.
    */
    virtual IOReturn SetConfiguration(IOService *forClient, UInt8 configValue, bool startInterfaceMatching=true);
    
    // Access to addressing and cached info
    /*!
        @function GetAddress
        returns the bus address of the device
    */
    virtual USBDeviceAddress GetAddress(void) { return _address; }
    
    /*!
        @function GetSpeed
        returns the speed of the device
    */
    virtual UInt8 GetSpeed(void) { return _speed; }
    /*!
        @function GetBus
        returns a pointer to the bus object for the device
    */
    virtual IOUSBController *GetBus(void) { return _controller; }
    /*!
        @function GetBusPowerAvailable
        returns the power available to the device, in units of 2mA
    */
    virtual UInt32 GetBusPowerAvailable( void ) { return _busPowerAvailable; }
    /*!
        @function GetMaxPacketSize
        returns the maximum packet size for endpoint zero (only 8, 16, 32, 64 are valid)
    */
    virtual UInt8 GetMaxPacketSize(void) { return _descriptor.bMaxPacketSize0; }
    /*!
        @function GetVendorID
        returns the Vendor ID of the device
    */
    virtual UInt16 GetVendorID(void) { return USBToHostWord(_descriptor.idVendor); }
    /*!
        @function GetProductID
        returns the Product ID of the device
    */
    virtual UInt16 GetProductID(void) { return USBToHostWord(_descriptor.idProduct);}
    /*!
        @function GetDeviceRelease
        returns the DeviceRelease information
    */
    virtual UInt16 GetDeviceRelease(void) { return USBToHostWord(_descriptor.bcdDevice); }
    /*!
        @function GetNumConfigs
        returns the number of configs in the device config descriptor
    */
    virtual UInt8 GetNumConfigurations(void) { return _descriptor.bNumConfigurations; }
    /*!
        @function GetManufacturerStringIndex
        returns the index of string descriptor describing manufacturer
    */
    virtual UInt8 GetManufacturerStringIndex(void ) { return _descriptor.iManufacturer; }
    /*!
        @function GetProductStringIndex
        returns the index of string descriptor describing product
    */
    virtual UInt8 GetProductStringIndex(void ) { return _descriptor.iProduct; }
    /*!
        @function GetSerialNumberStringIndex
        returns the index of string descriptor describing the device's serial number
    */
    virtual UInt8 GetSerialNumberStringIndex(void ) { return _descriptor.iSerialNumber; }
    /*!
        @function GetPipeZero
        returns a pointer to the device's default pipe
    */
    virtual IOUSBPipe * GetPipeZero(void) { return _pipeZero; }
    /*!
        @function MakePipe
        @abstract build a pipe on a given endpoint
        @param ep A description of the endpoint
        returns the desired pipe
    */
    virtual IOUSBPipe*	MakePipe(const IOUSBEndpointDescriptor *ep) 
        {return IOUSBPipe::ToEndpoint(ep, _speed, _address, _controller); }
        
    /*!
	@function DeviceRequest
        @abstract execute a device request
        @param request The parameter block to send to the device
	@completion Function to call when request completes. If omitted then deviceRequest()
	executes synchronously, blocking until the request is complete.
    */
    virtual IOReturn DeviceRequest(IOUSBDevRequest	*request,
                                IOUSBCompletion	*completion = 0);

    // Same but with a memory descriptor
    virtual IOReturn DeviceRequest(IOUSBDevRequestDesc	*request,
                                   IOUSBCompletion	*completion = 0);

    /*!
	@function GetConfiguration
	Gets the current configuration from the device
	@param configNum Pointer to place to store configuration value
    */
    virtual IOReturn GetConfiguration(UInt8 *configNumber);

    /*!
        @function GetConfiguration
        Gets the current configuration from the device
        @param configNum Pointer to place to store configuration value
    */
    virtual IOReturn GetDeviceStatus(USBStatus *status);

    /*! 
	@function GetStringDescriptor
	Get a string descriptor as ASCII, in the specified language (default is US English)
	@param index Index of the string descriptor to get.
	@param buf Pointer to place to store ASCII string
	@param maxLen Size of buffer pointed to by buf
        @param lang Language to get string in (default is US English)
    */
    virtual IOReturn GetStringDescriptor(UInt8 index, char *buf, int maxLen, UInt16 lang=0x409);
    
    /*! 
	@function GetChildLocationID
	Get the locationID (UInt32) given the port number and the parent's location
	@param parentLocationID locationID for the hub to which this device is attached.
	@param port Port number of the hub where this device is attached
    */
    virtual UInt32 GetChildLocationID(UInt32 parentLocationID, int port);

    virtual const IOUSBDescriptorHeader* FindNextDescriptor(const void *cur, UInt8 descType);

    virtual void 	DisplayNotEnoughPowerNotice();

    OSMetaClassDeclareReservedUsed(IOUSBDevice,  0);
    virtual IOReturn DeviceRequest(IOUSBDevRequest	*request,
				UInt32 noDataTimeout,
				UInt32 completionTimeout,
                                IOUSBCompletion	*completion = 0);

    // Same but with a memory descriptor
    OSMetaClassDeclareReservedUsed(IOUSBDevice,  1);
    virtual IOReturn DeviceRequest(IOUSBDevRequestDesc	*request,
				    UInt32 noDataTimeout,
				    UInt32 completionTimeout,
				    IOUSBCompletion	*completion = 0);

    OSMetaClassDeclareReservedUsed(IOUSBDevice,  2);
    virtual IOReturn SuspendDevice( bool suspend);
    
    OSMetaClassDeclareReservedUsed(IOUSBDevice,  3);
    virtual IOReturn ReEnumerateDevice( UInt32 options );
    
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  4);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  5);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  6);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  7);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  8);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  9);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  10);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  11);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  12);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  13);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  14);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  15);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  16);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  17);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  18);
    OSMetaClassDeclareReservedUnused(IOUSBDevice,  19);
    
private:

    static void 	ProcessPortResetEntry(OSObject *target);
    void 		ProcessPortReset(void);

    void 		TerminateInterfaces(void);

    static void 	ProcessPortSuspendEntry(OSObject *target, thread_call_param_t suspend);
    void 		ProcessPortSuspend( bool suspend);
   
    static void 	ProcessPortReEnumerateEntry(OSObject *target, thread_call_param_t options);
    void 		ProcessPortReEnumerate(UInt32 options);



};

#endif /* _IOKIT_IOUSBDEVICE_H */
