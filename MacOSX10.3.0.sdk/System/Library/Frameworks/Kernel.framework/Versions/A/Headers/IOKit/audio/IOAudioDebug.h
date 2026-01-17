/*
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
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

// There are several different categories of debug messages possible by the IOAudioFamily
//   1) General debugging messages
//      - #define DEBUG
//   2) Function/method logging
//      - #define DEBUG_CALLS
//   3) Timer debugging messages - functions called during timer operations (4 per buffer cycle)
//      - #define DEBUG_TIMER
//   4) IO debugging messages - called for each IO by the HAL
//      - #define DEBUG_IO
//      - Devided into separate input and output logs
//        - #define DEBUG_INPUT
//        - #define DEBUG_OUTPUT

#ifndef _IOAUDIODEBUG_H
#define _IOAUDIODEBUG_H

#ifdef DEBUG_ALL
#define DEBUG
#define DEBUG_CALLS
#define DEBUG_TIMER
#define DEBUG_IO
#endif

#ifdef DEBUG_IO
#define DEBUG_INPUT
#define DEBUG_OUTPUT
#endif

#ifdef DEBUG_INPUT
#define DEBUG_IO
#endif

#ifdef DEBUG_OUTPUT
#define DEBUG_IO
#endif

#if defined(DEBUG_TIMER) && defined(DEBUG_CALLS)
#define DEBUG_TIMER_CALLS
#endif

#if defined(DEBUG_INPUT) && defined(DEBUG_CALLS)
#define DEBUG_INPUT_CALLS
#endif

#if defined(DEBUG_OUTPUT) && defined(DEBUG_CALLS)
#define DEBUG_OUTPUT_CALLS
#endif

#if defined(DEBUG_IO) && defined(DEBUG_CALLS)
#define DEBUG_IO_CALLS
#endif 

#endif /* _IOAUDIODEBUG_H */
