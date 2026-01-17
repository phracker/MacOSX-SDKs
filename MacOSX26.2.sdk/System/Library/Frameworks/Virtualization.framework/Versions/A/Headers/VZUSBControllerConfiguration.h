//
//  VZUSBControllerConfiguration.h
//  Virtualization
//
//  Copyright © 2023-2024 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@protocol VZUSBDeviceConfiguration;

/*!
 @abstract Base class for a USB Controller configuration.
 @discussion
    VZUSBControllerConfiguration should not be instantiated directly.
    One of its subclasses like VZXHCIControllerConfiguration should be used instead.
 @see VZXHCIControllerConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(15.0))
@interface VZUSBControllerConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract List of USB devices. Empty by default.
 @discussion
    This list represents a set of USB devices that virtual machine will start with.
    For each entry in this list, there will be a corresponding runtime object created in VZUSBController.usbDevices property.
 @see VZUSBController
 @see VZUSBDeviceConfiguration
 @see VZUSBMassStorageDeviceConfiguration
 */
@property (readwrite, copy) NSArray<id <VZUSBDeviceConfiguration>> *usbDevices;

@end

NS_ASSUME_NONNULL_END
