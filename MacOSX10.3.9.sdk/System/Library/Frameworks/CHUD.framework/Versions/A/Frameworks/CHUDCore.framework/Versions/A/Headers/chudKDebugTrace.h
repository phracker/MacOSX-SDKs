/*
 * Copyright (c) 2003-2004 Apple Computer, Inc. All rights reserved.
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

#ifndef CHUD_KDEBUG_TRACE_H
#define CHUD_KDEBUG_TRACE_H

#include <CHUDCore/chudCtrl.h>
#include <CHUDCore/chudPMCs.h>
#include <CHUDCore/chudSample.h>
#include <CHUDCore/chudTimeBase.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/kdebug.h>
/* not defined in sys/kdebug.h */
#define DKIO_WRITE	0

#define KDEBUG_ARG_COUNT	5

typedef struct debug_code_bits_s {
    unsigned int Class : 8;
    unsigned int Subclass : 8;
    unsigned int Code : 14;
    unsigned int FuncQual : 2;
} debug_code_bits_t;

typedef union debug_code_u {
    unsigned int value;
    debug_code_bits_t field;
} debug_code_t; 

typedef struct dkio_code_bits_s {
    unsigned int : 27;
    unsigned int paging : 1;
    unsigned int meta : 1;
    unsigned int async : 1;
    unsigned int read : 1;
    unsigned int done : 1;
} dkio_code_bits_t;

typedef union dkio_code_u {
    unsigned int value;
    dkio_code_bits_t field;
} dkio_code_t;

typedef struct kdebug_sample_s {
    chud_sample_context_t context;
    debug_code_t debugcode;
    uint32_t arg[KDEBUG_ARG_COUNT];
} kdebug_sample_t;

#ifndef CHUD_KEXT
int	chudAcquireKDebugTraceFacility( int blocking_acquire );
int	chudReleaseKDebugTraceFacility( int retain_samples );
int 	chudGetKDebugTraceFacilityOwnerPID( void );

int 	chudSetKDebugTraceStartDelay( int delay_time, chud_time_unit_t delay_time_units );
int	chudGetKDebugTraceStartDelay( int *delay_time, chud_time_unit_t *delay_time_units );

int	chudGetMaxKDebugTraceSampleLimit( void );
int	chudSetMaxKDebugTraceSampleLimit( int max );

int	chudStartKDebugTrace( void );
int	chudStopKDebugTrace( void );

int	chudGetKDebugTraceSampleCount( chud_device_t dev );
kdebug_sample_t *chudGetKDebugTraceSample( chud_device_t dev, int sample_idx );

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void	chudMaxKDebugTraceSampleLimitCallback( chudCallbackFunc uicf, unsigned long ha1, unsigned long ha2 ); 

#endif /* !CHUD_KEXT */

#ifdef __cplusplus
}
#endif

#endif /* CHUD_KDEBUG_TRACE_H */