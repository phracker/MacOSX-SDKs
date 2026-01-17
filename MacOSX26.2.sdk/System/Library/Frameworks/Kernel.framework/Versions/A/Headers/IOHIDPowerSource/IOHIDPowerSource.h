/*
 * Copyright (C) 2021-2022 Apple Inc. All rights reserved.
 *
 * This document is the property of Apple Inc.
 * It is considered confidential and proprietary.
 *
 * This document may not be reproduced or transmitted in any form,
 * in whole or in part, without the express written permission of
 * Apple Inc.
 */
#pragma once

#include <IOKit/IOService.h>
#include <AppleCallbackPowerSource/AppleCallbackPowerSourceProvider.hpp>

class IOHIDTranslationService;

class IOHIDPowerSourceClient;

/*! @class IOHIDPowerSource
    @abstract Power source interface
 */
class IOHIDPowerSource: public AppleCallbackPowerSourceProvider
{
    OSDeclareDefaultStructors(IOHIDPowerSource)
 
    struct IOHIDPowerSource_ivar;
    IOHIDPowerSource_ivar * ivar;
    
    /*!
     * @function serializeDebugState
     * @abstract Serialize state of the object
     *
     * @param    ref    context
     * @param    serializer    serializer
     * @result   true if success , false is otherwise
     */

    bool serializeDebugState(void *ref, OSSerialize *serializer);

    /*!
     * @function copyClient
     * @abstract Copy reference of IOHIDPowerSourceClient for service
     *
     * @param    service    service
     * @result   instance of IOHIDPowerSourceClient on nullptr.
     */
    IOHIDPowerSourceClient * copyClient (const IOService * service) const;
 
    /*!
     * @function setInterfaceGated
     * @abstract Associate power source with IOHIDTranslationService called inGate.
     *
     * @param    interface    IOHIDTranslationService instance
     */
    void setInterfaceGated(IOHIDTranslationService * interface);

    /*!
     * @function handleTranslationEvent
     * @abstract callback from translation services
     *
     * @param    target    target object for this callback
     * @param    eventValue   event value.
     *
     */
    static void handleTranslationEvent (void * target,  OSDictionary * eventValue);

    /*!
     * @function handleTranslationEvent
     * @abstract callback from translation services
     *
     * @param    eventValue   event value.
     *
     */
    void handleTranslationEvent (OSDictionary * eventValue);

    /*!
     * @function handleEventCallback
     * @abstract callback for times event source use to process reposting event to object workloop
     *
     */
    void handleEventCallback();
    
protected:
    
    friend class IOHIDPowerSourceController;

    /*!
     * @function handlePowerSourceEvent
     * @abstract dispatch event to all clients
     *
     * @param    event    event value
     */
    virtual void handlePowerSourceEvent (OSDictionary * event);

    /*!
     * @function setInterface
     * @abstract Associate power source with IOHIDTranslationService
     *
     * @param    interface    IOHIDTranslationService instance
     */
    virtual void setInterface(IOHIDTranslationService * interface);

    /*!
     * @function setInterface
     * @abstract Disassociate power source with IOHIDTranslationService
     *
     * @param    interface    IOHIDTranslationService instance
     */
    virtual void removeInterface(IOHIDTranslationService * interface);

    /*!
     * @function handleOpen
     * @abstract See <code>IOService::handleOpen</code> for more details.
     *
     * @param    client    Client service provider
     * @param    options   options
     * @param    argument   argument
     * @result   true if success , false is otherwise
     *
     */
    virtual bool handleOpen(IOService *  client,
                            IOOptionBits options,
                            void *       argument) APPLE_KEXT_OVERRIDE;


    /*!
     * @function handleClose
     * @abstract See <code>IOService::handleOpen</code> for more details.
     *
     * @param    client    Client service provider
     * @param    options   options
     *
     */
    virtual void handleClose(IOService * client, IOOptionBits options) APPLE_KEXT_OVERRIDE;


    /*!
     * @function handleIsOpen
     * @abstract See <code>IOService::handleIsOpen</code> for more details.
     *
     * @param    client    Client service provider
     * @result   true if open, false otherwise
     *
     */
    virtual bool handleIsOpen(const IOService * client) const APPLE_KEXT_OVERRIDE;

public:

    
    /*!@typedef PowerSourceEventHandler
     *
     * @param target Reference supplied when the handler was registered.
     * @param eventType Type of the power source event
     * @param eventData Power source event value
     */

    typedef void (*PowerSourceEventHandler) (void * target, const OSSymbol * eventType, OSDictionary * eventData);

    /*!
     * @function open
     * @abstract Open  service to receive power source events
     *
     * @param    forClient   Client service
     * @param    handler       Client event callback
     * @param    options       presently unused
     * @result   true if  succeed, false otherwise
     *
     */
    virtual bool open (IOService *forClient, PowerSourceEventHandler handler, uint32_t options) APPLE_KEXT_OVERRIDE;

    /*!
     * @function start
     * @abstract See <code>IOService::start</code> for more details.
     *
     * @param    provider    Client service provider
     * @result   true if  succeed, false otherwise
     *
     */
    virtual bool start(IOService *provider) APPLE_KEXT_OVERRIDE;

    /*!
     * @function stop
     * @abstract See <code>IOService::stop</code> for more details.
     *
     * @param    provider    Client service provider
     *
     */
    virtual void stop(IOService *provider) APPLE_KEXT_OVERRIDE;

    /*!
     * @function free
     * @abstract Frees data structures associated with object
     *
     */
    virtual void free() APPLE_KEXT_OVERRIDE;
};
