#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIMenuController.h>)
//
//  UIMenuController.h
//  UIKit
//
//  Copyright (c) 2009-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_ENUM(NSInteger, UIMenuControllerArrowDirection) {
    UIMenuControllerArrowDefault, // up or down based on screen location
    UIMenuControllerArrowUp API_AVAILABLE(ios(3.2)),
    UIMenuControllerArrowDown API_AVAILABLE(ios(3.2)),
    UIMenuControllerArrowLeft API_AVAILABLE(ios(3.2)),
    UIMenuControllerArrowRight API_AVAILABLE(ios(3.2)),
} API_DEPRECATED("UIMenuController is deprecated. Use UIEditMenuInteraction instead.", ios(3.2, 16.0), visionos(1.0, 1.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos);

@class UIView, UIMenuItem;

UIKIT_EXTERN API_DEPRECATED("UIMenuController is deprecated. Use UIEditMenuInteraction instead.", ios(3.0, 16.0), visionos(1.0, 1.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIMenuController : NSObject

@property(class, nonatomic, readonly) UIMenuController *sharedMenuController;

@property(nonatomic,getter=isMenuVisible) BOOL menuVisible;	    // default is NO

- (void)setMenuVisible:(BOOL)menuVisible API_DEPRECATED("Use showMenuFromView:rect: or hideMenuFromView: instead.", ios(3.0, 13.0)) API_UNAVAILABLE(visionos);
- (void)setMenuVisible:(BOOL)menuVisible animated:(BOOL)animated API_DEPRECATED("Use showMenuFromView:rect: or hideMenuFromView: instead.", ios(3.0, 13.0)) API_UNAVAILABLE(visionos, watchos);

- (void)setTargetRect:(CGRect)targetRect inView:(UIView *)targetView API_DEPRECATED("Use showMenuFromView:rect: instead.", ios(3.0, 13.0)) API_UNAVAILABLE(visionos, watchos);

- (void)showMenuFromView:(UIView *)targetView rect:(CGRect)targetRect API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);
- (void)hideMenuFromView:(UIView *)targetView API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);
- (void)hideMenu API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

@property(nonatomic) UIMenuControllerArrowDirection arrowDirection API_AVAILABLE(ios(3.2)); // default is UIMenuControllerArrowDefault
		
@property(nullable, nonatomic,copy) NSArray<UIMenuItem *> *menuItems API_AVAILABLE(ios(3.2)); // default is nil. these are in addition to the standard items

- (void)update;	

@property(nonatomic,readonly) CGRect menuFrame;

@end

UIKIT_EXTERN NSNotificationName const UIMenuControllerWillShowMenuNotification API_DEPRECATED("UIMenuController is deprecated. Use UIEditMenuInteraction instead.", ios(3.0, 16.0), visionos(1.0, 1.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIMenuControllerDidShowMenuNotification API_DEPRECATED("UIMenuController is deprecated. Use UIEditMenuInteraction instead.", ios(3.0, 16.0), visionos(1.0, 1.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIMenuControllerWillHideMenuNotification API_DEPRECATED("UIMenuController is deprecated. Use UIEditMenuInteraction instead.", ios(3.0, 16.0), visionos(1.0, 1.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIMenuControllerDidHideMenuNotification API_DEPRECATED("UIMenuController is deprecated. Use UIEditMenuInteraction instead.", ios(3.0, 16.0), visionos(1.0, 1.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN NSNotificationName const UIMenuControllerMenuFrameDidChangeNotification API_DEPRECATED("UIMenuController is deprecated. Use UIEditMenuInteraction instead.", ios(3.0, 16.0), visionos(1.0, 1.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) NS_SWIFT_NONISOLATED;

UIKIT_EXTERN API_DEPRECATED("UIMenuItem is deprecated. Use UIEditMenuInteraction instead.", ios(3.2, 16.0), visionos(1.0, 1.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIMenuItem : NSObject 

- (instancetype)initWithTitle:(NSString *)title action:(SEL)action NS_DESIGNATED_INITIALIZER;

@property(nonatomic,copy) NSString *title;
@property(nonatomic)      SEL       action;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIMenuController.h>
#endif
