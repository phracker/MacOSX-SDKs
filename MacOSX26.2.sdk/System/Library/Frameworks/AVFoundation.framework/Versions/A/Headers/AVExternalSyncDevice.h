#if !__has_include(<AVFCapture/AVExternalSyncDevice.h>)
/*
	File:  AVExternalSyncDevice.h

	Framework:  AVFoundation
 
	Copyright 2024-2025 Apple, Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <Foundation/Foundation.h>
#import <CoreMedia/CMSync.h>

NS_ASSUME_NONNULL_BEGIN

/// Connection state of an external sync device
typedef NS_ENUM( NSInteger, AVExternalSyncDeviceStatus ) {
    /// Indicates that external sync signal is not connected, or has transitioned to a state that is not recoverable.
    AVExternalSyncDeviceStatusUnavailable  = 0,
    /// Indicates that a device supporting external sync is connected, but calibration has not started.
    AVExternalSyncDeviceStatusReady        = 1,
    /// Indicates that the external sync signal is connected and that the AVExternalSyncDevice object is calibrating to follow.
    AVExternalSyncDeviceStatusCalibrating  = 2,
    /// Indicates that the ``AVExternalSyncDevice`` object is running and that the clock property on ``AVExternalSyncDevice`` is calibrated to the external sync signal.
    AVExternalSyncDeviceStatusActiveSync   = 3,
    /// Indicates that the AVExternalSyncDevice was calibrated to follow the external sync, but the sync signal has been lost. The camera will continue to match the last signal it received, but sync is not guaranteed.
    AVExternalSyncDeviceStatusFreeRunSync  = 4,
} API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos);

/// An external sync device connected to a host device that can be used to drive the timing of an internal component, such as a camera sensor.
///
/// Each instance of ``AVExternalSyncDevice`` corresponds to a physical external device that can drive an internal component, like a camera readout. You cannot create instances of ``AVExternalSyncDevice``. Instead, you obtain an array of all currently available external sync devices using ``AVExternalSyncDeviceDiscoverySession``.
API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@interface AVExternalSyncDevice : NSObject

AV_INIT_UNAVAILABLE

/// The status of the externally connected device.
///
/// Use this property to query the current connection status of the external sync device. This property is key-value observable.
@property(nonatomic, readonly) AVExternalSyncDeviceStatus status;

/// A clock representing the source of time from the external sync device.
///
/// This property returns `NULL` until the ``status`` reaches ``AVExternalSyncDeviceStatusActiveSync``.
@property(nonatomic, readonly, nullable) __attribute__((NSObject)) CMClockRef clock;

/// Delay to wait before starting the frame capture.
///
/// An external sync is generally used to configure multiple devices in the real world. A display and a camera may receive a signal at the same time, but that does not mean the refresh of the display and camera are aligned in a way that does not cause tearing in the recording. The signal compensation delay can be used to offset the readout of a camera on an intra-frame scale.
///
/// - Important: You should always set this property to a value less than the frame duration at which the camera is operating.
@property(nonatomic) CMTime signalCompensationDelay;

/// A unique identifier for an external sync device.
///
/// Use this property to select a specific external sync device.
@property(nonatomic, readonly) NSUUID *uuid;

/// The USB vendor identifier associated with the external sync device.
///
/// This `UInt32` value is provided by the hardware vendor, and returns 0 if not available.
@property(nonatomic, readonly) UInt32 vendorID;

/// The USB product identifier associated with the external sync device.
///
/// This `UInt32` value comes from the hardware vendor, and returns 0 if not available. Use this value in conjunction with the ``vendorID`` to determine a specific product.
@property(nonatomic, readonly) UInt32 productID;

@end

/// A means of discovering and monitoring connection / disconnection of external sync devices to the host.
///
/// ``AVExternalSyncDeviceDiscoverySession`` is a singleton that lists the external sync devices connected to the host. The client is expected to key-value observe the ``AVExternalSyncDeviceDiscoverySession/devices`` property for changes to the external sync devices list.
API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
NS_SWIFT_NAME(AVExternalSyncDevice.DiscoverySession)
@interface AVExternalSyncDeviceDiscoverySession : NSObject

AV_INIT_UNAVAILABLE

/// The singleton instance of the external sync source device discovery session.
///
/// Access the one and only external sync device discovery session on this host device using this method. ``sharedSession`` returns `nil` if the host device doesn't support external sync devices.
@property(class, readonly, nullable) AVExternalSyncDeviceDiscoverySession *sharedSession;

/// Whether external sync devices are supported by this device.
///
/// A value of `true` indicates that external sync devices are supported while `false` indicates they are not.
@property(class, readonly, getter=isSupported) BOOL supported;

/// An array of external sync devices connected to this host.
///
/// The list is updated when external sync devices are connected to the host and they remain in the list until they become unavailable. This property is key-value observable.
@property(readonly) NSArray<AVExternalSyncDevice *> *devices;

@end

/// Defines an interface for delegates of ``AVCaptureDeviceInput`` to respond to events that occur when connecting, calibrating, and disconnecting external sync devices.
API_AVAILABLE(macos(26.0), ios(26.0), macCatalyst(26.0), tvos(26.0)) API_UNAVAILABLE(visionos) API_UNAVAILABLE(watchos)
@protocol AVExternalSyncDeviceDelegate <NSObject>

@optional
/// Informs your delegate when the external sync device status has changed.
- (void)externalSyncDeviceStatusDidChange:(AVExternalSyncDevice *)device;

// Informs your delegate when the external sync device has encountered an error.
- (void)externalSyncDevice:(AVExternalSyncDevice *)device failedWithError:(nullable NSError *)error;

@end

NS_ASSUME_NONNULL_END

#else
#import <AVFCapture/AVExternalSyncDevice.h>
#endif
