/*
 * Copyright (c) 2019 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEVPNManager.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NETransparentProxyManager.h
 * @discussion This file declares the NETransparentProxyManager API. The NETransparentProxyManager API is used to configure and control transparent proxies provided by NEAppProxyProviders.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NETransparentProxyManager
 * @discussion The NETransparentProxyManager class declares the programmatic interface for an object that is used to configure and control transparent proxies provided by NEAppProxyProviders.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED
@interface NETransparentProxyManager : NEVPNManager

/*!
 * @method loadAllFromPreferencesWithCompletionHandler:
 * @discussion This function asynchronously reads all of the transparent proxy configurations associated with the calling app that have previously been saved to disk and returns them as NETransparentProxyManager objects.
 * @param completionHandler A block that takes an array NETransparentProxyManager objects. The array passed to the block may be empty if no transparent proxy configurations were successfully read from the disk.  The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
+ (void)loadAllFromPreferencesWithCompletionHandler:(void (^)(NSArray<NETransparentProxyManager *> * __nullable managers, NSError * __nullable error))completionHandler API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

@end

NS_ASSUME_NONNULL_END
