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

#ifndef CHUD_TIMER_H
#define CHUD_TIMER_H
/*!
 @header CHUD Tools Timer Functions: 
 @discussion In the CHUD Tools API, the "timer device" is an abstraction built on top of the Processors' decrementer register for making accurate timing decisions during sampling. CHUD Tools have a average minimum sampling time-interval of 60 micro-seconds. Which is orders of magnitude smaller than the soft timers in the OS. And that is with recording over a dozen performance counter values, and the program counter at each sample point. See the chudTimebase.h documentation for a explanation of the chud_time_unit_t data type.
 */
 

#include <CHUDCore/chudTimeBase.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 @function chudSetupTimer
 @discussion Setup timer sampling
 @param period Number of units per sample
 @param period_units Units for period
 @param delay_period Number of units delay before sampling begins
 @param delay_scale Units for delay_period
 @param max_samples Maximum number of samples allowed
 @result chudSuccess
 */
int 	chudSetupTimer( int period, chud_time_unit_t period_units, int delay_period, chud_time_unit_t delay_period_units, int maxSamples );
                     
/*!
 @function chudGetTimerSetup
 @discussion Retrieve the timer sampling information
 @param *period Storage for number of units per sample
 @param *p_units Storage for units for period
 @param *delay Storage for number of units delay before sampling begins
 @param *d_units Storage for units for delay_period
 @param *max_samples Storage for maximum number of samples allowed
 @result void
 */
int	chudGetTimerSetup( int *period, chud_time_unit_t *p_units, int *delay, chud_time_unit_t *d_units, int *max_samples );

/*!
 @function chudSetTimerPeriod
 @discussion Set the time between timer samples
 @param period Number of units between samples
 @param period_scale Units for period
*/
int	chudSetTimerPeriod( int period, chud_time_unit_t period_units );
/*!
 @function chudGetTimerPeriod
 @discussion Get timer period between samples
 @param *period Storage for number of units per sample
 @param *period_scale Storage for units for period
 @result chudSuccess
 */
int	chudGetTimerPeriod( int *period, chud_time_unit_t *period_units );

#ifdef __cplusplus
}
#endif

#endif /* CHUD_TIMER_H */