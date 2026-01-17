/*
 * Copyright (c) 2000-2010 Apple Inc. All rights reserved.
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

/* 	Copyright (c) 1997 Apple Computer, Inc.  All rights reserved. 
 *
 * kdebug.h -   kernel_debug definitions
 *
 */

#ifndef BSD_SYS_KDEBUG_H
#define BSD_SYS_KDEBUG_H

#include <sys/appleapiopts.h>
#include <sys/cdefs.h>
__BEGIN_DECLS

#ifdef __APPLE_API_UNSTABLE

#include <mach/clock_types.h>
#include <stdint.h>
#if	defined(KERNEL_BUILD)
#include <kdebug.h>
#endif /* KERNEL_BUILD */


/*
 * types of faults that vm_fault handles
 * and creates trace entries for
 */
#define DBG_ZERO_FILL_FAULT   1
#define DBG_PAGEIN_FAULT      2
#define DBG_COW_FAULT         3
#define DBG_CACHE_HIT_FAULT   4
#define DBG_NZF_PAGE_FAULT    5
#define DBG_GUARD_FAULT	      6	
#define DBG_PAGEINV_FAULT     7
#define DBG_PAGEIND_FAULT     8


/* The debug code consists of the following 
*
* ----------------------------------------------------------------------
*|              |               |                               |Func   |
*| Class (8)    | SubClass (8)  |          Code (14)            |Qual(2)|
* ----------------------------------------------------------------------
* The class specifies the higher level 
*/

/* The Function qualifiers  */
#define DBG_FUNC_START		1
#define DBG_FUNC_END		2
#define DBG_FUNC_NONE		0


/* The Kernel Debug Classes  */
#define DBG_MACH		1
#define DBG_NETWORK		2	
#define DBG_FSYSTEM		3
#define DBG_BSD			4
#define DBG_IOKIT		5
#define DBG_DRIVERS		6
#define DBG_TRACE           	7
#define DBG_DLIL	        8
#define DBG_SECURITY		9
#define DBG_CORESTORAGE		10
#define DBG_MISC		20
#define DBG_DYLD           	31
#define DBG_QT              	32
#define DBG_APPS            	33
#define DBG_LAUNCHD         	34
#define DBG_MIG			255

/* **** The Kernel Debug Sub Classes for Mach (DBG_MACH) **** */
#define	DBG_MACH_EXCP_KTRAP_x86	0x02	/* Kernel Traps on x86 */
#define	DBG_MACH_EXCP_DFLT	0x03	/* Data Translation Fault */
#define	DBG_MACH_EXCP_IFLT	0x04	/* Inst Translation Fault */
#define	DBG_MACH_EXCP_INTR	0x05	/* Interrupts */
#define	DBG_MACH_EXCP_ALNG	0x06	/* Alignment Exception */
#define	DBG_MACH_EXCP_UTRAP_x86	0x07	/* User Traps on x86 */
#define	DBG_MACH_EXCP_FP	0x08	/* FP Unavail */
#define	DBG_MACH_EXCP_DECI	0x09	/* Decrementer Interrupt */
#define	DBG_MACH_CHUD		0x0A	/* CHUD */
#define	DBG_MACH_EXCP_SC	0x0C	/* System Calls */
#define	DBG_MACH_EXCP_TRACE	0x0D	/* Trace exception */
#define	DBG_MACH_EXCP_EMUL	0x0E	/* Instruction emulated */
#define	DBG_MACH_IHDLR		0x10	/* Interrupt Handlers */
#define	DBG_MACH_IPC		0x20	/* Inter Process Comm */
#define	DBG_MACH_VM		0x30	/* Virtual Memory */
#define	DBG_MACH_LEAKS		0x31    /* alloc/free */
#define	DBG_MACH_SCHED		0x40	/* Scheduler */
#define	DBG_MACH_MSGID_INVALID	0x50	/* Messages - invalid */
#define DBG_MACH_LOCKS		0x60	/* new lock APIs */
#define DBG_MACH_PMAP		0x70	/* pmap */
#define DBG_MACH_MP		0x90	/* MP related */

/* Codes for Scheduler (DBG_MACH_SCHED) */     
#define MACH_SCHED              0x0     /* Scheduler */
#define MACH_STACK_ATTACH       0x1     /* stack_attach() */
#define MACH_STACK_HANDOFF      0x2     /* stack_handoff() */
#define MACH_CALL_CONT          0x3     /* call_continuation() */
#define MACH_CALLOUT            0x4     /* callouts */
#define MACH_STACK_DETACH       0x5
#define MACH_MAKE_RUNNABLE      0x6     /* make thread runnable */
#define	MACH_PROMOTE            0x7	/* promoted due to resource */
#define	MACH_DEMOTE             0x8	/* promotion undone */
#define MACH_IDLE               0x9	/* processor idling */
#define MACH_STACK_DEPTH        0xa	/* stack depth at switch */
#define MACH_MOVED              0xb	/* did not use original scheduling decision */
#define MACH_FAIRSHARE_ENTER    0xc	/* move to fairshare band */
#define MACH_FAIRSHARE_EXIT     0xd	/* exit fairshare band */
#define MACH_FAILSAFE		0xe	/* tripped fixed-pri/RT failsafe */
#define	MACH_GET_URGENCY	0x14	/* Urgency queried by platform */
#define	MACH_URGENCY		0x15	/* Urgency (RT/BG/NORMAL) communicated
					 * to platform */
#define	MACH_REDISPATCH		0x16	/* "next thread" thread redispatched */
#define	MACH_REMOTE_AST		0x17	/* AST signal issued to remote processor */
#define	MACH_SCHED_LPA_BROKEN	0x18	/* last_processor affinity broken in choose_processor */

/* Codes for pmap (DBG_MACH_PMAP) */     
#define PMAP__CREATE		0x0
#define PMAP__DESTROY		0x1
#define PMAP__PROTECT		0x2
#define PMAP__PAGE_PROTECT	0x3
#define PMAP__ENTER		0x4
#define PMAP__REMOVE		0x5
#define PMAP__NEST		0x6
#define PMAP__UNNEST		0x7
#define PMAP__FLUSH_TLBS	0x8
#define PMAP__UPDATE_INTERRUPT	0x9
#define PMAP__ATTRIBUTE_CLEAR	0xa

/* **** The Kernel Debug Sub Classes for Network (DBG_NETWORK) **** */
#define DBG_NETIP	1	/* Internet Protocol */
#define DBG_NETARP	2	/* Address Resolution Protocol */
#define	DBG_NETUDP	3	/* User Datagram Protocol */
#define	DBG_NETTCP	4	/* Transmission Control Protocol */
#define	DBG_NETICMP	5	/* Internet Control Message Protocol */
#define	DBG_NETIGMP	6	/* Internet Group Management Protocol */
#define	DBG_NETRIP	7	/* Routing Information Protocol */
#define	DBG_NETOSPF	8	/* Open Shortest Path First */
#define	DBG_NETISIS	9	/* Intermediate System to Intermediate System */
#define	DBG_NETSNMP	10	/* Simple Network Management Protocol */
#define DBG_NETSOCK	11	/* Socket Layer */

/* For Apple talk */
#define	DBG_NETAARP	100	/* Apple ARP */
#define	DBG_NETDDP	101	/* Datagram Delivery Protocol */
#define	DBG_NETNBP	102	/* Name Binding Protocol */
#define	DBG_NETZIP	103	/* Zone Information Protocol */
#define	DBG_NETADSP	104	/* Name Binding Protocol */
#define	DBG_NETATP	105	/* Apple Transaction Protocol */
#define	DBG_NETASP	106	/* Apple Session Protocol */
#define	DBG_NETAFP	107	/* Apple Filing Protocol */
#define	DBG_NETRTMP	108	/* Routing Table Maintenance Protocol */
#define	DBG_NETAURP	109	/* Apple Update Routing Protocol */
#define	DBG_NETIPSEC	128	/* IPsec Protocol  */

/* **** The Kernel Debug Sub Classes for IOKIT (DBG_IOKIT) **** */
#define DBG_IOINTC			0	/* Interrupt controller */
#define DBG_IOWORKLOOP		1	/* Work from work loop */
#define DBG_IOINTES			2	/* Interrupt event source */
#define DBG_IOCLKES			3	/* Clock event source */
#define DBG_IOCMDQ			4	/* Command queue latencies */
#define DBG_IOMCURS			5	/* Memory Cursor */
#define DBG_IOMDESC			6	/* Memory Descriptors */
#define DBG_IOPOWER			7	/* Power Managerment */
#define DBG_IOSERVICE		8	/* Matching etc. */

/* **** 9-32 reserved for internal IOKit usage **** */

#define DBG_IOSTORAGE		32	/* Storage layers */
#define	DBG_IONETWORK		33	/* Network layers */
#define	DBG_IOKEYBOARD		34	/* Keyboard */
#define	DBG_IOHID		35	/* HID Devices */
#define	DBG_IOAUDIO		36	/* Audio */
#define	DBG_IOSERIAL		37	/* Serial */
#define	DBG_IOTTY		38	/* TTY layers */
#define DBG_IOSAM		39	/* SCSI Architecture Model layers */
#define DBG_IOPARALLELATA   	40	/* Parallel ATA */
#define DBG_IOPARALLELSCSI	41	/* Parallel SCSI */
#define DBG_IOSATA		42	/* Serial-ATA */
#define DBG_IOSAS		43	/* SAS */
#define DBG_IOFIBRECHANNEL	44	/* FiberChannel */
#define DBG_IOUSB		45	/* USB */
#define DBG_IOBLUETOOTH		46	/* Bluetooth */
#define DBG_IOFIREWIRE		47	/* FireWire */
#define DBG_IOINFINIBAND	48	/* Infiniband */
#define DBG_IOCPUPM		49	/* CPU Power Management */
#define DBG_IOGRAPHICS		50	/* Graphics */
#define DBG_HIBERNATE		51	/* hibernation related events */


/* Backwards compatibility */
#define	DBG_IOPOINTING		DBG_IOHID			/* OBSOLETE: Use DBG_IOHID instead */
#define DBG_IODISK			DBG_IOSTORAGE		/* OBSOLETE: Use DBG_IOSTORAGE instead */

/* **** The Kernel Debug Sub Classes for Device Drivers (DBG_DRIVERS) **** */
#define DBG_DRVSTORAGE		1	/* Storage layers */
#define	DBG_DRVNETWORK		2	/* Network layers */
#define	DBG_DRVKEYBOARD		3	/* Keyboard */
#define	DBG_DRVHID			4	/* HID Devices */
#define	DBG_DRVAUDIO		5	/* Audio */
#define	DBG_DRVSERIAL		7	/* Serial */
#define DBG_DRVSAM			8	/* SCSI Architecture Model layers */
#define DBG_DRVPARALLELATA  9	/* Parallel ATA */
#define DBG_DRVPARALLELSCSI	10	/* Parallel SCSI */
#define DBG_DRVSATA			11	/* Serial ATA */
#define DBG_DRVSAS			12	/* SAS */
#define DBG_DRVFIBRECHANNEL	13	/* FiberChannel */
#define DBG_DRVUSB			14	/* USB */
#define DBG_DRVBLUETOOTH	15	/* Bluetooth */
#define DBG_DRVFIREWIRE		16	/* FireWire */
#define DBG_DRVINFINIBAND	17	/* Infiniband */
#define DBG_DRVGRAPHICS		18  /* Graphics */
#define DBG_DRVSD		19 	/* Secure Digital */

/* Backwards compatibility */
#define	DBG_DRVPOINTING		DBG_DRVHID		/* OBSOLETE: Use DBG_DRVHID instead */
#define DBG_DRVDISK			DBG_DRVSTORAGE	/* OBSOLETE: Use DBG_DRVSTORAGE instead */

/* **** The Kernel Debug Sub Classes for the DLIL Layer (DBG_DLIL) **** */
#define DBG_DLIL_STATIC 1       /* Static DLIL code */
#define DBG_DLIL_PR_MOD 2       /* DLIL Protocol Module */
#define DBG_DLIL_IF_MOD 3       /* DLIL Interface Module */
#define DBG_DLIL_PR_FLT 4       /* DLIL Protocol Filter */
#define DBG_DLIL_IF_FLT 5       /* DLIL Interface FIlter */

/* The Kernel Debug Sub Classes for File System (DBG_FSYSTEM) */
#define DBG_FSRW      1       /* reads and writes to the filesystem */
#define DBG_DKRW      2       /* reads and writes to the disk */
#define DBG_FSVN      3       /* vnode operations (inc. locking/unlocking) */
#define DBG_FSLOOOKUP 4       /* namei and other lookup-related operations */
#define DBG_JOURNAL   5       /* journaling operations */
#define DBG_IOCTL     6       /* ioctl to the disk */
#define DBG_BOOTCACHE 7       /* bootcache operations */
#define DBG_HFS       8       /* HFS-specific events; see bsd/hfs/hfs_kdebug.h */

/* The Kernel Debug Sub Classes for BSD */
#define DBG_BSD_PROC		0x01	/* process/signals related */
#define	DBG_BSD_EXCP_SC		0x0C	/* System Calls */
#define	DBG_BSD_AIO		0x0D	/* aio (POSIX async IO) */
#define DBG_BSD_SC_EXTENDED_INFO 0x0E	/* System Calls, extended info */
#define DBG_BSD_SC_EXTENDED_INFO2 0x0F	/* System Calls, extended info */


/* The Codes for BSD subcode class DBG_BSD_PROC */
#define BSD_PROC_EXIT		1	/* process exit */
#define BSD_PROC_FRCEXIT 	2	/* Kernel force termination */

/* The Kernel Debug Sub Classes for DBG_TRACE */
#define DBG_TRACE_DATA      0
#define DBG_TRACE_STRING    1
#define	DBG_TRACE_INFO	    2

/* The Kernel Debug Sub Classes for DBG_CORESTORAGE */
#define DBG_CS_IO	0

/* The Kernel Debug Sub Classes for DBG_MISC */
#define DBG_EVENT	0x10
#define	DBG_BUFFER	0x20

/* The Kernel Debug Sub Classes for DBG_DYLD */
#define DBG_DYLD_STRING   5

/* The Kernel Debug modifiers for the DBG_DKRW sub class */
#define DKIO_DONE 	0x01
#define DKIO_READ	0x02
#define DKIO_ASYNC	0x04
#define DKIO_META	0x08
#define DKIO_PAGING	0x10
#define DKIO_THROTTLE	0x20
#define DKIO_PASSIVE	0x40

/* Codes for Application Sub Classes */
#define DBG_APP_SAMBA	128

/**********************************************************************/

#define KDBG_CODE(Class, SubClass, code) (((Class & 0xff) << 24) | ((SubClass & 0xff) << 16) | ((code & 0x3fff)  << 2))

#define KDBG_MIGCODE(msgid) ((DBG_MIG << 24) | (((msgid) & 0x3fffff)  << 2))

#define MACHDBG_CODE(SubClass, code) KDBG_CODE(DBG_MACH, SubClass, code)
#define NETDBG_CODE(SubClass, code) KDBG_CODE(DBG_NETWORK, SubClass, code)
#define FSDBG_CODE(SubClass, code) KDBG_CODE(DBG_FSYSTEM, SubClass, code)
#define BSDDBG_CODE(SubClass, code) KDBG_CODE(DBG_BSD, SubClass, code)
#define IOKDBG_CODE(SubClass, code) KDBG_CODE(DBG_IOKIT, SubClass, code)
#define DRVDBG_CODE(SubClass, code) KDBG_CODE(DBG_DRIVERS, SubClass, code)
#define TRACEDBG_CODE(SubClass,code) KDBG_CODE(DBG_TRACE, SubClass, code)
#define MISCDBG_CODE(SubClass,code) KDBG_CODE(DBG_MISC, SubClass, code)
#define DLILDBG_CODE(SubClass,code) KDBG_CODE(DBG_DLIL, SubClass, code)
#define SECURITYDBG_CODE(SubClass,code) KDBG_CODE(DBG_SECURITY, SubClass, code)
#define DYLDDBG_CODE(SubClass,code) KDBG_CODE(DBG_DYLD, SubClass, code)
#define QTDBG_CODE(SubClass,code) KDBG_CODE(DBG_QT, SubClass, code)
#define APPSDBG_CODE(SubClass,code) KDBG_CODE(DBG_APPS, SubClass, code)
#define CPUPM_CODE(code) IOKDBG_CODE(DBG_IOCPUPM, code)

#define KMEM_ALLOC_CODE MACHDBG_CODE(DBG_MACH_LEAKS, 0)
#define KMEM_ALLOC_CODE_2 MACHDBG_CODE(DBG_MACH_LEAKS, 1)
#define KMEM_FREE_CODE MACHDBG_CODE(DBG_MACH_LEAKS, 2)
#define KMEM_FREE_CODE_2 MACHDBG_CODE(DBG_MACH_LEAKS, 3)
#define ZALLOC_CODE MACHDBG_CODE(DBG_MACH_LEAKS, 4)
#define ZALLOC_CODE_2 MACHDBG_CODE(DBG_MACH_LEAKS, 5)
#define ZFREE_CODE MACHDBG_CODE(DBG_MACH_LEAKS, 6)
#define ZFREE_CODE_2 MACHDBG_CODE(DBG_MACH_LEAKS, 7)

#define PMAP_CODE(code) MACHDBG_CODE(DBG_MACH_PMAP, code)

/*   Usage:
* kernel_debug((KDBG_CODE(DBG_NETWORK, DNET_PROTOCOL, 51) | DBG_FUNC_START), 
*	offset, 0, 0, 0,0) 
* 
* For ex, 
* 
* #include <sys/kdebug.h>
* 
* #define DBG_NETIPINIT NETDBG_CODE(DBG_NETIP,1)
* 
* 
* void
* ip_init()
* {
*	register struct protosw *pr;
*	register int i;
* 	
*	KERNEL_DEBUG(DBG_NETIPINIT | DBG_FUNC_START, 0,0,0,0,0)
* 	--------
*	KERNEL_DEBUG(DBG_NETIPINIT, 0,0,0,0,0)
* 	--------
*	KERNEL_DEBUG(DBG_NETIPINIT | DBG_FUNC_END, 0,0,0,0,0)
* }
*

*/

extern unsigned int kdebug_enable;
#define KDEBUG_ENABLE_TRACE   0x1
#define KDEBUG_ENABLE_ENTROPY 0x2
#define KDEBUG_ENABLE_CHUD    0x4

#if	(!defined(NO_KDEBUG))
#define KERNEL_DEBUG_CONSTANT(x,a,b,c,d,e)				\
do {									\
	if (kdebug_enable)						\
        kernel_debug(x,(uintptr_t)a,(uintptr_t)b,(uintptr_t)c,		\
		       (uintptr_t)d,(uintptr_t)e);			\
} while(0)

#define KERNEL_DEBUG_CONSTANT1(x,a,b,c,d,e)				\
do {									\
	if (kdebug_enable)						\
        kernel_debug1(x,(uintptr_t)a,(uintptr_t)b,(uintptr_t)c,		\
			(uintptr_t)d,(uintptr_t)e);			\
} while(0)
#else /*!NO_KDEBUG */
#define KERNEL_DEBUG_CONSTANT(x,a,b,c,d,e) do { } while(0)
#define KERNEL_DEBUG_CONSTANT1(x,a,b,c,d,e) do { } while(0)

#define __kdebug_constant_only __unused
#endif

extern void kernel_debug(
		uint32_t  debugid,
		uintptr_t arg1,
		uintptr_t arg2,
		uintptr_t arg3,
		uintptr_t arg4,
		uintptr_t arg5);

extern void kernel_debug1(
		uint32_t  debugid,
		uintptr_t arg1,
		uintptr_t arg2,
		uintptr_t arg3,
		uintptr_t arg4,
		uintptr_t arg5);


#if	(KDEBUG && (!defined(NO_KDEBUG)))
#define KERNEL_DEBUG(x,a,b,c,d,e)					\
do {									\
	if (kdebug_enable)						\
        kernel_debug((uint32_t)x,  (uintptr_t)a, (uintptr_t)b,		\
		     (uintptr_t)c, (uintptr_t)d, (uintptr_t)e);		\
} while(0)

#define KERNEL_DEBUG1(x,a,b,c,d,e)					\
do {									\
	if (kdebug_enable)						\
        kernel_debug1((uint32_t)x,  (uintptr_t)a, (uintptr_t)b,		\
		      (uintptr_t)c, (uintptr_t)d, (uintptr_t)e);	\
} while(0)
#else

#define KERNEL_DEBUG(x,a,b,c,d,e) do {} while (0)
#define KERNEL_DEBUG1(x,a,b,c,d,e) do {} while (0)

#define __kdebug_only __unused
#endif



#endif /* __APPLE_API_UNSTABLE */
__END_DECLS



#endif /* !BSD_SYS_KDEBUG_H */
