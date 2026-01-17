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


#ifndef _IOKIT_IOPCCARD16ENABER_H
#define _IOKIT_IOPCCARD16ENABER_H

/*! @header IOPCCard16Enabler
    @abstract An OSObject based class used to control the configuration of 16-bit PC Card devices.
 */

/*!
 * @defined kMaxConfigurations
 * @abstract  The maximum number of configurations that can be handled.
 */
 #define kMaxConfigurations	32

// return values from getWindowType()
#define IOPCCARD16_BAD_INDEX		0
#define IOPCCARD16_MEMORY_WINDOW 	1
#define IOPCCARD16_IO_WINDOW 		2

/*! @class IOPCCard16Enabler
    @abstract Class used to control the configuration of 16-bit PC Card devices.
    @discussion
When a 16-bit PC Card is inserted, the PC Card Family creates an
IOPCCard16Device provider nub for drivers to match against.  The
provider nub allows the attached driver to control the card.  For each
instance of the IOPCCard16Device provider nub there is also an
IOPCCard16Enabler object.  Most calls to the provider nub are routed
to the enabler object.  All calls to the enabler come from the
provider nub.

16-bit drivers need to take the additional step of configuring the card
before they can request to have hardware registers mapped into virtual
memory for them.  This differs from the PCI or CardBus drivers where
the card is presented to the driver in a state that is basically ready
to go.

The class IOPCCard16Enabler implements the "default" card enabler for
the configuration of cards.  For most cards, this default enabler is
sufficient for handling the needs of your attached driver. Some
drivers may require additional support. The IOPCCard16Enabler class
can be subclassed to provide additional support.

The attached 16-bit PC Card driver can replace the default enabler
prior to requesting a configuration by calling its provider's
installEnabler() method.  If your driver supports multiple cards, it
can implement more than one enabler and install the correct enabler
depending on the card that it matches against.

The most common reason to create your own enabler is to override the
default sorting of the configuration tuple entries
 (CISTPL_CFTABLE_ENTRY) in the card's Card Information Structure (CIS)
or Metaformat.  Drivers may want to look for different window
configurations first.  You may wish to filter out certain
configurations or in the case of a mistake in the CIS on your card you
may need to replace parts the CIS and/or override parts of the
configuration process.

The configure method in the provider's nub calls the enabler's
configure method to do three things: retrieve the configuration
entries from the card's CIS, sort those entries, and then try each
entry one by one until a configuration is found that works with
that machine's overall configuration.  Any or all of these steps can be
overridden if necessary.
*/

class IOPCCard16Enabler : public OSObject
{
    OSDeclareDefaultStructors(IOPCCard16Enabler);

 protected:
    /*! @var device
      Pointer to the provider nub */
    IOPCCard16Device *		device;
    /*! @var handle
      Stores the Card Services handle for this socket */
    client_handle_t		handle;
    /*! @var state
      Stores the current state of this socket */
    u_int			state;
    /*! @var configuration
      Stores the configuration reserved from Card Services */
    config_req_t		configuration;
    /*! @var configTable
      Stores the expanded information from the CIS configuration tuples */
    cistpl_cftable_entry_t *	configTable[kMaxConfigurations];
    /*! @var tableEntryCount
      Number of entries stored in the configTable */
    u_int			tableEntryCount;
    /*! @var memoryWindowCount
      Number of reserved memory windows */
    UInt32			memoryWindowCount;
    /*! @var ioWindowCount
      Number of reserved I/O windows */
    UInt32			ioWindowCount;
    /*! @var io
      Tracks the current I/O reservations */
    io_req_t			io;
    /*! @var irq
      Tracks the current IRQ reservations */
    irq_req_t			irq;
    /*! @var win
      Stores the Card Services handle for a memory window */
    window_handle_t		win[CISTPL_MEM_MAX_WIN];
    /*! @var req
      Tracks the current common memory reservations */
    win_req_t			req[CISTPL_MEM_MAX_WIN];
    /*! @var map
      Tracks the current common memory mapping */
    memreq_t 			map[CISTPL_MEM_MAX_WIN];

    struct ExpansionData	{ };
    ExpansionData *		reserved;

 public:
    /*! @function withDevice
     *  @abstract Sets up a new enabler.
     *  @discussion This factory method creates and connects an enabler to a 16-bit PC Card provider nub.
     *  @result Returns the address of the new enabler.
     */    
    static IOPCCard16Enabler *	withDevice(IOPCCard16Device * provider);

    virtual bool		init(IOPCCard16Device * provider);
    virtual bool		attach(IOPCCard16Device * provider);
    virtual bool		detach(IOPCCard16Device * provider);
    virtual void		free(void);

    /*! @function eventHandler
     *  @abstract Hook for Card Services events.
     *  @discussion This method allows the enabler to catch Card Services events prior to routing them to the attached driver(s).  This may be helpful if you need to do addition work or clean up for certain events. The default enabler does nothing.
     *  @result A return value of non-zero prevents the event from being passed on to the socket drivers.
     */    
    virtual int			eventHandler(cs_event_t event, int priority, event_callback_args_t *args);

    /*! @function setPowerState
     *  @abstract Hook for power management state changes.
     *  @discussion This method allows the enabler to catch power management events.  This may be helpful if you need to do addition work or clean up for certain events. The default enabler uses this to track the state of power management.
     *  @result The return value is currently ignored.
     */    
    virtual IOReturn		setPowerState(unsigned long, IOService *);

    /*! @function configure
     *  @abstract Selects a 16-bit card configuration and enables it for use.
     *  @discussion This method uses the indicated index from the 16-bit PC Card Configuration Table Entry Tuple, CISTPL_CFTABLE_ENTRY, to allocate resources and properly configure the card.  If the index is not specified, the enabler will decide which configuration entries are to be tried.
     *  @param index Index of configuration to try.  If no index is given then it is up to the enabler to decide.
     *  @result Returns true if the card configuration was successful.
     */    
    virtual bool		configure(UInt32 index=0);
    /*! @function unconfigure
     *  @abstract Unconfigures a card.
     *  @discussion This method releases resources that were previously allocated back to Card Services.
     *  @result Returns true if the card was successfully unconfigured.
     */    
    virtual bool		unconfigure();

    /*! @function getConfigurations
     *  @abstract Adds configuration data from the card's CIS to the configTable array.
     *  @discussion This method fetches configuration data from the card's CIS and expands them out into a form that is easier to use.
     *  @result Returns true if any configurations were successfully found.
     */    
    virtual bool		getConfigurations(void);

    /*! @function sortConfigurations
     *  @abstract Sorts configurations in the selection order.
     *  @discussion This method sorts configurations into the order in which they should be tried.  This method can also be used to eliminate configurations that might not be valid.
     *  @result Returns true if any configurations were successfully found.
     */    
    virtual bool		sortConfigurations(void);

    /*! @function tryConfiguration
     *  @abstract Tests if a configuration can be used.
     *  @discussion This method is used to test if a configuration can be reserved from Card Services.  If all resources are successfully reserved, the configuration is kept.  The configure method enables the configuration later on.  The built configuration is kept in the state variable, configuration.
     *  @result Returns true if any configurations were successfully found.
     */    
    virtual bool		tryConfiguration(UInt32 index);

    /*! @function getState
     *  @abstract Returns the current state of the card.
     *  @discussion This method returns the current state of the card enabler.
     *  @result Current state of card.
     */    
    virtual u_int		getState(void);

    /*! @function getConfigurationInfo
     *  @abstract Returns information on the card's current configuration.
     *  @discussion This is a convenience method used to call the Card Services call GetConfigurationInfo.
     *  @param config Pointer to config_info_t structure to be filled in.
     *  @result Returns true on success.
     */    
    virtual bool		getConfigurationInfo(config_info_t * config);

    /*! @function getWindowCount
     *  @abstract Returns the number of windows that have been configured.
     *  @discussion This method returns the number of windows that have been reserved in this configuration.
     *  @result Returns the number of windows.
     */    
    virtual UInt32		getWindowCount(void);
    
    /*! @function getWindowType
     *  @abstract Returns the window type.
     *  @discussion This method is used to find the type of window given its index.  There are two types of windows, I/O and memory.  If they are available in a specific configuration, memory windows will always come first in the list of windows.
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
    virtual bool		getWindowAttributes(UInt32 index, UInt32 * attributes);

    /*! @function getWindowHandle
     *  @abstract Returns the Card Services handle for this window.
     *  @discussion This method returns the Card Services handle for the window requested.  This call is only valid for memory windows.
     *  @param index Index to window.
     *  @param handle Pointer to the window_handle_t structure to be filled in.
     *  @result Returns true if the window handle was found.
     */    
    virtual bool		getWindowHandle(UInt32 index, window_handle_t * handle);

    /*! @function getWindowOffset
     *  @abstract Returns the offset that this window is currently at.
     *  @discussion This method returns the current offset for this window into the card's memory space.  This call is only valid for memory windows.
     *  @param index Index of window.
     *  @param offset The current offset for this window.
     *  @result Returns true if the returned window offset is valid.
     */    
    virtual bool		getWindowOffset(UInt32 index, UInt32 * offset);

    /*! @function setWindowOffset
     *  @abstract Sets the offset for this window.
     *  @discussion This method updates the offset into the card's memory space for this window.  This call is only valid for memory windows.
     *  @param index Index of window.
     *  @param offset The new offset for this window.
     *  @result Returns true if the window offset was successfully updated.
     */    
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
