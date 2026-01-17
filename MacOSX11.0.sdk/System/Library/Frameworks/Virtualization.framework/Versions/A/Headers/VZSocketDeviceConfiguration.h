//
//  VZSocketDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for a socket device configuration.
 @discussion
    VZNetworkDeviceConfiguration should not be instantiated directly.
    One of its subclasses like VZVirtioSocketDeviceConfiguration should be used instead.

 @see VZVirtioSocketDeviceConfiguration
*/
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZSocketDeviceConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
