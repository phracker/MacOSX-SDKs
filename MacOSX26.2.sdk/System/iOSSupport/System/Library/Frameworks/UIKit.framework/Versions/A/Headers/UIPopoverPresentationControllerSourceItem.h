#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPopoverPresentationControllerSourceItem.h>)
//
//  UIPopoverPresentationControllerSourceItem.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIView.h>
#import <UIKit/UILayoutGuide.h>
#import <UIKit/UIBarButtonItem.h>
#import <UIKit/UITabBarItem.h>

#if TARGET_OS_MACCATALYST || TARGET_OS_OSX
#import <AppKit/NSToolbarItem.h>
#endif // TARGET_OS_MACCATALYST

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos)
@protocol UIPopoverPresentationControllerSourceItem <NSObject>

- (CGRect)frameInView:(UIView *)referenceView API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(tvos, watchos);

@end

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos)
@interface UIView (UIPopoverPresentationControllerSourceItem) <UIPopoverPresentationControllerSourceItem>
@end

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos)
@interface UILayoutGuide (UIPopoverPresentationControllerSourceItem) <UIPopoverPresentationControllerSourceItem>
@end

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos)
@interface UIBarButtonItem (UIPopoverPresentationControllerSourceItem) <UIPopoverPresentationControllerSourceItem>
@end

API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos)
@interface UITabBarItem (UIPopoverPresentationControllerSourceItem) <UIPopoverPresentationControllerSourceItem>
@end

#if TARGET_OS_MACCATALYST || TARGET_OS_OSX
API_AVAILABLE(macCatalyst(16.0))
@interface NSToolbarItem (UIPopoverPresentationControllerSourceItem) <UIPopoverPresentationControllerSourceItem>
@end
#endif // TARGET_OS_MACCATALYST

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIPopoverPresentationControllerSourceItem.h>
#endif
