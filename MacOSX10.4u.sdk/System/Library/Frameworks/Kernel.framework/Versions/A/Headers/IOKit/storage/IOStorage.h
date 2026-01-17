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

#ifdef KERNEL
#ifdef __cplusplus

/*
 * Kernel
 */

#include <IOKit/assert.h>
#include <IOKit/IOMemoryDescriptor.h>
#include <IOKit/IOService.h>

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
     * @param completion
     * Completion routine to call once the data transfer is complete.
     */

    virtual void read(IOService *          client,
                      UInt64               byteStart,
                      IOMemoryDescriptor * buffer,
                      IOStorageCompletion  completion) = 0;

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
     * @param completion
     * Completion routine to call once the data transfer is complete.
     */

    virtual void write(IOService *          client,
                       UInt64               byteStart,
                       IOMemoryDescriptor * buffer,
                       IOStorageCompletion  completion) = 0;

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
     * @param actualByteCount
     * Returns the actual number of bytes transferred in the data transfer.
     * @result
     * Returns the status of the data transfer.
     */

    virtual IOReturn read(IOService *          client,
                          UInt64               byteStart,
                          IOMemoryDescriptor * buffer,
                          UInt64 *             actualByteCount = 0);

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
     * @param actualByteCount
     * Returns the actual number of bytes transferred in the data transfer.
     * @result
     * Returns the status of the data transfer.
     */

    virtual IOReturn write(IOService *          client,
                           UInt64               byteStart,
                           IOMemoryDescriptor * buffer,
                           UInt64 *             actualByteCount = 0);

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

    static void complete(IOStorageCompletion completion,
                         IOReturn            status,
                         UInt64              actualByteCount = 0);

    OSMetaClassDeclareReservedUnused(IOStorage,  0);
    OSMetaClassDeclareReservedUnused(IOStorage,  1);
    OSMetaClassDeclareReservedUnused(IOStorage,  2);
    OSMetaClassDeclareReservedUnused(IOStorage,  3);
    OSMetaClassDeclareReservedUnused(IOStorage,  4);
    OSMetaClassDeclareReservedUnused(IOStorage,  5);
    OSMetaClassDeclareReservedUnused(IOStorage,  6);
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
