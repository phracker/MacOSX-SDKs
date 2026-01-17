//
//  VSSubscriptionRegistrationCenter.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class VSSubscription;

/// VSSubscriptionRegistrationCenter stores subscription information.
#if TARGET_OS_IPHONE
VS_EXPORT API_AVAILABLE(ios(11.0), tvos(11.0))
#else
VS_EXPORT
#endif // #if TARGET_OS_IPHONE
@interface VSSubscriptionRegistrationCenter : NSObject

/// Use the default subscription registration center to tell the system about
/// the customer's ability to access content within your app.
+ (VSSubscriptionRegistrationCenter *)defaultSubscriptionRegistrationCenter;

/// Provide a subscription when the subscriber first authenticates, and when the
/// subscription changes.
///
/// When the subscriber signs out or otherwise loses access to subscription
/// content, invoke this method with nil.
///
/// You might also want to call this method opportunistically, if you happen to
/// have just confirmed the validity of the subscription, or in response to app
/// lifecycle events, e.g. when your app becomes active.  The system may use
/// this activity as a hint that the user is actively using the subscription.
///
/// It is an error to provide a current subscription with an unknown access
/// level; you should not provide a subscription if the user only has access to
/// content that is offered for free without any account requirements.
- (void)setCurrentSubscription:(nullable VSSubscription *)currentSubscription;

@end

NS_ASSUME_NONNULL_END
