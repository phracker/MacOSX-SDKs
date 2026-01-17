//
//  VZBridgedNetworkInterface.h
//  Virtualization
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Virtualization/VZDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract Define a network interface that bridges a physical interface with a virtual machine.
 @discussion
    A bridged interface is shared between the virtual machine and the host system. Both host and virtual machine send and receive packets on the same physical interface
    but have distinct network layers.

    VZBridgedNetworkInterface cannot be instantiated directly. A list of supported network interfaces can be obtained using +[VZBridgedNetworkInterface networkInterfaces].

    The VZBridgedNetworkInterface can be used with a VZBridgedNetworkDeviceAttachment to set up a network device VZNetworkDeviceConfiguration.

    @seealso VZBridgedNetworkDeviceAttachment
    @seealso VZNATNetworkDeviceAttachment
    @seealso VZNetworkDeviceConfiguration
 */
VZ_EXPORT API_AVAILABLE(macos(11.0))
@interface VZBridgedNetworkInterface : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/*! @abstract Return the list of network interfaces available for bridging. */
@property (class, readonly, copy) NSArray<VZBridgedNetworkInterface *> *networkInterfaces;

/*! @abstract Return the unique identifier for this interface. The identifier is the BSD name associated with the interface (e.g. "en0"). */
@property (readonly, copy) NSString *identifier;

/*! @abstract Return a display name if available (e.g. "Ethernet"). */
@property (readonly, copy, nullable) NSString *localizedDisplayName;

@end

NS_ASSUME_NONNULL_END
