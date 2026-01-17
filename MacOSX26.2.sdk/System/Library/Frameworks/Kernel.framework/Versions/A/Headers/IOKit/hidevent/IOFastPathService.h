/*
 * Copyright (C) 2024 Apple Inc. All rights reserved.
 *
 * This document is the property of Apple Inc.
 * It is considered confidential and proprietary.
 *
 * This document may not be reproduced or transmitted in any form,
 * in whole or in part, without the express written permission of
 * Apple Inc.
 */

#ifndef IO_FASTPATH_SERVICE_H
#define IO_FASTPATH_SERVICE_H

#include <IOFastPath/IOFastPathCommon.h>
#include <IOKit/IOService.h>
#include <IOKit/IOCircularDataQueue.h>

/// Object representing a single field of an IOFastPath sample.
///
class IOFastPathField : public OSObject
{
    OSDeclareDefaultStructors(IOFastPathField);
    using super = OSObject;

public:

    /// Create a new field object. Asserts on failure.
    static OSPtr<IOFastPathField> create(IOFastPathFieldKey key, IOFastPathFieldType type, size_t offset, size_t size);

    /// See OSObject.h
    virtual bool serialize(OSSerialize * serializer) const override;

    IOFastPathFieldKey getKey() const { return _key; }
    IOFastPathFieldType getType() const { return _type; }
    size_t getOffset() const { return _offset; }
    size_t getSize() const { return _size; }

private:

    bool init(IOFastPathFieldKey key, IOFastPathFieldType type, size_t offset, size_t size);

    IOFastPathFieldKey _key;
    IOFastPathFieldType _type;
    size_t _offset;
    size_t _size;
};

/// Descriptor for an IOFastPath service.
///
/// A descriptor defines the fields of a sample and its layout in memory.
///
class IOFastPathDescriptor : public OSObject
{
    OSDeclareDefaultStructors(IOFastPathDescriptor);
    using super = OSObject;

public:

    /// Create a new descriptor object. Asserts on failure.
    ///
    /// @param  fields
    ///     Array of `IOFastPathField` objects.
    ///
    static OSPtr<IOFastPathDescriptor> create(OSArray * fields);

    /// See OSObject.h
    virtual bool serialize(OSSerialize * serializer) const override;

    OSPtr<OSArray> copyFields() const;

    uint32_t getSampleSize() const { return _sampleSize; }

private:

    bool init(OSArray * fields);

    OSPtr<OSArray> _fields;
    uint32_t _sampleSize;
};


/// Abstract base class for a generic IOFastPath service.
///
/// `IOFastPathService` implements features common to all IOFastPath services. Namely, it publishes
/// the fast path descriptor via the service's property table, manages the circular data queue used
/// to pass samples to user space clients, and supports creation of user clients to map the memory
/// for said queue into client process' address spaces.
///
/// Subclasses must override `createDescriptor` to define the fast path descriptor for a given
/// service instance.
///
class IOFastPathService : public IOService
{
    OSDeclareAbstractStructors(IOFastPathService);
    using super = IOService;
    friend class IOFastPathUserClient;

public:

    /// Start the service. See IOKit/IOService.h for more info.
    virtual bool start(IOService * provider) override;

    /// Stop the service. See IOKit/IOService.h for more info.
    virtual void stop(IOService * provider) override;

    /// Create a new user client. See IOKit/IOService.h for more info.
    virtual IOReturn newUserClient(task_t owningTask, void * securityID, UInt32 type, OSDictionary * properties, IOUserClient ** handler) override;

    /// Open the service. See IOKit/IOService.h for more info.
    virtual bool handleOpen(IOService * client, IOOptionBits options, void * arg) override;

    /// Close the service. See IOKit/IOService.h for more info.
    virtual void handleClose(IOService * client, IOOptionBits options) override;

    /// Returns whether the service is open. See IOKit/IOService.h for more info.
    virtual bool handleIsOpen(const IOService * client) const override;

protected:

    /// Returns `true` if the fast path service is a data producer, `false` if the service is a data
    /// consumer.
    ///
    virtual bool isProducer() const = 0;

    /// Create the fast path service's descriptor object.
    ///
    /// Subclasses must override this method to return the fast path descriptor for a given fast
    /// path service. The method is invoked by the base class during driver start.
    ///
    virtual OSPtr<IOFastPathDescriptor> createDescriptor() = 0;

    /// Copy the fast path descriptor.
    ///
    /// Do not call this method until `start` has completed succesfully. Once the driver has
    /// started, this method is guaranteed to succeed.
    ///
    OSPtr<IOFastPathDescriptor> copyDescriptor() const;

    /// Get a reference to the service's data queue.
    IOCircularDataQueue * getQueue() const;

private:

    OSPtr<IOFastPathDescriptor> _descriptor;
    IOCircularDataQueue * _queue;
    OSPtr<OSSet> _clients;
};


#endif /* IO_FASTPATH_SERVICE_H */
