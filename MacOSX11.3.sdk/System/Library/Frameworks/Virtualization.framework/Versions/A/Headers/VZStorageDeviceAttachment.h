//
//  VZStorageDeviceAttachment.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for a storage device attachment.
 @discussion
    A storage device attachment defines how a virtual machine storage device interfaces with the host system.

    VZStorageDeviceAttachment should not be instantiated directly.
    One of its subclasses like VZDiskImageStorageDeviceAttachment should be used instead.

 @see VZDiskImageStorageDeviceAttachment
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZStorageDeviceAttachment : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
