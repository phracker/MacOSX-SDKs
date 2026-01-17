//
//  INMediaUserContext.h
//  Intents
//
//  Copyright (c) 2019 Apple Inc. All rights reserved.
//

#import <Intents/INUserContext.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, INMediaUserContextSubscriptionStatus) {
    /// The app does not offer subscriptions, or the subscription status is unavailable
    INMediaUserContextSubscriptionStatusUnknown = 0,
    /// The user is not a subscriber, but subscriptions are offered
    INMediaUserContextSubscriptionStatusNotSubscribed,
    /// The user is registered with a subscription (free, trial, or paid)
    INMediaUserContextSubscriptionStatusSubscribed
} API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0)) API_UNAVAILABLE(macos) NS_SWIFT_NAME(INMediaUserContext.SubscriptionStatus);

API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0)) API_UNAVAILABLE(macos)
@interface INMediaUserContext : INUserContext

- (instancetype)init;

/// Used as a signal of user affinity for the app
@property (readwrite, assign, NS_NONATOMIC_IOSONLY) INMediaUserContextSubscriptionStatus subscriptionStatus;
/// Approximate number of relevant items available in the user's library (playlists, songs, podcasts, albums, etc.) - used as a signal of user affinity for the app
@property (nullable, readwrite, copy, NS_NONATOMIC_IOSONLY) NSNumber *numberOfLibraryItems NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
