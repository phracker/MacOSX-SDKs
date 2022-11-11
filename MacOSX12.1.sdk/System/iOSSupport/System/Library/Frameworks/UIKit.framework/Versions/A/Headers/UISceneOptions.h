#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneOptions.h>)
//
//  UISceneOptions.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class UIScene, UIOpenURLContext, UNNotificationResponse, UIApplicationShortcutItem, CKShareMetadata, UIEventAttribution;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - UISceneConnectionOptions
// This object is vended to your application by UIKit when a UIScene connects to a session
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) NS_SWIFT_UI_ACTOR
@interface UISceneConnectionOptions : NSObject
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

// A set of UIOpenURLContexts to handle on connection
@property (nonatomic, readonly, copy) NSSet<UIOpenURLContext *> *URLContexts;

// A NSString containing the bundle ID of the originating application.
// non-nil if the originating application and this application share the same team identifier.
@property (nullable, nonatomic, readonly) NSString *sourceApplication;

// The type of a handoff user activity if one is pending on connect.
// The delegate callbacks will be invoked for this activity when it is available. 
@property (nullable, nonatomic, readonly) NSString *handoffUserActivityType;

// A set of available user activities to handle on connection.
// For handoff, the user activity is not immediately available and will not be in this set,
// a handoff user activity will instead be indicated via the handoffUserActivityType property
// above, and the application will receive a callback on their UISceneDelegate when the activity is fully loaded.
@property (nonatomic, readonly, copy) NSSet<NSUserActivity *> *userActivities;

// A notification response to handle on connection
@property (nullable, nonatomic, readonly) UNNotificationResponse *notificationResponse API_UNAVAILABLE(tvos);

// A shortcut item to handle on connection
@property (nullable, nonatomic, readonly) UIApplicationShortcutItem *shortcutItem API_UNAVAILABLE(tvos);

// A CloudKit share metadata item to handle on connection
@property (nullable, nonatomic, readonly) CKShareMetadata *cloudKitShareMetadata;
@end

#pragma mark - UISceneOpenURLOptions
// This object is vended to your application's UISceneDelegate when it is asked to open a URL
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) NS_SWIFT_UI_ACTOR
@interface UISceneOpenURLOptions : NSObject
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

// A NSString containing the bundle ID of the originating application.
// non-nil if the originating application and this application share the same team identifier.
@property (nullable, nonatomic, readonly) NSString *sourceApplication;

// A property-list typed object corresponding to what the originating application passed in UIDocumentInteractionController's annotation property
@property (nullable, nonatomic, readonly) id annotation;

// Copy the file before use if this value is NO
@property (nonatomic, readonly) BOOL openInPlace;

// An event attribution associated with the URL to open.
@property (nullable, nonatomic, readonly) UIEventAttribution *eventAttribution API_AVAILABLE(ios(14.5)) API_UNAVAILABLE(watchos, tvos);
@end

#pragma mark - UISceneOpenExternalURLOptions
// This object is created by your application and passed into a UIScene's openURL method.
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) NS_SWIFT_UI_ACTOR
@interface UISceneOpenExternalURLOptions : NSObject
// URLs must be universal links and have an app configured to open them.
@property (nonatomic, readwrite) BOOL universalLinksOnly;
// An event attribution associated with the external URL to open.
@property (nullable, nonatomic, copy) UIEventAttribution *eventAttribution API_AVAILABLE(ios(14.5)) API_UNAVAILABLE(watchos, tvos);
@end

#pragma mark - UISceneActivationRequestOptions
// This object is created by your application and passed with a UISceneSession activation request

typedef NS_ENUM(NSInteger, UISceneCollectionJoinBehavior) {
    UISceneCollectionJoinBehaviorAutomatic, // The scene follows system preferences for joining collections.
    UISceneCollectionJoinBehaviorPreferred, // If requestingScene is set, add the new scene to its collection and activate it. Otherwise attempt to join a compatible collection.
    UISceneCollectionJoinBehaviorDisallowed, // Create a new collection for the scene, ignoring system preferences.
    UISceneCollectionJoinBehaviorPreferredWithoutActivating, // If requestingScene is set, add the new scene without deactivating the requestingScene. Otherwise behaves the same as preferred. For example, in Catalyst this could be used to open a link in a new tab in the background.
}  API_AVAILABLE(macCatalyst(14.0)) API_UNAVAILABLE(ios, watchos, tvos);

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) NS_SWIFT_UI_ACTOR
@interface UISceneActivationRequestOptions : NSObject
// Informs the system the interface instance the user interacted with to create the new interface for the purposes of system navigation.
@property (nullable, nonatomic, readwrite, strong) UIScene *requestingScene;

// A scene collection is a group of scenes that display together. In Catalyst, this is used to add windows to an NSWindowTabGroup.
@property (nonatomic, readwrite) UISceneCollectionJoinBehavior collectionJoinBehavior  API_AVAILABLE(macCatalyst(14.0)) API_UNAVAILABLE(ios, watchos, tvos);
@end

#pragma mark - UISceneDestructionRequestOptions
// This object is created by your application and passed with a UISceneSession destruction request
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) NS_SWIFT_UI_ACTOR
@interface UISceneDestructionRequestOptions : NSObject
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UISceneOptions.h>
#endif
