//
//  VZNetworkDeviceConfiguration.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VZMACAddress;
@class VZNetworkDeviceAttachment;

/*!
 @abstract Base class for a network adapter configuration.
 @discussion
    VZNetworkDeviceConfiguration should not be instantiated directly.
    One of its subclasses like VZVirtioNetworkDeviceConfiguration should be used instead.

 @see VZVirtioNetworkDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZNetworkDeviceConfiguration : NSObject <NSCopying>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*!
 @abstract The media access control address of the device. The default is a random, locally administered, unicast address.
 */
@property (readwrite, copy) VZMACAddress *MACAddress;

/*!
 @abstract Network device attachment. Defines how the virtual device interfaces with the host system. The default is nil.
 @see VZBridgedNetworkDeviceAttachment
 @see VZFileHandleNetworkDeviceAttachment
 @see VZNATNetworkDeviceAttachment
 */
@property (readwrite, nullable, strong) VZNetworkDeviceAttachment *attachment;

@end

NS_ASSUME_NONNULL_END
