/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
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


#ifndef _IOKIT_IOPCCARD16ENABER_H
#define _IOKIT_IOPCCARD16ENABER_H

#define kMaxConfigurations	32

// return values from getWindowType()
#define IOPCCARD16_BAD_INDEX		0
#define IOPCCARD16_MEMORY_WINDOW 	1
#define IOPCCARD16_IO_WINDOW 		2

class IOPCCard16Enabler : public OSObject
{
    OSDeclareDefaultStructors(IOPCCard16Enabler);

 protected:
    IOPCCard16Device *		device;
    client_handle_t		handle;
    u_int			state;
    config_req_t		configuration;
    cistpl_cftable_entry_t *	configTable[kMaxConfigurations];
    u_int			tableEntryCount;
    UInt32			memoryWindowCount;
    UInt32			ioWindowCount;
    io_req_t			io;
    irq_req_t			irq;
    window_handle_t		win[CISTPL_MEM_MAX_WIN];
    win_req_t			req[CISTPL_MEM_MAX_WIN];
    memreq_t 			map[CISTPL_MEM_MAX_WIN];

    struct ExpansionData	{ };
    ExpansionData *		reserved;

 public:
    static IOPCCard16Enabler *	withDevice(IOPCCard16Device * provider);

    virtual bool		init(IOPCCard16Device * provider);
    virtual bool		attach(IOPCCard16Device * provider);
    virtual bool		detach(IOPCCard16Device * provider);
    virtual void		free(void);

    virtual int			eventHandler(cs_event_t event, int priority, event_callback_args_t *args);
    virtual IOReturn		setPowerState(unsigned long, IOService *);

    virtual bool		configure(UInt32 index=0);
    virtual bool		unconfigure();

    virtual bool		getConfigurations(void);
    virtual bool		sortConfigurations(void);
    virtual bool		tryConfiguration(UInt32 index);

    virtual u_int		getState(void);
    virtual bool		getConfigurationInfo(config_info_t * config);
    virtual UInt32		getWindowCount(void);
    virtual UInt32		getWindowType(UInt32 index);
    virtual UInt32		getWindowSize(UInt32 index);
    virtual bool		getWindowAttributes(UInt32 index, UInt32 * attributes);

    virtual bool		getWindowHandle(UInt32 index, window_handle_t * handle);
    virtual bool		getWindowOffset(UInt32 index, UInt32 * offset);
    virtual bool		setWindowOffset(UInt32 index, UInt32 newOffset);
    
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler,  0);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler,  1);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler,  2);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler,  3);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler,  4);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler,  5);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler,  6);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler,  7);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler,  8);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler,  9);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 10);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 11);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 12);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 13);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 14);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 15);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 16);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 17);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 18);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 19);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 20);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 21);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 22);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 23);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 24);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 25);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 26);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 27);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 28);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 29);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 30);
    OSMetaClassDeclareReservedUnused(IOPCCard16Enabler, 31);
};

#endif /* ! _IOKIT_IOPCCARD16ENABER_H */
