//
//  VZGraphicsDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2023 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZGraphicsDeviceConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
