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
#include <stdint.h>

/*!
  @header CHUD Tools API overview header
  The CHUD Tools API encapsulates all the functionality needed to set up, organize and interogate the Performance Monitor Faciliy embedded in the PowerPC processors, Apple system comtrollers, and virtualized in the MacOS X operating system. 
  
  Each of the other headers listed in this documentation is include simply by including this one header file (chud.h).
  
  Here's a brief synopsis of what's contained in each of the other modules:
  
  chudCtrl.h: Use the CHUD Control Functions to initialize the framework, keep track of status 
  and error conditions, and deallocate system resources when the CHUD Tools API is 
  no longer needed. This header file should ALWAYS be included in modules making CHUD Tools API
  calls.
  
  chudHotkeys.h: Use the CHUD Hot-keys to set up global key combinations that will send 
  input to a performance monitor program, even when the program does not have keyboard focus, 
  of if it is minimized.
  
  chudInfo.h: The CHUD Info functions provide a mechanism to ask about the characteristics, 
  and performance monitoring capabilities of a system. Information is available for every device 
  that has performance monitoring hardware.
  
  chudPMCs.h: The CHUD PMC functions provide a mechanism to configure, start, and stop 
  the processor, memory controller, and OS performance counters.
  
  chudPMI.h: The CHUD Tools' API for performance monitor interrupts to be enabled and 
  provide a mechanism to select a particular performance monitor counter (PMC) to be used as 
  a sampling trigger. Instead og the more traditional time-based sampling.
  
  chudRemote.h: Use the CHUD Remote functions to setup inter-process communication using 
  mach-messages between a performance monitor application (like MONster or Shark) and an
  application to be profiled. The application drives the profiler, instead of the other way 
  around.
  
  chudSample.h: CHUD Sampling Functions and data structures are used to setup all the timing and 
  device control parameters for collecting performance monitor counter data, initializing the
  system wide sampling facility, and sharing the sampling facility between applications.
  
  chudSPRs.h: Use the CHUD SPR Functions to retrieve and modify the contents of any of the 
  special purpose registers. The file also contains extensive constants reprenting the various
  SPR id's in all the different processors CHUD Tools support.
  
  chudTimeBase.h: the functions in this module access to the time base registers in each PowerPC
  processor. They also provide ways to convert data retrieved from the time base registers into 
  different time units.
  
  chudTimer.h: Similar to the chudPMI.h functions these routine are used to configure the low
  level hardware timers to drive the sampling of performance data in an automated deterministic
  and very accurate way.
  
  chudUtil.h: the utility functions are a low-level "catch all." The functions in this module 
  deal primarily with process marking, system memory configuration, processor cache settings, 
  and the Amber instruction tracing toggle routine.
  
  chudSystem.h: includes many common system header files that the CHUD Tools API depends on
*/

#include <CHUDCore/chudCtrl.h>
#include <CHUDCore/chudHotkeys.h>
#include <CHUDCore/chudInfo.h>
#include <CHUDCore/chudKDebugTrace.h>
#include <CHUDCore/chudPMCs.h>
#include <CHUDCore/chudPMI.h>
#include <CHUDCore/chudPPCInst.h>
#include <CHUDCore/chudRemote.h>
#include <CHUDCore/chudSample.h>
#include <CHUDCore/chudSPRs.h>
#include <CHUDCore/chudTimeBase.h>
#include <CHUDCore/chudTimer.h>
#include <CHUDCore/chudUtil.h>

#ifdef __OBJC__
// depends on CoreFoundation headers
#include <CHUDCore/chudShortcuts.h>
#endif __OBJC__
