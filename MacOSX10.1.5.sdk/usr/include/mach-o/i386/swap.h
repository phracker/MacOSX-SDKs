/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Portions Copyright (c) 1999 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 1.1 (the "License").  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON- INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
#import <architecture/byte_order.h>
#import <mach/i386/thread_status.h>

extern void swap_i386_thread_state(
    i386_thread_state_t *cpu,
    enum NXByteOrder target_byte_order);

extern void swap_i386_thread_fpstate(
    i386_thread_fpstate_t *fpu,
    enum NXByteOrder target_byte_order);

extern void swap_i386_thread_exceptstate(
    i386_thread_exceptstate_t *exc,
    enum NXByteOrder target_byte_order);

extern void swap_i386_thread_cthreadstate(
    i386_thread_cthreadstate_t *user,
    enum NXByteOrder target_byte_order);
