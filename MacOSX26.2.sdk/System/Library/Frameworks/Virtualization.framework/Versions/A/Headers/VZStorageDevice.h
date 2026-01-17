//
//  VZStorageDevice.h
//  Virtualization
//
//  Copyright © 2023-2024 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Class representing a storage device in a virtual machine.
 @discussion
    VZStorageDevice should not be instantiated directly.
    One of its subclasses like VZUSBMassStorageDevice should be used instead.
 @see VZUSBMassStorageDevice
 */
VZ_EXPORT API_AVAILABLE(macos(15.0))
@interface VZStorageDevice : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
