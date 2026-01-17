//
//  UNNotificationContent.h
//  UserNotifications
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UNNotificationAttachment;
@class UNNotificationSound;

NS_ASSUME_NONNULL_BEGIN

// Other system framework objects can conform to UNNotificationContentProviding to provide context relevant to the notification. Only objects that conform to UNNotificationContentProviding in the Apple SDK are allowed. The conformance will be ignored by other objects conforming to UNNotificationContentProviding. Do not conform objects to UNNotificationContentProviding.
API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0))
@protocol UNNotificationContentProviding <NSObject>
@end

typedef NS_ENUM(NSUInteger, UNNotificationInterruptionLevel) {
    // Added to the notification list; does not light up screen or play sound
    UNNotificationInterruptionLevelPassive,
    
    // Presented immediately; Lights up screen and may play a sound
    UNNotificationInterruptionLevelActive,
    
    // Presented immediately; Lights up screen and may play a sound; May be presented during Do Not Disturb
    UNNotificationInterruptionLevelTimeSensitive,
    
    // Presented immediately; Lights up screen and plays sound; Always presented during Do Not Disturb; Bypasses mute switch; Includes default critical alert sound if no sound provided
    UNNotificationInterruptionLevelCritical,

} API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNNotificationContent : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

// Optional array of attachments.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray <UNNotificationAttachment *> *attachments API_UNAVAILABLE(tvos);

// The application badge number.
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSNumber *badge;

// The body of the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *body API_UNAVAILABLE(tvos);

// The identifier for a registered UNNotificationCategory that will be used to determine the appropriate actions to display for the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *categoryIdentifier API_UNAVAILABLE(tvos);

// The launch image that will be used when the app is opened from the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *launchImageName API_UNAVAILABLE(macos, tvos);

// The sound that will be played for the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) UNNotificationSound *sound API_UNAVAILABLE(tvos);

// The subtitle of the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *subtitle API_UNAVAILABLE(tvos);

// The unique identifier for the thread or conversation related to this notification request. It will be used to visually group notifications together.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *threadIdentifier API_UNAVAILABLE(tvos);

// The title of the notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *title API_UNAVAILABLE(tvos);

// Apps can set the userInfo for locally scheduled notification requests. The contents of the push payload will be set as the userInfo for remote notifications.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSDictionary *userInfo API_UNAVAILABLE(tvos);

/// The argument to be inserted in the summary for this notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *summaryArgument API_DEPRECATED("summaryArgument is ignored", ios(12.0, 15.0), watchos(5.0, 8.0), tvos(12.0, 15.0));

/// A number that indicates how many items in the summary are represented in the summary.
/// For example if a podcast app sends one notification for 3 new episodes in a show,
/// the argument should be the name of the show and the count should be 3.
/// Default is 1 and cannot be 0.
@property (NS_NONATOMIC_IOSONLY, readonly, assign) NSUInteger summaryArgumentCount API_DEPRECATED("summaryArgumentCount is ignored", ios(12.0, 15.0), watchos(5.0, 8.0), tvos(12.0, 15.0));

// An identifier for the content of the notification used by the system to customize the scene to be activated when tapping on a notification.
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSString *targetContentIdentifier API_AVAILABLE(ios(13.0)); // default nil

// The interruption level determines the degree of interruption associated with the notification
@property (NS_NONATOMIC_IOSONLY, readonly, assign) UNNotificationInterruptionLevel interruptionLevel API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

// Relevance score determines the sorting for the notification across app notifications. The expected range is between 0.0f and 1.0f.
@property (NS_NONATOMIC_IOSONLY, readonly, assign) double relevanceScore API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

@property (NS_NONATOMIC_IOSONLY, readonly, copy, nullable) NSString *filterCriteria API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0)) API_UNAVAILABLE(tvos);

/**
 Contextualizes your UNNotificationContent object with other Apple SDK objects conforming to UNNotificationContentProviding. This will specialize the notification and decorate its look and behavior accordingly. For example, the notification will be treated as a message with an avatar and be promoted to the top of notification center if the object passed in is a valid INSendMessageIntent<UNNotificationContentProviding>. This throws an error with a UNErrorCode found in UNError.h if the UNNotificationContentProviding object is invalid. A valid UNNotificationContent result should not be mutated and be passed directly to UNUserNotificationCenter.

 This should be called in the UNNotificationServiceExtension in didReceiveNotificationRequest:withContentHandler: and the returned UNNotificationContent should be passed to the contentHandler for incoming push notifications.
 */
- (nullable UNNotificationContent *)contentByUpdatingWithProvider:(id<UNNotificationContentProviding>)provider error:(out NSError **)outError API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0)) NS_SWIFT_NAME(updating(from:));

@end

API_AVAILABLE(macos(10.14), ios(10.0), watchos(3.0), tvos(10.0))
@interface UNMutableNotificationContent : UNNotificationContent

// Optional array of attachments.
@property (NS_NONATOMIC_IOSONLY, readwrite, copy) NSArray <UNNotificationAttachment *> *attachments API_UNAVAILABLE(tvos);

// The application badge number. nil means no change. 0 to hide.
@property (NS_NONATOMIC_IOSONLY, readwrite, copy, nullable) NSNumber *badge;

// The body of the notification. Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
@property (NS_NONATOMIC_IOSONLY, readwrite, copy) NSString *body API_UNAVAILABLE(tvos);

// The identifier for a registered UNNotificationCategory that will be used to determine the appropriate actions to display for the notification.
@property (NS_NONATOMIC_IOSONLY, readwrite, copy) NSString *categoryIdentifier API_UNAVAILABLE(tvos);

// The launch image that will be used when the app is opened from the notification.
@property (NS_NONATOMIC_IOSONLY, readwrite, copy) NSString *launchImageName API_UNAVAILABLE(macos, tvos);

// The sound that will be played for the notification.
@property (NS_NONATOMIC_IOSONLY, readwrite, copy, nullable) UNNotificationSound *sound API_UNAVAILABLE(tvos);

// The subtitle of the notification. Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
@property (NS_NONATOMIC_IOSONLY, readwrite, copy) NSString *subtitle API_UNAVAILABLE(tvos);

// The unique identifier for the thread or conversation related to this notification request. It will be used to visually group notifications together.
@property (NS_NONATOMIC_IOSONLY, readwrite, copy) NSString *threadIdentifier API_UNAVAILABLE(tvos);

// The title of the notification. Use -[NSString localizedUserNotificationStringForKey:arguments:] to provide a string that will be localized at the time that the notification is presented.
@property (NS_NONATOMIC_IOSONLY, readwrite, copy) NSString *title API_UNAVAILABLE(tvos);

// Apps can set the userInfo for locally scheduled notification requests. The contents of the push payload will be set as the userInfo for remote notifications.
@property (NS_NONATOMIC_IOSONLY, readwrite, copy) NSDictionary *userInfo API_UNAVAILABLE(tvos);

/// The argument to be inserted in the summary for this notification.
@property (NS_NONATOMIC_IOSONLY, readwrite, copy) NSString *summaryArgument API_DEPRECATED("summaryArgument is ignored", ios(12.0, 15.0), watchos(5.0, 8.0), tvos(12.0, 15.0));

/// A number that indicates how many items in the summary are represented in the summary.
/// For example if a podcast app sends one notification for 3 new episodes in a show,
/// the argument should be the name of the show and the count should be 3.
/// Default is 1 and cannot be 0.
@property (NS_NONATOMIC_IOSONLY, readwrite, assign) NSUInteger summaryArgumentCount API_DEPRECATED("summaryArgumentCount is ignored", ios(12.0, 15.0), watchos(5.0, 8.0), tvos(12.0, 15.0));

// An identifier for the content of the notification used by the system to customize the scene to be activated when tapping on a notification.
@property (NS_NONATOMIC_IOSONLY, readwrite, copy, nullable) NSString *targetContentIdentifier API_AVAILABLE(ios(13.0)); // default nil

// The interruption level determines the degree of interruption associated with the notification
@property (NS_NONATOMIC_IOSONLY, readwrite, assign) UNNotificationInterruptionLevel interruptionLevel API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

// Relevance score determines the sorting for the notification across app notifications. The expected range is between 0.0f and 1.0f.
@property (NS_NONATOMIC_IOSONLY, readwrite, assign) double relevanceScore API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));

@property (NS_NONATOMIC_IOSONLY, readwrite, copy, nullable) NSString *filterCriteria API_AVAILABLE(macos(13.0), ios(16.0), watchos(9.0)); // default nil

@end

NS_ASSUME_NONNULL_END
