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

#ifndef _IOKIT_HID_IOHIDEVENTDRIVER_H
#define _IOKIT_HID_IOHIDEVENTDRIVER_H

#include <IOKit/IOService.h>
#include <IOKit/hidsystem/IOHIDTypes.h>
#include <IOKit/hid/IOHIDInterface.h>
#include <IOKit/hidevent/IOHIDEventService.h>


/*! @class IOHIDEventDriver : public IOHIDEventService
    @abstract
    @discussion
*/
struct  IOHIDReportHandler;

class IOHIDEventDriver: public IOHIDEventService
{
    OSDeclareDefaultStructors( IOHIDEventDriver )

private:
    IOHIDInterface *            _interface;
    IOHIDReportHandler *        _reportHandlers;
    
    IOHIDElement *              _ledElements[2];
    OSArray *                   _supportedElements;
        
    UInt32                      _bootSupport;
    bool                        _multipleReports;
    bool                        _relativeButtonCollection;
    UInt32                      _cachedButtonState;
    bool                        _cachedRangeState;
    
    struct ExpansionData {
        SInt32  absoluteAxisRemovalPercentage;
        
        struct { 
            bool        containsRange;
            uint32_t    type;
        } digitizer;
        
        struct {
            UInt32          capable;
            UInt32          sendingReportID;
            IOFixed         axis[6];
            IOOptionBits    options;
        } multiAxis;
    };
    /*! @var reserved
        Reserved for future use.  (Internal use only)  */
    ExpansionData *             _reserved;
    
    bool                    findElements ( OSArray * elementArray, UInt32 bootProtocol );
        
    bool                    storeReportElement ( IOHIDElement * element );

    void                    handleBootPointingReport (
                                IOMemoryDescriptor *        report,
                                SInt32 *                    dX,
                                SInt32 *                    dY,
                                UInt32 *                    buttonState);

    static void             processMultiAxisElement(IOHIDElement * element, UInt32 * isMultiAxis, bool * supportsInk=NULL, IOHIDElement ** relativeCollection=NULL);
    static void             calibrateDigitizerElement(IOHIDElement * element, SInt32 removalPercentage);
    static void             calibratePreferredStateElement(IOHIDElement * element, SInt32 removalPercentage);
    static void             calibrateAxisToButtonElement(IOHIDElement * element, SInt32 removalPercentage);

protected:

    virtual void            free();
    
    virtual OSArray *       getReportElements();
    
    virtual bool            handleStart( IOService * provider );

    virtual void            handleStop(  IOService * provider );
    
    virtual void            handleInterruptReport (
                                AbsoluteTime                timeStamp,
                                IOMemoryDescriptor *        report,
                                IOHIDReportType             reportType,
                                UInt32                      reportID);

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

    virtual void            setElementValue (
                                UInt32                      usagePage,
                                UInt32                      usage,
                                UInt32                      value );
    
    virtual UInt32          getElementValue ( 
                                UInt32                      usagePage,
                                UInt32                      usage );

public:


    virtual bool            init( OSDictionary * dictionary = 0 );

    virtual bool            didTerminate(
                                IOService *                 provider,
                                IOOptionBits                options,
                                bool *                      defer );
    
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver,  0);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver,  1);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver,  2);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver,  3);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver,  4);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver,  5);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver,  6);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver,  7);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver,  8);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver,  9);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 10);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 11);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 12);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 13);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 14);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 15);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 16);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 17);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 18);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 19);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 20);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 21);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 22);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 23);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 24);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 25);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 26);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 27);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 28);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 29);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 30);
    OSMetaClassDeclareReservedUnused(IOHIDEventDriver, 31);

};

#endif /* !_IOKIT_HID_IOHIDEVENTDRIVER_H */
