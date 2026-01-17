//
//  VZXHCIControllerConfiguration.h
//  Virtualization
//
//  Copyright © 2023-2024 Apple Inc. All rights reserved.
//

#import <Virtualization/VZUSBControllerConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Configuration for the USB XHCI controller.
 @discussion This configuration creates a USB XHCI controller device for the guest.
 */
VZ_EXPORT API_AVAILABLE(macos(15.0))
@interface VZXHCIControllerConfiguration : VZUSBControllerConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
