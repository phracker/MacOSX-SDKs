//
//  VZGenericPlatformConfiguration.h
//  Virtualization
//
//  Copyright © 2021-2024 Apple Inc. All rights reserved.
//

#import <Virtualization/VZPlatformConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class VZGenericMachineIdentifier;

/*!
 @abstract The platform configuration for a generic Intel or ARM virtual machine.
 @discussion
    When a virtual machine is saved to disk then loaded again, the `machineIdentifier`
    must be restored to the original value.

    If multiple virtual machines are created from the same configuration, each should have a unique `machineIdentifier`.
*/
VZ_EXPORT API_AVAILABLE(macos(12.0))
@interface VZGenericPlatformConfiguration : VZPlatformConfiguration

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/*!
 @abstract The unique machine identifier.
 @discussion
    Running two virtual machines concurrently with the same identifier results in undefined behavior
    in the guest operating system. When restoring a virtual machine from saved state, this
    `machineIdentifier` must match the `machineIdentifier` of the saved virtual machine.
 */
@property (copy) VZGenericMachineIdentifier *machineIdentifier API_AVAILABLE(macos(13.0));

/*!
 @abstract Indicate whether or not nested virtualization is available.
 @discussion
    Nested virtualization is only available on some hardware and software configurations. It may also be disabled by policy.

    Use this property to check if support is available for the platform. If nested virtualization is supported,
    use `nestedVirtualizationEnabled` to enable the feature.
 @see nestedVirtualizationEnabled.
 */
@property (class, readonly, getter=isNestedVirtualizationSupported) BOOL nestedVirtualizationSupported API_AVAILABLE(macos(15.0));

/*!
 @abstract Enable nested virtualization for the platform.
 @discussion
    If nested virtualization is available, enable it for the current platform configuration.

    You can use `nestedVirtualizationSupported` to discover the nested virtualization availability before enabling it.

    The default value is NO, nested virtualization is disabled.
 @see nestedVirtualizationSupported.
 */
@property (readwrite, getter=isNestedVirtualizationEnabled) BOOL nestedVirtualizationEnabled API_AVAILABLE(macos(15.0));

@end

NS_ASSUME_NONNULL_END
