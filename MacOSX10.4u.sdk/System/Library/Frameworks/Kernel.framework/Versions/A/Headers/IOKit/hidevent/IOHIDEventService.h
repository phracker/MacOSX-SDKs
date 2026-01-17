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

#ifndef _IOKIT_HID_IOHIDEVENTSERVICE_H
#define _IOKIT_HID_IOHIDEVENTSERVICE_H

#include <IOKit/IOService.h>
#include <IOKit/hidsystem/IOHIDTypes.h>
#include <IOKit/hid/IOHIDInterface.h>
#include <IOKit/hid/IOHIDElement.h>

enum 
{
    kHIDDispatchOptionPointerNoAcceleration            = 0x01,
    kHIDDispatchOptionPointerAffixToScreen             = 0x02,
    kHIDDispatchOptionPointerAbsolutToRelative         = 0x04
};

enum 
{
    kHIDDispatchOptionScrollNoAcceleration             = 0x01
};

enum 
{
    kHIDDispatchOptionKeyboardNoRepeat                 = 0x01
};

/*! @class IOHIDEventService : public IOService
    @abstract
    @discussion
*/
class   IOHIDPointing;
class   IOHIDKeyboard;
class   IOHIDConsumer;
struct  TransducerData;

class IOHIDEventService: public IOService
{
    OSDeclareAbstractStructors( IOHIDEventService )
    
    friend class IOHIDPointing;
    friend class IOHIDKeyboard;
    friend class IOHIDConsumer;

private:
    IOHIDKeyboard *         _keyboardNub;
    IOHIDPointing *         _pointingNub;
    IOHIDConsumer *         _consumerNub;

    IONotifier *			_publishNotify;
    IORecursiveLock *       _nubLock;
    
    OSArray *               _transducerDataArray;
    
    bool                    _readyForInputReports;


    struct ExpansionData { 
    };
    /*! @var reserved
        Reserved for future use.  (Internal use only)  */
    ExpansionData *         _reserved;
    
    IOHIDPointing *         newPointingShim (
                                UInt32          buttonCount         = 1,
                                IOFixed         pointerResolution   = (400 << 16),
                                IOFixed         scrollResolution    = 0,
                                IOOptionBits    options             = 0 );
                                
    IOHIDKeyboard *         newKeyboardShim (
                                UInt32          supportedModifiers  = 0,
                                IOOptionBits    options             = 0 );

    IOHIDConsumer *         newConsumerShim ( IOOptionBits options = 0 );
    
    void                    parseSupportedElements ( 
                                OSArray *                   elementArray, 
                                UInt32                      bootProtocol );
                                
    void                    processTabletElement ( IOHIDElement * element );

    void                    processTransducerData ();
    
    TransducerData *        createTransducerData ( UInt32 tranducerID );
    
    TransducerData *        getTransducerData ( UInt32 tranducerID );
                                
    IOFixed                 determineResolution ( IOHIDElement * element );
                                    
    static bool 			_publishNotificationHandler(void * target, void * ref, IOService * newService );
    
protected:

    virtual void            free();
        
/*! @function handleStart
    @abstract Prepare the hardware and driver to support I/O operations.
    @discussion IOHIDEventService will call this method from start() before
    any I/O operations are issued to the concrete subclass. Methods
    such as getReportElements() are only called after handleStart()
    has returned true. A subclass that overrides this method should
    begin its implementation by calling the version in super, and
    then check the return value.
    @param provider The provider argument passed to start().
    @result True on success, or false otherwise. Returning false will
    cause start() to fail and return false. */

    virtual bool            handleStart( IOService * provider );

/*! @function handleStop
    @abstract Quiesce the hardware and stop the driver.
    @discussion IOHIDEventService will call this method from stop() to
    signal that the hardware should be quiesced and the driver stopped.
    A subclass that overrides this method should end its implementation
    by calling the version in super.
    @param provider The provider argument passed to stop(). */

    virtual void            handleStop(  IOService * provider );
    
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
    
    virtual OSArray *       getReportElements();

    virtual void            setElementValue (
                                UInt32                      usagePage,
                                UInt32                      usage,
                                UInt32                      value );
    
    virtual UInt32          getElementValue ( 
                                UInt32                      usagePage,
                                UInt32                      usage );
                                
    virtual void            dispatchKeyboardEvent(
                                AbsoluteTime                timeStamp,
                                UInt32                      usagePage,
                                UInt32                      usage,
                                UInt32                      value,
                                IOOptionBits                options = 0 );

    virtual void            dispatchRelativePointerEvent(
                                AbsoluteTime                timeStamp,
                                SInt32                      dx,
                                SInt32                      dy,
                                UInt32                      buttonState,
                                IOOptionBits                options = 0 );
    
    virtual void            dispatchAbsolutePointerEvent(
                                AbsoluteTime                timeStamp,
                                SInt32                      x,
                                SInt32                      y,
                                Bounds *                    bounds,
                                UInt32                      buttonState,
                                bool                        inRange,
                                SInt32                      tipPressure,
                                SInt32                      tipPressureMin,
                                SInt32                      tipPressureMax,
                                IOOptionBits                options = 0 );

    virtual void            dispatchScrollWheelEvent(
                                AbsoluteTime                timeStamp,
                                SInt32                      deltaAxis1,
                                SInt32                      deltaAxis2,
                                SInt32                      deltaAxis3,
                                IOOptionBits                options = 0 );

    virtual void            dispatchTabletPointerEvent(
                                AbsoluteTime                timeStamp,
                                UInt32                      tranducerID,
                                SInt32                      x,
                                SInt32                      y,
                                SInt32                      z,
                                Bounds *                    bounds,
                                UInt32                      buttonState,
                                SInt32                      tipPressure,
                                SInt32                      tipPressureMin,
                                SInt32                      tipPressureMax,
                                SInt32                      barrelPressure,
                                SInt32                      barrelPressureMin,
                                SInt32                      barrelPressureMax,
                                SInt32                      tiltX,
                                SInt32                      tiltY,
                                UInt32                      twist,
                                IOOptionBits                options = 0 );

    virtual void            dispatchTabletProximityEvent(
                                AbsoluteTime                timeStamp,
                                UInt32                      tranducerID,
                                bool                        inRange,
                                bool                        invert,
                                UInt32                      vendorTransducerUniqueID        = 0,
                                UInt32                      vendorTransducerSerialNumber    = 0,
                                IOOptionBits                options                         = 0 );

public:

    virtual bool            init(OSDictionary * properties = 0);

    virtual bool            start( IOService * provider );
    
    virtual void            stop( IOService * provider );

    virtual bool            matchPropertyTable(OSDictionary * table, SInt32 * score);    
    
    virtual IOReturn        setSystemProperties( OSDictionary * properties );
    
    virtual IOReturn        setProperties( OSObject * properties );
    
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  0);
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  1);
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  2);
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  3);
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  4);
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  5);
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  6);
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  7);
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  8);
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  9);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 10);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 11);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 12);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 13);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 14);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 15);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 16);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 17);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 18);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 19);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 20);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 21);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 22);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 23);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 24);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 25);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 26);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 27);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 28);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 29);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 30);
    OSMetaClassDeclareReservedUnused(IOHIDEventService, 31);

};

#endif /* !_IOKIT_HID_IOHIDEVENTSERVICE_H */
