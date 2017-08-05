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


class DigitizerTransducer;
class EventElementCollection;
class IOHIDEvent;

/*! @class IOHIDEventDriver : public IOHIDEventService
    @abstract
    @discussion
*/
class IOHIDEventDriver: public IOHIDEventService
{
    OSDeclareDefaultStructors( IOHIDEventDriver )

private:
    IOHIDInterface *            _interface;
    void *                      _reservedVoid[3] __unused;
    
    OSArray *                   _supportedElements;
        
    UInt32                      _bootSupport;
    bool                        _multipleReports;
    bool                        _authenticatedDevice;
    bool                        _reservedBool   __unused;
    UInt32                      _reservedUInt32 __unused;
    bool                        _reservedBool1  __unused;
    
    
    struct ExpansionData {
        SInt32  absoluteAxisRemovalPercentage;
        SInt32  preferredAxisRemovalPercentage;
        
        struct {
            OSArray *           elements;
        } led;
        
        struct {
            OSArray *           elements;
        } scroll;
        
        struct {
            OSArray *           elements;
            bool                disabled;
        } relative;
        
        struct {
            OSArray *           elements;
            UInt8               bootMouseData[4];
            bool                appleVendorSupported;
        } keyboard;
        
        struct {
            IOHIDElement *      deviceModeElement;
            OSArray *           transducers;
            IOHIDElement *      touchCancelElement;
            bool                native;
            bool                collectionDispatch;
            IOFixed             centroidX;
            IOFixed             centroidY;
        } digitizer;
        
        struct {
            OSArray *           elements;

            UInt32              capable;
            UInt32              sendingReportID;
            IOFixed             axis[6];
            UInt32              buttonState;
            IOOptionBits        options;            
            bool                disabled;
        } multiAxis;
        
        struct {
            IOHIDElement *      gestureStateElement;
            OSArray *           legacyElements;
            OSArray *           gesturesCandidates;
        } unicode;
        
        struct {
            bool                extended;
            bool                formFitting;
            OSArray *           elements;
            UInt32              capable;
            UInt32              sendingReportID;
            
            struct {
                IOFixed up;
                IOFixed down;
                IOFixed left;
                IOFixed right;
            } dpad;
            
            struct {
                IOFixed x;
                IOFixed y;
                IOFixed a;
                IOFixed b;
            }face;
            
            struct {
                IOFixed x;
                IOFixed y;
                IOFixed z;
                IOFixed rz;
            } joystick;
            
            struct {
                IOFixed l1;
                IOFixed l2;
                IOFixed r1;
                IOFixed r2;
            } shoulder;

        } gameController;
      
        struct {
            OSArray *           elements;
            OSArray *           pendingEvents;
        } vendorMessage;
        
        struct {
            OSArray *           elements;
        } biometric;

        UInt64  lastReportTime;
    };
    ExpansionData *             _reserved;
    
    bool                    parseElements(OSArray * elementArray, UInt32 bootProtocol);
    bool                    parseRelativeElement(IOHIDElement * element);
    bool                    parseMultiAxisElement(IOHIDElement * element);
    bool                    parseGameControllerElement(IOHIDElement * element);
    bool                    parseDigitizerElement(IOHIDElement * element);
    bool                    parseDigitizerTransducerElement(IOHIDElement * element, IOHIDElement * parent=NULL);
    bool                    parseScrollElement(IOHIDElement * element);
    bool                    parseLEDElement(IOHIDElement * element);
    bool                    parseKeyboardElement(IOHIDElement * element);
    bool                    parseUnicodeElement(IOHIDElement * element);
    bool                    parseLegacyUnicodeElement(IOHIDElement * element);
    bool                    parseGestureUnicodeElement(IOHIDElement * element);
    bool                    parseVendorMessageElement(IOHIDElement * element);
    bool                    parseBiometricElement(IOHIDElement * element);
  
    void                    processDigitizerElements();
    void                    processMultiAxisElements();
    void                    processGameControllerElements();
    void                    processUnicodeElements();
    
    void                    setRelativeProperties();
    void                    setDigitizerProperties();
    void                    setGameControllerProperties();
    void                    setMultiAxisProperties();
    void                    setScrollProperties();
    void                    setLEDProperties();
    void                    setKeyboardProperties();
    void                    setUnicodeProperties();
    void                    setAccelerationProperties();
    void                    setVendorMessageProperties();
    void                    setBiometricProperties();

    UInt32                  checkGameControllerElement(IOHIDElement * element);
    UInt32                  checkMultiAxisElement(IOHIDElement * element);
    
    static void             calibrateJustifiedPreferredStateElement(IOHIDElement * element, SInt32 removalPercentage);
    static void             calibrateCenteredPreferredStateElement(IOHIDElement * element, SInt32 removalPercentage);

    void                    handleBootPointingReport(AbsoluteTime timeStamp, IOMemoryDescriptor * report, UInt32 reportID);
    void                    handleRelativeReport(AbsoluteTime timeStamp, UInt32 reportID);
    void                    handleGameControllerReport(AbsoluteTime timeStamp, UInt32 reportID);
    void                    handleMultiAxisPointerReport(AbsoluteTime timeStamp, UInt32 reportID);
    void                    handleDigitizerCollectionReport(AbsoluteTime timeStamp, UInt32 reportID);
    void                    handleDigitizerReport(AbsoluteTime timeStamp, UInt32 reportID);
    IOHIDEvent*             handleDigitizerTransducerReport(DigitizerTransducer * transducer, AbsoluteTime timeStamp, UInt32 reportID);
    void                    handleScrollReport(AbsoluteTime timeStamp, UInt32 reportID);
    void                    handleKeboardReport(AbsoluteTime timeStamp, UInt32 reportID);
    void                    handleUnicodeReport(AbsoluteTime timeStamp, UInt32 reportID);
    void                    handleUnicodeLegacyReport(AbsoluteTime timeStamp, UInt32 reportID);
    void                    handleUnicodeGestureReport(AbsoluteTime timeStamp, UInt32 reportID);
    IOHIDEvent *            handleUnicodeGestureCandidateReport(EventElementCollection * candidate, AbsoluteTime timeStamp, UInt32 reportID);

    void                    handleVendorMessageReport(AbsoluteTime timeStamp, IOMemoryDescriptor * report, UInt32 reportID, int phase);
    void                    handleBiometricReport(AbsoluteTime timeStamp, UInt32 reportID);
  
    bool                    serializeCharacterGestureState(void * ref, OSSerialize * serializer);
    bool                    conformTo (UInt32 usagePage, UInt32 usage);
    IOHIDEvent*             createDigitizerTransducerEventForReport(DigitizerTransducer * transducer, AbsoluteTime timeStamp, UInt32 reportID);
    bool                    serializeDebugState(void * ref, OSSerialize * serializer);

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

    virtual IOReturn        setElementValue (
                                UInt32                      usagePage,
                                UInt32                      usage,
                                UInt32                      value );
    
    virtual UInt32          getElementValue ( 
                                UInt32                      usagePage,
                                UInt32                      usage );

    virtual void            dispatchEvent(IOHIDEvent * event, IOOptionBits options=0);

public:


    virtual bool            init( OSDictionary * dictionary = 0 );

    virtual bool            didTerminate(
                                IOService *                 provider,
                                IOOptionBits                options,
                                bool *                      defer );

    virtual IOReturn        setProperties( OSObject * properties );
  
  
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
