/*======================================================================

    The contents of this file are subject to the Mozilla Public
    License Version 1.1 (the "License"); you may not use this file
    except in compliance with the License. You may obtain a copy of
    the License at http://www.mozilla.org/MPL/

    Software distributed under the License is distributed on an "AS
    IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
    implied. See the License for the specific language governing
    rights and limitations under the License.

    The initial developer of the original code is David A. Hinds
    <dahinds@users.sourceforge.net>.  Portions created by David A. Hinds
    are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.

    Contributor:  Apple Computer, Inc.  Portions © 2003 Apple Computer, 
    Inc. All rights reserved.

    Alternatively, the contents of this file may be used under the
    terms of the GNU Public License version 2 (the "GPL"), in which
    case the provisions of the GPL are applicable instead of the
    above.  If you wish to allow the use of your version of this file
    only under the terms of the GPL and not to allow others to use
    your version of this file under the MPL, indicate your decision
    by deleting the provisions above and replace them with the notice
    and other provisions required by the GPL.  If you do not delete
    the provisions above, a recipient may use your version of this
    file under either the MPL or the GPL.

======================================================================*/

#ifndef _LINUX_K_COMPAT_H
#define _LINUX_K_COMPAT_H

#include <IOKit/assert.h>
#include <IOKit/IOLib.h>
#include <libkern/OSByteOrder.h>
#include <sys/errno.h>

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned int	u32;

#define printk IOLog
#define KERN_INFO	"IOPCCard info:   "
#define KERN_NOTICE	"IOPCCard notice: "
#define KERN_DEBUG	"IOPCCard debug:  "

#define MODULE_PARM(a,b)
#define MODULE_AUTHOR(a)
#define MODULE_DESCRIPTION(a)

#define MOD_DEC_USE_COUNT
#define MOD_INC_USE_COUNT

#define __init
#define __exit

// we don't need these if we are always inside the workloop
#define ACQUIRE_RESOURCE_LOCK
#define RELEASE_RESOURCE_LOCK

#define NR_IRQS			256
#define PCI_INTERRUPT_LINE	0x3c

#define PCI_CACHE_LINE_SIZE	0xc
#define PCI_LATENCY_TIMER	0xd
#define PCI_BASE_ADDRESS_0	0x10
#define PCI_COMMAND		0x4
#define PCI_COMMAND_IO		0x1
#define PCI_COMMAND_MEMORY	0x2
#define PCI_COMMAND_MASTER	0x4
#define PCI_COMMAND_WAIT	0x80

#define PCI_HEADER_TYPE		0xe
#define PCI_CLASS_REVISION	0x8
#define PCI_VENDOR_ID		0x0
#define PCI_DEVICE_ID		0x2
#define PCI_STATUS		0x6

#define PCI_CLASS_BRIDGE_CARDBUS	0x0607
#define PCI_CLASS_BRIDGE_PCMCIA		0x0605

#define PCI_BASE_ADDRESS_SPACE_IO 	0x1
#define PCI_BASE_ADDRESS_SPACE_MEMORY	0x0
#define PCI_BASE_ADDRESS_MEM_PREFETCH	0x8
#define PCI_BASE_ADDRESS_MEM_MASK 	(~0x0fUL)
#define PCI_BASE_ADDRESS_SPACE		0x1
#define PCI_BASE_ADDRESS_IO_MASK	(~0x03UL)
#define	PCI_INTERRUPT_PIN		0x3d

struct pt_regs {};

#define HZ		100

#define mdelay(i)	IODelay( i * 1000 )
#define udelay(i)	IODelay( i )

struct timer_list {
        unsigned long expires;
        void (*function)(unsigned long);
        unsigned long data;
};

extern void IOPCCardAddTimer(struct timer_list * timer);
extern int IOPCCardDeleteTimer(struct timer_list * timer);

#define jiffies (0)	// just cheat on the whole jiffies thing :-)

#define add_timer(t)	IOPCCardAddTimer(t)
#define del_timer(t)	IOPCCardDeleteTimer(t)
#define mod_timer(a, b)	do { del_timer(a); (a)->expires = (b); add_timer(a); } while (0)

extern void *kern_os_malloc(size_t size);
extern void *kern_os_realloc(void * addr, size_t size);
extern void kern_os_free(void * addr);

#define kmalloc(s, x) kern_os_malloc(s)
#define krealloc(a, s, x) kern_os_realloc(a, s)
#define kfree(a) kern_os_free(a)

#define le16_to_cpu(x)	OSSwapLittleToHostInt16(x)
#define le32_to_cpu(x)	OSSwapLittleToHostInt32(x)

//MACOSXXX - all this needs to be cleaned up
typedef struct wait_queue *wait_queue_head_t;
#define init_waitqueue_head(p)	DEBUG(0, "init_waitqueue_head stubbed out!\n");

#define wacquire(w)		do { } while (0)
#define wrelease(w)		do { } while (0)
#define wsleep(w)		DEBUG(0, "wsleep stubbed out!\n");
#define wsleeptimeout(w,t)	DEBUG(0, "wsleeptimeout stubbed out!\n");
#define wakeup(w)		DEBUG(0, "wakeup stubbed out!\n");

extern u_char IOPCCardReadByte(void *virt);
extern u_long IOPCCardReadLong(void *virt);
extern void IOPCCardWriteByte(void *virt, u_char value);
extern void IOPCCardWriteLong(void *virt, u_int value);

#define readb(a)		IOPCCardReadByte(a)
#define readl(a)		IOPCCardReadLong(a)
#define writeb(v, a)		IOPCCardWriteByte(a, v)
#define writel(v, a)		IOPCCardWriteLong(a, v)

extern void *IOPCCardIORemap(u_long paddr, u_long size);
extern void IOPCCardIOUnmap(void *vaddr);

#define ioremap(p, s)	IOPCCardIORemap(p, s)
#define iounmap(v)	IOPCCardIOUnmap(v)

#ifdef IOPCCARD_IN_IOKIT_CODE

class IOPCIDevice;
class IOPCCardBridge;
class IOCardBusDevice;
class IOPCCard16Device;

extern int init_i82365(IOPCCardBridge *bus, IOPCIDevice *bridge, IOVirtualAddress device_regs);
extern int init_pcmcia_cs(void);

#else /* !IOPCCARD_IN_IOKIT_CODE */

typedef struct IOPCIDevice	IOPCIDevice;
typedef struct IOPCCardBridge	IOPCCardBridge;
#define        IOCardBusDevice	IOPCIDevice	// subclassing C style
typedef struct IOPCCard16Device	IOPCCard16Device;

extern IOCardBusDevice *IOPCCardCreateCardBusNub(IOPCCardBridge *bus, unsigned int socket, unsigned int function);
extern void IOPCCardRetainNub(void *nub);
extern void IOPCCardReleaseNub(void *nub);

extern int IOPCCardAddCSCInterruptHandlers(IOPCCardBridge *bus, unsigned int socket, unsigned int irq,
					   u_int (*top_handler)(u_int), u_int (*bottom_handler)(u_int), 
					   u_int (*enable_functional)(u_int), u_int (*disable_functional)(u_int),
					   const char* name);
extern int IOPCCardRemoveCSCInterruptHandlers(IOPCCardBridge *bus, unsigned int socket);

// MACOSXXX - i82365.c and cardbus.c currently use these differently :-)
// the #defines are in those files for now
extern int IOPCCardReadConfigByte(IOPCIDevice *bus, int r, u_char *v);
extern int IOPCCardWriteConfigByte(IOPCIDevice *bus, int r, u_char v);
extern int IOPCCardReadConfigWord(IOPCIDevice *bus, int r, u_short *v);
extern int IOPCCardWriteConfigWord(IOPCIDevice *bus, int r, u_short v);
extern int IOPCCardReadConfigLong(IOPCIDevice *bus, int r, u_int *v);
extern int IOPCCardWriteConfigLong(IOPCIDevice *bus, int r, u_int v);

// MACOSXXX these need to use IOPCCardBridge *bus, if we have multiple controllers
// on different pci bridges, the current code breaks down, this is currently
// not really an issue on laptops :-)

extern int check_mem_region(u_long base, u_long num);
extern void request_mem_region(u_long base, u_long num, char *name);
extern void release_mem_region(u_long base, u_long num);

extern int check_io_region(u_long base, u_long num);
extern void request_io_region(u_long base, u_long num, char *name);
extern void release_io_region(u_long base, u_long num);

#define check_region(a, l) 	check_io_region(a, l)
#define request_region(a, l, n)	request_io_region(a, l, n)
#define release_region(a, l)	release_io_region(a, l)

extern int configure_i82365(IOPCCardBridge *pccard_nub, IOPCIDevice *bridge_nub, void * device_regs);

#endif /* IOPCCARD_IN_IOKIT_CODE */

/* Flags for device state, from ds.h */
#define DEV_PRESENT		0x01
#define DEV_CONFIG		0x02
#define DEV_STALE_CONFIG	0x04	/* release on close */
#define DEV_STALE_LINK		0x08	/* detach on release */
#define DEV_CONFIG_PENDING	0x10
#define DEV_RELEASE_PENDING	0x20
#define DEV_SUSPEND		0x40
#define DEV_BUSY		0x80

#define DEV_OK(state) (((state) & ~DEV_BUSY) == (DEV_CONFIG|DEV_PRESENT))

#endif /* _LINUX_K_COMPAT_H */
