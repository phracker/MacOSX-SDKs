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


#ifndef _IOKIT_IOCARDBUSDEVICE_H
#define _IOKIT_IOCARDBUSDEVICE_H

class IOCardBusDevice : public IOPCIDevice
{
    OSDeclareDefaultStructors(IOCardBusDevice);

    friend class IOPCCardBridge;

private:
    u_char			socket;
    u_char			function;
    u_int			state;
    dev_info_t			bindName;
    client_handle_t		handle;
    config_req_t		configuration;

    struct ExpansionData	{ };
    ExpansionData		*reserved;

protected:
    virtual bool		bindCardServices(void);
    virtual bool		unbindCardServices(void);
    virtual bool		matchPropertyTable(OSDictionary * table, SInt32 * score);
    virtual IOService *		matchLocation(IOService * client);
    virtual bool		finalize(IOOptionBits options);
    
    static int			eventHandler(cs_event_t event, int priority, event_callback_args_t *args);
    
public:
    virtual IOReturn		setPowerState(unsigned long powerState, IOService * whatDevice);

    virtual u_int		getState(void);
    virtual client_handle_t	getCardServicesHandle(void);

    virtual int			cardServices(int func, void * arg1 = 0, void * arg2 = 0, void * arg3 = 0);

    OSMetaClassDeclareReservedUnused(IOCardBusDevice,  0);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice,  1);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice,  2);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice,  3);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice,  4);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice,  5);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice,  6);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice,  7);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice,  8);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice,  9);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 10);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 11);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 12);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 13);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 14);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 15);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 16);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 17);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 18);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 19);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 20);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 21);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 22);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 23);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 24);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 25);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 26);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 27);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 28);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 29);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 30);
    OSMetaClassDeclareReservedUnused(IOCardBusDevice, 31);
};

#endif /* ! _IOKIT_IOCARDBUSDEVICE_H */
