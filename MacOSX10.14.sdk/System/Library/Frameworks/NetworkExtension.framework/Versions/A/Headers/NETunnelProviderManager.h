/*
 * Copyright (c) 2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEVPNManager.h>
#import <NetworkExtension/NETunnelProvider.h>

NS_ASSUME_NONNULL_BEGIN

@class NEAppRule;

/*!
 * @file NETunnelProviderManager
 * @discussion This file declares the NETunnelProviderManager API. The NETunnelProviderManager API is used to configure and control network tunnels provided by NETunnelProviders.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NETunnelProviderManager
 * @discussion The NETunnelProviderManager class declares the programmatic interface for an object that is used to configure and control network tunnels provided by NETunnelProviders.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos)
@interface NETunnelProviderManager : NEVPNManager

/*!
 * @method loadAllFromPreferencesWithCompletionHandler:
 * @discussion This function asynchronously reads all of the NETunnelProvider configurations created by the calling app that have previously been saved to disk and returns them as NETunnelProviderManager objects.
 * @param completionHandler A block that takes an array NETunnelProviderManager objects. The array passed to the block may be empty if no NETunnelProvider configurations were successfully read from the disk.  The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
+ (void)loadAllFromPreferencesWithCompletionHandler:(void (^)(NSArray<NETunnelProviderManager *> * __nullable managers, NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @method copyAppRules
 * @discussion This function returns an array of NEAppRule objects.
 */
- (nullable NSArray<NEAppRule *> *)copyAppRules API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

/*!
 * @property routingMethod
 * @discussion The method by which network traffic is routed to the tunnel. The default is NETunnelProviderRoutingMethodDestinationIP.
 */
@property (readonly) NETunnelProviderRoutingMethod routingMethod API_AVAILABLE(macos(10.11), ios(9.0)) API_UNAVAILABLE(watchos, tvos);

@end

NS_ASSUME_NONNULL_END

