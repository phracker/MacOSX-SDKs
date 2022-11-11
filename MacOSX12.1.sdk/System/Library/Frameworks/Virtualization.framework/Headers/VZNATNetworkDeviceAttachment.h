//
//  VZNATNetworkDeviceAttachment.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZNetworkDeviceAttachment.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Network device attachment using network address translation (NAT) with outside networks.
 @discussion
    Using the NAT attachment type, the host serves as router and performs network address translation for accesses to outside networks.

 @see VZNetworkDeviceConfiguration
 @see VZVirtioNetworkDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZNATNetworkDeviceAttachment : VZNetworkDeviceAttachment

- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
