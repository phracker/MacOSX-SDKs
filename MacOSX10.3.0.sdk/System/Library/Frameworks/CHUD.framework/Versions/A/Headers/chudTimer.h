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

#ifndef CHUD_TIMER_H
#define CHUD_TIMER_H

#include <CHUD/chudTimeBase.h>

#ifdef __cplusplus
extern "C" {
#endif

int 	chudSetupTimer( int period, chud_time_unit_t period_units, int delay_period, chud_time_unit_t delay_period_units, int maxSamples );
                     
int	chudGetTimerSetup( int *period, chud_time_unit_t *p_units, int *delay, chud_time_unit_t *d_units, int *max_samples );

int	chudSetTimerPeriod( int period, chud_time_unit_t period_units );
int	chudGetTimerPeriod( int *period, chud_time_unit_t *period_units );

#ifdef __cplusplus
}
#endif

#endif /* CHUD_TIMER_H */