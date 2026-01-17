//
//  CKNotification.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CKRecordID, CKRecordZoneID;

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKNotificationID : NSObject <NSCopying, NSSecureCoding>
@end

typedef NS_ENUM(NSInteger, CKNotificationType) {
    CKNotificationTypeQuery            = 1,
    CKNotificationTypeRecordZone       = 2,
    CKNotificationTypeReadNotification = 3, /* Indicates a notification that a client had previously marked as read. */
} NS_ENUM_AVAILABLE(10_10, 8_0);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKNotification : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)notificationFromRemoteNotificationDictionary:(NSDictionary *)notificationDictionary;

/* When you instantiate a CKNotification from a remote notification dictionary, you will get back a concrete
 subclass defined below.  Use the type of notification to avoid -isKindOfClass: checks */
@property (nonatomic, readonly, assign) CKNotificationType notificationType;

@property (nonatomic, readonly, copy) CKNotificationID *notificationID;

@property (nonatomic, readonly, copy) NSString *containerIdentifier;

/* push notifications have a limited size.  In some cases, CloudKit servers may not be able to send you a full
 CKNotification's worth of info in one push.  In those cases, isPruned returns YES.  The order in which we'll
 drop properties is defined in each CKNotification subclass below.
 The CKNotification can be obtained in full via a CKFetchNotificationChangesOperation */
@property (nonatomic, readonly, assign) BOOL isPruned;


/* These keys are parsed out of the 'aps' payload from a remote notification dictionary */

/* Optional alert string to display in a push notification. */
@property (nonatomic, readonly, copy) NSString *alertBody;
/* Instead of a raw alert string, you may optionally specify a key for a localized string in your app's Localizable.strings file. */
@property (nonatomic, readonly, copy) NSString *alertLocalizationKey;
/* A list of field names to take from the matching record that is used as substitution variables in a formatted alert string. */
@property (nonatomic, readonly, copy) NSArray /* NSString */ *alertLocalizationArgs;
/* A key for a localized string to be used as the alert action in a modal style notification. */
@property (nonatomic, readonly, copy) NSString *alertActionLocalizationKey;
/* The name of an image in your app bundle to be used as the launch image when launching in response to the notification. */
@property (nonatomic, readonly, copy) NSString *alertLaunchImage;

/* The number to display as the badge of the application icon */
@property (nonatomic, readonly, copy) NSNumber *badge;
/* The name of a sound file in your app bundle to play upon receiving the notification. */
@property (nonatomic, readonly, copy) NSString *soundName;

@end

/* notificationType == CKNotificationTypeQuery
 When properties must be dropped (see isPruned), here's the order of importance.  The most important properties are first,
 they'll be the last ones to be dropped.
 - notificationID
 - badge
 - alertLocalizationKey
 - alertLocalizationArgs
 - alertBody
 - alertActionLocalizationKey
 - alertLaunchImage
 - soundName
 - desiredKeys
 - queryNotificationReason
 - recordID
 - containerIdentifier
 */

typedef NS_ENUM(NSInteger, CKQueryNotificationReason) {
    CKQueryNotificationReasonRecordCreated = 1,
    CKQueryNotificationReasonRecordUpdated,
    CKQueryNotificationReasonRecordDeleted,
} NS_ENUM_AVAILABLE(10_10, 8_0);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKQueryNotification : CKNotification

@property (nonatomic, readonly, assign) CKQueryNotificationReason queryNotificationReason;

/* A set of key->value pairs for creates and updates.  You request the server fill out this property via the
 "desiredKeys" property of CKNotificationInfo */
@property (nonatomic, readonly, copy) NSDictionary *recordFields;

@property (nonatomic, readonly, copy) CKRecordID *recordID;

/* If YES, this record is in the public database.  Else, it's in the private database */
@property (nonatomic, readonly, assign) BOOL isPublicDatabase;

@end


/* notificationType == CKNotificationTypeRecordZone
 When properties must be dropped (see isPruned), here's the order of importance.  The most important properties are first,
 they'll be the last ones to be dropped.
 - notificationID
 - badge
 - alertLocalizationKey
 - alertLocalizationArgs
 - alertBody
 - alertActionLocalizationKey
 - alertLaunchImage
 - soundName
 - recordZoneID
 - containerIdentifier
 */

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKRecordZoneNotification : CKNotification

@property (nonatomic, readonly, copy) CKRecordZoneID *recordZoneID;

@end
