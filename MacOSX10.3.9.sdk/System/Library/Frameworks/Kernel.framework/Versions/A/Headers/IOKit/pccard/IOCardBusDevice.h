/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */


#ifndef _IOKIT_IOCARDBUSDEVICE_H
#define _IOKIT_IOCARDBUSDEVICE_H

/*! @header IOCardBusDevice
    @abstract An IOPCIDevice based class that represents a 32-bit CardBus device.
*/

/*! @class IOCardBusDevice
    @abstract Class that represents a 32-bit CardBus device.
    @discussion <b>Introduction</b>    

After the discovery of a 32-bit PC Card, the PC Card Family creates
and publishes an instance of the IOCardBusDevice provider nub.

The same driver should work for CardBus cards and PCI cards in most
cases.  For more information on writing CardBus drivers please refer
to the documentation for writing PCI device drivers.  It is recommended
that CardBus drivers list their provider as IOPCIDevice instead of
IOCardBusDevice to avoid having to pull in the PC Card Family if it is
not required.

CardBus cards can be shut down from the menu bar or physically
ejected.  The driver will first receive a Card Services event through
its message method before being terminated.  If your driver can handle
being unloaded by using the shell command "kextunload" it should also
be ready and able to handle being ejected.
    
<b>Types of Driver Matching Supported by IOCardBusDevice</b>

Matching is done by comparing the driver's matching properties against
information retrieved from the Configuration Space and its CIS
information.  In addition to what is provided by IOService and
IOPCIDevice, the following matching is also supported:

<b>"VersionOneInfo"</b>

The "VersionOneInfo" property match is based on the CISTPL_VERS_1
tuple.  It matches against an array of strings, where each string is
one of the entries from the version one tuple.  Trailing entries that are
omitted from the driver's matching entry are treated as wild matches.
*/

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
    virtual IOReturn		setProperties(OSObject * properties);

    /*! @function getState
     *  @abstract Returns the current state of the card.
     *  @discussion This method returns the current state of the card.
     *  @result Current state of card.
     */    
    virtual u_int		getState(void);

    /*! @function getCardServicesHandle
     *  @abstract Returns the Card Services client handle for this card.
     *  @discussion This method returns the Card Services client handle for this card.  This handle is created for the driver when the card was bound to Card Services.  This handle is needed to make most Card Services calls.  In most cases you should not need to use this method.
     *  @result Returns Card Services client handle. This should always be successful.
     */    
    virtual client_handle_t	getCardServicesHandle(void);

    /*! @function cardServices
     *  @abstract Makes a call to Card Services.
     *  @discussion This method is used to directly make calls to Card Services.  You should always call Card Services using this method.  This will ensure that it is run on the correct IOPCCardBridge workloop.  See the file "doc/PCMCIA-PROG" in the IOPCCardFamily Darwin project and header file "IOKit/pccard/cs.h" for more info.<br><br><i>In most cases, you should never need to use this method and its misuse will cause problems.</i>
     *  @param func The Card Services function index.
     *  @param arg1 Argument number one.
     *  @param arg2 Argument number two.
     *  @param arg3 Argument number three.
     *  @result See "IOKit/pccard/cs.h" for return codes.
     */    
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
