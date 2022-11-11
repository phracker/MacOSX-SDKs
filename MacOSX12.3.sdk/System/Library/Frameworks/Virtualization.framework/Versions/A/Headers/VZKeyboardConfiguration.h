//
//  VZKeyboardConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for a keyboard configuration.
 @discussion
    VZKeyboardConfiguration should not be instantiated directly.
    One of its subclasses like VZUSBKeyboardConfiguration should be used instead.

 @see VZUSBKeyboardConfiguration
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZKeyboardConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
