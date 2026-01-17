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
    CKSubscriptionTypeQuery                                     = 1,
    CKSubscriptionTypeRecordZone                                = 2,
    CKSubscriptionTypeDatabase NS_ENUM_AVAILABLE(10_12, 10_0)   = 3,
} NS_ENUM_AVAILABLE(10_10, 8_0) __WATCHOS_PROHIBITED;

@class CKNotificationInfo, CKRecordZoneID;

NS_CLASS_AVAILABLE(10_10, 8_0) __WATCHOS_PROHIBITED
@interface CKSubscription : NSObject <NSSecureCoding, NSCopying>

- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, readonly, copy) NSString *subscriptionID;
@property (nonatomic, readonly, assign) CKSubscriptionType subscriptionType;

/* Optional property describing the notification that will be sent when the subscription fires. */
@property (nonatomic, copy, nullable) CKNotificationInfo *notificationInfo;

@end


typedef NS_OPTIONS(NSUInteger, CKQuerySubscriptionOptions) {
    CKQuerySubscriptionOptionsFiresOnRecordCreation     = 1 << 0,
    CKQuerySubscriptionOptionsFiresOnRecordUpdate       = 1 << 1,
    CKQuerySubscriptionOptionsFiresOnRecordDeletion     = 1 << 2,
    CKQuerySubscriptionOptionsFiresOnce                 = 1 << 3,
} NS_ENUM_AVAILABLE(10_12, 10_0) __WATCHOS_PROHIBITED;

/* A subscription that fires whenever a change matching the predicate occurs.
 CKQuerySubscriptions are not supported in a sharedCloudDatabase */
NS_CLASS_AVAILABLE(10_12, 10_0) __WATCHOS_PROHIBITED
@interface CKQuerySubscription : CKSubscription <NSSecureCoding, NSCopying>

- (instancetype)initWithRecordType:(NSString *)recordType predicate:(NSPredicate *)predicate options:(CKQuerySubscriptionOptions)querySubscriptionOptions;
- (instancetype)initWithRecordType:(NSString *)recordType predicate:(NSPredicate *)predicate subscriptionID:(NSString *)subscriptionID options:(CKQuerySubscriptionOptions)querySubscriptionOptions NS_DESIGNATED_INITIALIZER;

/* The record type that this subscription watches */
@property (nonatomic, readonly, copy) NSString *recordType;

/* A predicate that determines when the subscription fires. */
@property (nonatomic, readonly, copy) NSPredicate *predicate;

/* Optional property.  If set, a query subscription is scoped to only record changes in the indicated zone. */
@property (nonatomic, copy, nullable) CKRecordZoneID *zoneID;

/* Options flags describing the firing behavior subscription. One of
 CKQuerySubscriptionOptionsFiresOnRecordCreation,
 CKQuerySubscriptionOptionsFiresOnRecordUpdate, or
 CKQuerySubscriptionOptionsFiresOnRecordDeletion must be specified or an
 NSInvalidArgumentException will be thrown. */
@property (nonatomic, readonly, assign) CKQuerySubscriptionOptions querySubscriptionOptions;

@end


/* A subscription that fires whenever any change happens in the indicated Record Zone.
 The RecordZone must have the capability CKRecordZoneCapabilityFetchChanges
 CKRecordZoneSubscriptions are not supported in a sharedCloudDatabase */
NS_CLASS_AVAILABLE(10_12, 10_0) __WATCHOS_PROHIBITED
@interface CKRecordZoneSubscription : CKSubscription <NSSecureCoding, NSCopying>

- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID;
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID subscriptionID:(NSString *)subscriptionID NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, copy) CKRecordZoneID *zoneID;

/* Optional property. If set, a zone subscription is scoped to record changes for this record type */
@property (nonatomic, copy, nullable) NSString *recordType;

@end


/* This subscription fires whenever any change happens in the database that this subscription was saved in.
   CKDatabaseSubscription is only supported in the Private and Shared databases. */
NS_CLASS_AVAILABLE(10_12, 10_0) __WATCHOS_PROHIBITED
@interface CKDatabaseSubscription : CKSubscription <NSSecureCoding, NSCopying>

- (instancetype)init;
- (instancetype)initWithSubscriptionID:(NSString *)subscriptionID NS_DESIGNATED_INITIALIZER;

/* Optional property. If set, a database subscription is scoped to record changes for this record type */
@property (nonatomic, copy, nullable) NSString *recordType;

@end


/* The payload of a push notification delivered in the UIApplication application:didReceiveRemoteNotification: delegate method contains information about the firing subscription.   Use
   +[CKNotification notificationFromRemoteNotificationDictionary:] to parse that payload.
 
   On tvOS, alerts, badges, sounds, and categories are not handled in push notifications. However,
   CKSubscriptions remain available to help you avoid polling the servers */

NS_CLASS_AVAILABLE(10_10, 8_0) __WATCHOS_PROHIBITED
@interface CKNotificationInfo : NSObject <NSSecureCoding, NSCopying>

/* Optional alert string to display in a push notification. */
@property (nonatomic, copy, nullable) NSString *alertBody __TVOS_PROHIBITED;

/* Instead of a raw alert string, you may optionally specify a key for a localized string in your app's Localizable.strings file. */
@property (nonatomic, copy, nullable) NSString *alertLocalizationKey __TVOS_PROHIBITED;

/* A list of field names to take from the matching record that is used as substitution variables in a formatted alert string. */
@property (nonatomic, copy, nullable) NSArray<NSString *> *alertLocalizationArgs __TVOS_PROHIBITED;

/* A key for a localized string to be used as the alert action in a modal style notification. */
@property (nonatomic, copy, nullable) NSString *alertActionLocalizationKey __TVOS_PROHIBITED;

/* The name of an image in your app bundle to be used as the launch image when launching in response to the notification. */
@property (nonatomic, copy, nullable) NSString *alertLaunchImage __TVOS_PROHIBITED;

/* The name of a sound file in your app bundle to play upon receiving the notification. */
@property (nonatomic, copy, nullable) NSString *soundName __TVOS_PROHIBITED;

/* A list of keys from the matching record to include in the notification payload.
 Only some keys are allowed.  The value types associated with those keys on the server must be one of these classes:
     CKReference
     CLLocation
     NSDate
     NSNumber
     NSString */
@property (nonatomic, copy, nullable) NSArray<NSString *> *desiredKeys;

/* Indicates that the notification should increment the app's badge count. Default value is NO. */
@property (nonatomic, assign) BOOL shouldBadge __TVOS_AVAILABLE(10_0);

/* Indicates that the notification should be sent with the "content-available" flag to allow for background downloads in the application. 
   Default value is NO. */
@property (nonatomic, assign) BOOL shouldSendContentAvailable;

/* Optional property for the category to be sent with the push when this subscription fires. Categories allow you to present custom actions to the user on your push notifications. See UIMutableUserNotificationCategory for more information. */
@property (nonatomic, copy, nullable) NSString *category NS_AVAILABLE(10_11, 9_0) __TVOS_PROHIBITED;

@end

#pragma mark - Deprecated CKSubscription

/* Replaced with CKQuerySubscriptionOptions */
typedef NS_OPTIONS(NSUInteger, CKSubscriptionOptions) {
    CKSubscriptionOptionsFiresOnRecordCreation     = 1 << 0,
    CKSubscriptionOptionsFiresOnRecordUpdate       = 1 << 1,
    CKSubscriptionOptionsFiresOnRecordDeletion     = 1 << 2,
    CKSubscriptionOptionsFiresOnce                 = 1 << 3,
} NS_ENUM_DEPRECATED(10_10, 10_12, 8_0, 10_0, "Use CKQuerySubscriptionOptions instead") __WATCHOS_PROHIBITED;

@interface CKSubscription (CKSubscriptionDeprecated)

- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DEPRECATED(10_10, 10_12, 8_0, 10_0, "Init the appropriate CKSubscription subclass");

/* Replaced with CKQuerySubscription */
- (instancetype)initWithRecordType:(NSString *)recordType predicate:(NSPredicate *)predicate options:(CKSubscriptionOptions)subscriptionOptions NS_DEPRECATED(10_10, 10_12, 8_0, 10_0, "Use CKQuerySubscription instead");
- (instancetype)initWithRecordType:(NSString *)recordType predicate:(NSPredicate *)predicate subscriptionID:(NSString *)subscriptionID options:(CKSubscriptionOptions)subscriptionOptions NS_DEPRECATED(10_10, 10_12, 8_0, 10_0, "Use CKQuerySubscription instead");
@property (nonatomic, readonly, copy, nullable) NSString *recordType NS_DEPRECATED(10_10, 10_12, 8_0, 10_0, "Use CKQuerySubscription instead");
@property (nonatomic, readonly, copy, nullable) NSPredicate *predicate NS_DEPRECATED(10_10, 10_12, 8_0, 10_0, "Use CKQuerySubscription instead");

/* Replaced with CKQuerySubscriptionOptions */
@property (nonatomic, readonly, assign) CKSubscriptionOptions subscriptionOptions NS_DEPRECATED(10_10, 10_12, 8_0, 10_0, "Use CKQuerySubscriptionOptions instead");

/* Replaced with CKRecordZoneSubscription */
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID options:(CKSubscriptionOptions)subscriptionOptions NS_DEPRECATED(10_10, 10_12, 8_0, 10_0, "Use CKRecordZoneSubscription instead");
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID subscriptionID:(NSString *)subscriptionID options:(CKSubscriptionOptions)subscriptionOptions NS_DEPRECATED(10_10, 10_12, 8_0, 10_0, "Use CKRecordZoneSubscription instead");
@property (nonatomic, copy, nullable) CKRecordZoneID *zoneID NS_DEPRECATED(10_10, 10_12, 8_0, 10_0, "Use CKRecordZoneSubscription instead");

@end


NS_ASSUME_NONNULL_END
