#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIMenuLeaf.h>)
//
//  UIMenuLeaf.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <UIKit/UIMenuElement.h>

NS_ASSUME_NONNULL_BEGIN

@class NSString, UIImage;
@protocol UIPopoverPresentationControllerSourceItem;

UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIMenuLeaf <NSObject>

/// Short display title.
@property (nonatomic, copy) NSString *title;

/// Image that can appear next to this element.
@property (nullable, nonatomic, copy) UIImage *image;

/// Image that can appear next to this action when the `state` is `UIMenuElementStateOn`
@property (nullable, nonatomic, copy) UIImage *selectedImage API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos);

/// Elaborated title used in keyboard shortcut overlay.
@property (nullable, nonatomic, copy) NSString *discoverabilityTitle;

/// The element's attributes.
@property (nonatomic) UIMenuElementAttributes attributes;

/// The element's selection state.
@property (nonatomic) UIMenuElementState state;

/// The leaf's preferred repeat behavior.
/// Menu leaves can repeatedly perform their primary actions on prolonged interactions,
/// such as by holding down their keyboard shortcut.
@property (nonatomic) UIMenuElementRepeatBehavior repeatBehavior;

/// The object on behalf of which the element's primary action is being performed.
/// This property is only populated during the execution of the element's
/// primary action (i.e. its handler or selector) if available.
@property (nonatomic, readonly, nullable) id sender;

/// Source item for subsequent presentations. For example, an element displayed in a menu attached to a
/// @c UIButton may return the button so that a popover may be presented from it when the element is tapped.
/// If available, this property is only populated during the execution of the element's action (i.e. its handler or selector).
@property (nonatomic, readonly, nullable) id<UIPopoverPresentationControllerSourceItem> presentationSourceItem API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos);

/// Performs the element’s primary action (i.e. it's handler or selector).
- (void)performWithSender:(nullable id)sender target:(nullable id)target;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIMenuLeaf.h>
#endif
