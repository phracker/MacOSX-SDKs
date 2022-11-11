//
//  AXHearingUtilities.h
//  Accessibility
//
//  Copyright © 2020 Apple. All rights reserved.
//

#import <Accessibility/AXFoundation.h>

NS_ASSUME_NONNULL_BEGIN

#ifdef __swift__
// This struct is not available in Objective-C. Its only purpose is to create a namespace for accessibility symbols in Swift.
typedef struct AXMFiHearingDevice { void *_reserved; } AXMFiHearingDevice;
#endif

typedef NS_OPTIONS(NSUInteger, AXHearingDeviceEar) {
    AXHearingDeviceEarNone    = 0,
    AXHearingDeviceEarLeft    = 1 << 1,
    AXHearingDeviceEarRight   = 1 << 2,
    AXHearingDeviceEarBoth    = AXHearingDeviceEarLeft | AXHearingDeviceEarRight,
} API_AVAILABLE(ios(15.0), watchos(8.0)) API_UNAVAILABLE(tvos, macos) NS_SWIFT_NAME(AXMFiHearingDevice.Ear);

AX_EXTERN AXHearingDeviceEar AXMFiHearingDeviceStreamingEar(void) API_AVAILABLE(ios(15.0), watchos(8.0)) API_UNAVAILABLE(tvos, macos) NS_SWIFT_NAME(AXMFiHearingDevice.streamingEar());

AX_EXTERN NSNotificationName const AXMFiHearingDeviceStreamingEarDidChangeNotification API_AVAILABLE(ios(15.0), watchos(8.0)) API_UNAVAILABLE(tvos, macos) NS_SWIFT_NAME(AXMFiHearingDevice.streamingEarDidChangeNotification);

AX_EXTERN BOOL AXSupportsBidirectionalAXMFiHearingDeviceStreaming(void) API_AVAILABLE(ios(15.0), watchos(8.0)) API_UNAVAILABLE(tvos, macos) NS_SWIFT_NAME(AXMFiHearingDevice.supportsBidirectionalStreaming());

/*
 Returns the CoreBluetooth UUIDs of the hearing device CBPeripherals. This requires that the value of the "com.apple.developer.hearing-aid-app" entitlement match the manufacturer of the CBPeripherals. For bimodal hearing devices the entitlement should be an array of the manufacturers.
 */
AX_EXTERN NSArray<NSUUID *> * AXMFiHearingDevicePairedUUIDs(void) API_AVAILABLE(ios(15.0), watchos(8.0)) API_UNAVAILABLE(tvos, macos)  NS_SWIFT_NAME(AXMFiHearingDevice.pairedDeviceIdentifiers());
AX_EXTERN NSNotificationName const AXMFiHearingDevicePairedUUIDsDidChangeNotification API_AVAILABLE(ios(15.0), watchos(8.0)) API_UNAVAILABLE(tvos, macos)  NS_SWIFT_NAME(AXMFiHearingDevice.pairedUUIDsDidChangeNotification);

NS_ASSUME_NONNULL_END

