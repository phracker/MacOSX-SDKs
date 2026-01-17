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
  @header CHUD Sampling Control Functions and structures
  Use the CHUD Sampling Functions and data structures to setup all the timing and device control parameters for
  collecting performance monitor counter data, initializing the system wide sampling facility,
   and sharing the sampling facility between applications.
*/

#ifndef CHUD_SAMPLE_H
#define CHUD_SAMPLE_H

#include <CHUDCore/chudCtrl.h>
#include <CHUDCore/chudPMCs.h>
#include <CHUDCore/chudTimeBase.h>

#ifdef __cplusplus
extern "C" {
#endif

/* sample facility acquisition methods */
#define CHUD_NONBLOCKING   0
#define CHUD_BLOCKING      1

/*!
    @typedef chud_sample_context_t
    @abstract Every sample collected by the performance monitor facility using the CHUD Tools API has an associated context.
    @discussion Each sample that is collected by the CHUD framework has an associated context. The following fields can be accessed.
    @field t_begin Number of time-base ticks recorded at the start of the sample
    @field t_end Number of time-base ticks recorded at the end of the sample
    @field pc The program counter of the module executing when the sample was collected
    @field thread_id The thread id that was executing when the sample was collected
    @field cpu_num The processor number the sample was collected from
    @field supervisor A single bit which is HI if the executing thread was in supervisor mode
    @field pid The process id of the process that was executing when the sample was collected
    @field tag Reserved for future use
 */
typedef struct chud_sample_context_s {
    uint64_t t_begin;
    uint64_t t_end;
    uint32_t pc;
    uint32_t thread_id;
    uint32_t cpu_num : 2;
    uint32_t supervisor : 1;
    uint32_t pid : 16; /* PID_MAX is 30000 */
    uint32_t tag : 13;
} chud_sample_context_t;

#ifndef CHUD_KEXT
 /*!
 @function chudAcquireSamplingFacility
 @discussion call this function prior to calls to chudStartPMCs, in order to prepare for 
 collecting samples, and gain exclusive access to the performance facility.
 @param blocking_acquire is either CHUD_BLOCKING, or CHUD_NONBLOCKING. passing in CHUD_BLOCKING 
 will cause the caller to wait until the sampling facility is released before proceeding. If 
 CHUD_NONBLOCKING is passed then the routine will return immediately, and set the return status 
 accordingly.
 @result chudSuccess, chudSampleFacilityInUse, chudWaitingForSampleFacility
 */
int	chudAcquireSamplingFacility( int blocking_acquire );
 /*!
 @function chudReleaseSamplingFacility
 @discussion stop using the performance monitor facility, and allow some other process access to 
 the facility.
 @param retain_samples if TRUE any collected samples will be copied from the system sample buffer 
 into local memory of the calling process before the facility is released.
 @result chudSuccess , chudFailure , chudSampleFacilityNotAcquired
 */
int	chudReleaseSamplingFacility( int retain_samples );
 /*!
 @function chudGetSamplingFacilityOwnerPID
 @discussion retrieve the process ID of whomever has acquired the sampling
 facility, or -1 if the calling process owns it already
 @param void
 @result a PID, or -1
 */
int 	chudGetSamplingFacilityOwnerPID( void );

 /*!
 @function chudGetSamplingDevice
 @discussion return current sampling chud_device_t
 @param void
 @result chud_device_t chudAllCPUDev, chudOSDev, chudTimerDev, or chudUserDev
 */
chud_device_t chudGetSamplingDevice( void );
 /*!
 @function chudSetSamplingDevice
 @discussion set the sampling device (chudUserDev for single sampling, 
 chudCPU1Dev/chudCPU2Dev/chudAllCPUDev for CPU PMI, chudOSDev for OS PMI or
 chudTimerDev for timer based sampling, chudUserDev, for single samples per
 chudStartPMCs/chudStopPMCs function pair
 @param dev chud_device_t
 @result chudStatus:  chudSuccess
 */
int	chudSetSamplingDevice( chud_device_t dev );

 /*!
 @function chudSetFuzziness
 @discussion set percent of nominal value to vary sample time or pmi
 trigger count.
 @param pct percent to vary triggering (nominal-pct%...nominal+pct%)
 @result chudSuccess, or chudInvalidUnits
 */
int 	chudSetFuzziness( unsigned int pct );
 /*!
 @function chudGetFuzziness
 @discussion get percent of nominal value that sample time or pmi
 trigger count is varied
 @param void
 @result returns percent triggering is varied (nominal-pct%...nominal+pct%)
 */
int 	chudGetFuzziness( void );

 /*!
 @function chudSetStartDelay
 @discussion set the sampling start-delay in delay_time_units. The sampling facility is blocked
 for the amount of time specified by this function, after chudStartPMCs is called.
 @param delay_time int 
 @param delay_time_units chud_time_unit_t 
 @result chudSuccess, chudInvalidUnits, chudInvalidValue
 */
int 	chudSetStartDelay( int delay_time, chud_time_unit_t delay_time_units );
 /*!
 @function chudGetStartDelay
 @discussion get the sampling start-delay in delay_time_units
 @param delay_time (int *) storage for the delay time
 @param delay_time_units (chud_time_unit_t *) storage for the delay time units
 @result chudSuccess, chudInvalidUnits, chudInvalidMemoryPointer
 */
int	chudGetStartDelay( int *delay_time, chud_time_unit_t *delay_time_units );

 /*!
 @function chudGetMaxSampleLimit
 @discussion return the maximum number of samples that can be taken during
 measurement (before the measurement is automatically stopped)
 @param void 
 @result the maximum sample count
 */
int	chudGetMaxSampleLimit( void );
 /*!
 @function chudSetMaxSampleLimit
 @discussion set the maximum number of samples that can elapse during
 measurement (before the measurement is automatically stopped)
 @param
 @result chudSuccess
 */
int	chudSetMaxSampleLimit( int max );

 /*!
 @function chudGetRecordCallstacks
 @discussion returns whether or not call stacks will be recorded during sampling
 @param void
 @result truth TRUE or FALSE
 */
int	chudGetRecordCallstacks( void );
 /*!
 @function chudSetRecordCallstacks
 @discussion select whether or not callstacks will be recorded during sampling the default is to 
 NOT record call stacks.
 @param record pass in TRUE to record call stacks, or FALSE to ignore them during sampling
 @result chudSuccess
 */
int	chudSetRecordCallstacks( int record );

 /*!
 @function chudGetTargetPID
 @discussion return the target process id (PID). a single process can be designated as the only
 PID to sample from see chudSetTargetPID.  Only when the 'target' process is running on a 
 processor, will samples be generated.
 @param
 @result PID
 */
int	chudGetTargetPID( void );
 /*!
 @function chudSetTargetPID
 @discussion set the target process id (PID) - does nothing unless 
 chudSampleOnlyTargetPID() or chudStopSamplingIfTargetPIDExits()
 are enabled
 @param pid process id (pid_t) to e sampled exclusively
 @result chudSuccess
 */
int	chudSetTargetPID( int pid );
 /*!
 @function chudSampleOnlyTargetPID
 @discussion only record samples from target PID, by default this is disabled
 @param enable pass in TRUE to enable this feature, FALSE otherwise
 @result chudSuccess
 */
int	chudSampleOnlyTargetPID( int enable );
 /*!
 @function chudStopSamplingIfTargetPIDExits
 @discussion stop sampling if target PID exits, or is terminated
 @param pid a process id (pid_t)
 @result chudSuccess
 */
int	chudStopSamplingIfTargetPIDExits( int enable );
 /*!
 @function chudGetSampleCount
 @discussion returns a value that represents the total number of samples
 taken that have information (counts & context) relevant to the desired device
 @param
 @result returns the count valid samples
 */
int	chudGetSampleCount( chud_device_t dev );
 /*!
 @function chudGetSamplePMCCounts
 @discussion retrieve all counts in a sample for a device's PMCs as an array of double precision 
 floats. One entry per sample representing the count of events in each PMC for sample.
 @param dev which chud_device_t to collect event counts from.
 @param sample_idx which sample to get event counts from
 @param nCtrRtn number of doubles in the returned array (usually == number of pmcs on the device)
 @result an array of measured event counts
 */
double *chudGetSamplePMCCounts( chud_device_t dev, int sample_idx, int *nItrRtn );
 /*!
 @function chudGetSingleSamplePMCCounts
 @discussion return the event counts from all pmc's on a particular cpu
 @param
 @result an array of double-precision values 1 for each pmc measured
 */
double *chudGetSingleSamplePMCCounts( chud_device_t dev, int *nCtrRtn );
 /*!
 @function chudGetSampleTimeStamp
 @discussion return the time interval associated with a particular device sample
 @param
 @result returns a double with the requested units
 */
double	chudGetSampleTimeStamp( chud_device_t dev, int sample_idx, chud_time_unit_t units );
 /*!
 @function chudGetSingleSampleTimeStamp
 @discussion retrieve the timebase tick count from 
 the specified device (must be chudCPU1Dev or chudCPU2Dev)
 @param
 @result returns a double with the timebase tick count in it.
 */
double	chudGetSingleSampleTimeStamp( chud_device_t dev, chud_time_unit_t units );
 /*!
 @function chudGetSampleContext
 @discussion return a pointer to the sample context for the sample at sample_idx
 @param
 @result returns a double with the requested units
 */
chud_sample_context_t *chudGetSampleContext( chud_device_t dev, int sample_idx );
 /*!
 @function chudGetTotalRawCallStacksSize
 @discussion return total number of bytes required for call-stacks on device.
 @param
 @result total callstacks size
 */
unsigned int chudGetTotalRawCallStacksSize( chud_device_t dev );
 /*!
 @function chudGetSampleRawCallStack
 @discussion return a pointer to the raw call stack backtrace for the sample at
 sample_idx (raw because it includes fixup info including pc and r0).
 @param
 @result returns a pointer to the raw call stack backtrace
 */
unsigned int *chudGetSampleRawCallStack( chud_device_t dev, int sample_idx, int *length );
 /*!
 @function chudGetRangeSamplePMCCounts
 @discussion retrieve the full or partial list of all sample measurements for
 all pmc's on the specified device
 @param
 @result returns chudstatus: chudSuccess, 
 */
int	chudGetRangeSamplePMCCounts( chud_device_t dev, int startIdx, int endIdx, double **resultsPtr, int *nResults );

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

 /*!
 @function chudMaxSampleLimitCallback
 @discussion when the maximum number of samples for collecting PMC event 
 counts has been used, this programmer defined final routine is called
 @param  uicf  a pointer to an external function with a chudCallbackFunc contract. See chudCtrl.h documentation for a discussion of the chudCallbackFunc.
 @param  ha1  this a compatability argument bridging the C -> Obj-C calling conventions
 @param  ha2  the second compatability argument bridging the C -> Obj-C calling conventions
 @result void
 */
void	chudMaxSampleLimitCallback( chudCallbackFunc uicf, unsigned long ha1, unsigned long ha2 ); 
 /*!
 @function chudPerSampleCallback
 @discussion after each sample get a callback
 @param  uicf  a pointer to an external function with a chudCallbackFunc contract. See chudCtrl.h documentation for a discussion of the chudCallbackFunc.
 @param  ha1  this a compatability argument bridging the C -> Obj-C calling conventions
 @param  ha2  the second compatability argument bridging the C -> Obj-C calling conventions
 @result void
 */
void 	chudPerSampleCallback( chudCallbackFunc uicf, unsigned long ha1, unsigned long ha2 );
 /*!
 @function chudTaskWillExitCallback
 @discussion notification when a sampled task will exit
 @param  uicf  a pointer to an external function with a chudCallbackFuncData contract. See chudCtrl.h documentation for a discussion of the chudCallbackFuncData.
 @param  ha1  this a compatability argument bridging the C -> Obj-C calling conventions
 @param  ha2  the second compatability argument bridging the C -> Obj-C calling conventions
 @result void
 */
void	chudTaskWillExitCallback( chudCallbackFuncData uicf, unsigned long ha1, unsigned long ha2 ); 

#endif /* !CHUD_KEXT */

#ifdef __cplusplus
}
#endif

#endif /* CHUD_SAMPLE_H */