//
//  VZStorageDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZStorageDeviceAttachment;

/*!
 @abstract Base class for a storage device configuration.
 @discussion
    VZStorageDeviceConfiguration should not be instantiated directly.
    One of its subclasses like VZVirtioBlockDeviceConfiguration should be used instead.

 @see VZVirtioBlockDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZStorageDeviceConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract Storage device attachment. Defines what local resource is exposed to the virtual machine as a disk.
 @see VZDiskImageStorageDeviceAttachment
 */
@property (readonly, strong) VZStorageDeviceAttachment *attachment;

@end

NS_ASSUME_NONNULL_END
