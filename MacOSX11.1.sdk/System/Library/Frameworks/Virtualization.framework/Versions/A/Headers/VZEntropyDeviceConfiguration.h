//
//  VZEntropyDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for an entropy device configuration.
 @discussion
    VZEntropyDeviceConfiguration should not be instantiated directly.
    The subclass VZVirtioEntropyDeviceConfiguration should be used instead.

 @see VZVirtioEntropyDeviceConfiguration
*/
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZEntropyDeviceConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
