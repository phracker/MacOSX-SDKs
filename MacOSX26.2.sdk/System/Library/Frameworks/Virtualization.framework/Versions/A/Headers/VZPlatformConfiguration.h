//
//  VZPlatformConfiguration.h
//  Virtualization
//
//  Copyright © 2021-2024 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for a platform configuration.
 @discussion
    VZPlatformConfiguration should not be instantiated directly.
    One of its subclasses should be used instead.

 @see VZGenericPlatformConfiguration
 @see VZMacPlatformConfiguration.
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZPlatformConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
