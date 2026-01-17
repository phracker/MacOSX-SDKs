/*
 * Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
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

#ifndef CHUD_TIMEBASE_H
#define CHUD_TIMEBASE_H

/*!
    @header CHUD Timebase Constants
 */
 
#ifdef __cplusplus
extern "C" {
#endif

/*!
    @typedef chud_time_unit_t
    @abstract The CHUD framework support measuring the passage of time in a variety of sizes.
    @discussion These constants represent the fractions of time that CHUD can measure and report measurements in.
    @constant chudTimeBaseTicks Typically the timebase frequency will be a fraction of the processor bus frequency
    @constant chudNanoSeconds
    @constant chudMicroSeconds
    @constant chudMilliSeconds
    @constant chudSeconds
    @constant chudCPUCycles
    @constant chudBusCycles
 */
typedef enum {
    chudTimeBaseTicks	= 1,
    chudNanoSeconds	= 2,
    chudMicroSeconds	= 3,
    chudMilliSeconds	= 4,
    chudSeconds		= 5,
    chudCPUCycles	= 6,
    chudBusCycles	= 7
} chud_time_unit_t;

#define ATHOUSAND 1000.0   //milli
#define AMILLION  1000000.0 //micro
#define ABILLION  1000000000.0 //nano

#ifndef CHUD_KEXT
double  chudReadTimeBase( chud_time_unit_t units ); 

double	chudTimebaseResult( chud_device_t dev, chud_time_unit_t units );

double  chudConvertTime( double time_in, chud_time_unit_t units_in, chud_time_unit_t units_ret );
#endif /* !CHUD_KEXT */

#ifdef __cplusplus
}
#endif

#endif /* CHUD_TIMEBASE_H */