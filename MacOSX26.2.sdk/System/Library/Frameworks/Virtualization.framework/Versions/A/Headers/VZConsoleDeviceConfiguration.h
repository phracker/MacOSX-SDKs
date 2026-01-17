//
//  VZConsoleDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for a console device configuration.
 @discussion
    VZConsoleDeviceConfiguration should not be instantiated directly.
    One of its subclasses like VZVirtioConsoleDeviceConfiguration should be used instead.

 @see VZVirtioConsoleDeviceConfiguration
*/
VZ_EXPORT API_AVAILABLE(macos(13.0))
@interface VZConsoleDeviceConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
