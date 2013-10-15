/*
 * Copyright (c) 1998-2009 Apple Inc. All rights reserved.
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
 * @header IOMedia
 * @abstract
 * This header contains the IOMedia class definition.
 */

#ifndef _IOMEDIA_H
#define _IOMEDIA_H

#include <IOKit/IOTypes.h>

/*!
 * @defined kIOMediaClass
 * @abstract
 * The name of the IOMedia class.
 */

#define kIOMediaClass "IOMedia"

/*!
 * @defined kIOMediaContentKey
 * @abstract
 * A property of IOMedia objects.
 * @discussion
 * The kIOMediaContentKey property has an OSString
 * value and contains a description of the media's
 * contents.  The description is the same as the hint at the time of the
 * object's creation, but it is possible that the description has been overridden
 * by a client (which has probed the media and identified the content correctly)
 * of the media object.  It is more accurate than the hint for this reason.  The
 * string is formed in the likeness of Apple's "Apple_HFS" strings or in the
 * likeness of a UUID.
 */

#define kIOMediaContentKey "Content"

/*!
 * @defined kIOMediaContentHintKey
 * @abstract
 * A property of IOMedia objects.
 * @discussion
 * The kIOMediaContentHintKey property has an OSString
 * value and contains a hint of the media's contents.
 * The hint is set at the time of the object's creation, should the creator have
 * a clue as to what it may contain.  The hint string does not change for the
 * lifetime of the object and is formed in the likeness of Apple's "Apple_HFS"
 * strings or in the likeness of a UUID.
 */

#define kIOMediaContentHintKey "Content Hint"

/*!
 * @defined kIOMediaEjectableKey
 * @abstract
 * A property of IOMedia objects.
 * @discussion
 * The kIOMediaEjectableKey property has an OSBoolean
 * value and describes whether the media is ejectable
 * from the drive mechanism under software control.  Implies IOMediaRemovable
 * is also true.
 */

#define kIOMediaEjectableKey "Ejectable"

/*!
 * @defined kIOMediaLeafKey
 * @abstract
 * A property of IOMedia objects.
 * @discussion
 * The kIOMediaLeafKey property has an OSBoolean value and describes whether the media is a leaf, that is,
 * it is the deepest media object in this branch of the I/O Registry.
 */

#define kIOMediaLeafKey "Leaf"

/*!
 * @defined kIOMediaOpenKey
 * @abstract
 * A property of IOMedia objects.
 * @discussion
 * The kIOMediaOpenKey property has an OSBoolean value and describes whether
 * a client presently has an open on this media.
 */

#define kIOMediaOpenKey "Open"

/*!
 * @defined kIOMediaPreferredBlockSizeKey
 * @abstract
 * A property of IOMedia objects.
 * @discussion
 * The kIOMediaPreferredBlockSizeKey property has an
 * OSNumber value and describes the media's natural
 * block size in bytes.  This information is useful to clients that want to
 * optimize access to the media.
 */

#define kIOMediaPreferredBlockSizeKey "Preferred Block Size"

/*!
 * @defined kIOMediaRemovableKey
 * @abstract
 * A property of IOMedia objects.
 * @discussion
 * The kIOMediaRemovableKey property has an OSBoolean
 * value and describes whether the media is removable
 * from the drive mechanism.
 */

#define kIOMediaRemovableKey "Removable"

/*!
 * @defined kIOMediaSizeKey
 * @abstract
 * A property of IOMedia objects.
 * @discussion
 * The kIOMediaSizeKey property has an OSNumber value and describes the total length of the media in
 * bytes.
 */

#define kIOMediaSizeKey "Size"

/*!
 * @defined kIOMediaUUIDKey
 * @abstract
 * A property of IOMedia objects.
 * @discussion
 * The kIOMediaUUIDKey property has an OSString value and contains a persistent
 * Universal Unique Identifier for the media if such an identifier is available.
 */

#define kIOMediaUUIDKey "UUID"

/*!
 * @defined kIOMediaWholeKey
 * @abstract
 * A property of IOMedia objects.
 * @discussion
 * The kIOMediaWholeKey property has an OSBoolean
 * value and describes whether the media is whole, that is,
 * it represents the whole disk (the physical disk, or a virtual replica
 * thereof).
 */

#define kIOMediaWholeKey "Whole"

/*!
 * @defined kIOMediaWritableKey
 * @abstract
 * A property of IOMedia objects.
 * @discussion
 * The kIOMediaWritableKey property has an OSBoolean
 * value and describes whether the media is writable.
 */

#define kIOMediaWritableKey "Writable"

/*!
 * @defined kIOMediaContentMaskKey
 * @abstract
 * A property of IOMedia clients.
 * @discussion
 * The kIOMediaContentMaskKey property has an OSString
 * value and must exist in all IOMedia clients that
 * drive new content (that is, produce new media objects).  When the client
 * matches against the provider media, the value of the client's
 * kIOMediaContentMaskKey property is used to replace the provider's
 * kIOMediaContentKey property.
 */

#define kIOMediaContentMaskKey "Content Mask"

/*!
 * @defined kIOMediaIconKey
 * @abstract
 * A property of any object in the media stack.
 * @discussion
 * kIOMediaIconKey is a property of any object in the media stack that wishes
 * to override the default icon shown for the media objects in the stack.  It
 * is usually defined in a provider object below the media object.  It has an
 * OSDictionary value, with properties identical to the kIOIconKey definition,
 * that is, kCFBundleIdentifierKey and kIOBundleResourceFileKey.
 */

#define kIOMediaIconKey "IOMediaIcon"

/*!
 * @enum IOMediaAttributeMask
 * @discussion
 * The IOMediaAttributeMask bit mask describes various attributes of
 * the media object, such as its ejectability and its removability.
 * @constant kIOMediaAttributeEjectableMask
 * Indicates whether the media is ejectable from the drive mechanism
 * under software control.  Implies kIOMediaAttributeRemovableMask.
 * @constant kIOMediaAttributeRemovableMask
 * Indicates whether the media is removable from the drive mechanism.
 */

enum
{
    kIOMediaAttributeEjectableMask = 0x00000001,
    kIOMediaAttributeRemovableMask = 0x00000002,
    kIOMediaAttributeReservedMask  = 0xFFFFFFFC
};

typedef UInt32 IOMediaAttributeMask;

#ifdef KERNEL
#ifdef __cplusplus

/*
 * Kernel
 */

#include <IOKit/storage/IOStorage.h>

/*!
 * @class IOMedia
 * @abstract
 * A random-access disk device abstraction.
 * @discussion
 * The IOMedia class is a random-access disk device abstraction.   It provides a
 * consistent interface for both real and virtual disk devices, for subdivisions
 * of disks such as partitions, for supersets of disks such as RAID volumes, and
 * so on.   It extends the IOStorage class by implementing the appropriate open,
 * close, read, write, and matching semantics for media objects.  The properties
 * it has reflect the properties of real disk devices,  such as ejectability and
 * writability.
 *
 * The read and write interfaces support byte-level access to the storage space,
 * with the appropriate deblocking handled by the block storage driver, however,
 * a typical client will want to get the natural block size in order to optimize
 * access to the real disk device.  A read or write is accepted so long as the
 * client's access is valid, the media is formatted and the transfer is within
 * the bounds of the media.  An optional non-zero base (offset) is then applied
 * before the read or write is passed to provider object.
 */

class IOMedia : public IOStorage
{
    OSDeclareDefaultStructors(IOMedia)

protected:

    struct ExpansionData { /* */ };
    ExpansionData * _expansionData;

    UInt32          _attributes;

    bool            _isWhole;
    bool            _isWritable;

    UInt64          _mediaBase;  /* (relative to the storage object below us) */
    UInt64          _mediaSize;

    IOStorageAccess _openLevel;
    OSDictionary *  _openClients;

    UInt32          _reserved0320;

    UInt64          _preferredBlockSize;

    /*
     * Free all of this object's outstanding resources.
     */

    virtual void free();

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
     *
     * This implementation replaces the IOService definition of handleOpen().
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
                            void *       access);

    /*!
     * @function handleIsOpen
     * @discussion
     * The handleIsOpen method determines whether the specified client, or any
     * client if none is specified, presently has an open on this object.
     *
     * This implementation replaces the IOService definition of handleIsOpen().
     * @param client
     * Client to check the open state of.  Set to zero to check the open state
     * of all clients.
     * @result
     * Returns true if the client was (or clients were) open, false otherwise.
     */

    virtual bool handleIsOpen(const IOService * client) const;

    /*!
     * @function handleClose
     * @discussion
     * The handleClose method closes the client's access to this object.
     *
     * This implementation replaces the IOService definition of handleClose().
     * @param client
     * Client requesting the close.
     * @param options
     * Options for the close.  Set to zero.
     */

    virtual void handleClose(IOService * client, IOOptionBits options);

public:

    using IOStorage::read;
    using IOStorage::write;

#ifndef __LP64__
    virtual bool init(UInt64         base,
                      UInt64         size,
                      UInt64         preferredBlockSize,
                      bool           isEjectable,
                      bool           isWhole,
                      bool           isWritable,
                      const char *   contentHint = 0,
                      OSDictionary * properties  = 0) __attribute__ ((deprecated));
#endif /* !__LP64__ */

    /*
     * This method is called for each client interested in the services we
     * provide.  The superclass links us as a parent to this client in the
     * I/O Kit registry on success.
     */

    virtual bool attachToChild(IORegistryEntry *       client,
                               const IORegistryPlane * plane);

    /*
     * This method is called for each client that loses interest in the
     * services we provide.  The superclass unlinks us from this client
     * in the I/O Kit registry on success.
     */

    virtual void detachFromChild(IORegistryEntry *       client,
                                 const IORegistryPlane * plane);

    /*
     * Obtain this object's provider.  We override the superclass's method to
     * return a more specific subclass of OSObject -- IOStorage.  This method
     * serves simply as a convenience to subclass developers.
     */

    virtual IOStorage * getProvider() const;

    /*
     * Compare the properties in the supplied table to this object's properties.
     */

    virtual bool matchPropertyTable(OSDictionary * table, SInt32 * score);

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

    virtual void read(IOService *           client,
                      UInt64                byteStart,
                      IOMemoryDescriptor *  buffer,
                      IOStorageAttributes * attributes,
                      IOStorageCompletion * completion);

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

    virtual void write(IOService *           client,
                       UInt64                byteStart,
                       IOMemoryDescriptor *  buffer,
                       IOStorageAttributes * attributes,
                       IOStorageCompletion * completion);

    /*!
     * @function synchronizeCache
     * @discussion
     * Flush the cached data in the storage object, if any, synchronously.
     * @param client
     * Client requesting the cache synchronization.
     * @result
     * Returns the status of the cache synchronization.
     */

    virtual IOReturn synchronizeCache(IOService * client);

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
                           UInt32            options = 0);

    /*!
     * @function getPreferredBlockSize
     * @discussion
     * Ask the media object for its natural block size.  This information
     * is useful to clients that want to optimize access to the media.
     * @result
     * Natural block size, in bytes.
     */

    virtual UInt64 getPreferredBlockSize() const;

    /*!
     * @function getSize
     * @discussion
     * Ask the media object for its total length in bytes.
     * @result
     * Media size, in bytes.
     */

    virtual UInt64 getSize() const;

    /*!
     * @function getBase
     * @discussion
     * Ask the media object for its byte offset relative to its provider media
     * object below it in the storage hierarchy.
     * Media offset, in bytes.
     */

    virtual UInt64 getBase() const;

    /*!
     * @function isEjectable
     * @discussion
     * Ask the media object whether it is ejectable.
     * @result
     * Returns true if the media is ejectable, false otherwise.
     */

    virtual bool isEjectable() const;

    /*!
     * @function isFormatted
     * @discussion
     * Ask the media object whether it is formatted.
     * @result
     * Returns true if the media is formatted, false otherwise.
     */

    virtual bool isFormatted() const;

    /*!
     * @function isWhole
     * @discussion
     * Ask the media object whether it represents the whole disk.
     * @result
     * Returns true if the media represents the whole disk, false otherwise.
     */

    virtual bool isWhole() const;

    /*!
     * @function isWritable
     * @discussion
     * Ask the media object whether it is writable.
     * @result
     * Returns true if the media is writable, false otherwise.
     */

    virtual bool isWritable() const;

    /*!
     * @function getContent
     * @discussion
     * Ask the media object for a description of its contents.  The description
     * is the same as the hint at the time of the object's creation,  but it is
     * possible that the description has been overridden by a client (which has probed
     * the media and identified the content correctly) of the media object.  It
     * is more accurate than the hint for this reason.  The string is formed in
     * the likeness of Apple's "Apple_HFS" strings or in the likeness of a UUID.
     *
     * The content description can be overridden by any client that matches onto
     * this media object with a match category of kIOStorageCategory.  The media
     * object checks for a kIOMediaContentMaskKey property in the client, and if
     * it finds one, it copies it into kIOMediaContentKey property.
     * @result
     * Description of media's contents.
     */

    virtual const char * getContent() const;

    /*!
     * @function getContentHint
     * @discussion
     * Ask the media object for a hint of its contents.  The hint is set at the
     * time of the object's creation, should the creator have a clue as to what
     * it may contain.  The hint string does not change for the lifetime of the
     * object and is also formed in the likeness of Apple's "Apple_HFS" strings
     * or in the likeness of a UUID.
     * @result
     * Hint of media's contents.
     */

    virtual const char * getContentHint() const;

    /*!
     * @function init
     * @discussion
     * Initialize this object's minimal state.
     * @param base
     * Media offset, in bytes.
     * @param size
     * Media size, in bytes.
     * @param preferredBlockSize
     * Natural block size, in bytes.
     * @param attributes
     * Media attributes, such as ejectability and removability.  See
     * IOMediaAttributeMask.
     * @param isWhole
     * Indicates whether the media represents the whole disk.
     * @param isWritable
     * Indicates whether the media is writable.
     * @param contentHint
     * Hint of media's contents (optional).  See getContentHint().
     * @param properties
     * Substitute property table for this object (optional).
     * @result
     * Returns true on success, false otherwise.
     */

    virtual bool init(UInt64               base,
                      UInt64               size,
                      UInt64               preferredBlockSize,
                      IOMediaAttributeMask attributes,
                      bool                 isWhole,
                      bool                 isWritable,
                      const char *         contentHint = 0,
                      OSDictionary *       properties  = 0); /* 10.2.0 */

    /*!
     * @function getAttributes
     * @discussion
     * Ask the media object for its attributes.
     * @result
     * Media attributes, such as ejectability and removability.  See
     * IOMediaAttributeMask.
     */

    virtual IOMediaAttributeMask getAttributes() const; /* 10.2.0 */

#ifdef __LP64__
    OSMetaClassDeclareReservedUnused(IOMedia,  0);
    OSMetaClassDeclareReservedUnused(IOMedia,  1);
#else /* !__LP64__ */
    OSMetaClassDeclareReservedUsed(IOMedia,  0);
    OSMetaClassDeclareReservedUsed(IOMedia,  1);
#endif /* !__LP64__ */
    OSMetaClassDeclareReservedUnused(IOMedia,  2);
    OSMetaClassDeclareReservedUnused(IOMedia,  3);
    OSMetaClassDeclareReservedUnused(IOMedia,  4);
    OSMetaClassDeclareReservedUnused(IOMedia,  5);
    OSMetaClassDeclareReservedUnused(IOMedia,  6);
    OSMetaClassDeclareReservedUnused(IOMedia,  7);
    OSMetaClassDeclareReservedUnused(IOMedia,  8);
    OSMetaClassDeclareReservedUnused(IOMedia,  9);
    OSMetaClassDeclareReservedUnused(IOMedia, 10);
    OSMetaClassDeclareReservedUnused(IOMedia, 11);
    OSMetaClassDeclareReservedUnused(IOMedia, 12);
    OSMetaClassDeclareReservedUnused(IOMedia, 13);
    OSMetaClassDeclareReservedUnused(IOMedia, 14);
    OSMetaClassDeclareReservedUnused(IOMedia, 15);
};

#endif /* __cplusplus */
#endif /* KERNEL */
#endif /* !_IOMEDIA_H */
