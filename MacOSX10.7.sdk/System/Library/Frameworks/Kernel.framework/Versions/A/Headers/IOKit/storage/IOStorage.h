/*
 * Copyright (c) 1998-2011 Apple Inc. All rights reserved.
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
 * @header IOStorage
 * @abstract
 * This header contains the IOStorage class definition.
 */

#ifndef _IOSTORAGE_H
#define _IOSTORAGE_H

#include <IOKit/IOTypes.h>

/*!
 * @defined kIOStorageClass
 * @abstract
 * The name of the IOStorage class.
 */

#define kIOStorageClass "IOStorage"

/*!
 * @defined kIOStorageCategory
 * @abstract
 * kIOStorageCategory is a value for IOService's kIOMatchCategoryKey property.
 * @discussion
 * The kIOStorageCategory value is the standard value for the IOService property
 * kIOMatchCategoryKey ("IOMatchCategory") for all storage drivers.  All storage
 * objects that expect to drive new content (that is, produce new media objects)
 * are expected to compete within the kIOStorageCategory namespace.
 *
 * See the IOService documentation for more information on match categories.
 */

#define kIOStorageCategory "IOStorage"                /* (as IOMatchCategory) */

/*!
 * @defined kIOStorageFeaturesKey
 * @abstract
 * A property of any object in the storage stack.
 * @discussion
 * kIOStorageFeaturesKey is a property of any object in the storage stack that
 * wishes to express support of additional features, such as Force Unit Access.
 * It is typically defined in the device object below the block storage driver
 * object.  It has an OSDictionary value, where each entry describes one given
 * feature.
 */

#define kIOStorageFeaturesKey "IOStorageFeatures"

/*!
 * @defined kIOStorageFeatureUnmap
 * @abstract
 * Describes the presence of the Unmap feature.
 * @discussion
 * This property describes the ability of the storage stack to delete unused
 * data from the media.  It is one of the feature entries listed under the top-
 * level kIOStorageFeaturesKey property table.  It has an OSBoolean value.
 */

#define kIOStorageFeatureUnmap "Unmap"

/*!
 * @defined kIOStorageFeatureForceUnitAccess
 * @abstract
 * Describes the presence of the Force Unit Access feature.
 * @discussion
 * This property describes the ability of the storage stack to force a request
 * to access the media.  It is one of the feature entries listed under the top-
 * level kIOStorageFeaturesKey property table.  It has an OSBoolean value.
 */

#define kIOStorageFeatureForceUnitAccess "Force Unit Access"

#ifdef KERNEL
#ifdef __cplusplus

/*
 * Kernel
 */

#include <IOKit/assert.h>
#include <IOKit/IOMemoryDescriptor.h>
#include <IOKit/IOService.h>

/*!
 * @enum IOStorageAccess
 * @discussion
 * The IOStorageAccess enumeration describes the possible access levels for open
 * requests.
 * @constant kIOStorageAccessNone
 * No access is requested; should not be passed to open().
 * @constant kIOStorageAccessReader
 * Read-only access is requested.
 * @constant kIOStorageAccessReaderWriter
 * Read and write access is requested.
 * @constant kIOStorageAccessSharedLock
 * Shared access is requested.
 * @constant kIOStorageAccessExclusiveLock
 * Exclusive access is requested.
 */

enum
{
    kIOStorageAccessNone          = 0x00,
    kIOStorageAccessReader        = 0x01,
    kIOStorageAccessReaderWriter  = 0x03,
    kIOStorageAccessSharedLock    = 0x04,
    kIOStorageAccessExclusiveLock = 0x08
};

typedef UInt32 IOStorageAccess;

/*!
 * @enum IOStorageOptions
 * @discussion
 * Options for read and write storage requests.
 * @constant kIOStorageOptionForceUnitAccess
 * Force the request to access the media.
 * @constant kIOStorageOptionIsEncrypted
 * The data is already encrypted.
 */

enum
{
    kIOStorageOptionNone            = 0x00000000,
    kIOStorageOptionForceUnitAccess = 0x00000001,
    kIOStorageOptionIsEncrypted     = 0x00000010,
    kIOStorageOptionReserved        = 0xFFFFFFEE
};

typedef UInt32 IOStorageOptions;

/*!
 * @struct IOStorageAttributes
 * @discussion
 * Attributes of read and write storage requests.
 * @field options
 * Options for the request.  See IOStorageOptions.
 * @field reserved
 * Reserved for future use.  Set to zero.
 */

struct IOStorageAttributes
{
    IOStorageOptions options;
#ifdef __LP64__
    UInt32           reserved0032;
    UInt64           reserved0064;
    UInt64           reserved0128;
    void *           bufattr;
#else /* !__LP64__ */
    void *           bufattr;
    UInt64           reserved0064;
#endif /* !__LP64__ */
};

/*!
 * @struct IOStorageExtent
 * @discussion
 * Extent for unmap storage requests.
 * @field byteStart
 * Starting byte offset for the operation.
 * @field byteCount
 * Size of the operation.
 */

struct IOStorageExtent
{
    UInt64 byteStart;
    UInt64 byteCount;
};

/*!
 * @typedef IOStorageCompletionAction
 * @discussion
 * The IOStorageCompletionAction declaration describes the C (or C++) completion
 * routine that is called once an asynchronous storage operation completes.
 * @param target
 * Opaque client-supplied pointer (or an instance pointer for a C++ callback).
 * @param parameter
 * Opaque client-supplied pointer.
 * @param status
 * Status of the data transfer.
 * @param actualByteCount
 * Actual number of bytes transferred in the data transfer.
 */

typedef void (*IOStorageCompletionAction)(void *   target,
                                          void *   parameter,
                                          IOReturn status,
                                          UInt64   actualByteCount);

/*!
 * @struct IOStorageCompletion
 * @discussion
 * The IOStorageCompletion structure describes the C (or C++) completion routine
 * that is called once an asynchronous storage operation completes.   The values
 * passed for the target and parameter fields will be passed to the routine when
 * it is called.
 * @field target
 * Opaque client-supplied pointer (or an instance pointer for a C++ callback).
 * @field action
 * Completion routine to call on completion of the data transfer.
 * @field parameter
 * Opaque client-supplied pointer.
 */

struct IOStorageCompletion
{
    void *                    target;
    IOStorageCompletionAction action;
    void *                    parameter;
};

/*!
 * @class IOStorage
 * @abstract
 * The common base class for mass storage objects.
 * @discussion
 * The IOStorage class is the common base class for mass storage objects.  It is
 * an abstract class that defines the open/close/read/write APIs that need to be
 * implemented in a given subclass.  Synchronous versions of the read/write APIs
 * are provided here -- they are coded in such a way as to wrap the asynchronous
 * versions implemented in the subclass.
 */

class IOStorage : public IOService
{
    OSDeclareAbstractStructors(IOStorage);

protected:

    struct ExpansionData { /* */ };
    ExpansionData * _expansionData;

    /*!
     * @function handleOpen
     * @discussion
     * The handleOpen method grants or denies permission to access this object
     * to an interested client.  The argument is an IOStorageAccess value that
     * specifies the level of access desired -- reader or reader-writer.
     *
     * This method can be invoked to upgrade or downgrade the access level for
     * an existing client as well.  The previous access level will prevail for
     * upgrades that fail, of course.   A downgrade should never fail.  If the
     * new access level should be the same as the old for a given client, this
     * method will do nothing and return success.  In all cases, one, singular
     * close-per-client is expected for all opens-per-client received.
     * @param client
     * Client requesting the open.
     * @param options
     * Options for the open.  Set to zero.
     * @param access
     * Access level for the open.  Set to kIOStorageAccessReader or
     * kIOStorageAccessReaderWriter.
     * @result
     * Returns true if the open was successful, false otherwise.
     */

    virtual bool handleOpen(IOService *  client,
                            IOOptionBits options,
                            void *       access) = 0;

    /*!
     * @function handleIsOpen
     * @discussion
     * The handleIsOpen method determines whether the specified client, or any
     * client if none is specified, presently has an open on this object.
     * @param client
     * Client to check the open state of.  Set to zero to check the open state
     * of all clients.
     * @result
     * Returns true if the client was (or clients were) open, false otherwise.
     */

    virtual bool handleIsOpen(const IOService * client) const = 0;

    /*!
     * @function handleClose
     * @discussion
     * The handleClose method closes the client's access to this object.
     * @param client
     * Client requesting the close.
     * @param options
     * Options for the close.  Set to zero.
     */

    virtual void handleClose(IOService * client, IOOptionBits options) = 0;

public:

#ifndef __LP64__
    /*
     * Initialize this object's minimal state.
     */

    virtual bool init(OSDictionary * properties = 0);
#endif /* !__LP64__ */

    /*!
     * @function complete
     * @discussion
     * Invokes the specified completion action of the read/write request.  If
     * the completion action is unspecified, no action is taken.  This method
     * serves simply as a convenience to storage subclass developers.
     * @param completion
     * Completion information for the data transfer.
     * @param status
     * Status of the data transfer.
     * @param actualByteCount
     * Actual number of bytes transferred in the data transfer.
     */

    static void complete(IOStorageCompletion * completion,
                         IOReturn              status,
                         UInt64                actualByteCount = 0);

#ifndef __LP64__
    static void complete(IOStorageCompletion completion,
                         IOReturn            status,
                         UInt64              actualByteCount = 0); /* DEPRECATED */
#endif /* !__LP64__ */

    /*!
     * @function open
     * @discussion
     * Ask the storage object for permission to access its contents; the method
     * is equivalent to IOService::open(), but with the correct parameter types.
     *
     * This method may also be invoked to upgrade or downgrade the access of an
     * existing open (if it fails, the existing open prevails).
     * @param client
     * Client requesting the open.
     * @param options
     * Options for the open.  Set to zero.
     * @param access
     * Access level for the open.  Set to kIOStorageAccessReader or
     * kIOStorageAccessReaderWriter.
     * @result
     * Returns true if the open was successful, false otherwise.
     */

    virtual bool open(IOService *     client,
                      IOOptionBits    options,
                      IOStorageAccess access);

#ifndef __LP64__
    virtual void read(IOService *          client,
                      UInt64               byteStart,
                      IOMemoryDescriptor * buffer,
                      IOStorageCompletion  completion) __attribute__ ((deprecated));

    virtual void write(IOService *          client,
                       UInt64               byteStart,
                       IOMemoryDescriptor * buffer,
                       IOStorageCompletion  completion) __attribute__ ((deprecated));
#endif /* !__LP64__ */

    /*!
     * @function read
     * @discussion
     * Read data from the storage object at the specified byte offset into the
     * specified buffer, synchronously.   When the read completes, this method
     * will return to the caller.  The actual byte count field is optional.
     * @param client
     * Client requesting the read.
     * @param byteStart
     * Starting byte offset for the data transfer.
     * @param buffer
     * Buffer for the data transfer.  The size of the buffer implies the size of
     * the data transfer.
     * @param attributes
     * Attributes of the data transfer.  See IOStorageAttributes.
     * @param actualByteCount
     * Returns the actual number of bytes transferred in the data transfer.
     * @result
     * Returns the status of the data transfer.
     */

#ifdef __LP64__
    virtual IOReturn read(IOService *           client,
                          UInt64                byteStart,
                          IOMemoryDescriptor *  buffer,
                          IOStorageAttributes * attributes      = 0,
                          UInt64 *              actualByteCount = 0);
#else /* !__LP64__ */
    virtual IOReturn read(IOService *           client,
                          UInt64                byteStart,
                          IOMemoryDescriptor *  buffer,
                          UInt64 *              actualByteCount = 0);
#endif /* !__LP64__ */

    /*!
     * @function write
     * @discussion
     * Write data into the storage object at the specified byte offset from the
     * specified buffer, synchronously.   When the write completes, this method
     * will return to the caller.  The actual byte count field is optional.
     * @param client
     * Client requesting the write.
     * @param byteStart
     * Starting byte offset for the data transfer.
     * @param buffer
     * Buffer for the data transfer.  The size of the buffer implies the size of
     * the data transfer.
     * @param attributes
     * Attributes of the data transfer.  See IOStorageAttributes.
     * @param actualByteCount
     * Returns the actual number of bytes transferred in the data transfer.
     * @result
     * Returns the status of the data transfer.
     */

#ifdef __LP64__
    virtual IOReturn write(IOService *           client,
                           UInt64                byteStart,
                           IOMemoryDescriptor *  buffer,
                           IOStorageAttributes * attributes      = 0,
                           UInt64 *              actualByteCount = 0);
#else /* !__LP64__ */
    virtual IOReturn write(IOService *           client,
                           UInt64                byteStart,
                           IOMemoryDescriptor *  buffer,
                           UInt64 *              actualByteCount = 0);
#endif /* !__LP64__ */

    /*!
     * @function synchronizeCache
     * @discussion
     * Flush the cached data in the storage object, if any, synchronously.
     * @param client
     * Client requesting the cache synchronization.
     * @result
     * Returns the status of the cache synchronization.
     */

    virtual IOReturn synchronizeCache(IOService * client) = 0;

    /*!
     * @function read
     * @discussion
     * Read data from the storage object at the specified byte offset into the
     * specified buffer, asynchronously.   When the read completes, the caller
     * will be notified via the specified completion action.
     *
     * The buffer will be retained for the duration of the read.
     * @param client
     * Client requesting the read.
     * @param byteStart
     * Starting byte offset for the data transfer.
     * @param buffer
     * Buffer for the data transfer.  The size of the buffer implies the size of
     * the data transfer.
     * @param attributes
     * Attributes of the data transfer.  See IOStorageAttributes.  It is the
     * responsibility of the callee to maintain the information for the duration
     * of the data transfer, as necessary.
     * @param completion
     * Completion routine to call once the data transfer is complete.  It is the
     * responsibility of the callee to maintain the information for the duration
     * of the data transfer, as necessary.
     */

#ifdef __LP64__
    virtual void read(IOService *           client,
                      UInt64                byteStart,
                      IOMemoryDescriptor *  buffer,
                      IOStorageAttributes * attributes,
                      IOStorageCompletion * completion) = 0;
#else /* !__LP64__ */
    virtual void read(IOService *           client,
                      UInt64                byteStart,
                      IOMemoryDescriptor *  buffer,
                      IOStorageAttributes * attributes,
                      IOStorageCompletion * completion); /* 10.5.0 */
#endif /* !__LP64__ */

    /*!
     * @function write
     * @discussion
     * Write data into the storage object at the specified byte offset from the
     * specified buffer, asynchronously.   When the write completes, the caller
     * will be notified via the specified completion action.
     *
     * The buffer will be retained for the duration of the write.
     * @param client
     * Client requesting the write.
     * @param byteStart
     * Starting byte offset for the data transfer.
     * @param buffer
     * Buffer for the data transfer.  The size of the buffer implies the size of
     * the data transfer.
     * @param attributes
     * Attributes of the data transfer.  See IOStorageAttributes.  It is the
     * responsibility of the callee to maintain the information for the duration
     * of the data transfer, as necessary.
     * @param completion
     * Completion routine to call once the data transfer is complete.  It is the
     * responsibility of the callee to maintain the information for the duration
     * of the data transfer, as necessary.
     */

#ifdef __LP64__
    virtual void write(IOService *           client,
                       UInt64                byteStart,
                       IOMemoryDescriptor *  buffer,
                       IOStorageAttributes * attributes,
                       IOStorageCompletion * completion) = 0;
#else /* !__LP64__ */
    virtual void write(IOService *           client,
                       UInt64                byteStart,
                       IOMemoryDescriptor *  buffer,
                       IOStorageAttributes * attributes,
                       IOStorageCompletion * completion); /* 10.5.0 */
#endif /* !__LP64__ */

    virtual IOReturn discard(IOService * client,
                             UInt64      byteStart,
                             UInt64      byteCount) __attribute__ ((deprecated));

    /*!
     * @function unmap
     * @discussion
     * Delete unused data from the storage object at the specified byte offsets,
     * synchronously.
     * @param client
     * Client requesting the operation.
     * @param extents
     * List of extents.  See IOStorageExtent.  It is legal for the callee to
     * overwrite the contents of this buffer in order to satisfy the request.
     * @param extentsCount
     * Number of extents.
     * @result
     * Returns the status of the operation.
     */

    virtual IOReturn unmap(IOService *       client,
                           IOStorageExtent * extents,
                           UInt32            extentsCount,
                           UInt32            options = 0); /* 10.6.6 */

    /*!
     * @function lockPhysicalExtents
     * @discussion
     * Lock the contents of the storage object against relocation temporarily,
     * for the purpose of getting physical extents.
     * @param client
     * Client requesting the operation.
     * @result
     * Returns true if the lock was successful, false otherwise.
     */

    virtual bool lockPhysicalExtents(IOService * client); /* 10.7.0 */

    /*!
     * @function copyPhysicalExtent
     * @discussion
     * Convert the specified byte offset into a physical byte offset, relative
     * to a physical storage object.  This call should only be made within the
     * context of lockPhysicalExtents().
     * @param client
     * Client requesting the operation.
     * @param byteStart
     * Starting byte offset for the operation.  Returns a physical byte offset,
     * relative to the physical storage object, on success.
     * @param byteCount
     * Size of the operation.  Returns the actual number of bytes which can be
     * transferred, relative to the physical storage object, on success. 
     * @result
     * A reference to the physical storage object, which should be released by
     * the caller, or a null on error.
     */

    virtual IOStorage * copyPhysicalExtent(IOService * client,
                                           UInt64 *    byteStart,
                                           UInt64 *    byteCount); /* 10.7.0 */

    /*!
     * @function unlockPhysicalExtents
     * @discussion
     * Unlock the contents of the storage object for relocation again.  This
     * call must balance a successful call to lockPhysicalExtents().
     * @param client
     * Client requesting the operation.
     */

    virtual void unlockPhysicalExtents(IOService * client); /* 10.7.0 */

    OSMetaClassDeclareReservedUsed(IOStorage,  0);
    OSMetaClassDeclareReservedUsed(IOStorage,  1);
    OSMetaClassDeclareReservedUsed(IOStorage,  2);
    OSMetaClassDeclareReservedUsed(IOStorage,  3);
#ifdef __LP64__
    OSMetaClassDeclareReservedUnused(IOStorage,  4);
    OSMetaClassDeclareReservedUnused(IOStorage,  5);
    OSMetaClassDeclareReservedUnused(IOStorage,  6);
#else /* !__LP64__ */
    OSMetaClassDeclareReservedUsed(IOStorage,  4);
    OSMetaClassDeclareReservedUsed(IOStorage,  5);
    OSMetaClassDeclareReservedUsed(IOStorage,  6);
#endif /* !__LP64__ */
    OSMetaClassDeclareReservedUnused(IOStorage,  7);
    OSMetaClassDeclareReservedUnused(IOStorage,  8);
    OSMetaClassDeclareReservedUnused(IOStorage,  9);
    OSMetaClassDeclareReservedUnused(IOStorage, 10);
    OSMetaClassDeclareReservedUnused(IOStorage, 11);
    OSMetaClassDeclareReservedUnused(IOStorage, 12);
    OSMetaClassDeclareReservedUnused(IOStorage, 13);
    OSMetaClassDeclareReservedUnused(IOStorage, 14);
    OSMetaClassDeclareReservedUnused(IOStorage, 15);
};

#endif /* __cplusplus */
#endif /* KERNEL */
#endif /* !_IOSTORAGE_H */
