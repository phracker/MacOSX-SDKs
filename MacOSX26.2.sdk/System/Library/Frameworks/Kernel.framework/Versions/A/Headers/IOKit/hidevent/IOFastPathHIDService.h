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

#ifndef IO_FASTPATH_HIDSERVICE_H
#define IO_FASTPATH_HIDSERVICE_H

#include <IOKit/IOService.h>
#include <IOKit/hidevent/IOFastPathService.h>
#include <IOKit/hidevent/IOHIDEventService.h>

class IOHIDElement;
class IOHIDElementPrivate;
class IOHIDTimeSyncService;


/// Abstract base class for an IOFastPath service which generates samples from HID events.
///
/// Each `IOFastPathHIDService` is a client of an `IOHIDEventService`. It implements features common
/// to all HID-based fast path services including open/close of the provider and the plumbing for
/// subclasses to receive HID events.
///
/// Subclasses must override the superclass method `createDescriptor` to define the fast path
/// descriptor for a given service instance. Subclasses must also override `handleEvent` to
/// implement the HID event to fast path sample transform.
///
class IOFastPathHIDService : public IOFastPathService
{
    OSDeclareAbstractStructors(IOFastPathHIDService);
    using super = IOFastPathService;
    
public:
    
    /// Start the service. See IOKit/IOService.h for more info.
    virtual bool start(IOService * provider) override;
    
    /// Notification that the provider will terminate. See IOKit/IOService.h for more info.
    virtual bool willTerminate(IOService * provider, IOOptionBits options) override;
    
protected:
    
    /// Handle a HID event dispatched by the event service.
    ///
    /// Subclasses must override this method to implement the HID event to fast path sample
    /// transform for the service.
    ///
    /// @param  sender
    ///     Event service which dispatched the event.
    ///
    /// @param  context
    ///     Context argument provided at provider open. Always `nullptr`.
    ///
    /// @param  event
    ///     The dispatched event.
    ///
    /// @param  options
    ///     Event options.
    ///
    virtual void handleEvent(IOHIDEventService * sender, void * context, IOHIDEvent * event, IOOptionBits options) = 0;
    
    /// Get a reference to the provider event service.
    OSPtr<IOHIDEventService> copyService() const;

    /// Get the object used to hold the current sample data.
    OSPtr<OSData> copySample() const;

    /// Convert a local (mach absolute time) timestamp to the time-sync representation.
    ///
    /// This method must be called with the workloop gate held, and asserts if this condition is not
    /// met.
    ///
    /// @param  timestamp
    ///     Timestamp to convert, in mach absolute time.
    ///
    /// @param  outTime
    ///     Output storage for result. Caller takes ownership and is responsible for freeing the
    ///     object on success.
    ///
    /// @return
    ///     - `kIOReturnSuccess` on success
    ///     - `kIOReturnNotReady` if the time sync service has not been published
    ///     - `kIOReturnOffline` if the driver or time sync service has terminated
    ///     - Other return codes are propagated from the underlying time sync service.
    ///
    IOReturn doTimeSyncForLocalTimeGated(UInt64 timestamp, OSData ** outTime);

    /// Checks a HID event for a child event containing a time-sync'ed timestamp and, if present, returns its value.
    ///
    /// @param  event
    ///     HID event.
    ///
    /// @return
    ///     Mach absolute timestamp associated with the event, or 0 if there is none.
    ///
    UInt64 getSyncedTimestampForHIDEvent(IOHIDEvent * event);

private:

    void cleanupHelper();

    OSPtr<IOHIDEventService> _service;
    OSPtr<OSData> _sample;
};


/// IOFastPath service which generates samples from accelerometer HID events.
///
/// The service supports the following sample keys:
///   - `kIOFastPathFieldKeyTimestamp`
///   - `kIOFastPathFieldKeySampleTimestamp`
///   - `kIOFastPathFieldKeySampleID`
///   - `kIOFastPathFieldKeyAccelX`
///   - `kIOFastPathFieldKeyAccelY`
///   - `kIOFastPathFieldKeyAccelZ`
///
class IOFastPathHIDAccelService : public IOFastPathHIDService
{
    OSDeclareDefaultStructors(IOFastPathHIDAccelService);
    using super = IOFastPathHIDService;

public:

    /// Start the service. See IOKit/IOService.h for more info.
    virtual bool start(IOService * provider) override;

protected:

    virtual bool isProducer() const override { return true; }

    /// Create the service's fast path descriptor.
    ///
    virtual OSPtr<IOFastPathDescriptor> createDescriptor() override;

    /// Handle a HID event dispatched by the event service. If the event is an accelerometer event,
    /// enqueue a sample with the event data.
    ///
    virtual void handleEvent(IOHIDEventService * sender, void * context, IOHIDEvent * event, IOOptionBits options) override;

private:

    void handleAccelerometerEvent(IOHIDEvent * event);

    struct __attribute__((packed)) QueueEntry {
        UInt64 eventTimestamp;
        UInt64 sampleTimestamp;
        UInt64 sampleID;
        double x;
        double y;
        double z;
    };

    UInt64 generation; ///< counter used to generate sample IDs
};


/// IOFastPath service which generates samples from gyro HID events.
///
/// The service supports the following sample keys:
///   - `kIOFastPathFieldKeyTimestamp`
///   - `kIOFastPathFieldKeySampleTimestamp`
///   - `kIOFastPathFieldKeySampleID`
///   - `kIOFastPathFieldKeyGyroX`
///   - `kIOFastPathFieldKeyGyroY`
///   - `kIOFastPathFieldKeyGyroZ`
///
class IOFastPathHIDGyroService : public IOFastPathHIDService
{
    OSDeclareDefaultStructors(IOFastPathHIDGyroService);
    using super = IOFastPathHIDService;

public:

    /// Start the service. See IOKit/IOService.h for more info.
    virtual bool start(IOService * provider) override;

protected:

    virtual bool isProducer() const override { return true; }

    /// Create the service's fast path descriptor.
    ///
    virtual OSPtr<IOFastPathDescriptor> createDescriptor() override;

    /// Handle a HID event dispatched by the event service. If the event is an gyro event, enqueue
    /// a sample with the event data.
    ///
    virtual void handleEvent(IOHIDEventService * sender, void * context, IOHIDEvent * event, IOOptionBits options) override;

private:

    void handleGyroEvent(IOHIDEvent * event);

    struct __attribute__((packed)) QueueEntry {
        UInt64 eventTimestamp;
        UInt64 sampleTimestamp;
        UInt64 sampleID;
        double x;
        double y;
        double z;
    };

    UInt64 generation; ///< counter used to generate sample IDs
};

#if APPLE_FEATURE_P192

/// IOFastPath service which generates button samples.
///
class IOFastPathHIDButtonService : public IOFastPathHIDService
{
    OSDeclareDefaultStructors(IOFastPathHIDButtonService);
    using super = IOFastPathHIDService;

public:

    /// Start the service. See IOKit/IOService.h for more info.
    virtual bool start(IOService * provider) override;

protected:

    virtual bool isProducer() const override { return true; }

    /// Create the service's fast path descriptor.
    ///
    virtual OSPtr<IOFastPathDescriptor> createDescriptor() override;

    /// Handle a HID event dispatched by the event service. If the event is a button event, enqueue
    /// a sample with the event data.
    ///
    virtual void handleEvent(IOHIDEventService * sender, void * context, IOHIDEvent * event, IOOptionBits options) override;

private:

    struct __attribute__((packed)) QueueEntry {
        UInt64 timestamp;
        UInt64 number;
        UInt64 state;
        double pressure;
        double force;
    };

    void parseSampleFromHIDEvent(IOHIDEvent * event, QueueEntry * sample);
    void handleButtonEvent(IOHIDEvent * event);
    double getButtonForce(IOHIDEvent * event) const;
};

#endif


/// IOFastPath service which controls HID device LEDs.
///
/// The service supports the following sample keys:
///   - `kIOFastPathFieldKeySampleTimestamp`
///   - `kIOFastPathFieldKeyLEDMode`
///   - `kIOFastPathFieldKeyLEDBlinkDuration`
///   - `kIOFastPathFieldKeyLEDBlinkPeriod`
///   - `kIOFastPathFieldKeyLEDIntensity`
///
class IOFastPathHIDLEDService : public IOFastPathHIDService
{
    OSDeclareDefaultStructors(IOFastPathHIDLEDService);
    using super = IOFastPathHIDService;

public:
    
    /// Probe the provider service. See IOKit/IOService.h for more info.
    virtual IOService * probe(IOService * provider, SInt32 * score) override;

    /// Start the service. See IOKit/IOService.h for more info.
    virtual bool start(IOService * provider) override;

    /// See IOKit/IOService.h for more info.
    virtual void stop(IOService * provider) override;

    /// See IOKit/IOService.h for more info.
    virtual bool handleOpen(IOService * forClient, IOOptionBits options, void * arg) override;

    /// See IOKit/IOService.h for more info.
    virtual void handleClose(IOService * forClient, IOOptionBits options) override;

protected:

    virtual bool isProducer() const override { return false; }

    /// Create the service's fast path descriptor.
    ///
    virtual OSPtr<IOFastPathDescriptor> createDescriptor() override;

    /// Handle a HID event dispatched by the event service. If the event is an gyro event, enqueue
    /// a sample with the event data.
    ///
    virtual void handleEvent(IOHIDEventService * sender, void * context, IOHIDEvent * event, IOOptionBits options) override;

    /// Timer event source callback. Checks the circular queue for new LED control values and
    /// applies them to the device.
    ///
    virtual void timerCallback(IOTimerEventSource * sender);

private:

    struct QueueEntry {
        UInt64 timestamp;
        UInt64 mode;
        UInt64 intensity;
        UInt64 blinkDuration;
        UInt64 blinkPeriod;
    };

    struct LEDState {
        bool on;
        bool off;
        bool blink;
        UInt8 intensity;
        UInt16 blinkOnTime;
        UInt16 blinkOffTime;
        UInt64 pulseMidpoint; // mach absolute time
    
        bool operator==(const LEDState &other) const {
            return (on == other.on && off == other.off && blink == other.blink && intensity == other.intensity && blinkOnTime == other.blinkOnTime && blinkOffTime == other.blinkOffTime && pulseMidpoint == other.pulseMidpoint);
        }

        bool operator!=(const LEDState &other) const {
            return !(*this == other);
        }
    };

    /// Parse the HID report elements published by the provider.
    ///
    /// This method is called from `probe` to validate the report elements published by a matched
    /// provider. If all required elements to control an LED constellation are present, this method
    /// returns `true` and initializes the driver's internal state. Otherwise, it returns `false`.
    ///
    bool parseElements(OSArray * elements);

    /// Check if an element matches a set of parameters and, if so, save a refernce to it. Returns
    /// `true` if the element matches, `false` otherwise. If matching, `storage` will contain
    /// `element` upon return. The reference count is not incremented.
    ///
    bool parseElement(IOHIDElementPrivate * element,
                      UInt32 page,
                      UInt32 usage,
                      IOHIDElementType type,
                      UInt32 bits,
                      IOHIDElementPrivate ** storage);

    /// Parse LED state values from an entry in the data queue.
    ///
    LEDState parseStateFromQueueEntry(QueueEntry * entry) const;

    /// Returns `true` if an LED state update is needed.
    ///
    bool stateUpdateNeeded(LEDState newState);

    /// Update the LED state on the device via a set report.
    ///
    void updateLEDState(LEDState newState);

    UInt32 getTimerPeriodUS() const;

    OSPtr<IOHIDDevice> _device;
    OSPtr<IOTimerEventSource> _timer;
    LEDState _ledState;
    IOHIDElementPrivate * _modeOn;
    IOHIDElementPrivate * _modeOff;
    IOHIDElementPrivate * _modeBlink;
    IOHIDElementPrivate * _blinkOnTime;
    IOHIDElementPrivate * _blinkOffTime;
    IOHIDElementPrivate * _intensity;
    IOHIDElementPrivate * _ts;

    UInt64 emptyQueueTimerCnt;
    bool dequeuedSample;
};

#endif /* IO_FASTPATH_HIDSERVICE_H */
