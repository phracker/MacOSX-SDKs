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

#ifndef IO_FASTPATH_USERCLIENT_H
#define IO_FASTPATH_USERCLIENT_H

#include <IOFastPath/IOFastPathCommon.h>
#include <IOKit/IOUserClient.h>
#include <IOKit/IOEventSource.h>

class IOFastPathService;

/// Simple user client for accessing an `IOFastPathService`.
///
class IOFastPathUserClient : public IOUserClient2022
{
    OSDeclareDefaultStructors(IOFastPathUserClient);
    using super = IOUserClient2022;

public:

    /// See IOKit/IOService.h for more info.
    virtual bool start(IOService * provider) APPLE_KEXT_OVERRIDE;

    /// See IOKit/IOService.h for more info.
    virtual void stop(IOService * provider) APPLE_KEXT_OVERRIDE;

    /// See IOKit/IOService.h for more info.
    virtual bool willTerminate(IOService * provider, IOOptionBits options) APPLE_KEXT_OVERRIDE;

    /// See IOKit/IOUserClient.h for more info.
    virtual IOReturn clientClose() APPLE_KEXT_OVERRIDE;

    /// See IOKit/IOUserClient.h for more info.
    virtual IOReturn externalMethod(uint32_t selector, IOExternalMethodArgumentsOpaque * args) APPLE_KEXT_OVERRIDE;
    
    /// See IOKit/IOUserClient.h for more info.
    virtual IOReturn clientMemoryForType(UInt32 type, IOOptionBits * options, IOMemoryDescriptor ** memory) APPLE_KEXT_OVERRIDE;

private:

    IOReturn externalMethodGated(uint32_t selector, IOExternalMethodArgumentsOpaque * args);
    IOReturn clientMemoryForTypeGated(UInt32 type, IOOptionBits * options, IOMemoryDescriptor ** memory);

    /// Execute a block synchronously in the workloop gate. Returns `kIOReturnOffline` if the
    /// service has been made inactive. Otherwise, returns the value returned by `action`.
    ///
    IOReturn dispatchWorkloopSync(IOEventSource::ActionBlock action);

    OSPtr<IOFastPathService> _service;
    OSPtr<IOCommandGate> _gate;
};

#endif /* IO_FASTPATH_USERCLIENT_H */
