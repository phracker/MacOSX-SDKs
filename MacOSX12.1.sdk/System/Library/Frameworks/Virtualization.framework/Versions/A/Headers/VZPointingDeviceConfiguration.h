//
//  VZPointingDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for a pointing device configuration.
 @discussion
    VZPointingDeviceConfiguration should not be instantiated directly.
    One of its subclasses like VZUSBScreenCoordinatePointingDeviceConfiguration should be used instead.

 @see VZUSBScreenCoordinatePointingDeviceConfiguration
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZPointingDeviceConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
