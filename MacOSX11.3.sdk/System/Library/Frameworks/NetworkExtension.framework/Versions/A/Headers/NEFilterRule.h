/*
 * Copyright (c) 2019 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NEFilterDataProvider.h>

@class NENetworkRule;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @interface NEFilterRule
 * @discussion The NEFilterRule class declares the programmatic interface of an object that defines a rule for matching network traffic and the action to take when the rule matches.
 */
API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED
@interface NEFilterRule : NSObject <NSSecureCoding,NSCopying>

/*!
 * @method initWithNetworkRule:action:
 * @discussion Initialize a newly-allocated NEFilterRule object
 * @param networkRule A NENetworkRule object that defines the network traffic characteristics that this rule matches.
 * @param action The action to take when this rule matches.
 */
- (instancetype)initWithNetworkRule:(NENetworkRule *)networkRule action:(NEFilterAction)action API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property matchNetworkRule
 * @discussion The NENetworkRule that defines the network traffic characteristics that this rule matches.
 */
@property (readonly, copy) NENetworkRule *networkRule API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

/*!
 * @property action
 * @discussion The action to take when this rule matches network traffic.
 */
@property (readonly) NEFilterAction action API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios, tvos) __WATCHOS_PROHIBITED;

@end


NS_ASSUME_NONNULL_END
