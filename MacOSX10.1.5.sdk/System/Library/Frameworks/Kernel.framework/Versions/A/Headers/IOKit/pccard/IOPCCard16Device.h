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


#ifndef _IOKIT_IOPCCARD16DEVICE_H
#define _IOKIT_IOPCCARD16DEVICE_H

// supported power management states, see powerStates array in attach
enum {
    kIOPCCard16DeviceOffState		= 0,
    kIOPCCard16DeviceDozeState		= 1,
    kIOPCCard16DeviceOnState		= 2,
    kIOPCCard16DevicePowerStateCount	= 3,
};

class IOPCCard16Enabler;
class IODeviceMemory;

class IOPCCard16Device : public IOService
{
    OSDeclareDefaultStructors(IOPCCard16Device);

    friend class IOPCCardBridge;

private:
    IOPCCardBridge *		bridge;	
    u_char			socket;
    u_char			function;
    dev_info_t			bindName;
    client_handle_t		handle;
    IOPCCard16Enabler *		enabler;
    IOMemoryMap *		ioMap;
    
    struct ExpansionData	{ };
    ExpansionData *		reserved;
    
protected:
    virtual bool		bindCardServices(void);
    virtual bool		unbindCardServices(void);
    virtual bool		matchPropertyTable(OSDictionary *table, SInt32 *score);
    virtual IOService *		matchLocation(IOService * client);
    virtual bool		finalize(IOOptionBits options);
    
    static int			eventHandler(cs_event_t event, int priority, event_callback_args_t *args);
    
public:
    virtual bool		attach(IOService * provider);
    virtual void		detach(IOService * provider);
    virtual IOReturn		setPowerState(unsigned long powerState, IOService * whatDevice);

    virtual u_int		getState(void);
    virtual client_handle_t	getCardServicesHandle(void);

    virtual int			cardServices(int func, void * arg1 = 0, void * arg2 = 0, void * arg3 = 0);

    virtual bool		installEnabler(IOPCCard16Enabler *customEnabler = 0);
    virtual bool		configure(UInt32 index = 0);
    virtual bool		unconfigure(void);

    virtual bool		getConfigurationInfo(config_info_t *config);
    virtual UInt32		getWindowCount(void);
    virtual UInt32		getWindowType(UInt32 index);
    virtual UInt32		getWindowSize(UInt32 index);
    virtual bool		getWindowAttributes(UInt32 index, UInt32 *attributes);
    virtual bool		getWindowHandle(UInt32 index, window_handle_t *handle);
    virtual bool		getWindowOffset(UInt32 index, UInt32 *offset);
    virtual bool		setWindowOffset(UInt32 index, UInt32 newOffset);
    
    virtual IODeviceMemory *	ioDeviceMemory(void);
    virtual void		ioWrite32( UInt16 offset, UInt32 value, IOMemoryMap * map = 0 );
    virtual void		ioWrite16( UInt16 offset, UInt16 value, IOMemoryMap * map = 0 );
    virtual void		ioWrite8( UInt16 offset, UInt8 value, IOMemoryMap * map = 0 );
    virtual UInt32		ioRead32( UInt16 offset, IOMemoryMap * map = 0 );
    virtual UInt16		ioRead16( UInt16 offset, IOMemoryMap * map = 0 );
    virtual UInt8		ioRead8( UInt16 offset, IOMemoryMap * map = 0 );

    OSMetaClassDeclareReservedUnused(IOPCCard16Device,  0);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device,  1);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device,  2);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device,  3);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device,  4);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device,  5);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device,  6);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device,  7);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device,  8);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device,  9);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 10);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 11);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 12);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 13);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 14);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 15);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 16);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 17);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 18);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 19);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 20);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 21);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 22);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 23);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 24);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 25);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 26);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 27);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 28);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 29);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 30);
    OSMetaClassDeclareReservedUnused(IOPCCard16Device, 31);
};

#endif /* ! _IOKIT_IOPCCARD16DEVICE_H */
