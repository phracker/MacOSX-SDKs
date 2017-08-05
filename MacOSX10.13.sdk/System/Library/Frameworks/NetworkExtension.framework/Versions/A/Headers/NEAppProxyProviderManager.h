/*
 * Copyright (c) 2015 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NETunnelProviderManager.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @file NEAppProxyProviderManager
 * @discussion This file declares the NEAppProxyProviderManager API. The NEAppProxyProviderManager API is used to configure and control network tunnels provided by NEAppProxyProviders.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEAppProxyProviderManager
 * @discussion The NEAppProxyProviderManager class declares the programmatic interface for an object that is used to configure and control network tunnels provided by NEAppProxyProviders.
 *
 * Instances of this class are thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface NEAppProxyProviderManager : NETunnelProviderManager

/*!
 * @method loadAllFromPreferencesWithCompletionHandler:
 * @discussion This function asynchronously reads all of the NEAppProxy configurations associated with the calling app that have previously been saved to disk and returns them as NEAppProxyProviderManager objects.
 * @param completionHandler A block that takes an array NEAppProxyProviderManager objects. The array passed to the block may be empty if no NETunnelProvider configurations were successfully read from the disk.  The NSError passed to this block will be nil if the load operation succeeded, non-nil otherwise.
 */
+ (void)loadAllFromPreferencesWithCompletionHandler:(void (^)(NSArray<NEAppProxyProviderManager *> * __nullable managers, NSError * __nullable error))completionHandler NS_AVAILABLE(10_11, 9_0);

@end

NS_ASSUME_NONNULL_END

