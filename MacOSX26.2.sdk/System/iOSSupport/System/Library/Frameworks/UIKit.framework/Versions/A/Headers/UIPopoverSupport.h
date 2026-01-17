#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPopoverSupport.h>)
//
//  UIPopoverSupport.h
//  UIKit
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIViewController.h>

typedef NS_OPTIONS(NSUInteger, UIPopoverArrowDirection) {
    UIPopoverArrowDirectionUp = 1UL << 0,
    UIPopoverArrowDirectionDown = 1UL << 1,
    UIPopoverArrowDirectionLeft = 1UL << 2,
    UIPopoverArrowDirectionRight = 1UL << 3,
    UIPopoverArrowDirectionAny = UIPopoverArrowDirectionUp | UIPopoverArrowDirectionDown | UIPopoverArrowDirectionLeft | UIPopoverArrowDirectionRight,
    UIPopoverArrowDirectionUnknown = NSUIntegerMax
} API_UNAVAILABLE(watchos);

@interface UIViewController (UIPopoverController)

/* modalInPopover is set on the view controller when you wish to force the popover hosting the view controller into modal behavior. When this is active, the popover will ignore events outside of its bounds until this is set to NO.
 */
@property (nonatomic,readwrite,getter=isModalInPopover) BOOL modalInPopover API_DEPRECATED_WITH_REPLACEMENT("modalInPresentation", ios(3.2, 13.0)) API_UNAVAILABLE(visionos, watchos);

/* contentSizeForViewInPopover allows you to set the size of the content from within the view controller. This property is read/write, and you should generally not override it.
 */
@property (nonatomic,readwrite) CGSize contentSizeForViewInPopover API_DEPRECATED_WITH_REPLACEMENT("preferredContentSize", ios(3.2, 7.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(visionos, watchos);

@end


#else
#import <UIKitCore/UIPopoverSupport.h>
#endif
