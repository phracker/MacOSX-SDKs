/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _IOKIT_HID_IOHIDDEVICE_H
#define _IOKIT_HID_IOHIDDEVICE_H

#include <IOKit/IOService.h>
#include <IOKit/IOBufferMemoryDescriptor.h>
#include <IOKit/hidsystem/IOHIDDescriptorParser.h>
#include "IOHIDKeys.h"

class  IOHIDElement;
class  IOHIDEventQueue;
struct IOHIDReportHandler;

/*! @class IOHIDDevice : public IOService
    @abstract IOHIDDevice defines a Human Interface Device (HID) object,
    which will interact with the HID Manager by publishing static properties
    in the registry, and also by reporting HID events through shared memory.
    IOHIDDevice is an abstract class that must be subclassed to support a
    specific type of HID devices, such as USB HID class devices.
    <br>
    Since most HID devices are expected to be USB devices, IOHIDDevice
    uses the USB HID specification to define the format of the report
    descriptor, and also reports that are used to communicate with the
    hardware via some intervening transport layer. However, there is no
    mandate that the transport layer must be restricted to USB. A subclass
    may be created to support legacy ADB joysticks, and issue packets on
    the ADB bus and translate those packets to USB reports, and vice versa.
    IOHIDDevice does not care how those reports are generated or consumed
    by the physical device, as long as the reports abide to the USB
    specification. */

class IOHIDDevice : public IOService
{
    OSDeclareDefaultStructors( IOHIDDevice )

private:
    OSArray *                   _elementArray;
    UInt32                      _dataElementIndex;
    IOLock *                    _elementLock;
    IOHIDReportHandler *        _reportHandlers;
    IOBufferMemoryDescriptor *  _elementValuesDescriptor;
    bool                        _readyForInputReports;
    UInt32                      _reportCount;
    UInt32                      _maxInputReportSize;
    UInt32                      _maxOutputReportSize;
    UInt32                      _maxFeatureReportSize;

    struct ExpansionData { };
    /*! @var reserved
        Reserved for future use.  (Internal use only)  */
    ExpansionData * _reserved;

    // HID report descriptor parsing support.

    bool linkToParent( const OSArray * array,
                       UInt32          parentIndex,
                       UInt32          childIndex );

    bool createCollectionElements( HIDPreparsedDataRef parseData,
                                   OSArray *           array,
                                   UInt32              maxCount );

    bool createValueElements( HIDPreparsedDataRef parseData,
                              OSArray *           array,
                              UInt32              hidReportType,
                              IOHIDElementType    elementType,
                              UInt32              maxCount );

    bool createButtonElements( HIDPreparsedDataRef parseData,
                               OSArray *           array,
                               UInt32              hidReportType,
                               IOHIDElementType    elementType,
                               UInt32              maxCount );

    bool getReportCountAndSizes( HIDPreparsedDataRef parseData );

    bool setReportSize( UInt8           reportID,
                        IOHIDReportType reportType,
                        UInt32          bits );

    IOReturn createElementHierarchy( HIDPreparsedDataRef parseData );

    IOReturn parseReportDescriptor( IOMemoryDescriptor * report,
                                    IOOptionBits         options = 0 );

    IOBufferMemoryDescriptor * createMemoryForElementValues();

protected:

/*! @function free
    @abstract Free the IOHIDDevice object.
    @discussion Release all resources that were previously allocated,
    then call super::free() to propagate the call to our superclass. */

    virtual void free();

/*! @function handleStart
    @abstract Prepare the hardware and driver to support I/O operations.
    @discussion IOHIDDevice will call this method from start() before
    any I/O operations are issued to the concrete subclass. Methods
    such as newReportDescriptor() are only called after handleStart()
    has returned true. A subclass that overrides this method should
    begin its implementation by calling the version in super, and
    then check the return value.
    @param provider The provider argument passed to start().
    @result True on success, or false otherwise. Returning false will
    cause start() to fail and return false. */

    virtual bool handleStart( IOService * provider );

/*! @function handleStop
    @abstract Quiesce the hardware and stop the driver.
    @discussion IOHIDDevice will call this method from stop() to
    signal that the hardware should be quiesced and the driver stopped.
    A subclass that overrides this method should end its implementation
    by calling the version in super.
    @param provider The provider argument passed to stop(). */

    virtual void handleStop(  IOService * provider );

/*! @function newUserClient
    @abstract Handle a request to create a connection for a non kernel
    client.
    @discussion Create a new IOUserClient, or a subclass of IOUserClient,
    to service a connection to a non kernel client. This implementation
    will simply call the implementation in IOService to handle the call.
    @param owningTask The mach task requesting the connection.
    @param security_id A token representing the access level for the task.
    @param type A constant specifying the type of connection to be created.
    @param handler The IOUserClient object returned.
    @result The return from IOService::newUserClient() is returned. */

    virtual IOReturn newUserClient( task_t          owningTask,
                                    void *          security_id,
                                    UInt32          type,
                                    IOUserClient ** handler );

/*! @function publishProperties
    @abstract Publish HID properties to the I/O Kit registry.
    @discussion Called by the start() method to fetch and publish all
    HID properties to the I/O Kit registry. These properties will allow
    the HID Manager to identify all HID device(s) in the system, by
    iterating through objects that are subclasses of IOHIDDevice, and
    then fetch their published property values. The implementation in
    IOHIDDevice will call methods to get each individual HID property,
    and subclasses will not normally need to override this method.
    @param provider The provider argument passed to start().
    @result True to indicate that all properties were discovered and
    published to the registry, false otherwise. Returning false will
    cause start() to fail and return false. */

    virtual bool publishProperties( IOService * provider );

public:

/*! @function init
    @abstract Initialize an IOHIDDevice object.
    @discussion Prime the IOHIDDevice object and prepare it to support
    a probe() or a start() call. This implementation will simply call
    super::init().
    @param A dictionary A property table associated with this IOHIDDevice
    instance.
    @result True on sucess, or false otherwise. */

    virtual bool init( OSDictionary * dictionary = 0 );

/*! @function start
    @abstract Start up the driver using the given provider.
    @discussion IOHIDDevice will allocate resources, then call handleStart()
    before fetching the report descriptor through newReportDescriptor(), and
    publishing HID properties to the registry. Before returning true to 
    indicate success, registerService() is called to trigger client matching.
    Subclasses are recommended to override handleStart().
    @param provider The provider that the driver was matched to, and selected
    to run with.
    @result True on success, or false otherwise. */

    virtual bool start( IOService * provider );

/*! @function stop
    @abstract Called by a provider (during its termination) before detaching
    all its clients.
    @discussion IOHIDDevice will call handleStop(), then release allocated
    resources. Subclasses are recommended to override handleStop().
    @param provider The provider that the driver was started on. */

    virtual void stop( IOService * provider );

/*! @function newTransportString
    @abstract Returns a string object that describes the transport
    layer used by the HID device.
    @result A string object. The caller must decrement the retain count
    on the object returned. */

    virtual OSString * newTransportString() const;
    
/*! @function newManufacturerString
    @abstract Returns a string object that describes the manufacturer
    of the HID device.
    @result A string object. The caller must decrement the retain count
    on the object returned. */

    virtual OSString * newManufacturerString() const;

/*! @function newProductString
    @abstract Returns a string object that describes the product
    of the HID device.
    @result A string object. The caller must decrement the retain count
    on the object returned. */

    virtual OSString * newProductString() const;

/*! @function newVendorIDNumber
    @abstract Returns a number object that describes the vendor ID
    of the HID device.
    @result A number object. The caller must decrement the retain count
    on the object returned. */

    virtual OSNumber * newVendorIDNumber() const;

/*! @function newProductIDNumber
    @abstract Returns a number object that describes the product ID
    of the HID device.
    @result A number object. The caller must decrement the retain count
    on the object returned. */

    virtual OSNumber * newProductIDNumber() const;

/*! @function newVersionNumber
    @abstract Returns a number object that describes the version number
    of the HID device.
    @result A number object. The caller must decrement the retain count
    on the object returned. */

    virtual OSNumber * newVersionNumber() const;

/*! @function newSerialNumber
    @abstract Returns a number object that describes the serial number
    of the HID device.
    @result A number object. The caller must decrement the retain count
    on the object returned. */

    virtual OSNumber * newSerialNumber() const;

/*! @function newPrimaryUsageNumber
    @abstract Returns a number object that describes the primary usage
    of the HID device.
    @result A number object. The caller must decrement the retain count
    on the object returned. */

    virtual OSNumber * newPrimaryUsageNumber() const;

/*! @function newPrimaryUsagePageNumber
    @abstract Returns a number object that describes the primary usage
    page of the HID device.
    @result A number object. The caller must decrement the retain count
    on the object returned. */

    virtual OSNumber * newPrimaryUsagePageNumber() const;

/*! @function newReportDescriptor
    @abstract Create and return a new memory descriptor that describes the
    report descriptor for the HID device.
    @discussion A subclass must override this pure virtual function, and
    return a memory descriptor that describes the HID report descriptor as
    defined by the USB Device Class Definition for Human Interface Devices
    Version 1.1 specification.
    @param descriptor Pointer to the memory descriptor returned. This
    memory descriptor will be released by the caller.
    @result kIOReturnSuccess on success, or an error return otherwise. */

    virtual IOReturn newReportDescriptor(
                        IOMemoryDescriptor ** descriptor ) const = 0;

/*! @function handleReport
    @abstract Handle an asynchronous report received from the HID device.
    @param report A memory descriptor that describes the report.
    @param reportType The type of report. Currently, only
    kIOHIDReportTypeInput report type is handled.
    @param options Options to specify the request. No options are
    currently defined, and the default value is 0.
    @result kIOReturnSuccess on success, or an error return otherwise. */

	virtual IOReturn handleReport(
                     IOMemoryDescriptor * report,
	                 IOHIDReportType      reportType = kIOHIDReportTypeInput,
	                 IOOptionBits         options    = 0 );

/*! @function getReport
    @abstract Get a report from the HID device.
    @discussion A completion parameter may be added in the future.
    @param report A memory descriptor that describes the memory to store
    the report read from the HID device.
    @param reportType The report type.
    @param options Options to specify the request.
    @result kIOReturnSuccess on success, or an error return otherwise. */

    virtual IOReturn getReport( IOMemoryDescriptor * report,
                                IOHIDReportType      reportType,
                                IOOptionBits         options );

/*! @function setReport
    @abstract Send a report to the HID device.
    @discussion A completion parameter may be added in the future.
    @param report A memory descriptor that describes the report to send
    to the HID device.
    @param reportType The report type.
    @param options Options to specify the request.
    @result kIOReturnSuccess on success, or an error return otherwise. */

    virtual IOReturn setReport( IOMemoryDescriptor * report,
                                IOHIDReportType      reportType,
                                IOOptionBits         options = 0 );

/*! @function getMemoryWithCurrentElementValues
    @abstract Get a reference to a memory descriptor that describes the
    memory block containing the current HID element values.
    @discussion Each HID element that can contribute to an input, output,
    or feature report, is assigned an area of memory from a common memory
    block allocated by IOHIDDevice. Each element will use its assigned
    memory area to store its current value, defined by an IOHIDElementValue
    structure. The memory described by the memory descriptor may be mapped
    to user space to allow the HID Manager to poll the current element
    value without the cost of a user-kernel transition. Subclasses should
    not override this method.
    @result A reference to a memory descriptor that describes the current
    element values, or 0 to indicate a resource shortage. */

    virtual IOMemoryDescriptor * getMemoryWithCurrentElementValues() const;

/*! @function registerElement
    @abstract A registration function called by a HID element to register
    itself, and also to obtain an unique cookie identifier
    (unique per device, not unique system-wide).
    @discussion An internal data type, an IOHIDElement, is created to
    represent each HID element discovered by parsing the HID report
    descriptor. Each element created will call this method to register
    itself with its owner (IOHIDDevice), and also to obtain an element
    cookie that is used by HID Manager to specify and identify the element.
    Subclasses should not override this method.
    @param element The element that is requesting registration with its
    owner.
    @param cookie Pointer to the returned cookie assigned to this element.
    @result True on success, or false otherwise. */

    virtual bool registerElement( IOHIDElement *       element,
                                  IOHIDElementCookie * cookie );

/*! @function startEventDelivery
    @abstract Start delivering events from a HID element to the event
    queue specified.
    @discussion Clients of IOHIDDevice may create an IOHIDEventQueue, and
    then call this method to register for delivery of events generated by
    one or more HID elements to that event queue. Subclasses should not
    override this method.
    @param queue The event queue that is interested in receiving events
    generated by the HID element specified. The retain count on the queue
    will be incremented by one.
    @param cookie The cookie for a HID element published by the HID device.
    @param options Options to specify the request. No options are currently
    defined, and the default value is zero.
    @result kIOReturnSuccess on success, or kIOReturnBadArgument if the
    queue or the cookie argument specified is invalid, or kIOReturnNoMemory
    if a resource shortage was encountered. */

    virtual IOReturn startEventDelivery( IOHIDEventQueue *  queue,
                                         IOHIDElementCookie cookie,
                                         IOOptionBits       options = 0 );

/*! @function stopEventDelivery
    @abstract Stop delivering events from one or more HID elements to the
    event queue specified.
    @discussion Clients that called startEventDelivery() must eventually
    call this method to stop event delivery to its queue from one or more
    HID elements.
    @param queue The event queue that no longer wishes to receive events
    generated by the HID element specified.
    @param cookie The cookie for a HID element published by the HID device.
    The default value of zero indicates that the queue should be removed from
    the event dispatch list of all HID elements published by the HID device.
    Subclasses should not override this method.
    @result kIOReturnSuccess if the queue was removed from the event dispatch
    list for one or more HID elements, or kIOReturnBadArgument if the queue
    or the cookie argument specified is invalid, or kIOReturnNotFound if the
    queue was not found. */

    virtual IOReturn stopEventDelivery( IOHIDEventQueue *  queue,
                                        IOHIDElementCookie cookie = 0 );

/*! @function checkEventDelivery
    @abstract Check whether events from a HID element will be delivered to
    the event queue specified.
    @param queue The event queue.
    @param cookie The cookie for a HID element published by the HID device.
    @param isActive Pointer to the return value that is set to true if events
    generated by the HID element will be delivered to the queue, or false
    otherwise. This return value is set only if kIOReturnSuccess is
    returned.
    @result kIOReturnSuccess on success, or kIOReturnBadArgument if one or
    more of the arguments provided are invalid. */

    virtual IOReturn checkEventDelivery( IOHIDEventQueue *  queue,
                                         IOHIDElementCookie cookie,
                                         bool *             isActive );

    OSMetaClassDeclareReservedUnused(IOHIDDevice,  0);
    OSMetaClassDeclareReservedUnused(IOHIDDevice,  1);
    OSMetaClassDeclareReservedUnused(IOHIDDevice,  2);
    OSMetaClassDeclareReservedUnused(IOHIDDevice,  3);
    OSMetaClassDeclareReservedUnused(IOHIDDevice,  4);
    OSMetaClassDeclareReservedUnused(IOHIDDevice,  5);
    OSMetaClassDeclareReservedUnused(IOHIDDevice,  6);
    OSMetaClassDeclareReservedUnused(IOHIDDevice,  7);
    OSMetaClassDeclareReservedUnused(IOHIDDevice,  8);
    OSMetaClassDeclareReservedUnused(IOHIDDevice,  9);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 10);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 11);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 12);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 13);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 14);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 15);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 16);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 17);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 18);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 19);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 20);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 21);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 22);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 23);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 24);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 25);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 26);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 27);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 28);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 29);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 30);
    OSMetaClassDeclareReservedUnused(IOHIDDevice, 31);
};

#endif /* !_IOKIT_HID_IOHIDDEVICE_H */
