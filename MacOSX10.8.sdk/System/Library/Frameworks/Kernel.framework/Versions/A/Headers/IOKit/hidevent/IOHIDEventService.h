/*
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 1999-2009 Apple Computer, Inc.  All Rights Reserved.
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

#include <TargetConditionals.h>

#include <IOKit/IOService.h>
#include <IOKit/IOWorkLoop.h>
#include <IOKit/IOTimerEventSource.h>
#include <IOKit/hidsystem/IOHIDTypes.h>
#include <IOKit/hid/IOHIDInterface.h>
#include <IOKit/hid/IOHIDElement.h>
#include <IOKit/hid/IOHIDKeys.h>

#if TARGET_OS_EMBEDDED
    #include <IOKit/hid/IOHIDEvent.h>
#endif

enum 
{
    kHIDDispatchOptionPointerNoAcceleration            = 0x01,
    kHIDDispatchOptionPointerAffixToScreen             = 0x02,
    kHIDDispatchOptionPointerAbsolutToRelative         = 0x04
};

enum
{
    kHIDDispatchOptionScrollNoAcceleration      = 0x001,

    kHIDDispatchOptionScrollMomentumAny         = 0x00e,
    kHIDDispatchOptionScrollMomentumContinue    = 0x002,
    kHIDDispatchOptionScrollMomentumStart       = 0x004,
    kHIDDispatchOptionScrollMomentumEnd         = 0x008,
    
    kHIDDispatchOptionPhaseAny                  = 0xff0,
    kHIDDispatchOptionPhaseBegan                = 0x010,
    kHIDDispatchOptionPhaseChanged              = 0x020,
    kHIDDispatchOptionPhaseEnded                = 0x040,
    kHIDDispatchOptionPhaseCanceled             = 0x080,
    kHIDDispatchOptionPhaseMayBegin             = 0x800,
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
    friend class AppleEmbeddedKeyboard;
    friend class IOHIDEventServiceUserClient;

private:
    IOHIDKeyboard *         _keyboardNub;
    IOHIDPointing *         _pointingNub;
    IOHIDConsumer *         _consumerNub;

    IONotifier *			_publishNotify;
    IORecursiveLock *       _nubLock;
    
    OSArray *               _transducerDataArray;
    
    bool                    _readyForInputReports;


    struct ExpansionData { 
		IOService *				provider;
        IOWorkLoop *            workLoop;
        UInt32                  ejectDelayMS;
        IOTimerEventSource 	*   ejectTimerEventSource;
        UInt32                  ejectState;
        IOOptionBits            ejectOptions;
        UInt32                  capsDelayMS;
        IOTimerEventSource 	*   capsTimerEventSource;
        UInt32                  capsState;
        IOOptionBits            capsOptions;
        OSArray *               deviceUsagePairs;
        IOCommandGate       *   commandGate;
        
#if TARGET_OS_EMBEDDED
        OSDictionary *          clientDict;
        UInt32                  debuggerMask;
        UInt32                  startDebuggerMask;
        IOTimerEventSource *    debuggerTimerEventSource;
        bool                    shouldSwapISO;
        
        bool                    previousRangeState;
        SInt32                  previousX;
        SInt32                  previousY;
        bool                    prevousTouchState;
#endif
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
                                    
    static bool 			_publishMatchingNotificationHandler(void * target, void * ref, IOService * newService, IONotifier * notifier);

    void                    ejectTimerCallback(IOTimerEventSource *sender);

    void                    capsTimerCallback(IOTimerEventSource *sender);
    
#if TARGET_OS_EMBEDDED
    void                    debuggerTimerCallback(IOTimerEventSource *sender);
#endif
	void					calculateCapsLockDelay();
    
    void                    calculateStandardType();

protected:

    virtual void            free();
        
/*! @function handleOpen
    @abstract Handle a client open on the interface.
    @discussion This method is called by IOService::open() with the
    arbitration lock held, and must return true to accept the client open.
    This method will in turn call handleClientOpen() to qualify the client
    requesting the open.
    @param client The client object that requested the open.
    @param options Options passed to IOService::open().
    @param argument Argument passed to IOService::open().
    @result true to accept the client open, false otherwise. */

    virtual bool handleOpen(IOService *  client,
                            IOOptionBits options,
                            void *       argument);

/*! @function handleClose
    @abstract Handle a client close on the interface.
    @discussion This method is called by IOService::close() with the
    arbitration lock held. This method will in turn call handleClientClose()
    to notify interested subclasses about the client close. If this represents
    the last close, then the interface will also close the controller before
    this method returns. The controllerWillClose() method will be called before
    closing the controller. Subclasses should not override this method.
    @param client The client object that requested the close.
    @param options Options passed to IOService::close(). */

    virtual void handleClose(IOService * client, IOOptionBits options);

/*! @function handleIsOpen
    @abstract Query whether a client has an open on the interface.
    @discussion This method is always called by IOService with the
    arbitration lock held. Subclasses should not override this method.
    @result true if the specified client, or any client if none (0) is
    specified, presently has an open on this object. */

    virtual bool handleIsOpen(const IOService * client) const;

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
                                IOGBounds *                 bounds,
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
                                IOGBounds *                 bounds,
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
    bool                    readyForReports();

    virtual bool            init(OSDictionary * properties = 0);

    virtual bool            start( IOService * provider );
    
    virtual void            stop( IOService * provider );

    virtual bool            matchPropertyTable(OSDictionary * table, SInt32 * score);    
    
    virtual IOReturn        setSystemProperties( OSDictionary * properties );
    
    virtual IOReturn        setProperties( OSObject * properties );
    
protected:
    OSMetaClassDeclareReservedUsed(IOHIDEventService,  0);
    virtual OSArray *       getDeviceUsagePairs();
    
        
#if TARGET_OS_EMBEDDED
public:
    typedef void (*Action)(OSObject *target, OSObject * sender, void *context, OSObject *event, IOOptionBits options);

    OSMetaClassDeclareReservedUsed(IOHIDEventService,  1);
    virtual bool            open(
                                IOService *                 client,
                                IOOptionBits                options,
                                void *                      context,
                                Action                      action);
                                
protected:    
    OSMetaClassDeclareReservedUsed(IOHIDEventService,  2);
    virtual void            dispatchEvent(IOHIDEvent * event, IOOptionBits options=0);

    OSMetaClassDeclareReservedUsed(IOHIDEventService,  3);
    virtual UInt32          getPrimaryUsagePage();
    
    OSMetaClassDeclareReservedUsed(IOHIDEventService,  4);
    virtual UInt32          getPrimaryUsage();
    
    OSMetaClassDeclareReservedUsed(IOHIDEventService,  5);
    virtual UInt32          getReportInterval();

public:    
    OSMetaClassDeclareReservedUsed(IOHIDEventService,  6);
    virtual IOHIDEvent *    copyEvent(
                                IOHIDEventType              type, 
                                IOHIDEvent *                matching = 0,
                                IOOptionBits                options = 0);
#else
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  1);
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  2);
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  3);
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  4);
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  5);
    OSMetaClassDeclareReservedUnused(IOHIDEventService,  6);
#endif    
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
    
#if TARGET_OS_EMBEDDED
public:
    virtual void            close( IOService * forClient, IOOptionBits options = 0 );
    
private:
    bool                    openGated( IOService *client, IOOptionBits options, void *context, Action action);
    void                    closeGated( IOService * forClient, IOOptionBits options = 0 );
#endif

};

#endif /* !_IOKIT_HID_IOHIDEVENTSERVICE_H */
