#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextSelectionDisplayInteraction.h>)
//
//  UITextSelectionDisplayInteraction.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitCore.h>

#import <UIKit/UIInteraction.h>
#import <UIKit/UITextCursorView.h>
#import <UIKit/UITextSelectionHandleView.h>
#import <UIKit/UITextSelectionHighlightView.h>

NS_ASSUME_NONNULL_BEGIN

@class UITextSelectionDisplayInteraction;
@protocol UITextCursorView;

UIKIT_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UITextSelectionDisplayInteractionDelegate <NSObject>

@optional
/// If different than the view that the interaction is installed onto, one can return a container view here for
/// selection views that draw _below_ text. Includes selection highlight view, etc. The default is assumed
/// that all views are to be installed onto the interaction's view.
- (nullable UIView *)selectionContainerViewBelowTextForSelectionDisplayInteraction:(UITextSelectionDisplayInteraction *)interaction;

@end

/// @class      @c UITextSelectionDisplayInteraction
/// @abstract   Manages a collection of selection views (cursor, highlight, range adjustment) for a particular UITextInput object.
/// @discussion This is the component that @c UITextInteraction  generally talks to in order to accomplish all selection display
///             using a collection of "managed subviews", i.e., selection view components that actually manage the display of the selection
///             and the various affordances for changing the selection.
UIKIT_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UITextSelectionDisplayInteraction : NSObject <UIInteraction>

/// Controls both the hidden sate of contained selection views as well as interactions that follow.
@property (nonatomic, readwrite, assign, getter=isActivated) BOOL activated;

/// The object the selection is being managed for.
@property (nonatomic, weak, readonly) id<UITextInput> textInput;

/// See @c UITextSelectionDisplayInteractionDelegate.
@property (nonatomic, weak, readonly) id<UITextSelectionDisplayInteractionDelegate> delegate;

/// The cursor view (also known as "caret" view). Shown when the selection is not ranged.
@property (nonatomic, strong) UIView<UITextCursorView> *cursorView;

/// The highlight view. This is the blue/tinted highlight drawn behind the rendered text.
@property (nonatomic, strong) UIView<UITextSelectionHighlightView> *highlightView;

/// @abstract   The selection handles, shown adjacent to the highlight view's @c selectionRects when the selection is ranged.
/// @discussion If you are replacing these system-provided handle views with your own, you must provide exactly two handle views, one to be used as the leading handle,
///             and another to be used as the trailing handle.
@property (nonatomic, strong) NSArray<UIView<UITextSelectionHandleView> *> *handleViews;

/// Creates a UITextSelectionDisplayInteractionDelegate for a given object that implements the UITextInput protocol.
/// `textInput` may be the same as the view this interaction is installed onto.
- (instancetype)initWithTextInput:(id<UITextInput>)textInput
                        delegate:(id<UITextSelectionDisplayInteractionDelegate>)delegate
                        NS_DESIGNATED_INITIALIZER;

/// Loads the selection from `-[UITextInput selectedTextRange]` and applies the selection to all managed subviews.
- (void)layoutManagedSubviews;

/// Call this whenever the selection changes, or needs to be re-laid out.
- (void)setNeedsSelectionUpdate;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITextSelectionDisplayInteraction.h>
#endif
