/*
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights Reserved.
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef _IOKIT_HID_IOHIDINTERFACE_H
#define _IOKIT_HID_IOHIDINTERFACE_H

#include <IOKit/IOService.h>
#include <IOKit/hid/IOHIDKeys.h>

class IOHIDDevice;

/*! @class IOHIDInterface : public IOService
    @abstract In kernel interface to a HID device.
    @discussion
*/

class IOHIDInterface: public IOService
{
    OSDeclareDefaultStructors( IOHIDInterface )
    
public:

    /*! @typedef IOHIDInterface::InterruptReportAction
        @abstract Callback to handle an asynchronous report received from 
        the HID device.
        @discussion This callback is set when calling IOHIDInterface::open.  
        @param target Pointer to your data object.
        @param timestamp Time when the report was delivered.
        @param report A memory descriptor that describes the report. 
        @param reportType The type of report.
        @param reportID The ID of the report.
        @param refcon void * pointer to more data.
    */  
    typedef void (*InterruptReportAction)(
                                OSObject *                  target,
                                AbsoluteTime                timestamp,
                                IOMemoryDescriptor *        report,
                                IOHIDReportType             type,
                                UInt32                      reportID,
                                void *                      refcon);

    /*!
        @typedef IOHIDInterface::CompletionAction
        @discussion Function called when HID I/O completes.
        @param target
        @param refcon
        @param status Completion status.
        @param bufferSizeRemaining Bytes left to be transferred.
    */
        
    typedef void (*CompletionAction)(
                                OSObject *                  target,
                                void *                      refcon,
                                IOReturn                    status,
                                UInt32                      bufferSizeRemaining);

private:
    IOHIDDevice *               _owner;
    OSArray *                   _elementArray;
    InterruptReportAction       _interruptAction;
    void *                      _interruptRefCon;
    OSObject *                  _interruptTarget;
    OSString *                  _transportString;
    OSString *                  _manufacturerString;
    OSString *                  _productString;
    OSString *                  _serialNumberString;
    UInt32                      _locationID;
    UInt32                      _vendorID;
    UInt32                      _vendorIDSource;
    UInt32                      _productID;
    UInt32                      _version;
    UInt32                      _countryCode;
    IOByteCount                 _maxReportSize[kIOHIDReportTypeCount];

    struct ExpansionData { 
        UInt32                  reportInterval;
    };
    /*! @var reserved
        Reserved for future use.  (Internal use only)  */
    ExpansionData *             _reserved;
    
protected:

    /*! 
        @function free
        @abstract Free the IOHIDInterface object.
        @discussion Release all resources that were previously allocated,
        then call super::free() to propagate the call to our superclass. 
    */

    virtual void            free();

public:

    static IOHIDInterface * withElements ( OSArray * elements );

    /*! 
        @function init
        @abstract Initialize an IOHIDInterface object.
        @discussion Prime the IOHIDInterface object and prepare it to support
        a probe() or a start() call. This implementation will simply call
        super::init().
        @param A dictionary A property table associated with this IOHIDInterface
        instance.
        @result True on sucess, or false otherwise. 
    */

    virtual bool            init( OSDictionary * dictionary = 0 );

    /*! 
        @function start
        @abstract Start up the driver using the given provider.
        @discussion IOHIDInterface will allocate resources. Before returning true
        to indicate success, registerService() is called to trigger client matching.
        @param provider The provider that the driver was matched to, and selected
        to run with.
        @result True on success, or false otherwise. 
    */

    virtual bool            start( IOService * provider );
    

    virtual void            stop( IOService * provider );
    /*! 
        @function matchPropertyTable
        @abstract Called by the provider during a match
        @discussion Compare the properties in the supplied table to this 
        object's properties.
        @param table The property table that this device will match against
    */

    virtual bool            matchPropertyTable(
                                OSDictionary *              table, 
                                SInt32 *                    score);    

    virtual bool            open (
                                IOService *                 client,
                                IOOptionBits                options,
                                InterruptReportAction       action,
                                void *                      refCon);

    virtual void			close(  
								IOService *					client,
								IOOptionBits				options = 0 );

    virtual OSString *      getTransport ();
    virtual UInt32          getLocationID ();
    virtual UInt32          getVendorID ();
    virtual UInt32          getVendorIDSource ();
    virtual UInt32          getProductID ();
    virtual UInt32          getVersion ();
    virtual UInt32          getCountryCode ();
    virtual OSString *      getManufacturer ();
    virtual OSString *      getProduct ();
    virtual OSString *      getSerialNumber ();
    virtual IOByteCount     getMaxReportSize (IOHIDReportType type);

    virtual OSArray *       createMatchingElements (
                                OSDictionary *              matching            = 0, 
                                IOOptionBits                options             = 0);
                                
    virtual void            handleReport (
                                AbsoluteTime                timeStamp,
                                IOMemoryDescriptor *        report,
                                IOHIDReportType             reportType,
                                UInt32                      reportID,
                                IOOptionBits                options             = 0);
    
    virtual IOReturn        setReport ( 
                                IOMemoryDescriptor *        report,
                                IOHIDReportType             reportType,
                                UInt32                      reportID            = 0,
                                IOOptionBits                options             = 0);

    virtual IOReturn        getReport ( 
                                IOMemoryDescriptor *        report,
                                IOHIDReportType             reportType,
                                UInt32                      reportID            = 0,
                                IOOptionBits                options             = 0);

    virtual IOReturn        setReport ( 
                                IOMemoryDescriptor *        report,
                                IOHIDReportType             reportType,
                                UInt32                      reportID,
                                IOOptionBits                options,
                                UInt32                      completionTimeout,
                                CompletionAction *          completion          = 0);    

    virtual IOReturn        getReport ( 
                                IOMemoryDescriptor *        report,
                                IOHIDReportType             reportType,
                                UInt32                      reportID,
                                IOOptionBits                options,
                                UInt32                      completionTimeout,
                                CompletionAction *          completion          = 0);
    virtual IOReturn        message(
                                UInt32 type,
                                IOService * provider,
                                void * argument = NULL);
    
    OSMetaClassDeclareReservedUsed(IOHIDInterface,  0);
    virtual UInt32             getReportInterval ();
    
    OSMetaClassDeclareReservedUnused(IOHIDInterface,  1);
    OSMetaClassDeclareReservedUnused(IOHIDInterface,  2);
    OSMetaClassDeclareReservedUnused(IOHIDInterface,  3);
    OSMetaClassDeclareReservedUnused(IOHIDInterface,  4);
    OSMetaClassDeclareReservedUnused(IOHIDInterface,  5);
    OSMetaClassDeclareReservedUnused(IOHIDInterface,  6);
    OSMetaClassDeclareReservedUnused(IOHIDInterface,  7);
    OSMetaClassDeclareReservedUnused(IOHIDInterface,  8);
    OSMetaClassDeclareReservedUnused(IOHIDInterface,  9);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 10);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 11);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 12);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 13);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 14);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 15);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 16);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 17);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 18);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 19);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 20);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 21);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 22);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 23);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 24);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 25);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 26);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 27);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 28);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 29);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 30);
    OSMetaClassDeclareReservedUnused(IOHIDInterface, 31);
};

#endif /* !_IOKIT_HID_IOHIDINTERFACE_H */
