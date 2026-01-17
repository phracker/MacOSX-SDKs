//
//  VZLinuxRosettaCachingOptions.h
//  Virtualization
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

#ifdef __arm64__

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for a VZLinuxRosettaCachingOptions.
 @discussion
    VZLinuxRosettaCachingOptions define the communication mechanism between the Rosetta daemon and the Rosetta runtime.

    VZLinuxRosettaCachingOptions should not be instantiated directly.
    One of its subclasses like VZLinuxRosettaUnixSocketCachingOptions or VZLinuxRosettaAbstractCachingOptions should be used instead.

 @see VZLinuxRosettaUnixSocketCachingOptions
 @see VZLinuxRosettaAbstractCachingOptions
 */
VZ_EXPORT API_AVAILABLE(macos(14.0))
NS_REFINED_FOR_SWIFT
@interface VZLinuxRosettaCachingOptions : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif
