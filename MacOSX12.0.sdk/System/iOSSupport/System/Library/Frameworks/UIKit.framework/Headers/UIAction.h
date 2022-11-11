#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIAction.h>)
//
//  UIAction.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIMenu.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString *UIActionIdentifier NS_SWIFT_NAME(UIAction.Identifier) NS_TYPED_EXTENSIBLE_ENUM API_AVAILABLE(ios(13.0));

/// Default action identifiers for paste variants
UIKIT_EXTERN const UIActionIdentifier UIActionPaste API_AVAILABLE(ios(15.0));
UIKIT_EXTERN const UIActionIdentifier UIActionPasteAndMatchStyle API_AVAILABLE(ios(15.0));
UIKIT_EXTERN const UIActionIdentifier UIActionPasteAndGo API_AVAILABLE(ios(15.0));
UIKIT_EXTERN const UIActionIdentifier UIActionPasteAndSearch API_AVAILABLE(ios(15.0));

@class UIAction;

typedef void (^UIActionHandler)(__kindof UIAction *action);

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) NS_SWIFT_UI_ACTOR
@interface UIAction : UIMenuElement

/// Short display title.
@property (nonatomic, copy) NSString *title;

/// Image that can appear next to this action.
@property (nullable, nonatomic, copy) UIImage *image;

/// Elaborated title, if any.
@property (nullable, nonatomic, copy) NSString *discoverabilityTitle;

/// This action's identifier.
@property (nonatomic, readonly) UIActionIdentifier identifier;

/// This action's style.
@property (nonatomic) UIMenuElementAttributes attributes;

/// State that can appear next to this action.
@property (nonatomic) UIMenuElementState state;

/// If available, the object on behalf of which the actionHandler is called.
@property (nonatomic, readonly, nullable) id sender API_AVAILABLE(ios(14.0));

/*!
 * @abstract Creates a UIAction with an empty title, nil image, and automatically generated identifier
 *
 * @param handler  Handler block. Called when the user selects the action.
 *
 * @return A new UIAction.
 */
+ (instancetype)actionWithHandler:(UIActionHandler)handler API_AVAILABLE(ios(14.0)) NS_SWIFT_UNAVAILABLE("Use init(title:image:identifier:discoverabilityTitle:attributes:state:handler:) instead.");

/*!
 * @abstract Creates a UIAction with the given arguments.
 *
 * @param title    The action's title.
 * @param image    Image that can appear next to this action, if needed.
 * @param identifier  The action's identifier. Pass nil to use an auto-generated identifier.
 * @param handler  Handler block. Called when the user selects the action.
 *
 * @return A new UIAction.
 */
+ (instancetype)actionWithTitle:(NSString *)title
                          image:(nullable UIImage *)image
                     identifier:(nullable UIActionIdentifier)identifier
                        handler:(UIActionHandler)handler
    NS_SWIFT_UNAVAILABLE("Use init(title:image:identifier:discoverabilityTitle:attributes:state:handler:) instead.");

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@protocol UIKeyInput;
@class UIResponder;

@interface UIAction (UICaptureTextFromCameraSupporting)

/*!
 * @abstract Creates a new UIAction for the captureTextFromCamera: standard edit action.
 *
 * @param responder The UIKeyInput responder to send captureTextFromCamera: to.
 * @param identifier  The action's identifier. Pass nil to use an auto-generated identifier.
 *
 * @return A new UIAction.
 */
+ (instancetype)captureTextFromCameraActionForResponder:(UIResponder<UIKeyInput> *)responder identifier:(nullable UIActionIdentifier)identifier NS_SWIFT_NAME(captureTextFromCamera(responder:identifier:)) API_AVAILABLE(ios(15.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIAction.h>
#endif
