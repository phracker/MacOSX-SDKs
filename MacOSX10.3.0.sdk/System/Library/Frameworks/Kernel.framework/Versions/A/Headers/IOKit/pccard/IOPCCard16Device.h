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


#ifndef _IOKIT_IOPCCARD16DEVICE_H
#define _IOKIT_IOPCCARD16DEVICE_H

/*! @header IOPCCard16Device
    @abstract An IOService based class that represents a 16-bit PC Card device.
 */

/*!
 * @enum Power States
 * @discussion These are the supported power management states for 16-bit PC Cards.
 * @constant kIOPCCard16DeviceOffState No power to the socket.
 * @constant kIOPCCard16DeviceDozeState Power to the socket, the device can shut down all or parts of the device.  If you don't support this, you can treat this the same as the "on" state.
 * @constant kIOPCCard16DeviceOnState The socket is powered up.
 */
enum {
    kIOPCCard16DeviceOffState		= 0,
    kIOPCCard16DeviceDozeState		= 1,
    kIOPCCard16DeviceOnState		= 2,
    kIOPCCard16DevicePowerStateCount	= 3,
};

class IOPCCard16Enabler;
class IODeviceMemory;

/*! @class IOPCCard16Device
    @abstract Class that represents a 16-bit PC Card device.
    @discussion <b>Introduction</b>    

After the discovery of a 16-bit PC Card, the PC Card Family creates
and publishes an instance of the IOPCCard16Device provider nub.
This nub provides the driver with methods to handle card
initialization, simplified memory and I/O window management, and
access to Card Services.

Typically, drivers that attach to the IOPCCard16Device nub will either
subclass from another IOKit family or directly from IOService.  The
IOPCCard16Device class is not meant to be subclassed.

Writing drivers for 16-bit PC Cards should be very similar to writing
drivers for PCI or CardBus devices.  The main difference is that a
card's configuration will also need to be selected before the card can
be used.  Once the configuration is selected, the mapping of register windows works exactly as with PCI or CardBus device.  Most
drivers should never need to make a Card Services call to support their
card.

The IOPCCard16Device class defers much of its work to an instance of
IOPCCard16Enabler class.  The enabler does the work of finding,
ordering, reserving, and enabling possible card configurations.  It
handles the details of requesting and releasing individual elements of
that configuration from Card Services.  The PC Card Family provides a
default enabler that should handle most cards.  The default enabler is
automatically installed for you.

During sleep, PC Cards are completely powered off.  When power is
returned, cards are automatically reconfigured and left in basically the
same state as if the configure method had just been called.  The
driver is responsible for saving any additional card state across this
power management event or it can just reinitialize the card from scratch.
The driver should also protect itself at this time from outside events
and try to avoid touching the hardware.  Typical events include: user
requests, spurious interrupts, timer events, card ejection events, ...

When cards are powered down from the menu bar or physically ejected,
the driver will first receive a Card Services event through its
message method before being terminated. Power management events are
handled in the usual IOKit manner.

<b>Types of Driver Matching Supported by IOPCCard16Device</b>

Matching is done by comparing the driver's matching properties against
information retrieved from the PC Card's CIS information.  In addition to
what is provided by IOService, the following types of matching are
supported:

<b>"IONameMatch"</b>

The "IONameMatch" property matches the name give by the PC Card Bridge
driver to a card's driver.  Normally, this name will be of the form
"pccardX,Y", where X is the manufacturer ID and Y is the card ID.
Both IDs are taken from the tuple CISTPL_MANFID.

If the card has no CIS on it, the name will be "pccard-no-cis".  If
the card has CIS but it does not have the CISTPL_MANFID tuple the name
will be "pccard-no-manfid".

<b>"VersionOneInfo"</b>

The "VersionOneInfo" property match is based on the CISTPL_VERS_1
tuple.  It matches against an array of strings, where each string is
one of the entries from the version one tuple.  Trailing entries that are
omitted from the driver's matching entry are treated as wild matches.

<b>"FunctionName"</b>

The "FunctionName" property match is based on the CISTPL_FUNCID tuple.
The following function type strings are supported:

	"Multi-Function", "Memory", "Serial Port", "Parallel Port",
	"Fixed Disk", "Video Adapter", "Network Adapter", "AIMS",
	"SCSI", "Security", "Instrument", "Vendor-Specific", "Anonymous"

The "Anonymous" string is used if no CIS information was found on the card.	

<b>"FunctionID"</b>

The "FunctionID" property match is is also based on the CISTPL_FUNCID tuple.
Instead of looking for a string, it matches on the actual ID number.

<b>"VendorID"</b>

The "VendorID" property match is based on the manufacturer ID in the
CISTPL_MANFID tuple.

<b>"DeviceID"</b>

The "DeviceID" property match is based on the device ID in the CISTPL_MANFID tuple.

<b>"MemoryDeviceName"</b>

The "MemoryDeviceName" property match is based on the CISTPL_DEVICE
and CISTPL_DEVICE_A tuples.  It matches against the following memory
types:

	"ROM", "OTPROM", "EPROM", "EEPROM", "Flash",
	"SRAM",	"DRAM",	"Function Specific", "Extended"
*/

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
    virtual IOReturn		setProperties(OSObject * properties);

    /*! @function getState
     *  @abstract Returns the current state of the card.
     *  @discussion This method returns the current state of the card by asking the enabler.
     *  @result Current state of card.  Returns zero if the enabler has not been installed.
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


    /*! @function installEnabler
     *  @abstract Installs an alternate 16-bit PC Card enabler.
     *  @discussion This method switches out the default enabler for a user-supplied enabler.  It is not necessary to call this method if the default enabler is going to be used.
     *  @param customEnabler Pointer in the instance of an alternate enabler.
     *  @result Returns true if the enabler was successfully installed.
     */    
    virtual bool		installEnabler(IOPCCard16Enabler *customEnabler = 0);

    /*! @function configure
     *  @abstract Selects a 16-bit card configuration and enables it for use.
     *  @discussion This method uses the indicated index from the 16-bit PC Card Configuration Table Entry Tuple, CISTPL_CFTABLE_ENTRY, to allocate resources and properly configure the card.  If the index is not specified, the currently installed enabler will decide the order in which configuration entries are to be tried.  If no index is given, configuration entries are tried one by one until the card is successfully configured. The default enabler sorts entries first by looking for the least number of windows, preferring memory windows over I/O windows.<br><br>After making this call, windows need to be mapped into the kernel virtual address space by using the mapDeviceMemoryWithIndex().  This step is the same as the one you would take in a PCI or Cardbus based driver.  Additional information about the configured windows can be obtained from this class.  This information is sometimes needed when writing a generic driver that matches against multiple cards.
     *  @param index Index of configuration to try.  If no index is given then try all indexes, one by one, until successful.
     *  @result Returns true if the card configuration was successful.
     */    
    virtual bool		configure(UInt32 index = 0);

    /*! @function unconfigure
     *  @abstract Unconfigures a card.
     *  @discussion This method releases resources that were previously allocated back to Card Services. It does not unmap windows. Virtual-to-physical mappings need to be released separately.
     *  @result Returns true if the card was successfully unconfigured.
     */    
    virtual bool		unconfigure(void);


    /*! @function getConfigurationInfo
     *  @abstract Returns information on the card's current configuration.
     *  @discussion This is a convenience method used to call the Card Services call GetConfigurationInfo.  Normally this call is not needed.
     *  @param config Pointer to config_info_t structure to be filled in.
     *  @result Returns true on success.
     */    
    virtual bool		getConfigurationInfo(config_info_t *config);

    /*! @function getWindowCount
     *  @abstract Returns the number of windows that have been configured.
     *  @discussion This method returns the number of windows in this configuration.
     *  @result Returns the number of windows.
     */    
    virtual UInt32		getWindowCount(void);

    /*! @function getWindowType
     *  @abstract Returns the window type.
     *  @discussion This method is used to find the type of window given its index.  There are two types of windows, I/O and memory.  if they are available in a specific configuration, memory windows will always come first in the list of windows.
     *  @param index Index of window.
     *  @result Returns IOPCCARD16_MEMORY_WINDOW, IOPCCARD16_IO_WINDOW or IOPCCARD16_BAD_INDEX.
     */    
    virtual UInt32		getWindowType(UInt32 index);

    /*! @function getWindowSize
     *  @abstract Returns the size of this window.
     *  @discussion This method returns the size of the window in bytes.
     *  @param index Index of window.
     *  @result Returns the size of the window in bytes.
     */    
    virtual UInt32		getWindowSize(UInt32 index);

    /*! @function getWindowAttributes
     *  @abstract Returns the attributes of this window.
     *  @discussion This method returns the attributes for the specified window.  The meaning of the attributes flags varies depending on the type of window.  The most useful attributes are the data access width flags for I/O windows.  For definitions of these flags for both types of windows see "IOKit/pccard/cs.h".
     *  @param index Index of window.
     *  @param attributes Pointer to the attribute flags to be filled in.
     *  @result Returns attributes for the window.
     */    
    virtual bool		getWindowAttributes(UInt32 index, UInt32 *attributes);

    /*! @function getWindowHandle
     *  @abstract Returns the Card Services handle for this window.
     *  @discussion This method returns the Card Services handle for the window requested.  This call is only valid for memory windows. Normally this call is not needed.
     *  @param index Index to window.
     *  @param handle Pointer to the window_handle_t structure to be filled in.
     *  @result Returns true if the window handle was found.
     */    
    virtual bool		getWindowHandle(UInt32 index, window_handle_t *handle);

    /*! @function getWindowOffset
     *  @abstract Returns the offset that this window is currently at.
     *  @discussion This method returns the current offset for this window into the card's memory space.  This call is only valid for memory windows.
     *  @param index Index of window.
     *  @param offset The current offset for this window.
     *  @result Returns true if the returned window offset is valid.
     */    
    virtual bool		getWindowOffset(UInt32 index, UInt32 *offset);

    /*! @function setWindowOffset
     *  @abstract Sets the offset for this window.
     *  @discussion This method updates the offset into the card's memory space for this window.  This call is only valid for memory windows.
     *  @param index Index of window.
     *  @param offset The new offset for this window.
     *  @result Returns true if the window offset was successfully updated.
     */    
    virtual bool		setWindowOffset(UInt32 index, UInt32 newOffset);

    /*! @function ioDeviceMemory
     *  @abstract Accessor to the I/O space aperture for this bus.
     *  @discussion This method will return a reference to the IODeviceMemory for the I/O aperture of the bus the device is on.
     *  @result A pointer to an IODeviceMemory object for the I/O aperture. The IODeviceMemory is retained by the provider, so is valid while attached, or while any mappings to it exist. It should not be released by the caller.
     */
    virtual IODeviceMemory *	ioDeviceMemory(void);

    /*! @function ioWrite32
     *  @abstract Writes a 32-bit value to an I/O space aperture.
     *  @discussion This method will write a 32-bit value to a 4-byte aligned offset in an I/O space aperture. If a map object is passed in, the value is written relative to it, otherwise the value is written relative to the I/O space aperture for the bus. This function encapsulates the differences between architectures in generating I/O space operations. An eieio instruction is included on PPC.
     *  @param offset An offset into a bus or device's I/O space aperture.
     *  @param value The value to be written in host byte order (big endian on PPC).
     *  @param map If the offset is relative to the beginning of a device's aperture, an IOMemoryMap object for that object should be passed in. Otherwise, passing zero will write the value relative to the beginning of the bus's I/O space.
     */
    virtual void		ioWrite32( UInt16 offset, UInt32 value, IOMemoryMap * map = 0 );

    /*! @function ioWrite16
     *  @abstract Writes a 16-bit value to an I/O space aperture.
     *  @discussion This method will write a 16-bit value to a 2-byte aligned offset in an I/O space aperture. If a map object is passed in, the value is written relative to it, otherwise the value is written relative to the I/O space aperture for the bus. This function encapsulates the differences between architectures in generating I/O space operations. An eieio instruction is included on PPC.
     *  @param offset An offset into a bus or device's I/O space aperture.
     *  @param value The value to be written in host byte order (big endian on PPC).
     *  @param map If the offset is relative to the beginning of a device's aperture, an IOMemoryMap object for that object should be passed in. Otherwise, passing zero will write the value relative to the beginning of the bus's I/O space.
     */
    virtual void		ioWrite16( UInt16 offset, UInt16 value, IOMemoryMap * map = 0 );

    
    /*! @function ioWrite8
     *  @abstract Writes an 8-bit value to an I/O space aperture.
     *  @discussion This method will write a 8-bit value to an offset in an I/O space aperture. If a map object is passed in, the value is written relative to it, otherwise the value is written relative to the I/O space aperture for the bus. This function encapsulates the differences between architectures in generating I/O space operations. An eieio instruction is included on PPC.
     *  @param offset An offset into a bus or device's I/O space aperture.
     *  @param value The value to be written in host byte order (big endian on PPC).
     *  @param map If the offset is relative to the beginning of a device's aperture, an IOMemoryMap object for that object should be passed in. Otherwise, passing zero will write the value relative to the beginning of the bus's I/O space.
     */
    virtual void		ioWrite8( UInt16 offset, UInt8 value, IOMemoryMap * map = 0 );

    /*! @function ioRead32
     *  @abstract Reads a 32-bit value from an I/O space aperture.
     *  @discussion This method will read a 32-bit value from a 4-byte aligned offset in an I/O space aperture. If a map object is passed in, the value is read relative to it, otherwise the value is read relative to the I/O space aperture for the bus. This function encapsulates the differences between architectures in generating I/O space operations. An eieio instruction is included on PPC.
     *  @param offset An offset into a bus or device's I/O space aperture.
     *  @param map If the offset is relative to the beginning of a device's aperture, an IOMemoryMap object for that object should be passed in. Otherwise, passing zero will write the value relative to the beginning of the bus's I/O space.
     *  @result The value read in host byte order (big endian on PPC).
     */
    virtual UInt32		ioRead32( UInt16 offset, IOMemoryMap * map = 0 );

    /*! @function ioRead16
     *  @abstract Reads a 16-bit value from an I/O space aperture.
     *  @discussion This method will read a 16-bit value from a 2-byte aligned offset in an I/O space aperture. If a map object is passed in, the value is read relative to it, otherwise the value is read relative to the I/O space aperture for the bus. This function encapsulates the differences between architectures in generating I/O space operations. An eieio instruction is included on PPC.
     *  @param offset An offset into a bus or device's I/O space aperture.
     *  @param map If the offset is relative to the beginning of a device's aperture, an IOMemoryMap object for that object should be passed in. Otherwise, passing zero will write the value relative to the beginning of the bus's I/O space.
     *  @result The value read in host byte order (big endian on PPC).
     */
    virtual UInt16		ioRead16( UInt16 offset, IOMemoryMap * map = 0 );

    /*! @function ioRead8
     *  @abstract Reads an 8-bit value from an I/O space aperture.
     *  @discussion This method will read an 8-bit value from an offset in an I/O space aperture. If a map object is passed in, the value is read relative to it, otherwise the value is read relative to the I/O space aperture for the bus. This function encapsulates the differences between architectures in generating I/O space operations. An eieio instruction is included on PPC.
     *  @param offset An offset into a bus or device's I/O space aperture.
     *  @param map If the offset is relative to the beginning of a device's aperture, an IOMemoryMap object for that object should be passed in. Otherwise, passing zero will write the value relative to the beginning of the bus's I/O space.
     *  @result The value read in host byte order (big endian on PPC).
     */
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
