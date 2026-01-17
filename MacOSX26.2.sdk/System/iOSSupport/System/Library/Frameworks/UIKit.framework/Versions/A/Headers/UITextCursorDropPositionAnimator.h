#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextCursorDropPositionAnimator.h>)
//
//  UITextCursorDropPositionAnimator.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UITextCursorView.h>
#import <UIKit/UITextInput.h>

/// @class      @c UITextCursorDropPositionAnimator
/// @abstract   Provides a mechanism for displaying and animating a temporary text cursor to indicate a drop location.
/// @discussion For custom text view implementations that implement drag and drop functionality, use this animator providing either your own UITextCursorView
///             implementation or a concrete implementation to indicate at which point in your document the dropped item will be inserted. Using this animator provides
///             you with all of the default system animations for how the text cursor would behave.
UIKIT_EXTERN API_AVAILABLE(ios(17.4)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UITextCursorDropPositionAnimator : NSObject

/// The cursor view to be animated.
@property (nonatomic, readonly) UIView<UITextCursorView> *cursorView;

/// The object that implements the UITextInput protocol, used to query for geometry information regarding cursor placement.
@property (nonatomic, readonly) UIView<UITextInput> *textInput;

/// Creates an animator for the given text cursor view implementation, and the document object that implements the UITextInput protocol.
- (instancetype)initWithTextCursorView:(UIView<UITextCursorView> *)cursorView textInput:(UIView<UITextInput> *)textInput NS_DESIGNATED_INITIALIZER;

/// Controls the visibility of the cursor.
- (void)setCursorVisible:(BOOL)visible animated:(BOOL)animated;

/// Controls the placement of the cursor, using @c textInput and @c position to compute the final frame for the cursor view.
- (void)placeCursorAtPosition:(UITextPosition *)position animated:(BOOL)animated;

/// Optionally, provide an animation block or completion block to run alongside cursor appearance or position update animations.
- (void)animateAlongsideChanges:(void (^ __nullable)(void))animation completion:(void (^ __nullable)(void))completion;

- (instancetype)init NS_UNAVAILABLE;
@end

#else
#import <UIKitCore/UITextCursorDropPositionAnimator.h>
#endif
