#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneOptions.h>)
//
//  UISceneOptions.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class UIScene, UIOpenURLContext, UNNotificationResponse, UIApplicationShortcutItem, CKShareMetadata;

NS_ASSUME_NONNULL_BEGIN

#pragma mark - UISceneConnectionOptions
// This object is vended to your application by UIKit when a UIScene connects to a session
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) @interface UISceneConnectionOptions : NSObject
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
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) @interface UISceneOpenURLOptions : NSObject
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

// A NSString containing the bundle ID of the originating application.
// non-nil if the originating application and this application share the same team identifier.
@property (nullable, nonatomic, readonly) NSString *sourceApplication;

// A property-list typed object corresponding to what the originating application passed in UIDocumentInteractionController's annotation property
@property (nullable, nonatomic, readonly) id annotation;

// Copy the file before use if this value is NO
@property (nonatomic, readonly) BOOL openInPlace;
@end

#pragma mark - UISceneOpenExternalURLOptions
// This object is created by your application and passed into a UIScene's openURL method.
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) @interface UISceneOpenExternalURLOptions : NSObject
// URLs must be universal links and have an app configured to open them.
@property (nonatomic, readwrite) BOOL universalLinksOnly;
@end

#pragma mark - UISceneActivationRequestOptions
// This object is created by your application and passed with a UISceneSession activation request
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) @interface UISceneActivationRequestOptions : NSObject
// Informs the system the interface instance the user interacted with to create the new interface for the purposes of system navigation.
@property (nullable, nonatomic, readwrite, strong) UIScene *requestingScene;
@end

#pragma mark - UISceneDestructionRequestOptions
// This object is created by your application and passed with a UISceneSession destruction request
UIKIT_EXTERN API_AVAILABLE(ios(13.0)) @interface UISceneDestructionRequestOptions : NSObject
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UISceneOptions.h>
#endif
