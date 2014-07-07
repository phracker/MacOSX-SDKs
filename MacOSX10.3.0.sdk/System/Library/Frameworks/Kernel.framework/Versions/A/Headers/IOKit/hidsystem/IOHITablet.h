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
#ifndef _IOHITABLET_H
#define _IOHITABLET_H

#include <IOKit/hidsystem/IOHIPointing.h>
#include <IOKit/hidsystem/IOLLEvent.h>

class IOHITabletPointer;

#define kIOHIVendorID		"VendorID"
#define kIOHISystemTabletID	"SystemTabletID"
#define kIOHIVendorTabletID	"VendorTabletID"

typedef void (*TabletEventAction)(OSObject		*target,
                                  NXEventData	*tabletData,	// Do we want to parameterize this?
                                  AbsoluteTime ts);

typedef void (*ProximityEventAction)(OSObject		*target,
                                     NXEventData	*proximityData,	// or this?
                                     AbsoluteTime ts);

/* Event Callback Definitions */
typedef void (*TabletEventCallback)(
                        /* target */       OSObject *    target,
                        /* event */        NXEventData * tabletData,
                        /* atTime */       AbsoluteTime  ts,
                        /* sender */       OSObject *    sender,
                        /* refcon */       void *        refcon);

typedef void (*ProximityEventCallback)(
                        /* target */       OSObject *    target,
                        /* event */        NXEventData * proximityData,
                        /* atTime */       AbsoluteTime  ts,
                        /* sender */       OSObject *    sender,
                        /* refcon */       void *        refcon);
                                  
class IOHITablet : public IOHIPointing
{
    OSDeclareDefaultStructors(IOHITablet);

public:
    UInt16		_systemTabletID;

private:
    OSObject *				_tabletEventTarget;
    TabletEventAction		_tabletEventAction;
    OSObject *				_proximityEventTarget;
    ProximityEventAction	_proximityEventAction;

protected:
    virtual void dispatchTabletEvent(NXEventData *tabletEvent,
                                     AbsoluteTime ts);

    virtual void dispatchProximityEvent(NXEventData *proximityEvent,
                                        AbsoluteTime ts);

    virtual bool startTabletPointer(IOHITabletPointer *pointer, OSDictionary *properties);

public:
    static UInt16 generateTabletID();

    virtual bool init(OSDictionary * propTable);
    virtual bool open(IOService *	client,
                      IOOptionBits	options,
                      RelativePointerEventAction	rpeAction,
                      AbsolutePointerEventAction	apeAction,
                      ScrollWheelEventAction		sweAction,
                      TabletEventAction			tabletAction,
                      ProximityEventAction		proximityAction);

    bool open(        IOService *			client,
                      IOOptionBits			options,
                      void *,
                      RelativePointerEventCallback	rpeCallback,
                      AbsolutePointerEventCallback	apeCallback,
                      ScrollWheelEventCallback		sweCallback,
                      TabletEventCallback		tabletCallback,
                      ProximityEventCallback		proximityCallback);
                      
private:

  static void _tabletEvent(IOHITablet *self,
                           NXEventData *tabletData,
                           AbsoluteTime ts);

  static void _proximityEvent(IOHITablet *self,
                              NXEventData *proximityData,
                              AbsoluteTime ts);


};

#endif /* !_IOHITABLET_H */
