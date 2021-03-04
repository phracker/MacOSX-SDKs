#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDeferredMenuElement.h>)
//
//  UIDeferredMenuElement.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIMenuElement.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(14.0)) @interface UIDeferredMenuElement : UIMenuElement

/*!
 * @abstract Returns a placeholder menu element that is replaced with the result of the block's
 *           completion handler. A loading UI takes the place of the element in the menu
 *           until it is fulfilled. While the element may be stored and re-used across menus, its block is
 *           called only once, when the element is first encountered in a menu.
 *
 * @param elementProvider  Called by the system to request the deferred menu items when the containing menu is presented.
 *                         Call this block's completion handler when the menu items are available.
 */
+ (instancetype)elementWithProvider:(void(^)(void(^completion)(NSArray<UIMenuElement *> *elements)))elementProvider;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIDeferredMenuElement.h>
#endif
