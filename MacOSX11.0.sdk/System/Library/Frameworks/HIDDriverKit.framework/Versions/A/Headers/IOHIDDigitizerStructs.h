/*
 * Copyright (c) 2018-2019 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#ifndef IOHIDDigitizerStructs_h
#define IOHIDDigitizerStructs_h

/*!
 * @typedef IOHIDDigitizerStylusData
 *
 * @abstract
 * Digitizer stylus data that gets passed in to the dispatchDigitizerStylusEvent 
 * call in the IOHIDEventService class.
 *
 * @field identifier
 * A unique stylus identifier.
 *
 * @field x
 * A X value between 0.0 and 1.0.
 *
 * @field y
 * A Y value between 0.0 and 1.0.
 *
 * @field tipPressure
 * The tip pressure value between 0.0 and 1.0.
 *
 * @field barrelPressure
 * The barrel pressure value between 0.0 and 1.0.
 *
 * @field tiltX
 * The tilt of the stylus across the x-axis.
 *
 * @field tiltY
 * The tilt of the stylus across the y-axis.
 *
 * @field twist
 * The clockwise rotation of the stylus.
 *
 * @field pointerType
 * Optional pointer type defined by vendor.
 *
 * @field effect
 * Optional stylus effect defined by vendor.
 *
 * @field uniqueID
 * Optional stylus unique identifier.
 * 
 * @field inRange
 * True if the stylus is in range.
 *
 * @field tip
 * True if the tip of the stylus is in contact with the surface of the digitizer.
 *
 * @field barrelSwitch
 * True if the barrel switch button is pressed.
 *
 * @field invert
 * True if the stylus is inverted.
 *
 * @field eraser
 * True if the inverted stylus is in contact with the surface of the digitizer.
 *
 * @field tipChanged
 * True if the tip variable has changed since the last event was dispatched
 * (e.g. 0 -> 1 or 1 -> 0).
 *
 * @field positionChanged
 * True if the x or y position has changed since the last event was dispatched.
 *
 * @field rangeChanged
 * True if the range variable has changed since the last event was dispatched.
 */
typedef struct IOHIDDigitizerStylusData {
    uint32_t identifier;
    IOFixed x;
    IOFixed y;
    IOFixed tipPressure;
    IOFixed barrelPressure;
    IOFixed tiltX;
    IOFixed tiltY;
    IOFixed twist;
    uint32_t pointerType;
    uint32_t effect;
    uint64_t uniqueID;
    uint32_t inRange : 1;
    uint32_t tip : 1;
    uint32_t barrelSwitch : 1;
    uint32_t invert : 1;
    uint32_t eraser : 1;
    
    uint32_t tipChanged : 1;
    uint32_t positionChanged : 1;
    uint32_t rangeChanged : 1;
} IOHIDDigitizerStylusData;

/*!
 * @typedef IOHIDDigitizerTouchData
 *
 * @abstract
 * Digitizer touch data that gets passed in to the dispatchDigitizerTouchEvent 
 * call in the IOHIDEventService class.
 *
 * @field identifier
 * A unique contact identifier.
 *
 * @field x
 * A X value between 0.0 and 1.0.
 *
 * @field y
 * A Y value between 0.0 and 1.0.
 *
 * @field inRange
 * True if the finger is in range.
 *
 * @field touch
 * True if the finger is in contact with the surface of the digitizer.
 *
 * @field touchValid
 * True if the touch contact was intended. The device should report 0 if the
 * contact is not a valid touch.
 *
 * @field touchChanged
 * True if the touch variable has changed since the last event was dispatched 
 * (e.g. 0 -> 1 or 1 -> 0).
 *
 * @field positionChanged
 * True if the x or y position has changed since the last event was dispatched.
 *
 * @field rangeChanged
 * True if the range variable has changed since the last event was dispatched.
 */
typedef struct IOHIDDigitizerTouchData {
    uint32_t identifier;
    IOFixed x;
    IOFixed y;
    uint32_t inRange : 1;
    uint32_t touch : 1;
    uint32_t touchValid : 1;
    
    uint32_t touchChanged : 1;
    uint32_t positionChanged : 1;
    uint32_t rangeChanged : 1;
} IOHIDDigitizerTouchData;

#endif /* IOHIDDigitizerStructs_h */
