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

typedef void (^UIActivityViewControllerCompletionHandler)(UIActivityType __nullable activityType, BOOL completed);
typedef void (^UIActivityViewControllerCompletionWithItemsHandler)(UIActivityType __nullable activityType, BOOL completed, NSArray * __nullable returnedItems, NSError * __nullable activityError);

NS_CLASS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED @interface UIActivityViewController : UIViewController

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE;
- (instancetype)initWithActivityItems:(NSArray *)activityItems applicationActivities:(nullable NSArray<__kindof UIActivity *> *)applicationActivities NS_DESIGNATED_INITIALIZER;

@property(nullable, nonatomic, copy) UIActivityViewControllerCompletionHandler completionHandler API_DEPRECATED_WITH_REPLACEMENT("completionWithItemsHandler", ios(6.0, 8.0));  // set to nil after activity performs or view controller is dismissed
@property(nullable, nonatomic, copy) UIActivityViewControllerCompletionWithItemsHandler completionWithItemsHandler API_AVAILABLE(ios(8.0)); // set to nil after activity performs or view controller is dismissed

@property(nullable, nonatomic, copy) NSArray<UIActivityType> *excludedActivityTypes; // default is nil. activity types listed will not be displayed

@end

@interface UIActivityViewController (UIActivityItemsConfiguration)

- (instancetype)initWithActivityItemsConfiguration:(id<UIActivityItemsConfigurationReading>)activityItemsConfiguration API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END

#else
#import <ShareSheet/UIActivityViewController.h>
#endif
