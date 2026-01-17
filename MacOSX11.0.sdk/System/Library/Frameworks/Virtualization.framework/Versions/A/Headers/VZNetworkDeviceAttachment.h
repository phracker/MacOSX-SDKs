//
//  VZNetworkDeviceAttachment.h
//  Virtualization
//
//  Copyright © 2019-2020 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Base class for a network device attachment.
 @discussion
    A network device attachment defines how a virtual network device interfaces with the host system.

    VZNetworkDeviceAttachment should not be instantiated directly. One of its subclasses should be used instead.

    Common attachment types include:
    - VZNATNetworkDeviceAttachment
    - VZFileHandleNetworkDeviceAttachment

 @see VZBridgedNetworkDeviceAttachment
 @see VZFileHandleNetworkDeviceAttachment
 @see VZNATNetworkDeviceAttachment
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZNetworkDeviceAttachment : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
