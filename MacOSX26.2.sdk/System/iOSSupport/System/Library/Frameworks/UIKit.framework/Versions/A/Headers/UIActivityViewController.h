#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<ShareSheet/UIActivityViewController.h>)
//
//  UIActivityViewController.h
//  UIKit
//
//  Copyright 2012-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIActivity.h>

NS_ASSUME_NONNULL_BEGIN

@protocol UIActivityItemsConfigurationReading;

typedef NS_OPTIONS(NSUInteger, UIActivitySectionTypes) {
	UIActivitySectionTypesNone = 0,
	UIActivitySectionTypesPeopleSuggestions = (1 << 0),
} API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos, tvos);

typedef void (^UIActivityViewControllerCompletionHandler)(UIActivityType __nullable activityType, BOOL completed) API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(watchos);
typedef void (^UIActivityViewControllerCompletionWithItemsHandler)(UIActivityType __nullable activityType, BOOL completed, NSArray * __nullable returnedItems, NSError * __nullable activityError) API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos);

API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(watchos) __TVOS_PROHIBITED @interface UIActivityViewController : UIViewController

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE;
- (instancetype)initWithActivityItems:(NSArray *)activityItems applicationActivities:(nullable NSArray<__kindof UIActivity *> *)applicationActivities NS_DESIGNATED_INITIALIZER;

@property(nullable, nonatomic, copy) UIActivityViewControllerCompletionHandler completionHandler API_DEPRECATED_WITH_REPLACEMENT("completionWithItemsHandler", ios(6.0, 8.0)) API_UNAVAILABLE(watchos);  // set to nil after activity performs or view controller is dismissed
@property(nullable, nonatomic, copy) UIActivityViewControllerCompletionWithItemsHandler completionWithItemsHandler API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos); // set to nil after activity performs or view controller is dismissed

@property(nullable, nonatomic, copy) NSArray<UIActivityType> *excludedActivityTypes; // default is nil. activity types listed will not be displayed

/// Hides some sections of the activity view controller. Default is none
@property (nonatomic) UIActivitySectionTypes excludedActivitySectionTypes API_AVAILABLE(ios(18.0)) API_UNAVAILABLE(watchos, tvos);

/// In some contexts, the activity view controller can elevate a specific activity in the header view to enhance it.
/// The prominent activity can only be chosen by the system.
/// Defaults to YES.
@property (nonatomic) BOOL allowsProminentActivity API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(watchos, tvos);

@end

@interface UIActivityViewController (UIActivityItemsConfiguration)

- (instancetype)initWithActivityItemsConfiguration:(id<UIActivityItemsConfigurationReading>)activityItemsConfiguration API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) API_UNAVAILABLE(tvos);

@end

NS_ASSUME_NONNULL_END

#else
#import <ShareSheet/UIActivityViewController.h>
#endif
