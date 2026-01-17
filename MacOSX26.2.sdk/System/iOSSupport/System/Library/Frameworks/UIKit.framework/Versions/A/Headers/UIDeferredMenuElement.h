#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDeferredMenuElement.h>)
//
//  UIDeferredMenuElement.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIMenuElement.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NSString *UIDeferredMenuElementIdentifier NS_SWIFT_NAME(UIDeferredMenuElement.Identifier) NS_TYPED_EXTENSIBLE_ENUM API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIDeferredMenuElement : UIMenuElement

/// The identifier of this deferred menu element.
@property (nonatomic, copy, readonly) UIDeferredMenuElementIdentifier identifier API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos);

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

/*!
 * @abstract Returns a placeholder menu element that is replaced with the result of the block's
 *           completion handler. A loading UI takes the place of the element in the menu
 *           until it is fulfilled. Elements created using this initializer are "uncached",
 *           so their @c elementProvider block is called every time the element is displayed.
 *
 * @param elementProvider  Called by the system to request the deferred menu items when the containing menu is presented.
 *                         Call this block's completion handler when the menu items are available.
 */
+ (instancetype)elementWithUncachedProvider:(void(^)(void(^completion)(NSArray<UIMenuElement *> *elements)))elementProvider API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);

/*!
 * @abstract Returns a placeholder menu element that is replaced with elements provided from the responder chain.
 *           A loading UI takes the place of the element in the menu until it is fulfilled. The element may be stored
 *           and re-used across menus.
 *
 * @param identifier An identifier for this deferred element that responders can check to determine which elements
 *                   to provide.
 * @param shouldCacheItems Whether or not the deferred element caches items. Passing in @c YES causes this deferred element to
 *                         ask the responder chain for elements only once, when the element is first encountered in a menu.
 *                         Passing in @c NO asks the responder chain for elements every time the element is displayed.
 */
+ (instancetype)elementUsingFocusWithIdentifier:(UIDeferredMenuElementIdentifier)identifier shouldCacheItems:(BOOL)shouldCacheItems API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(usingFocus(identifier:shouldCacheItems:));

@end


/*!
 * @abstract Represents an element provider for a deferred menu element.
 *           When the containing menu for a responder-based deferred element is presented, the system asks the
 *           responder chain for one of these element providers for the deferred element.
 */
UIKIT_EXTERN API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(UIDeferredMenuElement.Provider) NS_SWIFT_UI_ACTOR
@interface UIDeferredMenuElementProvider : NSObject

/*!
 * @abstract Creates a deferred menu element provider with an asynchronous block.
 *
 * @param elementProvider An asynchronous element provider block. Call this block's completion handler when the responder's
 *                        menu items are available.
 */
+ (instancetype)providerWithElementProvider:(void(^)(void(^completion)(NSArray<UIMenuElement *> *elements)))elementProvider NS_SWIFT_NAME(init(_:));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIDeferredMenuElement.h>
#endif
