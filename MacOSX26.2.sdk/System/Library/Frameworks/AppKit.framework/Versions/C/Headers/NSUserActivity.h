/*
    NSUserActivity.h
    Application Kit
    Copyright (c) 2014-2024, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSUserActivity.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSResponder.h>
#import <AppKit/NSDocument.h>

#if __OBJC2__
#define NS_USER_ACTIVITY_SUPPORTED 1
#endif

#if NS_USER_ACTIVITY_SUPPORTED

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@protocol NSUserActivityRestoring <NSObject>
/* This method exists to be overridden and will be called from the main thread. It will be called on any objects passed to the restorationHandler given to application:continueUserActivity:restorationHandler: below. You should use the state in the userInfo to restore the object. On macOS, activities managed by NSDocument can be restored automatically, if NO is returned from application:continueActivity:restorationHandler: (or it is unimplemented). In this situation, the document will be opened via -[NSDocumentController openDocumentWithContentsOfURL:display:completionHandler:], and will have restoreUserActivityState: called on it. */
- (void)restoreUserActivityState:(NSUserActivity *)userActivity NS_SWIFT_UI_ACTOR API_AVAILABLE(macos(10.10));
@end

@interface NSResponder (NSUserActivity) <NSUserActivityRestoring>

/*
 Setting an NSUserActivity will cause it to become managed by AppKit/UIKit. NSUserActivities managed by AppKit/UIKit will be saved automatically at an appropriate time. You will have an opportunity to add state representing the user’s activity via the below updateUserActivityState: override. It is recommended that you override the updateUserActivityState: method to lazily write any state to the userInfo.

 On macOS, NSUserActivities managed by NSResponder will automatically becomeCurrent based on the main window and the responder chain.

 To unassociate an object from the user activity, you can set this to nil. If no objects are associated with an NSUserActivity managed by AppKit/UIKit, it will be removed.

 This property can be used from any thread.
 
 This property is KVO observable.
 */
@property (nullable, strong) NSUserActivity *userActivity API_AVAILABLE(macos(10.10));

/* This method exists to be overridden and will be called from the main thread. You should save any state representing the user's activity into the NSUserActivity's userInfo via its -addUserInfoEntriesFromDictionary method. When the state is out of date, you should mark the userActivity as needing to save via the needsSave property, and your override will be invoked again at an appropriate time. */
- (void)updateUserActivityState:(NSUserActivity *)userActivity API_AVAILABLE(macos(10.10));

@end

@interface NSDocument (NSUserActivity) <NSUserActivityRestoring>

/*
 This works just like the above responder methods for the most part.

 On macOS, NSUserActivities managed by NSDocument will automatically become current when any of the document window controller's window's become main. You will need to invoke [[document userActivity] becomeCurrent] at an appropriate time if there aren't any.

 If there is a CFBundleDocumentTypes entry for the document's type with a NSUbiquitousDocumentUserActivityType key, AppKit/UIKit will automatically create an NSUserActivity with the given activityType when the document is ubiquitous. When it is non-ubiquitous, the userActivity will be nil. Note that userActivity is KVO observable, in case the userActivity is being shared with other objects that need to be kept in sync as the document moves into and out of iCloud.
 */
@property (nullable, strong) NSUserActivity *userActivity API_AVAILABLE(macos(10.10));

/* On macOS, the default implementation of this will put the fileURL into the userInfo with the NSUserActivityDocumentURLKey. NSDocument will automatically call needsSave on the userActivity when the fileURL changes. */
- (void)updateUserActivityState:(NSUserActivity *)activity API_AVAILABLE(macos(10.10));

@end

#if !TARGET_OS_IPHONE
/* When NSUbiquitousDocumentUserActivityType is present in a CFBundleDocumentTypes entry, AppKit will automatically create an NSUserActivity for documents in iCloud, using the given activityType. */
APPKIT_EXTERN NSString * const NSUserActivityDocumentURLKey API_AVAILABLE(macos(10.10));
#endif

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)

#endif
