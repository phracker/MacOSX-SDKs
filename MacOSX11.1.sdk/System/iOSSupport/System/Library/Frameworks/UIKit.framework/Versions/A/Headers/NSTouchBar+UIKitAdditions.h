#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/NSTouchBar+UIKitAdditions.h>)
//
//  NSTouchBar+UIKitAdditions.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <TargetConditionals.h>

#if TARGET_OS_MACCATALYST

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIResponder.h>
#import <UIKit/UIViewController.h>
#import <UIKit/UIActivityItemsConfigurationReading.h>
#import <AppKit/NSTouchBar.h>
#import <AppKit/NSSharingServicePickerTouchBarItem.h>

@class UIResponder, UIViewController;

NS_ASSUME_NONNULL_BEGIN

@interface UIResponder (NSTouchBarProvider) <NSTouchBarProvider>
/*
 The NSTouchBar object associated with this responder. If no NSTouchBar is explicitly set, UIResponder will send -makeTouchBar to itself to create the default NSTouchBar for this responder.
 */
@property (nonatomic, strong, readwrite, nullable) NSTouchBar *touchBar API_AVAILABLE(macCatalyst(13.0));
/*
 Subclasses should override this method to create and configure the default NSTouchBar for this responder.
 */
- (nullable NSTouchBar *)makeTouchBar API_AVAILABLE(macCatalyst(13.0));
@end

@interface UIViewController (NSTouchBarProvider)
/*
 Override to return a child view controller or nil. If non-nil, that view controller's touchBar will be used. If nil, self is used.
 Defaults to nil.
 */
@property (nonatomic, readonly, nullable) UIViewController *childViewControllerForTouchBar API_AVAILABLE(macCatalyst(13.0));
/*
 Whenever the return value from -childViewControllerForTouchBar changes, -setNeedsTouchBarUpdate should be called.
 */
- (void)setNeedsTouchBarUpdate API_AVAILABLE(macCatalyst(13.0));

@end

@interface NSSharingServicePickerTouchBarItem (UIActivityItemsConfiguration)
/*
 Expresses the payload of what should be shared.
 If nil or the activityItemsConfiguration contains no valid data, the item will be disabled.
 */
@property (nonatomic, nullable, strong) id<UIActivityItemsConfigurationReading> activityItemsConfiguration;
@end

NS_ASSUME_NONNULL_END

#endif

#else
#import <UIKitCore/NSTouchBar+UIKitAdditions.h>
#endif
