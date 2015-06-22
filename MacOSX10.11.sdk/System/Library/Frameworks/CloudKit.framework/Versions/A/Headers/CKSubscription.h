//
//  CKSubscription.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDefines.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CKSubscriptionType) {
    CKSubscriptionTypeQuery      = 1,
    CKSubscriptionTypeRecordZone = 2,
} NS_ENUM_AVAILABLE(10_10, 8_0);

typedef NS_OPTIONS(NSUInteger, CKSubscriptionOptions) {
    CKSubscriptionOptionsFiresOnRecordCreation     = 1 << 0, // Applies to CKSubscriptionTypeQuery
    CKSubscriptionOptionsFiresOnRecordUpdate       = 1 << 1, // Applies to CKSubscriptionTypeQuery
    CKSubscriptionOptionsFiresOnRecordDeletion     = 1 << 2, // Applies to CKSubscriptionTypeQuery
    CKSubscriptionOptionsFiresOnce                 = 1 << 3, // Applies to CKSubscriptionTypeQuery
} NS_ENUM_AVAILABLE(10_10, 8_0);

@class CKNotificationInfo, CKRecordZoneID;

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKSubscription : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithRecordType:(NSString *)recordType predicate:(NSPredicate *)predicate options:(CKSubscriptionOptions)subscriptionOptions;

- (instancetype)initWithRecordType:(NSString *)recordType predicate:(NSPredicate *)predicate subscriptionID:(NSString *)subscriptionID options:(CKSubscriptionOptions)subscriptionOptions NS_DESIGNATED_INITIALIZER;

/* This subscription fires whenever any change happens in the indicated RecordZone.
 The RecordZone must have the capability CKRecordZoneCapabilityFetchChanges */
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID options:(CKSubscriptionOptions)subscriptionOptions;
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID subscriptionID:(NSString *)subscriptionID options:(CKSubscriptionOptions)subscriptionOptions NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, copy) NSString *subscriptionID;

@property (nonatomic, readonly, assign) CKSubscriptionType subscriptionType;

/* The record type that this subscription watches. This property is only used by query subscriptions, and must be set. */
@property (nonatomic, readonly, copy, nullable) NSString *recordType;

/* A predicate that determines when the subscription fires. This property is only used by query subscriptions, and must be set */
@property (nonatomic, readonly, copy, nullable) NSPredicate *predicate;

/* Options flags describing the firing behavior subscription. For query subscriptions, one of CKSubscriptionOptionsFiresOnRecordCreation, CKSubscriptionOptionsFiresOnRecordUpdate, or CKSubscriptionOptionsFiresOnRecordDeletion must be specified or an NSInvalidArgumentException will be thrown. */
@property (nonatomic, readonly, assign) CKSubscriptionOptions subscriptionOptions;

/* Optional property describing the notification that will be sent when the subscription fires. */
@property (nonatomic, copy, nullable) CKNotificationInfo *notificationInfo;

/* Query subscriptions: Optional property.  If set, a query subscription is scoped to only record changes in the indicated zone.
   RecordZone subscriptions: */
@property (nonatomic, copy, nullable) CKRecordZoneID *zoneID;

@end

/* The payload of a push notification delivered in the UIApplication application:didReceiveRemoteNotification: delegate method contains information about the firing subscription.   Use
   +[CKNotification notificationFromRemoteNotificationDictionary:] to parse that payload. */

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKNotificationInfo : NSObject <NSSecureCoding, NSCopying>

/* Optional alert string to display in a push notification. */
@property (nonatomic, copy, nullable) NSString *alertBody;

/* Instead of a raw alert string, you may optionally specify a key for a localized string in your app's Localizable.strings file. */
@property (nonatomic, copy, nullable) NSString *alertLocalizationKey;

/* A list of field names to take from the matching record that is used as substitution variables in a formatted alert string. */
@property (nonatomic, copy, nullable) NSArray <NSString *> *alertLocalizationArgs;

/* A key for a localized string to be used as the alert action in a modal style notification. */
@property (nonatomic, copy, nullable) NSString *alertActionLocalizationKey;

/* The name of an image in your app bundle to be used as the launch image when launching in response to the notification. */
@property (nonatomic, copy, nullable) NSString *alertLaunchImage;

/* The name of a sound file in your app bundle to play upon receiving the notification. */
@property (nonatomic, copy, nullable) NSString *soundName;

/* A list of keys from the matching record to include in the notification payload.
 Only some keys are allowed.  The value types associated with those keys on the server must be one of these classes:
     CKReference
     CLLocation
     NSDate
     NSNumber
     NSString */
@property (nonatomic, copy, nullable) NSArray <NSString *> *desiredKeys;

/* Indicates that the notification should increment the app's badge count. Default value is NO. */
@property (nonatomic, assign) BOOL shouldBadge;

/* Indicates that the notification should be sent with the "content-available" flag to allow for background downloads in the application. 
   Default value is NO. */
@property (nonatomic, assign) BOOL shouldSendContentAvailable;

/* Optional property for the category to be sent with the push when this subscription fires. Categories allow you to present custom actions to the user on your push notifications. See UIMutableUserNotificationCategory for more information. */
@property (nonatomic, copy, nullable) NSString *category NS_AVAILABLE(10_11, 9_0);

@end
NS_ASSUME_NONNULL_END
