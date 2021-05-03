/* iig(DriverKit-107.100.6) generated from DriverKit.iig */

/* DriverKit.iig:1- */
/*
 * Copyright (c) 2019-2019 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#include <sys/cdefs.h>
#include <DriverKit/IOLib.h>

#if __IIG
#include <DriverKit/OSDictionary.h>  /* .iig include */
#include <DriverKit/OSArray.h>  /* .iig include */
#include <DriverKit/OSString.h>  /* .iig include */
#include <DriverKit/OSData.h>  /* .iig include */
#include <DriverKit/OSNumber.h>  /* .iig include */
#include <DriverKit/OSBoolean.h>  /* .iig include */
#include <DriverKit/OSSerialization.h>  /* .iig include */
#else
#include <DriverKit/OSCollections.h>
#endif

#include <DriverKit/OSObject.h>  /* .iig include */
#include <DriverKit/OSAction.h>  /* .iig include */
#include <DriverKit/IODispatchQueue.h>  /* .iig include */
#include <DriverKit/IODispatchSource.h>  /* .iig include */
#include <DriverKit/IODataQueueDispatchSource.h>  /* .iig include */
#include <DriverKit/IOInterruptDispatchSource.h>  /* .iig include */
#include <DriverKit/IOTimerDispatchSource.h>  /* .iig include */
#include <DriverKit/IOServiceNotificationDispatchSource.h>  /* .iig include */
#include <DriverKit/IOMemoryDescriptor.h>  /* .iig include */
#include <DriverKit/IOMemoryMap.h>  /* .iig include */
#include <DriverKit/IOBufferMemoryDescriptor.h>  /* .iig include */
#include <DriverKit/IODMACommand.h>  /* .iig include */
#include <DriverKit/IOService.h>  /* .iig include */
#include <DriverKit/IOUserClient.h>  /* .iig include */

