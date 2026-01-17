/*
 * Copyright (C) 2022 Apple Inc. All rights reserved.
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
#include <IOKit/hid/IOHIDDeviceTypes.h>

class IOHIDInterface;

class IOHIDPowerSourceClient;

/*! @class IOHIDTranslationService
    @abstract Class manage translation of HIDElement value to  dictionary representation  in accordance to spec provided with value of "Events" property.
    Value "Events" property is  dictionary with  "key" represent event type and "value"  represent event description.  See example in info.plist
 */
class IOHIDTranslationService: public IOService
{
    OSDeclareDefaultStructors(IOHIDTranslationService)
 
    struct IOHIDTranslationService_ivar;
    IOHIDTranslationService_ivar * ivar;

    /*!
     * @function handleInterruptReport
     * @abstract callback to receive  interrupt reports update.
     *
     * @param    timeStamp    report timestamp
     * @param    report    memory descriptor that represent the HID report
     * @param    reportType    report type
     * @param    reportID    report ID
     */
    void handleInterruptReport (AbsoluteTime timeStamp, IOMemoryDescriptor * report, IOHIDReportType reportType, UInt32 reportID);
    
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
     * @function createReporters
     * @abstract Initialize IOReport support
     *
     * @result   true if success , false is otherwise
     */
    bool createReporters();

    /*!
     * @function configureReport
     * @abstract See  <code>IOService::configureReport</code> for more details
     *
     * @param    channels    channels
     * @param    action    action
     * @param    result    result
     * @param    destination    destination
     * @result   kIOReturnSuccess  if success , error  otherwise
      */
    IOReturn  configureReport(IOReportChannelList   *channels,
                              IOReportConfigureAction action,
                              void                  *result,
                              void                  *destination) APPLE_KEXT_OVERRIDE;

    /*!
     * @function updateReport
     * @abstract See  <code>IOService::updateReport</code> for more details
     *
     * @param    channels    channels
     * @param    action    action
     * @param    result    result
     * @param    destination    destination
     * @result   kIOReturnSuccess  if success , error  otherwise
     */
    IOReturn updateReport(IOReportChannelList       *channels,
                          IOReportUpdateAction      action,
                          void                      *result,
                          void                      *destination) APPLE_KEXT_OVERRIDE;

    /*!
     * @function logEvent
     * @abstract debug facility to log event
     *
     * @param    eventValue    event value
     */
    void logEvent (OSDictionary * eventValue);
 
    /*!
     * @function copyEventCallback
     * @abstract timer callback callback to manage event copy processing
     *
     */

    void copyEventCallback();
 
protected:
    
 
    /*!
     * @function handleEvent
     * @abstract dispatch event to all clients
     *
     * @param    eventValue    event value
     */

    virtual void handleEvent (OSDictionary * eventValue);

    
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

    static const OSSymbol *EventTypeKey;
    
    /*!@typedef PowerSourceEventHandler
     *
     * @param target Reference supplied when the handler was registered.
     * @param eventValue dictionary the represent translated event
     */

    typedef void (*EventHandler) (void * target, OSDictionary * eventValue);

    /*!
     * @function open
     * @abstract Open  service to receive power source events
     *
     * @param    forClient   Client service
     * @param    handler       Client  event callback
     * @param    options    presently unused
     * @result   Dictionary with event data on NULL
     *
     */
    virtual bool open (IOService *forClient, EventHandler handler, uint32_t options);

   
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

    /*!
     * @function finalize
     * @abstract See <code>IOService::finalize</code> for more details.
     *
     * @param    options    options
     *
     */

    virtual bool finalize(IOOptionBits options) APPLE_KEXT_OVERRIDE;

    /*!@typedef EventBlock
     *
     * @param events Array of events or empty array if no events available.
     */

    typedef  void (^EventBlock)(OSArray * events);

    /*!
     * @function copyEvents
     * @abstract Copy  events
     *
     * @param    eventType   Event Type or null (to get copy of all available events)
     * @param    eventBlock Block will be called with  OSArray of  OSDictionary that  represent event
     * @result   kIOReturnSuccess or error  if issue occur while requesting copy event. Note eventBlock will not be called if copyEvents return error.
     *
     */
    virtual IOReturn copyEvents (const OSSymbol * eventType,  EventBlock eventBlock);
  
};
