//
//  VZGenericPlatformConfiguration.h
//  Virtualization
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Virtualization/VZPlatformConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract The platform configuration for a generic Intel or ARM virtual machine.
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZGenericPlatformConfiguration : VZPlatformConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
