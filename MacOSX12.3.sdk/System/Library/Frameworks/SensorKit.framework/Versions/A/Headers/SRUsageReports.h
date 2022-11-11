//
//  SRUsageReports.h
//  SensorKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <SensorKit/SRDeviceUsageCategories.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SRApplicationUsage;
@class SRNotificationUsage;
@class SRWebUsage;

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRDeviceUsageReport : NSObject

/// The duration of this report
@property (readonly) NSTimeInterval duration;

/// Usage time of applications per category
///
/// @discussion category is the primary genre from the app's iTunesMetadata.plist.
///
@property (readonly, copy) NSDictionary<SRDeviceUsageCategoryKey, NSArray<SRApplicationUsage *> *> *applicationUsageByCategory;

/// Usage time of notifications per category
///
/// @discussion category is the primary genre from the notifying app's iTunesMetadata.plist.
///
@property (readonly, copy) NSDictionary<SRDeviceUsageCategoryKey, NSArray<SRNotificationUsage *> *> *notificationUsageByCategory;

/// Usage time of web domains per category
///
/// @discussion category based on the primary Screen Time category of the web domain
///
@property (readonly, copy) NSDictionary<SRDeviceUsageCategoryKey, NSArray<SRWebUsage *> *> *webUsageByCategory;

/// Total number of screen wakes over this duration
@property (readonly) NSInteger totalScreenWakes;

/// Total number of unlocks over this duration
@property (readonly) NSInteger totalUnlocks;

/// Total amount of time the device was unlocked over this duration
@property (readonly) NSTimeInterval totalUnlockDuration;

@end

typedef NS_ENUM(NSInteger, SRTextInputSessionType) {
    SRTextInputSessionTypeKeyboard = 1,
    SRTextInputSessionTypeThirdPartyKeyboard,
    SRTextInputSessionTypePencil,
    SRTextInputSessionTypeDictation,
} API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos);

SR_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRTextInputSession : NSObject

@property (readonly) NSTimeInterval duration;

@property (readonly) SRTextInputSessionType sessionType;

@end

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRApplicationUsage : NSObject

/// The bundle identifier of the app in use. Only populated for Apple apps.
@property (readonly, copy, nullable) NSString *bundleIdentifier;

/// The amount of time the app is used
@property (readonly) NSTimeInterval usageTime;

/*!
 * @property reportApplicationIdentifier
 *
 * @brief An application identifier that is valid for the duration of the report.
 *
 * @discussion This is useful for identifying distinct application uses within the same
 * report duration without revealing the actual application identifier.
 */
@property (readonly, copy) NSString *reportApplicationIdentifier API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos);

/*!
 * @property textInputSessions
 *
 * @brief
 * The text input session types that occurred during this application usage
 *
 * @discussion
 * The list of text input sessions describes the order and type of text input that may
 * have occured during an application usage. Multiple sessions of the same text input
 * type will appear as separate array entries. If no text input occurred, this array
 * will be empty.
 */
@property (readonly, copy) NSArray<SRTextInputSession *> *textInputSessions API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos);

@end

typedef NS_ENUM(NSInteger, SRNotificationEvent) {
    SRNotificationEventUnknown,
    SRNotificationEventReceived,
    SRNotificationEventDefaultAction,
    SRNotificationEventSupplementaryAction,
    SRNotificationEventClear,
    SRNotificationEventNotificationCenterClearAll,
    SRNotificationEventRemoved,
    SRNotificationEventHide,
    SRNotificationEventLongLook,
    SRNotificationEventSilence,
    SRNotificationEventAppLaunch,
    SRNotificationEventExpired,
    SRNotificationEventBannerPulldown,
    SRNotificationEventTapCoalesce,
    SRNotificationEventDeduped,
    SRNotificationEventDeviceActivated,
    SRNotificationEventDeviceUnlocked,
} API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos);

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRNotificationUsage : NSObject

/// The bundle identifier of the application that corresponds to the notification. Only populated for Apple apps.
@property (readonly, copy, nullable) NSString *bundleIdentifier;

@property (readonly) SRNotificationEvent event;

@end

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRWebUsage : NSObject
@property (readonly) NSTimeInterval totalUsageTime;
@end

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRMessagesUsageReport : NSObject

@property (readonly) NSTimeInterval duration;
@property (readonly) NSInteger totalOutgoingMessages;
@property (readonly) NSInteger totalIncomingMessages;
@property (readonly) NSInteger totalUniqueContacts;

@end

SR_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos, macos)
@interface SRPhoneUsageReport : NSObject

@property (readonly) NSTimeInterval duration;
@property (readonly) NSInteger totalOutgoingCalls;
@property (readonly) NSInteger totalIncomingCalls;
@property (readonly) NSInteger totalUniqueContacts;
@property (readonly) NSTimeInterval totalPhoneCallDuration;

@end

NS_ASSUME_NONNULL_END
