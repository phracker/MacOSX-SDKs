/*
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
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
#ifndef _IOHIPOINTING_H
#define _IOHIPOINTING_H

#include <IOKit/hidsystem/IOHIPointing.h>
#include <IOKit/hidsystem/IOHIDevice.h>
#include <IOKit/hidsystem/IOHIDTypes.h>

/* Start Action Definitions */

/*
 * HISTORICAL NOTE:
 *   The following entry points were part of the IOHIPointingEvents
 *   protocol.
 */
typedef void (*RelativePointerEventAction)(OSObject * target,
                        /* buttons */      int        buttons,
                        /* deltaX */       int        dx,
                        /* deltaY */       int        dy,
                        /* atTime */       AbsoluteTime ts);

typedef void (*AbsolutePointerEventAction)(OSObject * target,
                        /* buttons */      int        buttons,
                        /* at */           Point *    newLoc,
                        /* withBounds */   Bounds *   bounds,
                        /* inProximity */  bool       proximity,
                        /* withPressure */ int        pressure,
                        /* withAngle */    int        stylusAngle,
                        /* atTime */       AbsoluteTime ts);

typedef void (*ScrollWheelEventAction)(OSObject * target,
                                       short      deltaAxis1,
                                       short      deltaAxis2,
                                       short      deltaAxis3,
                                       AbsoluteTime ts);

/* End Action Definitions */
class IOHIDPointingDevice;

class IOHIPointing : public IOHIDevice
{
    OSDeclareDefaultStructors(IOHIPointing);

private:
    IOLock *		_deviceLock;  // Lock for all device access
    int			_buttonMode;  // The "handedness" of the pointer
    IOFixed		_acceleration;
    bool		_convertAbsoluteToRelative;
    bool		_contactToMove;
    bool		_hadContact;
    Point		_previousLocation;
    UInt8		_pressureThresholdToClick;	// A scale factor of 0 to 255 to determine how much pressure is necessary to generate a primary mouse click - a value of 255 means no click will be generated
    void *		_scaleSegments;
    IOItemCount		_scaleSegCount;
    IOFixed		_fractX;
    IOFixed		_fractY;

    OSObject *                 _relativePointerEventTarget;
    RelativePointerEventAction _relativePointerEventAction;
    OSObject *                 _absolutePointerEventTarget;
    AbsolutePointerEventAction _absolutePointerEventAction;
    OSObject *                 _scrollWheelEventTarget;
    ScrollWheelEventAction     _scrollWheelEventAction;
    
    #define SCROLL_TIME_DELTA_COUNT		8

    struct ExpansionData { 
    
        // Added for scroll whell accel support
        IOFixed		scrollAcceleration;
        void *		scrollScaleSegments;
        IOItemCount	scrollScaleSegCount;

        UInt32		scrollTimeDeltas1[SCROLL_TIME_DELTA_COUNT];
        UInt32		scrollTimeDeltas2[SCROLL_TIME_DELTA_COUNT];
        UInt32		scrollTimeDeltas3[SCROLL_TIME_DELTA_COUNT];
        UInt8 		scrollTimeDeltaIndex1;
        UInt8 		scrollTimeDeltaIndex2;
        UInt8 		scrollTimeDeltaIndex3;
        int		scrollLastDeltaAxis1;
        int		scrollLastDeltaAxis2;
        int		scrollLastDeltaAxis3;
        AbsoluteTime	scrollLastEventTime1;
        AbsoluteTime	scrollLastEventTime2;
        AbsoluteTime	scrollLastEventTime3;

        // Added to post events to the HID Manager
        IOHIDPointingDevice  * hidPointingNub;

    };

    void *  _reserved;
    
    #define _scrollAcceleration		((ExpansionData *)_reserved)->scrollAcceleration
    #define _scrollScaleSegments 	((ExpansionData *)_reserved)->scrollScaleSegments
    #define _scrollScaleSegCount 	((ExpansionData *)_reserved)->scrollScaleSegCount
    #define _scrollTimeDeltas1		((ExpansionData *)_reserved)->scrollTimeDeltas1
    #define _scrollTimeDeltas2		((ExpansionData *)_reserved)->scrollTimeDeltas2
    #define _scrollTimeDeltas3		((ExpansionData *)_reserved)->scrollTimeDeltas3
    #define _scrollTimeDeltaIndex1	((ExpansionData *)_reserved)->scrollTimeDeltaIndex1
    #define _scrollTimeDeltaIndex2	((ExpansionData *)_reserved)->scrollTimeDeltaIndex2
    #define _scrollTimeDeltaIndex3	((ExpansionData *)_reserved)->scrollTimeDeltaIndex3
    #define _scrollLastDeltaAxis1	((ExpansionData *)_reserved)->scrollLastDeltaAxis1
    #define _scrollLastDeltaAxis2	((ExpansionData *)_reserved)->scrollLastDeltaAxis2
    #define _scrollLastDeltaAxis3	((ExpansionData *)_reserved)->scrollLastDeltaAxis3
    #define _scrollLastEventTime1	((ExpansionData *)_reserved)->scrollLastEventTime1
    #define _scrollLastEventTime2	((ExpansionData *)_reserved)->scrollLastEventTime2
    #define _scrollLastEventTime3	((ExpansionData *)_reserved)->scrollLastEventTime3

    #define _hidPointingNub		((ExpansionData *)_reserved)->hidPointingNub

protected:
  virtual void dispatchRelativePointerEvent(int        dx,
                                            int        dy,
                                            UInt32     buttonState,
                                            AbsoluteTime ts);
    
  virtual void dispatchAbsolutePointerEvent(Point *	newLoc,
                                            Bounds *	bounds,
                                            UInt32	buttonState,
                                            bool	proximity,
                                            int		pressure,
                                            int		pressureMin,
                                            int		pressureMax,
                                            int		stylusAngle,
                                            AbsoluteTime	ts);

  virtual void dispatchScrollWheelEvent(short deltaAxis1,
                                        short deltaAxis2,
                                        short deltaAxis3,
                                        AbsoluteTime ts);

public:
  virtual bool init(OSDictionary * properties = 0);
  virtual bool start(IOService * provider);
  virtual void stop( IOService * provider );
  virtual void free();

  virtual bool open(IOService *                client,
		    IOOptionBits	       options,
                    RelativePointerEventAction rpeAction,
                    AbsolutePointerEventAction apeAction,
                    ScrollWheelEventAction     sweAction);
  virtual void close(IOService * client, IOOptionBits );

  virtual IOHIDKind hidKind();
  virtual bool 	    updateProperties( void );
  virtual IOReturn  setParamProperties( OSDictionary * dict );
  virtual IOReturn  powerStateWillChangeTo( IOPMPowerFlags powerFlags,
                        unsigned long newState, IOService * device);
  virtual IOReturn  powerStateDidChangeTo( IOPMPowerFlags powerFlags,
                        unsigned long newState, IOService * device);

protected: // for subclasses to implement
  virtual OSData *    copyAccelerationTable();
  virtual IOItemCount buttonCount();
  virtual IOFixed     resolution();

  // RY: Adding method to copy scroll wheel accel table.
  // Unfortunately, we don't have any padding, so this
  // is going to be non-virtual.
  /*virtual*/ OSData * copyScrollAccelerationTable();

private:
  virtual bool resetPointer();
  virtual void scalePointer(int * dxp, int * dyp);
  virtual void setupForAcceleration(IOFixed accl);
  
  // RY: Adding methods to support scroll wheel accel.
  // Unfortunately, we don't have any padding, so these
  // are going to be non-virtual.
  /*virtual*/ bool 	resetScroll();
  /*virtual*/ void 	scaleScrollAxes(int * axis1p, int * axis2p, int * axis3p);
  /*virtual*/ void 	setupScrollForAcceleration(IOFixed accl);
  
  // RY: We have to make sure that subclasses that will 
  // take advantage of this have their defined resolution 
  // in their property table.
  /*virtual*/ IOFixed	scrollResolution();
};

#endif /* !_IOHIPOINTING_H */
