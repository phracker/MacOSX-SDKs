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

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UIMenuControllerArrowDirection) {
    UIMenuControllerArrowDefault, // up or down based on screen location
    UIMenuControllerArrowUp API_AVAILABLE(ios(3.2)),
    UIMenuControllerArrowDown API_AVAILABLE(ios(3.2)),
    UIMenuControllerArrowLeft API_AVAILABLE(ios(3.2)),
    UIMenuControllerArrowRight API_AVAILABLE(ios(3.2)),
} API_UNAVAILABLE(tvos);

@class UIView, UIMenuItem;

UIKIT_EXTERN API_AVAILABLE(ios(3.0)) API_UNAVAILABLE(tvos) @interface UIMenuController : NSObject

@property(class, nonatomic, readonly) UIMenuController *sharedMenuController;

@property(nonatomic,getter=isMenuVisible) BOOL menuVisible;	    // default is NO

- (void)setMenuVisible:(BOOL)menuVisible API_DEPRECATED("Use showMenuFromView:rect: or hideMenuFromView: instead.", ios(3.0, 13.0));
- (void)setMenuVisible:(BOOL)menuVisible animated:(BOOL)animated API_DEPRECATED("Use showMenuFromView:rect: or hideMenuFromView: instead.", ios(3.0, 13.0));

- (void)setTargetRect:(CGRect)targetRect inView:(UIView *)targetView API_DEPRECATED("Use showMenuFromView:rect: instead.", ios(3.0, 13.0));

- (void)showMenuFromView:(UIView *)targetView rect:(CGRect)targetRect API_AVAILABLE(ios(13.0));
- (void)hideMenuFromView:(UIView *)targetView API_AVAILABLE(ios(13.0));
- (void)hideMenu API_AVAILABLE(ios(13.0));

@property(nonatomic) UIMenuControllerArrowDirection arrowDirection API_AVAILABLE(ios(3.2)); // default is UIMenuControllerArrowDefault
		
@property(nullable, nonatomic,copy) NSArray<UIMenuItem *> *menuItems API_AVAILABLE(ios(3.2)); // default is nil. these are in addition to the standard items

- (void)update;	

@property(nonatomic,readonly) CGRect menuFrame;

@end

UIKIT_EXTERN NSNotificationName const UIMenuControllerWillShowMenuNotification API_UNAVAILABLE(tvos);
UIKIT_EXTERN NSNotificationName const UIMenuControllerDidShowMenuNotification API_UNAVAILABLE(tvos);
UIKIT_EXTERN NSNotificationName const UIMenuControllerWillHideMenuNotification API_UNAVAILABLE(tvos);
UIKIT_EXTERN NSNotificationName const UIMenuControllerDidHideMenuNotification API_UNAVAILABLE(tvos);
UIKIT_EXTERN NSNotificationName const UIMenuControllerMenuFrameDidChangeNotification API_UNAVAILABLE(tvos);

UIKIT_EXTERN API_AVAILABLE(ios(3.2)) API_UNAVAILABLE(tvos) @interface UIMenuItem : NSObject 

- (instancetype)initWithTitle:(NSString *)title action:(SEL)action NS_DESIGNATED_INITIALIZER;

@property(nonatomic,copy) NSString *title;
@property(nonatomic)      SEL       action;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIMenuController.h>
#endif
