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

#ifndef CHUD_SAMPLE_H
#define CHUD_SAMPLE_H

#include <CHUD/chudCtrl.h>
#include <CHUD/chudPMCs.h>
#include <CHUD/chudTimeBase.h>

/*!
  @header CHUD Sampling Control Structures
  Use the CHUD Sampling Structures to setup all the timing and device control parameters for
  collecting performance monitor counter data, initializing the system wide sampling facility,
   and sharing the sampling facility between applications.
*/

#ifdef __cplusplus
extern "C" {
#endif

/* sample facilty acquisition methods */
#define CHUD_NONBLOCKING   0
#define CHUD_BLOCKING      1

typedef struct pmc_mask_bits_s {
    uint16_t pmc1 : 1;
    uint16_t pmc2 : 1;
    uint16_t pmc3 : 1;
    uint16_t pmc4 : 1;
    uint16_t pmc5 : 1;
    uint16_t pmc6 : 1;
    uint16_t pmc7 : 1;
    uint16_t pmc8 : 1;
    uint16_t /* reserved */ : 8;
} pmc_mask_bits_t;

typedef union pmc_mask_s {
    uint32_t value;
    pmc_mask_bits_t field;
} pmc_mask_t;

typedef struct misc_mask_s {
    uint32_t callstack : 1;
    uint32_t /* reserved */ : 7;    
    uint32_t recordLength : 24;  /* number of elements (uint32_t) long */
} misc_mask_t;

/*!
    @typedef chud_sample_context_t
    @abstract Every sample collected by the performance monitor facility using the CHUD API has an associated context.
    @discussion Each sample that is collected by the CHUD framework has an associated context. The following fields can be accessed.
    @field t_begin Number of timebase ticks recorded at the start of the sample
    @field t_end Number of timebase ticks recorded at the end of the sample
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
    unsigned int pc;
    unsigned int thread_id;
    unsigned int cpu_num : 2;
    unsigned int supervisor : 1;
    unsigned int pid : 16; /* PID_MAX is 30000 */
    unsigned int tag : 13;
} chud_sample_context_t;

#ifndef CHUD_KEXT
int	chudAcquireSamplingFacility( int blocking_acquire );
int	chudReleaseSamplingFacility( int retain_samples );
int 	chudGetSamplingFacilityOwnerPID( void );

chud_device_t chudGetSamplingDevice( void );
int	chudSetSamplingDevice( chud_device_t dev );

int 	chudSetFuzziness( unsigned int pct );
int 	chudGetFuzziness( void );

int 	chudSetStartDelay( int delay_time, chud_time_unit_t delay_time_units );
int	chudGetStartDelay( int *delay_time, chud_time_unit_t *delay_time_units );

int	chudGetMaxSampleLimit( void );
int	chudSetMaxSampleLimit( int max );

int	chudGetRecordCallstacks( void );
int	chudSetRecordCallstacks( int record );

int	chudGetTargetPID( void );
int	chudSetTargetPID( int pid );
int	chudSampleOnlyTargetPID( int enable );
int	chudStopSamplingIfTargetPIDExits( int enable );

int	chudGetSampleCount( chud_device_t dev );
double *chudGetSamplePMCCounts( chud_device_t dev, int sample_idx, int *nItrRtn );
double *chudGetSingleSamplePMCCounts( chud_device_t dev, int *nCtrRtn );
double	chudGetSampleTimeStamp( chud_device_t dev, int sample_idx, chud_time_unit_t units );
double	chudGetSingleSampleTimeStamp( chud_device_t dev, chud_time_unit_t units );
chud_sample_context_t *chudGetSampleContext( chud_device_t dev, int sample_idx );
unsigned int chudGetTotalRawCallStacksSize( chud_device_t dev );
unsigned int *chudGetSampleRawCallStack( chud_device_t dev, int sample_idx, int *length );
int	chudGetRangeSamplePMCCounts( chud_device_t dev, int startIdx, int endIdx, double **resultsPtr, int *nResults );

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void	chudMaxSampleLimitCallback( chudCallbackFunc uicf, unsigned long ha1, unsigned long ha2 ); 
void 	chudPerSampleCallback( chudCallbackFunc uicf, unsigned long ha1, unsigned long ha2 );
void	chudTaskWillExitCallback( chudCallbackFuncData uicf, unsigned long ha1, unsigned long ha2 ); 

#endif /* !CHUD_KEXT */

#ifdef __cplusplus
}
#endif

#endif /* CHUD_SAMPLE_H */