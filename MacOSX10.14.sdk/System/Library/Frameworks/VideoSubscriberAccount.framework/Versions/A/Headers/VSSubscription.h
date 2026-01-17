//
//  VSSubscription.h
//  VideoSubscriberAccount
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <Foundation/NSObject.h>
#import <VideoSubscriberAccount/VideoSubscriberAccountDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSArray<ObjectType>;
@class NSDate;
@class NSString;

/// Describes the level of access to content.
typedef NS_ENUM(NSInteger, VSSubscriptionAccessLevel)
{
    VSSubscriptionAccessLevelUnknown,/// The default access level.
    VSSubscriptionAccessLevelFreeWithAccount, /// The customer has access to content that is offered for free to users with a valid account.  This value corresponds content in your availability feed with the "account" offering type.
    VSSubscriptionAccessLevelPaid, /// The customer also has access to content that is offered as part of a paid subscription.  The value corresponds content in your availability feed with the "subscription" offering type.
}
#if TARGET_OS_IPHONE
API_AVAILABLE(ios(11.0), tvos(11.0));
#else
;
#endif // TARGET_OS_IPHONE

/// A VSSubscription instance describes the extent to which a subscriber has
/// access to content.
#if TARGET_OS_IPHONE
VS_EXPORT API_AVAILABLE(ios(11.0), tvos(11.0))
#else
VS_EXPORT
#endif // #if TARGET_OS_IPHONE
@interface VSSubscription : NSObject

/// After this point in time, the subscription will be considered inactive.
///
/// If the current subscription becomes inactive, the system will behave as
/// though the user is not subscribed at all, i.e. as though the registration
/// center's current subscription had been set to nil.
///
/// Defaults to distantFuture.
///
/// Providing a value is useful in a limited number of scenarios, e.g. when the
/// a subscriber decides not to renew their subscription, you should provide an
/// expiration date that corresponds to the point in time when the final billing
/// cycle will end.
///
/// This might also be useful if the subscription only grants access to content
/// that is time-limited, e.g. a single season of games for a sports league.
@property (nonatomic, copy, null_resettable) NSDate *expirationDate;

/// Describes the level of access the subscriber has to your catalog of content.
///
/// It is an error to provide a subscription with an unknown access level as
/// the current subscription.  Instead, choose the access level that describes
/// the content that the subscriber can play.
@property (nonatomic, assign) VSSubscriptionAccessLevel accessLevel;

/// Identifies a subset of content from your catalog that subscriber can play.
///
/// Only provide values that are used in your availability feed's tier restrictions.
@property (nonatomic, copy, null_resettable) NSArray<NSString *> *tierIdentifiers;

/// Identifies the billing group associated with the subscription.  May be used,
/// for example, to restrict content availability based on the proximity of the
/// billing address to a specific venue.
@property (nonatomic, copy, nullable) NSString *billingIdentifier
#if TARGET_OS_IPHONE
API_AVAILABLE(ios(11.3), tvos(11.3));
#else
;
#endif // TARGET_OS_IPHONE

@end

NS_ASSUME_NONNULL_END
