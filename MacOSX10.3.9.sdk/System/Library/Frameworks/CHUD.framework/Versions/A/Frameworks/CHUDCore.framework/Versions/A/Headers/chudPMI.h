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
/*!
  @header CHUD Processor Monitor Interrupt (PMI) Functions
  The CHUD Tools API Processor Monitor Interrupt (PMI) functions provide a mechanism to select a particular performance monitor counter (PMC) to be used as a sampling trigger. If a PMC is used as a trigger, each time the PMC reaches a preset number of events counted all the other PMCs are sampled.  PMI can be used with processor PMCs or operating system PMCs. Not all processors support PMI. PPC 750, PPC 7400, and PPC 7410 (before version 3) processor architectures do NOT support the PMI feature.
*/

#ifndef CHUD_PMI_H
#define CHUD_PMI_H

#include <CHUDCore/chudTimeBase.h>

#ifdef __cplusplus
extern "C" {
#endif
 
 /*!
 @function chudSupportsPMI
 @discussion report whether Performance Monitor Interrupt feature is available on the current CPU
 @param dev chud_device_t either chudCPU1Dev, or chudAltCPU1Dev
 @result 1=Yes, 0=No whether the cpu supports PMI
 */
int	chudSupportsPMI( chud_device_t dev );

 /*!
 @function chudSetupPMI
 @discussion Set up the pmc's to trigger Performance Monitor Interrupts
 whenever PMC_n on <cpu> registers <evtct> events of type <evt>.
 this way other PMCs can measure event counts with respect to
 the count of a certain event on PMC_n. 
 @param dev which device to set pmi on, 
 @param pmc_modes a list of what to do with the device counters. 
 one entry should be chudTrigger, 
 the others can be chudUnused, or chudCounter
 @param trigger_evt which event on the TRIGGER PMC to select
 @param trigger_ct how many events to count before triggering a PMI
 @param delay_time time to delay before start of sampling
 @param delay_time_units units of time to delay before start of sampling
 @param max_samples maximum number of samples to take 
 @result  chudStatus:  chudSuccess, chudBadDeviceID, chudBadPmcID
 */
int	chudSetupPMI( chud_device_t dev, int trigger_pmc, int trigger_evt, int trigger_ct, int delay_time, chud_time_unit_t delay_time_units, int max_samples );
/*!
 @function chudGetPMISetup
 @discussion Retrieve the timer sampling info: timer period,
 maximum number of samples, the delay (in microseconds before the start 
 of sampling. Input: storage for each of the sampling info items
 @param dev the device that is set up to generate PMIs
 @param *trigger_pmc which register is set to cause PMI's when it overflows
 @param *trigger_evt which performance event is selected on the trigger_pmc
 @param *trigger_ct the number of events that must elapse to cause a PMI
 @param *delay_time number of time units that should elapse before event counting begins
 @param *delay_time_units chud_time_unit_t
 @param *max_samples total samples to be collected one sample per PMI
 @result chudSuccess, or one of the error codes from any of the functions this calls
 */
int	chudGetPMISetup( chud_device_t *dev, int *trigger_pmc, int *trigger_evt, int *trigger_ct, int *delay_time, chud_time_unit_t *delay_time_units, int *max_samples );

 /*!
 @function chudSetPMItrigger
 @discussion choose which pmc (on the current PMI device) will be 
 the trigger
 @param trigger_pmc PMC_1 through PMC_8 (depends on the device)
 @result chudStatus:  chudSuccess, chudBadPmcID
 */
int	chudSetPMItrigger( int trigger_pmc );
 /*!
 @function chudGetPMItrigger
 @discussion return the trigger pmc on the current pmi device
 @param
 @result the trigger_pmc index, or chudStatus:  chudNoPMIdeviceSet, 
 chudNoPMItriggerSet, chudBadDeviceID
 */
int	chudGetPMItrigger( void );
 /*!
 @function chudSetPMItriggerEvent
 @discussion select an event (on the current pmc) to trigger PMI's on 
 @param trigger_evt a valid event on the current PMC
 @result chudStatus:  chudSuccess, chudInvalidIndex
 */
int	chudSetPMItriggerEvent( int trigger_evt );
 /*!
 @function chudGetPMItriggerEvent
 @discussion return the event index of the current pmi device's current trigger PMC
 @param
 @result the trigger event index, or chudStatus:  chudNoPMIdeviceSet, 
 chudNoPMItriggerSet, chudBadDeviceID
 */
int	chudGetPMItriggerEvent( void );
 /*!
 @function chudSetPMItriggerCount
 @discussion select a number of events to trigger PMI's on 
 @param trigger_ct number of events that must elapse to cause a PMI
 @result chudStatus:  chudSuccess, chudInvalidValue
 */
int	chudSetPMItriggerCount( int trigger_ct );
 /*!
 @function chudGetPMItriggerCount
 @discussion return the event count that will generate a PMI
 @param void
 @result the event index, or chudStatus:  chudSamplingDeviceNotSet, 
 chudPMItriggerNotSet, chudBadDeviceID
 */
int	chudGetPMItriggerCount( void );

#ifdef __cplusplus
}
#endif

#endif /* CHUD_PMI_H */