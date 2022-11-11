#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIStateRestoration.h>)
/*
 *  UIStateRestoration.h
 *  UIKit
 *
 *  Copyright 2012-2018 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark -- State Restoration Coder Keys --

// UIStoryBoard that originally created the ViewController that saved state, nil if no UIStoryboard

UIKIT_EXTERN NSString *const UIStateRestorationViewControllerStoryboardKey API_AVAILABLE(ios(6.0));

// NSString with value of info.plist's Bundle Version (app version) when state was last saved for the app
UIKIT_EXTERN NSString *const UIApplicationStateRestorationBundleVersionKey API_AVAILABLE(ios(6.0));

// NSNumber containing the UIUserInterfaceIdiom enum value of the app that saved state
UIKIT_EXTERN NSString *const UIApplicationStateRestorationUserInterfaceIdiomKey API_AVAILABLE(ios(6.0));

// NSDate specifying the date/time the state restoration archive was saved. This is in UTC.
UIKIT_EXTERN NSString *const UIApplicationStateRestorationTimestampKey API_AVAILABLE(ios(7.0));

// NSString with value of the system version (iOS version) when state was last saved for the app
UIKIT_EXTERN NSString *const UIApplicationStateRestorationSystemVersionKey API_AVAILABLE(ios(7.0));

@class UIView;
@class UIViewController;

#pragma mark -- State Restoration protocols for UIView and UIViewController --

// A class must implement this protocol if it is specified as the restoration class of a UIViewController.
NS_SWIFT_UI_ACTOR
@protocol UIViewControllerRestoration
+ (nullable UIViewController *) viewControllerWithRestorationIdentifierPath:(NSArray<NSString *> *)identifierComponents coder:(NSCoder *)coder;
@end

NS_SWIFT_UI_ACTOR
@protocol UIDataSourceModelAssociation
- (nullable NSString *) modelIdentifierForElementAtIndexPath:(NSIndexPath *)idx inView:(UIView *)view;
- (nullable NSIndexPath *) indexPathForElementWithModelIdentifier:(NSString *)identifier inView:(UIView *)view;
@end

#pragma mark -- State Restoration object protocols and methods --

@protocol UIObjectRestoration;
// Conform to this protocol if you want your objects to participate in state restoration. 
//
// To participate in state restoration, the function registerObjectForStateRestoration must
// be called for the object.
NS_SWIFT_UI_ACTOR
@protocol UIStateRestoring <NSObject>
@optional
// The parent property is used to scope the restoration identifier path for an object, to
// disambiguate it from other objects that might be using the same identifier. The parent
// must be a restorable object or a view controller, else it will be ignored.
@property (nonatomic, readonly, nullable) id<UIStateRestoring> restorationParent;

// The restoration class specifies a class which is consulted during restoration to find/create
// the object, rather than trying to look it up implicitly
@property (nonatomic, readonly, nullable) Class<UIObjectRestoration> objectRestorationClass;

// Methods to save and restore state for the object. If these aren't implemented, the object
// can still be referenced by other objects in state restoration archives, but it won't
// save/restore any state of its own.
- (void) encodeRestorableStateWithCoder:(NSCoder *)coder;
- (void) decodeRestorableStateWithCoder:(NSCoder *)coder;


// applicationFinishedRestoringState is called on all restored objects that implement the method *after* all other object
// decoding has been done (including the application delegate). This allows an object to complete setup after state
// restoration, knowing that all objects from the restoration archive have decoded their state.
- (void) applicationFinishedRestoringState;
@end

// Protocol for classes that act as a factory to find a restorable object during state restoration
// A class must implement this protocol if it is specified as the restoration class of a UIRestorableObject.
NS_SWIFT_UI_ACTOR
@protocol UIObjectRestoration
+ (nullable id<UIStateRestoring>) objectWithRestorationIdentifierPath:(NSArray<NSString *> *)identifierComponents coder:(NSCoder *)coder;
@end

NS_ASSUME_NONNULL_END



#else
#import <UIKitCore/UIStateRestoration.h>
#endif
