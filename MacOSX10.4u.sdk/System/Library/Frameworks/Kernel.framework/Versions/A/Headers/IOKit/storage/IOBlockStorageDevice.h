/*
 * Copyright (c) 1998-2005 Apple Computer, Inc. All rights reserved.
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

/*!
 * @header IOBlockStorageDevice
 * @abstract
 * This header contains the IOBlockStorageDevice class definition.
 */

#ifndef _IOBLOCKSTORAGEDEVICE_H
#define _IOBLOCKSTORAGEDEVICE_H

#include <IOKit/IOTypes.h>
#include <IOKit/storage/IOStorageDeviceCharacteristics.h>

/*!
 * @defined kIOBlockStorageDeviceClass
 * @abstract
 * The name of the IOBlockStorageDevice class.
 */

#define kIOBlockStorageDeviceClass "IOBlockStorageDevice"

/*!
 * @defined kIOBlockStorageDeviceWriteCacheStateKey
 * @abstract
 * The name of the property used to get or set the write cache state of the
 * block storage device.
 */
#define kIOBlockStorageDeviceWriteCacheStateKey	"WriteCacheState"

#ifdef KERNEL
#ifdef __cplusplus

/*
 * Kernel
 */

#include <IOKit/IOMemoryDescriptor.h>
#include <IOKit/IOMessage.h>
#include <IOKit/IOService.h>
#include <IOKit/storage/IOMedia.h>

/*!
 * @defined kIOMessageMediaStateHasChanged
 * @abstract
 * The message ID which indicates that the media state has changed.
 * @discussion
 * The message is passed to all clients of the IOBlockStorageDevice via the message() method.
 * The argument that is passed along with this message is an IOMediaState value.
 *
 * Devices that aren't capable of detecting media state changes indicate this in
 * the reportPollRequirements() method.
 */
#define kIOMessageMediaStateHasChanged iokit_family_msg(sub_iokit_block_storage, 1)

/* Property used for matching, so the generic driver gets the nub it wants. */
/*!
 * @defined kIOBlockStorageDeviceTypeKey
 * @abstract The name of the property tested for nub type matching by the generic block
 * storage driver.
 */
#define	kIOBlockStorageDeviceTypeKey	"device-type"
/*!
 * @defined kIOBlockStorageDeviceTypeGeneric
 * @abstract A character string used for nub matching.
 */
#define	kIOBlockStorageDeviceTypeGeneric	"Generic"

/*!
 * @class
 * IOBlockStorageDevice
 * @abstract
 * A generic block storage device abstraction.
 * @discussion
 * The IOBlockStorageDevice class exports the generic block storage protocol,
 * independent of the physical connection protocol (e.g. SCSI, ATA, USB),
 * forwarding all requests to its provider (the Transport Driver).
 * Though the nub does no actual processing of requests, it is necessary
 * in a C++ environment. The Transport Driver can be of any type, as
 * long as it inherits from IOService. Because Transport Drivers needn't
 * derive from a type known to IOBlockStorageDriver, it isn't possible for
 * IOBlockStorageDriver to include the appropriate header file to allow direct
 * communication with the Transport Driver. Thus we achieve polymorphism by 
 * having the Transport Driver instantiate a subclass of IOBlockStorageDevice.
 * A typical implementation for a concrete subclass of IOBlockStorageDevice
 * simply relays all methods to its provider (the Transport Driver), which
 * implements the protocol- and device-specific behavior.
 * 
 * All pure-virtual functions must be implemented by the Transport Driver, which
 * is responsible for instantiating the Nub.
 */

class IOBlockStorageDevice : public IOService {

    OSDeclareAbstractStructors(IOBlockStorageDevice)
    
protected:

    struct ExpansionData { /* */ };
    ExpansionData * _expansionData;

public:

    /* Overrides from IORegistryEntry */

    using IORegistryEntry::getProperty;

    /*!
     * @function init
     * @discussion
     * This function is overridden so that IOBlockStorageDevice can set a
     * property, used by IOBlockStorageDriver for matching. Since the concrete
     * subclass of IOBlockStorageDevice can be of any class type, the property
     * is used for matching.
     * 
     * This function is usually not overridden by developers.
     */    
    virtual bool	init(OSDictionary * properties);

    virtual OSObject *	getProperty(const OSSymbol * key) const;

    virtual IOReturn	setProperties(OSObject * properties);

    /* --- A subclass must implement the the following methods: --- */

    /*!
     * @function doAsyncReadWrite
     * @abstract
     * Start an asynchronous read or write operation.
     * @param buffer
     * An IOMemoryDescriptor describing the data-transfer buffer. The data direction
     * is contained in the IOMemoryDescriptor. Responsibility for releasing the descriptor
     * rests with the caller.
     * @param block
     * The starting block number of the data transfer.
     * @param nblks
     * The integral number of blocks to be transferred.
     * @param completion
     * The completion routine to call once the data transfer is complete.
     */

    virtual IOReturn	doAsyncReadWrite(IOMemoryDescriptor *buffer,
                                            UInt32 block, UInt32 nblks,
                                            IOStorageCompletion completion)	= 0;

    /* DEPRECATED */ virtual IOReturn	doSyncReadWrite(IOMemoryDescriptor *buffer,
    /* DEPRECATED */                                 UInt32 block,UInt32 nblks);

    /*!
     * @function doEjectMedia
     * @abstract
     * Eject the media.
     */
    virtual IOReturn	doEjectMedia(void)	= 0;

    /*!
     * @function doFormatMedia
     * @abstract
     * Format the media to the specified byte capacity.
     * @discussion
     * The specified byte capacity must be one supported by the device.
     * Supported capacities can be obtained by calling doGetFormatCapacities.
     * @param byteCapacity
     * The byte capacity to which the device is to be formatted, if possible.
     */
    virtual IOReturn	doFormatMedia(UInt64 byteCapacity)	= 0;

    /*!
     * @function doGetFormatCapacities
     * @abstract
     * Return the allowable formatting byte capacities.
     * @discussion
     * This function returns the supported byte capacities for the device.
     * @param capacities
     * Pointer for returning the list of capacities.
     * @param capacitiesMaxCount
     * The number of capacity values returned in "capacities," or if no buffer
     * is given, the total number of capacity values available.
     */
    virtual UInt32	doGetFormatCapacities(UInt64 * capacities,
                                            UInt32   capacitiesMaxCount) const	= 0;
    
    /*!
     * @function doLockUnlockMedia
     * @abstract
     * Lock or unlock the (removable) media in the drive.
     * @discussion
     * This method should only be called if the media is known to be removable.
     * @param doLock
     * True to lock the media, False to unlock.
     */
    virtual IOReturn	doLockUnlockMedia(bool doLock)	= 0;

    /*!
     * @function doSynchronizeCache
     * @abstract
     * Force data blocks in the hardware's buffer to be flushed to the media.
     * @discussion
     * This method should only be called if the media is writable.
     */
    virtual IOReturn	doSynchronizeCache(void)	= 0;
    
    /*!
     * @function getVendorString
     * @abstract
     * Return Vendor Name string for the device.
     * @result
     * A pointer to a static character string.
     */
    virtual char *	getVendorString(void)	= 0;
    
    /*!
     * @function getProductString
     * @abstract
     * Return Product Name string for the device.
     * @result
     * A pointer to a static character string.
     */
    virtual char *	getProductString(void)	= 0;
    
    /*!
     * @function getRevisionString
     * @abstract
     * Return Product Revision string for the device.
     * @result
     * A pointer to a static character string.
     */
    virtual char *	getRevisionString(void)	= 0;
    
    /*!
     * @function getAdditionalDeviceInfoString
     * @abstract
     * Return additional informational string for the device.
     * @result
     * A pointer to a static character string.
     */
    virtual char *	getAdditionalDeviceInfoString(void)	= 0;

    /*!
     * @function reportBlockSize
     * @abstract
     * Report the block size for the device, in bytes.
     * @param blockSize
     * Pointer to returned block size value.
     */    
    virtual IOReturn	reportBlockSize(UInt64 *blockSize)	= 0;

    /*!
     * @function reportEjectability
     * @abstract
     * Report if the media is ejectable under software control.
     * @discussion
     * This method should only be called if the media is known to be removable.
     * @param isEjectable
     * Pointer to returned result. True indicates the media is ejectable, False indicates
     * the media cannot be ejected under software control.
     */
    virtual IOReturn	reportEjectability(bool *isEjectable)	= 0;

    /*!
     * @function reportLockability
     * @abstract
     * Report if the media is lockable under software control.
     * @discussion
     * This method should only be called if the media is known to be removable.
     * @param isLockable
     * Pointer to returned result. True indicates the media can be locked in place; False
     * indicates the media cannot be locked by software.
     */
    virtual IOReturn	reportLockability(bool *isLockable)	= 0;

    /*!
     * @function reportMaxReadTransfer
     * @abstract
     * Report the maximum allowed byte transfer for read operations.
     * @discussion
     * Some devices impose a maximum data transfer size. Because this limit
     * may be determined by the size of a block-count field in a command, the limit may
     * depend on the block size of the transfer.
     * @param blockSize
     * The block size desired for the transfer.
     * @param max
     * Pointer to returned result.
     */
    virtual IOReturn	reportMaxReadTransfer (UInt64 blockSize, UInt64 *max)	= 0;

    /*!
     * @function reportMaxWriteTransfer
     * @abstract
     * Report the maximum allowed byte transfer for write operations.
     * @discussion
     * Some devices impose a maximum data transfer size. Because this limit
     * may be determined by the size of a block-count field in a command, the limit may
     * depend on the block size of the transfer.
     * @param blockSize
     * The block size desired for the transfer.
     * @param max
     * Pointer to returned result.
     */
    virtual IOReturn	reportMaxWriteTransfer(UInt64 blockSize,UInt64 *max)	= 0;
    
    /*!
     * @function reportMaxValidBlock
     * @abstract
     * Report the highest valid block for the device.
     * @param maxBlock
     * Pointer to returned result
     */    
    virtual IOReturn	reportMaxValidBlock(UInt64 *maxBlock)	= 0;

    /*!
     * @function reportMediaState
     * @abstract
     * Report the device's media state.
     * @discussion
     * This method reports whether we have media in the drive or not, and
     * whether the state has changed from the previously reported state.
     * 
     * A result of kIOReturnSuccess is always returned if the test for media is successful,
     * regardless of media presence. The mediaPresent result should be used to determine
     * whether media is present or not. A return other than kIOReturnSuccess indicates that
     * the Transport Driver was unable to interrogate the device. In this error case, the
     * outputs mediaState and changedState will *not* be stored.
     * @param mediaPresent Pointer to returned media state. True indicates media is present
     * in the device; False indicates no media is present.
     * @param changedState Pointer to returned result. True indicates a change of state since
     * prior calls, False indicates that the state has not changed.
     */
    virtual IOReturn	reportMediaState(bool *mediaPresent,bool *changedState)	= 0;
    
    /*!
     * @function reportPollRequirements
     * @abstract
     * Report if it's necessary to poll for media insertion, and if polling is expensive.
     * @discussion
     * This method reports whether the device must be polled to detect media
     * insertion, and whether a poll is expensive to perform.
     * 
     * The term "expensive" typically implies a device that must be spun-up to detect media,
     * as on a PC floppy. Most devices can detect media inexpensively.
     * @param pollRequired
     * Pointer to returned result. True indicates that polling is required; False indicates
     * that polling is not required to detect media.
     * @param pollIsExpensive
     * Pointer to returned result. True indicates that the polling operation is expensive;
     * False indicates that the polling operation is cheap.
     */
    virtual IOReturn	reportPollRequirements(bool *pollRequired,
                                            bool *pollIsExpensive)	= 0;
    
    /*!
     * @function reportRemovability
     * @abstract
     * Report whether the media is removable or not.
     * @discussion
     * This method reports whether the media is removable, but it does not
     * provide detailed information regarding software eject or lock/unlock capability.
     * @param isRemovable
     * Pointer to returned result. True indicates that the media is removable; False
     * indicates the media is not removable.
     */
    virtual IOReturn	reportRemovability(bool *isRemovable)  	= 0;
    
    /*!
     * @function reportWriteProtection
     * @abstract
     * Report whether the media is write-protected or not.
     * @param isWriteProtected
     * Pointer to returned result. True indicates that the media is write-protected (it
     * cannot be written); False indicates that the media is not write-protected (it
     * is permissible to write).
     */
    virtual IOReturn	reportWriteProtection(bool *isWriteProtected)	= 0;

    /*!
     * @function doAsyncReadWrite
     * @abstract
     * Start an asynchronous read or write operation.
     * @param buffer
     * An IOMemoryDescriptor describing the data-transfer buffer. The data direction
     * is contained in the IOMemoryDescriptor. Responsibility for releasing the descriptor
     * rests with the caller.
     * @param block
     * The starting block number of the data transfer.
     * @param nblks
     * The integral number of blocks to be transferred.
     * @param completion
     * The completion routine to call once the data transfer is complete.
     */
    virtual IOReturn	doAsyncReadWrite(IOMemoryDescriptor *buffer,
                                            UInt64 block, UInt64 nblks,
                                            IOStorageCompletion completion);

    OSMetaClassDeclareReservedUsed(IOBlockStorageDevice, 0); /* 10.2.0 */

    /*!
     * @function getWriteCacheState
     * @abstract
     * Reports the current write cache state of the device.
     * @discussion
     * Reports the current write cache state of the device.  The write cache
     * state is not guaranteed to persist across reboots and detaches.
     * @param enabled
     * Pointer to returned result. True indicates the write cache is enabled;
     * False indicates the write cache is disabled.
     */
    virtual IOReturn	getWriteCacheState(bool *enabled);

    OSMetaClassDeclareReservedUsed(IOBlockStorageDevice, 1); /* 10.3.0 */

    /*!
     * @function setWriteCacheState
     * @abstract
     * Sets the write cache state of the device.
     * @discussion
     * Sets the write cache state of the device.  The write cache state
     * is not guaranteed to persist across reboots and detaches.
     * @param enabled
     * True to enable the write cache; False to disable the write cache.
     */
    virtual IOReturn	setWriteCacheState(bool enabled);

    OSMetaClassDeclareReservedUsed(IOBlockStorageDevice, 2); /* 10.3.0 */

    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice,  3);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice,  4);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice,  5);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice,  6);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice,  7);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice,  8);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice,  9);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 10);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 11);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 12);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 13);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 14);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 15);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 16);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 17);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 18);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 19);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 20);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 21);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 22);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 23);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 24);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 25);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 26);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 27);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 28);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 29);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 30);
    OSMetaClassDeclareReservedUnused(IOBlockStorageDevice, 31);
};

#endif /* __cplusplus */
#endif /* KERNEL */
#endif /* !_IOBLOCKSTORAGEDEVICE_H */
