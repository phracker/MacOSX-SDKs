/*
 * Copyright (c) 2002-2004 Apple Computer, Inc. All rights reserved.
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
    @header CHUD Tools API Timebase Functions and Constants. 
    @discussion The CHUD Tools API provides access to the time base registers in each PowerPC processor. It also provides ways to convert data retrieved from the time base registers into different time units.
 */
 
#ifdef __cplusplus
extern "C" {
#endif

/*!
    @typedef chud_time_unit_t
    @abstract The CHUD framework support measuring the passage of time in a variety of sizes.
    @discussion These constants represent the fractions of time that CHUD can measure and report measurements in.
    @constant chudTimeBaseTicks Typically the time-base frequency will be a fraction of the processor bus frequency
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
/*!
 @function chudTimeBaseGetUptime
 @discussion Read the elapsed timebase 'ticks' register. This ticks register in the most accurate user-accessible device in any Mac.
 @param *result Storage for the timebase register contents
 @result void
 */
void	chudTimeBaseGetUptime( uint64_t *result );

/*!
 @function chudReadTimeBase
 @discussion Return the timebase count from a cpu.  Value calculated as chud_time_unit_t.
 @param dev Processor device to retrieve from
 @param units Timebase calculation type
 @result a double with the timebase tick count converted to whatever units specified
 */
double  chudReadTimeBase( chud_time_unit_t units ); 

/*!
 @function chudConvertTime
 @discussion Convert time_in to any chud_time_unit_t
 @param time_in Time value
 @param units_in Input units
 @param units_ret Return units
 @result a double with the converted time value
 */
double  chudConvertTime( double time_in, chud_time_unit_t units_in, chud_time_unit_t units_ret );
#endif /* !CHUD_KEXT */

#ifdef __cplusplus
}
#endif

#endif /* CHUD_TIMEBASE_H */