#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDocumentViewControllerLaunchOptions.h>)
//
//  UIDocumentViewControllerLaunchOptions.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <UIKit/UIAction.h>
#import <UIKit/UIBackgroundConfiguration.h>
#import <UIKit/UIDocument.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIDocumentBrowserViewController;

UIKIT_EXTERN API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_NAME(UIDocumentViewController.LaunchOptions) NS_SWIFT_UI_ACTOR
@interface UIDocumentViewControllerLaunchOptions : NSObject

/// The view controller for browsing documents to open.
@property (nonatomic, strong) UIDocumentBrowserViewController *browserViewController;

/// The title of the view. Default is the application's name.
@property (nonatomic, copy) NSString *title;

/// The primary action.
@property (nonatomic, copy, nullable) UIAction *primaryAction;

/// The secondary action.
@property (nonatomic, copy, nullable) UIAction *secondaryAction;

/// The view which displays an open document. Default is the view controller's view.
@property (nonatomic, strong, nullable) UIView *documentTargetView;

/// The foreground accessory view.
@property (nonatomic, strong, nullable) UIView *foregroundAccessoryView;

/// The background accessory view.
@property (nonatomic, strong, nullable) UIView *backgroundAccessoryView;

/// The background configuration.
@property (nonatomic, strong) UIBackgroundConfiguration *background NS_REFINED_FOR_SWIFT;

/// Returns an action which requests the creation of a new document with the specified intent.
/// Can be used for either the primary or secondary action.
+ (UIAction *)createDocumentActionWithIntent:(UIDocumentCreationIntent)intent;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIDocumentViewControllerLaunchOptions.h>
#endif
