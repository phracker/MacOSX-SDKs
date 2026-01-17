//
//  VZGraphicsDisplayConfiguration.h
//  Virtualization
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for a graphics display configuration.
 @discussion
    VZGraphicsDisplayConfiguration should not be instantiated directly.
    One of its subclasses should be used instead.

 @see VZMacGraphicsDisplayConfiguration
 @see VZVirtioGraphicsScanoutConfiguration
*/
VZ_EXPORT API_AVAILABLE(macos(14.0))
@interface VZGraphicsDisplayConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
