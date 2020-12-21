//
//  VZMemoryBalloonDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for a memory balloon device configuration.
 @discussion
    VZMemoryBalloonDeviceConfiguration should not be instantiated directly.
    One of its subclasses like VZVirtioTraditionalMemoryBalloonDeviceConfiguration should be used instead.

 @see VZVirtioTraditionalMemoryBalloonDeviceConfiguration
*/
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZMemoryBalloonDeviceConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
